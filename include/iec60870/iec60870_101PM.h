/* 
 * File:   ns_ioclient.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 17 ???? 2010 ?., 0:05
 */

#ifndef _DVNCI_KRNL_NS_IEC60850_101PM_H
#define	_DVNCI_KRNL_NS_IEC60850_101PM_H

#include <iec60870/iec60870_protocol.h>
#include <boost/asio/serial_port.hpp>

namespace dvnci {
    namespace prot80670 {

        typedef boost::uint16_t tcpcounter_type;



        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// class apdu_101
        /////////////////////////////////////////////////////////////////////////////////////////////////       

        typedef asdu_body<lasz_none, ctsz_double, select_double, ioa_three> asdu_body101;

        const octet_sequence::value_type FC_START101 = '\x68';
        const unum32 HD101_STARTDTact = 0x0003 | 0x0004;
        const unum32 HD101_STARTDTcon = 0x0003 | 0x0008;
        const unum32 HD101_STOPDTact = 0x0003 | 0x0010;
        const unum32 HD101_STOPDTcon = 0x0003 | 0x0020;
        const unum32 HD101_TESTFRact = 0x0003 | 0x0040;
        const unum32 HD101_TESTFRcon = 0x0003 | 0x0080;
        const unum16 HD101_U_IND = 0x01;


        class apdu_101;
        typedef boost::shared_ptr<apdu_101> apdu_101_ptr;

        class apdu_101 {

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
            apdu_101();

            apdu_101(apcitypeU u);

            apdu_101(tcpcounter_type rx);

            apdu_101(tcpcounter_type tx, tcpcounter_type rx, const dataobject& vl, cause_type cs);

            apdu_101(tcpcounter_type tx, tcpcounter_type rx, const asdu_body101& vl);

            ~apdu_101();

            static apdu_101_ptr create();

            static apdu_101_ptr create(apcitypeU u);

            static apdu_101_ptr create(tcpcounter_type rx);

            static apdu_101_ptr create(tcpcounter_type tx, tcpcounter_type rx, const dataobject& vl, cause_type cs);

            static apdu_101_ptr create(tcpcounter_type tx, tcpcounter_type rx, const asdu_body101& vl);

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

            void encode_body(const asdu_body101& vl);

            /*bool decode_header();*/


            octet_sequence_ptr header_;
            octet_sequence_ptr body_;

        };


        typedef std::deque<apdu_101_ptr> apdu_101_deq;
        typedef std::set<apdu_101_ptr> apdu_101_set;





        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870_101PM
        /////////////////////////////////////////////////////////////////////////////////////////////////  

        class iec60870_101PM : public iec60870_PM {

        public:

            iec60870_101PM(chnlnumtype chnm, const metalink & lnk, const iec_option& opt, iec60870_data_listener_ptr listr = iec60870_data_listener_ptr());
            
            virtual  bool operator()();

            virtual void disconnect();

        protected:

            virtual void connect();

            virtual void terminate();

        private:

            void work();

            void handle_request(const boost::system::error_code& error, apdu_101_ptr req);

            void handle_response(const boost::system::error_code& error, apdu_101_ptr resp);

            bool send_S1(const apdu_101_ptr & req, std::size_t tmo);

            apdu_101_ptr request(const apdu_101_ptr & req, std::size_t tmo);

            /*void send(const asdu_body101& asdu);

            void send(apdu_101_ptr msg);

            void send(apdu_101::apcitypeU u);

            void send(tcpcounter_type cnt);

            void receive();

            void check_work_available();

            bool parse_data(apdu_101_ptr resp);*/



            //////// request_operation 

            template< typename handler>
            struct req_operation {

                req_operation(handler hnd, boost::asio::serial_port& sock, apdu_101_ptr rq) : hndl(hnd), serialport_(sock), req_(rq), headersz_(0), bodysz_(0) {
                }

