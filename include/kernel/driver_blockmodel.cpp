/* 
 * File:   blockgenerator.cpp
 * Author: Serg
 * 
 * Created on 19 Октябрь 2010 г., 16:19
 */

#include <kernel/driver_blockmodel.h>

namespace dvnci {
    namespace driver {

        basis_req_parcel::basis_req_parcel(std::string vl , tagtype tgtp , const metalink& mlnk) :
        iscorrect_(false), devnum_(0), kind_(0), chanel_(0), addr_(0), indx_(0), size_(0), type_(tgtp), protocol_(0), isbcd_(false),
        isvalue_(false), value_(0) {
            chanel_ = mlnk.chanaltype();
            devnum_ = mlnk.devicenum();
            protocol_ = mlnk.protocol();};

        bool  basis_req_parcel::operator==(const basis_req_parcel& rs) const  {
            if (devnum() != rs.devnum()) return false;
            if (kind() != rs.kind()) return false;
            if (chanel() != rs.chanel()) return false;
            if (addr() != rs.addr()) return false;
            if (indx() != rs.indx()) return false;
            if (size() != rs.size()) return false;
            return true;};

        bool  basis_req_parcel::operator<(const basis_req_parcel& rs) const {
            if (devnum() != rs.devnum()) return (devnum() < rs.devnum());
            if (kind() != rs.kind()) return (kind() < rs.kind());
            if (chanel() != rs.chanel()) return (chanel() < rs.chanel());
            if (addr() != rs.addr()) return (addr() < rs.addr());
            if (indx() != rs.indx()) return (indx() < rs.indx());
            if (size() != rs.size()) return (size() < rs.size());
            return false;}
        
        
        

        std::string basis_req_parcel::to_string() {
            return num64_and_type_cast<std::string>(value_.value64(), value_.type() );};
            
            

        template<>
        void basis_req_parcel::value_cast<double>(double val, const datetime& tm, vlvtype valid) {
            if (IN_SMPLSET(type())) {
                value_ = short_value(val);
                value_.time(tm);
                value_.valid(valid);
                isvalue_ = true;
                error(0);}
            else {
                error(ERROR_IO_DATA_CONV);}}

        template<>
        void basis_req_parcel::value_cast<float>(float val, const datetime& tm, vlvtype valid) {
            if (IN_SMPLSET(type())) {
                value_ = short_value(val);
                value_.time(tm);
                value_.valid(valid);
                isvalue_ = true;
                error(0);}
            else {
                error(ERROR_IO_DATA_CONV);}}
        

        template<>
        void basis_req_parcel::value_cast<std::string>(std::string val, const datetime& tm, vlvtype valid) {
            if (IN_SMPLSET(type())) {
                value_ = short_value(val);
                value_.time(tm);
                value_.valid(valid);
                isvalue_ = true;
                error(0);}
            else {
                error(ERROR_IO_DATA_CONV);}}
        
