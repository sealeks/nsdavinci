
#include "iec60870ioclient.h"


namespace dvnci {
    namespace prot80670 {


        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870pm
        /////////////////////////////////////////////////////////////////////////////////////////////////           

        iec60870pm::iec60870pm(std::string hst, std::string prt, timeouttype tmo) :
        io_service_(), socket_(io_service_), tmout_timer(io_service_), host(hst), port(prt), timout(tmo), state_(disconnected), error_cod(0), tx_(0), rx_(0) {
        }

        iec60870pm::~iec60870pm() {
            if (state_ == connected) disconnect();
        }

        bool iec60870pm::operator()() {
            connect();
            return true;
        }

        bool iec60870pm::initialize() {
            return true;
        }

        bool iec60870pm::uninitialize() {
            return true;
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

        void iec60870pm::handle_resolve(const boost::system::error_code& err,
                boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
            if (!err) {
                boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
                socket_.async_connect(endpoint,
                        boost::bind(&iec60870pm::handle_connect, this,
                        boost::asio::placeholders::error, ++endpoint_iterator));
            } else {

            }
        }

        void iec60870pm::handle_connect(const boost::system::error_code& err,
                boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {

            if (!err) {
                state_ = connectedCh;
                tmout_timer.cancel();
                message_104_ptr msgtmp =message_104::create(message_104::STARTDTact);
                async_request(
                        boost::bind(&iec60870pm::handle_request, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred), msgtmp);
            } else
                if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator()) {
                socket_.close();
                boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
                socket_.async_connect(endpoint,
                        boost::bind(&iec60870pm::handle_connect, this,
                        boost::asio::placeholders::error, ++endpoint_iterator));
            } else {
            }
        }

        void iec60870pm::handle_request(const boost::system::error_code& error, message_104_ptr req) {  
            //message_104_ptr msgtmp =message_104::create();
            async_response(
                    boost::bind(&iec60870pm::handle_response, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        }

        void iec60870pm::handle_response(const boost::system::error_code& error, message_104_ptr resp) {
            if (resp){
                switch(resp->type()){
                    case message_104::S_type:{
                        rx_=resp->rx();
                        break;
                    }
                    case message_104::U_type:{
                        message_104::apcitypeU tput=resp->typeU();
                        switch (resp->typeU()) {
                            case message_104::TESTFRact:
                            {
                                async_request(
                                        boost::bind(&iec60870pm::handle_request, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred),
                                        message_104::create(message_104::TESTFRcon));
                                return;
                            }
                            case message_104::TESTFRcon:{
                                break;
                            }
                            case message_104::STARTDTact:{
                                async_request(
                                        boost::bind(&iec60870pm::handle_request, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred), 
                                        message_104::create(message_104::STARTDTcon));
                                return;
                            }
                            case message_104::STARTDTcon:{
                                break;
                            }
                            case message_104::STOPDTact:{
                                break;
                            }
                            case message_104::STOPDTcon:{
                                break;
                            }
                            default:{}
                        }                        
                        break;
                    }
                    case message_104::I_type:{
                        rx_=resp->tx();
                        if (socket_.available()) {
                            break;
                        }
                        else{
                                async_request(
                                        boost::bind(&iec60870pm::handle_request, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred), message_104::create(rx_));
                                return;                            
                        }
                        break;
                    }
                    default:{}
                }
            }
            async_response(
                    boost::bind(&iec60870pm::handle_response, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        }

        void iec60870pm::handle_timout_expire(const boost::system::error_code& err) {

            if (!err) {
                DEBUG_STR_DVNCI(TIMEOUT EXPIRE NEED EXCEPTION)
            } else {
            }
        }

        iec60870ioclient::iec60870ioclient(std::string host, std::string port, timeouttype tmo) {
            iooclnt = callable_shared_ptr<iec60870pm>(new iec60870pm(host, port, tmo));
            ioth = boost::shared_ptr<boost::thread>(new boost::thread(iooclnt));
        }

        iec60870pm::PMState iec60870ioclient::state() const {
            return iooclnt->state();
        }


    }
}


