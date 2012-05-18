/* 
 * File:   gui_executor.h
 * Author: sealeks@mail.ru
 *
 * Created on 13 Июль 2011 г., 18:32
 */

#ifndef GUI_EXECUTOR_H
#define	GUI_EXECUTOR_H

#include <kernel/constdef.h>
#include <kernel/systemutil.h>
#include <kernel/expression.h>
#include <kernel/short_value.h>
#include <kernel/mainstruct.h>
#include <kernel/memfile.h>

#include <boost/bimap/multiset_of.hpp>

namespace dvnci {

    class expression_listener {
    public:
        virtual void event(const short_value& val) = 0;};

    typedef boost::shared_ptr<expression_listener> expression_listener_ptr;

    
    class alarms_table{
    public:
        alarms_table(const vect_alarms_row& val_): val(val_){};
        const vect_alarms_row& val;
    };
    
    
    class alarms_listener {
    public:
        alarms_listener(const std::string& grp="", const std::string& agrp="") 
                : group_(trim_copy(grp)), agroup_(trim_copy(agrp)), version_(0) {
                filtered_=((agroup()!="") || (group()!=""));}
        virtual ~alarms_listener(){}
        virtual void event(const vect_alarms_row& val) = 0;
        std::string group() const{
            return trim_copy(group_);}
        std::string agroup() const{
            return trim_copy(agroup_);}
        bool filtered() const{
            return filtered_;}
        vect_alarms_row& table(){
            return table_;}
        guidtype version() const{
            return version_;} 
        void version(guidtype ver){
            version_=ver;}        
    private:
        
        std::string     group_;
        std::string     agroup_;
        guidtype        version_;        
        bool            filtered_;
        vect_alarms_row table_;};

    typedef boost::shared_ptr<alarms_listener> alarms_listener_ptr;
    
    
    class trends_table{
    public:
        trends_table(const short_values_table& val_): val(val_){};
        const short_values_table& val;
    };    

    class trend_listener {
    public:
        trend_listener(const str_vect& tgs, num64 histmilisec = 0) : tags_(tgs), history_(histmilisec) {}
        virtual ~trend_listener(){}
        virtual bool event(const short_values_table& val) = 0;
        
        num64 history() const { return history_>0 ? history_ : 0;}
        const str_vect& tags() const { return tags_;}
        void  remove(const str_vect& rem) { 
            for (str_vect::const_iterator it = rem.begin(); it != rem.end(); ++it)
                tags_.erase(std::remove(tags_.begin(),tags_.end(),*it), tags_.end());}

    private:
        str_vect       tags_;
        num64          history_;
    
    };

    typedef boost::shared_ptr<trend_listener> trend_listener_ptr;
    
    
    
    class journal_table{
    public:
        journal_table(const vect_journal_row& val_): val(val_){};
        const vect_journal_row& val;
    };
    
    
    class journal_listener {
    public:
        virtual void event(const vect_journal_row& val) = 0;};

    typedef boost::shared_ptr<journal_listener> journal_listener_ptr;
    
    
    
    class debug_table{
    public:
        debug_table(const vect_debug_row& val_): val(val_){};
        const vect_debug_row& val;
    };
    
    class debug_listener {
    public:
        virtual void event(const vect_debug_row& val) = 0;};

    typedef boost::shared_ptr<debug_listener> debug_listener_ptr;
    
    



    namespace custom {

        template<typename INTF, typename LISTENER = expression_listener, typename TRENDLISTENER = trend_listener>

                class gui_executor : public executable {
        public:
            
            static const size_t MAX_TABLE_SIZE = MAX_NUM32_SIGNED;

            typedef INTF interface_type;
            typedef membase_sync_ptr_tmpl<interface_type> interface_type_ptr;

            typedef LISTENER listener_type;
            typedef boost::shared_ptr<listener_type> listener_type_ptr;

