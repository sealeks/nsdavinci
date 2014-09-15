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


        const octet_sequence::value_type RES_MASK ='\x80';        
        const octet_sequence::value_type PRM_MASK ='\x40';     
        const octet_sequence::value_type FCB_MASK ='\x20'; 
        const octet_sequence::value_type FCV_MASK ='\x10';        
        const octet_sequence::value_type ACD_MASK ='\x20'; 
        const octet_sequence::value_type DFC_MASK ='\x10';    
        const octet_sequence::value_type FNC_MASK ='\xF';        
        
        
        //  PRM=1
        
        const octet_sequence::value_type FNC_SET_CANAL ='\x1';   // S2
        const octet_sequence::value_type FNC_SET_PROCESS ='\x2';    // S2
        const octet_sequence::value_type FNC_TEST_CANAL ='\x3';    // S2
        const octet_sequence::value_type FNC_SEND_ ='\x4';        // S2
        const octet_sequence::value_type FNC_SEND_S1 ='\x5';    //S1
        const octet_sequence::value_type FNC_SEND_GEN ='\x8';    // S3
        const octet_sequence::value_type FNC_REQ_STATUS ='\x9';      // S3
        const octet_sequence::value_type FNC_REQ_CLS1 ='\xA';    // S3
        const octet_sequence::value_type FNC_REQ_CLS2 ='\xB';   // S3             
        
        // PRM= 0
        
        const octet_sequence::value_type FNC_ACK ='\x0';   // conf
        const octet_sequence::value_type FNC_NACK ='\x1';    // conf
        const octet_sequence::value_type FNC_RESP_ENDSEQ ='\x7';    // resp
        const octet_sequence::value_type FNC_RESP_DATA ='\x8';        // resp
        const octet_sequence::value_type FNC_RESP_NODATA ='\x9';    //resp
        const octet_sequence::value_type FNC_RESP_CANAL_STATUS ='\xB';   // resp         
        const octet_sequence::value_type FNC_RESP_CANAL_NOWORK ='\xE';    //resp
        const octet_sequence::value_type FNC_RESP_CANAL_UNAVAIL ='\xF';   // resp  
        
        class func850{
          
        public:
            
            func850() : vl_(0){}            
            
            explicit func850(octet_sequence::value_type vl) : vl_(vl){}
            
            explicit func850(bool fcb_, bool fcv_, octet_sequence::value_type vl, bool prm_=false, bool res_=false) : vl_(vl_ & FNC_MASK){
                fcb(fcb_);
                fcv(fcv_);  
                res(res_);
                prm(prm_);                 
            }            
            
            ~func850(){}
            
            octet_sequence::value_type val() const{
                return vl_;
            }
            
           void val(octet_sequence::value_type vl){
                vl_=vl;
            }       
           
            octet_sequence::value_type fc() const{
                return (vl_ & FNC_MASK);
            }
            
            void fc(octet_sequence::value_type vl){
                vl = (vl_ & (~FNC_MASK)) | (vl & FNC_MASK);
            }            
            

            bool res() const {
                return (vl_ & RES_MASK);
            }
            
            void res(bool vl) {
                if (vl)
                    vl_|= RES_MASK;
                else
                    vl_&=(~RES_MASK);
            }       
            
            bool prm() const {
                return (vl_ & PRM_MASK);
            }
            
            void prm(bool vl) {
                if (vl)
                    vl_|= PRM_MASK;
                else
                    vl_&=(~PRM_MASK);
            }              
            
            bool fcb() const {
                return (vl_ & FCB_MASK);
            }
            
            void fcb(bool vl) {
                if (vl)
                    vl_|= FCB_MASK;
                else
                    vl_&=(~FCB_MASK);
            }             
            
            bool fcv() const {
                return (vl_ & FCV_MASK);
            }
            
            void fcv(bool vl) {
                if (vl)
                    vl_|= FCV_MASK;
                else
                    vl_&=(~FCV_MASK);
            }        
            
            bool acd() const {
                return (vl_ & ACD_MASK);
            }
            
            void acd(bool vl) {
                if (vl)
                    vl_|= ACD_MASK;
                else
                    vl_&=(~ACD_MASK);
            }             
            
            bool dfc() const {
                return (vl_ & DFC_MASK);
            }
            
            void dfc(bool vl) {
                if (vl)
                    vl_|= DFC_MASK;
                else
                    vl_&=(~DFC_MASK);
            }        
            
            bool ack() const {
                return ((!prm()) && (!fc()));
            }
            
            bool nack() const {
                return ((!prm()) && (fc()==FNC_NACK));
            }    
            
            bool data() const {
                return ((!prm()) && (fc()==FNC_RESP_DATA));
            }
            
            bool nodata() const {
                return ((!prm()) && (fc()==FNC_RESP_NODATA));
            }               
            
            bool status() const {
                return ((!prm()) && (fc()==FNC_RESP_CANAL_STATUS));
            }           
            
            bool nowork() const {
                return ((!prm()) && (fc()==FNC_RESP_CANAL_NOWORK));
            }            
            
            bool unavilable() const {
                return ((!prm()) && (fc()==FNC_RESP_CANAL_UNAVAIL));
            }                 
            
        private:               
            octet_sequence::value_type vl_;
        };



        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// class apdu_870
        /////////////////////////////////////////////////////////////////////////////////////////////////       
        
        inline octet_sequence::value_type crc_calculate(const octet_sequence& fst) {
            std::size_t rslt=0;
            for (octet_sequence::const_iterator it=fst.begin();it!=fst.end();++it)
                rslt+=(*it);
            return static_cast<octet_sequence::value_type>(rslt%0x100);
        }        

        inline octet_sequence::value_type crc_calculate(const octet_sequence& fst, const octet_sequence& scnd) {
            std::size_t rslt=0;
            for (octet_sequence::const_iterator it=fst.begin();it!=fst.end();++it)
                rslt+=(*it);
            for (octet_sequence::const_iterator it=scnd.begin();it!=scnd.end();++it)
                rslt+=(*it);                
            return static_cast<octet_sequence::value_type>(rslt%0x100);
        }
        
        const octet_sequence::value_type FC_START1_F1_2 = '\x10';
        const octet_sequence::value_type FC_START2_F1_2 = '\x68';
        const octet_sequence::value_type FC_END_F1_2 = '\x16';        
        const octet_sequence::value_type FC_SEQ1 = '\xE5';
        const octet_sequence::value_type FC_SEQ2 = '\xA2';       

        //class apdu_870;
        //typedef boost::shared_ptr<apdu_870> apdu_870_ptr;

        template<ADDRESS_sizetype LinkAddress, COT_sizetype COT, SECTOR_sizetype Selector, IOA_sizetype IOA>        
        class apdu_870 {

        public:
            
            typedef protocol_traits<COT, Selector, IOA> prot_traints;
            typedef link_traits<LinkAddress> lnk_traints;  
            typedef asdu_body<COT, Selector, IOA> asdu_body_type;
            typedef boost::shared_ptr<asdu_body_type> asdu_body_ptr;    
            typedef apdu_870<LinkAddress, COT, Selector, IOA> self_type;               
            typedef boost::shared_ptr<self_type> self_type_ptr;             

            
            static std::size_t apci_fixlength(){
                return 2 + lnk_traints::link_size();  // 10h(1) + FC (1) + Addr(?);// 
            };

            static std::size_t apci_varlength() {
                return 4 + lnk_traints::link_size(); // 68h(1) + L(1) +  68h(1)  + FC (1) + Addr(?)   //
            };            

            enum apcitype {

                E5_type, A2_type, Fx_type, Vr_type, None_type
            };


            //

            apdu_870() :
            header_(new octet_sequence()), body_(new octet_sequence()) {
                header_prepare();
            }

            explicit apdu_870(octet_sequence::value_type vl) : 
            header_(new octet_sequence()), body_(new octet_sequence()) {
                encode_header(vl);
            }        

             explicit apdu_870(device_address dev, bool fcb_, bool fcv_, octet_sequence::value_type fc, bool prm_=true, bool res_=false) : 
            header_(new octet_sequence()), body_(new octet_sequence()) {
                encode_header(FC_START1_F1_2, dev, fcb_, fcv_, fc, prm_, res_);
            }
             
             explicit apdu_870(const asdu_body_type& asdu_, device_address dev, bool fcb_, bool fcv_, octet_sequence::value_type fc, bool prm_=true, bool res_=false) : 
            header_(new octet_sequence()), body_(new octet_sequence(asdu_.body())) {    
                encode_header(FC_START2_F1_2, dev, fcb_, fcv_, fc, prm_, res_);
            }             

            ~apdu_870(){};

            static self_type_ptr create(){
                return self_type_ptr( new self_type());
            }

            static self_type_ptr create(apcitype u) {
                switch (u) {
                    case E5_type: return self_type_ptr(new self_type(FC_SEQ1));
                    case A2_type: return self_type_ptr(new self_type(FC_SEQ2));
                    default:
                    {
                    }
                }
                return create();
            }
            
            static self_type_ptr create(const asdu_body_type& asdu_, device_address dev, bool fcb_, bool fcv_, octet_sequence::value_type fc, bool prm_=true, bool res_=false) {
                return self_type_ptr(new self_type(asdu_,  dev, fcb_, fcv_, fc, prm_, res_));
            }            
            
            static self_type_ptr create(device_address dev, bool fcb_, bool fcv_, octet_sequence::value_type fc, bool prm_=true, bool res_=false) {
                return self_type_ptr(new self_type(dev, fcb_, fcv_, fc, prm_, res_));
            }                      
            
            octet_sequence&header() {
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
            
            size_t header_length() const {
                switch (type()) {
                    case FC_START1_F1_2: return (2+ lnk_traints::link_size()); // 10h(1) + FC(1) +  Addr(?) 
                    case FC_START2_F1_2: return (5+ lnk_traints::link_size()); // 68h(1) + L(1) + L(1) +68h(1) +FC(1)) +  Addr(?) 
                    case FC_SEQ1: return 1;
                    case FC_SEQ2: return 1;                     
                    default:
                    {
                    }
                }
                return 0;
            }            

            std::size_t body_length() const {
                switch (type()) {
                    case FC_START1_F1_2: return 2; // CRC(1) + 0x16(1) 
                    case FC_START2_F1_2:  {        
                        if ((body_->size()>3) && (*body[1]==*body[2])){
                            std::size_t sz =static_cast<std::size_t > (body[1]);
                            if (sz>(lnk_traints::link_size()+1))
                                return (sz-(lnk_traints::link_size()+1));
                        }
                    }
                    default:
                    {
                    }
                }
                return 0;
            }

            apcitype type() const{
                if (!header_->empty()){
                    switch((*header_)[1]){
                        case FC_START1_F1_2: return Fx_type;
                        case FC_START2_F1_2: return Vr_type;
                        case FC_SEQ1: return E5_type;
                        case FC_SEQ2: return A2_type; 
                        default:{}
                    }
                }
                return None_type;
            }


        octet_sequence& header_prepare() {
            header().clear();
            header().assign(1, 0);
            return header();
        }
        
        octet_sequence& header_expand() {
            header().clear();
            header().assign(1, 0);
            return header();
        }        

        octet_sequence& body_prepare() {
            body().clear();
            if (body_length())
                body().assign(body_length(), 0);
            return body();
        }

           /* bool complete() const {
                return (body_length() == body().size());
            }

            bool valid() const {
                return ((complete()) && (type() != Null_type));
            }*/

        bool get(dataobject_vct& rslt) {
            if (body_ && (body_->size()>2)) {
                body_->erase(body_->begin()+(body_->size()-2),body_->end());
                asdu_body_type asdu(body_);
                return asdu.get(rslt);
            }
            return false;
        }


        private:

            void encode_header(octet_sequence::value_type vl){
                header_->clear();
                header_->push_back(vl);
            }
            
            void encode_header(octet_sequence::value_type st, device_address dev, bool fcb_, bool fcv_, octet_sequence::value_type vl, bool prm_=false, bool res_=false){
                //header_->reserve(apci_fixlength()+2);
                header_->clear();
                header_->push_back(st);
                if (st == FC_START2_F1_2) {
                    octet_sequence::value_type sz =
                            static_cast<octet_sequence::value_type> (body_->size() + 3 + lnk_traints::link_size()); // FC(1) +  Addr(?) +Body() +  CRC(1) + 0x16(1) 
                    header_->push_back(sz);
                    header_->push_back(sz);
                    header_->push_back(st);
                }
                octet_sequence::size_type crc_strt=header_->size();
                header_->push_back(func850(fcb_, fcv_, vl, prm_, res_).val());                           
                if (lnk_traints::link_size()){
                    header_->insert(header().end(), (const char*) &dev, (const char*) &dev + lnk_traints::link_size());
                }
                body_->push_back(crc_calculate(octet_sequence(header_->begin() + crc_strt, header_->end()), body()));
                body_->push_back(FC_END_F1_2);
            }            

            /*bool decode_header();*/

            octet_sequence_ptr header_;
            octet_sequence_ptr body_;

        };






        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870_101PM
        /////////////////////////////////////////////////////////////////////////////////////////////////  

        template<ADDRESS_sizetype LinkAddress, COT_sizetype COT, SECTOR_sizetype Selector, IOA_sizetype IOA>        
        class iec60870_101PM : public iec60870_PM {

        public:
            
            typedef apdu_870<LinkAddress, COT, Selector, IOA> apdu_type;
            typedef boost::shared_ptr<apdu_type> apdu_ptr;  
            typedef std::deque<apdu_ptr> apdu_deq;

            iec60870_101PM(chnlnumtype chnm, const metalink & lnk, const iec_option& opt, iec60870_data_listener_ptr listr = iec60870_data_listener_ptr()) :
            iec60870_PM(opt, listr),
            serialport_(io_service_), serialport_io_sevice(io_service_), req_timer(io_service_),
            is_timout(false), is_error(false), error_cod(0), reqtmo_(1000), chnum_(chnm), comsetter_(lnk) {
            }

            virtual void disconnect() {
                terminate_ = true;
                need_disconnect_ = true;
            };

        protected:

            virtual void connect() {
                DEBUG_STR_DVNCI(ioclient connect)
                DEBUG_VAL_DVNCI(chnum_)
                DEBUG_VAL_DVNCI(timout)
                if (!chnum_) {
                    state_ = disconnected;
                    error_cod = ERROR_IO_CHANNOOPEN;
                }
#if defined(_DVN_WIN_) 
                std::string device = "\\\\.\\COM" + to_str(chnum_);
#elif defined(_DVN_LIN_)
                std::string device = "/dev/ttyS" + to_str(chnum_ - 1);
#endif                

                try {
                    serialport_.open(device);
                    if (!serialport_.is_open()) {
                        state_ = disconnected;
                        error_cod = ERROR_IO_CHANNOOPEN;
                        return;
                    }
                    try {
                        if (!setoption(comsetter_)) {
                            serialport_.close();
                            state_ = disconnected;
                            error_cod = ERROR_IO_CHANNOOPEN;
                        }
                    } catch (boost::system::system_error err) {
                        serialport_.close();
                        state_ = disconnected;
                        error_cod = ERROR_IO_CHANNOOPEN;
                    }
                } catch (boost::system::system_error err) {
                    state_ = disconnected;
                    error_cod = ERROR_IO_CHANNOOPEN;
                } catch (...) {
                    state_ = disconnected;
                    error_cod = ERROR_IO_CHANNOOPEN;
                }
                if (!error_cod) {
                    state_ = connected;
                } else {
                }

            }

            virtual void terminate() {
                terminate_ = true;
                state_ = disconnected;
                serialport_.close();
                io_service_.stop();
            }

            virtual void work() {
                THD_EXCLUSIVE_LOCK(mtx)
                if (!waitrequestdata_.empty()) {
                    apdu_ptr resp = request(apdu_type::create(1, false, false, FNC_SET_CANAL));
                    waitrequestdata_.pop_front();
                }
            }

        private:

            void handle_request(const boost::system::error_code& err, apdu_ptr req) {
                if (!err) {
                    req_timer.cancel();
                    data_ready_ = req;
                    is_timout = false;
                    error_cod = err.value();
                    is_error = false;
                    io_service_.stop();
                } else {
                    req_timer.cancel();
                    is_timout = false;
                    data_ready_ = apdu_ptr();
                    error_cod = err.value();
                    is_error = true;
                    io_service_.stop();
                }
            }

            void handle_response(const boost::system::error_code& err, apdu_ptr resp) {
                if (!err) {
                    req_timer.cancel();
                    data_ready_ = resp;
                    is_timout = false;
                    error_cod = err.value();
                    is_error = false;
                    io_service_.stop();
                } else {
                    req_timer.cancel();
                    is_timout = false;
                    data_ready_ = apdu_ptr();
                    error_cod = err.value();
                    is_error = true;
                    io_service_.stop();
                }
            }

            bool send_S1(apdu_ptr req) {

                io_service_.reset();

                is_timout = false;
                data_ready_ = apdu_ptr();
                error_cod = 0;
                is_error = false;

                async_request(
                        boost::bind(&iec60870_101PM::handle_request, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred),
                        req);

                set_t_req();

                io_service_.run();

                if (is_error || is_timout)
                    return false;

                return true;
            }

            apdu_ptr request(apdu_ptr req) {
                io_service_.reset();

                is_timout = false;
                data_ready_ = apdu_ptr();
                error_cod = 0;
                is_error = true;

                async_request(
                        boost::bind(&iec60870_101PM::handle_request, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred),
                        req);

                set_t_req();

                io_service_.run();

                if (is_error || is_timout)
                    return apdu_ptr();

                io_service_.reset();

                is_timout = false;
                data_ready_ = apdu_ptr();
                error_cod = 0;
                is_error = false;

                async_response(
                        boost::bind(&iec60870_101PM::handle_response, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

                set_t_req();

                io_service_.run();

                if (is_error || is_timout)
                    return apdu_ptr();

                return data_ready_;
            }


            //////// request_operation 

            template< typename handler>
            struct req_operation {

                req_operation(handler hnd, boost::asio::serial_port& sock, apdu_ptr rq) : hndl(hnd), serialport_(sock), req_(rq), headersz_(0), bodysz_(0) {
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
                apdu_ptr req_;
                std::size_t headersz_;
                std::size_t bodysz_;
            };

            template< typename handler>
            void async_request(handler hnd, apdu_ptr req) {

                typedef req_operation< handler> req_operation_type;

                serialport_.async_write_some(boost::asio::buffer(&(req->header()[0]), req->header().size()),
                        boost::bind(&req_operation_type::header, req_operation_type(hnd, serialport_, req),
                        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));


            }



            //////// response_operation           

            template< typename handler>
            struct resp_operation {

                resp_operation(handler hnd, boost::asio::serial_port& sock, apdu_ptr rsp) : hndl(hnd), serialport_(sock), resp_(rsp), headersz_(0), bodysz_(0) {
                }

                void header(const boost::system::error_code& error, std::size_t bytes_transferred) {
                    if (!error) {
                        headersz_ += bytes_transferred;
                        if (headersz_ < apdu_type::apci_length)
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
                apdu_ptr resp_;
                std::size_t headersz_;
                std::size_t bodysz_;
            };

            template< typename handler>
            void async_response(handler hnd) {

                typedef resp_operation< handler> resp_operation_type;

                apdu_ptr resp = apdu_type::create();

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

            virtual void insert_sector_sevice(device_address dev, selector_address slct){
                waitrequestdata_.push_back(dataobject::create_activation_1(0, slct));
            }

            //virtual void remove_sector_sevice(device_address dev, selector_address slct){}; 

            //virtual void insert_data_sevice(dataobject_ptr vl){};             

            //virtual void remove_data_sevice(dataobject_ptr vl){};    


        private:


            bool parse_data(apdu_ptr resp) {
                dataobject_vct rslt;
                if (resp->get(rslt))
                    execute_data(rslt);
                return true;                
            }

            void set_t_req() {
                std::cout << "set t_req" << std::endl;
                req_timer.cancel();
                req_timer.expires_from_now(boost::posix_time::milliseconds(reqtmo_));
                req_timer.async_wait(boost::bind(
                        &iec60870_101PM::handle_t_req_expire, this,
                        boost::asio::placeholders::error));
            }

            void handle_t_req_expire(const boost::system::error_code& err) {
                if (!err) {
                    std::cout << "exp t req" << std::endl;
                    is_timout = true;
                    data_ready_ = apdu_ptr();
                    error_cod = err.value();
                    is_error = true;
                    io_service_.stop();
                } else {
                    //t0_state = false;                
                }
            }

            boost::asio::serial_port serialport_;
            boost::asio::serial_port_service serialport_io_sevice;
            boost::asio::deadline_timer req_timer;
            chnlnumtype chnum_;
            iec60870_com_option_setter comsetter_;
            apdu_ptr data_ready_;
            volatile bool is_timout;
            volatile bool is_error;
            volatile int error_cod;
            std::size_t reqtmo_;
            apdu_deq sended_;

        };







    }
}


#endif	/* _NS_IOCLIENT_H */

