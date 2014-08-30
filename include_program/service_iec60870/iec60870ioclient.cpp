
#include "iec60870ioclient.h"


namespace dvnci {
    namespace prot80670 {


        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870_executable
        /////////////////////////////////////////////////////////////////////////////////////////////////     

        iec60870_executable::iec60870_executable(iec60870ioclient_ptr clnt) : executable(), clnt_(clnt), state_(iec60870_executable::noinit) {
        }

        bool iec60870_executable::operator()() {
            while (!terminate_var) {
                switch (state_) {
                    case noinit:
                    {
                        message_104_ptr msg = message_104_ptr(new message_104(message_104::STARTDTact));
                        clnt_->handle_request(boost::bind(&iec60870_executable::handle_startdt_act, this, boost::asio::placeholders::error), msg);
                    }
                    default:
                    {
                    }
                }
            }
            return true;
        }

        bool iec60870_executable::initialize() {
            return true;
        }

        bool iec60870_executable::uninitialize() {
            return true;
        }

        void iec60870_executable::handle_startdt_act(const boost::system::error_code& err) {

        }

        void iec60870_executable::handle_startdt_conf(message_104_ptr req, const boost::system::error_code& err) {

        }

        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870ioclient
        /////////////////////////////////////////////////////////////////////////////////////////////////           

        iec60870ioclient::iec60870ioclient() : io_service_(), socket_(io_service_), tmout_timer(io_service_), respmsg(0, 0, ""), error_cod(0), tx_(0), rx_(0) {
            state_ = disconnected;
            executable_ = executable_ptr(new iec60870_executable(shared_from_this()));
        }

        iec60870ioclient::~iec60870ioclient() {
            if (state_ == connected) disconnect();
        }

