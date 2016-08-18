//
// request_handler.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c)  Author: Serg Alexeev sealeks@mail.ru
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cmath>
#include <sstream>

#include "request_executor.hpp"

/*
  $$(expr [,handler])   ?!
 $$check(expr [,handler])  ?!
 $$error(expr [,handler])   ?!
 $$users(handler)  ?!
 $$registuser(handler, user, password )   ?!
 $$unregistuser(handler)   ?!
 $$adduser(handler, user, password, access)   ?!
 $$removeuser(handler, user, password)   ?!
 $$changeuserpassword(handler, user, oldpassword, newpassword)   ?!
 $$changeuseraccess(handler, user, access)   ?!
 $$exit()
 $$writefile()
 $$filelist([ext]) !!!!
 $$fileexists((file|dir))  !!!!
 $$kill()
 $$editable()
 $$runtime()
 $$global()
 element.onalarm = handler  - delete
 element.ontrend = handler - delete
 addExpressionListener(handler, expr)
 removeExpressionListener(handler)
 addAlarmsListener(handler[, agroup, group])
 removeAlarmsListener(handler)
 addTrendsListener(handler, taglist, period)
 removTrendsListener(handler)
 
 
       
 
 
 */

/*Correct bug parsing UTF-8 by boost::pt*/
namespace boost {
    namespace property_tree {
        namespace json_parser
        {
            // Create necessary escape sequences from illegal characters
            static std::string create_escapes(const std::string &s){
                return s;
            }
        }
    }
}

namespace http {
    namespace server {


        namespace ptree = boost::property_tree;

        const operationid_type SESSION_REQUEST = 1;
        const operationid_type INIT_REQUEST = 2;
        const operationid_type INIT_RESPONSE = 3;
        const operationid_type UNINIT_REQUEST = 4;
        const operationid_type UNINIT_RESPONSE = 5;
        const operationid_type UPDATE_REQUEST = 6;

        const operationid_type ADDTAG_REQUEST = 7;
        const operationid_type ADDTAG_RESPONSE = 8;
        const operationid_type UPDATETAG_RESPONSE = 9;
        const operationid_type REMOVETAG_REQUEST = 10;
        const operationid_type REMOVETAG_RESPONSE = 11;

        const operationid_type EXECUTE_REQUEST = 12;
        const operationid_type EXECUTE_RESPONSE = 13;


        const operationid_type REGISTRATEUSER_REQUEST = 14;
        const operationid_type REGISTRATEUSER_RESPONSE = 15;

        const operationid_type UNREGISTRATEUSER_REQUEST = 16;
        const operationid_type UNREGISTRATEUSER_RESPONSE = 17;

        const operationid_type ADDUSER_REQUEST = 18;
        const operationid_type ADDUSER_RESPONSE = 19;

        const operationid_type REMOVEUSER_REQUEST = 20;
        const operationid_type REMOVEUSER_RESPONSE = 21;

        const operationid_type CHANGEPASSWORD_REQUEST = 22;
        const operationid_type CHANGEPASSWORD_RESPONSE = 23;

        const operationid_type CHANGEACCESS_REQUEST = 24;
        const operationid_type CHANGEACCESS_RESPONSE = 25;

        const operationid_type ENTITIESINFO_REQUEST = 26;
        const operationid_type ENTITIESINFO_RESPONSE = 27;

        const operationid_type ADDTREND_REQUEST = 28;
        const operationid_type ADDTREND_RESPONSE = 29;
        const operationid_type UPDATETREND_RESPONSE = 30;
        const operationid_type REMOVETREND_REQUEST = 31;
        const operationid_type REMOVETREND_RESPONSE = 32;

        const operationid_type ADDALARMS_REQUEST = 33;
        const operationid_type ADDALARMS_RESPONSE = 34;
        const operationid_type UPDATEALARMS_RESPONSE = 35;
        const operationid_type REMOVEALARMS_REQUEST = 36;
        const operationid_type REMOVEALARMS_RESPONSE = 37;

        const operationid_type ADDDEBUG_REQUEST = 38;
        const operationid_type ADDDEBUG_RESPONSE = 39;
        const operationid_type UPDATEDEBUG_RESPONSE = 40;
        const operationid_type REMOVEDEBUG_REQUEST = 41;
        const operationid_type REMOVEDEBUG_RESPONSE = 42;

        const operationid_type ADDJOURNAL_REQUEST = 43;
        const operationid_type ADDJOURNAL_RESPONSE = 44;
        const operationid_type UPDATEJOURNAL_RESPONSE = 45;
        const operationid_type REMOVEJOURNAL_REQUEST = 46;
        const operationid_type REMOVEJOURNAL_RESPONSE = 47;

        const operationid_type REMOVE_RESPONSE = 48;

        const std::string& SESSION_REQUEST_S = "session";
        const std::string& INIT_REQUEST_S = "init-request";
        const std::string& INIT_RESPONSE_S = "init-response";
        const std::string& UNINIT_REQUEST_S = "uninit-request";
        const std::string& UNINIT_RESPONSE_S = "uninit-response";
        const std::string& UPDATE_REQUEST_S = "update-request";

        const std::string& ADDTAG_REQUEST_S = "addtags-request";
        const std::string& ADDTAG_RESPONSE_S = "addtags-response";
        const std::string& UPDATETAG_RESPONSE_S = "updatetags-response";
        const std::string& REMOVETAG_REQUEST_S = "removetags-request";
        const std::string& REMOVETAG_RESPONSE_S = "removetags-response";

