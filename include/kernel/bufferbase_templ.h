/* 
 * File:   bufferbase_templ.h
 * Author: sealeks@mail.ru
 *
 * Created on 18 Май 2011 г., 0:15
 */

#ifndef _KERNEL_BUFFERBASE_TEMPL_H
#define	_KERNEL_BUFFERBASE_TEMPL_H

#include <kernel/constdef.h>
#include <kernel/systemutil.h>

namespace dvnci {
    
    const size_t TREND_EPOHPERIOD = 3600 * 8;
    const size_t REPORT_EPOHPERIOD = 3600 * 24 * 7200;
    
    
 
    template <typename TIMETYPE, typename VALUETYPE, size_t ITEM_BUFFER_SIZE, size_t EPOHPERIOD >
    struct logpoint {

        typedef TIMETYPE                    timetype;
        typedef VALUETYPE                   valuetype;

        struct logline_header {

            logline_header(double min, double max) : mtx_(), cnt_(0), maxcnt_(ITEM_BUFFER_SIZE), cursor_(0), epohtime_(),
            nextepohtime_(), expireepohtime_(), mineu_(min), maxeu_(max), free_(false) {}

            size_t count() const {
                return cnt_;}

            size_t maxcount() const {
                return maxcnt_;}

            size_t cursor() const {
                return cursor_;}

            bool isepoch() const {
                return (!epohtime_.is_not_a_date_time());}

            void epoch(const datetime & dt) {
                epohtime_ = incsecond(dt, -1);
                nextepohtime_ = incsecond(epohtime_, EPOHPERIOD);
                expireepohtime_ = incsecond(epohtime_, 2 * EPOHPERIOD);}

            bool isexpire(const datetime & dt) const  {
                return (expireepohtime_ < dt);}

            datetime epoch() const {
                return epohtime_;}

            datetime nextepoch() const {
                return nextepohtime_;}

            datetime expireepoch() const {
                return expireepohtime_;}

            bool free() const {
                return free_;}

            bool needwrite() const {
                return needwrite_;}

            void needwrite(bool vl)  {
                needwrite_=vl;}

            void clear( bool withfree = false) {
                cnt_ = 0;
                cursor_ = 0;
                datetime tmp;
                epohtime_ = tmp;
                nextepohtime_ = tmp;
                expireepohtime_ = tmp;
                free_ = withfree;}

            void range(const double& min, const double& max) {
                if ((mineu_ != min) || (maxeu_ != max)) {
                    mineu_ = min;
                    maxeu_ = max;
                    cnt_ = 0;
                    cursor_ = 0;
                    datetime tmp;
                    epohtime_ = tmp;
                    nextepohtime_ = tmp;
                    expireepohtime_ = tmp;}}

            size_t inc() {
                cnt_ = (cnt_ < maxcnt_) ? cnt_ + 1 : maxcnt_;
                cursor_ = ((cursor_ + 1) < maxcnt_) ? cursor_ + 1 : 0;
                return cursor_;}

            double mineu() const {
                return mineu_;}

            double maxeu() const {
                return maxeu_;}

            interproc_mutex & memlock() const {
                return mtx_;}

        private:
            mutable interproc_mutex mtx_;
            size_t                  cnt_;
            size_t                  maxcnt_;
            size_t                  cursor_;
            datetime                epohtime_;
            datetime                nextepohtime_;
            datetime                expireepohtime_;
            double                  mineu_;
            double                  maxeu_;
            bool                    free_;
            bool                    needwrite_;} ;

        typedef logline_header        headertype;

        logpoint() : tm_(), vl_(0) {}

        logpoint(timetype tim, valuetype val) : tm_(tim), vl_(val) {}

        timetype time() const {
            return tm_;}

        void time(const timetype & val)  {
            tm_ = val;}

        valuetype value() const {
            return vl_;}

        void set(timetype tim, valuetype val) {
            tm_ = tim;
            vl_ = val;}

