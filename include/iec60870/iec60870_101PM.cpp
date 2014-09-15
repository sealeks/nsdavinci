
#include <deque>

#include "iec60870_101PM.h"


namespace dvnci {
    namespace prot80670 {


        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870_101PM
        /////////////////////////////////////////////////////////////////////////////////////////////////           

        /*iec60870_101PM::iec60870_101PM(chnlnumtype chnm, const metalink & lnk, const iec_option& opt, iec60870_data_listener_ptr listr) :
        iec60870_PM(opt, listr),
        serialport_(io_service_), serialport_io_sevice(io_service_), req_timer(io_service_),
        is_timout(false), is_error(false), error_cod(0), reqtmo_(1000), chnum_(chnm), comsetter_(lnk) {
        }*/

        /*void iec60870_101PM::connect() {
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
                apdu_870_ptr resp =request(apdu_870::create(0));
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

        void iec60870_101PM::handle_request(const boost::system::error_code& err, apdu_870_ptr req) {
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
                data_ready_ = apdu_870_ptr();
                error_cod = err.value();
                is_error = true;
                io_service_.stop();
            }
        }

        void iec60870_101PM::handle_response(const boost::system::error_code& err, apdu_870_ptr resp) {
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
                data_ready_ = apdu_870_ptr();
                error_cod = err.value();
                is_error = true;
                io_service_.stop();
            }
        }

        bool iec60870_101PM::send_S1(apdu_870_ptr req) {

            io_service_.reset();

            is_timout = false;
            data_ready_ = apdu_870_ptr();
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

        apdu_870_ptr iec60870_101PM::request(apdu_870_ptr req) {

            io_service_.reset();

            is_timout = false;
            data_ready_ = apdu_870_ptr();
            error_cod = 0;
            is_error = true;

            async_request(
                    boost::bind(&iec60870_101PM::handle_request, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred),
                    req);

            set_t_req();

            io_service_.run();

            if (is_error || is_timout)
                return apdu_870_ptr();

            io_service_.reset();

            is_timout = false;
            data_ready_ = apdu_870_ptr();
            error_cod = 0;
            is_error = false;

            async_response(
                    boost::bind(&iec60870_101PM::handle_response, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

            set_t_req();

            io_service_.run();

            if (is_error || is_timout)
                return apdu_870_ptr();

            return data_ready_;

        }






        bool iec60870_101PM::parse_data(apdu_870_ptr resp) {
            dataobject_vct rslt;
            if (resp->get(rslt))
                execute_data(rslt);
            return true;
        }

        void iec60870_101PM::insert_sector_sevice(device_address dev, selector_address slct) {
            waitrequestdata_.push_back(dataobject::create_activation_1(0, slct));
        }*/

        /*void iec60870_101PM::set_t_req() {
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
                data_ready_ = apdu_870_ptr();
                error_cod = err.value();
                is_error = true;
                io_service_.stop();
            } else {
                //t0_state = false;
            }
        }*/

    }
}