        const std::string& EXECUTE_REQUEST_S = "executeexpressions-request";
        const std::string& EXECUTE_RESPONSE_S = "executeexpressions-response";


        const std::string& REGISTRATEUSER_REQUEST_S = "registrate-request";
        const std::string& REGISTRATEUSER_RESPONSE_S = "registrate-response";

        const std::string& UNREGISTRATEUSER_REQUEST_S = "unregistrate-request";
        const std::string& UNREGISTRATEUSER_RESPONSE_S = "unregistrate-response";

        const std::string& ADDUSER_REQUEST_S = "adduser-request";
        const std::string& ADDUSER_RESPONSE_S = "adduser-response";

        const std::string& REMOVEUSER_REQUEST_S = "removeuser-request";
        const std::string& REMOVEUSER_RESPONSE_S = "removeuser-response";

        const std::string& CHANGEPASSWORD_REQUEST_S = "changepassword-request";
        const std::string& CHANGEPASSWORD_RESPONSE_S = "changepassword-response";

        const std::string& CHANGEACCESS_REQUEST_S = "changeaccess-request";
        const std::string& CHANGEACCESS_RESPONSE_S = "changeaccess-response";

        const std::string& ENTITIESINFO_REQUEST_S = "entities-request";
        const std::string& ENTITIESINFO_RESPONSE_S = "entities-response";

        const std::string& ADDTREND_REQUEST_S = "addtrend-request";
        const std::string& ADDTREND_RESPONSE_S = "addtrend-response";
        const std::string& UPDATETREND_RESPONSE_S = "updatetrend-response";
        const std::string& REMOVETREND_REQUEST_S = "removetrend-request";
        const std::string& REMOVETREND_RESPONSE_S = "removetrend-response";

        const std::string& ADDALARMS_REQUEST_S = "addalarms-request";
        const std::string& ADDALARMS_RESPONSE_S = "addalarms-response";
        const std::string& UPDATEALARMS_RESPONSE_S = "updatealarms-response";
        const std::string& REMOVEALARMS_REQUEST_S = "removealarms-request";
        const std::string& REMOVEALARMS_RESPONSE_S = "removealarms-response";

        const std::string& ADDDEBUG_REQUEST_S = "adddebug-request";
        const std::string& ADDDEBUG_RESPONSE_S = "adddebug-response";
        const std::string& UPDATEDEBUG_RESPONSE_S = "updatedebug-response";
        const std::string& REMOVEDEBUG_REQUEST_S = "removedebug-request";
        const std::string& REMOVEDEBUG_RESPONSE_S = "removedebug-response";

        const std::string& ADDJOURNAL_REQUEST_S = "addjournal-request";
        const std::string& ADDJOURNAL_RESPONSE_S = "addjournal-response";
        const std::string& UPDATEJOURNAL_RESPONSE_S = "updatejournal-response";
        const std::string& REMOVEJOURNAL_REQUEST_S = "removejournal-request";
        const std::string& REMOVEJOURNAL_RESPONSE_S = "removejournal-response";

        const std::string& REMOVE_RESPONSE_S = "remove-response";