        friend bool operator<(const logpoint& ls, const logpoint& rs){
            return (ls.tm_ < rs.tm_);}

    private:

#pragma  pack(push,2)
        timetype           tm_;
        valuetype          vl_;
#pragma  pack(pop)
        /* */
    } ;

    struct trend_logline {

        typedef logpoint<unum16, unum16, TREND_BUFFER_SIZE, TREND_EPOHPERIOD>  pointtype;
        typedef pointtype::headertype                                          headertype;

        trend_logline(double min = 0, double max = 0) : hdr(min, max) {}

        void insert(const datetime& tim, const double& val) {

            if (!hdr.isepoch()) hdr.epoch(tim);
            if (hdr.isexpire(tim)) resetepoch();
            double tmpvl = val;
            double tmpmax = hdr.maxeu();
            double tmpmin = hdr.mineu();
            if (tmpmax < val) tmpvl = tmpmax;
            if (tmpmin > val) tmpvl = tmpmin;
            unum16 tmptm = static_cast<unum16> (secondsbetween(hdr.epoch(), tim));
            unum16 tmpval = 0;
            if ((val == val) && (tmpmax != tmpmin)) {
                tmpval = 1 +  static_cast<unum16> ((tmpvl - tmpmin) / (tmpmax - tmpmin) * static_cast<double> (0xFFF0));}
            if ((!tmpval) && (value(0)!=value(0))) return;
            if ((hdr.count()) && (timenum(0) == tmptm))
                set(tmptm, tmpval);
            else {
                hdr.inc();
                set(tmptm, tmpval);}}

        bool insert(const dt_val_map& values) {
            datetime dtm = (count()) ? time(0) :  nill_time;
            for (dt_val_map::const_iterator it=values.begin();it!=values.end();++it)
                insert(it->first, it->second);
            return true;}

         bool select(dt_val_map& vl, datetime from, datetime to_, const double& lgdb = NULL_DOUBLE) const  {
            vl.clear();
            if (count()){
                bool tmprng = ((to_ == nill_time) && (from == nill_time));
                if (count()) {
                    bool lftrng =  ((from==nill_time) || ((from!=nill_time) && (from>=time(count()-1))));
                    bool rtrng =  ((to_==nill_time) || ((to_!=nill_time) && (to_<=time(0))));
                    tmprng =((lftrng) && (rtrng));}
                else{
                    tmprng =false;}
                if (to_ == nill_time) to_ = now();
                size_t end = (from==nill_time) ? count()-1 : (find(from)+1);
                size_t beg = (to_==nill_time) ? 0 : find(to_);
                if (end>=count()) end = count()-1;
                if (beg>=count()) beg = count()-1;
                bool islgdb = (lgdb==lgdb);
                double  tmplogval = NULL_DOUBLE;
                double  tmpvl = NULL_DOUBLE;
                datetime tmptm = nill_time;
                for (size_t i = beg; i <= end ; i++) {
                    tmptm = time(i);
                    tmpvl = value(i);
                    if ((tmptm <= to_) && ((from == nill_time) || (tmptm >= from) || (i==end))){
                         if (!islgdb){
                             vl.insert(dt_val_pair(tmptm, tmpvl));}
                         else {
                             if ((i==beg) && (from != nill_time) && (tmptm==from)){
                                   tmplogval=tmpvl;}
                             else{
                                   if ((tmpvl!=tmpvl) || (tmplogval!=tmplogval) || (dvnci::abs(tmpvl-tmplogval)>=lgdb)){
                                       if (!((i==beg) && (tmpvl!=tmpvl))){
                                           vl.insert(dt_val_pair(tmptm, tmpvl));
                                           tmplogval=tmpvl;}}}}}}
                return tmprng;}
            return false;}

        datetime toptime() const  {
             return (count()) ? time(0) :  nill_time;}

