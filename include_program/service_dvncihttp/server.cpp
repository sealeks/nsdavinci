//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2014 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "server.hpp"
#include <boost/bind.hpp>

namespace http {
    namespace server {

        void sessions_checker::operator()() {
            boost::xtime tx;
            while (manager && !terminated) {
                manager->check();            
                dvnci::addmillisec_to_now(tx, 1000);
                boost::thread::sleep(tx);
            }
        }    
        

        server::server(const std::string& address, const std::string& port,
                const std::string& doc_root, std::size_t io_service_pool_size)
        : io_service_pool_(io_service_pool_size),
        signals_(io_service_pool_.get_io_service()),
        acceptor_(io_service_pool_.get_io_service()),
        new_connection_(),
        manager_( new http_session_manager()),
        checker_(manager_),
        th(checker_),                
        request_handler_(doc_root, manager_){
            // Register to handle the signals that indicate when the server should exit.
            // It is safe to register for the same signal multiple times in a program,
            // provided all registration for the specified signal is made through Asio.
            signals_.add(SIGINT);
            signals_.add(SIGTERM);
#if defined(SIGQUIT)
            signals_.add(SIGQUIT);
#endif // defined(SIGQUIT)
            signals_.async_wait(boost::bind(&server::handle_stop, this));

            // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
            boost::asio::ip::tcp::resolver resolver(acceptor_.get_io_service());
            boost::asio::ip::tcp::resolver::query query(address, port);
            boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
            acceptor_.open(endpoint.protocol());
            acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
            acceptor_.bind(endpoint);
            acceptor_.listen();

            start_accept();
        }

        server::~server() {
            checker_.terminate();
        }            

        void server::run() {
            io_service_pool_.run();
        }

        void server::start_accept() {
            new_connection_.reset(new connection(
                    io_service_pool_.get_io_service(), request_handler_));
            acceptor_.async_accept(new_connection_->socket(),
                    boost::bind(&server::handle_accept, this,
                    boost::asio::placeholders::error));
        }

        void server::handle_accept(const boost::system::error_code& e) {
            if (!e) {
                new_connection_->start();
            }

            start_accept();
        }

        void server::handle_stop() {
            io_service_pool_.stop();
        }

    } // namespace server
} // namespace http