        operationmap get_operationid_map_int() {
            operationmap rslt;
            rslt.insert(operationpair(SESSION_REQUEST_S, SESSION_REQUEST));
            rslt.insert(operationpair(INIT_REQUEST_S, INIT_REQUEST));
            rslt.insert(operationpair(INIT_RESPONSE_S, INIT_RESPONSE));
            rslt.insert(operationpair(UNINIT_REQUEST_S, UNINIT_REQUEST));
            rslt.insert(operationpair(UNINIT_RESPONSE_S, UNINIT_RESPONSE));
            rslt.insert(operationpair(UPDATE_REQUEST_S, UPDATE_REQUEST));

            rslt.insert(operationpair(ADDTAG_REQUEST_S, ADDTAG_REQUEST));
            rslt.insert(operationpair(ADDTAG_RESPONSE_S, ADDTAG_RESPONSE));
            rslt.insert(operationpair(UPDATETAG_RESPONSE_S, UPDATETAG_RESPONSE));
            rslt.insert(operationpair(REMOVETAG_REQUEST_S, REMOVETAG_REQUEST));
            rslt.insert(operationpair(REMOVETAG_RESPONSE_S, REMOVETAG_RESPONSE));

            rslt.insert(operationpair(EXECUTE_REQUEST_S, EXECUTE_REQUEST));
            rslt.insert(operationpair(EXECUTE_RESPONSE_S, EXECUTE_RESPONSE));

            rslt.insert(operationpair(REGISTRATEUSER_REQUEST_S, REGISTRATEUSER_REQUEST));
            rslt.insert(operationpair(REGISTRATEUSER_RESPONSE_S, REGISTRATEUSER_RESPONSE));

            rslt.insert(operationpair(UNREGISTRATEUSER_REQUEST_S, UNREGISTRATEUSER_REQUEST));
            rslt.insert(operationpair(UNREGISTRATEUSER_RESPONSE_S, UNREGISTRATEUSER_RESPONSE));

            rslt.insert(operationpair(ADDUSER_REQUEST_S, ADDUSER_REQUEST));
            rslt.insert(operationpair(ADDUSER_RESPONSE_S, ADDUSER_RESPONSE));

            rslt.insert(operationpair(REMOVEUSER_REQUEST_S, REMOVEUSER_REQUEST));
            rslt.insert(operationpair(REMOVEUSER_RESPONSE_S, REMOVEUSER_RESPONSE));

            rslt.insert(operationpair(CHANGEPASSWORD_REQUEST_S, CHANGEPASSWORD_REQUEST));
            rslt.insert(operationpair(CHANGEPASSWORD_RESPONSE_S, CHANGEPASSWORD_RESPONSE));

            rslt.insert(operationpair(CHANGEACCESS_REQUEST_S, CHANGEACCESS_REQUEST));
            rslt.insert(operationpair(CHANGEACCESS_RESPONSE_S, CHANGEACCESS_RESPONSE));

            rslt.insert(operationpair(ENTITIESINFO_REQUEST_S, ENTITIESINFO_REQUEST));
            rslt.insert(operationpair(ENTITIESINFO_RESPONSE_S, ENTITIESINFO_RESPONSE));

            rslt.insert(operationpair(ADDTREND_REQUEST_S, ADDTREND_REQUEST));
            rslt.insert(operationpair(ADDTREND_RESPONSE_S, ADDTREND_RESPONSE));
            rslt.insert(operationpair(UPDATETREND_RESPONSE_S, UPDATETREND_RESPONSE));
            rslt.insert(operationpair(REMOVETREND_REQUEST_S, REMOVETREND_REQUEST));
            rslt.insert(operationpair(REMOVETREND_RESPONSE_S, REMOVETREND_RESPONSE));

            rslt.insert(operationpair(ADDALARMS_REQUEST_S, ADDALARMS_REQUEST));
            rslt.insert(operationpair(ADDALARMS_RESPONSE_S, ADDALARMS_RESPONSE));
            rslt.insert(operationpair(UPDATEALARMS_RESPONSE_S, UPDATEALARMS_RESPONSE));
            rslt.insert(operationpair(REMOVEALARMS_REQUEST_S, REMOVEALARMS_REQUEST));
            rslt.insert(operationpair(REMOVEALARMS_RESPONSE_S, REMOVEALARMS_RESPONSE));

            rslt.insert(operationpair(ADDDEBUG_REQUEST_S, ADDDEBUG_REQUEST));
            rslt.insert(operationpair(ADDDEBUG_RESPONSE_S, ADDDEBUG_RESPONSE));
            rslt.insert(operationpair(UPDATEDEBUG_RESPONSE_S, UPDATEDEBUG_RESPONSE));
            rslt.insert(operationpair(REMOVEDEBUG_REQUEST_S, REMOVEDEBUG_REQUEST));
            rslt.insert(operationpair(REMOVEDEBUG_RESPONSE_S, REMOVEDEBUG_RESPONSE));

            rslt.insert(operationpair(ADDJOURNAL_REQUEST_S, ADDJOURNAL_REQUEST));
            rslt.insert(operationpair(ADDJOURNAL_RESPONSE_S, ADDJOURNAL_RESPONSE));
            rslt.insert(operationpair(UPDATEJOURNAL_RESPONSE_S, UPDATEJOURNAL_RESPONSE));
            rslt.insert(operationpair(REMOVEJOURNAL_REQUEST_S, REMOVEJOURNAL_REQUEST));
            rslt.insert(operationpair(REMOVEJOURNAL_RESPONSE_S, REMOVEJOURNAL_RESPONSE));

            rslt.insert(operationpair(REMOVE_RESPONSE_S, REMOVE_RESPONSE));
            return rslt;
        }





        ////////////////////////////////////////////////////////
        //  get request func
        ////////////////////////////////////////////////////////                 

        const operationmap& get_operationid_map() {
            static operationmap rslt = get_operationid_map_int();
            return rslt;
        }

        operationid_type get_operationid(const std::string& key) {
            const operationmap& mp = get_operationid_map();
            operationmap::const_iterator fnd = mp.find(key);
            if (fnd != mp.end())
                return fnd->second;
            return 0;
        }

        static bool get_tags_list(const boost::property_tree::ptree& req, tagset_type& tgs) {
            for (ptree::ptree::const_iterator it = req.begin(); it != req.end(); ++it) {
                std::string item_id = it->first;
                std::string item_tag = it->second.get_value<std::string>();
                if (!item_tag.empty())
                    tgs.insert(entity_atom(item_id, item_tag, false));
            }
            return !tgs.empty();
        }

        static bool get_tags_list(const boost::property_tree::ptree& req, str_vect& tgs) {
            for (ptree::ptree::const_iterator it = req.begin(); it != req.end(); ++it) {
                std::string item_tag = it->second.get_value<std::string>();
                if (!item_tag.empty())
                    tgs.push_back(item_tag);
            }
            return !tgs.empty();
        }

        static bool get_executes_list(const boost::property_tree::ptree& req, executevect_type& excs) {
            for (ptree::ptree::const_iterator it = req.begin(); it != req.end(); ++it) {
                std::string item_id = it->first;
                std::string item_expr = it->second.get_value<std::string>();
                if (!item_expr.empty()) {
                    if (!item_id.empty())
                        excs.push_back(entity_atom(item_id, item_expr, true));
                }
            }
            return !excs.empty();
        }






