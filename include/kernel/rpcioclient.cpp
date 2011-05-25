
#include <kernel/rpcioclient.h>


namespace dvnci {
    namespace rpc {

        rpcioclient::rpcioclient() : io_service_(), socket_(io_service_), tmout_timer(io_service_), error_cod(0) {
            state_ = disconnected;}

        rpcioclient::~rpcioclient() {
            if (state_ == connected) disconnect();}

        void rpcioclient::connect(std::string host, std::string port, unsigned int timout_ ) {
            timout = in_bounded<unsigned int>(50, 600000, timout_);
            DEBUG_STR_DVNCI(ioclient connect)
            DEBUG_VAL_DVNCI(host)
            DEBUG_VAL_DVNCI(port)
            DEBUG_VAL_DVNCI(timout)
            boost::asio::ip::tcp::resolver resolver(io_service_);
            boost::asio::ip::tcp::resolver::query query(host.c_str(), port.c_str());

            is_timout     = false;
            is_connect    = false;
            is_error      = false;
            error_cod     = 0;

            io_service_.reset();

            DEBUG_STR_DVNCI(START ASYNC RESOLVER)

            resolver.async_resolve(query,
                    boost::bind(&rpcioclient::handle_resolve, shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::iterator));

            DEBUG_STR_DVNCI(START ASYNC CONNECTTIMER)

            tmout_timer.expires_from_now(boost::posix_time::milliseconds(timout));
            tmout_timer.async_wait(boost::bind(
                    &rpcioclient::handle_timout_expire, shared_from_this(),
                    boost::asio::placeholders::error));

            DEBUG_STR_DVNCI(START WAIT)

            io_service_.run();

            if (!is_connect) {
                DEBUG_STR_DVNCI(TIMOUTED OR ERROR)
                state_ = disconnected;
                try {
                    socket_.close();
                    io_service_.stop();}
                catch (...) {};
                throw dvncierror(ERROR_NONET_CONNECTED);}
            state_ = connected;}

        void rpcioclient::disconnect() {
            state_ = disconnected;
            socket_.close();
            io_service_.stop();}

        bool rpcioclient::req(rpcmessage& msg, rpcmessage& resp) {

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
                        boost::bind(&rpcioclient::handle_write, shared_from_this(),
                        boost::asio::placeholders::error));

                DEBUG_STR_DVNCI(SET ASYNCTIME)

                tmout_timer.expires_from_now(boost::posix_time::milliseconds(timout));
                tmout_timer.async_wait(boost::bind(
                        &rpcioclient::handle_timout_expire, shared_from_this(),
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
                resp.build_message("", 0);};
            return false;}

        void rpcioclient::handle_resolve(const boost::system::error_code& err,
                boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
            if (!err) {

                boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
                socket_.async_connect(endpoint,
                        boost::bind(&rpcioclient::handle_connect, shared_from_this(),
                        boost::asio::placeholders::error, ++endpoint_iterator));}
            else {
                io_service_.stop();
                tmout_timer.cancel();
                is_timout   = false;
                is_connect  = false;
                error_cod      = err.value();
                is_error       = true;
                DEBUG_STR_DVNCI(isErrorReesolve!!!)}}

        void rpcioclient::handle_connect(const boost::system::error_code& err,
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
                        boost::bind(&rpcioclient::handle_connect, shared_from_this(),
                        boost::asio::placeholders::error, ++endpoint_iterator));}
            else {}}

        void rpcioclient::handle_write(const boost::system::error_code& err) {

            if (!err) {

                boost::asio::async_read(socket_, boost::asio::buffer(buf), boost::asio::transfer_at_least(10), boost::bind(&rpcioclient::handle_readheader, shared_from_this(),
                        boost::asio::placeholders::error));}

            else {
                io_service_.stop();
                tmout_timer.cancel();
                is_timout      = false;
                is_data_ready  = false;
                error_cod      = err.value();
                is_error       = true;
                DEBUG_STR_DVNCI(is errror handle_write!!!)
                DEBUG_VAL_DVNCI(err.message())
                DEBUG_VAL_DVNCI(err.value())}}

        void rpcioclient::handle_readheader(const boost::system::error_code& err) {
            if (!err) {
                respmsg.setheader(buf.c_array());
                DEBUG_VAL_DVNCI(respmsg.body_length())
                boost::asio::async_read(socket_, response_body, boost::asio::transfer_at_least(respmsg.body_length()), boost::bind(&rpcioclient::handle_endreq, shared_from_this(),
                        boost::asio::placeholders::error));}
            else {
                io_service_.stop();
                tmout_timer.cancel();
                is_timout      = false;
                is_data_ready  = false;
                error_cod      = err.value();
                is_error       = true;
                DEBUG_STR_DVNCI(is errror readheader!!!)}}

        void rpcioclient::handle_endreq(const boost::system::error_code& err) {
            if (!err) {
                io_service_.stop();
                tmout_timer.cancel();
                respmsg.setbody(response_body);
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
                DEBUG_STR_DVNCI(is errror handle_endreq!!!)}}

        void rpcioclient::handle_timout_expire(const boost::system::error_code& err) {

            if (!err ) {
                io_service_.stop();
                socket_.close();
                is_timout      = true;
                is_data_ready  = false;
                is_error       = false;
                is_connect     = false;
                DEBUG_STR_DVNCI(TIMEOUT EXPIRE NEED EXCEPTION)}
            else {}}
}}



