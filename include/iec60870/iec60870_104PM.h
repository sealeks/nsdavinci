/* 
 * File:   ns_ioclient.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 17 ???? 2010 ?., 0:05
 */

#ifndef _DVNCI_KRNL_NS_IEC60850_104PM_H
#define	_DVNCI_KRNL_NS_IEC60850_104PM_H

#include <iec60870/iec60870_protocol.h>

namespace dvnci {
    namespace prot80670 {

        typedef boost::uint16_t tcpcounter_type;



        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// class apdu_104
        /////////////////////////////////////////////////////////////////////////////////////////////////       
        
        typedef asdu_body<lasz_none, ctsz_double, select_double, ioa_three> asdu_body104;

        const octet_sequence::value_type FC_START104 = '\x68';
        const unum32 HD104_STARTDTact = 0x0003 | 0x0004;
        const unum32 HD104_STARTDTcon = 0x0003 | 0x0008;
        const unum32 HD104_STOPDTact = 0x0003 | 0x0010;
        const unum32 HD104_STOPDTcon = 0x0003 | 0x0020;
        const unum32 HD104_TESTFRact = 0x0003 | 0x0040;
        const unum32 HD104_TESTFRcon = 0x0003 | 0x0080;
        const unum16 HD104_U_IND = 0x01;

        class apdu_104;
        typedef boost::shared_ptr<apdu_104> apdu_104_ptr;

        class apdu_104 {

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
            apdu_104();

            apdu_104(apcitypeU u);

            apdu_104(tcpcounter_type rx);

            apdu_104(tcpcounter_type tx, tcpcounter_type rx, const dataobject& vl, cause_type cs);

            apdu_104(tcpcounter_type tx, tcpcounter_type rx, const asdu_body104& vl);

            ~apdu_104();

            static apdu_104_ptr create();

            static apdu_104_ptr create(apcitypeU u);

            static apdu_104_ptr create(tcpcounter_type rx);

            static apdu_104_ptr create(tcpcounter_type tx, tcpcounter_type rx, const dataobject& vl, cause_type cs);

            static apdu_104_ptr create(tcpcounter_type tx, tcpcounter_type rx, const asdu_body104& vl);

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

            void encode_header(apcitype tp, apcitypeU tpu, tcpcounter_type tx = 0, tcpcounter_type rx = 0);

            void encode_body(const dataobject& vl, cause_type cs);

            void encode_body(const asdu_body104& vl);

            /*bool decode_header();*/


            octet_sequence_ptr header_;
            octet_sequence_ptr body_;

        };


        typedef std::deque<apdu_104_ptr> apdu_104_deq;
        typedef std::set<apdu_104_ptr> apdu_104_set;





        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870_104PM
        /////////////////////////////////////////////////////////////////////////////////////////////////  

        const std::size_t PM_104_T0d = 30;
        const std::size_t PM_104_T1d = 15;
        const std::size_t PM_104_T2d = 10;
        const std::size_t PM_104_T3d = 20;

        const tcpcounter_type PM_104_K = 12;
        const tcpcounter_type PM_104_W = 8;
        const tcpcounter_type PM_104_MODULO = 0x8000;

        BOOST_STATIC_ASSERT(sizeof (tcpcounter_type) == 2);
        BOOST_STATIC_ASSERT(!std::numeric_limits<tcpcounter_type>::is_signed);

        class iec60870_104PM : public iec60870_PM {

        public:

            iec60870_104PM(const std::string& hst, const std::string& prt, const iec_option& opt, iec60870_data_listener_ptr listr = iec60870_data_listener_ptr());

            virtual void disconnect();

        protected:

            virtual void connect();

            virtual void terminate();

        private:

            void handle_resolve(const boost::system::error_code& err,
                    boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

            void handle_connect(const boost::system::error_code& err,
                    boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

            void handle_request(const boost::system::error_code& error, apdu_104_ptr req);

            void handle_response(const boost::system::error_code& error, apdu_104_ptr resp);

            void handle_short_timout_expire(const boost::system::error_code& err);




            void send(const asdu_body104& asdu);

            void send(apdu_104_ptr msg);

            void send(apdu_104::apcitypeU u);

            void send(tcpcounter_type cnt);

            void receive();

            void short_wait();

            void check_work_available();



            void ack_tx(tcpcounter_type vl);

            void set_rx(tcpcounter_type vl);

            bool parse_response(apdu_104_ptr resp);

            bool parse_data(apdu_104_ptr resp);

            bool parse_U(apdu_104_ptr resp);



            //////// request_operation 

            template< typename handler>
            struct req_operation {

                req_operation(handler hnd, boost::asio::ip::tcp::socket& sock, apdu_104_ptr rq) : hndl(hnd), socket_(sock), req_(rq), headersz_(0), bodysz_(0) {
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
                            socket_.async_send(boost::asio::buffer(&(req_->body()[0]) + bodysz_, req_->body().size() - bodysz_),
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
                apdu_104_ptr req_;
                std::size_t headersz_;
                std::size_t bodysz_;
            };

            template< typename handler>
            void async_request(handler hnd, apdu_104_ptr req) {

                typedef req_operation< handler> req_operation_type;

                socket_.async_send(boost::asio::buffer(&(req->header()[0]), req->header().size()),
                        boost::bind(&req_operation_type::header, req_operation_type(hnd, socket_, req),
                        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));


            }



            //////// response_operation           

            template< typename handler>
            struct resp_operation {

                resp_operation(handler hnd, boost::asio::ip::tcp::socket& sock, apdu_104_ptr rsp) : hndl(hnd), socket_(sock), resp_(rsp), headersz_(0), bodysz_(0) {
                }

                void header(const boost::system::error_code& error, std::size_t bytes_transferred) {
                    if (!error) {
                        headersz_ += bytes_transferred;
                        if (headersz_ < apdu_104::apci_length)
                            socket_.async_receive(boost::asio::buffer(&(resp_->header()[0]) + headersz_, resp_->header().size() - headersz_),
                                boost::bind(&resp_operation::header, *this,
                                boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                        else {
                            if (resp_->body_length()) {
                                resp_->body_prepare();
                                socket_.async_receive(boost::asio::buffer(&(resp_->body()[0]), resp_->body().size()),
                                        boost::bind(&resp_operation::body, *this,
                                        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                            } else
                                hndl(error, resp_);
                        }
                    } else
                        hndl(error, resp_);
                }

                void body(const boost::system::error_code& error, std::size_t bytes_transferred) {
                    if (!error) {
                        bodysz_ += bytes_transferred;
                        if (bodysz_ < resp_->body().size())
                            socket_.async_receive(boost::asio::buffer(&(resp_->body()[0]) + bodysz_, resp_->body().size() - bodysz_),
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
                apdu_104_ptr resp_;
                std::size_t headersz_;
                std::size_t bodysz_;
            };

            template< typename handler>
            void async_response(handler hnd) {

                typedef resp_operation< handler> resp_operation_type;

                apdu_104_ptr resp = apdu_104::create();

                socket_.async_receive(boost::asio::buffer(resp->header().data(), resp->header().size()),
                        boost::bind(&resp_operation_type::header, resp_operation_type(hnd, socket_, resp),
                        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
            }
            
            
            
        protected:
            
            //virtual void insert_device_sevice(device_address dev){};             
            
            //virtual void remove_device_sevice(device_address dev){};            
            
            virtual void insert_sector_sevice(device_address dev, selector_address slct);             
            
            //virtual void remove_sector_sevice(device_address dev, selector_address slct){}; 
            
            //virtual void insert_data_sevice(dataobject_ptr vl){};             
            
            //virtual void remove_data_sevice(dataobject_ptr vl){};    
            

            boost::asio::io_service io_service_;
            boost::asio::deadline_timer tmout_timer;
            boost::asio::deadline_timer short_timer;            

        private:

            tcpcounter_type w() const {
                return w_;
            }

            bool w_expire() const {
                return w_ >= w_fct;
            }

            tcpcounter_type inc_tx();
            bool in_rx_range(tcpcounter_type inlist_vl, tcpcounter_type confirmed_rx);
            bool k_expire() const;

            void set_t0();
            void cancel_t0();
            void handle_t0_expire(const boost::system::error_code& err);

            void reset_t1();
            void set_t1();
            void cancel_t1();
            void handle_t1_expire(const boost::system::error_code& err);

            void reset_t2();
            void set_t2();
            void cancel_t2();
            void handle_t2_expire(const boost::system::error_code& err);

            void reset_t3();
            void set_t3();
            void cancel_t3();
            void handle_t3_expire(const boost::system::error_code& err);


            boost::asio::ip::tcp::socket socket_;
            boost::asio::deadline_timer t1_timer;
            std::size_t PM_104_T1;
            boost::asio::deadline_timer t2_timer;
            std::size_t PM_104_T2;
            boost::asio::deadline_timer t3_timer;
            std::size_t PM_104_T3;
            bool t0_state;
            bool t1_state;
            bool t1_progress;
            bool t2_state;
            bool t2_progress;
            bool t3_state;
            bool t3_progress;
            std::string host;
            std::string port;
            tcpcounter_type tx_;
            tcpcounter_type rx_;
            tcpcounter_type w_;
            tcpcounter_type k_fct;
            tcpcounter_type w_fct;
            apdu_104_deq sended_;

        };







    }
}


#endif	/* _NS_IOCLIENT_H */

