//
// server.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2014 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_SERVER_SERVER_HPP
#define HTTP_SERVER_SERVER_HPP

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "connection.hpp"
#include "io_service_pool.hpp"
#include "request_handler.hpp"

namespace http {
    namespace server {

        /// The top-level class of the HTTP server.
        
        
        struct sessions_checker {
            
            sessions_checker(http_session_manager_ptr manager_): 
            manager(manager_), terminated(false) {}
            
            ~sessions_checker() {}   
            
            void terminate(){
                terminated=true;
            }
            
            void operator()();
            
            http_session_manager_ptr manager;
            bool terminated;
        };
        
        

        class server
        : private boost::noncopyable {

        public:
            /// Construct the server to listen on the specified TCP address and port, and
            /// serve up files from the given directory.
            explicit server(const std::string& address, const std::string& port,
                    const std::string& doc_root, std::size_t io_service_pool_size);
            
            virtual ~server();        

            /// Run the server's io_service loop.
            void run();

        private:
            /// Initiate an asynchronous accept operation.
            void start_accept();

            /// Handle completion of an asynchronous accept operation.
            void handle_accept(const boost::system::error_code& e);

            /// Handle a request to stop the server.
            void handle_stop();

            /// The pool of io_service objects used to perform asynchronous operations.
            io_service_pool io_service_pool_;

            /// The signal_set is used to register for process termination notifications.
            boost::asio::signal_set signals_;

            /// Acceptor used to listen for incoming connections.
            boost::asio::ip::tcp::acceptor acceptor_;

            /// The next connection to be accepted.
            connection_ptr new_connection_;
            
            // Session_manager
            http_session_manager_ptr manager_;  
            
            sessions_checker checker_;
            
            boost::thread  th;

            /// The handler for all incoming requests.
            request_handler request_handler_;
        };

    } // namespace server
} // namespace http

#endif // HTTP_SERVER_SERVER_HPP