            typedef TRENDLISTENER trendlistener_type;
            typedef boost::shared_ptr<trendlistener_type> trendlistener_type_ptr;

            typedef dvnci::expr::expression_templ<INTF> expression_type;
            typedef boost::shared_ptr<expression_type> expression_type_ptr;

            struct listener_less :
            public std::binary_function<listener_type_ptr, listener_type_ptr, bool> {

                bool operator()(const listener_type_ptr& ls,
                        const listener_type_ptr & rs) const {
                    return ((intptr_t) ls.get()) < ((intptr_t) rs.get());}};

            struct trendlistener_less :
            public std::binary_function<trendlistener_type_ptr, trendlistener_type_ptr, bool> {

                bool operator()(const trendlistener_type_ptr& ls,
                        const trendlistener_type_ptr & rs) const {
                    return ((intptr_t) ls.get()) < ((intptr_t) rs.get());}};

            struct expression_pair {

                expression_pair(expression_type_ptr exp, const short_value & sh) : first(exp), second(sh) {}
                expression_type_ptr first;
                mutable short_value second;};

            struct expression_less :
            public std::binary_function<expression_pair, expression_pair, bool> {

                bool operator()(const expression_pair& ls,
                        const expression_pair & rs) const {
                    return ls.first->expressionstr() < rs.first->expressionstr();}};

            typedef boost::bimaps::multiset_of<expression_pair, expression_less > expressions;
            typedef boost::bimaps::set_of<listener_type_ptr, listener_less > listener_set;
            typedef boost::bimaps::bimap<expressions, listener_set > expression_listeners_map;
            typedef typename expression_listeners_map::value_type value_type;
            typedef typename expression_listeners_map::left_map expression_map;
            typedef typename expression_listeners_map::left_map::range_type left_range;
            typedef typename expression_listeners_map::left_map::const_range_type const_left_range;
            typedef typename expression_listeners_map::right_map::range_type right_range;
            typedef typename expression_listeners_map::right_map::const_range_type const_right_range;
            typedef typename expression_listeners_map::right_map listeners_map;
            typedef typename expression_listeners_map::left_iterator expression_iterator;
            typedef typename expression_listeners_map::left_const_iterator expression_const_iterator;
            typedef typename expression_listeners_map::right_iterator listeners_iterator;
            typedef typename expression_listeners_map::right_const_iterator listeners_const_iterator;

            typedef std::set<listener_type_ptr, listener_less> updatedlistener_set;
            typedef typename updatedlistener_set::iterator updatedlistener_set_iterator;

            
            typedef std::set<trendlistener_type_ptr, trendlistener_less >     trendlistener_set;
            typedef typename trendlistener_set::const_iterator                trendlistener_constiterator;
            

            struct alarms_listener_less :
            public std::binary_function<alarms_listener_ptr, alarms_listener_ptr, bool> {

                bool operator()(const alarms_listener_ptr& ls,
                        const alarms_listener_ptr & rs) const {
                    return ((intptr_t) ls.get()) < ((intptr_t) rs.get());}};
                    
                    

            typedef std::set<alarms_listener_ptr, alarms_listener_less > alarms_listener_set;
            typedef typename alarms_listener_set::iterator alarms_listener_iterator;
            
            
            struct journal_listener_less :
            public std::binary_function<journal_listener_ptr, journal_listener_ptr, bool> {

                bool operator()(const journal_listener_ptr& ls,
                        const journal_listener_ptr & rs) const {
                    return ((intptr_t) ls.get()) < ((intptr_t) rs.get());}};            
            
            
            typedef std::deque<journal_row>                                journal_table_deq;
            typedef typename journal_table_deq::iterator                   journal_table_iterator;
            typedef std::set<journal_listener_ptr, journal_listener_less > journal_listener_set;
            typedef typename journal_listener_set::iterator                journal_listener_iterator;   
            
            
            struct debug_listener_less :
            public std::binary_function<debug_listener_ptr, debug_listener_ptr, bool> {

                bool operator()(const debug_listener_ptr& ls,
                        const debug_listener_ptr & rs) const {
                    return ((intptr_t) ls.get()) < ((intptr_t) rs.get());}};            
            
            
            typedef std::deque<debug_row>                                  debug_table_deq;
            typedef typename debug_table_deq::iterator                     debug_table_iterator;
            typedef std::set<debug_listener_ptr, debug_listener_less >     debug_listener_set;
            typedef typename debug_listener_set::iterator                  debug_listener_iterator;    
            
            
            
            
            