        void iec60870ioclient::connect(std::string host, std::string port, timeouttype tmo) {
            timout = in_bounded<timeouttype>(50, 600000, tmo);
            DEBUG_STR_DVNCI(ioclient connect)
            DEBUG_VAL_DVNCI(host)
            DEBUG_VAL_DVNCI(port)
            DEBUG_VAL_DVNCI(timout)
            boost::asio::ip::tcp::resolver resolver(io_service_);
            boost::asio::ip::tcp::resolver::query query(host.c_str(), port.c_str());

            is_timout = false;
            is_connect = false;
            is_error = false;
            error_cod = 0;

            io_service_.reset();

            DEBUG_STR_DVNCI(START ASYNC RESOLVER)

            resolver.async_resolve(query,
                    boost::bind(&iec60870ioclient::handle_resolve, shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::iterator));

            DEBUG_STR_DVNCI(START ASYNC CONNECTTIMER)

            tmout_timer.expires_from_now(boost::posix_time::milliseconds(timout));
            tmout_timer.async_wait(boost::bind(
                    &iec60870ioclient::handle_timout_expire, shared_from_this(),
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
                throw dvncierror(ERROR_NONET_CONNECTED);
            }
            state_ = connected;
            /*message_104 respmesg;
            if (blocked_request(message_104(message_104::STARTDTact), respmesg)){
                if (respmesg.typeU()==message_104::STARTDTcon){
                    
                }
            }*/
        }

        void iec60870ioclient::disconnect() {
            state_ = disconnected;
            socket_.close();
            io_service_.stop();
        }

        void iec60870ioclient::start_thread() {
            if (executable_)
                ioth = boost::shared_ptr<boost::thread>(new boost::thread(executable_));
        }

        void iec60870ioclient::stop_thread() {
            if (executable_)
                executable_->terminate();
            if (ioth)
                ioth->join();
        }

        bool iec60870ioclient::blocked_request(const message_104& msg, message_104& resp) {

            if (state_ == connected) {

                boost::asio::streambuf request;
                std::ostream request_stream(&request);
                request_stream << msg.header();
                request_stream << msg.message();

                is_timout = false;
                is_data_ready = false;
                is_error = false;
                is_connect = true;
                error_cod = 0;
                response_body.consume(response_body.size());

                io_service_.reset();

                DEBUG_STR_DVNCI(SET ASYNCWRITE)

                boost::asio::async_write(socket_, request,
                        boost::bind(&iec60870ioclient::handle_write, shared_from_this(),
                        boost::asio::placeholders::error));

                DEBUG_STR_DVNCI(SET ASYNCTIME)

                tmout_timer.expires_from_now(boost::posix_time::milliseconds(timout));
                tmout_timer.async_wait(boost::bind(
                        &iec60870ioclient::handle_timout_expire, shared_from_this(),
                        boost::asio::placeholders::error));

                DEBUG_STR_DVNCI(SET RUN)

                io_service_.run();

                DEBUG_STR_DVNCI(SET RESULT)

                if (is_timout) {
                    state_ = disconnected;
                    try {
                        socket_.close();
                        io_service_.stop();
                    } catch (...) {
                    };
                    DEBUG_STR_DVNCI(ERROR_FAILNET_CONNECTED THROWING)
                            throw dvncierror(ERROR_FAILNET_CONNECTED);
                }

                if (is_error) {
                    if ((error_cod == 10054) || (error_cod == 10053)) {
                        state_ = disconnected;
                        try {
                            socket_.close();
                            io_service_.stop();
                        } catch (...) {
                        };
                        DEBUG_STR_DVNCI(ERROR_FAILNET_CONNECTED THROWING BY ERROR)
                                throw dvncierror(ERROR_FAILNET_CONNECTED);
                    } else DEBUG_STR_VAL_DVNCI(reqerr, error_cod)
                    }
                resp = respmsg;
                return true;
            } else {
                resp = message_104();
            };
            return false;
        }

        void handle_response(message_104_ptr req, const boost::system::error_code& err) {

        }

        bool iec60870ioclient::request(const message_104& msg) {

            if (state_ == connected) {

                boost::asio::streambuf request;
                std::ostream request_stream(&request);
                request_stream << msg.header();
                request_stream << msg.message();

                is_timout = false;
                is_data_ready = false;
                is_error = false;
                is_connect = true;
                error_cod = 0;
                response_body.consume(response_body.size());

                io_service_.reset();

                DEBUG_STR_DVNCI(SET ASYNCWRITE)

                boost::asio::async_write(socket_, request,
                        boost::bind(&iec60870ioclient::handle_write, shared_from_this(),
                        boost::asio::placeholders::error));

                /*DEBUG_STR_DVNCI(SET ASYNCTIME)

                tmout_timer.expires_from_now(boost::posix_time::milliseconds(timout));
                tmout_timer.async_wait(boost::bind(
                        &iec60870ioclient::handle_timout_expire, shared_from_this(),
                        boost::asio::placeholders::error));*

                DEBUG_STR_DVNCI(SET RUN)*/

                io_service_.run();

                DEBUG_STR_DVNCI(SET RESULT)

                if (is_timout) {
                    state_ = disconnected;
                    try {
                        socket_.close();
                        io_service_.stop();
                    } catch (...) {
                    };
                    DEBUG_STR_DVNCI(ERROR_FAILNET_CONNECTED THROWING)
                            throw dvncierror(ERROR_FAILNET_CONNECTED);
                }

                if (is_error) {
                    if ((error_cod == 10054) || (error_cod == 10053)) {
                        state_ = disconnected;
                        try {
                            socket_.close();
                            io_service_.stop();
                        } catch (...) {
                        };
                        DEBUG_STR_DVNCI(ERROR_FAILNET_CONNECTED THROWING BY ERROR)
                                throw dvncierror(ERROR_FAILNET_CONNECTED);
                    } else DEBUG_STR_VAL_DVNCI(reqerr, error_cod)
                    }
                return true;
            } else {
            };
            return false;
        }

        void iec60870ioclient::handle_resolve(const boost::system::error_code& err,
                boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {
            if (!err) {

                boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
                socket_.async_connect(endpoint,
                        boost::bind(&iec60870ioclient::handle_connect, shared_from_this(),
                        boost::asio::placeholders::error, ++endpoint_iterator));
            } else {
                io_service_.stop();
                tmout_timer.cancel();
                is_timout = false;
                is_connect = false;
                error_cod = err.value();
                is_error = true;
                DEBUG_STR_DVNCI(isErrorReesolve!!!)
            }
        }

        void iec60870ioclient::handle_connect(const boost::system::error_code& err,
                boost::asio::ip::tcp::resolver::iterator endpoint_iterator) {

            if (!err) {
                io_service_.stop();
                tmout_timer.cancel();
                is_timout = false;
                is_connect = true;
                is_error = false;
                DEBUG_STR_DVNCI(isConnected!!!)
            } else
                if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator()) {
                socket_.close();
                boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
                socket_.async_connect(endpoint,
                        boost::bind(&iec60870ioclient::handle_connect, shared_from_this(),
                        boost::asio::placeholders::error, ++endpoint_iterator));
            } else {
            }
        }

        void iec60870ioclient::handle_write(const boost::system::error_code& err) {

            if (!err) {

                boost::asio::async_read(socket_, boost::asio::buffer(buf), boost::asio::transfer_at_least(message_104::apci_length), boost::bind(&iec60870ioclient::handle_readheader, shared_from_this(),
                        boost::asio::placeholders::error));
            } else {
                io_service_.stop();
                tmout_timer.cancel();
                is_timout = false;
                is_data_ready = false;
                error_cod = err.value();
                is_error = true;
                DEBUG_STR_DVNCI(is errror handle_write!!!)
                DEBUG_VAL_DVNCI(err.message())
                DEBUG_VAL_DVNCI(err.value())
            }
        }

        void iec60870ioclient::handle_readheader(const boost::system::error_code& err) {
            if (!err) {
                respmsg.header(buf.c_array());
                DEBUG_VAL_DVNCI(respmsg.body_length())
                if (respmsg.body_length())
                    boost::asio::async_read(socket_, response_body, boost::asio::transfer_at_least(respmsg.body_length()), boost::bind(&iec60870ioclient::handle_endreq, shared_from_this(),
                        boost::asio::placeholders::error));
                else {
                    io_service_.stop();
                    tmout_timer.cancel();
                    is_timout = false;
                    is_data_ready = true;
                    error_cod = err.value();
                    is_error = false;
                }
            } else {
                io_service_.stop();
                tmout_timer.cancel();
                is_timout = false;
                is_data_ready = false;
                error_cod = err.value();
                is_error = true;
                DEBUG_STR_DVNCI(is errror readheader!!!)
            }
        }

        void iec60870ioclient::handle_endreq(const boost::system::error_code& err) {
            if (!err) {
                io_service_.stop();
                tmout_timer.cancel();
                respmsg.message(response_body);
                is_timout = false;
                is_data_ready = true;
                is_error = false;
            } else {
                io_service_.stop();
                tmout_timer.cancel();
                is_timout = false;
                is_data_ready = false;
                error_cod = err.value();
                is_error = true;
                DEBUG_STR_DVNCI(is errror handle_endreq!!!)
            }
        }

        void iec60870ioclient::handle_timout_expire(const boost::system::error_code& err) {

            if (!err) {
                io_service_.stop();
                socket_.close();
                is_timout = true;
                is_data_ready = false;
                is_error = false;
                is_connect = false;
                DEBUG_STR_DVNCI(TIMEOUT EXPIRE NEED EXCEPTION)
            } else {
            }
        }


    }
}


