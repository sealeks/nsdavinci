
#include "iec60870ioclient.h"


namespace dvnci {
    namespace prot80670 {

        static string_type_id_map string_type_id_load() {
            string_type_id_map mp;
            mp.insert(string_type_id_pair("M_SP_NA", 1)); // Single-point information
            mp.insert(string_type_id_pair("M_SP_TA", 2)); //Single-point information with time-tag
            mp.insert(string_type_id_pair("M_DP_NA", 3)); //Double-point information
            mp.insert(string_type_id_pair("M_DP_TA", 4)); //Double-point information with time-tag
            mp.insert(string_type_id_pair("M_ST_NA", 5)); //Step position information
            mp.insert(string_type_id_pair("M_ST_TA", 6)); //Step position information with time-tag
            mp.insert(string_type_id_pair("M_BO_NA", 7)); //Bitstring of 32 bits
            mp.insert(string_type_id_pair("M_BO_TA", 8)); //Bitstring of 32 bits with time-tag
            mp.insert(string_type_id_pair("M_ME_NA", 9)); //Measured value, normalized value
            mp.insert(string_type_id_pair("M_ME_TA", 10)); //Measured value, normalized value with time-tag
            mp.insert(string_type_id_pair("M_ME_NB", 11)); //Measured value, scaled value
            mp.insert(string_type_id_pair("M_ME_TB", 12)); //Measured value, scaled value with time-tag
            mp.insert(string_type_id_pair("M_ME_NC", 13)); //Measured value, short floating point value
            mp.insert(string_type_id_pair("M_ME_TC", 14)); //Measured value, short floating point value with time-tag
            mp.insert(string_type_id_pair("M_IT_NA", 15)); //Integrated totals
            mp.insert(string_type_id_pair("M_IT_TA", 16)); //Integrated totals with time-tag
            mp.insert(string_type_id_pair("M_EP_TA", 17)); //Event of protection equipment with time-tag
            mp.insert(string_type_id_pair("M_EP_TB", 18)); //Packed start events of protection equipment with time-tag
            mp.insert(string_type_id_pair("M_EP_TC", 19)); //Packed output circuit information of protection equipment with timetag
            mp.insert(string_type_id_pair("M_PS_NA", 20)); //Packed single point information with status change detection
            mp.insert(string_type_id_pair("M_ME_ND", 21)); //Measured value, normalized value without quality descriptor
            mp.insert(string_type_id_pair("M_SP_TB", 30)); //Single-point information with time tag CP56Time2a
            mp.insert(string_type_id_pair("M_DP_TB", 31)); //Double-point information with time tag CP56Time2a
            mp.insert(string_type_id_pair("M_ST_TB", 32)); //Step position information with time tag CP56Time2a
            mp.insert(string_type_id_pair("M_BO_TB", 33)); //Bitstring of 32 bit with time tag CP56Time2a
            mp.insert(string_type_id_pair("M_ME_TD", 34)); //Measured value, normalized value with time tag CP56Time2a
            mp.insert(string_type_id_pair("M_ME_TE", 35)); //Measured value, scaled value with time tag CP56Time2a
            mp.insert(string_type_id_pair("M_ME_TF", 36)); //Measured value, short floating point value with time tag CP56Time2a
            mp.insert(string_type_id_pair("M_IT_TB", 37)); //Integrated totals with time tag CP56Time2a
            mp.insert(string_type_id_pair("M_EP_TD", 38)); //Event of protection equipment with time-tag CP56Time2a
            mp.insert(string_type_id_pair("M_EP_TE", 39)); //Packed start events of protection equipment with time-tag CP56Time2a
            mp.insert(string_type_id_pair("M_EP_TF", 40)); //Packed output circuit information of protection equipment with timetag CP56Time2a
            mp.insert(string_type_id_pair("C_SC_NA", 45)); // Single command 
            mp.insert(string_type_id_pair("C_DC_NA", 46)); // Double command
            mp.insert(string_type_id_pair("C_RC_NA", 47)); // Regulating step command
            mp.insert(string_type_id_pair("C_SE_NA", 48)); // Set point command, normalized value
            mp.insert(string_type_id_pair("C_SE_NB", 49)); // Set point command, scaled value
            mp.insert(string_type_id_pair("C_SE_NC", 50)); // Set point command, short floating point value
            mp.insert(string_type_id_pair("C_BO_NA", 51)); // Bitstring of 32 bit
            mp.insert(string_type_id_pair("C_SC_TA", 58)); // Single command with time tag CP56Time 2a 
            mp.insert(string_type_id_pair("C_DC_TA", 59)); // Double command with time tag CP56Time 2a
            mp.insert(string_type_id_pair("C_RC_TA", 60)); // Regulating step command with time tag CP56Time 2a
            mp.insert(string_type_id_pair("C_SE_TA", 61)); // Set point command, normalized value with time tag CP56Time 2a
            mp.insert(string_type_id_pair("C_SE_TB", 62)); // Set point command, scaled value with time tag CP56Time 2a
            mp.insert(string_type_id_pair("C_SE_TC", 63)); // Set point command, short floating point value with time tag CP56Time 2a
            mp.insert(string_type_id_pair("C_BO_TA", 64)); // Bitstring of 32 bit with time tag CP56Time 2a      
            mp.insert(string_type_id_pair("P_ME_NA", 110)); // Parameter of measured value, normalized value 110
            mp.insert(string_type_id_pair("P_ME_NB", 111)); // Parameter of measured value, scaled value
            mp.insert(string_type_id_pair("P_ME_NC", 112)); // Parameter of measured value, short floating point value
            mp.insert(string_type_id_pair("P_AC_NA", 113)); // Parameter activation            
            return mp;
        }