            gui_executor(interface_type_ptr inf) : 
                 executable(), intf(inf), alarm_version(0), 
                 journal_version(0), journal_crnt(0), journal_cnt(0),
                 debug_version(0) , debug_crnt(0), debug_cnt(0) {};

            virtual ~gui_executor() {};

            virtual bool operator()() {
                while (!terminated()) {
                    if (init()) {
                        if (terminated()) break;
                        boost::xtime xt_loop;
                        addmillisec_to_now(xt_loop, internal_expr_exec() ? 200 : 600);
                        boost::thread::sleep(xt_loop);}
                    if (terminated()) break;}
                return true;}

            bool regist_expr_listener(const std::string& expr, listener_type_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                expression_pair extmp(expression_type_ptr(new expression_type(expr, intf)), short_value());
                expression_iterator itb = expressions_map.left.lower_bound(extmp);
                expression_iterator ite = expressions_map.left.upper_bound(extmp);
                if (itb == ite) {
                    value_type val(extmp, listener);
                    expressions_map.insert(val);
                    itb = expressions_map.left.lower_bound(extmp);
                    ite = expressions_map.left.upper_bound(extmp);
                    if (itb == ite)
                        return false;
                    updatedset.insert(listener);}
                else {
                    value_type val(itb->first, listener);
                    expressions_map.insert(val);
                    itb = expressions_map.left.lower_bound(extmp);
                    ite = expressions_map.left.upper_bound(extmp);
                    if (itb == ite)
                        return false;
                    updatedset.insert(listener);}

                return true;}

            bool unregist_expr_listener(listener_type_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                listeners_iterator itb = expressions_map.right.lower_bound(listener);
                listeners_iterator ite = expressions_map.right.upper_bound(listener);
                if (updatedset.find(listener)!=updatedset.end())
                    updatedset.erase(listener);
                if (itb != ite) {
                    expressions_map.right.erase(itb->first);
                    return true;}
                return false;}

            bool regist_trend_listener(trendlistener_type_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                
                if (trends_set.find(listener)==trends_set.end()){
                    trends_set.insert(listener);
                    newtrendset.insert(listener);
                    return true;
                }
                return false;}

            bool unregist_trend_listener(trendlistener_type_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                if (newtrendset.find(listener)!=newtrendset.end())
                        newtrendset.erase(listener);
                if (trends_set.find(listener)!=trends_set.end()){
                    trends_set.erase(listener);
                    return true;
                }
                return false;}

            bool regist_alarm_listener(alarms_listener_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                if (alarms_listeners.find(listener) == alarms_listeners.end()) {
                    alarms_listeners.insert(listener);
                    listener->event(alarms);
                    return true;}
                return false;}

            bool unregist_alarm_listener(alarms_listener_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                if (alarms_listeners.find(listener) != alarms_listeners.end()) {
                    alarms_listeners.erase(listener);
                    return true;}
                return false;}
            
            
            bool regist_journal_listener(journal_listener_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                if (journal_listeners.find(listener) == journal_listeners.end()) {
                    journal_listeners.insert(listener);
                    init_journal_listener(listener);
                    return true;}
                return false;}
            
            void init_journal_listener(journal_listener_ptr listener) {
                vect_journal_row journalnew(journal.begin(),journal.end());
                listener->event(journalnew);}             
                       