        bool value_by_time(const datetime& tm, dt_val_pair& vl) const {
            if (count()){
                size_t fnd = find(tm);
                if (fnd<count()){
                   vl.first = time(fnd);
                   vl.second = value(fnd);
                return (time(fnd)==tm);}}
            return false;}

        bool topvalue(dt_val_pair& vl) const {
            if (count()){
                vl.first = time(0);
                vl.second = value(0);
                return true;}
            return false;}

        void range(double min, double max) {
            hdr.range(min, max);}
        
        void clear(bool withfree = false) {
            hdr.clear(withfree);}

        bool free() const {
            return (hdr.free());}

        size_t count() const {
            return hdr.count();}

        bool needwrite() const {
                return hdr.needwrite();}

        void needwrite(bool vl)  {
                hdr.needwrite(vl);}

        interproc_mutex & memlock() const {
                return hdr.memlock();}

    protected:


        size_t   find(const datetime& tm) const {
            if (count()){
               size_t strt = index(0) + 1;
               pointtype* bgn = (pointtype*)&item[0];
               pointtype* end = (pointtype*)&item[strt];
               pointtype tmp(static_cast<unum16> (hdr.epoch() < tm ? secondsbetween(hdr.epoch(), tm) : 0) , 0);
               size_t fndlow = static_cast<size_t> (std::lower_bound(bgn, end , tmp ) - bgn);
               if (fndlow >0) {
                   return (fndlow==strt) ? 0 : index(fndlow);}
               if (fndlow==0) {
                   bgn = (pointtype*)&item[strt];
                   end = (pointtype*)&item[count()];
                   fndlow = static_cast<size_t> (std::lower_bound(bgn, end , tmp ) - bgn);
                   if (fndlow>0) return index(fndlow); }
               return count()-1;}
            return npos;}



        size_t maxcount() const {
            return hdr.maxcount();}

        double value(size_t vl) const {
            if (index(vl)<maxcount()){
               unum16 tmp = item[index(vl)].value();
               return tmp ? hdr.mineu() + static_cast<double> (tmp-1) / static_cast<double> (0xFFF0) * (hdr.maxeu() - hdr.mineu()) : NULL_DOUBLE;}
            return NULL_DOUBLE;}

        datetime time(size_t vl) const  {
            if (index(vl)<maxcount()){
               unum16 tmp = item[index(vl)].time();
               return tmp ? incsecond(hdr.epoch(), tmp) : nill_time;}
            return nill_time;}

        unum16 timenum(size_t vl) const  {
            if (index(vl)<maxcount()){
               return item[index(vl)].time();}
            return 0;}

        void set(unum16 tm, unum16 val){
            size_t ind = index(0);
            if (ind < maxcount()){
                item[ind].set(tm,val);}}

        size_t index(size_t vl) const {
            return vl < hdr.cursor() ? hdr.cursor() - vl - 1 : hdr.count()- (vl - hdr.cursor()) - 1;}

        void resetepoch() {
            size_t delt = static_cast<size_t> (secondsbetween(hdr.epoch(), hdr.nextepoch()));
            hdr.epoch(hdr.nextepoch());
            for (size_t i = 0; i < count() ; i++) {
                item[i].time((item[i].time() > delt) ?  item[i].time() - delt : 0);}}

        headertype       hdr;
#pragma  pack(push,2)
        pointtype        item[TREND_BUFFER_SIZE];
#pragma  pack(pop)
    /**/
    } ;

    struct report_logline {


        typedef logpoint<datetime, double, REPORT_BUFFER_SIZE, REPORT_EPOHPERIOD>  pointtype;
        typedef pointtype::headertype                                              headertype;

        report_logline(double min = 0, double max = 0) : hdr(0, 0) {}

        void insert(const datetime& tim, const double& val) {
            datetime dtm = (count()) ? time(0) :  nill_time;
            bool   topvlnan  = (count()) ? isNaN(value(0)) :  false;
            if ((dtm.is_special()) || (tim>dtm)){
               if (((isNaN(val)) || (topvlnan)) && (count())){
                   set(tim, val);
                   return;}
               hdr.inc();
               set(tim, val);}}
        
