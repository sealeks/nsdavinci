/* 
 * File:   ns_ioclient.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 17 ???? 2010 ?., 0:05
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
        //////// class message_104
        /////////////////////////////////////////////////////////////////////////////////////////////////           

        const octet_sequence::value_type FC_START104 = '\x68';
        const unum32 HD104_STARTDTact = 0x0003 | 0x0004;
        const unum32 HD104_STARTDTcon = 0x0003 | 0x0008;
        const unum32 HD104_STOPDTact = 0x0003 | 0x0010;
        const unum32 HD104_STOPDTcon = 0x0003 | 0x0020;
        const unum32 HD104_TESTFRact = 0x0003 | 0x0040;
        const unum32 HD104_TESTFRcon = 0x0003 | 0x0080;
        const unum16 HD104_U_IND = 0x01;
        
        class message_104;
        typedef boost::shared_ptr<message_104> message_104_ptr;        

        class message_104 {

        public:

            enum {

                apci_length = 6
            };

            enum apcitype {

                Null_type, S_type, U_type, I_type
            };

            enum apcitypeU {

                NULLu, TESTFRact, TESTFRcon, STARTDTact, STARTDTcon, STOPDTact, STOPDTcon
            };

            //
            message_104();

            message_104(apcitypeU u);

            message_104(tcpcounter_type rx);

            message_104(tcpcounter_type tx, tcpcounter_type rx, const dataobject& vl, cause_type cs);
            
            message_104(tcpcounter_type tx, tcpcounter_type rx, const asdu_body& vl);

            ~message_104();            
            
            static message_104_ptr create();

            static message_104_ptr create(apcitypeU u);

            static message_104_ptr create(tcpcounter_type rx);

            static message_104_ptr create(tcpcounter_type tx, tcpcounter_type rx, const dataobject& vl, cause_type cs);   
            
            static message_104_ptr create(tcpcounter_type tx, tcpcounter_type rx, const asdu_body& vl);              
            
            octet_sequence& header() {
                return *header_;
            }            

            octet_sequence& body() {
                return *body_;
            }
            
            const octet_sequence& header() const {
                return *header_;
            }            

            const octet_sequence& body() const {
                return *body_;
            }            


            void body(const boost::asio::streambuf& vl);

            size_t body_length() const;

            apcitype type() const;

            apcitypeU typeU() const;
            
            tcpcounter_type tx() const;            
            
            tcpcounter_type rx() const;     
            
            octet_sequence& header_prepare();
            
            octet_sequence& body_prepare();            


            bool complete() const {
                return (body_length() == body().size());
            }

            bool valid() const {
                return ((complete()) && (type() != Null_type));
            }

            bool countered() const {
                apcitype tmp = type();
                return ((tmp != U_type) && (tmp != Null_type));
            }
            
            bool get(dataobject_vct& rslt);


        private:

            void encode_header(apcitype tp, apcitypeU tpu, tcpcounter_type tx=0, tcpcounter_type rx=0);

            void encode_body(const dataobject& vl, cause_type cs);
            
            void encode_body(const asdu_body& vl);            

            /*bool decode_header();*/


            octet_sequence_ptr header_;            
            octet_sequence_ptr body_;

        };


        typedef std::deque<message_104_ptr> message_104_deq;
        typedef std::set<message_104_ptr> message_104_set;        


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
                                boost::bind(&req_operation::header, *this,
                                boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                        else {
                            if (!req_->body().empty())
                                socket_.async_send(boost::asio::buffer(&(req_->body()[0]), req_->body().size()),
                                    boost::bind(&req_operation::body, *this,
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
                        if (bodysz_ < req_->body().size())
                            socket_.async_send(boost::asio::buffer(&(req_->body()[0]) + bodysz_, req_->body().size()-bodysz_),
                                boost::bind(&req_operation::body, *this,
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

                socket_.async_send(boost::asio::buffer(&(req->header()[0]), req->header().size()),
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
                             socket_.async_receive( boost::asio::buffer(&(resp_->header()[0]) + headersz_, resp_->header().size() - headersz_),
                                boost::bind(&resp_operation::header, *this,
                                boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                        else {
                            if (resp_->body_length()){
                                resp_->body_prepare();
                                 socket_.async_receive( boost::asio::buffer(&(resp_->body()[0]), resp_->body().size()),
                                    boost::bind(&resp_operation::body, *this,
                                    boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));}
                            else
                                hndl(error, resp_);
                        }
                    } else
                        hndl(error, resp_);
                }

                void body(const boost::system::error_code& error, std::size_t bytes_transferred) {
                    if (!error) {
                        bodysz_ += bytes_transferred;
                        if (bodysz_ < resp_->body().size())
                             socket_.async_receive( boost::asio::buffer(&(resp_->body()[0]) + bodysz_, resp_->body().size() - bodysz_),
                                boost::bind(&resp_operation::body, *this,
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
                
                message_104_ptr resp=message_104::create();

                socket_.async_receive( boost::asio::buffer(resp->header().data(), resp->header().size()),
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