            bool unregist_journal_listener(journal_listener_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                if (journal_listeners.find(listener) != journal_listeners.end()) {
                    journal_listeners.erase(listener);
                    return true;}
                return false;} 
            
            
            
            bool regist_debug_listener(debug_listener_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                if (debug_listeners.find(listener) == debug_listeners.end()) {
                    debug_listeners.insert(listener);
                    init_debug_listener(listener);
                    return true;}
                return false;}
            
            void init_debug_listener(debug_listener_ptr listener) {
                vect_debug_row debugnew(debug.begin(),debug.end());
                listener->event(debugnew);}            
                       

            bool unregist_debug_listener(debug_listener_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                if (debug_listeners.find(listener) != debug_listeners.end()) {
                    debug_listeners.erase(listener);
                    return true;}
                return false;}            
                        
            
            

            short_value execute(const std::string& expr, bool testmode = false) {
                THD_EXCLUSIVE_LOCK(mtx);
                expression_type_ptr cmd = expression_type_ptr(new expression_type(expr, intf, testmode));
                if (cmd) {
                    cmd->active(true);
                    return cmd->value();}
                return short_value();}

            bool call() {{
                    THD_EXCLUSIVE_LOCK(mtx);
                    for (updatedlistener_set_iterator it = updatedset.begin(); it != updatedset.end(); ++it) {
                        listeners_iterator itf = expressions_map.right.find(*it);
                        if (itf != expressions_map.right.end()) {
                            (*it)->event(itf->second.second);}}
                    updatedset.clear();}

                internal_alarm_exec();
                internal_journal_exec();
                internal_debug_exec();                
                internal_trend_exec();

                return true;}

            void detachall(){
		THD_EXCLUSIVE_LOCK(mtx);
                expressions_map.clear();
                trends_set.clear();
                alarms_listeners.clear();
                alarms.clear();
                updatedset.clear();
                newtrendset.clear();}


        protected:

            bool internal_expr_exec() {
                bool rslt = false;
                THD_EXCLUSIVE_LOCK(mtx);
                for (expression_iterator it = expressions_map.left.begin(); it != expressions_map.left.end(); ++it) {
                    short_value vl = it->first.first->value();
                    if (vl != it->first.second) {
                        it->first.second = vl;
                        rslt = true;
                        updatedset.insert(it->second);}}
                return rslt;}

            
            bool init_trend_listener() {
                if (newtrendset.empty())
                    return false;
                for (trendlistener_constiterator it=newtrendset.begin(); it!=newtrendset.end(); ++it) {
                        str_vect need_remove;
                        for (str_vect::const_iterator ittag = (*it)->tags().begin(); ittag != (*it)->tags().end(); ++ittag)
                            if (!intf->exists(*ittag))
                                need_remove.push_back(*ittag);
                        short_values_table tmptable;
                        datetime from = (*it)->history() ? incmillisecond(now() , -((*it)->history()) ) : nill_time;
                        intf->select_trendsbuff((*it)->tags(), tmptable, from);
                        (*it)->event(tmptable);
                        (*it)->remove(need_remove);}
                newtrendset.clear();
                return true;}

            bool internal_trend_exec() {
                THD_EXCLUSIVE_LOCK(mtx);
                bool rslt = init_trend_listener();               
                for (trendlistener_constiterator it=trends_set.begin(); it!=trends_set.end(); ++it) {
                    trendlistener_type_ptr listener_ptr=*it;
                    short_values_table tmptable;
                    for (str_vect::const_iterator ittag = listener_ptr->tags().begin(); ittag != listener_ptr->tags().end(); ++ittag) {
                        short_value val = intf->value_shv(*ittag);
                        if (val.time().is_special())
                            val.time(now());
                        tmptable.push_back(short_values_row(tag_info_pair(*ittag, BUFFER_READ_CURRENT) , short_value_vect(1, val)));}
                    listener_ptr->event(tmptable);}
                return rslt;}
            
            

