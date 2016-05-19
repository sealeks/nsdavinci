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


namespace http {
    namespace server {

       
        
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
            if (thr){
                return http_session_ptr( new http_session(id, thr));
            }
            return http_session_ptr();
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
        
    }
} 