        ////////////////////////////////////////////////////////
        //  add to response func
        ////////////////////////////////////////////////////////           


        ////////////////////////////////////////////////////////
        //  registrate func
        ////////////////////////////////////////////////////////                

        static bool add_registrates_func(const registratemap_type& vls, ptree::ptree& resp) {
            for (registratemap_type::const_iterator it = vls.begin(); it != vls.end(); ++it) {
                ptree::ptree result;
                ptree::ptree subresult;
                subresult.put("error", dvnci::to_str(it->second.error));
                result.add_child(it->first, subresult);
                switch (it->second.type) {
                    case registrate_listener::REGIST: resp.add_child(REGISTRATEUSER_RESPONSE_S, result);
                        break;
                    case registrate_listener::UNREGIST: resp.add_child(UNREGISTRATEUSER_RESPONSE_S, result);
                        break;
                    case registrate_listener::ADDUSER: resp.add_child(ADDUSER_RESPONSE_S, result);
                        break;
                    case registrate_listener::REMOVEUSER: resp.add_child(REMOVEUSER_RESPONSE_S, result);
                        break;
                    case registrate_listener::CHANGEPASS: resp.add_child(CHANGEPASSWORD_RESPONSE_S, result);
                        break;
                    case registrate_listener::CHANGEACCESS: resp.add_child(CHANGEACCESS_RESPONSE_S, result);
                        break;
                    default:
                    {
                    }
                }
            }
            return false;
        }



        ////////////////////////////////////////////////////////
        //  update value func
        ////////////////////////////////////////////////////////   
        
       /* static std::string correct_utf8(const std::string& val) {
            const std::string& hexdigits = "0123456789ABCDEF";
            std::string result;
            for (std::string::size_type it = 0; it<val.length(); ++it) {
                std::string::value_type tst=val[it];
                if ((tst & 0x80)) 
                    result += ("\\x" + hexdigits.substr(0xF & (tst >> 4),1) + hexdigits.substr(0xF & tst,1));
                else
                    result+=tst;
            }       
            return result;
        }*/        

        static ptree::ptree add_tag_value(const short_value& val) {
            ptree::ptree result;
            if (!val.error()) {
                if (val.type() == dvnci::TYPE_TEXT) {
                    //std::string tmp = val.value<std::string>();
                    result.put("value", val.value<std::string>());
                } else
                    result.put("value", val.value<std::string>());
                result.put("type", dvnci::to_str(val.type()));
                result.put("valid", dvnci::to_str(val.valid()));
                //result.put("time", dvnci::to_str(val.time()));
            } else {
                result.put("error", dvnci::to_str(val.error()));
            }
            return result;
        }

        static bool add_vaues_func(const valuemap_type& vls, ptree::ptree& resp) {
            ptree::ptree result;
            bool has_exec = false;
            resp.add_child(UPDATETAG_RESPONSE_S, ptree::ptree());
            for (valuemap_type::const_iterator it = vls.begin(); it != vls.end(); ++it) {
                if (it->first.single())
                    has_exec = true;
                else
                    result.add_child(it->first.expr(), add_tag_value(it->second));
            }
            resp.get_child(UPDATETAG_RESPONSE_S).swap(result);
            result.clear();
            if (has_exec) {
                resp.add_child(EXECUTE_RESPONSE_S, ptree::ptree());
                for (valuemap_type::const_iterator it = vls.begin(); it != vls.end(); ++it) {
                    if (it->first.single()) {
                        result.add_child(it->first.id(), add_tag_value(it->second));
                    }
                }
                resp.get_child(EXECUTE_RESPONSE_S).swap(result);
            }
            return false;
        }



        ////////////////////////////////////////////////////////
        //  entity info func
        ////////////////////////////////////////////////////////         

        static void add_entity_info(const iteminfo_map& val, ptree::ptree& result) {
            for (iteminfo_map::const_iterator it = val.begin(); it != val.end(); ++it) {
                ptree::ptree subresult;
                subresult.put("name", it->second.name());
                subresult.put("type", dvnci::to_str(it->second.typeex().operator dvnci::num64()));
                result.add_child(dvnci::to_str(it->first), subresult);
            }
        }

        static bool add_entities_func(const entetyinfomap_type& vls, ptree::ptree& resp) {
            ptree::ptree result;
            for (entetyinfomap_type::const_iterator it = vls.begin(); it != vls.end(); ++it) {
                result.add_child(it->first, ptree::ptree());
                add_entity_info(it->second, result.get_child(it->first));
            }
            resp.add_child(ENTITIESINFO_RESPONSE_S, ptree::ptree());
            resp.get_child(ENTITIESINFO_RESPONSE_S).swap(result);
            return false;
        }


        ////////////////////////////////////////////////////////
        //  add trend func
        ////////////////////////////////////////////////////////                 

        static void add_trend_value(const dvnci::short_value_vect& val, ptree::ptree& result) {
            for (dvnci::short_value_vect::const_iterator it = val.begin(); it != val.end(); ++it) {
                ptree::ptree subresult, arr1, arr2;
                arr1.put("", dvnci::datetime_to_epoch_msc(it->time()));
                if (it->valid() < 100)
                    arr2.put("", "null");
                else
                    arr2.put("", it->value<double>());
                subresult.push_back(std::pair<std::string, ptree::ptree>("", arr1));
                subresult.push_back(std::pair<std::string, ptree::ptree>("", arr2));
                result.push_back(std::pair<std::string, ptree::ptree>("", subresult));
            }
        }

