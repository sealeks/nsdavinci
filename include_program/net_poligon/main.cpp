/*  * File:   main.cpp
 * Author: sealeks@mail.ru
 *
 * Created on 27 Р  Р Р‹Р  Р’ВµР  Р вЂ¦Р РЋРІР‚С™Р РЋР РЏР  Р’В±Р РЋР вЂљР РЋР Р‰ 2012 Р  РЎвЂ“., 15:58
 */

#include <cstdlib>
#include <deque>
#include <iostream>

#define SESSION_PROT

#include <kernel/constdef.h>
#include <kernel/memfile.h>
#include <kernel/systemutil.h>
#include <kernel/serviceapp.h>
#include <kernel/factory.h>
#include <kernel/templ.h>

#if defined(SESSION_PROT)
#include <iso/iso8327.h>
#else
#include <iso/rfc1006.h>
#endif

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include <cstdio>
#include <cstdlib>
#include <cstring>




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
const selector_type  SELECTOR = selector_type("SERVER-SSEL", lowselector_type("SERVER-TSEL", boost::asio::iso::SIZE128));
#else
const selector_type  SELECTOR = selector_type("SERVER-TSEL", boost::asio::iso::SIZE128);
#endif

typedef boost::asio::iso::archive_temp<>    trans_data;
typedef boost::asio::iso::archive_ptr            trans_data_type;


int port = 102;

enum {
    max_length = 100
} ;

//#define NET_BLOCKING

#ifndef NET_BLOCKING

class session {
public:

    session(boost::asio::io_service& io_service, trans_data_type trans = trans_data_type())
    : socket_(io_service, SELECTOR), trans_(trans) {
        std::cout << "New sesion\n";
    }

    socket_type& socket() {
        return socket_;
    }

    void start() {
        if (trans_) {
            std::cout << "Client accept data : " << trans_->respond_str() << std::endl;
        }

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
            std::cout << "Server reade: " <<  std::string(data_, bytes_transferred) <<  " size: " <<  bytes_transferred << std::endl;
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
    trans_data_type trans_;
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
        trans_data_type trans_ = trans_data_type( new   trans_data());

        session* new_session = new session(io_service_, trans_);



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

} ;

class client {
public:

    client(boost::asio::io_service& io_service,
            resolver_type::iterator endpoint_iterator, const std::string& called = "")
    : io_service_(io_service),
    socket_(io_service, SELECTOR) {
        endpoint_type endpoint = *endpoint_iterator;

        trans_ = trans_data_type( new   trans_data(/*"Hello server from test"*/));
        trans_->request_str("Hello server from test");

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
     
        }
    }

    void release() {
        std::cout << "Start release"  << std::endl;
#if defined(PRES_PROT)
        io_service_.reset();
        boost::asio::asyn_releaseconnect(socket_, boost::bind(&client::handle_release, this, boost::asio::placeholders::error));
        io_service_.poll();
#elif defined(SESSION_PROT)
        io_service_.reset();
        trans_ = trans_data_type( new   trans_data());
        socket_.asyn_releaseconnect(boost::bind(&client::handle_release, this, boost::asio::placeholders::error), boost::asio::iso::SESSION_NORMAL_RELEASE, trans_);
        io_service_.poll();
#else
        io_service_.reset();
         trans_ = trans_data_type();
        boost::asio::asyn_releaseconnect(socket_, boost::bind(&client::handle_release, this, boost::asio::placeholders::error));
        io_service_.poll();
#endif           


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
                
#if defined(SESSION_PROT)                
                std::cout << "Server accept data : " << trans_->respond_str() << std::endl;
#else
                std::cout << "Server accept data : " << trans_->respond_str() << std::endl;
#endif                
                
            }
        }
        else if (endpoint_iterator != resolver_type::iterator()) {
            socket_.close();
            endpoint_type endpoint = *endpoint_iterator;

            trans_ = trans_data_type( new   trans_data());
            trans_->request_str("Hello server from test");

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
        if (trans_) {
            std::cout << "Server release data : " << trans_->respond_str() << std::endl;
        }
    }

    void handle_read(const boost::system::error_code& error,
            size_t bytes_transferred) {
        if (!error) {
            std::cout << "Client read:" << std::string(data_, bytes_transferred) <<  " size: " <<  bytes_transferred <<  " is complete: "  <<  socket_.input_empty() << std::endl;
            if (!socket_.input_empty()){
                    std::cout << "Client read continiu" <<  std::endl;                
                    socket_.async_read_some(boost::asio::buffer(data_, max_length),
                    boost::bind(&client::handle_read, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));   
                    
            }
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

    session(boost::asio::io_service& io_service, trans_data_type trans)
    : socket_(io_service, SELECTOR), trans_(trans) {
        std::cout << "New sesion\n";
    }

    socket_type& socket() {
        return socket_;
    }

    void run() {
        if (trans_) 
            std::cout << "Client accept data : " << trans_->respond_str() << std::endl;
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
    trans_data_type trans_;
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
            
            trans_data_type trans_ = trans_data_type( new   trans_data("Hello client from test"));
            
            session* new_session = new session(io_service_, trans_);
            boost::system::error_code ec;
            acceptor_.accept(new_session->socket(),
#if defined(PRES_PROT)
                trans_,
#elif defined(SESSION_PROT)
                trans_,
#else
#endif            
            ec);
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
    socket_(io_service, SELECTOR) {
        
        trans_ = trans_data_type( new   trans_data("Hello server  from test"));        
        
        boost::system::error_code ec;
        endpoint_type endpoint = *endpoint_iterator;
        socket_.connect(endpoint, 
#if defined(PRES_PROT)
                trans_,
#elif defined(SESSION_PROT)
                trans_,
#else
#endif          
        ec);
        if (!ec) {
        if (trans_) 
            std::cout << "Client accept data : " << trans_->respond_str() << std::endl; 
        }
    }

    ~client() {
        if (socket_.is_open()) {
            socket_.close();
        }
    }

    void release() {
#if defined(PRES_PROT)

#elif defined(SESSION_PROT)
                trans_ = trans_data_type( new   trans_data("Goodbuy server  from test"));
                boost::system::error_code ecc;
                socket_.releaseconnect(boost::asio::iso::SESSION_NORMAL_RELEASE, trans_,ecc);
                if (trans_) 
                       std::cout << "Server release data : " << trans_->respond_str() << std::endl;
                
#else
                boost::system::error_code ecc;
                socket_.releaseconnect(ecc); 
#endif  
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
    trans_data_type trans_ ;
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
       // io_service.stop();
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

