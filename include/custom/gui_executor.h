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

#include <boost/bimap/multiset_of.hpp>

namespace dvnci {

    class expression_listener {
    public:
        virtual void event(const short_value& val) = 0;} ;

    typedef boost::shared_ptr<expression_listener>                             expression_listener_ptr;
    
 


    class alarms_listener {
    public:
        virtual void event(const vect_alarms_row& val) = 0;};

    typedef boost::shared_ptr<alarms_listener>                                 alarms_listener_ptr;



    namespace custom {

        template<typename INTF, typename LISTENER = expression_listener>

                class gui_executor : public executable {
        public:

            typedef INTF                                                            interface_type;
            typedef membase_sync_ptr_tmpl<interface_type>                           interface_type_ptr;

            typedef LISTENER                                                        listener_type;
            typedef boost::shared_ptr<listener_type>                                listener_type_ptr;

            typedef dvnci::expr::expression_templ<INTF>                             expression_type;
            typedef boost::shared_ptr<expression_type>                              expression_type_ptr;

            struct listener_less :
            public std::binary_function<listener_type_ptr, listener_type_ptr , bool> {

                bool operator()(const listener_type_ptr& ls,
                                const listener_type_ptr & rs) const {
                    return ((intptr_t) ls.get()) < ((intptr_t) rs.get());}} ;

            struct expression_pair {

                expression_pair(expression_type_ptr  exp, const short_value &  sh) : first(exp) , second(sh) {}
                expression_type_ptr  first;
                mutable short_value  second;};

            struct expression_less :
            public std::binary_function<expression_pair, expression_pair , bool> {

                bool operator()(const expression_pair& ls,
                                const expression_pair & rs) const {
                    return ls.first->expressionstr() < rs.first->expressionstr();}} ;

            typedef boost::bimaps::multiset_of<expression_pair, expression_less >     expressions;
            typedef boost::bimaps::set_of<listener_type_ptr, listener_less >          listener_set;
            typedef boost::bimaps::bimap<expressions , listener_set >                 expression_listeners_map;
            typedef typename expression_listeners_map::value_type                     value_type;
            typedef typename expression_listeners_map::left_map                       expression_map;
            typedef typename expression_listeners_map::left_map::range_type           left_range;
            typedef typename expression_listeners_map::left_map::const_range_type     const_left_range;
            typedef typename expression_listeners_map::right_map                      listeners_map;
            typedef typename expression_listeners_map::left_iterator                  expression_iterator;
            typedef typename expression_listeners_map::left_const_iterator            expression_const_iterator;
            typedef typename expression_listeners_map::right_iterator                 listeners_iterator;
            typedef typename expression_listeners_map::right_const_iterator           listeners_const_iterator;
            
            struct alarms_listener_less :
            public std::binary_function<alarms_listener_ptr, alarms_listener_ptr , bool> {

                bool operator()(const alarms_listener_ptr& ls,
                                const alarms_listener_ptr& rs) const {
                    return ((intptr_t) ls.get()) < ((intptr_t) rs.get());}};            
            
            typedef std::set<alarms_listener_ptr , alarms_listener_less >             alarms_listener_set;
            typedef typename alarms_listener_set::iterator                            alarms_listener_iterator;

            gui_executor(interface_type_ptr inf) : executable() , intf(inf), alarm_version(0) {};

            virtual ~gui_executor() {};

            virtual bool operator()() {
                while (!terminated()) {
                    if (init()) {
                        if (terminated()) break;
                        boost::xtime xt_loop;
                        if (internal_expr_exec() || internal_alarm_exec())
                            addmillisec_to_now(xt_loop, 1);
                        else
                            addmillisec_to_now(xt_loop, 10);
                        boost::thread::sleep(xt_loop);}
                    if (terminated()) break;}
                return true;}

            bool regist_expr_listener(const std::string& expr, listener_type_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);
                expression_pair  extmp(expression_type_ptr( new expression_type(expr, intf)), short_value());
                expression_iterator itb = expressions_map.left.lower_bound(extmp);
                expression_iterator ite = expressions_map.left.upper_bound(extmp);
                if (itb == ite) {
                    value_type val(extmp , listener);
                    expressions_map.insert(val);
                    itb = expressions_map.left.lower_bound(extmp);
                    ite = expressions_map.left.upper_bound(extmp);
                    if (itb == ite)
                        return false;
                    listener->event(itb->first.second);}
                else {
                    value_type val(itb->first , listener);
                    expressions_map.insert(val);
                    itb = expressions_map.left.lower_bound(extmp);
                    ite = expressions_map.left.upper_bound(extmp);
                    if (itb == ite)
                        return false;
                    listener->event(itb->first.second);}
                
                return true;}

            bool unregist_expr_listener(listener_type_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);                
                listeners_iterator itb = expressions_map.right.lower_bound(listener);
                expression_iterator ite = expressions_map.right.upper_bound(listener);
                if (itb != ite) {
                    expressions_map.right.erase.insert(itb->first);
                    return true;}
                return false;}
            
            bool regist_alarm_listener(alarms_listener_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);                
                if (alarms_listeners.find(listener)==alarms_listeners.end()){
                    alarms_listeners.insert(listener);
                    listener->event(alarms);
                    return true;}
                return false;}
            
            bool unregist_alarm_listener(alarms_listener_ptr listener) {
                THD_EXCLUSIVE_LOCK(mtx);                
                if (alarms_listeners.find(listener)!=alarms_listeners.end()){
                    alarms_listeners.erase(listener);
                    return true;}
                return false;}            


        protected:

            bool internal_expr_exec() {
                bool rslt = false;
                THD_EXCLUSIVE_LOCK(mtx);
                for (expression_iterator it = expressions_map.left.begin(); it != expressions_map.left.end(); ++it) {
                    short_value vl = it->first.first->value();
                    if ((vl.value64() != it->first.second.value64()) || (vl.valid() != it->first.second.valid())) {
                        it->first.second = vl;
                        rslt = true;
                        it->second->event(vl);}}
                return rslt;}
            
           bool internal_alarm_exec() {
                THD_EXCLUSIVE_LOCK(mtx);
                if (alarms_listeners.empty())
                    return false;
                guidtype lst=alarm_version;
                intf->select_alarms(alarms, alarm_version);
                if (lst!=alarm_version){
                    for (alarms_listener_iterator it = alarms_listeners.begin();
                            it != alarms_listeners.end(); ++it) {
                        (*it)->event(alarms);}
                    return true;}
				return false;}

            virtual bool    initialize() {
                return intf;}

            virtual  bool   uninitialize() {
                return true;}

            interface_type_ptr            intf;
            guidtype                      alarm_version;
            boost::mutex                  mtx;
            expression_listeners_map      expressions_map;
            alarms_listener_set           alarms_listeners;
            vect_alarms_row               alarms;};}}

#endif	/* GUI_EXECUTOR_H */