        static void add_trends_value(const short_values_table& val, ptree::ptree& result) {
            for (short_values_table::const_iterator it = val.begin(); it != val.end(); ++it) {
                result.push_back(std::pair<std::string, ptree::ptree>("", ptree::ptree()));
                ptree::ptree& subresult=result.back().second;
                subresult.put("start", it->first.second == 1 ? "true" : "false");
                subresult.put("tag", it->first.first);
                if (it->first.second > 1) {
                    subresult.put("error", "true");
                } else {
                    subresult.add_child("data", ptree::ptree());
                    add_trend_value(it->second, subresult.get_child("data"));
                }
            }
        }

        static bool add_trends_func(const short_values_map_type& vls, ptree::ptree& resp) {
            ptree::ptree result;
            for (short_values_map_type::const_iterator it = vls.begin(); it != vls.end(); ++it) {
                result.add_child(it->first, ptree::ptree());
                add_trends_value(it->second, result.get_child(it->first));
            }
            resp.add_child(UPDATETREND_RESPONSE_S, ptree::ptree());
            resp.get_child(UPDATETREND_RESPONSE_S).swap(result);
            return false;
        }



        ////////////////////////////////////////////////////////
        //  add remove func
        ////////////////////////////////////////////////////////          

        static bool add_removes_func(const removesessionid_type& vls, ptree::ptree& resp) {
            ptree::ptree result;
            for (removesessionid_type::const_iterator it = vls.begin(); it != vls.end(); ++it) {
                ptree::ptree subresult;
                subresult.put("error", it->second);
                result.add_child(it->first, subresult);
            }
            resp.add_child(REMOVE_RESPONSE_S, ptree::ptree());
            resp.get_child(REMOVE_RESPONSE_S).swap(result);
            return true;
        }




        ////////////////////////////////////////////////////////
        //  all update  func
        ////////////////////////////////////////////////////////          

        static void update_all_value(http_session_ptr session, ptree::ptree& resp) {
            if (!session->regaction().empty()) {
                add_registrates_func(session->regaction(), resp);
                session->regaction().clear();
            }
            if (!session->updatelist().empty()) {
                add_vaues_func(session->updatelist(), resp);
                session->updatelist().clear();
            }
            if (!session->entetyinfo().empty()) {
                add_entities_func(session->entetyinfo(), resp);
                session->entetyinfo().clear();
            }
            if (!session->trends().empty()) {
                add_trends_func(session->trends(), resp);
                session->trends().clear();
            }
            if (!session->removesessionid().empty()) {
                add_removes_func(session->removesessionid(), resp);
                session->removesessionid().clear();
            }
        }




        ////////////////////////////////////////////////////////
        //  http_terminated_thread
        ////////////////////////////////////////////////////////          

        http_executor_ptr build_http_executor() {
            dvnci::fspath basepath = dvnci::getlocalbasepath();
            dvnci::tagsbase_ptr kintf = dvnci::krnl::factory::build(basepath, 0);
            if (kintf)
                return http_executor_ptr(new http_gui_executor(kintf));
            //static guichrome_terminated_thread dvnth(DVNCI_INTERFACE);
            return http_executor_ptr();
        }

        http_terminated_thread_ptr build_http_execthread() {
            http_executor_ptr exec = build_http_executor();
            if (exec)
                return http_terminated_thread_ptr(new http_terminated_thread(exec));
            return http_terminated_thread_ptr();
        }

        http_session_ptr build_http_session(sessionid_type id) {
            http_terminated_thread_ptr thr = build_http_execthread();
            if (thr) {
                return http_session_ptr(new http_session(id, thr));
            }
            return http_session_ptr();
        }




        ////////////////////////////////////////////////////////
        //  entity_atom
        ////////////////////////////////////////////////////////             

        bool operator<(const entity_atom& ls, const entity_atom& rs) {
            return (ls.id_ + "-" + ls.expr_) < (rs.id_ + "-" + rs.expr_);
        }

        bool operator==(const entity_atom& ls, const entity_atom& rs) {
            return (ls.id_ + "-" + ls.expr_) == (rs.id_ + "-" + rs.expr_);
        }



        ////////////////////////////////////////////////////////
        //  http_base_listener
        ////////////////////////////////////////////////////////         

        http_expression_listener::http_expression_listener(const entity_atom& exp, http_session_ptr sess, bool single, bool test) :
        expression_listener(single, test), expr(exp), session(sess) {
        }

        void http_expression_listener::event(const short_value& val) {
            if (session) {
                session->updatelist()[expr] = val;
            }
        }


        ////////////////////////////////////////////////////////
        //   http_registrate_listener
        ////////////////////////////////////////////////////////              

        http_registrate_listener::http_registrate_listener(http_session_ptr sess, const std::string& id, int type,
                const std::string& user, const std::string& password, const std::string& newpassword)
        : registrate_listener(type, user, password, newpassword), session(sess), operid_(id) {
        };

        void http_registrate_listener::event(const ns_error& val) {
            if (session) {
                session->regaction().insert(
                        registratemap_type::value_type(id(), registrate_struct(val, type())));
            }
        }



        ////////////////////////////////////////////////////////
        //   http_entety_listener
        ////////////////////////////////////////////////////////   

