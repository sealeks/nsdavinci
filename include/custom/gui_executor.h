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
        /*bool remove(const std::string& val) {
            str_vect::iterator it = std::find(tags_.begin(), tags_.end(), val);
            if (it != tags_.end()) {
                tags_.erase(it);
                return true;}
            return false;}*/

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
            

            gui_executor(interface_type_ptr inf) : executable(), intf(inf), alarm_version(0) {};

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
                            intf->select_alarms<alarms_row, guidtype>((*it)->table(), lstc, (*it)->agroup(), (*it)->group() );
                            if (lstc != (*it)->version())
                                (*it)->event((*it)->table());}}
                    return true;}
                return false;}

            bool init_trend_listener() {
                if (newtrendset.empty())
                    return false;
                for (trendlistener_constiterator it=newtrendset.begin(); it!=newtrendset.end(); ++it) {
                        short_values_table tmptable;
                        datetime from = (*it)->history() ? incmillisecond(now() , -((*it)->history()) ) : nill_time;
                        intf->select_trendsbuff((*it)->tags(), tmptable, from);
                        (*it)->event(tmptable);}
                newtrendset.clear();
                return true;}

            bool internal_trend_exec() {
                THD_EXCLUSIVE_LOCK(mtx);
                bool rslt = init_trend_listener();               
                for (trendlistener_constiterator it=trends_set.begin(); it!=trends_set.end(); ++it) {
                    trendlistener_type_ptr listener_ptr=*it;
                    const str_vect& tags = listener_ptr->tags();
                    short_values_table tmptable;
                    for (str_vect::const_iterator ittag = tags.begin(); ittag != tags.end(); ++ittag) {
                        short_value val = intf->value_shv(*ittag);
                        num32 error = 0;
                        if (val.time().is_special()){
                            if (!intf->exists(*ittag))
                                error = 2;
                            val.time(now());}
                        tmptable.push_back(short_values_row(tag_info_pair(*ittag,error) , short_value_vect(1, val)));}
                    listener_ptr->event(tmptable);}
                return rslt;}

            virtual bool initialize() {
                return intf;}

            virtual bool uninitialize() {
                return true;}
            


            interface_type_ptr       intf;
            guidtype                 alarm_version;
            boost::mutex             mtx;
            expression_listeners_map expressions_map;
            trendlistener_set        trends_set;
            alarms_listener_set      alarms_listeners;
            vect_alarms_row          alarms;
            updatedlistener_set      updatedset;
            trendlistener_set        newtrendset;};}

    typedef dvnci::custom::gui_executor<tagsbase > chrome_gui_executor;
    typedef callable_shared_ptr<chrome_gui_executor> chrome_executor_ptr;}

#endif	/* GUI_EXECUTOR_H */