        bool insert(const dt_val_map& values) {
            bool tmpbl = false;
            datetime dtm = (count()) ? time(0) :  nill_time;
            for (dt_val_map::const_iterator it=values.begin();it!=values.end();++it)
               if ((dtm.is_special()) || (it->first>dtm)){
                    tmpbl = true;
                    if ((count()) && (isNaN(value(0)))){
                        set(it->first, it->second);}
                    else{
                        hdr.inc();
                        set(it->first, it->second);}}
            return tmpbl;}

        bool select(dt_val_map& vl, datetime from, datetime to_, const double& lgdb = NULL_DOUBLE) const  {
            vl.clear();
            if (count()){
                bool tmprng = ((to_ == nill_time) && (from == nill_time));
                if (count()) {
                    bool lftrng =  ((from==nill_time) || ((from!=nill_time) && (from>=time(count()-1))));
                    bool rtrng =  ((to_==nill_time) || ((to_!=nill_time) && (to_<=time(0))));
                    tmprng =((lftrng) && (rtrng));}
                else{
                    tmprng =false;}
                if (to_ == nill_time) to_ = now();
                size_t end = (from==nill_time) ? count()-1 : find(from);
                size_t beg = (to_==nill_time) ? 0 : find(to_);
                if (end>=count()) end = count()-1;
                if (beg>=count()) beg = count()-1;
                for (size_t i = beg; i <= end ; i++) {
                    datetime tmp = time(i);
                    if (tmp != nill_time) {
                        if ((tmp <= to_) && ((from == nill_time) || (tmp >= from)))
                            vl.insert(dt_val_pair(time(i), value(i)));}}
                return tmprng;}
            return false;}
        
         datetime toptime() const {
             return (count()) ? time(0) :  nill_time;}

         bool topvalue(dt_val_pair& vl) const {
            if (count()){
                vl.first = time(0);
                vl.second = value(0);
                return true;}
            return false;}

         bool value_by_time(const datetime& tm, dt_val_pair& vl) const {
            if (count()){
                size_t fnd = find(tm);
                if (fnd<count()){
                   vl.first = time(fnd);
                   vl.second = value(fnd);
                return (time(fnd)==tm);}}
            return false;}

        void range(double min, double max) {
            hdr.range(min, max);}

        void clear(bool withfree = false) {
            hdr.clear();}

        bool free() const {
            return (hdr.free());}

        size_t count() const {
            return hdr.count();}

        bool needwrite() const {
                return hdr.needwrite();}

        void needwrite(bool vl)  {
                hdr.needwrite(vl);}

        interproc_mutex & memlock() const {
                return hdr.memlock();}

    protected:

        size_t   find(const datetime& tm) const {
            if (count()){
               size_t strt = index(0) + 1;
               pointtype* bgn = (pointtype*)&item[0];
               pointtype* end = (pointtype*)&item[strt];
               pointtype tmp(tm, 0);
               size_t fndlow = static_cast<size_t> (std::lower_bound(bgn, end , tmp ) - bgn);
               if (fndlow >0) {
                   return (fndlow==strt) ? 0 : index(fndlow);}
               if (fndlow==0) {
                   bgn = (pointtype*)&item[strt];
                   end = (pointtype*)&item[count()];
                   fndlow = static_cast<size_t> (std::lower_bound(bgn, end , tmp ) - bgn);
                   if (fndlow>0) return index(fndlow); }
               return count()-1;}
            return npos;}



        size_t maxcount() const {
            return hdr.maxcount();}

        double value(size_t vl) const {
            return index(vl) < maxcount() ? item[index(vl)].value() : NULL_DOUBLE;}

        datetime time(size_t vl) const  {
            return index(vl) < maxcount() ? item[index(vl)].time() : nill_time;}

