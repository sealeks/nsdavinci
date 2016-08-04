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
 
 
 Type request:
           
 1. init
  
                                        user                                                                                                                                      server
                                  {  "init-req":  "0"    }                                                          ->           
                                                                                                                                                    <-              {"init-resp" : "RESPID"}
 
 2. process
 
    2.1 add tags in request
 
              { "session" : "RESPID" , add-tag : [... added tags list...] }         ->
 
     2.2 remove tags from request
 
              { "session" : "RESPID" , remove-tag : [... remove tags list...] }         ->     
 
     2.3  single execute expression in request
 
              { "session" : "RESPID" , add-execute : [... added executes list...] }         ->         
 
 
 */


namespace http {
    namespace server {


        namespace ptree = boost::property_tree;



        const operationid_type SESSION_REQUEST = 1;
        const operationid_type INIT_REQUEST = 2;
        const operationid_type INIT_RESPONSE = 3;
        const operationid_type ADDTAG_REQUEST = 4;
        const operationid_type ADDTAG_RESPONSE = 5;        
        const operationid_type ADDEXECUTE_REQUEST = 6;        
        const operationid_type ADDEXECUTE_RESPONSE = 7;        
        const operationid_type REMOVETAG_REQUEST = 8;
        const operationid_type REMOVETAG_RESPONSE = 9;        
        const operationid_type UPDATE_REQUEST = 10;
        const operationid_type UPDATE_RESPONSE = 11;
        const operationid_type REGISTRATEUSER_REQUEST = 12;   
        const operationid_type REGISTRATEUSER_RESPONSE = 13;         
        const operationid_type UNREGISTRATEUSER_REQUEST = 14;   
        const operationid_type UNREGISTRATEUSER_RESPONSE = 15;         
        const operationid_type ADDUSER_REQUEST = 16;   
        const operationid_type ADDUSER_RESPONSE = 17;        
        const operationid_type REMOVEUSER_REQUEST = 18;   
        const operationid_type REMOVEUSER_RESPONSE = 19;   
        const operationid_type CHANGEPASSWORD_REQUEST = 20;   
        const operationid_type CHANGEPASSWORD_RESPONSE =21;        
        const operationid_type CHANGEACCESS_REQUEST = 22;   
        const operationid_type CHANGEACCESS_RESPONSE =23;        

        const std::string& SESSION_REQUEST_S = "session";
        const std::string& INIT_REQUEST_S = "init-req";
        const std::string& INIT_RESPONSE_S = "init-resp";
        const std::string& ADDTAG_REQUEST_S = "addtags-request";
        const std::string& ADDTAG_RESPONSE_S = "addtags-response";        
        const std::string& ADDEXECUTE_REQUEST_S = "executeexpressions-request";        
        const std::string& ADDEXECUTE_RESPONSE_S = "executeexpressions-response";        
        const std::string& REMOVETAG_REQUEST_S = "removetags-request";
        const std::string& REMOVETAG_RESPONSE_S = "removetags-response";        
        const std::string& UPDATE_REQUEST_S = "update-request";
        const std::string& UPDATE_RESPONSE_S = "update-response";        
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

