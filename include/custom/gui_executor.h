/* 
 * File:   gui_executor.h
 * Author: sealeks@mail.ru
 *
 * Created on 13 ГђЛњГ‘ЕЅГђВ»Г‘Е’ 2011 ГђВі., 18:32
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
    
 
    
    class root_listener {
    public:
             
        root_listener(bool single=false) : singletask_(single),needupdate_(true){}
        virtual ~root_listener(){}      
        virtual bool execute() = 0;       
        bool needupdate() const{
            return needupdate_;} 
        void needupdate(bool val){
            needupdate_=val;}  
        bool singletask() const{
            return singletask_;}         
        
    protected:
        bool            singletask_;
        bool            needupdate_;}; 
        
 
            
    typedef boost::shared_ptr<root_listener>          root_listener_ptr;
            
    typedef std::multiset<root_listener_ptr >         rootlistener_set;
    typedef rootlistener_set::iterator                rootlistener_set_iterator;         
        
        
    
    template<typename VALUETYPE>
    class template_listener : public root_listener {
    public:
        
        typedef VALUETYPE    valuetype;
        
        template_listener(bool single=false) : root_listener(single){}
        virtual void event(const valuetype& val) = 0;
        
        virtual bool execute() {
            if (needupdate_){              
                event(value_);
                needupdate(false);
                return true;}
            return false;}
        
        virtual bool set(const valuetype& val) {
            return false;} 
                        
    protected:        
        valuetype       value_;};
    
   
    class expression_listener : public template_listener<short_value > {
    public:
        expression_listener(bool single=false,bool test=false) 
                : template_listener<short_value >(single),testmode_(test) {};
        virtual bool set(const valuetype& val) {
            if (val!=value_ || singletask()){
                needupdate(true);
                value_=val;
                return true;}
            return false;}
        bool testmode() const{
            return testmode_;} 
        
    protected:
        bool            testmode_;};         



    typedef boost::shared_ptr<expression_listener> expression_listener_ptr;
    
    
    
    
    
    
    class trends_table {
    public:
        trends_table(const short_values_table& val_): val(val_){};
        const short_values_table& val;
    };    

    class trend_listener : public template_listener<short_values_table > {
    public:
        trend_listener(const str_vect& tgs, num64 histmilisec = 0) : 
                template_listener<short_values_table >() , tags_(tgs), history_(histmilisec) {}
                
        virtual bool execute() {
                bool result = template_listener<short_values_table >::execute();
                value_.clear();
                return result;}               
                
        virtual bool set(const short_values_table& val){
                needupdate(true);
                if (!value_.empty()){
                    for (short_values_table::const_iterator it = val.begin(); it != val.end(); ++it)
                        insert(*it);}
                else
                    value_=val;                     
                return true;} 
        
        void insert(const short_values_row& val){
                short_values_table::iterator it=value_.find(val.first);
                if (it!=value_.end()){
                    it->second.insert(it->second.end(), val.second.begin(),val.second.end());}}        
        
               
        num64 history() const { return history_>0 ? history_ : 0;}        
        const str_vect& tags() const { return tags_;}
        void  remove(const str_vect& rem) { 
            for (str_vect::const_iterator it = rem.begin(); it != rem.end(); ++it)
                tags_.erase(std::remove(tags_.begin(),tags_.end(),*it), tags_.end());}

    private:
        str_vect           tags_;
        num64              history_;};

    typedef boost::shared_ptr<trend_listener> trend_listener_ptr;
    
    
    
    

    
    class alarms_table{
    public:
        alarms_table(const vect_alarms_row& val_): val(val_){};
        const vect_alarms_row& val;
    };
    
    
    class alarms_listener : public template_listener<vect_alarms_row > {
    public:
        alarms_listener(const std::string& grp="", const std::string& agrp="") 
                : template_listener<vect_alarms_row >() ,group_(trim_copy(grp)),
                  agroup_(trim_copy(agrp)), version_(0) {
            filtered_=((agroup()!="") || (group()!=""));}       
        
        virtual bool set(const vect_alarms_row& val){
                needupdate(true);
                value_=val;
                return true;}        
        
        std::string group() const{
            return group_;}
        std::string agroup() const{
            return agroup_;}
        bool filtered() const{
            return filtered_;}
        vect_alarms_row& table(){
            return value_;}
        guidtype version() const{
            return version_;} 
        void version(guidtype ver){
            version_=ver;}  
       
    private:

        std::string     group_;
        std::string     agroup_;
        guidtype        version_;        
        bool            filtered_;};

    typedef boost::shared_ptr<alarms_listener> alarms_listener_ptr;
    

    
    class journal_table{
    public:
        journal_table(const vect_journal_row& val_): val(val_){};
        const vect_journal_row& val;
    };
    
    
    class journal_listener : public template_listener<vect_journal_row > {
    public:
        journal_listener() : template_listener<vect_journal_row >() {}
        
        virtual bool execute() {
                bool result = template_listener<vect_journal_row >::execute();
                value_.clear();
                return result;}
        
        virtual bool set(const vect_journal_row& val){
                needupdate(true);
                if (!value_.empty())
                    value_.insert(value_.end(),val.begin(), val.end());
                else
                    value_=val;                     
                return true;} 
        
    };

    typedef boost::shared_ptr<journal_listener> journal_listener_ptr;
    
    
    
    class debug_table{
    public:
        debug_table(const vect_debug_row& val_): val(val_){};
        const vect_debug_row& val;
    };
    
    class debug_listener : public template_listener<vect_debug_row> {
    public:
        debug_listener() : template_listener<vect_debug_row >() {}
    
        virtual bool execute() {
                bool result = template_listener<vect_debug_row >::execute();
                value_.clear();
                return result;}
        
        virtual bool set(const vect_debug_row& val){
                needupdate(true);
                if (!value_.empty())
                    value_.insert(value_.end(),val.begin(), val.end());
                else
                    value_=val;                     
                return true;}   
    }; 

    typedef boost::shared_ptr<debug_listener> debug_listener_ptr;
    
    
    class entety_listener : public template_listener<iteminfo_map > {
    public:
        
        entety_listener(nodetype enttp, indx parentid = dvnci::npos, const std::string& filter ="") 
                : template_listener<iteminfo_map >(true), type_(enttp), parentid_(parentid), filter_(filter){};
                
        virtual bool set(const valuetype& val) {
                needupdate(true);
                value_=val;
                return true;}
        
        std::string filter() const{
            return filter_;} 
        
        indx parentid() const{
            return parentid_;}
        
        nodetype type() const{
            return type_;}         
        
    protected:
        
        nodetype          type_;
        indx              parentid_;       
        std::string       filter_;}; 
        
    typedef boost::shared_ptr<entety_listener> entety_listener_ptr;        
        
        
        
        
    class registrate_listener : public template_listener<ns_error > {
    public:
        
        static const int REGIST = 1;
        static const int UNREGIST = 0;
        
        
        registrate_listener(int type, const std::string& user ="", const std::string& password ="") 
                : template_listener<ns_error >(true), type_(type), user_(user), password_(password) {};
                
        virtual bool set(const valuetype& val) {
                needupdate(true);
                value_=val;
                return true;}
        
        std::string user() const{
            return user_;} 
        
        std::string password() const{
            return password_;}
        
        int type() const{
            return type_;}         
        
    protected:
        
        int               type_;
        std::string       user_;       
        std::string       password_;};
        
        
    typedef boost::shared_ptr<registrate_listener> registrate_listener_ptr;     


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

            struct expression_pair {

                expression_pair(expression_type_ptr exp, const short_value & sh) : first(exp), second(sh) {}
                expression_type_ptr first;
                mutable short_value second;};

            struct expression_less :
            public std::binary_function<expression_pair, expression_pair, bool> {

                bool operator()(const expression_pair& ls,
                        const expression_pair & rs) const {
                    return ls.first->expressionstr() < rs.first->expressionstr();}};
                    
                    

            typedef boost::bimaps::multiset_of<expression_pair, expression_less >  expressions;
            typedef boost::bimaps::set_of<listener_type_ptr >                      listener_set;
            typedef boost::bimaps::bimap<expressions, listener_set >               expression_listeners_map;
            typedef typename expression_listeners_map::value_type                  value_type;
            typedef typename expression_listeners_map::left_map                    expression_map;
            typedef typename expression_listeners_map::left_map::range_type        left_range;
            typedef typename expression_listeners_map::left_map::const_range_type  const_left_range;
            typedef typename expression_listeners_map::right_map::range_type       right_range;
            typedef typename expression_listeners_map::right_map::const_range_type const_right_range;
            typedef typename expression_listeners_map::right_map                   listeners_map;
            typedef typename expression_listeners_map::left_iterator               expression_iterator;
            typedef typename expression_listeners_map::left_const_iterator         expression_const_iterator;
            typedef typename expression_listeners_map::right_iterator              listeners_iterator;
            typedef typename expression_listeners_map::right_const_iterator        listeners_const_iterator;
            
            
            typedef std::set<trendlistener_type_ptr >                              trendlistener_set;
            typedef typename trendlistener_set::const_iterator                     trendlistener_constiterator;
            

            typedef std::set<alarms_listener_ptr >                                 alarms_listener_set;
            typedef typename alarms_listener_set::iterator                         alarms_listener_iterator;

            
            typedef std::deque<journal_row>                                        journal_table_deq;
            typedef typename journal_table_deq::iterator                           journal_table_iterator;
            typedef std::set<journal_listener_ptr>                                 journal_listener_set;
            typedef typename journal_listener_set::iterator                        journal_listener_iterator;         
            
            
            typedef std::deque<debug_row>                                          debug_table_deq;
            typedef typename debug_table_deq::iterator                             debug_table_iterator;
            typedef std::set<debug_listener_ptr >                                  debug_listener_set;
            typedef typename debug_listener_set::iterator                          debug_listener_iterator;   
            
            typedef std::set<entety_listener_ptr >                                 entety_listener_set;
            typedef typename entety_listener_set::iterator                         entety_listener_iterator;   
            
            typedef std::set<registrate_listener_ptr >                             registrate_listener_set;
            typedef typename registrate_listener_set::iterator                     registrate_listener_iterator;             
            
          

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
                        bool updated = internal_expr_exec();
                        internal_alarm_exec();
                        internal_trend_exec();
                        internal_journal_exec();
                        internal_debug_exec();  
                        internal_entety_exec();
                        internal_registrate_exec();
                        addmillisec_to_now(xt_loop, updated ? 200 : 600);
                        boost::thread::sleep(xt_loop);}
                    if (terminated()) break;}
                return true;}

            bool regist_expr_listener(const std::string& expr, listener_type_ptr listener, bool testmode = false) {
                THD_EXCLUSIVE_LOCK(mtx);
                expression_pair extmp(expression_type_ptr(new expression_type(expr, intf, testmode)), short_value());
                expression_iterator itb = expressions_map.left.lower_bound(extmp);
                expression_iterator ite = expressions_map.left.upper_bound(extmp);
                if (itb == ite) {
                    value_type val(extmp, listener);
                    expressions_map.insert(val);
                    itb = expressions_map.left.lower_bound(extmp);
                    ite = expressions_map.left.upper_bound(extmp);
                    if (itb == ite)
                        return false;}
                else {
                    value_type val(itb->first, listener);
                    expressions_map.insert(val);
                    itb = expressions_map.left.lower_bound(extmp);
                    ite = expressions_map.left.upper_bound(extmp);
                    if (itb == ite)
                        return false;}

                return true;}

            bool unregist_expr_listener(listener_type_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                remove_from_update(listener);
                return internal_unregist_expr_listener(listener);}

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
                remove_from_update(listener);                
                newtrendset.erase(listener);
                return trends_set.erase(listener);}

            bool regist_alarm_listener(alarms_listener_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                if (alarms_listeners.find(listener) == alarms_listeners.end()) {
                    alarms_listeners.insert(listener);
                    return true;}
                return false;}

            bool unregist_alarm_listener(alarms_listener_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                remove_from_update(listener);   
                alarmupdatemap.erase(listener);
                return alarms_listeners.erase(listener);}
            
            
            bool regist_journal_listener(journal_listener_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                if (journal_listeners.find(listener) == journal_listeners.end()) {
                    journal_listeners.insert(listener);
                    newjournal_listeners.insert(listener);
                    return true;}
                return false;}
                        
                       

            bool unregist_journal_listener(journal_listener_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                remove_from_update(listener);
                newjournal_listeners.erase(listener);
                return journal_listeners.erase(listener);} 
            
            
            
            bool regist_debug_listener(debug_listener_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                if (debug_listeners.find(listener) == debug_listeners.end()) {
                    debug_listeners.insert(listener);
                    newdebug_listeners.insert(listener);
                    return true;}
                return false;}
            
                       
            bool unregist_debug_listener(debug_listener_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                remove_from_update(listener);
                newdebug_listeners.erase(listener);
                return debug_listeners.erase(listener);}
            
            
            bool regist_entety_listener(entety_listener_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                entety_set.insert(listener);
                return true;}
            
            
            bool regist_registrate_listener(registrate_listener_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                registrate_set.insert(listener);
                return true;}
            

            bool execute(const std::string& expr, bool testmode = false) {
                if (THD_TRY_LOCK(mtx)) {
                    expression_type_ptr cmd = expression_type_ptr(new expression_type(expr, intf, testmode));
                    if (cmd) {
                        cmd->active(true);
                        cmd->value();}
                    return true;}
                return false;}

            bool call() {{
                    THD_EXCLUSIVE_LOCK(mtx);               
                    for (rootlistener_set_iterator it = updatemap.begin(); it != updatemap.end(); ++it) {
                        (*it)->execute();
                        if ((*it)->singletask())
                            unregist(*it);}
                    updatemap.clear();
                    for (alarms_listener_iterator it = alarmupdatemap.begin(); it != alarmupdatemap.end(); ++it) {
                        (*it)->event(alarms);}
                    alarmupdatemap.clear();}                    
                return true;}
            

            void detachall(){
		THD_EXCLUSIVE_LOCK(mtx);
                updatemap.clear();
                expressions_map.clear();
                entety_set.clear();
                registrate_set.clear();                
                trends_set.clear();
                newtrendset.clear();
                alarmupdatemap.clear();
                alarms_listeners.clear();
                alarms.clear();
                newjournal_listeners.clear();
                journal_listeners.clear();
                newdebug_listeners.clear();
                debug_listeners.clear();}


        protected:
            
            void remove_from_update(root_listener_ptr val){
                  updatemap.erase(val);}
            
            bool unregist(root_listener_ptr val) {
                if (expressions_map.right.lower_bound(boost::static_pointer_cast<listener_type>(val))!=
                        expressions_map.right.upper_bound(boost::static_pointer_cast<listener_type>(val))) {
                    return internal_unregist_expr_listener(boost::static_pointer_cast<listener_type>(val));}
                if (entety_set.find(boost::static_pointer_cast<entety_listener>(val))!=entety_set.end()) {
                    entety_set.erase(boost::static_pointer_cast<entety_listener>(val));
                    return true;} 
                if (registrate_set.find(boost::static_pointer_cast<registrate_listener>(val))!=registrate_set.end()) {
                    registrate_set.erase(boost::static_pointer_cast<registrate_listener>(val));
                    return true;}                               
                return false;}
            
            bool internal_unregist_expr_listener(listener_type_ptr listener) {              
                listeners_iterator itb = expressions_map.right.lower_bound(listener);
                listeners_iterator ite = expressions_map.right.upper_bound(listener);
                if (itb != ite) {
                    expressions_map.right.erase(itb->first);
                    return true;}
                return false;}            
            
            

            bool internal_expr_exec() {
                bool rslt = false;
                THD_EXCLUSIVE_LOCK(mtx);
                for (expression_iterator it = expressions_map.left.begin(); it != expressions_map.left.end(); ++it) {
                    if (it->second->set(it->first.first->value()))
                        updatemap.insert(it->second);}
                return rslt;}
            
            
            bool internal_entety_exec() {
                THD_EXCLUSIVE_LOCK(mtx);
                for (entety_listener_iterator it = entety_set.begin(); it != entety_set.end(); ++it) {
                    iteminfo_map result;
                    intf->select_entities((*it)->type(), result, (*it)->parentid(), (*it)->filter());
                    (*it)->set(result);
                    updatemap.insert(*it);
                    return true;}
                return false;}
            
            bool internal_registrate_exec() {
                bool rslt = false;
                THD_EXCLUSIVE_LOCK(mtx);
                for (registrate_listener_iterator it = registrate_set.begin(); it != registrate_set.end(); ++it) {
                    ns_error result = 0;
                    if ((*it)->type() == registrate_listener::REGIST) {
                        result = intf->registrate_user((*it)->user(), (*it)->password());}
                    else {
                        result = intf->unregistrate_user();}
                    (*it)->set(result);
                    updatemap.insert(*it);
                    return true;}
                return false;}             

            
            bool init_trend_listeners() {
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
                        (*it)->set(tmptable);
                        updatemap.insert(*it);                       
                        (*it)->remove(need_remove);}
                newtrendset.clear();
                return true;}

            bool internal_trend_exec() {
                THD_EXCLUSIVE_LOCK(mtx);
                bool rslt = init_trend_listeners();
                for (trendlistener_constiterator it=trends_set.begin(); it!=trends_set.end(); ++it) {
                    trendlistener_type_ptr listener_ptr=*it;
                    if (newtrendset.find(listener_ptr)==newtrendset.end()) {
                    short_values_table tmptable;
                    for (str_vect::const_iterator ittag = listener_ptr->tags().begin(); ittag != listener_ptr->tags().end(); ++ittag) {
                        short_value val = intf->value_shv(*ittag);
                        //if (val.time().is_special())
                        val.time(now());
                        tmptable.insert(short_values_row(tag_info_pair(*ittag, BUFFER_READ_CURRENT) , short_value_vect(1, val)));}
                    (*it)->set(tmptable);
                    updatemap.insert(*it);}}                       
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
                            (*it)->set(vect_alarms_row());
                            alarmupdatemap.insert(*it);}
                        else {
                            guidtype lstc = (*it)->version();
                            intf->select_alarms((*it)->table(), lstc, (*it)->agroup(), (*it)->group() );
                            if (lstc != (*it)->version()){
                                (*it)->set((*it)->table());
                                updatemap.insert(*it);}}}
                    return true;}
                return false;}
            
            
            bool init_journal_listeners() {
                if (newjournal_listeners.empty())
                    return false;
                for (journal_listener_iterator it = newjournal_listeners.begin();
                            it != newjournal_listeners.end(); ++it) {
                    (*it)->set(vect_journal_row(journal.begin(),journal.end()));}           
                newjournal_listeners.clear();
                return true;}
                
            
            
            bool internal_journal_exec() {
                THD_EXCLUSIVE_LOCK(mtx);
                init_journal_listeners();
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
                            (*it)->set(journalnew);
                            updatemap.insert(*it);}
                    return true;}
                return false;}
            
            bool insert_to_journal(const vect_journal_row& vect) {
               size_t newsize = vect.size() + journal.size();
               if (newsize>MAX_TABLE_SIZE){
                   size_t needdelete = newsize - MAX_TABLE_SIZE;                   
                   journal.erase(journal.begin(), needdelete<=journal.size() ? journal.begin() + needdelete : journal.end());}
               journal.insert(journal.end(),vect.begin(), vect.end());
               return true;}
            
            
            
            bool init_debug_listeners() {
                if (newdebug_listeners.empty())
                    return false;
                for (debug_listener_iterator it = newdebug_listeners.begin();
                            it != newdebug_listeners.end(); ++it) {
                    (*it)->set(vect_debug_row(debug.begin(),debug.end()));}              
                newdebug_listeners.clear();
                return true;}
            
            
            
            bool internal_debug_exec() {
                THD_EXCLUSIVE_LOCK(mtx);
                init_debug_listeners();
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
                            (*it)->set(debugnew);
                            updatemap.insert(*it);}
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
            

            boost::mutex             mtx;
            interface_type_ptr       intf;
            
            rootlistener_set         updatemap;
            
            expression_listeners_map expressions_map;
                                   
            trendlistener_set        trends_set;
            trendlistener_set        newtrendset;
            
            entety_listener_set      entety_set;
            
            registrate_listener_set  registrate_set;            
                       
            guidtype                 alarm_version;
            alarms_listener_set      alarms_listeners;
            vect_alarms_row          alarms;
            alarms_listener_set      alarmupdatemap;

            
            guidtype                 journal_version;
            size_t                   journal_crnt;
            size_t                   journal_cnt;   
            journal_table_deq        journal;
            journal_listener_set     journal_listeners;
            journal_listener_set     newjournal_listeners;
            
            guidtype                 debug_version;
            size_t                   debug_crnt;
            size_t                   debug_cnt; 
            debug_table_deq          debug;
            debug_listener_set       debug_listeners;
            debug_listener_set       newdebug_listeners;};}

    typedef dvnci::custom::gui_executor<tagsbase >   chrome_gui_executor;
    typedef callable_shared_ptr<chrome_gui_executor> chrome_executor_ptr;}

#endif	/* GUI_EXECUTOR_H */

