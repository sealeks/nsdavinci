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


        const octet_sequence::value_type RES_MASK = '\x80';
        const octet_sequence::value_type PRM_MASK = '\x40';
        const octet_sequence::value_type FCB_MASK = '\x20';
        const octet_sequence::value_type FCV_MASK = '\x10';
        const octet_sequence::value_type ACD_MASK = '\x20';
        const octet_sequence::value_type DFC_MASK = '\x10';
        const octet_sequence::value_type FNC_MASK = '\xF';


        //  PRM=1

        const octet_sequence::value_type FNC_SET_CANAL = '\x0'; // S2
        const octet_sequence::value_type FNC_SET_PROCESS = '\x1'; // S2
        const octet_sequence::value_type FNC_TEST_CANAL = '\x2'; // S2
        const octet_sequence::value_type FNC_SEND = '\x3'; // S2
        const octet_sequence::value_type FNC_SEND_S1 = '\x4'; //S1
        const octet_sequence::value_type FNC_SEND_GEN = '\x8'; // S3
        const octet_sequence::value_type FNC_REQ_STATUS = '\x9'; // S3
        const octet_sequence::value_type FNC_REQ_CLS1 = '\xA'; // S3
        const octet_sequence::value_type FNC_REQ_CLS2 = '\xB'; // S3             

        // PRM= 0

        const octet_sequence::value_type FNC_ACK = '\x0'; // conf
        const octet_sequence::value_type FNC_NACK = '\x1'; // conf
        const octet_sequence::value_type FNC_RESP_ENDSEQ = '\x7'; // resp
        const octet_sequence::value_type FNC_RESP_DATA = '\x8'; // resp
        const octet_sequence::value_type FNC_RESP_NODATA = '\x9'; //resp
        const octet_sequence::value_type FNC_RESP_CANAL_STATUS = '\xB'; // resp         
        const octet_sequence::value_type FNC_RESP_CANAL_NOWORK = '\xE'; //resp
        const octet_sequence::value_type FNC_RESP_CANAL_UNAVAIL = '\xF'; // resp  

        class func850 {

        public:

            func850() : vl_(0) {
            }

            explicit func850(octet_sequence::value_type vl) : vl_(vl) {
            }

            explicit func850(bool fcb_, bool fcv_, octet_sequence::value_type vl, bool prm_ = false, bool res_ = false) : vl_(vl & FNC_MASK) {
                fcb(fcb_);
                fcv(fcv_);
                res(res_);
                prm(prm_);
            }

            ~func850() {
            }

            octet_sequence::value_type val() const {
                return vl_;
            }

            void val(octet_sequence::value_type vl) {
                vl_ = vl;
            }

            octet_sequence::value_type fc() const {
                return (vl_ & FNC_MASK);
            }

            void fc(octet_sequence::value_type vl) {
                vl = (vl_ & (~FNC_MASK)) | (vl & FNC_MASK);
            }

            bool res() const {
                return (vl_ & RES_MASK);
            }

            void res(bool vl) {
                if (vl)
                    vl_ |= RES_MASK;
                else
                    vl_ &= (~RES_MASK);
            }

            bool prm() const {
                return (vl_ & PRM_MASK);
            }

            void prm(bool vl) {
                if (vl)
                    vl_ |= PRM_MASK;
                else
                    vl_ &= (~PRM_MASK);
            }

            bool fcb() const {
                return ((vl_ & PRM_MASK) && (vl_ & FCB_MASK));
            }

            void fcb(bool vl) {
                if (vl)
                    vl_ |= FCB_MASK;
                else
                    vl_ &= (~FCB_MASK);
            }

            bool fcv() const {
                return ((vl_ & PRM_MASK) && (vl_ & FCV_MASK));
            }

            void fcv(bool vl) {
                if (vl)
                    vl_ |= FCV_MASK;
                else
                    vl_ &= (~FCV_MASK);
            }

            bool acd() const {
                return (!(vl_ & PRM_MASK) && (vl_ & ACD_MASK));
            }

            void acd(bool vl) {
                if (vl)
                    vl_ |= ACD_MASK;
                else
                    vl_ &= (~ACD_MASK);
            }

            bool dfc() const {
                return (!(vl_ & PRM_MASK) && (vl_ & DFC_MASK));
            }

            void dfc(bool vl) {
                if (vl)
                    vl_ |= DFC_MASK;
                else
                    vl_ &= (~DFC_MASK);
            }

            bool ack() const {
                return ((!prm()) && (!fc()));
            }

            bool nack() const {
                return ((!prm()) && (fc() == FNC_NACK));
            }

            bool data() const {
                return ((!prm()) && (fc() == FNC_RESP_DATA));
            }

            bool nodata() const {
                return ((!prm()) && (fc() == FNC_RESP_NODATA));
            }

            bool status() const {
                return ((!prm()) && (fc() == FNC_RESP_CANAL_STATUS));
            }

            bool nowork() const {
                return ((!prm()) && (fc() == FNC_RESP_CANAL_NOWORK));
            }

            bool unavilable() const {
                return ((!prm()) && (fc() == FNC_RESP_CANAL_UNAVAIL));
            }

        private:
            octet_sequence::value_type vl_;
        };



        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// class apdu_870
        /////////////////////////////////////////////////////////////////////////////////////////////////       

        inline octet_sequence::value_type crc_calculate(const octet_sequence& fst) {
            std::size_t rslt = 0;
            for (octet_sequence::const_iterator it = fst.begin(); it != fst.end(); ++it)
                rslt += (*it);
            return static_cast<octet_sequence::value_type> (rslt % 0x100);
        }

        inline octet_sequence::value_type crc_calculate(const octet_sequence& fst, const octet_sequence& scnd) {
            std::size_t rslt = 0;
            for (octet_sequence::const_iterator it = fst.begin(); it != fst.end(); ++it)
                rslt += (*it);
            for (octet_sequence::const_iterator it = scnd.begin(); it != scnd.end(); ++it)
                rslt += (*it);
            return static_cast<octet_sequence::value_type> (rslt % 0x100);
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

            explicit apdu_870(device_address dev, bool fcb_, bool fcv_, octet_sequence::value_type fc, bool prm_ = true, bool res_ = false) :
            header_(new octet_sequence()), body_(new octet_sequence()) {
                encode_header(FC_START1_F1_2, dev, fcb_, fcv_, fc, prm_, res_);
            }

            explicit apdu_870(const asdu_body_type& asdu_, device_address dev, bool fcb_, bool fcv_, octet_sequence::value_type fc, bool prm_ = true, bool res_ = false) :
            header_(new octet_sequence()), body_(new octet_sequence(asdu_.body())) {
                encode_header(FC_START2_F1_2, dev, fcb_, fcv_, fc, prm_, res_);
            }

            explicit apdu_870(dataobject_ptr obj, device_address dev, bool fcb_, bool fcv_, octet_sequence::value_type fc, bool prm_ = true, bool res_ = false) :
            header_(new octet_sequence()), body_(new octet_sequence(asdu_body_type(obj).body())) {
                encode_header(FC_START2_F1_2, dev, fcb_, fcv_, fc, prm_, res_);
            }

            ~apdu_870() {
            };

            static self_type_ptr create() {
                return self_type_ptr(new self_type());
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

            static self_type_ptr create(const asdu_body_type& asdu_, device_address dev, bool fcb_, bool fcv_, octet_sequence::value_type fc, bool prm_ = true, bool res_ = false) {
                return self_type_ptr(new self_type(asdu_, dev, fcb_, fcv_, fc, prm_, res_));
            }

            static self_type_ptr create(device_address dev, bool fcb_, bool fcv_, octet_sequence::value_type fc, bool prm_ = true, bool res_ = false) {
                return self_type_ptr(new self_type(dev, fcb_, fcv_, fc, prm_, res_));
            }

            static self_type_ptr create(dataobject_ptr obj, device_address dev, bool fcb_, bool fcv_, octet_sequence::value_type fc, bool prm_ = true, bool res_ = false) {
                return self_type_ptr(new self_type(obj, dev, fcb_, fcv_, fc, prm_, res_));
            }

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

            //!! All Sended Message in Header

            octet_sequence& smessage() {
                return *header_;
            }

            const octet_sequence& smessage() const {
                return *header_;
            }

            size_t smessage_length() const {
                return smessage().size();
            }

            size_t header_length() const {
                switch (type()) {
                    case Fx_type: return (2 + lnk_traints::link_size()); // 10h(1) + FC(1) +  Addr(?) 
                    case Vr_type: return (5 + lnk_traints::link_size()); // 68h(1) + L(1) + L(1) +68h(1) +FC(1)) +  Addr(?) 
                    case E5_type: return 1;
                    case A2_type: return 1;
                    default:
                    {
                    }
                }
                return 0;
            }

            std::size_t body_length() const {
                switch (type()) {
                    case Fx_type: return 2; // CRC(1) + 0x16(1) 
                    case Vr_type:
                    {
                        if ((body_->size() > 3) && (body_->operator [](1) == body_->operator [](2))) {
                            std::size_t sz = static_cast<std::size_t> (body_->operator [](1));
                            if (sz > (lnk_traints::link_size() + 1))
                                return (sz - lnk_traints::link_size() + 1); // -2 + 1= +1
                        }
                        break;
                    }
                    default:
                    {
                    }
                }
                return 0;
            }

            bool valid() const {
                if ((header_length() == header().size()) && (body_length() == body().size())) {
                    switch (type()) {
                        case Fx_type: return ((!body().empty()) && (body().back() == FC_END_F1_2)) ? crc_check(): false;
                        case Vr_type:
                        {
                            if ((header().size() > 4) && (header()[0] == header()[3]) && (header()[1] == header()[2]))
                                return ((!body().empty()) && (body().back() == FC_END_F1_2)) ? crc_check() : false;
                            return false;
                        }
                        case E5_type:
                        case A2_type: return true;
                        default:
                        {
                        }
                    }
                }
                return false;
            }

            apcitype type() const {
                if (!header_->empty()) {
                    switch (header_->operator[](0)) {
                        case FC_START1_F1_2: return Fx_type;
                        case FC_START2_F1_2: return Vr_type;
                        case FC_SEQ1: return E5_type;
                        case FC_SEQ2: return A2_type;
                        default:
                        {
                        }
                    }
                }
                return None_type;
            }

            func850 control() const {
                switch (type()) {
                    case Fx_type:
                    {
                        if (header().size() > 1)
                            return func850(header()[1]);
                        break;
                    }
                    case Vr_type:
                    {
                        if (header().size() > 4)
                            return func850(header()[4]);
                        break;
                    }
                    default:
                    {
                    }
                }
                return func850();
            }

            octet_sequence::value_type fc() const {
                return control().fc();
            }

            bool fcb() const {
                return control().fcb();
            }

            bool fcv() const {
                return control().fcv();
            }

            bool acd() const {
                return control().acd();
            }

            bool dfc() const {
                return control().dfc();
            }

            bool ack() const {
                return ((control().ack()) || (type() == E5_type));
            }

            bool nack() const {
                return control().nack();
            }

            bool hasdata() const {
                return control().data();
            }

            bool nodata() const {
                return control().nodata();
            }

            bool status() const {
                return control().status();
            }

            bool nowork() const {
                return control().nowork();
            }

            bool unavilable() const {
                return control().unavilable();
            }

            bool crc_check() const {
                if (body().size() > 1) {
                    octet_sequence::value_type crc = body()[body().size() - 2];
                    switch (type()) {
                        case Fx_type: return (header().size() > 1) ?
                                    crc = crc_calculate(octet_sequence(header().begin() + 1, header().end())) : false;
                        case Vr_type:return (header().size() > 4) ?
                                    crc = crc_calculate(octet_sequence(header().begin() + 4, header().end()),
                                    octet_sequence(body().begin(), body().begin()+(body().size() - 2))) : false;
                        default:
                        {
                        }
                    }
                }
                return false;
            }

            octet_sequence& header_prepare() {
                header().clear();
                header().assign(1, 0);
                return header();
            }

            octet_sequence::size_type header_expand() {
                switch (type()) {
                    case Fx_type:
                    {
                        header().insert(header().end(), 1 + lnk_traints::link_size(), '\x0');
                        return 1;
                    }
                    case Vr_type:
                    {
                        header().insert(header().end(), 4 + lnk_traints::link_size(), '\x0');
                        return 1;
                    }
                    default:
                    {

                    }
                }
                return 0;
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
                if (body_ && (body_->size() > 2)) {
                    body_->erase(body_->begin()+(body_->size() - 2), body_->end());
                    asdu_body_type asdu(body_);
                    return asdu.get(rslt);
                }
                return false;
            }


        private:

            void encode_header(octet_sequence::value_type vl) {
                smessage().clear();
                smessage().push_back(vl);
            }

            void encode_header(octet_sequence::value_type st, device_address dev, bool fcb_, bool fcv_, octet_sequence::value_type vl, bool prm_ = false, bool res_ = false) {
                //smessage().reserve(apci_fixlength()+2);
                smessage().clear();
                smessage().push_back(st);
                if (st == FC_START2_F1_2) {
                    octet_sequence::value_type sz =
                            static_cast<octet_sequence::value_type> (body().size() + 1 + lnk_traints::link_size()); // FC(1) +  Addr(?) +Body();//
                    smessage().push_back(sz);
                    smessage().push_back(sz);
                    smessage().push_back(st);
                }
                octet_sequence::size_type crc_strt = smessage().size();
                smessage().push_back(func850(fcb_, fcv_, vl, prm_, res_).val());
                if (lnk_traints::link_size()) {
                    smessage().insert(header().end(), (const char*) &dev, (const char*) &dev + lnk_traints::link_size());
                }
                body().push_back(crc_calculate(octet_sequence(smessage().begin() + crc_strt, smessage().end()), body()));
                body().push_back(FC_END_F1_2);
                //!! All Sended Message in Header
                smessage().insert(smessage().end(), body().begin(), body().end());
                body().clear();

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
            iec60870_PM(opt, 5000, listr),
            serialport_(io_service_), serialport_io_sevice(io_service_), req_timer(io_service_),
            is_timout(false), is_error(false), reqtmo_(1000), chnum_(chnm), comsetter_(lnk) {
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
                error_cod = boost::system::error_code();
                if (!chnum_) {
                    state_ = disconnected;
                    error_cod = ERR_BADADDRESS;
                }
#if defined(_DVN_WIN_) 
                std::string device = "\\\\.\\COM" + to_str(chnum_);
#elif defined(_DVN_LIN_)
                std::string device = "/dev/ttyS" + to_str(chnum_ - 1);
#endif                

                try {
                    if ((serialport_.open(device, error_cod)) || (!serialport_.is_open())) {
                        state_ = disconnected;
                        return;
                    }
                    try {
                        error_cod = setoption(comsetter_);
                        if (error_cod) {
                            serialport_.close();
                            state_ = disconnected;
                        }
                    } catch (boost::system::system_error err) {
                        serialport_.close();
                        state_ = disconnected;
                        error_cod = err.code();
                    }
                } catch (boost::system::system_error err) {
                    state_ = disconnected;
                    error_cod = err.code();
                } catch (...) {
                    state_ = disconnected;
                }
                if (!error_cod) {
                    state_ = connected;
                    pmstate_ = activated;
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
                update_model();
                for (id_device_map::iterator dit = devices().begin(); dit != devices().end(); ++dit) {
                    if (dit->second->state() == iec60870_device::d_disconnect) {
                        if (open_device(dit->second->address(), dit->second->trycount())) {
                            dit->second->state(iec60870_device::d_connected);
                        } else
                            dit->second->dec_trycount();
                        if (terminate_)
                            return;
                        if (dit->second->state() == iec60870_device::d_disconnect)
                            continue;
                    }
                    for (id_selestor_map::iterator sit = dit->second->sectors().begin(); sit != dit->second->sectors().end(); ++sit) {
                        if (sit->second->state() == iec60870_sector::s_noaciveted) {
                            if (init_selector(dit->second->address(), sit->second->selector(), dit->second->fcb(), 3))
                                sit->second->state(iec60870_sector::s_activate);
                            else
                                continue;
                        }
                        if (sit->second->state() == iec60870_sector::s_activate) {
                            apdu_ptr rslt = req_selectorCLS2(dit->second->address(), dit->second->fcb(), 3);
                            if (rslt) {
                                sit->second->state(iec60870_sector::s_confirmactivated);
                            } else
                                continue;
                        }
                        if (sit->second->state() == iec60870_sector::s_confirmactivated) {
                            apdu_ptr rslt;
                            do {
                                rslt = req_selectorCLS1(dit->second->address(), dit->second->fcb(), 3);
                            } while (rslt && (rslt->acd()));
                            if (!rslt)
                                continue;
                            sit->second->state(iec60870_sector::s_fullactivated);
                        }
                    }
                }
            }

            bool send_S1(octet_sequence::value_type fc, device_address dev, std::size_t ret = 1, bool prm_ = true, bool res_ = false) {
                return send_S1(apdu_type::create(dev, false, false, fc, prm_, res_), ret);
            }

            bool send_S1(apdu_ptr req, std::size_t ret = 1) {
                ret &= 0xF;
                ret = ret ? ret : 1;
                while (ret--) {
                    if (request(req))
                        return true;
                    return false;
                }
            }

            bool send_S2(octet_sequence::value_type fc, device_address dev, std::size_t ret = 1, bool fcb_ = false, bool fcv_ = false, bool prm_ = true, bool res_ = false) {
                return send_S2(apdu_type::create(dev, fcb_, fcv_, fc, prm_, res_), ret);
            }

            bool send_S2(apdu_ptr req, std::size_t ret = 1) {
                ret &= 0xF;
                ret = ret ? ret : 1;
                while (ret--) {
                    if (request(req)) {
                        boost::system::error_code err;
                        apdu_ptr resp = response(err);
                        if (!err && resp && (resp->valid())) {
                            return resp->ack();
                        }
                    }
                }
                return false;
            }

            apdu_ptr request_S3(octet_sequence::value_type fc, device_address dev, std::size_t ret = 1, bool fcb_ = false, bool fcv_ = false, bool prm_ = true, bool res_ = false) {
                return request_S3(apdu_type::create(dev, fcb_, fcv_, fc, prm_, res_), ret);
            }

            apdu_ptr request_S3(apdu_ptr req, std::size_t ret = 1) {
                ret &= 0xF;
                ret = ret ? ret : 1;
                while (ret--) {
                    if (request(req)) {
                        boost::system::error_code err;
                        apdu_ptr resp = response(err);
                        if (!err && resp && (resp->valid())) {
                            return data_ready_;
                        }
                    }
                }
                return apdu_ptr();
            }

        private:

            bool open_device(device_address dev, std::size_t ret = 1) {

                apdu_ptr rslt = request_S3(FNC_REQ_STATUS, dev, ret);
                if (rslt && (rslt->status()) && (!rslt->dfc())) {
                    if (send_S2(FNC_SET_CANAL, dev, ret))
                        //if (send_S2(apdu_type::create(dataobject::create_activation_1(dev, 1), dev, true, true, FNC_SEND)))
                        return true;
                }
                return false;
            }

            bool init_selector(device_address dev, selector_address sel, bool fcb, std::size_t ret = 1) {
                if (send_S2(apdu_type::create(dataobject::create_activation_1(dev, sel), dev, fcb, true, FNC_SEND)))
                    return true;
                return false;
            }

            apdu_ptr req_selectorCLS1(device_address dev, bool fcb, std::size_t ret = 1) {
                return request_S3(FNC_REQ_CLS1, dev, ret, fcb, true);
            }

            apdu_ptr req_selectorCLS2(device_address dev, bool fcb, std::size_t ret = 1) {
                return request_S3(FNC_REQ_CLS2, dev, ret, fcb, true);
            }

            void handle_request(const boost::system::error_code& err, apdu_ptr req) {
                if (!err) {
                    req_timer.cancel();
                    data_ready_ = req;
                    is_timout = false;
                    error_cod = err;
                    is_error = false;
                    io_service_.stop();
                } else {
                    req_timer.cancel();
                    is_timout = false;
                    data_ready_ = apdu_ptr();
                    error_cod = err;
                    is_error = true;
                    io_service_.stop();
                }
            }

            void handle_response(const boost::system::error_code& err, apdu_ptr resp) {
                if (!err) {
                    req_timer.cancel();
                    data_ready_ = resp;
                    is_timout = false;
                    error_cod = err;
                    is_error = false;
                    io_service_.stop();
                } else {
                    req_timer.cancel();
                    is_timout = false;
                    data_ready_ = apdu_ptr();
                    error_cod = err;
                    is_error = true;
                    io_service_.stop();
                }
            }

            bool request(apdu_ptr req) {

                io_service_.reset();

                clear_var_req();

                async_request(
                        boost::bind(&iec60870_101PM::handle_request, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred),
                        req);

                set_t_req();

                io_service_.run();

                if (is_error || is_timout)
                    return false;

                return true;
            }

            apdu_ptr response(boost::system::error_code& err) {

                io_service_.reset();

                clear_var_req();

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

                req_operation(handler hnd, boost::asio::serial_port& sock, apdu_ptr rq) : hndl(hnd), serialport_(sock), req_(rq), messagesz_(0) {
                }

                void message(const boost::system::error_code& error, std::size_t bytes_transferred) {
                    if (!error) {
                        messagesz_ += bytes_transferred;
                        if (messagesz_ < req_->smessage_length())
                            serialport_.async_write_some(boost::asio::buffer(&(req_->smessage()[0]) + messagesz_, req_->smessage().size() - messagesz_),
                                boost::bind(&req_operation::message, *this,
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
                std::size_t messagesz_;
            };

            template< typename handler>
            void async_request(handler hnd, apdu_ptr req) {

                typedef req_operation< handler> req_operation_type;

                serialport_.async_write_some(boost::asio::buffer(&(req->smessage()[0]), req->smessage().size()),
                        boost::bind(&req_operation_type::message, req_operation_type(hnd, serialport_, req),
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
                        octet_sequence::size_type cont = resp_->header_expand();
                        if (cont)
                            serialport_.async_read_some(boost::asio::buffer(&(resp_->header()[0]) + headersz_, resp_->header().size() - headersz_),
                                boost::bind(&resp_operation::header_cont, *this,
                                boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                        else {
                            hndl(error, resp_);
                        }
                    } else
                        hndl(error, resp_);
                }

                void header_cont(const boost::system::error_code& error, std::size_t bytes_transferred) {
                    if (!error) {
                        headersz_ += bytes_transferred;
                        if (headersz_ < resp_->header().size())
                            serialport_.async_read_some(boost::asio::buffer(&(resp_->header()[0]) + headersz_, resp_->header().size() - headersz_),
                                boost::bind(&resp_operation::header_cont, *this,
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

            boost::system::error_code setoption(const iec60870_com_option_setter& opt) {
                try {
                    boost::system::error_code err;
                    serialport_.set_option<iec60870_com_option_setter > (opt, err);
                    return err;
                } catch (...) {
                }
                return ERR_BADADDRESS;
            };



        protected:

            //virtual void insert_device_sevice(device_address dev){};             

            //virtual void remove_device_sevice(device_address dev){};            

            virtual void insert_sector_sevice(device_address dev, selector_address slct) {
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

            void clear_var_req() {
                is_timout = false;
                data_ready_ = apdu_ptr();
                error_cod = boost::system::error_code();
                is_error = true;
            }

            void set_t_req() {
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
                    error_cod = ERR_TIMEOUT;
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
            std::size_t reqtmo_;
            apdu_deq sended_;

        };


    }
}


#endif	/* _NS_IOCLIENT_H */

