
#include "mmsioclient.h"


namespace prot9506 {

    mmsioclient::mmsioclient() : io_service_(), socket_(io_service_, prot9506::protocol_option()), state_(disconnected), 
            tmout_timer(io_service_), timout(),  is_data_ready(false), is_timout(false), 
            is_connect(false), is_error(false), error_cod(0) {
    }

    mmsioclient::~mmsioclient() {
        if (state_ == connected) disconnect();
    }

    void mmsioclient::connect(const std::string hst, const std::string prt, const std::string opt,
            timeouttype tmo) {
        timout = dvnci::in_bounded<timeouttype>(50, 600000, tmo);
        DEBUG_STR_DVNCI(ioclient connect)
        DEBUG_VAL_DVNCI(hst)
        DEBUG_VAL_DVNCI(prt)
        DEBUG_VAL_DVNCI(timout)
        boost::asio::ip::tcp::resolver resolver(io_service_);
        boost::asio::ip::tcp::resolver::query query(hst.c_str(), prt.c_str());

        is_timout = false;
        is_connect = false;
        is_error = false;
        error_cod = 0;

        io_service_.reset();

        DEBUG_STR_DVNCI(START ASYNC RESOLVER)

        boost::asio::ip::tcp::resolver::iterator itr(resolver.resolve(query));   
        endpoint_type endpoint = * itr;
                
        /*resolver.async_resolve(query,
                boost::bind(&mmsioclient::handle_resolve, shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::iterator));*/
        
             socket_.async_connect(endpoint,
                boost::bind(&mmsioclient::handle_connect, shared_from_this(),
                boost::asio::placeholders::error,
                ++itr));        

        DEBUG_STR_DVNCI(START ASYNC CONNECTTIMER)

        tmout_timer.expires_from_now(boost::posix_time::milliseconds(timout));
        tmout_timer.async_wait(boost::bind(
                &mmsioclient::handle_timout_expire, shared_from_this(),
                boost::asio::placeholders::error));

        DEBUG_STR_DVNCI(START WAIT)

        io_service_.run();

        if (!is_connect) {
            DEBUG_STR_DVNCI(TIMOUTED OR ERROR)
            state_ = disconnected;
            try {
                socket_.close();
                io_service_.stop();
            } catch (...) {
            };
            throw dvnci::dvncierror(dvnci::ERROR_NONET_CONNECTED);
        }
        state_ = connected;
    }

    void mmsioclient::disconnect() {
        state_ = disconnected;
        socket_.close();
        io_service_.stop();
    }

    /*bool mmsioclient::req(rpcmessage& msg, rpcmessage& resp) {

        if (state_ == connected) {

            boost::asio::streambuf request;
            std::ostream request_stream(&request);
            request_stream << msg.header();
            request_stream << msg.message();

            is_timout       = false;
            is_data_ready   = false;
            is_error        = false;
            is_connect      = true;
            error_cod       = 0;
            response_body.consume(response_body.size());

            io_service_.reset();

            DEBUG_STR_DVNCI(SET ASYNCWRITE)

            boost::asio::async_write(socket_, request,
                    boost::bind(&mmsioclient::handle_write, shared_from_this(),
                    boost::asio::placeholders::error));

            DEBUG_STR_DVNCI(SET ASYNCTIME)

            tmout_timer.expires_from_now(boost::posix_time::milliseconds(timout));
            tmout_timer.async_wait(boost::bind(
                    &mmsioclient::handle_timout_expire, shared_from_this(),
                    boost::asio::placeholders::error));

            DEBUG_STR_DVNCI(SET RUN)

            io_service_.run();

            DEBUG_STR_DVNCI(SET RESULT)

            if (is_timout) {
                state_ = disconnected;
                try {
                    socket_.close();
                    io_service_.stop();}
                catch (...) {};
                DEBUG_STR_DVNCI(ERROR_FAILNET_CONNECTED THROWING)
                        throw dvncierror(ERROR_FAILNET_CONNECTED);}

            if (is_error) {
                if ((error_cod == 10054) || (error_cod == 10053)) {
                    state_ = disconnected;
                    try {
                        socket_.close();
                        io_service_.stop();}
                    catch (...) {};
                    DEBUG_STR_DVNCI(ERROR_FAILNET_CONNECTED THROWING BY ERROR)
                            throw dvncierror(ERROR_FAILNET_CONNECTED);}
                else  DEBUG_STR_VAL_DVNCI(reqerr, error_cod)}
            resp = respmsg;
            return true;}
        else {
            resp=rpcmessage("");};
        return false;}*/

    void mmsioclient::handle_resolve(const boost::system::error_code& err,
            boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
         if (!err) {

             boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
             
             socket_.async_connect(endpoint,
                boost::bind(&mmsioclient::handle_connect, shared_from_this(),
                boost::asio::placeholders::error,
                ++endpoint_iterator));}
         else {
             io_service_.stop();
             tmout_timer.cancel();
             is_timout   = false;
             is_connect  = false;
             error_cod      = err.value();
             is_error       = true;
             DEBUG_STR_DVNCI(isErrorReesolve!!!)}
    }

    void mmsioclient::handle_connect(const boost::system::error_code& err,
            boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {

        if (!err) {
            io_service_.stop();
            tmout_timer.cancel();
            is_timout   = false;
            is_connect  = true;
            is_error       = false;
            DEBUG_STR_DVNCI(isConnected!!!)}
        else
            if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator()) {
            socket_.close();
            boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
            socket_.async_connect(endpoint,
                    boost::bind(&mmsioclient::handle_connect, shared_from_this(),
                    boost::asio::placeholders::error, ++endpoint_iterator));}
        else {}
    }



    void mmsioclient::handle_endreq(const boost::system::error_code& err) {
        /*if (!err) {
            io_service_.stop();
            tmout_timer.cancel();
            respmsg.message(response_body);
            is_timout      = false;
            is_data_ready  = true;
            is_error       = false;}
        else {
            io_service_.stop();
            tmout_timer.cancel();
            is_timout      = false;
            is_data_ready  = false;
            error_cod      = err.value();
            is_error       = true;
            DEBUG_STR_DVNCI(is errror handle_endreq!!!)}*/
    }

    void mmsioclient::handle_timout_expire(const boost::system::error_code& err) {

        if (!err ) {
            io_service_.stop();
            socket_.close();
            is_timout      = true;
            is_data_ready  = false;
            is_error       = false;
            is_connect     = false;
            DEBUG_STR_DVNCI(TIMEOUT EXPIRE NEED EXCEPTION)}
        else {}
    }
}



