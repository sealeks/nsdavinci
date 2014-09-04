
#include "iec60870ioclient.h"


namespace dvnci {
    namespace prot80670 {


        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// class message_104
        /////////////////////////////////////////////////////////////////////////////////////////////////              

        message_104::message_104() :
        inprogress_(false), header_(new octet_sequence()), body_(new octet_sequence()) {
            header_prepare();
        }

        message_104::message_104(apcitypeU u) :
        inprogress_(false), header_(new octet_sequence()), body_(new octet_sequence()) {
            encode_header(U_type, u);
        }

        message_104::message_104(tcpcounter_type rx) :
        inprogress_(false), header_(new octet_sequence()), body_(new octet_sequence()) {
            encode_header(S_type, NULLu, 0, rx);
        }

        message_104::message_104(tcpcounter_type tx, tcpcounter_type rx, const dataobject& vl, cause_type cs) :
        inprogress_(false), header_(new octet_sequence()), body_(new octet_sequence()) {
            encode_body(vl, cs);
            encode_header(I_type, NULLu, tx, rx);
        }

        message_104::message_104(tcpcounter_type tx, tcpcounter_type rx, const asdu_body& vl) :
        inprogress_(false), header_(new octet_sequence()), body_(new octet_sequence()) {
            encode_body(vl);
            encode_header(I_type, NULLu, tx, rx);
        }

        message_104::~message_104() {
        }

        message_104_ptr message_104::create() {
            return message_104_ptr(new message_104());
        }

        message_104_ptr message_104::create(apcitypeU u) {
            return message_104_ptr(new message_104(u));
        }

        message_104_ptr message_104::create(tcpcounter_type rx) {
            return message_104_ptr(new message_104(rx));
        }

        message_104_ptr message_104::create(tcpcounter_type tx, tcpcounter_type rx, const dataobject& vl, cause_type cs) {
            return message_104_ptr(new message_104(tx, rx, vl, cs));
        }

        message_104_ptr message_104::create(tcpcounter_type tx, tcpcounter_type rx, const asdu_body& vl) {
            return message_104_ptr(new message_104(tx, rx, vl));
        }

        size_t message_104::body_length() const {
            size_t bl = 0;
            if (header().size() == apci_length) {
                if (header()[0] == FC_START104) {
                    bl = static_cast<size_t> (*((unum8*) & header()[1]));
                    if (bl >= 4) {
                        bl -= 4;
                        return bl;
                    }
                }
            }
            return 0;
        }

        message_104::apcitype message_104::type() const {
            if (header().size() < apci_length)
                return Null_type;
            octet_sequence::value_type mk = header()[2];
            if (!(header()[2]&1))
                return I_type;
            else if ((header()[2]&3)==3)
                return U_type;
            return S_type;
        }