        http_entety_listener::http_entety_listener(http_session_ptr sess, const std::string& id,
                nodetype enttp, indx parentid, const std::string& filter)
        : entety_listener(enttp, parentid, filter), session(sess), operid_(id) {
        };

        void http_entety_listener::event(const iteminfo_map & val) {
            if (session) {
                session->entetyinfo().insert(
                        entetyinfomap_type::value_type(id(), val));
            }
        }

        ////////////////////////////////////////////////////////
        //   http_trend_listener
        ////////////////////////////////////////////////////////         

        http_trend_listener::http_trend_listener(http_session_ptr sess, const std::string& id,
                const str_vect& tgs, num64 histmilisec)
        : trend_listener(tgs, histmilisec), session(sess), operid_(id) {
        };

        void http_trend_listener::event(const short_values_table & val) {
            if (session) {
                session->trends().insert(
                        short_values_map_type::value_type(id(), val));
            }
        }


        ////////////////////////////////////////////////////////
        //  http_session
        ////////////////////////////////////////////////////////           

        http_session::http_session(sessionid_type id, http_terminated_thread_ptr th_, std::size_t ltm) :
        id_(id), session_livetm_(MIN_SESSION_LT > ltm ?
        MIN_SESSION_LT : (MAX_SESSION_LT < ltm ? MAX_SESSION_LT : ltm)),
        th(th_), mtx_(), dt_(dvnci::now()) {
        }

        void http_session::addtags(const tagset_type& vl) {
            http_executor_ptr inf = intf();
            if (inf) {
                for (tagset_type::const_iterator it = vl.begin(); it != vl.end(); ++it) {
                    expression_listener_ptr exrptr = expression_listener_ptr(new http_expression_listener(*it, shared_from_this()));
                    inf->regist_expr_listener(it->expr(), exrptr);
                    expressionlisteners().insert(expression_listener_map_type::value_type(it->id(), exrptr));
                }
            }
        }

        void http_session::addexecutes(const executevect_type& vl) {
            http_executor_ptr inf = intf();
            if (inf) {
                for (executevect_type::const_iterator it = vl.begin(); it != vl.end(); ++it) {
                    expression_listener_ptr exrptr = expression_listener_ptr(new http_expression_listener(*it, shared_from_this(), true));
                    inf->regist_expr_listener(it->expr(), exrptr);
                }
            }
            std::cout << std::endl;
        }

        void http_session::removetags(const tagset_type& vl) {
            http_executor_ptr inf = intf();
            if (inf) {
                for (tagset_type::const_iterator it = vl.begin(); it != vl.end(); ++it) {
                    //inf->
                }
            }
        }

        void http_session::registrate_operation(operationid_type oper, const ptree::ptree& req) {
            http_executor_ptr inf = intf();
            if (inf) {
                for (ptree::ptree::const_iterator it = req.begin(); it != req.end(); ++it) {
                    std::string item_id = it->first;
                    std::string arg1 = "";
                    std::string arg2 = "";
                    std::string arg3 = "";
                    int type = registrate_listener::REGIST;
                    switch (oper) {
                        case REGISTRATEUSER_REQUEST:
                        {
                            arg1 = it->second.get<std::string>("user", "");
                            arg2 = it->second.get<std::string>("password", "");
                            type = registrate_listener::REGIST;
                            break;
                        }
                        case UNREGISTRATEUSER_REQUEST:
                        {
                            arg1 = it->second.get<std::string>("user", "");
                            type = registrate_listener::UNREGIST;
                            break;
                        }
                        case ADDUSER_REQUEST:
                        {
                            arg1 = it->second.get<std::string>("user", "");
                            arg2 = it->second.get<std::string>("password", "");
                            arg3 = it->second.get<std::string>("access", "");
                            type = registrate_listener::ADDUSER;
                            break;
                        }
                        case REMOVEUSER_REQUEST:
                        {
                            arg1 = it->second.get<std::string>("user", "");
                            arg2 = it->second.get<std::string>("password", "");
                            type = registrate_listener::REMOVEUSER;
                            break;
                        }
                        case CHANGEPASSWORD_REQUEST:
                        {
                            arg1 = it->second.get<std::string>("user", "");
                            arg2 = it->second.get<std::string>("passwordold", "");
                            arg3 = it->second.get<std::string>("passwordnew", "");
                            type = registrate_listener::CHANGEPASS;
                            break;
                        }
                        case CHANGEACCESS_REQUEST:
                        {
                            arg1 = it->second.get<std::string>("user", "");
                            arg2 = it->second.get<std::string>("password", "");
                            arg3 = it->second.get<std::string>("access", "");
                            type = registrate_listener::CHANGEACCESS;
                            break;
                        }
                        default:
                        {
                        }
                    }
                    registrate_listener_ptr regptr = registrate_listener_ptr(
                            new http_registrate_listener(shared_from_this(), item_id, type, arg1, arg2, arg3));
                    inf->regist_registrate_listener(regptr);
                }
            }
        }