        void basis_req_parcel::value_byte_seq(const std::string& val, const datetime& tm, vlvtype valid) {
                if (IN_SMPLSET(type())) {
                switch (type()) {
                    case TYPE_NUM64:{
                        num64 tmp = 0;
                        if (string_to_primtype<num64 > (val, tmp)){ 
                            value_cast<num64 > (tmp , tm, valid);
                            return;}
                        break;}
                    case TYPE_UNUM64:{
                        unum64 tmp = 0;
                        if (string_to_primtype<unum64 > (val, tmp)){
                            value_cast<unum64 > (tmp , tm, valid);
                            return;}
                        break;}
                    case TYPE_NUM32:{
                        num32 tmp = 0;
                        if (string_to_primtype<num32 > (val, tmp)){
                            value_cast<num32 > (tmp , tm, valid);
                            return;}
                        break;}
                    case TYPE_UNUM32:{
                        unum32 tmp = 0;
                        if (string_to_primtype<unum32 > (val, tmp)) {
                            value_cast<unum32 > (tmp , tm, valid);
                            return;}
                        break;}
                    case TYPE_NUM16:{
                        num16 tmp = 0;
                        if (string_to_primtype<num16 > (val, tmp)){
                            value_cast<num16 > (tmp , tm, valid);
                            return;}
                        break;}
                    case TYPE_UNUM16:{
                        unum16 tmp = 0;
                        if (string_to_primtype<unum16 > (val, tmp)) {
                            value_cast<unum16 > (tmp , tm, valid);
                            return;}
                        break;}
                    case TYPE_NUM8:{
                        num8 tmp = 0;
                        if (string_to_primtype<num8 > (val, tmp)) {
                            value_cast<num8 > (tmp , tm, valid);
                            return;}
                        break;}
                    case TYPE_UNUM8:{
                        unum8 tmp = 0;
                        if (string_to_primtype<unum8 > (val, tmp)) {
                            value_cast<unum8 > (tmp , tm, valid);
                            return;}
                        break;}
                    case TYPE_DISCRET:{
                        num8 tmp = 0;
                        if (string_to_primtype<num8> (val, tmp)) {
                            value_cast<bool > (tmp!=0 , tm, valid);
                            return;}
                        break;}
                    case TYPE_NODEF:
                    case TYPE_DOUBLE:{
                        double tmp = 0;
                        if (string_to_primtype<double>(val, tmp)) {
                            value_cast<double>(tmp , tm, valid);
                            return;}
                        break;}
                    case TYPE_FLOAT:{
                        float tmp = 0;
                        if (string_to_primtype<float>(val, tmp)) {
                            value_cast<float>(tmp , tm, valid);
                            return;}
                        break;}
                    case TYPE_TEXT:{
                        value_cast<std::string>(val);
                        return;}
                    default:{;}}}
              error(ERROR_IO_DATA_CONV);}

        short_value basis_req_parcel::value() const {
            isvalue_ = false;
            return value_;}


        void basis_req_parcel::value(const short_value& vl) {    
	    if (is_bcd()) {
                short_value tmp= vl;
		tmp.covert_to_bcd();
                value_ = tmp;
                isvalue_ = !tmp.error();
                return;}
            else{
                value_ = vl;
                isvalue_ = !vl.error();}}

        void  basis_req_parcel::value_event(const datetime& dt, double vl, ns_error err) {
            eventvalue_.reset();
            isvalue_ = !error(err);
            if (isvalue_)
                eventvalue_ = datetime_val_ptr( new dt_val_pair(dt, vl));}

        dt_val_pair  basis_req_parcel::value_event() const {
            if (isvalue_) {
                if (eventvalue_) {
                    dt_val_pair tmp = *eventvalue_;
                    isvalue_ = false;
                    eventvalue_.reset();
                    return tmp;}}
            isvalue_ = false;
            return dt_val_pair(nill_time, NULL_DOUBLE);}
        
        
        
        

        void  basis_req_parcel::value_report(const dt_val_map & dt, ns_error err) {
            reportvalue_ = dt;
            isvalue_ = !error(err);}

        const dt_val_map &  basis_req_parcel::value_report() const {
            isvalue_ = false;
            return reportvalue_;}

        void basis_req_parcel::report_range(const datetime& start, const datetime&  stop) {
            reportrange_.reset();
            isvalue_ = false;
            reportrange_ = datetime_pair_ptr( new datetime_pair(start, stop));}

        datetime_pair  basis_req_parcel::report_range() const {
            return  (reportrange_) ? *reportrange_ : std::make_pair(nill_time, nill_time);}

        size_t  calculate_blocksize(parcel_ptr msblk, parcel_ptr lsblk) {
            return ((*msblk)-(*lsblk)) == BLOCKMAXDISTANCE ? 
                BLOCKMAXDISTANCE : std::max<size_t > (((*msblk)-(*lsblk)) + msblk->size(), lsblk->size());}
        
        

        std::ostream & operator<< (std::ostream& os, const block& ns) {
            os << " parsels_line [ ";
            os << "  " << *(ns.begin()->first) << " , "   << *(ns.end()->first) ;
            return os << " ] ";}