        operationmap get_operationid_map_int() {
            operationmap rslt;
            rslt.insert(operationpair(SESSION_REQUEST_S, SESSION_REQUEST));
            rslt.insert(operationpair(INIT_REQUEST_S, INIT_REQUEST));
            rslt.insert(operationpair(INIT_RESPONSE_S, INIT_RESPONSE));
            rslt.insert(operationpair(ADDTAG_REQUEST_S, ADDTAG_REQUEST));
            rslt.insert(operationpair(ADDTAG_RESPONSE_S, ADDTAG_RESPONSE));            
            rslt.insert(operationpair(ADDEXECUTE_REQUEST_S, ADDEXECUTE_REQUEST));        
            rslt.insert(operationpair(ADDEXECUTE_RESPONSE_S, ADDEXECUTE_RESPONSE));             
            rslt.insert(operationpair(REMOVETAG_REQUEST_S, REMOVETAG_REQUEST));
            rslt.insert(operationpair(REMOVETAG_RESPONSE_S, REMOVETAG_RESPONSE));            
            rslt.insert(operationpair(UPDATE_REQUEST_S, UPDATE_REQUEST));
            rslt.insert(operationpair(UPDATE_RESPONSE_S, UPDATE_RESPONSE));
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
            return rslt;
        }

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
                    tgs.insert(entity_atom(item_tag));
            }
            return !tgs.empty();
        }

        static bool get_executes_list(const boost::property_tree::ptree& req, executevect_type& excs) {
            for (ptree::ptree::const_iterator it = req.begin(); it != req.end(); ++it) {
                std::string item_id = it->first;
                std::string item_expr = it->second.get_value<std::string>();
                if (!item_expr.empty()) {
                    if (!item_id.empty())
                        excs.push_back(entity_atom(item_id, item_expr));
                }
            }
            return !excs.empty();
        }       

        static ptree::ptree add_tag_value(const dvnci::short_value& val) {
            ptree::ptree result;
            if (!val.error()) {
                result.put("value", val.value<std::string>());
                result.put("type", dvnci::to_str(val.type()));
                result.put("valid", dvnci::to_str(val.valid()));
                //result.put("time", dvnci::to_str(val.time()));
            } else {
                result.put("error", dvnci::to_str(val.error()));
            }
            return result;
        }

        static void update_all_value(http_session_ptr session, ptree::ptree& resp) {
            if (!session->regaction().empty()) {
                for (registratemap_type::const_iterator it = session->regaction().begin(); it != session->regaction().end(); ++it) {
                    ptree::ptree result;
                    result.put(it->first, dvnci::to_str(it->second.error));
                    switch (it->second.type) {
                        case dvnci::registrate_listener::REGIST: resp.add_child(REGISTRATEUSER_RESPONSE_S, result);
                            break;
                        case dvnci::registrate_listener::UNREGIST: resp.add_child(UNREGISTRATEUSER_RESPONSE_S, result);
                            break;
                        case dvnci::registrate_listener::ADDUSER: resp.add_child(ADDUSER_RESPONSE_S, result);
                            break;
                        case dvnci::registrate_listener::REMOVEUSER: resp.add_child(REMOVEUSER_RESPONSE_S, result);
                            break;
                        case dvnci::registrate_listener::CHANGEPASS: resp.add_child(CHANGEPASSWORD_RESPONSE_S, result);
                            break;
                        case dvnci::registrate_listener::CHANGEACCESS: resp.add_child(CHANGEACCESS_RESPONSE_S, result);
                            break;
                        default:
                        {
                        }
                    }
                }
                session->regaction().clear();
            }
            if (!session->updatelist().empty()) {
                ptree::ptree result;
                bool has_exec = false;
                for (valuemap_type::const_iterator it = session->updatelist().begin(); it != session->updatelist().end(); ++it) {
                    if (it->first.validid())
                        has_exec = true;
                    else
                        result.add_child(it->first.expr(), add_tag_value(it->second));
                }
                resp.add_child(UPDATE_RESPONSE_S, result);
                result.clear();
                if (has_exec) {
                    for (valuemap_type::const_iterator it = session->updatelist().begin(); it != session->updatelist().end(); ++it) {
                        if (it->first.validid()) {
                          result.add_child(it->first.id(), add_tag_value(it->second));
                        }
                    }
                    resp.add_child( ADDEXECUTE_RESPONSE_S, result);
                }
                session->updatelist().clear();
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
        
        bool operator<(const entity_atom& ls, const entity_atom& rs){
            return (ls.id_+"-"+ls.expr_) < (rs.id_+"-"+rs.expr_);
        }
        
        bool operator==(const entity_atom& ls, const entity_atom& rs){
            return (ls.id_+"-"+ls.expr_) == (rs.id_+"-"+rs.expr_);
        }                  
        
        

        ////////////////////////////////////////////////////////
        //  http_base_listener
        ////////////////////////////////////////////////////////         

        http_expression_listener::http_expression_listener(const std::string& exp, http_session_ptr sess, bool single, bool test) :
        dvnci::expression_listener(single, test), expr(exp), session(sess) {
        }
        
        http_expression_listener::http_expression_listener(const entity_atom& exp, http_session_ptr sess, bool single, bool test) :
        dvnci::expression_listener(single, test), expr(exp), session(sess) {
        }        

        void http_expression_listener::event(const dvnci::short_value& val) {
            if (session) {
                session->updatelist()[expr] = val;
            }
        }


        ////////////////////////////////////////////////////////
        //   http_registrate_listener
        ////////////////////////////////////////////////////////              

        http_registrate_listener::http_registrate_listener(http_session_ptr sess, const std::string& id, int type,
                const std::string& user, const std::string& password, const std::string& newpassword)
        : dvnci::registrate_listener(type, user, password, newpassword), session(sess), operid_(id) {
        };

        void http_registrate_listener::event(const dvnci::ns_error& val) {
            if (session) {
                session->regaction().insert(
                registratemap_type::value_type(id(), registrate_struct(val, type())));
            }
        }


        ////////////////////////////////////////////////////////
        //  http_session
        ////////////////////////////////////////////////////////           
        
         http_session::http_session(sessionid_type id, http_terminated_thread_ptr th_, std::size_t ltm) :
            id_(id), session_livetm_(MIN_SESSION_LT > ltm ?  
                MIN_SESSION_LT : (MAX_SESSION_LT < ltm ?  MAX_SESSION_LT  : ltm)), 
                 th(th_), mtx_(), dt_(dvnci::now()) {
            }        

        void http_session::addtags(const tagset_type& vl) {
            http_executor_ptr inf = intf();
            if (inf) {
                for (tagset_type::const_iterator it = vl.begin(); it != vl.end(); ++it) {
                    dvnci::expression_listener_ptr exrptr = dvnci::expression_listener_ptr(new http_expression_listener(*it, shared_from_this()));
                    inf->regist_expr_listener(it->expr(), exrptr);
                }
            }
            std::cout << std::endl;
        }
        
        void http_session::addexecutes(const executevect_type& vl) {    
            http_executor_ptr inf = intf();
            if (inf) {
                for (executevect_type::const_iterator it = vl.begin(); it != vl.end(); ++it) {
                    dvnci::expression_listener_ptr exrptr = dvnci::expression_listener_ptr(new http_expression_listener(*it, shared_from_this(), true));
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
                    int type = dvnci::registrate_listener::REGIST;
                    switch (oper) {
                        case REGISTRATEUSER_REQUEST:
                        {
                            arg1 = it->second.get<std::string>("user", "");
                            arg2 = it->second.get<std::string>("password", "");
                            type = dvnci::registrate_listener::REGIST;
                            break;
                        }
                        case UNREGISTRATEUSER_REQUEST:
                        {
                            arg1 = it->second.get<std::string>("user", "");
                            type = dvnci::registrate_listener::UNREGIST;
                            break;
                        }
                        case ADDUSER_REQUEST:
                        {
                            arg1 = it->second.get<std::string>("user", "");
                            arg2 = it->second.get<std::string>("password", "");
                            arg3 = it->second.get<std::string>("access", "");
                            type = dvnci::registrate_listener::ADDUSER;
                            break;
                        }
                        case REMOVEUSER_REQUEST:
                        {
                            arg1 = it->second.get<std::string>("user", "");
                            arg2 = it->second.get<std::string>("password", "");
                            type = dvnci::registrate_listener::REMOVEUSER;
                            break;
                        }
                        case CHANGEPASSWORD_REQUEST:
                        {
                            arg1 = it->second.get<std::string>("user", "");
                            arg2 = it->second.get<std::string>("passwordold", "");
                            arg3 = it->second.get<std::string>("passwordnew", "");
                            type = dvnci::registrate_listener::CHANGEPASS;
                            break;
                        }
                        case CHANGEACCESS_REQUEST:
                        {
                            arg1 = it->second.get<std::string>("user", "");
                            arg2 = it->second.get<std::string>("password", "");
                            arg3 = it->second.get<std::string>("access", "");
                            type = dvnci::registrate_listener::CHANGEACCESS;
                            break;
                        }
                        default:
                        {

                        }
                    }
                    dvnci::registrate_listener_ptr regptr = dvnci::registrate_listener_ptr(
                            new http_registrate_listener(shared_from_this(), item_id, type, arg1, arg2, arg3));
                    inf->regist_registrate_listener(regptr);
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
                case ADDEXECUTE_REQUEST:
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

        std::size_t http_session::session_livetm() const  {
            return session_livetm_;
        }
                        

        bool http_session::expired() const {
            return std::abs(dvnci::secondsbetween(dt_,  dvnci::now()) > session_livetm());
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
                            sid=sess->id();
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
                        }
                        else
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