        void http_session::enities_operation(const boost::property_tree::ptree& req) {
            http_executor_ptr inf = intf();
            if (inf) {
                for (ptree::ptree::const_iterator it = req.begin(); it != req.end(); ++it) {
                    std::string item_id = it->first;
                    nodetype type = it->second.get<nodetype>("type", 0);
                    indx index = it->second.get<indx>("indx", dvnci::npos);
                    std::string filter = it->second.get<std::string>("filter", "");
                    if (type) {
                        entety_listener_ptr entptr = entety_listener_ptr(
                                new http_entety_listener(shared_from_this(), item_id, type, index, filter));
                        inf->regist_entety_listener(entptr);
                    }
                }
            }
        }

        void http_session::addtrend_operation(const boost::property_tree::ptree& req) {
            http_executor_ptr inf = intf();
            if (inf) {
                for (ptree::ptree::const_iterator it = req.begin(); it != req.end(); ++it) {
                    std::string item_id = it->first;
                    num64 period = it->second.get<num64>("period", 0);
                    str_vect tgs;
                    std::string tg = it->second.get<std::string>("tag", "");
                    if (tg.empty())
                        std::string tg = it->second.get<std::string>("taglist", "");
                    if (tg.empty())
                        get_tags_list(it->second.get_child_optional("taglist").get(), tgs);
                    else
                        tgs.push_back(tg);
                    if (!tgs.empty()) {
                        trend_listener_ptr trendptr = trend_listener_ptr(
                                new http_trend_listener(shared_from_this(), item_id, tgs, period));
                        inf->regist_trend_listener(trendptr);
                        trendlisteners().insert(trend_listener_map_type::value_type(item_id, trendptr));
                    }
                }
            }
        }

        void http_session::removetrend_operation(const boost::property_tree::ptree& req) {
            http_executor_ptr inf = intf();
            if (inf) {
                for (ptree::ptree::const_iterator it = req.begin(); it != req.end(); ++it) {
                    std::string item_id = it->first;
                    trend_listener_map_type::iterator fit = trendlisteners().find(item_id);
                    if (fit != trendlisteners().end()) {
                        inf->unregist_trend_listener(fit->second);
                        trendlisteners().erase(fit);
                        removesessionid().insert(removesessionid_type::value_type(item_id, 0));
                    } else
                        removesessionid().insert(removesessionid_type::value_type(item_id, 1));
                }
            }
        }

        void http_session::addalarms_operation(const boost::property_tree::ptree& req) {
            http_executor_ptr inf = intf();
            if (inf) {
                for (ptree::ptree::const_iterator it = req.begin(); it != req.end(); ++it) {
                }
            }
        }

        void http_session::removealarms_operation(const boost::property_tree::ptree& req) {
            http_executor_ptr inf = intf();
            if (inf) {
                for (ptree::ptree::const_iterator it = req.begin(); it != req.end(); ++it) {
                }
            }
        }

        void http_session::adddebug_operation(const boost::property_tree::ptree& req) {
            http_executor_ptr inf = intf();
            if (inf) {
                for (ptree::ptree::const_iterator it = req.begin(); it != req.end(); ++it) {
                }
            }
        }

        void http_session::removedebug_operation(const boost::property_tree::ptree& req) {
            http_executor_ptr inf = intf();
            if (inf) {
                for (ptree::ptree::const_iterator it = req.begin(); it != req.end(); ++it) {
                }
            }
        }

        void http_session::addjournal_operation(const boost::property_tree::ptree& req) {
            http_executor_ptr inf = intf();
            if (inf) {
                for (ptree::ptree::const_iterator it = req.begin(); it != req.end(); ++it) {
                }
            }
        }

        void http_session::removejournal_operation(const boost::property_tree::ptree& req) {
            http_executor_ptr inf = intf();
            if (inf) {
                for (ptree::ptree::const_iterator it = req.begin(); it != req.end(); ++it) {
                }
            }
        }

        reply::status_type http_session::proccess_request(operationid_type oper, const ptree::ptree& req, ptree::ptree& resp) {
            reply::status_type result = reply::none;
            THD_EXCLUSIVE_LOCK(mtx_);
            switch (oper) {
                case UPDATE_REQUEST:
                {
                    resp.put(SESSION_REQUEST_S, id_);
                    update_all_value(shared_from_this(), resp);
                    result = reply::ok;
                    break;
                }
                case ADDTAG_REQUEST:
                {
                    tagset_type tgs;
                    if (get_tags_list(req, tgs))
                        addtags(tgs);
                    resp.put(SESSION_REQUEST_S, id_);
                    result = reply::ok;
                    break;

                }
                case EXECUTE_REQUEST:
                {
                    executevect_type excs;
                    if (get_executes_list(req, excs))
                        addexecutes(excs);
                    resp.put(SESSION_REQUEST_S, id_);
                    result = reply::ok;
                    break;

                }
                case REMOVETAG_REQUEST:
                {
                    tagset_type tgs;
                    if (get_tags_list(req, tgs))
                        removetags(tgs);
                    resp.put(SESSION_REQUEST_S, id_);
                    result = reply::ok;
                    break;
                }
                case REGISTRATEUSER_REQUEST:
                case UNREGISTRATEUSER_REQUEST:
                case ADDUSER_REQUEST:
                case REMOVEUSER_REQUEST:
                case CHANGEPASSWORD_REQUEST:
                case CHANGEACCESS_REQUEST:
                {
                    registrate_operation(oper, req);
                    resp.put(SESSION_REQUEST_S, id_);
                    result = reply::ok;
                    break;
                }
                case ENTITIESINFO_REQUEST:
                {
                    enities_operation(req);
                    resp.put(SESSION_REQUEST_S, id_);
                    result = reply::ok;
                    break;
                }
                case ADDTREND_REQUEST:
                {
                    addtrend_operation(req);
                    resp.put(SESSION_REQUEST_S, id_);
                    result = reply::ok;
                    break;
                }
                case REMOVETREND_REQUEST:
                {
                    removetrend_operation(req);
                    resp.put(SESSION_REQUEST_S, id_);
                    result = reply::ok;
                    break;
                }
                case ADDALARMS_REQUEST:
                {
                    addalarms_operation(req);
                    resp.put(SESSION_REQUEST_S, id_);
                    result = reply::ok;
                    break;
                }
                case REMOVEALARMS_REQUEST:
                {
                    removealarms_operation(req);
                    resp.put(SESSION_REQUEST_S, id_);
                    result = reply::ok;
                    break;
                }
                case ADDDEBUG_REQUEST:
                {
                    adddebug_operation(req);
                    resp.put(SESSION_REQUEST_S, id_);
                    result = reply::ok;
                    break;
                }
                case REMOVEDEBUG_REQUEST:
                {
                    removedebug_operation(req);
                    resp.put(SESSION_REQUEST_S, id_);
                    result = reply::ok;
                    break;
                }

                case ADDJOURNAL_REQUEST:
                {
                    addjournal_operation(req);
                    resp.put(SESSION_REQUEST_S, id_);
                    result = reply::ok;
                    break;
                }
                case REMOVEJOURNAL_REQUEST:
                {
                    removejournal_operation(req);
                    resp.put(SESSION_REQUEST_S, id_);
                    result = reply::ok;
                    break;
                }
                default:
                {

                }
            }
            return result;
        }