        parcels_vect &  operator<<  (parcels_vect& vct, const block& blk) {
            vct.clear();
            if (blk.begin() == blk.end()) {
                vct.push_back(blk.begin()->first);
                return vct;}
            else {
                for (parcel_iterator it = blk.begin(); it != blk.end(); ++it) {
                    vct.push_back(it->first);}}
            vct.push_back(blk.end()->first);
            return vct;}

        std::ostream & operator<< (std::ostream& os, const parcels_vect& ns) {
            os << " parsels_set [ ";
            for (parcels_vect::const_iterator it = ns.begin(); it != ns.end(); ++it) {
                if (it == ns.begin()) os << " { " << *(*it) << " } -";
                else {
                    if ((it + 1) == ns.end()) os << " { " << *(*it) << " }";}}
            return os << " ] ";}


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Базовый класс генератора блока опроса*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        bool abstract_block_model::next(block& blk) {
            if (needgenerate) {
                currentblockiteator = begin();}
            if (blocks.empty()) return false;
            if (currentblockiteator == end()) currentblockiteator = begin();
            blk = (*currentblockiteator);
            parcel_iterator bgn = blk.begin();
            parcel_iterator ed = blk.end();
            if (check_block_active(blk, bgn, ed)) {
                if (bgn != blk.begin()) blk.begin(bgn);
                if (ed != blk.end()) blk.end(ed);
                return true;}
            currentblockiteator++;
            return false;}

        bool abstract_block_model::command(commands_vect& cmdvect) {
            command_vector cmds;
            cmdvect.clear();
            intf->select_commands(cmds, executr->groupset());
            if (!cmds.empty()) {
                for (command_vector::const_iterator it = cmds.begin(); it != cmds.end(); ++it) {
                    tags_iterator itfnd = bmap.right.find(it->tagid());
                    if (itfnd != bmap.right.end()) {
                        itfnd->second->value(short_value(it->value_set<num64 > (), it->type()));
                        cmdvect.push_back(itfnd->second);}}
                return (!cmdvect.empty());}
            return false;}

        void abstract_block_model::ok(block& blk) {
            if (currentblockiteator != end()) currentblockiteator->set_ok();
            currentblockiteator++;
            parcel_iterator endit = blk.end();
            endit++;
            for (parcel_iterator it = blk.begin(); it != endit; ++it) {
                if (it->first->isvalue()) {
                    if (!it->first->error()) {
                        switch (SUPER_TYPE(it->first->type())) {
                            case TYPE_EVENT:{
                                executr->write_val_event(it->second, it->first->value_event());
                                break;}
                            case TYPE_REPORT:{
                                executr->write_val_report(it->second, it->first->value_report());
                                break;}
                            default:{
                                executr->write_val(it->second, it->first->value());}}}}
                if (it->first->error()) {
                    executr->error(it->second, it->first->error());}}}

        bool abstract_block_model::check_parcel_active(parcel_iterator& prsl) {
            if (IN_REPORTSET(intf->type(prsl->second))) {
                if (executr->requested(prsl->second)) {
                    datetime tmpstart = intf->time_log(prsl->second);
                    datetime tmpstop = tmpstart;
                    increporttime(tmpstop, intf->type(prsl->second), static_cast<reporthisttype>(archblocksize));
                    prsl->first->report_range(tmpstart, tmpstop);
                    return true;}
                else return false;}
            return executr->requested(prsl->second);}

        bool abstract_block_model::check_block_active(block& blk, parcel_iterator& bgn, parcel_iterator& ed) {
            if (!intf) return false;
            executr->push_all_report();
            parcel_iterator strt = blk.begin();;
            parcel_iterator stpit = blk.end();
            if (blk.begin() == stpit) {
                return check_parcel_active(strt);}
            ++stpit;
            for (parcel_iterator it = blk.begin(); it != stpit; ++it) {
                if (!check_parcel_active(it)) ++bgn;
                else {
                    if (it != ed) {
                        for (it = ed; it != bgn; --it) {
                            if (!check_parcel_active(it)) ed--;
                            else return true;}}
                    return true;}}
            return false;}


}}

