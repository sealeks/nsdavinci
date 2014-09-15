
#include <deque>

#include "iec60870_101PM.h"


namespace dvnci {
    namespace prot80670 {


        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// class apdu_101
        /////////////////////////////////////////////////////////////////////////////////////////////////              

        apdu_101::apdu_101() :
        header_(new octet_sequence()), body_(new octet_sequence()) {
            header_prepare();
        }

        apdu_101::apdu_101(apcitypeU u) :
        header_(new octet_sequence()), body_(new octet_sequence()) {
            encode_header(U_type, u);
        }

        apdu_101::apdu_101(tcpcounter_type rx) :
        header_(new octet_sequence()), body_(new octet_sequence()) {
            encode_header(S_type, NULLu, 0, rx);
        }

        apdu_101::apdu_101(tcpcounter_type tx, tcpcounter_type rx, const dataobject& vl, cause_type cs) :
        header_(new octet_sequence()), body_(new octet_sequence()) {
            encode_body(vl, cs);
            encode_header(I_type, NULLu, tx, rx);
        }

        apdu_101::apdu_101(tcpcounter_type tx, tcpcounter_type rx, const asdu_body101& vl) :
        header_(new octet_sequence()), body_(new octet_sequence()) {
            encode_body(vl);
            encode_header(I_type, NULLu, tx, rx);
        }

        apdu_101::~apdu_101() {
        }

        apdu_101_ptr apdu_101::create() {
            return apdu_101_ptr(new apdu_101());
        }

        apdu_101_ptr apdu_101::create(apcitypeU u) {
            return apdu_101_ptr(new apdu_101(u));
        }

        apdu_101_ptr apdu_101::create(tcpcounter_type rx) {
            return apdu_101_ptr(new apdu_101(rx));
        }

        apdu_101_ptr apdu_101::create(tcpcounter_type tx, tcpcounter_type rx, const dataobject& vl, cause_type cs) {
            return apdu_101_ptr(new apdu_101(tx, rx, vl, cs));
        }

        apdu_101_ptr apdu_101::create(tcpcounter_type tx, tcpcounter_type rx, const asdu_body101& vl) {
            return apdu_101_ptr(new apdu_101(tx, rx, vl));
        }

        size_t apdu_101::body_length() const {
            size_t bl = 0;
            if (header().size() == apci_length) {
                if (header()[0] == FC_START101) {
                    bl = static_cast<size_t> (*((unum8*) & header()[1]));
                    if (bl >= 4) {
                        bl -= 4;
                        return bl;
                    }
                }
            }
            return 0;
        }

        apdu_101::apcitype apdu_101::type() const {
            if (header().size() < apci_length)
                return Null_type;
            octet_sequence::value_type mk = header()[2];
            if (!(header()[2]&1))
                return I_type;
            else if ((header()[2]&3) == 3)
                return U_type;
            return S_type;
        }

        apdu_101::apcitypeU apdu_101::typeU() const {
            if (header().size() < apci_length)
                return NULLu;
            octet_sequence::value_type mk = header()[2];
            if (mk & 3) {
                switch (0x3F & ((mk & 0xFC) >> 2)) {
                    case 1: return STARTDTact;
                    case 2: return STARTDTcon;
                    case 4: return STOPDTact;
                    case 8: return STOPDTcon;
                    case 16: return TESTFRact;
                    case 32: return TESTFRcon;
                    default:
                    {
                    }
                }
            }
            return NULLu;
        }

        tcpcounter_type apdu_101::tx() const {
            if (header().size() < apci_length)
                return 0;
            return (((* reinterpret_cast<const tcpcounter_type*> (&header()[2])) >> 1) & 0x7FFF);
        }

        tcpcounter_type apdu_101::rx() const {
            if (header().size() < apci_length)
                return 0;
            return (((* reinterpret_cast<const tcpcounter_type*> (&header()[4])) >> 1) & 0x7FFF);
        }

        octet_sequence& apdu_101::header_prepare() {
            header().clear();
            header().assign(apci_length, 0);
            return header();
        }

        octet_sequence& apdu_101::body_prepare() {
            body().clear();
            if (body_length())
                body().assign(body_length(), 0);
            return body();
        }

