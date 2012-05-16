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

    class alarms_listener {
    public:
        virtual void event(const vect_alarms_row& val) = 0;};

    typedef boost::shared_ptr<alarms_listener> alarms_listener_ptr;

    class trend_listener {
    public:
        virtual bool event(const std::vector<short_value>& val) = 0;};

    typedef boost::shared_ptr<trend_listener> trend_listener_ptr;



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


            typedef boost::bimaps::set_of<trendlistener_type_ptr, trendlistener_less> trendlistener_set;
            typedef boost::bimaps::bimap<expressions, trendlistener_set > expression_trendlisteners_map;
            typedef typename expression_trendlisteners_map::value_type trendvalue_type;
            typedef typename expression_trendlisteners_map::left_map trendexpression_map;
            typedef typename expression_trendlisteners_map::left_map::range_type trendleft_range;
            typedef typename expression_trendlisteners_map::left_map::const_range_type trendconst_left_range;
            typedef typename expression_trendlisteners_map::right_map trendlisteners_map;
            typedef typename expression_trendlisteners_map::left_iterator trendexpression_iterator;
            typedef typename expression_trendlisteners_map::left_const_iterator trendexpression_const_iterator;
            typedef typename expression_trendlisteners_map::right_iterator trendlisteners_iterator;
            typedef typename expression_trendlisteners_map::right_const_iterator trendlisteners_const_iterator;

            typedef std::set<trendlistener_type_ptr, trendlistener_less> newtrendlistener_set;
            typedef typename newtrendlistener_set::iterator newtrendlistener_set_iterator;

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

            bool regist_trend_listener(const std::string& expr, trendlistener_type_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                if (!intf->exists(expr)) return false;
                expression_pair extmp(expression_type_ptr(new expression_type(expr, intf)), short_value());
                trendexpression_iterator itb = trends_map.left.lower_bound(extmp);
                trendexpression_iterator ite = trends_map.left.upper_bound(extmp);
                if (itb == ite) {
                    trendvalue_type val(extmp, listener);
                    trends_map.insert(val);
                    itb = trends_map.left.lower_bound(extmp);
                    ite = trends_map.left.upper_bound(extmp);
                    if (itb == ite)
                        return false;
                    //std::vector<short_value> tmpvct;
                    //intf->select_trendbuff(expr, tmpvct);
                    newtrendset.insert(listener);}
                else {
                    trendvalue_type val(itb->first, listener);
                    trends_map.insert(val);
                    itb = trends_map.left.lower_bound(extmp);
                    ite = trends_map.left.upper_bound(extmp);
                    if (itb == ite)
                        return false;
                    //std::vector<short_value> tmpvct;       
                    //intf->select_trendbuff(expr, tmpvct);
                    newtrendset.insert(listener);}

                return true;}

            bool unregist_trend_listener(trendlistener_type_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                trendlisteners_iterator itb = trends_map.right.lower_bound(listener);
                trendlisteners_iterator ite = trends_map.right.upper_bound(listener);
                if (newtrendset.find(listener)!=newtrendset.end())
                    newtrendset.erase(listener);
                if (itb != ite) {
                    trends_map.right.erase(itb->first);
                    return true;}
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
                trends_map.clear();
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
                        (*it)->event(alarms);}
                    return true;}
                return false;}

            bool init_trend_listener() {
                if (newtrendset.empty())
                    return false;
                for (newtrendlistener_set_iterator it = newtrendset.begin(); it != newtrendset.end(); ++it) {
                    trendlisteners_iterator itf = trends_map.right.find(*it);
                    if (itf != trends_map.right.end()) {
                        std::string expr = itf->second.first->expressionstr();
                        std::vector<short_value> tmpvct;
                        intf->select_trendbuff(expr, tmpvct);
                        (*it)->event(tmpvct);}}
                newtrendset.clear();
                return true;}

            bool internal_trend_exec() {
                bool rslt = init_trend_listener();
                THD_EXCLUSIVE_LOCK(mtx);
                for (trendexpression_iterator it = trends_map.left.begin(); it != trends_map.left.end(); ++it) {
                    short_value vl = it->first.first->value();
                    if ((vl != it->first.second) || (secondsbetween(it->first.second.time(), vl.time()) > 1)) {
                        it->first.second = vl;
                        rslt = true;
                        std::vector<short_value> tmpvct;
                        vl.time(now());
                        tmpvct.push_back(vl);
                        it->second->event(tmpvct);}}
                return rslt;}

            virtual bool initialize() {
                return intf;}

            virtual bool uninitialize() {
                return true;}
            


            interface_type_ptr intf;
            guidtype alarm_version;
            boost::mutex mtx;
            expression_listeners_map expressions_map;
            expression_trendlisteners_map trends_map;
            alarms_listener_set alarms_listeners;
            vect_alarms_row alarms;
            updatedlistener_set updatedset;
            newtrendlistener_set newtrendset;};}

    typedef dvnci::custom::gui_executor<tagsbase > chrome_gui_executor;
    typedef callable_shared_ptr<chrome_gui_executor> chrome_executor_ptr;}

#endif	/* GUI_EXECUTOR_H */