            bool internal_alarm_exec() {
                THD_EXCLUSIVE_LOCK(mtx);
                if (alarms_listeners.empty())
                    return false;
                guidtype lst = alarm_version;
                intf->select_alarms(alarms, alarm_version);
                if (lst != alarm_version) {
                    for (alarms_listener_iterator it = alarms_listeners.begin();
                            it != alarms_listeners.end(); ++it) {
                        if (!(*it)->filtered()) {
                            (*it)->event(alarms);}
                        else {
                            guidtype lstc = (*it)->version();
                            intf->select_alarms((*it)->table(), lstc, (*it)->agroup(), (*it)->group() );
                            if (lstc != (*it)->version())
                                (*it)->event((*it)->table());}}
                    return true;}
                return false;}
            
            
            bool internal_journal_exec() {
                THD_EXCLUSIVE_LOCK(mtx);
                if (journal_listeners.empty())
                    return false;
                guidtype lst = journal_version;
                vect_journal_row journalnew;
                intf->select_journal(journalnew, journal_version, journal_crnt, journal_cnt);
                if (!journalnew.empty())
                    insert_to_journal(journalnew);                  
                if (lst != journal_version) {
                    for (journal_listener_iterator it = journal_listeners.begin();
                            it != journal_listeners.end(); ++it) {
                            (*it)->event(journalnew);}
                    return true;}
                return false;}
            
            bool insert_to_journal(const vect_journal_row& vect) {
               size_t newsize = vect.size() + journal.size();
               if (newsize>MAX_TABLE_SIZE){
                   size_t needdelete = newsize - MAX_TABLE_SIZE;                   
                   journal.erase(journal.begin(), needdelete<=journal.size() ? journal.begin() + needdelete : journal.end());}
               journal.insert(journal.end(),vect.begin(), vect.end());
               return true;}
            
            
            
            bool internal_debug_exec() {
                THD_EXCLUSIVE_LOCK(mtx);
                if (debug_listeners.empty())
                    return false;
                guidtype lst = debug_version;
                vect_debug_row debugnew;
                intf->select_debug(debugnew, debug_version, debug_crnt, debug_cnt);
                if (!debugnew.empty())
                    insert_to_debug(debugnew);                  
                if (lst != debug_version) {
                    for (debug_listener_iterator it = debug_listeners.begin();
                            it != debug_listeners.end(); ++it) {
                            (*it)->event(debugnew);}
                    return true;}
                return false;}
            
            bool insert_to_debug(const vect_debug_row& vect) {
               size_t newsize = vect.size() + debug.size();
               if (newsize>MAX_TABLE_SIZE){
                   size_t needdelete = newsize - MAX_TABLE_SIZE;                   
                   debug.erase(debug.begin(), needdelete<=debug.size() ? debug.begin() + needdelete : debug.end());}
               debug.insert(debug.end(),vect.begin(), vect.end());
               return true;}        
            
            
            
            virtual bool initialize() {
                return intf;}

            virtual bool uninitialize() {
                return true;}
            


            interface_type_ptr       intf;
            guidtype                 alarm_version;
            guidtype                 journal_version;
            size_t                   journal_crnt;
            size_t                   journal_cnt;            
            guidtype                 debug_version;
            size_t                   debug_crnt;
            size_t                   debug_cnt;              
            boost::mutex             mtx;
            expression_listeners_map expressions_map;
            trendlistener_set        trends_set;
            alarms_listener_set      alarms_listeners;
            vect_alarms_row          alarms;
            journal_table_deq        journal;
            journal_listener_set     journal_listeners;            
            debug_table_deq          debug;
            debug_listener_set       debug_listeners;          
            updatedlistener_set      updatedset;
            trendlistener_set        newtrendset;};}

    typedef dvnci::custom::gui_executor<tagsbase > chrome_gui_executor;
    typedef callable_shared_ptr<chrome_gui_executor> chrome_executor_ptr;}

#endif	/* GUI_EXECUTOR_H */

