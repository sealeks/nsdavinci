/* 
 * File:   main.cpp
 * Author: sealeks@mail.ru
 *
 * Created on 27 Р РЋР ВµР Р…РЎвЂљРЎРЏР В±РЎР‚РЎРЉ 2012 Р С–., 15:58
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

#include <iso/rfc1006.h>
#include <iso/iso8327.h>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#define SESSION_PROT

#if defined(PRES_PROT)

#elif defined(SESSION_PROT)
using boost::asio::iso::iso8327;
typedef boost::asio::iso::iso8327                                        protocol_type;
#else
using boost::asio::iso::rfc1006;
typedef boost::asio::iso::rfc1006                                       protocol_type;
#endif


typedef protocol_type::selector                                         selector_type;
typedef protocol_type::socket                                            socket_type;
typedef protocol_type::acceptor                                        acceptor_type;
typedef protocol_type::endpoint                                       endpoint_type;
typedef protocol_type::resolver                                         resolver_type;

#if defined(PRES_PROT)

#elif defined(SESSION_PROT)

typedef protocol_type::lowselector                     lowselector_type;
const selector_type  SELECTOR = selector_type("SERVER-SSEL", lowselector_type("SERVER-TSEL",boost::asio::iso::SIZE128));
#else
const selector_type  SELECTOR = selector_type("SERVER-TSEL",boost::asio::iso::SIZE128);
#endif

typedef boost::asio::iso::trans_data_type  trans_data_type;
typedef boost::asio::iso::trans_data            trans_data;


int port = 102;

enum {
    max_length = 10000
} ;

//#define NET_BLOCKING

#ifndef NET_BLOCKING

class session {
public:

    session(boost::asio::io_service& io_service)
    : socket_(io_service, SELECTOR) {
        std::cout << "New sesion\n";
    }

    socket_type& socket() {
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
            std::cout << "Data indication: " <<  socket_.input_empty() << std::endl;

        }
        else {
            delete this;
        }
    }

    socket_type socket_;
    char data_[max_length];
    std::string message;
} ;

class server {
public:

    server(boost::asio::io_service& io_service, short port)
    : io_service_(io_service),
    acceptor_(io_service, endpoint_type(boost::asio::ip::tcp::v4(), port)) {
        start_accept();
    }

private:

    void start_accept() {
        session* new_session = new session(io_service_);
        
        trans_=trans_data_type( new   trans_data("Hellow client from 007"));
        
        acceptor_.async_accept(new_session->socket(),
        
#if defined(PRES_PROT)
 trans_,       
 #elif defined(SESSION_PROT)
trans_,
#else
#endif            
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
    acceptor_type acceptor_;
    trans_data_type trans_;
} ;

class client {
public:

    client(boost::asio::io_service& io_service,
            resolver_type::iterator endpoint_iterator, const std::string& called = "")
    : io_service_(io_service),
    socket_(io_service, SELECTOR) {
        endpoint_type endpoint = *endpoint_iterator;
        
        trans_=trans_data_type( new   trans_data("Hellow server from 007"));
        
        socket_.async_connect(endpoint, 
        
#if defined(PRES_PROT)
 trans_,       
 #elif defined(SESSION_PROT)
trans_,
#else
#endif   
        
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
        boost::asio::asyn_releaseconnect(socket_, boost::bind(&client::handle_release, this, boost::asio::placeholders::error));
        io_service_.poll();
    }

    void write(const std::string& msg) {
        message = msg;
        io_service_.post(boost::bind(&client::do_write, this));
    }

    void close() {
        io_service_.post(boost::bind(&client::do_close, this));
    }

private:

    void handle_connect(const boost::system::error_code& error,
            resolver_type::iterator endpoint_iterator) {
        if (!error) {
            if (trans_) {
                        std::cout << "Server accept data : " << trans_->respond_str() << std::endl;}
        }
        else if (endpoint_iterator != resolver_type::iterator()) {
            socket_.close();
            endpoint_type endpoint = *endpoint_iterator;
            
            trans_=trans_data_type( new   trans_data("Hellow server from 007"));
            
            socket_.async_connect(endpoint,
          
#if defined(PRES_PROT)
 trans_,       
 #elif defined(SESSION_PROT)
trans_,
#else
#endif               
                    boost::bind(&client::handle_connect,  this,
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

    void do_write() {
        std::cout << "Client write:" << message <<  " size: " <<  message.size() << std::endl;
        boost::asio::async_write(socket_,
                boost::asio::buffer(message.data(),
                message.size()),
                boost::bind(&client::handle_write, this,
                boost::asio::placeholders::error));

    }

    void handle_write(const boost::system::error_code& error) {
        if (!error) {
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
    socket_type socket_;
    std::string message;
    trans_data_type trans_;
    char data_[max_length];
} ;

#else

class session {
public:

    session(boost::asio::io_service& io_service)
    : socket_(io_service, SELECTOR) {
        std::cout << "New sesion\n";
    }

    socket_type& socket() {
        return socket_;
    }

    void run() {
        boost::system::error_code ec;
        while (!ec) {
            std::size_t bytes_transferred = socket_.read_some(boost::asio::buffer(data_, max_length), ec);
            if (ec) break;
            message = std::string(data_, bytes_transferred);
            std::cout << "Server read: " <<  message <<  " size: " <<  message.size() << std::endl;
            socket_.write_some(boost::asio::buffer(data_, bytes_transferred), ec);
        }
    }

private:


    socket_type socket_;
    char data_[max_length];
    std::string message;
} ;

class server {
public:

    server(boost::asio::io_service& io_service, short port)
    : io_service_(io_service),
    acceptor_(io_service, endpoint_type(boost::asio::ip::tcp::v4(), port)) {
        start_accept();
    }

private:

    void start_accept() {
        while (true) {
            session* new_session = new session(io_service_);
            boost::system::error_code ec;
            acceptor_.accept(new_session->socket(),  ec);
            if (ec)
                delete new_session;
            else
                new_session->run();
        };
    }

    boost::asio::io_service& io_service_;
    acceptor_type acceptor_;
} ;

class client {
public:

    client(boost::asio::io_service& io_service,
            resolver_type::iterator endpoint_iterator, const std::string& called = "")
    : io_service_(io_service),
    socket_(io_service, called) {
        boost::system::error_code ec;
        endpoint_type endpoint = *endpoint_iterator;
        socket_.connect(endpoint, ec);
        if (!ec) {

        }
    }

    ~client() {
        if (socket_.is_open()) {
            socket_.close();
        }
    }

    void release() {
        //io_service_.reset();
        //boost::asio::asyn_releaseconnect(socket_, boost::bind(&client::handle_release, this, boost::asio::placeholders::error));
        //io_service_.poll();
    }

    void write(const std::string& msg) {
        message = msg;
        boost::system::error_code ec;
        socket_.write_some(boost::asio::buffer(message.data(), message.size()), ec);
        std::size_t bytes_transferred = socket_.read_some(boost::asio::buffer(data_, max_length), ec);
        std::cout << "Client read:" << std::string(data_, bytes_transferred) <<  " size: " <<  bytes_transferred << std::endl;

    }

    void close() {
        socket_.close();
    }



private:
    boost::asio::io_service& io_service_;
    socket_type socket_;
    std::string message;
    char data_[max_length];
} ;


#endif


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
    resolver_type resolver;
    resolver_type::query query;
    resolver_type::iterator iterator;
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

    boost::asio::iso::prot8327::spdudata hdrs(boost::asio::iso::prot8327::CN_SPDU_ID);
    hdrs.setPGI(boost::asio::iso::prot8327::PGI_CN_AC, boost::asio::iso::prot8327::PI_PROPT, "\x2");
    hdrs.setPGI(boost::asio::iso::prot8327::PGI_CN_AC, boost::asio::iso::prot8327::PI_VERS, "\x2");
    hdrs.setPI(boost::asio::iso::prot8327::PI_CALLING, "ddddddddddddddddddddd");
    hdrs.setPI(boost::asio::iso::prot8327::PI_CALLED, "ddddddddddddddddddddd");
    hdrs.setPI(boost::asio::iso::prot8327::PI_USERDATA, "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiihhhhhhhhhhhhhhhhhhhhhhhhhh");

    //std::cout << hdrs << std::endl;

    boost::asio::iso::prot8327::spdudata hdrs_test(hdrs.sequence());

    try {
        if (argc < 2) {

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
        else {

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
