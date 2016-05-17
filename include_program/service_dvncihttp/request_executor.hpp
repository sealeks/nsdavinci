//
// request_handler.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2014 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_EXECUTOR_HANDLER_HPP
#define HTTP_EXECUTOR_HANDLER_HPP

#include <string>

#include <custom/gui_executor.h>
#include <kernel/utils.h>
#include <kernel/systemutil.h>
#include <kernel/constdef.h>
#include <kernel/factory.h>

namespace http {
    namespace server {
     

        typedef dvnci::custom::gui_executor<dvnci::tagsbase > http_gui_executor;
        typedef callable_shared_ptr<http_gui_executor> http_executor_ptr;          
        
        ////////////////////////////////////////////////////////
        //  http_terminated_thread
        ////////////////////////////////////////////////////////        
        
        struct http_terminated_thread {

            http_terminated_thread(http_executor_ptr inf_) : inf(inf_), th(inf_) {
            }

            ~http_terminated_thread() {
                if (inf && (!inf->terminated())) {
                    inf->detachall();
                    inf.terminate();
                }
                th.join();
            }

        private:
            http_executor_ptr inf;
            boost::thread th;
        };    
        
        typedef boost::shared_ptr<http_terminated_thread> http_terminated_thread_ptr;
        
      
        
        ////////////////////////////////////////////////////////
        //  http_terminated_thread
        ////////////////////////////////////////////////////////        

        http_executor_ptr build_http_executor();   
        
        http_terminated_thread_ptr build_http_execthread();
        

    } // namespace server
} // namespace http

#endif // HTTP_SERVER_REQUEST_HANDLER_HPP