        static const string_type_id_map& get_type_id_map() {
            static string_type_id_map mp = string_type_id_load();
            return mp;
        }

        type_id find_type_id(const std::string& val) {
            const string_type_id_map& mp = get_type_id_map();
            string_type_id_map::const_iterator fit = mp.find(val);
            if (fit != mp.end())
                return fit->second;
            return 0;
        }



        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// dataobject
        /////////////////////////////////////////////////////////////////////////////////////////////////           

        dataobject_ptr dataobject::build_from_bind(device_address dev, std::string bind) {
            /* Name data type without _1 example M_SP_NA_1 => M_SP_NA == X_XX_XX
                         X_XX_XXNNNNN[.B]                
                         main templ = [CMP]_[ABSDEIMPRS][CEPTOS]_[TN][ABCDEF][0-9]{1,6}.{0,1}[0-9]{0,2}   
             */
            if (bind.size() > 7) {
                upper_and_trim(bind);
                std::string typedata = bind.substr(0, 7);
                std::string addrdata = bind.substr(7);
                type_id tp = find_type_id(typedata);
                bit_number bt = NULL_BITNUMBER;
                data_address addr = 0;
                if (tp) {
                    std::string::size_type bitit = addrdata.find('.', 0);
                    if ((bitit != std::string::npos) && (bitit != (addrdata.size() - 1))) {
                        std::string bitdata = addrdata.substr(bitit + 1);
                        addrdata = addrdata.substr(0, bitit);
                        if (!dvnci::str_to(addrdata, bt)) {
                            return dataobject_ptr();
                        }
                    }
                    if (!dvnci::str_to(addrdata, addr))
                        return dataobject_ptr();
                    return dataobject_ptr(new dataobject(dev, tp, addr, bt));
                }
            }
            return dataobject_ptr();

        }

        bool operator==(const dataobject& ls, const dataobject& rs) {
            return ((ls.devnum_ == rs.devnum_) && (ls.address_ == rs.address_) && (ls.type_ == rs.type_));
        }

        bool operator<(const dataobject& ls, const dataobject& rs) {
            if (ls.devnum_ == rs.devnum_) {
                if (ls.type_ == rs.type_)
                    return ls.address_ < rs.address_;
                return ls.type_ < rs.type_;
            }
            return ls.devnum_ < rs.devnum_;
        }

        bool operator==(dataobject_ptr ls, dataobject_ptr rs) {
            if (ls && rs)
                return (*ls) == (*rs);
            return (!ls && !rs);
        }

        bool operator<(dataobject_ptr ls, dataobject_ptr rs) {
            if (ls && rs)
                return (*ls)<(*rs);
            if (!ls && !rs)
                return false;
            return !ls;
        }






        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870ioclient
        /////////////////////////////////////////////////////////////////////////////////////////////////           

        iec60870ioclient::iec60870ioclient() : io_service_(), socket_(io_service_), tmout_timer(io_service_), respmsg(0,0,""), error_cod(0) {
            state_ = disconnected;
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
                message_104 reqm(message_104::STARTDTcon);
                message_104 respm;
                req(reqm,respm);
        }

        void iec60870ioclient::disconnect() {
            state_ = disconnected;
            socket_.close();
            io_service_.stop();
        }

        bool iec60870ioclient::req(message_104& msg, message_104& resp) {

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
                    }                    catch (...) {
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
                        }                        catch (...) {
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

                  boost::asio::async_read(socket_, boost::asio::buffer(buf), boost::asio::transfer_at_least(6), boost::bind(&iec60870ioclient::handle_readheader, shared_from_this(),
                          boost::asio::placeholders::error));
              }
              else {
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
                else{
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


