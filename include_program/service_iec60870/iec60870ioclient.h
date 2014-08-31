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
#include <kernel/systemutil.h>
#include <kernel/error.h>
#include <kernel/constdef.h>

#include "iec60870_protocol.h"

namespace dvnci {
    namespace prot80670 {


        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870pm
        /////////////////////////////////////////////////////////////////////////////////////////////////        

        class iec60870pm : public executable {

        public:

            enum PMState {

                connectedCh, started, connected, disconnected
            };

            iec60870pm(std::string hst, std::string prt, timeouttype tmo);

            virtual ~iec60870pm();

            PMState state() const {
                return state_;
            }

            virtual bool operator()();


        private:


            void connect();
            void disconnect();


            void handle_resolve(const boost::system::error_code& err,
                    boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

            void handle_connect(const boost::system::error_code& err,
                    boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

            void handle_request(const boost::system::error_code& error, message_104_ptr req);

            void handle_response(const boost::system::error_code& error, message_104_ptr resp);

            template< typename handler>
            struct req_operation {

                req_operation(handler hnd, boost::asio::ip::tcp::socket& sock, message_104_ptr rq) : hndl(hnd), socket_(sock), req_(rq), headersz_(0), bodysz_(0) {
                }

                void header(const boost::system::error_code& error, std::size_t bytes_transferred) {
                    if (!error) {
                        headersz_ += bytes_transferred;
                        if (headersz_ < req_->header().size())
                            socket_.async_send(boost::asio::buffer(&(req_->header()[0]) + headersz_, req_->header().size() - headersz_),
                                boost::bind(&req_operation::header, this,
                                boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                        else {
                            if (!req_->message().empty())
                                socket_.async_send(boost::asio::buffer(&(req_->message()[0]), req_->message().size()),
                                    boost::bind(&req_operation::body, this,
                                    boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                            else
                                hndl(error, req_);
                        }
                    } else
                        hndl(error, req_);
                }

                void body(const boost::system::error_code& error, std::size_t bytes_transferred) {
                    if (!error) {
                        bodysz_ += bytes_transferred;
                        if (bodysz_ < req_->message().size())
                            socket_.async_send(boost::asio::buffer(&(req_->message()[0]), req_->message().size()),
                                boost::bind(&req_operation::body, this,
                                boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                        else
                            hndl(error, req_);
                    } else
                        hndl(error, req_);
                }


            private:

                handler hndl;
                boost::asio::ip::tcp::socket& socket_;
                message_104_ptr req_;
                std::size_t headersz_;
                std::size_t bodysz_;
            };

            template< typename handler>
            void async_request(handler hnd, message_104_ptr req) {

                typedef req_operation< handler> req_operation_type;

                boost::asio::async_write(socket_, boost::asio::buffer(&(req->header()[0]), req->header().size()),
                        boost::bind(&req_operation_type::header, req_operation_type(hnd, socket_, req),
                        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                io_service_.run();

            }

            template< typename handler>
            struct resp_operation {

                resp_operation(handler hnd, boost::asio::ip::tcp::socket& sock, message_104_ptr rsp) : hndl(hnd), socket_(sock), resp_(rsp), headersz_(0), bodysz_(0) {
                }

                void header(const boost::system::error_code& error, std::size_t bytes_transferred) {
                    if (!error) {
                        headersz_ += bytes_transferred;
                        if (headersz_ < message_104::apci_length)
                            boost::asio::async_read(socket_, boost::asio::buffer(&(resp_->header()[0]) + headersz_, resp_->header().size() - headersz_),
                                boost::bind(&resp_operation::header, this,
                                boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                        else {
                            if (resp_->body_length())
                                boost::asio::async_read(socket_, boost::asio::buffer(&(resp_->header()[0]), resp_->message().size()),
                                    boost::bind(&resp_operation::body, this,
                                    boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                            else
                                hndl(error, resp_);
                        }
                    } else
                        hndl(error, resp_);
                }

                void body(const boost::system::error_code& error, std::size_t bytes_transferred) {
                    if (!error) {
                        bodysz_ += bytes_transferred;
                        if (bodysz_ < resp_->message().size())
                            boost::asio::async_write(socket_, boost::asio::buffer(&(resp_->message()[0]), resp_->message().size()),
                                boost::bind(&resp_operation::body, this,
                                boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                        else
                            hndl(error, resp_);
                    } else
                        hndl(error, resp_);
                }




            private:

                handler hndl;
                boost::asio::ip::tcp::socket& socket_;
                message_104_ptr resp_;
                std::size_t headersz_;
                std::size_t bodysz_;
            };

            template< typename handler>
            void async_response(handler hnd) {

                typedef resp_operation< handler> resp_operation_type;

                message_104_ptr resp(new message_104());
                resp->header_prepare();

                boost::asio::async_read(socket_, boost::asio::buffer(resp->header().data(), resp->header().size()),
                        boost::bind(&resp_operation_type::header, resp_operation_type(hnd, socket_, resp),
                        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
            }


            void handle_timout_expire(const boost::system::error_code& err);



            boost::asio::io_service io_service_;
            boost::asio::ip::tcp::socket socket_;
            boost::asio::deadline_timer tmout_timer;
            std::string host;
            std::string port;
            timeouttype timout;
            volatile PMState state_;
            volatile int error_cod;
            tcpcounter_type tx_;
            tcpcounter_type rx_;
            dataobject_set data_;


        protected:

            bool initialize();

            bool uninitialize();

        };


        typedef boost::shared_ptr<iec60870pm> iec60870pm_ptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870ioclient
        /////////////////////////////////////////////////////////////////////////////////////////////////        

        class iec60870ioclient : public boost::enable_shared_from_this<iec60870ioclient> {

        public:

            iec60870ioclient(std::string host, std::string port, timeouttype tmo = DEFAULT_DVNCI_TIMOUT);

            ~iec60870ioclient() {
            }

            iec60870pm::PMState state() const;



        private:

            callable_shared_ptr<iec60870pm> iooclnt;
            boost::shared_ptr<boost::thread> ioth;
        };


        typedef boost::shared_ptr< iec60870ioclient> iec60870ioclient_ptr;

    }
}


#endif	/* _NS_IOCLIENT_H */