        void http_session::call() {
            THD_EXCLUSIVE_LOCK(mtx_);
            if (th->intf())
                th->intf()->call();
        }

        std::size_t http_session::session_livetm() const {
            return session_livetm_;
        }

        bool http_session::expired() const {
            return std::abs(dvnci::secondsbetween(dt_, dvnci::now()) > session_livetm());
        }

        void http_session::updtate_time() {
            dt_ = dvnci::now();
        }

        http_executor_ptr http_session::intf() {
            return th ? (th->intf()) : http_executor_ptr();
        }


        ////////////////////////////////////////////////////////
        //  http_session_manager
        ////////////////////////////////////////////////////////    

        http_session_ptr http_session_manager::get(sessionid_type id) {
            http_session_map::iterator fit = session_map.find(id);
            if (fit != session_map.end()) {
                return fit->second;
            }
            return http_session_ptr();
        }

        http_session_ptr http_session_manager::create() {
            http_session_ptr newsession = build_http_session(nextid_);
            if (newsession) {
                session_map.insert(http_session_map::value_type(nextid_, newsession));
                if (!(++nextid_))
                    ++nextid_;
                return newsession;
            }
            return http_session_ptr();
        }

        void http_session_manager::check() {
            THD_EXCLUSIVE_LOCK(mtx);
            if (!session_map.empty()) {
                http_session_map::iterator it = session_map.begin();
                while (it != session_map.end()) {
                    if (it->second->expired()) {
                        http_session_map::iterator fit = it;
                        it++;
                        session_map.erase(fit);
                    } else
                        ++it;
                }
            }
        }

        reply::status_type http_session_manager::proccess_request(const std::string& req, std::string& resp) {

            reply::status_type result = reply::none;

            ptree::ptree req_tree;
            ptree::ptree resp_tree;

            std::stringstream ss;
            std::stringstream so;
            ss << req;

            //THD_EXCLUSIVE_LOCK(mtx);

            ptree::json_parser::read_json(ss, req_tree);

            if (result = proccess_request(req_tree, resp_tree)) {

                ptree::json_parser::write_json(so, resp_tree);
                resp = so.str();

            }

            return result;
        }

        reply::status_type http_session_manager::proccess_request(const ptree::ptree& req, ptree::ptree& resp) {

            reply::status_type result = reply::none;

            sessionid_type sid = 0;
            http_session_ptr sess;

            for (ptree::ptree::const_iterator it = req.begin(); it != req.end(); ++it) {
                operationid_type oper = get_operationid(it->first);
                switch (oper) {
                    case INIT_REQUEST:
                    {
                        //THD_EXCLUSIVE_LOCK(mtx);
                        if (sess = create()) {
                            sid = sess->id();
                            resp.put(INIT_RESPONSE_S, sid);
                            result = reply::ok;
                            //std::cout << "New session id=" << sid << 
                            //" was created. Sessins count is " << session_map.size()  << std::endl;
                        }
                        break;
                    }
                    case SESSION_REQUEST:
                    {
                        sid = it->second.get_value<sessionid_type>();
                        {
                            //THD_EXCLUSIVE_LOCK(mtx);
                            sess = get(sid);
                        }
                        if (sess) {
                            //std::cout << "hook session id=" << sid << 
                            //" was created. << std::endl;
                            sess->updtate_time();
                            sess->call();
                        } else
                            return reply::request_timeout;
                        break;
                    }
                    default:
                    {
                        if (sess) {
                            reply::status_type result_p = sess->proccess_request(oper, it->second, resp);
                            if (result == reply::none)
                                result = result_p;
                        }
                    }
                }
            }
            return result;
        }


    }
}
