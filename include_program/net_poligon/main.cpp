/* 
 * File:   main.cpp
 * Author: sealeks@mail.ru
 *
 * Created on 27 Сентябрь 2012 г., 15:58
 */

#include <cstdlib>
#include <deque>
#include <iostream>


#include <kernel/constdef.h>
#include <kernel/memfile.h>
#include <kernel/systemutil.h>
#include <kernel/serviceapp.h>
#include <kernel/factory.h>
#include <kernel/templ.h>

#include "rfc1006.h"

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include <cstdio>
#include <cstdlib>
#include <cstring>


int port = 102;

using boost::asio::ip::rfc1006;

enum {
    max_length = 1024
} ;

class session {
public:

    session(boost::asio::io_service& io_service)
    : socket_(io_service, "SERVER-TSE") {
        std::cout << "New sesion\n";
    }

    rfc1006::socket& socket() {
        return socket_;
    }

    void start() {
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
                boost::bind(&session::handle_read, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));

    }

private:

    void handle_read(const boost::system::error_code& error,
            size_t bytes_transferred) {
        if (!error) {
            boost::asio::async_write(socket_,
                    boost::asio::buffer(data_, bytes_transferred),
                    boost::bind(&session::handle_write, this,
                    boost::asio::placeholders::error));
            std::cout << "Server read: " <<  std::string(data_, bytes_transferred) <<  " size: " <<  bytes_transferred << std::endl;
            message = std::string(data_, bytes_transferred);
        }
        else {
            delete this;
        }
    }

    void handle_write(const boost::system::error_code& error) {
        if (!error) {
            std::cout << "Server write: " <<  message <<  " size: " <<  message.size() << std::endl;
            socket_.async_read_some(boost::asio::buffer(data_, max_length),
                    boost::bind(&session::handle_read, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        }
        else {
            delete this;
        }
    }

    rfc1006::socket socket_;
    char data_[max_length];
    std::string message;
} ;

class server {
public:

    server(boost::asio::io_service& io_service, short port)
    : io_service_(io_service),
    acceptor_(io_service, rfc1006::endpoint(boost::asio::ip::tcp::v4(), port)) {
        start_accept();
    }

private:

    void start_accept() {
        session* new_session = new session(io_service_);
        acceptor_.async_accept(new_session->socket(),
                boost::bind(&server::handle_accept, this, new_session,
                boost::asio::placeholders::error));
    }

    void handle_accept(session* new_session,
            const boost::system::error_code& error) {
        if (!error) {
            new_session->start();
        }
        else {
            delete new_session;
        }

        start_accept();
    }

    boost::asio::io_service& io_service_;
    rfc1006::acceptor acceptor_;
} ;

class client {
public:

    client(boost::asio::io_service& io_service,
            rfc1006::resolver::iterator endpoint_iterator, const std::string& called = "")
    : io_service_(io_service),
    socket_(io_service, called) {
        rfc1006::endpoint endpoint = *endpoint_iterator;
        socket_.async_connect(endpoint,
                boost::bind(&client::handle_connect, this,
                boost::asio::placeholders::error, ++endpoint_iterator));
    }

    ~client() {
        if (socket_.is_open()) {
            socket_.close();
        }
    }

    void release() {
              io_service_.reset();
              socket_.asyn_releaseconnect(boost::bind(&client::handle_release, this, boost::asio::placeholders::error));
              io_service_.poll();
    }

    void write(const std::string& msg) {
        //do_write(msg);
        io_service_.post(boost::bind(&client::do_write, this, msg));
        message = msg;
    }

    void close() { //do_close();
        io_service_.post(boost::bind(&client::do_close, this));
    }

private:
    
    

    void handle_connect(const boost::system::error_code& error,
            rfc1006::resolver::iterator endpoint_iterator) {
        if (!error) {
            /*  socket_.async_read_some(boost::asio::buffer(data_, max_length),
          boost::bind(&client::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));*/
        }
        else if (endpoint_iterator != rfc1006::resolver::iterator()) {
            socket_.close();
            rfc1006::endpoint endpoint = *endpoint_iterator;
            socket_.async_connect(endpoint,
                    boost::bind(&client::handle_connect, this,
                    boost::asio::placeholders::error, ++endpoint_iterator));
        }
    }
    
    void handle_release(const boost::system::error_code& error) {
        std::cout << "Client release :" << (error ? "error " : "success") << std::endl;
    }
    

    void handle_read(const boost::system::error_code& error,
            size_t bytes_transferred) {
        if (!error) {
            std::cout << "Client read:" << std::string(data_, bytes_transferred) <<  " size: " <<  bytes_transferred << std::endl;
        }
        else {
            do_close();
        }
    }

    void do_write(const std::string& msg) {
        std::cout << "Client write:" << msg <<  " size: " <<  msg.size() << std::endl;
        boost::asio::async_write(socket_,
                boost::asio::buffer(msg.data(),
                msg.size()),
                boost::bind(&client::handle_write, this,
                boost::asio::placeholders::error));

    }

    void handle_write(const boost::system::error_code& error) {
        if (!error) {
            /*boost::asio::async_read(socket_,
              boost::asio::buffer(data_, max_length),
              boost::bind(&client::handle_read, this,
                boost::asio::placeholders::error));*/
            socket_.async_read_some(boost::asio::buffer(data_, max_length),
                    boost::bind(&client::handle_read, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        }
        else {
            do_close();
        }
    }

    void do_close() {
        socket_.close();
    }

private:
    boost::asio::io_service& io_service_;
    rfc1006::socket socket_;
    std::string message;
    char data_[max_length];
} ;







using namespace std;

struct Server {

    Server(boost::asio::io_service & serv) : terminated_(false), io_service(serv), server_(io_service, port) {
    }

    bool operator()() {
        //io_service.run(); 
        while (!terminated_) {
            boost::xtime xt_loop;
            dvnci::addmillisec_to_now(xt_loop, 100);
            boost::thread::sleep(xt_loop);
        }
        io_service.stop();
        return true;
    }

    void terminate() {
        terminated_ = true;
    }

private:
    bool terminated_;
    boost::asio::io_service& io_service;
    server server_;
} ;

typedef callable_shared_ptr< Server >                         server_ptr;

struct Client {

    Client(boost::asio::io_service& serv, const std::string & host) : terminated_(false), io_service(serv), resolver(io_service), query(boost::asio::ip::tcp::v4(), host , dvnci::to_str(port)),
    iterator(resolver.resolve(query)) ,
    client_(io_service, iterator, "SERVER-TSEL") {
    }

    bool operator()() {
        // io_service.run(); 
        while (!terminated_) {
            {
                THD_EXCLUSIVE_LOCK(mtx)
                if (msg.size()) {
                    io_service.reset();
                    client_.write(msg);
                    io_service.run();
                    msg = "";
                }
            }
            boost::xtime xt_loop;
            dvnci::addmillisec_to_now(xt_loop, 100);
            boost::thread::sleep(xt_loop);
        }
        //io_service.stop();
        client_.release();
        return true;
    }

    void set(const std::string & ms) {
        THD_EXCLUSIVE_LOCK(mtx)
        msg = ms;
    }

    void terminate() {
        terminated_ = true;
    }

private:
    bool terminated_;
    boost::asio::io_service& io_service;
    rfc1006::resolver resolver;
    rfc1006::resolver::query query;
    rfc1006::resolver::iterator iterator;
    client client_;
    boost::mutex mtx;
    std::string msg;
} ;




typedef callable_shared_ptr< Client >                         client_ptr;

struct IO {

    IO(boost::asio::io_service & serv) : terminated_(false), io_service(serv) {
    }

    bool operator()() {
        io_service.run();
        while (!terminated_) {
            boost::xtime xt_loop;
            dvnci::addmillisec_to_now(xt_loop, 100);
            boost::thread::sleep(xt_loop);
        }
        io_service.stop();
        return true;
    }

    void terminate() {
        terminated_ = true;
    }

private:
    bool terminated_;
    boost::asio::io_service& io_service;

} ;




typedef callable_shared_ptr<IO >                         io_ptr;

int main(int argc, char* argv[]) {

    std::string uuu = "rtrtr";

    /*dvnci::str_vect vectdata;
  
    boost::asio::ip::iec80f3::generate_header_TKPT_DT(uuu, boost::asio::ip::iec80f3::TPDU_SIZE8,vectdata);
  
    for (dvnci::str_vect::const_iterator it=vectdata.begin();it!=vectdata.end();++it){
        std::cout << "test: " << dvnci::binary_block_to_hexsequence_debug(*it) << std::endl;
    }*/


    std::cout << "test: " <<
            dvnci::binary_block_to_hexsequence_debug(boost::asio::ip::iec8073::generate_header_TKPT_ER(1, "ffff")) << std::endl;

    try {
        if (argc == 1) {

            boost::asio::io_service io_service;

            server_ptr ss = server_ptr( new Server(io_service));
            boost::thread serverth = boost::thread(ss);

            io_ptr io = io_ptr(new IO(io_service));
            boost::thread clientio = boost::thread(io);



            std::string quit_in;
            while (true) {
                std::getline(std::cin, quit_in);
                if (quit_in == "q") break;
            }

            ss->terminate();
            serverth.join();

        }

        if (argc == 2) {

            boost::asio::io_service io_service;

            server_ptr ss = server_ptr( new Server(io_service) );
            boost::thread serverth = boost::thread(ss);

            client_ptr cc = client_ptr( new Client(io_service, "localhost") );
            boost::thread clientth = boost::thread(cc);

            io_ptr io = io_ptr(new IO(io_service));
            boost::thread clientio = boost::thread(io);



            std::string quit_in;
            while (true) {
                std::getline(std::cin, quit_in);
                if (quit_in == "q") break;
                cc->set(quit_in);
            }


            ss->terminate();
            serverth.join();

            cc->terminate();
            clientth.join();


        }

        if (argc == 3) {

            boost::asio::io_service io_service;

            client_ptr cc = client_ptr( new Client(io_service, argv[1]) );
            boost::thread clientth = boost::thread(cc);

            io_ptr io = io_ptr(new IO(io_service));
            boost::thread clientio = boost::thread(io);



            std::string quit_in;
            while (true) {
                std::getline(std::cin, quit_in);
                if (quit_in == "q") break;
                cc->set(quit_in);
            }


            cc->terminate();
            clientth.join();


        }

    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

}