        void set(const datetime& tm, double val){
            size_t ind = index(0);
            if (ind < maxcount()){
                item[ind].set(tm,val);}}

        size_t index(size_t vl) const {
            return vl < hdr.cursor() ? hdr.cursor() - vl - 1 : hdr.count()- (vl - hdr.cursor()) - 1;}


        headertype       hdr;
#pragma  pack(push,2)
        pointtype        item[REPORT_BUFFER_SIZE];
#pragma  pack(pop)
    /**/
    } ;

    template<typename LOGLINE>
    class valuebufferbase_templ : public  staticmemorymap {

    protected:

        typedef LOGLINE                          logline;

        typedef struct loglinesstruct {

            loglinesstruct(size_t mx) : count_(0), maxcount_(mx), freeindex_(0) {}

            indx regist(double min = 0, double max = 0) {
                if (max < min) {
                    min = (max += min) - min;
                    max -= min;}
                size_t frtmp = freeindex(static_cast<double> (min), static_cast<double> (max));
                return (frtmp >= maxcount_) ? npos : frtmp;}

            void range(indx id, double min , double max) {
                if ((id != npos) && (id<static_cast<indx> (count_))) {
                    INP_EXCLUSIVE_LOCK(item[id].memlock());
                    if (max < min) {
                        min = (max += min) - min;
                        max -= min;}
                    item[id].range(min, max);}}

            void unregist(indx id) {
                if (id == npos) return;
                if (id<static_cast<indx> (count_)) {
                    item[id].clear(true);
                    if (freeindex_>static_cast<size_t> (id)) freeindex_ = static_cast<size_t> (id);}}

            void insert(indx id, const datetime& tim, const double& val) {
                if (id<static_cast<indx> (count_)) {
                    INP_EXCLUSIVE_LOCK(item[id].memlock());
                    item[id].insert(tim, val);}}

            bool insert(indx id, const dt_val_map& values) {
                if (id<static_cast<indx> (count_)) {
                    INP_EXCLUSIVE_LOCK(item[id].memlock());
                    return item[id].insert(values);}
                return false;}

            void insert(indx id, const datetime & tim) {
                if (id<static_cast<indx> (count_)) {
                    INP_EXCLUSIVE_LOCK(item[id].memlock());
                    item[id].insert(tim, NULL_DOUBLE);}}

            bool select(indx id, dt_val_map& vl, datetime from_, datetime to_, const double& lgdb = NULL_DOUBLE) const  {
                if ((id != npos) && (id<static_cast<indx> (count_))) {
                    INP_SHARE_LOCK(item[id].memlock());
                    return item[id].select(vl, from_, to_, lgdb);}
                return false;}

            void clear(indx id){
                 if ((id != npos) && (id<static_cast<indx> (count_))) {
                    INP_EXCLUSIVE_LOCK(item[id].memlock());
                    item[id].clear();}}

            datetime toptime(indx id) const  {
                 if ((id != npos) && (id<static_cast<indx> (count_))) {
                    INP_SHARE_LOCK(item[id].memlock());
                    return item[id].toptime();}
                 return nill_time;}

            bool topvalue(indx id, dt_val_pair& vl) const {
                 if ((id != npos) && (id<static_cast<indx> (count_))) {
                    INP_SHARE_LOCK(item[id].memlock());
                    return item[id].topvalue(vl);}
                 return false;}

            bool value_by_time(indx id, const datetime& tm, dt_val_pair& vl) const {
                 if ((id != npos) && (id<static_cast<indx> (count_))) {
                    INP_SHARE_LOCK(item[id].memlock());
                    return item[id].value_by_time(tm,vl);}
                 return false;}

            size_t count(indx id) const {
                 if ((id != npos) && (id<static_cast<indx> (count_))) {
                    INP_SHARE_LOCK(item[id].memlock());
                    return item[id].count();}
                 return 0;}

            bool needwrite(indx id) const {
                if ((id != npos) && (id<static_cast<indx> (count_))) {
                     INP_SHARE_LOCK(item[id].memlock());
                     return item[id].needwrite();}
                return false;}

            void needwrite(indx id, bool vl)  {
                if ((id != npos) && (id<static_cast<indx> (count_))) {
                     INP_SHARE_LOCK(item[id].memlock());
                     return item[id].needwrite(vl);}}


        private:

            size_t count() const {
                return count_;}

            size_t maxcount() const {
                return maxcount_;}

            size_t freeindex(double min = 0, double max = 0) {
                size_t frtmp = freeindex_;
                if ((frtmp + 1) >= maxcount_)
                    return maxcount_;
                if (freeindex_ == count_) {
                    freeindex_++;
                    count_++;}
                else {
                    freeindex_++;
                    while ((freeindex_ < count_) && (!item[freeindex_].free())) {
                        freeindex_++;}}
                new (&item[frtmp]) logline(min, max);
                return frtmp;}

            size_t      count_;
            size_t      maxcount_;
            size_t      freeindex_;
            logline     item[];} *pbufferbasestruct;


