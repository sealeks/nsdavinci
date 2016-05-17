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
                

    }
} 