        message_104::apcitypeU message_104::typeU() const {
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

        tcpcounter_type message_104::tx() const {
            if (header().size() < apci_length)
                return 0;
            return (((* reinterpret_cast<const tcpcounter_type*> (&header()[2])) >> 1) & 0x7FFF);
        }

        tcpcounter_type message_104::rx() const {
            if (header().size() < apci_length)
                return 0;
            return (((* reinterpret_cast<const tcpcounter_type*> (&header()[4])) >> 1) & 0x7FFF);
        }

        octet_sequence& message_104::header_prepare() {
            header().clear();
            header().assign(apci_length, 0);
            return header();
        }

        octet_sequence& message_104::body_prepare() {
            body().clear();
            if (body_length())
                body().assign(body_length(), 0);
            return body();
        }

        bool message_104::get(dataobject_vct& rslt) {
            if (body_) {
                asdu_body asdu(body_);
                return asdu.get(rslt);
            }
            return false;
        }

        void message_104::encode_header(apcitype tp, apcitypeU tpu, tcpcounter_type tx, tcpcounter_type rx) {
            header().clear();
            unum8 tmp_length = body().size() + 4;
            header().push_back(FC_START104);
            header().push_back(tmp_length);
            switch (tp) {
                case S_type:
                {
                    unum16 tmprx = (rx << 1) & 0xFFFE;
                    header().insert(header().end(), (const char*) &HD104_U_IND, (const char*) &HD104_U_IND + 2);
                    header().insert(header().end(), (const char*) &tmprx, (const char*) &tmprx + 2);
                    break;
                }
                case U_type:
                {
                    switch (tpu) {
                        case TESTFRact:
                        {
                            header().insert(header().end(), (const char*) &HD104_TESTFRact, (const char*) &HD104_TESTFRact + 4);
                            break;
                        }
                        case TESTFRcon:
                        {
                            header().insert(header().end(), (const char*) &HD104_TESTFRcon, (const char*) &HD104_TESTFRcon + 4);
                            break;
                        }
                        case STARTDTact:
                        {
                            header().insert(header().end(), (const char*) &HD104_STARTDTact, (const char*) &HD104_STARTDTact + 4);
                            break;
                        }
                        case STARTDTcon:
                        {
                            header().insert(header().end(), (const char*) &HD104_STARTDTcon, (const char*) &HD104_STARTDTcon + 4);
                            break;
                        }
                        case STOPDTact:
                        {
                            header().insert(header().end(), (const char*) &HD104_STOPDTact, (const char*) &HD104_STOPDTact + 4);
                            break;
                        }
                        case STOPDTcon:
                        {
                            header().insert(header().end(), (const char*) &HD104_STOPDTcon, (const char*) &HD104_STOPDTcon + 4);
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

        void message_104::encode_body(const dataobject& vl, cause_type cs) {
            body().clear();
            type_id tmptype = vl.type();
            body().push_back(tmptype);
            body().insert(body().end(), '\x1');
            body().push_back(cs);
            body().insert(body().end(), '\x0');
            device_address tmpdev = vl.devnum();
            body().insert(body().end(), (const char*) &tmpdev, (const char*) &tmpdev + 2);
            data_address tmpaddr = vl.address();
            body().insert(body().end(), (const char*) &tmpaddr, (const char*) &tmpaddr + 3);
            body().insert(body().end(), vl.data().begin(), vl.data().end());
        }

        void message_104::encode_body(const asdu_body& vl) {
            body_ = vl.body_ptr();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870pm
        /////////////////////////////////////////////////////////////////////////////////////////////////           

        iec60870pm::iec60870pm(std::string hst, std::string prt, timeouttype tmo, iec60870_data_listener_ptr listr) :
        io_service_(), socket_(io_service_), tmout_timer(io_service_), short_timer(io_service_),
        host(hst), port(prt), timout(tmo), state_(disconnected), pmstate_(noconnected),
         tx_(0), rx_(0), listener_(listr) {
        }

        iec60870pm::~iec60870pm() {
            if (state_ == connected) disconnect();
        }

        void iec60870pm::pmstate(iec60870pm::PMState vl) {
            pmstate_ = vl;
        }

        bool iec60870pm::operator()() {
            connect();
            iec60870_data_listener_ptr lstnr = listener();
            if (lstnr)
                lstnr->terminate60870();            
            return true;
        }

        bool iec60870pm::initialize() {
            return true;
        }

        bool iec60870pm::uninitialize() {
            return true;
        }
                 
        
        
        bool iec60870pm::add_items(const indx_dataobject_vct& cids, indx_dataobject_vct& rslt){
            THD_EXCLUSIVE_LOCK(mtx)
            for (indx_dataobject_vct::const_iterator it=cids.begin();it!=cids.end();++it){
                dataobject_set::const_iterator fnd=data_.find(it->second);
                if (fnd!=data_.end()){
                    rslt.push_back(indx_dataobject_pair(it->first,*fnd));
                }
                else{
                    if (it->second->readable()){
                        waitrequestdata_.push_back(it->second);
                    }
                }
            }
            return !rslt.empty();
        }
        
        
        void iec60870pm::error(boost::system::error_code& err) {
                iec60870_data_listener_ptr lstnr = listener();
                if (lstnr)
                    lstnr->execute60870(err);
        }              

        void iec60870pm::connect() {
            timout = in_bounded<timeouttype>(50, 600000, timout);
            DEBUG_STR_DVNCI(ioclient connect)
            DEBUG_VAL_DVNCI(host)
            DEBUG_VAL_DVNCI(port)
            DEBUG_VAL_DVNCI(timout)
            boost::asio::ip::tcp::resolver resolver(io_service_);
            boost::asio::ip::tcp::resolver::query query(host.c_str(), port.c_str());

            DEBUG_STR_DVNCI(START ASYNC RESOLVER)

            resolver.async_resolve(query,
                    boost::bind(&iec60870pm::handle_resolve, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::iterator));

            DEBUG_STR_DVNCI(START ASYNC CONNECTTIMER)

            tmout_timer.expires_from_now(boost::posix_time::milliseconds(timout));
            tmout_timer.async_wait(boost::bind(
                    &iec60870pm::handle_timout_expire, this,
                    boost::asio::placeholders::error));

            DEBUG_STR_DVNCI(START WAIT)
            io_service_.run();

        }

        void iec60870pm::disconnect() {
            state_ = disconnected;
            socket_.close();
            io_service_.stop();
        }

        void iec60870pm::terminate() {
            state_ = disconnected;
            socket_.close();
            io_service_.stop();
        }             
        
        
        void iec60870pm::handle_resolve(const boost::system::error_code& err,
                boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
            if (!err) {
                boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
                socket_.async_connect(endpoint,
                        boost::bind(&iec60870pm::handle_connect, this,
                        boost::asio::placeholders::error, ++endpoint_iterator));
            } else {
                terminate();
            }
        }

        void iec60870pm::handle_connect(const boost::system::error_code& err,
                boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {

            if (!err) {
                tmout_timer.cancel();
                pmstate(noaciveted);
                send(message_104::STARTDTact);
            } else
                if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator()) {
                socket_.close();
                boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
                socket_.async_connect(endpoint,
                        boost::bind(&iec60870pm::handle_connect, this,
                        boost::asio::placeholders::error, ++endpoint_iterator));
            } else {
                 terminate();               
            }
        }

        void iec60870pm::handle_request(const boost::system::error_code& error, message_104_ptr req) {
            if (!error)
                check_work_available();
            else
                terminate();
        }

        void iec60870pm::handle_response(const boost::system::error_code& error, message_104_ptr resp) {
            if (!error) {
                parse_response(resp);
            } else
                terminate();
        }

        void iec60870pm::handle_timout_expire(const boost::system::error_code& err) {

            if (!err) {
                terminate();
            } else {
               //std::cout << " expire timer error" << std::endl;
            }
        }
        
        void iec60870pm::handle_short_timout_expire(const boost::system::error_code& err){
            check_work_available();   
        }


        
        void iec60870pm::send(const asdu_body& asdu) {
            send(message_104::create(tx_++, rx_, asdu));
        }

        void iec60870pm::send(message_104_ptr msg) {
            if (msg->type() == message_104::I_type)
                sended_.push_back(msg);
            async_request(
                    boost::bind(&iec60870pm::handle_request, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred),
                    msg);
        }

        void iec60870pm::send(message_104::apcitypeU u) {
            async_request(
                    boost::bind(&iec60870pm::handle_request, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred),
                    message_104::create(u));
        }

        void iec60870pm::send(tcpcounter_type cnt) {
            async_request(
                    boost::bind(&iec60870pm::handle_request, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred), message_104::create(cnt));
        }
        
        void iec60870pm::receive() {
            async_response(
                    boost::bind(&iec60870pm::handle_response, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));            
        }    
        
        void iec60870pm::short_wait() {
            short_timer.expires_from_now(boost::posix_time::milliseconds(PM_SHORT_TIMER));
            short_timer.async_wait(boost::bind(
                    &iec60870pm::handle_short_timout_expire, this,
                    boost::asio::placeholders::error));
        }               

        void iec60870pm::check_work_available() {
            if (socket_.available()){
                receive();
                return;
            }            
            {
                THD_EXCLUSIVE_LOCK(mtx)
                if (!waitrequestdata_.empty()) {
                    send(asdu_body::create_polling(waitrequestdata_.back()));
                    waitrequestdata_.pop_back();
                    return;
                }
            }
            short_wait();
        }

 

        void iec60870pm::set_rx(tcpcounter_type vl) {
            //std::cout << " set Rx = " << vl << std::endl;
            rx_ = vl;
        }

        void iec60870pm::ack_tx(tcpcounter_type vl) {
            std::cout << " ack Tx = " << vl << std::endl;
            if (!sended_.empty()) {
                while ((!sended_.empty()) && (sended_.front()->tx() < vl)) {
                    sended_.pop_front();
                }
            }
            std::cout << " sended size = " << sended_.size()  << std::endl;
        }

        bool iec60870pm::parse_response(message_104_ptr resp) {
            if (resp) {
                switch (resp->type()) {
                    case message_104::S_type:
                    {
                        ack_tx(resp->rx());
                        break;
                    }
                    case message_104::U_type:
                    {
                        if (parse_U(resp))
                            return true;
                        break;
                    }
                    case message_104::I_type:
                    {
                        parse_data(resp);
                        if (socket_.available()) {
                            break;
                        } else {
                            send(rx_ + 1);
                            return true;
                        }
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
        

        bool iec60870pm::parse_U(message_104_ptr resp) {
            switch (resp->typeU()) {
                case message_104::TESTFRact:
                {
                    send(message_104::TESTFRcon);
                    return true;
                }
                case message_104::TESTFRcon:
                {
                    return false;
                }
                case message_104::STARTDTact:
                {
                    send(message_104::STARTDTcon);
                    pmstate(noaciveted);
                    return true;
                }
                case message_104::STARTDTcon:
                {
                    state_ = connected;
                    pmstate(activated);
                    send(asdu_body::create_activation());
                    return false;;
                }
                case message_104::STOPDTact:
                {
                    break;
                }
                case message_104::STOPDTcon:
                {
                    break;
                }
                default:
                {
                }
            }
            return false;
        }

        bool iec60870pm::parse_data(message_104_ptr resp) {
            set_rx(resp->tx());
            ack_tx(resp->rx());
            dataobject_vct rslt;
            if (resp->get(rslt)) {
                {
                    THD_EXCLUSIVE_LOCK(mtx)
                    data_.insert(rslt.begin(), rslt.end());
                }
                iec60870_data_listener_ptr lstnr = listener();
                if (lstnr)
                    lstnr->execute60870(rslt);
            }
            return true;
        }


        

        

        iec60870_thread::iec60870_thread(std::string host, std::string port, timeouttype tmo, iec60870_data_listener_ptr listr) {
            pm_ = callable_shared_ptr<iec60870pm>(new iec60870pm(host, port, tmo, listr));
            ioth = boost::shared_ptr<boost::thread>(new boost::thread(pm_));
        }

         iec60870_thread::~iec60870_thread() {
             /*if (ioth)
                 ioth->join();*/
        }

        iec60870_thread_ptr iec60870_thread::create(std::string host, std::string port, timeouttype tmo,
                iec60870_data_listener_ptr listr) {
            return iec60870_thread_ptr(new iec60870_thread(host, port, tmo, listr));
        }

        callable_shared_ptr<iec60870pm>iec60870_thread::pm() const {
            return pm_;
        }

        callable_shared_ptr<iec60870pm>iec60870_thread::pm() {
            return pm_;
        }

    }
}


