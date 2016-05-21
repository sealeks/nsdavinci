//
// request_handler.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2014 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "request_executor.hpp"

/*
 Type request:
           
 1. init
  
                                        user                                                                                                                                      server
                                  {  "init-req":  "0"    }                                                          ->           
                                                                                                                                                    <-              {"init-resp" : "RESPID"}
 
 2. process
 
    2.1 add tags in request
 
              { "session" : "RESPID" , add-tag : [... added tags list...] }         ->
     2.2                             
 
 
 */


namespace http {
    namespace server {


        namespace ptree = boost::property_tree;

        typedef int operationid_type;
        typedef std::map<std::string, operationid_type> operationmap;
        typedef std::pair<std::string, operationid_type> operationpair;


        const operationid_type SESSION_REQUEST = 1;
        const operationid_type INIT_REQUEST = 2;
        const operationid_type INIT_RESPONSE = 3;
        const operationid_type ADDTAG_REQUEST = 4;
        const operationid_type REMOVETAG_REQUEST = 5;
        const operationid_type UPDATE_REQUEST = 6;
        const operationid_type UPDATE_RESPONSE = 7;

        const std::string& SESSION_REQUEST_S = "session";
        const std::string& INIT_REQUEST_S = "init-req";
        const std::string& INIT_RESPONSE_S = "init-resp";
        const std::string& ADDTAG_REQUEST_S = "add-tags";
        const std::string& REMOVETAG_REQUEST_S = "remove-tags";
        const std::string& UPDATE_REQUEST_S = "get-update";
        const std::string& UPDATE_RESPONSE_S = "update-response";

        operationmap get_operationid_map_int() {
            operationmap rslt;
            rslt.insert(operationpair(SESSION_REQUEST_S, SESSION_REQUEST));
            rslt.insert(operationpair(INIT_REQUEST_S, INIT_REQUEST));
            rslt.insert(operationpair(INIT_RESPONSE_S, INIT_RESPONSE));
            rslt.insert(operationpair(ADDTAG_REQUEST_S, ADDTAG_REQUEST));
            rslt.insert(operationpair(REMOVETAG_REQUEST_S, REMOVETAG_REQUEST));
            rslt.insert(operationpair(UPDATE_REQUEST_S, UPDATE_REQUEST));
            rslt.insert(operationpair(UPDATE_RESPONSE_S, UPDATE_RESPONSE));
            return rslt;
        }

        const operationmap& get_operationid_map() {
            static operationmap rslt = get_operationid_map_int();
            return rslt;
        }

        operationid_type get_operationid(const std::string& key) {
            const operationmap& mp = get_operationid_map();
            operationmap::const_iterator fnd = mp.find(key);
            if (fnd!=mp.end())
                return fnd->second;
            return 0;
        }

        static bool get_tags_list(const boost::property_tree::ptree& req, tagset_type& tgs) {
            for (ptree::ptree::const_iterator it = req.begin(); it != req.end(); ++it)
                tgs.insert(it->second.get_value<std::string>());
            return !tgs.empty();
        }

        static ptree::ptree add_tag_value(const dvnci::short_value& val) {
            ptree::ptree result;
            result.put("value", val.value<std::string>());
            result.put("type", dvnci::to_str(val.type()));
            result.put("valid", dvnci::to_str(val.valid()));
            return result;
        }

        static void update_tags_value(http_session_ptr session, ptree::ptree& resp) {
            if (!session->updatelist().empty()) {
                ptree::ptree result;
                for (valuemap_type::const_iterator it = session->updatelist().begin(); it != session->updatelist().end(); ++it) {
                    result.add_child(it->first, add_tag_value(it->second));
                }
                resp.add_child("update-value", result);
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
        //  http_base_listener
        ////////////////////////////////////////////////////////         

        http_expression_listener::http_expression_listener(const std::string& exp, http_session_ptr sess) :
        dvnci::expression_listener(), expr(exp), session(sess) {
        }

        void http_expression_listener::event(const dvnci::short_value& val) {
            if (session) {
                session->updatelist()[expr] = val;
            }
        }





        ////////////////////////////////////////////////////////
        //  http_session
        ////////////////////////////////////////////////////////           

        void http_session::addtags(const tagset_type& vl) {
            http_executor_ptr inf = intf();
            std::cout << "add: ";
            for (tagset_type::const_iterator it = vl.begin(); it != vl.end(); ++it) {
                if (it == vl.begin())
                    std::cout << *it;
                else
                    std::cout << ", " << *it;
            }
            if (inf) {
                for (tagset_type::const_iterator it = vl.begin(); it != vl.end(); ++it) {
                    dvnci::expression_listener_ptr exrptr = dvnci::expression_listener_ptr(new http_expression_listener(*it, shared_from_this()));
                    inf->regist_expr_listener(*it, exrptr);
                }
            }
            std::cout << std::endl;
        }

        void http_session::removetags(const tagset_type& vl) {
            http_executor_ptr inf = intf();
            std::cout << "remove: ";
            for (tagset_type::const_iterator it = vl.begin(); it != vl.end(); ++it) {
                if (it == vl.begin())
                    std::cout << *it;
                else
                    std::cout << ", " << *it;
            }
            std::cout << std::endl;
            if (inf) {
                for (tagset_type::const_iterator it = vl.begin(); it != vl.end(); ++it) {
                    //inf->
                }
            }
        }

        reply::status_type http_session::proccess_request(const ptree::ptree& req, ptree::ptree& resp) {
            return reply::none;
        }

        void http_session::call() {
            if (th->intf())
                th->intf()->call();
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

        sessionid_type http_session_manager::create() {
            http_session_ptr newsession = build_http_session(nextid_);
            if (newsession) {
                session_map.insert(http_session_map::value_type(nextid_, newsession));
                sessionid_type result = nextid_;
                if (!(++nextid_))
                    ++nextid_;
                return result;
            }
            return 0;
        }

        reply::status_type http_session_manager::proccess_request(const std::string& req, std::string& resp) {

            reply::status_type result = reply::none;

            ptree::ptree req_tree;
            ptree::ptree resp_tree;

            std::stringstream ss;
            std::stringstream so;
            ss << req;

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
                        if (sid = create()) {
                            resp.put(INIT_RESPONSE_S, sid);
                            result = reply::ok;

                        }
                        break;
                    }
                    case SESSION_REQUEST:
                    {
                        sid = it->second.get_value<sessionid_type>();
                        sess = get(sid);
                        if (sess)
                            sess->call();
                        break;
                    }
                    case UPDATE_REQUEST:
                    {
                        if (sess) {
                            resp.put(INIT_RESPONSE_S, sid);
                            update_tags_value(sess, resp);
                            result = reply::ok;
                        }
                        break;
                    }
                    case ADDTAG_REQUEST:
                    {
                        if (sess) {
                            tagset_type tgs;
                            if (get_tags_list(it->second, tgs))
                                sess->addtags(tgs);
                            resp.put(INIT_RESPONSE_S, sid);
                            result = reply::ok;

                            break;
                        }
                    }
                    case REMOVETAG_REQUEST:
                    {
                        if (sess) {
                            tagset_type tgs;
                            if (get_tags_list(it->second, tgs))
                                sess->removetags(tgs);
                            resp.put(INIT_RESPONSE_S, sid);
                            result = reply::ok;
                        }
                        break;
                    }
                    default:{
                        
                    }
                }
            }
            return result;
        }


    }
}