        bool apdu_101::get(dataobject_vct& rslt) {
            if (body_) {
                asdu_body101 asdu(body_);
                return asdu.get(rslt);
            }
            return false;
        }

        void apdu_101::encode_header(apcitype tp, apcitypeU tpu, tcpcounter_type tx, tcpcounter_type rx) {
            header().clear();
            unum8 tmp_length = body().size() + 4;
            header().push_back(FC_START101);
            header().push_back(tmp_length);
            switch (tp) {
                case S_type:
                {
                    unum16 tmprx = (rx << 1) & 0xFFFE;
                    header().insert(header().end(), (const char*) &HD101_U_IND, (const char*) &HD101_U_IND + 2);
                    header().insert(header().end(), (const char*) &tmprx, (const char*) &tmprx + 2);
                    break;
                }
                case U_type:
                {
                    switch (tpu) {
                        case TESTFRact:
                        {
                            header().insert(header().end(), (const char*) &HD101_TESTFRact, (const char*) &HD101_TESTFRact + 4);
                            break;
                        }
                        case TESTFRcon:
                        {
                            header().insert(header().end(), (const char*) &HD101_TESTFRcon, (const char*) &HD101_TESTFRcon + 4);
                            break;
                        }
                        case STARTDTact:
                        {
                            header().insert(header().end(), (const char*) &HD101_STARTDTact, (const char*) &HD101_STARTDTact + 4);
                            break;
                        }
                        case STARTDTcon:
                        {
                            header().insert(header().end(), (const char*) &HD101_STARTDTcon, (const char*) &HD101_STARTDTcon + 4);
                            break;
                        }
                        case STOPDTact:
                        {
                            header().insert(header().end(), (const char*) &HD101_STOPDTact, (const char*) &HD101_STOPDTact + 4);
                            break;
                        }
                        case STOPDTcon:
                        {
                            header().insert(header().end(), (const char*) &HD101_STOPDTcon, (const char*) &HD101_STOPDTcon + 4);
                            break;
                        }
                        default:
                        {

                        }
                    }
                    break;
                }
                case I_type:
                {
                    unum16 tmptx = (tx << 1) & 0xFFFE;
                    unum16 tmprx = (rx << 1) & 0xFFFE;
                    header().insert(header().end(), (const char*) &tmptx, (const char*) &tmptx + 2);
                    header().insert(header().end(), (const char*) &tmprx, (const char*) &tmprx + 2);
                    break;
                }
                default:
                {

                }
            }
        }

        void apdu_101::encode_body(const dataobject& vl, cause_type cs) {
            body().clear();
            type_id tmptype = vl.type();
            body().push_back(tmptype);
            body().insert(body().end(), '\x1');
            body().push_back(cs);
            body().insert(body().end(), '\x0');
            device_address tmpdev = vl.devnum();
            body().insert(body().end(), (const char*) &tmpdev, (const char*) &tmpdev + 2);
            data_address tmpaddr = vl.ioa();
            body().insert(body().end(), (const char*) &tmpaddr, (const char*) &tmpaddr + 3);
            body().insert(body().end(), vl.data().begin(), vl.data().end());
        }

        void apdu_101::encode_body(const asdu_body101& vl) {
            body_ = vl.body_ptr();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870_101PM
        /////////////////////////////////////////////////////////////////////////////////////////////////           

        iec60870_101PM::iec60870_101PM(chnlnumtype chnm, const metalink & lnk, const iec_option& opt, iec60870_data_listener_ptr listr) :
        iec60870_PM(opt, listr),
        serialport_(io_service_), serialport_io_sevice(io_service_), req_timer(io_service_),
        is_timout(false), is_error(false), error_cod(0), reqtmo_(1000), chnum_(chnm), comsetter_(lnk) {
        }

        void iec60870_101PM::connect() {
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

        void iec60870_101PM::work() {
            THD_EXCLUSIVE_LOCK(mtx)
            if (!waitrequestdata_.empty()){
                apdu_101_ptr resp =request(apdu_101::create(0));
                waitrequestdata_.pop_front();
            }
        }

        void iec60870_101PM::disconnect() {
            terminate_ = true;
            need_disconnect_ = true;
        }

        void iec60870_101PM::terminate() {
            terminate_ = true;
            state_ = disconnected;
            serialport_.close();
            io_service_.stop();
        }

        void iec60870_101PM::handle_request(const boost::system::error_code& err, apdu_101_ptr req) {
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
                data_ready_ = apdu_101_ptr();
                error_cod = err.value();
                is_error = true;
                io_service_.stop();
            }
        }

        void iec60870_101PM::handle_response(const boost::system::error_code& err, apdu_101_ptr resp) {
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
                data_ready_ = apdu_101_ptr();
                error_cod = err.value();
                is_error = true;
                io_service_.stop();
            }
        }

