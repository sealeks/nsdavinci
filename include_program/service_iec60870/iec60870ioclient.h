/* 
 * File:   ns_ioclient.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 17 ���� 2010 �., 0:05
 */

#ifndef _DVNCI_KRNL_NS_IEC60850CLIENT_H
#define	_DVNCI_KRNL_NS_IEC60850CLIENT_H

#include <boost/asio/read_at.hpp>

#include <kernel/utils.h>
#include <kernel/error.h>
#include <kernel/constdef.h>

#include "iec60870_protocol.h"

namespace dvnci {
    namespace prot80670 {

        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870_executable
        /////////////////////////////////////////////////////////////////////////////////////////////////    


        class iec60870ioclient;
        typedef boost::shared_ptr<iec60870ioclient> iec60870ioclient_ptr;

        class iec60870_executable : public executable {

        public:

            enum pmState {

                noinit, activated, deactivated
            };

            iec60870_executable(iec60870ioclient_ptr clnt);

            virtual ~iec60870_executable() {
            }

            pmState state() {
                return state_;
            }

            virtual bool operator()();

            void handle_startdt_act(const boost::system::error_code& err);
            void handle_startdt_conf(message_104_ptr req, const boost::system::error_code& err);

        protected:



            virtual bool initialize();
            virtual bool uninitialize();

            iec60870ioclient_ptr clnt_;
            bool inuse_;
            pmState state_;
        };



        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870ioclient
        /////////////////////////////////////////////////////////////////////////////////////////////////        

        class iec60870ioclient : public boost::enable_shared_from_this<iec60870ioclient> {

            friend class iec60870_executable;

        public:

            enum connectionState {

                connected, disconnected
            };

            iec60870ioclient();

            virtual ~iec60870ioclient();

            connectionState state() {
                return state_;
            }

            void connect(std::string host, std::string port, timeouttype tmo = DEFAULT_DVNCI_TIMOUT);
            void disconnect();

        private:

            void start_thread();
            void stop_thread();


            bool blocked_request(const message_104& msg, message_104& resp);

            bool request(const message_104& msg);


            void handle_resolve(const boost::system::error_code& err,
                    boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

            void handle_connect(const boost::system::error_code& err,
                    boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

            template< typename handler>
            struct req_operation {

                req_operation(handler hnd, boost::asio::ip::tcp::socket& sock, message_104_ptr rq) : hndl(hnd), socket_(sock), req_(rq), headersz_(0), bodysz_(0) {
                }

                void header(const boost::system::error_code& error, std::size_t bytes_transferred) {
                    if (!error) {
                        headersz_ += bytes_transferred;
                        if (headersz_ < req_->header().size())
                            boost::asio::async_write(socket_, boost::asio::buffer(req_->header().c_str() + headersz_, req_->header().size() - headersz_),
                                boost::bind(&req_operation::header, this,
                                boost::asio::placeholders::error));
                        else {
                            if (!req_->message().empty())
                                boost::asio::async_write(socket_, boost::asio::buffer(req_->message().c_str(), req_->message().size()),
                                    boost::bind(&req_operation::body, this,
                                    boost::asio::placeholders::error));
                            else
                                hndl(error);
                        }
                    } else
                        hndl(error);
                }

                void body(const boost::system::error_code& error, std::size_t bytes_transferred) {
                    if (!error) {
                        bodysz_ += bytes_transferred;
                        if (bodysz_ < req_->message().size())
                            boost::asio::async_write(socket_, boost::asio::buffer(req_->message().c_str(), req_->message().size()),
                                boost::bind(&req_operation::body, this,
                                boost::asio::placeholders::error));
                        else
                            hndl(error);
                    } else
                        hndl(error);
                }


            private:

                handler hndl;
                boost::asio::ip::tcp::socket& socket_;
                message_104_ptr req_;
                std::size_t headersz_;
                std::size_t bodysz_;
            };

            template< typename handler>
            void handle_request(handler hnd, message_104_ptr req) {

                typedef req_operation< handler> req_operation_type;

                boost::asio::async_write(socket_, boost::asio::buffer(req->header().c_str(), req->header().size()),
                        boost::bind(&req_operation_type::header, req_operation_type(hnd, socket_, req),
                        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

            }

            template< typename handler>
            struct resp_operation {

                resp_operation(handler hnd, boost::asio::ip::tcp::socket& sock, message_104_ptr rsp) : hndl(hnd), socket_(sock), resp_(rsp), headersz_(0), bodysz_(0) {
                }

                void header(const boost::system::error_code& error, std::size_t bytes_transferred) {
                    if (!error) {
                        headersz_ += bytes_transferred;
                        if (headersz_ < message_104::apci_length)
                            boost::asio::async_read(socket_, boost::asio::buffer(resp_->header().c_str() + headersz_, resp_->header().size() - headersz_),
                                boost::bind(&resp_operation::header, this,
                                boost::asio::placeholders::error));
                        else {
                            if (resp_->body_length())
                                boost::asio::async_read(socket_, boost::asio::buffer(resp_->message().c_str(), resp_->message().size()),
                                    boost::bind(&resp_operation::body, this,
                                    boost::asio::placeholders::error));
                            else
                                hndl(error);
                        }
                    } else
                        hndl(error);
                }

                void body(const boost::system::error_code& error, std::size_t bytes_transferred) {
                    if (!error) {
                        bodysz_ += bytes_transferred;
                        if (bodysz_ < resp_->message().size())
                            boost::asio::async_write(socket_, boost::asio::buffer(resp_->message().c_str(), resp_->message().size()),
                                boost::bind(&resp_operation::body, this,
                                boost::asio::placeholders::error));
                        else
                            hndl(error);
                    } else
                        hndl(error);
                }


            private:

                handler hndl;
                boost::asio::ip::tcp::socket& socket_;
                message_104_ptr resp_;
                std::size_t headersz_;
                std::size_t bodysz_;
            };

            template< typename handler>
            void handle_response(handler hnd, const boost::system::error_code& err) {

                typedef resp_operation< handler> resp_operation_type;

                message_104_ptr resp(new message_104());

                boost::asio::async_read(socket_, boost::asio::buffer(resp->header().c_str(), resp->header().size()),
                        boost::bind(&resp_operation_type::header, resp_operation_type(hnd, socket_, resp),
                        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
            }


            void handle_response(message_104_ptr req, const boost::system::error_code& err);

            void handle_write(const boost::system::error_code& err);

            void handle_readheader(const boost::system::error_code& err);

            void handle_endreq(const boost::system::error_code& err);

            void handle_timout_expire(const boost::system::error_code& err);


            boost::asio::io_service io_service_;
            boost::asio::ip::tcp::socket socket_;
            connectionState state_;
            boost::asio::deadline_timer tmout_timer;
            timeouttype timout;


            message_104 respmsg;
            boost::asio::streambuf response_body;
            boost::array<char, message_104::apci_length > buf;

            volatile bool is_data_ready;
            volatile bool is_timout;
            volatile bool is_connect;
            volatile bool is_error;
            volatile int error_cod;
            tcpcounter_type tx_;
            tcpcounter_type rx_;
            dataobject_set data_;
            executable_ptr executable_;
            boost::shared_ptr<boost::thread> ioth;
        };

    }
}


#endif	/* _NS_IOCLIENT_H */