                void header(const boost::system::error_code& error, std::size_t bytes_transferred) {
                    if (!error) {
                        headersz_ += bytes_transferred;
                        if (headersz_ < req_->header().size())
                            serialport_.async_write_some(boost::asio::buffer(&(req_->header()[0]) + headersz_, req_->header().size() - headersz_),
                                boost::bind(&req_operation::header, *this,
                                boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                        else {
                            if (!req_->body().empty())
                                serialport_.async_write_some(boost::asio::buffer(&(req_->body()[0]), req_->body().size()),
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
                            serialport_.async_write_some(boost::asio::buffer(&(req_->body()[0]) + bodysz_, req_->body().size() - bodysz_),
                                boost::bind(&req_operation::body, *this,
                                boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                        else
                            hndl(error, req_);
                    } else
                        hndl(error, req_);
                }


            private:

                handler hndl;
                boost::asio::serial_port& serialport_;
                apdu_101_ptr req_;
                std::size_t headersz_;
                std::size_t bodysz_;
            };

            template< typename handler>
            void async_request(handler hnd, apdu_101_ptr req) {

                typedef req_operation< handler> req_operation_type;

                serialport_.async_write_some(boost::asio::buffer(&(req->header()[0]), req->header().size()),
                        boost::bind(&req_operation_type::header, req_operation_type(hnd, serialport_, req),
                        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));


            }



            //////// response_operation           

            template< typename handler>
            struct resp_operation {

                resp_operation(handler hnd, boost::asio::serial_port& sock, apdu_101_ptr rsp) : hndl(hnd), serialport_(sock), resp_(rsp), headersz_(0), bodysz_(0) {
                }

                void header(const boost::system::error_code& error, std::size_t bytes_transferred) {
                    if (!error) {
                        headersz_ += bytes_transferred;
                        if (headersz_ < apdu_101::apci_length)
                            serialport_.async_read_some(boost::asio::buffer(&(resp_->header()[0]) + headersz_, resp_->header().size() - headersz_),
                                boost::bind(&resp_operation::header, *this,
                                boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                        else {
                            if (resp_->body_length()) {
                                resp_->body_prepare();
                                serialport_.async_read_some(boost::asio::buffer(&(resp_->body()[0]), resp_->body().size()),
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
                            serialport_.async_read_some(boost::asio::buffer(&(resp_->body()[0]) + bodysz_, resp_->body().size() - bodysz_),
                                boost::bind(&resp_operation::body, *this,
                                boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                        else
                            hndl(error, resp_);
                    } else
                        hndl(error, resp_);
                }

            private:

                handler hndl;
                boost::asio::serial_port& serialport_;
                apdu_101_ptr resp_;
                std::size_t headersz_;
                std::size_t bodysz_;
            };

            template< typename handler>
            void async_response(handler hnd) {

                typedef resp_operation< handler> resp_operation_type;

                apdu_101_ptr resp = apdu_101::create();

                serialport_.async_read_some(boost::asio::buffer(resp->header().data(), resp->header().size()),
                        boost::bind(&resp_operation_type::header, resp_operation_type(hnd, serialport_, resp),
                        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
            }

            bool setoption(const iec60870_com_option_setter& opt) {
                try {
                    serialport_.set_option<iec60870_com_option_setter > (opt);
                    return true;
                } catch (...) {
                    return false;
                }
            };



        protected:

            //virtual void insert_device_sevice(device_address dev){};             

            //virtual void remove_device_sevice(device_address dev){};            

            virtual void insert_sector_sevice(device_address dev, selector_address slct);

            //virtual void remove_sector_sevice(device_address dev, selector_address slct){}; 

            //virtual void insert_data_sevice(dataobject_ptr vl){};             

            //virtual void remove_data_sevice(dataobject_ptr vl){};    


        private:


            bool parse_data(apdu_101_ptr resp);


            void set_t0();
            void handle_t0_expire(const boost::system::error_code& err);

            boost::asio::serial_port serialport_;
            boost::asio::serial_port_service serialport_io_sevice;
            boost::asio::deadline_timer req_timer;
            chnlnumtype chnum_;
            iec60870_com_option_setter comsetter_;
            volatile bool terminate_;
            apdu_101_ptr data_ready_;
            volatile bool is_timout;
            volatile bool is_error;
            volatile int error_cod;
            apdu_101_deq sended_;

        };







    }
}


#endif	/* _NS_IOCLIENT_H */