        static size_t getcnt(size_t cnt) {
            return (((cnt + 0x1000) < MAX_ANALOGBUFFCNT) ? (cnt + 1000) : MAX_ANALOGBUFFCNT);}



    public:

        valuebufferbase_templ(const std::string& mapname, size_t cnt) :
        staticmemorymap(mapname,  getcnt(cnt) * sizeof (logline) + 1000 ) {
            INP_EXCLUSIVE_LOCK(memlock())
            if (isnew())
                new (data()) loglinesstruct(getcnt(cnt));}

        size_t count() const {
            return pbufferbasestruct(data())->count();}

       interproc_mutex& memlock() const {
            return utilptr->memlock();}


        template<typename T>
        indx regist(T min, T max) {
            INP_EXCLUSIVE_LOCK(memlock())
            return pbufferbasestruct(data())->regist(static_cast<double> (min), static_cast<double> (max));}

        indx regist() {
            INP_EXCLUSIVE_LOCK(memlock())
            return pbufferbasestruct(data())->regist();}

        void unregist(indx id) {
            INP_EXCLUSIVE_LOCK(memlock())
            return pbufferbasestruct(data())->unregist(id);}

        template<typename T>
        void range(indx id, T min, T max) {
            return pbufferbasestruct(data())->range(id, static_cast<double> (min), static_cast<double> (max));}

        template<typename T>
        void  insert(indx id, const datetime& tim, T val) {
              pbufferbasestruct(data())->insert(id, tim, static_cast<double> (val));}

        bool  insert(indx id, const dt_val_map& values) {
              return pbufferbasestruct(data())->insert(id,  values);}

       void  insert(indx id, const datetime& tim) {
             pbufferbasestruct(data())->insert(id, tim, NULL_DOUBLE);}

        bool select(indx id, dt_val_map& vl, datetime from = nill_time, datetime to_ = nill_time, const double& lgdb = NULL_DOUBLE) const {
            vl.clear();
            return pbufferbasestruct(data())->select(id, vl, from, to_, lgdb);}

        datetime  toptime(indx id) const  {
            return pbufferbasestruct(data())->toptime(id);}

        bool  topvalue(indx id, dt_val_pair& vl) const {
            return pbufferbasestruct(data())->topvalue(id, vl);}

        bool  value_by_time(indx id, const datetime& tm, dt_val_pair& vl) const {
            return pbufferbasestruct(data())->value_by_time(id, tm, vl);}

        size_t count(indx id) const {
            return pbufferbasestruct(data())->count(id);}

        size_t capacity() const {
            return utilptr->capacity();}

        bool needwrite(indx id) const {
             return pbufferbasestruct(data())->needwrite(id);}

        void needwrite(indx id, bool vl)  {
             pbufferbasestruct(data())->needwrite(id, vl);}} ;}

#endif	/* BUFFERBASE_TEMPL_H */