        bool iec60870_101PM::send_S1(apdu_101_ptr req) {

            io_service_.reset();

            is_timout = false;
            data_ready_ = apdu_101_ptr();
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

        apdu_101_ptr iec60870_101PM::request(apdu_101_ptr req) {

            io_service_.reset();

            is_timout = false;
            data_ready_ = apdu_101_ptr();
            error_cod = 0;
            is_error = true;

            async_request(
                    boost::bind(&iec60870_101PM::handle_request, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred),
                    req);

            set_t_req();

            io_service_.run();

            if (is_error || is_timout)
                return apdu_101_ptr();

            io_service_.reset();

            is_timout = false;
            data_ready_ = apdu_101_ptr();
            error_cod = 0;
            is_error = false;

            async_response(
                    boost::bind(&iec60870_101PM::handle_response, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

            set_t_req();

            io_service_.run();

            if (is_error || is_timout)
                return apdu_101_ptr();

            return data_ready_;

        }



        /* void iec60870_101PM::check_work_available() {
           if (need_disconnect_) {
                if (pmstate() != todisconnect) {
                    pmstate(todisconnect);
                    send(apdu_101::STOPDTact);
                    receive();
                }
                return;
            }
            if (w_expire()) {
                w_ = 0;
                send(rx_ + 1);
                return;
            }
            if (t2_state) {
                t2_state = false;
                w_ = 0;
                send(rx_ + 1);
                return;
            }
            if (alse) {
                receive();
                return;
            }
            if (t3_state) {
                t3_state = false;
                send(apdu_101::TESTFRact);
                return;
            }
            {
                if (!k_expire()) {
                    THD_EXCLUSIVE_LOCK(mtx)
                    if (!waitrequestdata_.empty()) {
                        send(asdu_body101::create(waitrequestdata_.front()));
                        waitrequestdata_.pop_front();
                        return;
                    }
                }
            }
            set_t3();
            short_wait();
        }*/

        /*bool iec60870_101PM::parse_response(apdu_101_ptr resp) {
          if (resp) {
               cancel_t1();
               reset_t3();
               switch (resp->type()) {
                   case apdu_101::S_type:
                   {
                       ack_tx(resp->rx());
                       break;
                   }
                   case apdu_101::U_type:
                   {
                       if (parse_U(resp))
                           return true;
                       break;
                   }
                   case apdu_101::I_type:
                   {
                       reset_t2();
                       parse_data(resp);
                       w_++;
                       break;
                   }
                   default:
                   {
                   }
               }
               check_work_available();
               return true;
           }
           return false;
       }*/



        bool iec60870_101PM::parse_data(apdu_101_ptr resp) {
            dataobject_vct rslt;
            if (resp->get(rslt))
                execute_data(rslt);
            return true;
        }

        void iec60870_101PM::insert_sector_sevice(device_address dev, selector_address slct) {
            waitrequestdata_.push_back(dataobject::create_activation_1(0, slct));
        }

        void iec60870_101PM::set_t_req() {
            std::cout << "set t_req" << std::endl;
            req_timer.cancel();
            req_timer.expires_from_now(boost::posix_time::milliseconds(reqtmo_));
            req_timer.async_wait(boost::bind(
                    &iec60870_101PM::handle_t_req_expire, this,
                    boost::asio::placeholders::error));
        }

        void iec60870_101PM::handle_t_req_expire(const boost::system::error_code& err) {
            if (!err) {
                std::cout << "exp t req" << std::endl;
                is_timout = true;
                data_ready_ = apdu_101_ptr();
                error_cod = err.value();
                is_error = true;
                io_service_.stop();
            } else {
                //t0_state = false;
            }
        }

    }
}


