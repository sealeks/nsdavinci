
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
        serialport_(io_service_), serialport_io_sevice(io_service_), t1_timer(io_service_), PM_101_T1(opt.t1()),  t2_timer(io_service_), PM_101_T2(opt.t2()), t3_timer(io_service_), PM_101_T3(opt.t3()),
        t0_state(false), t1_state(false), t1_progress(false), t2_state(false), t2_progress(false), t3_state(false),
        chnum_(chnm), comsetter_(lnk), tx_(0), rx_(0), w_(0), k_fct(opt.k()), w_fct(opt.w()) {
        }

        void iec60870_101PM::connect() {
            DEBUG_STR_DVNCI(ioclient connect)
            DEBUG_VAL_DVNCI(chnum_)
            DEBUG_VAL_DVNCI(timout)
            ns_error error_cod = 0;
                if (!chnum_) {
                    state_ = disconnected;
                    error_cod = ERROR_IO_CHANNOOPEN;
                    return;
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
                    }                    catch (boost::system::system_error err) {
                        serialport_.close();
                        state_ = disconnected;
                        error_cod = ERROR_IO_CHANNOOPEN;
                    }
                }                catch (boost::system::system_error err) {
                    state_ = disconnected;
                    error_cod = ERROR_IO_CHANNOOPEN;
                    return;
                }                catch (...) {
                    state_ = disconnected;
                    error_cod = ERROR_IO_CHANNOOPEN;
                    return;
                }
                state_ = connected;
                error_cod = 0;
                return;

            set_t0();

            io_service_.run();

        }

        void iec60870_101PM::disconnect() {
            need_disconnect_ = true;
        }

        void iec60870_101PM::terminate() {
            state_ = disconnected;
            serialport_.close();
            io_service_.stop();
        }

        void iec60870_101PM::handle_resolve(const boost::system::error_code& err,
                boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
            /*if (!err) {
                boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
                serialport_.async_connect(endpoint,
                        boost::bind(&iec60870_101PM::handle_connect, this,
                        boost::asio::placeholders::error, ++endpoint_iterator));
            } else {
                terminate();
            }*/
        }

        void iec60870_101PM::handle_connect(const boost::system::error_code& err,
                boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {

           /* if (!err) {
                tmout_timer.cancel();
                pmstate(noaciveted);
                send(apdu_101::STARTDTact);
            } else
                if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator()) {
                serialport_.close();
                boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
                serialport_.async_connect(endpoint,
                        boost::bind(&iec60870_101PM::handle_connect, this,
                        boost::asio::placeholders::error, ++endpoint_iterator));
            } else {
                terminate();
            }*/
        }

        void iec60870_101PM::handle_request(const boost::system::error_code& error, apdu_101_ptr req) {
            if (!error)
                check_work_available();
            else
                terminate();
        }

        void iec60870_101PM::handle_response(const boost::system::error_code& error, apdu_101_ptr resp) {
            if (!error) {
                parse_response(resp);
            } else
                terminate();
        }

        void iec60870_101PM::handle_short_timout_expire(const boost::system::error_code& err) {
            check_work_available();
        }

        void iec60870_101PM::send(const asdu_body101& asdu) {
            send(apdu_101::create(inc_tx(), rx_, asdu));
        }

        void iec60870_101PM::send(apdu_101_ptr msg) {
            if (msg->type() == apdu_101::I_type)
                sended_.push_back(msg);
            reset_t1();
            reset_t3();
            cancel_t2();
            async_request(
                    boost::bind(&iec60870_101PM::handle_request, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred),
                    msg);
        }

        void iec60870_101PM::send(apdu_101::apcitypeU u) {
            if ((u == apdu_101::STARTDTact) 
                    || (u == apdu_101::STOPDTact) 
                    || (apdu_101::TESTFRact))
                reset_t1();
            reset_t3();
            cancel_t2();
            async_request(
                    boost::bind(&iec60870_101PM::handle_request, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred),
                    apdu_101::create(u));
        }

        void iec60870_101PM::send(tcpcounter_type cnt) {
            cancel_t2();
            reset_t3();
            async_request(
                    boost::bind(&iec60870_101PM::handle_request, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred), apdu_101::create(cnt));
        }

        void iec60870_101PM::receive() {
            async_response(
                    boost::bind(&iec60870_101PM::handle_response, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        }

        void iec60870_101PM::short_wait() {
            short_timer.expires_from_now(boost::posix_time::milliseconds(PM_SHORT_TIMER));
            short_timer.async_wait(boost::bind(
                    &iec60870_101PM::handle_short_timout_expire, this,
                    boost::asio::placeholders::error));
        }

        void iec60870_101PM::check_work_available() {
            if (need_disconnect_) {
                if (pmstate() != todisconnect) {
                    pmstate(todisconnect);
                    send(apdu_101::STOPDTact);
                    receive();
                }
                return;}
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
            if (/*serialport_.available()*/false) {
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
        }

        void iec60870_101PM::set_rx(tcpcounter_type vl) {
            if (((rx_ + 1) % PM_101_MODULO) != vl) {
                set_t1();
            } else
                rx_ = vl;
        }

        void iec60870_101PM::ack_tx(tcpcounter_type vl) {
            if (!sended_.empty()) {
                while ((!sended_.empty()) && (in_rx_range(sended_.front()->tx(), vl)))
                    sended_.pop_front();
            }
        }

        bool iec60870_101PM::parse_response(apdu_101_ptr resp) {
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
        }

        bool iec60870_101PM::parse_U(apdu_101_ptr resp) {
            switch (resp->typeU()) {
                case apdu_101::TESTFRact:
                {
                    send(apdu_101::TESTFRcon);
                    return true;
                }
                case apdu_101::TESTFRcon:
                {
                    return false;
                }
                case apdu_101::STARTDTact:
                {
                    send(apdu_101::STARTDTcon);
                    pmstate(noaciveted);
                    return true;
                }
                case apdu_101::STARTDTcon:
                {
                    state_ = connected;
                    pmstate(activated);
                    return false;
                }
                case apdu_101::STOPDTact:
                {
                    break;
                }
                case apdu_101::STOPDTcon:
                {
                    io_service_.stop();
                    return true;
                }
                default:
                {
                }
            }
            return false;
        }

        bool iec60870_101PM::parse_data(apdu_101_ptr resp) {
            set_rx(resp->tx());
            ack_tx(resp->rx());
            dataobject_vct rslt;
            if (resp->get(rslt)) 
                    execute_data(rslt);
            return true;
        }

        void iec60870_101PM::insert_sector_sevice(device_address dev, selector_address slct) {
            waitrequestdata_.push_back(dataobject::create_activation_1(0,slct));
        }        
        

        tcpcounter_type iec60870_101PM::inc_tx() {
            return (tx_ < PM_101_MODULO) ? (tx_++) : (tx_ = 0);
        }

        bool iec60870_101PM::in_rx_range(tcpcounter_type inlist_vl, tcpcounter_type confirmed_rx) {
            if ((confirmed_rx > k_fct) || (inlist_vl < confirmed_rx))
                return inlist_vl < confirmed_rx;
            else
                return inlist_vl >= (PM_101_MODULO - (k_fct - confirmed_rx));
        }

        bool iec60870_101PM::k_expire() const {
            return sended_.size() >= k_fct;
        }

        void iec60870_101PM::set_t0() {
            std::cout << "set t0 " << std::endl;
            tmout_timer.cancel();
            t0_state = false;
            tmout_timer.expires_from_now(boost::posix_time::milliseconds(timout));
            tmout_timer.async_wait(boost::bind(
                    &iec60870_101PM::handle_t0_expire, this,
                    boost::asio::placeholders::error));
        }

        void iec60870_101PM::cancel_t0() {
            std::cout << "cancel t0" << std::endl;
            tmout_timer.cancel();
        }

        void iec60870_101PM::handle_t0_expire(const boost::system::error_code& err) {
            if (!err) {
                std::cout << "exp t0 = terminate " << std::endl;
                terminate();
            } else {
                t0_state = false;
            }
        }

        void iec60870_101PM::reset_t1() {
            t1_timer.cancel();
            t1_state = false;
            t1_progress = true;
            t1_timer.expires_from_now(boost::posix_time::seconds(PM_101_T1));
            t1_timer.async_wait(boost::bind(
                    &iec60870_101PM::handle_t1_expire, this,
                    boost::asio::placeholders::error));
        }

        void iec60870_101PM::set_t1() {
            if (!t1_progress)
                reset_t1();
        }

        void iec60870_101PM::cancel_t1() {
            t1_timer.cancel();
            t1_progress = false;
        }

        void iec60870_101PM::handle_t1_expire(const boost::system::error_code& err) {
            if (!err) {
                std::cout << "exp t1  = terminate" << std::endl;
                terminate();
            } else {
                t1_state = false;
            }
        }

        void iec60870_101PM::reset_t2() {
            t2_timer.cancel();
            t2_state = false;
            t2_progress = true;
            t2_timer.expires_from_now(boost::posix_time::seconds(PM_101_T2));
            t2_timer.async_wait(boost::bind(
                    &iec60870_101PM::handle_t2_expire, this,
                    boost::asio::placeholders::error));
        }

        void iec60870_101PM::set_t2() {
            if (!t2_progress)
                reset_t2();
        }

        void iec60870_101PM::cancel_t2() {
            t2_timer.cancel();
            t2_progress = false;
        }

        void iec60870_101PM::handle_t2_expire(const boost::system::error_code& err) {
            if (!err) {
                std::cout << "exp t2 " << std::endl;
                t2_state = true;
                t2_progress = false;
            } else {
                t2_state = false;
            }
        }

        void iec60870_101PM::reset_t3() {
            t3_timer.cancel();
            t3_state = false;
            t3_progress = true;
            t3_timer.expires_from_now(boost::posix_time::seconds(PM_101_T3));
            t3_timer.async_wait(boost::bind(
                    &iec60870_101PM::handle_t3_expire, this,
                    boost::asio::placeholders::error));
        }

        void iec60870_101PM::set_t3() {
            if (!t3_progress)
                reset_t3();
        }

        void iec60870_101PM::cancel_t3() {
            t3_timer.cancel();
            t3_progress = false;
        }

        void iec60870_101PM::handle_t3_expire(const boost::system::error_code& err) {
            if (!err) {
                std::cout << "exp t3 " << std::endl;
                t3_state = true;
                t3_progress = false;
            } else {
                t3_state = false;
            }
        }




    }
}


