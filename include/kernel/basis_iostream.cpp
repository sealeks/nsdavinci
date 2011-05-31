/* 
 * File:   basis_iostream.cpp
 * Author: Serg
 * 
 * Created on 26 РћРєС‚СЏР±СЂСЊ 2010 Рі., 12:54
 */


#include <kernel/basis_iostream.h>

namespace dvnci {
    namespace driver {

#if defined(_DVN_WIN_)        

        void set_rs232_baudrate(com_port_option& opt, const baudratetype& br) {
            opt.BaudRate = static_cast<DWORD> (br);}

        void set_rs232_comoption(com_port_option& opt, size_t databit, const rsparitytype& prt, const rsstopbittype&  stpbt) {
            opt.ByteSize = static_cast<BYTE> (databit);
            opt.Parity   = static_cast<DWORD> (prt);
            opt.StopBits = static_cast<BYTE> (stpbt);}

        void set_rs232_cominill(com_port_option& opt) {
            opt.fOutxCtsFlow = 0;
            opt.fOutxDsrFlow = 0;
            opt.fDtrControl = 0;
            opt.fDsrSensitivity = 0;
            opt.fOutX = 0;
            opt.fInX = 0;}

        void set_rs232_flowcontrol(com_port_option& opt, bool vl) {
            if (!vl) {
                opt.fOutxCtsFlow = 0;
                opt.fOutxDsrFlow = 0;
                opt.fDtrControl = 0;
                opt.fDsrSensitivity = 0;
                opt.fOutX = 0;
                opt.fInX = 0;}
            else {
                opt.fOutxCtsFlow = 0;
                opt.fOutxDsrFlow = 0;
                opt.fDtrControl = 0;
                opt.fDsrSensitivity = 0;
                opt.fOutX = 0;
                opt.fInX = 0;}}

#elif defined(_DVN_LIN_)

        void set_rs232_baudrate(com_port_option& opt, const baudratetype& br) {
            switch (br) {
                case NT_RS_DOUNDRATE_110:{
                    cfsetospeed(&opt, B110);
                    cfsetispeed(&opt, B110);
                    return;}
                case NT_RS_DOUNDRATE_300:{
                    cfsetospeed(&opt, B300);
                    cfsetispeed(&opt, B300);
                    return;}
                case NT_RS_DOUNDRATE_600:{
                    cfsetospeed(&opt, B600);
                    cfsetispeed(&opt, B600);
                    return;}
                case NT_RS_DOUNDRATE_1200:{
                    cfsetospeed(&opt, B1200);
                    cfsetispeed(&opt, B1200);
                    return;}
                case NT_RS_DOUNDRATE_2400:{
                    cfsetospeed(&opt, B2400);
                    cfsetispeed(&opt, B2400);
                    return;}
                case NT_RS_DOUNDRATE_4800:{
                    cfsetospeed(&opt, B4800);
                    cfsetispeed(&opt, B4800);
                    return;}
                case NT_RS_DOUNDRATE_9600:{
                    cfsetospeed(&opt, B9600);
                    cfsetispeed(&opt, B9600);
                    return;}
                case NT_RS_DOUNDRATE_14400:{
                    cfsetospeed(&opt, B9600);
                    cfsetispeed(&opt, B9600);
                    return;}
                case NT_RS_DOUNDRATE_19200:{
                    cfsetospeed(&opt, B19200);
                    cfsetispeed(&opt, B19200);
                    return;}
                case NT_RS_DOUNDRATE_38400:{
                    cfsetospeed(&opt, B38400);
                    cfsetispeed(&opt, B38400);
                    return;}
                case NT_RS_DOUNDRATE_56000:{
                    cfsetospeed(&opt, B57600);
                    cfsetispeed(&opt, B57600);
                    return;}
                case NT_RS_DOUNDRATE_57600:{
                    cfsetospeed(&opt, B57600);
                    cfsetispeed(&opt, B57600);
                    return ;}
                case NT_RS_DOUNDRATE_115200:{
                    cfsetospeed(&opt, B115200);
                    cfsetispeed(&opt, B115200);
                    return;}
                case NT_RS_DOUNDRATE_128000:{
                    cfsetospeed(&opt, B115200);
                    cfsetispeed(&opt, B115200);
                    return;}
                case NT_RS_DOUNDRATE_256000:{
                    cfsetospeed(&opt, B2500000);
                    cfsetispeed(&opt, B2500000);
                    return;}}
            cfsetospeed(&opt, B9600);
            cfsetispeed(&opt, B9600);}

        void set_rs232_comoption(com_port_option& opt, size_t databit, const rsparitytype& prt, const rsstopbittype&  stpbt) {
            opt.c_cflag |= INPCK; // enable parity
            bool needextend = ((prt == NT_RS_MARKPARITY) || (prt == NT_RS_SPACEPARITY));
            opt.c_cflag &= ~CSIZE;
            switch (databit) {
                case 5:{
                    opt.c_cflag |= (needextend ? CS6: CS5);
                    break;}
                case 6:{
                    opt.c_cflag |= (needextend ? CS7: CS6);
                    break;}
                case 7:{
                    opt.c_cflag |= (needextend ? CS8: CS7);
                    break;}
                default:{
                    opt.c_cflag |= CS8;}}

            switch (prt) {
                case NT_RS_NOPARITY:{
                    opt.c_cflag &= ~PARENB;
                    break;}
                case NT_RS_ODDPARITY:{
                    opt.c_cflag |= PARENB;
                    opt.c_cflag |= PARODD;
                    break;}
                case NT_RS_EVENPARITY:{
                    opt.c_cflag |= PARENB;
                    opt.c_cflag &= ~PARODD;
                    break;}
                case NT_RS_MARKPARITY:{
                    opt.c_cflag &= ~PARENB;
                    break;}
                case NT_RS_SPACEPARITY:{
                    opt.c_cflag &= ~PARENB;
                    break;}
                default:{
                    opt.c_cflag &= ~PARENB;}}

            if (stpbt == NT_RS_ONESTOPBIT) {
                opt.c_cflag &= ~CSTOPB;}
            else {
                opt.c_cflag |= CSTOPB;}}

        void set_rs232_cominill(com_port_option& opt) {
            opt.c_oflag &= ~OPOST;
            opt.c_iflag |= (CLOCAL | CREAD);
            opt.c_iflag &= ~(IXON | IXOFF | IXANY);}

        void set_rs232_flowcontrol(com_port_option& opt, bool vl) {
            if (!vl)
                opt.c_iflag &= ~(IXON | IXOFF | IXANY);
            else
                opt.c_iflag &= ~(IXON | IXOFF | IXANY);}

#endif        


        //basis_iostream

        basis_iostream::basis_iostream(timeouttype tout, bool echor) : io_service_(), tmout_timer_(io_service_),
        is_data_ready(false), is_timout(false), is_connect(false), is_error(false), error_cod(0),
        state_(disconnected),   timout_(tout <= MINIMUM_IOTIMOUT ? DEFAULT_IOTIMOUT : tout), echorespopse_(echor) {};

        ns_error basis_iostream::open() {
            if (state() != connected) {
                error(0);
                connect_impl();}
            return error();}

        ns_error basis_iostream::close() {
            if (state() != disconnected) {
                error(0);
                disconnect_impl();
                return error();}
            return error(0);}

        void basis_iostream::clearbuff() {
            clear_wb();
            clear_rb();}

        size_t basis_iostream::clearbuff_deep(timeouttype tmo, size_t cnt) {
            std::string tmp = "1";
            if (state() != connected) return 0;
            size_t cnttmp = 0;
            while ((!read(tmp, 0, tmo)) && (cnt > (cnttmp++)) && (!tmp.empty())) {
                tmp = "";
                read(tmp, 0, tmo);
                clear_wb();
                clear_rb();
                error_cod = 0;}
            return tmp.size();}

        bool basis_iostream::timout_sec(timeouttype sec) {
            //DEBUG_STR_DVNCI(START ASYNC TIMER)
            sec = sec < 1 ? 0 : sec;
            is_timout    = false;
            try {
                io_service_.reset();
                tmout_timer_.expires_from_now(boost::posix_time::seconds(sec));
                tmout_timer_.async_wait(boost::bind(
                        &basis_iostream::tm_handle_timout_expire, shared_from_this(),
                        boost::asio::placeholders::error));
                io_service_.run();}
            catch (...) {
                return false;}
            return is_timout;}

        bool basis_iostream::timout_millisec(timeouttype mls) {
            //DEBUG_STR_DVNCI(START ASYNC TIMER)
            mls = mls < 1 ? 1 : mls;
            is_timout    = false;
            try {
                io_service_.reset();
                tmout_timer_.expires_from_now(boost::posix_time::millisec(mls));
                tmout_timer_.async_wait(boost::bind(
                        &basis_iostream::tm_handle_timout_expire, shared_from_this(),
                        boost::asio::placeholders::error));
                io_service_.run();}
            catch (...) {
                return false;}
            return is_timout;}

        bool basis_iostream::timout_micsec(timeouttype mcs) {
            //DEBUG_STR_DVNCI(START ASYNC TIMER)
            mcs = mcs < 1 ? 1 : mcs;
            is_timout    = false;
            try {
                io_service_.reset();
                tmout_timer_.expires_from_now(boost::posix_time::microsec(mcs));
                tmout_timer_.async_wait(boost::bind(
                        &basis_iostream::tm_handle_timout_expire, shared_from_this(),
                        boost::asio::placeholders::error));
                io_service_.run();}
            catch (...) {
                return false;}
            return is_timout;}

        void basis_iostream::io_handle_timout_expire(const boost::system::error_code& err) {

            if (!err ) {
                if (is_timout) {
                    io_service_.stop();
                    throw dvncierror(ERROR_IO_SERVICE_LOCK);}
                cancel_impl();
                is_timout      = true;
                is_data_ready  = false;
                is_connect     = false;
                tmout_timer_.expires_from_now(boost::posix_time::milliseconds( timout_ ? timout_ : 1000  ));
                tmout_timer_.async_wait(boost::bind(
                        &basis_iostream::io_handle_timout_expire, shared_from_this(),
                        boost::asio::placeholders::error));}
            else {
                ;}}

        void basis_iostream::tm_handle_timout_expire(const boost::system::error_code& err) {

            if (!err ) {
                is_timout      = true;
                is_error       = false;
                io_service_.stop();}
            else {
                is_timout      = false;
                error_cod      = err.value();
                is_error       = true;
                io_service_.stop();}}

        void basis_iostream::handle_write(const boost::system::error_code& err,
                size_t bytes_transferred) {

            if (!err) {
                tmout_timer_.cancel();
                io_service_.stop();
                is_timout      = false;
                is_error       = false;}

            else {
                tmout_timer_.cancel();
                checkerror(err);
                error_cod      = err.value();
                is_error       = true;
                io_service_.stop();
                is_data_ready  = false;
                DEBUG_STR_DVNCI(is errror handle_write!!!)}}

        void basis_iostream::handle_read(const boost::system::error_code& err, size_t bytes_transferred) {
            if (!err) {
                tmout_timer_.cancel();
                io_service_.stop();
                bytes_trans = bytes_transferred;
                is_timout      = false;
                is_data_ready  = (bytes_transferred > 0);
                is_error       = false;}
            else {
                DEBUG_VAL_DVNCI(err.message())
                tmout_timer_.cancel();
                checkerror(err);
                error_cod      = err.value();
                is_error       = true;
                io_service_.stop();
                is_data_ready  = false;}}

        ns_error basis_iostream::write(const std::string& vl, timeouttype tmout) {
            checkconnect();
            if (state_ == connected) {

                is_timout       = false;
                is_data_ready   = false;
                is_error        = false;
                is_connect      = true;
                error_cod       = 0;

                try {

                    set_wb(vl);

                    io_service_.reset();

                    //DEBUG_STR_DVNCI(SET ASYNCWRITE)

                    write_impl();

                    //DEBUG_STR_DVNCI(SET ASYNCTIME)

                    tmout_timer_.expires_from_now(boost::posix_time::milliseconds(tmout ? tmout : timout()  ));
                    tmout_timer_.async_wait(boost::bind(
                            &basis_iostream::io_handle_timout_expire, shared_from_this(),
                            boost::asio::placeholders::error));

                    //DEBUG_STR_DVNCI(SET RUN)

                    io_service_.run();}
                catch (dvncierror& errd) {
                    if (errd.code() == ERROR_IO_SERVICE_LOCK) throw errd;
                    return (errd.code());}
                catch (...) {
                    DEBUG_STR_DVNCI(ERROR RESULT);
                    return NS_ERROR_NODEF;}

                //DEBUG_STR_DVNCI(SET RESULT)

                if (is_timout) {
                    error_cod = ERROR_IO_TIMOUT_EXPIRE;
                    return error_cod;}

                if (is_error) {
                    error_cod = ERROR_FAILNET_CONNECTED;
                    return error_cod;}


                return 0;}
            return ERROR_IO_LINK_NOT_CONNECTION;}

        ns_error basis_iostream::read(std::string& vl,  size_t cnt, timeouttype tmout  ) {

            checkconnect();

            if (state_ == connected) {

                is_timout       = false;
                is_data_ready   = false;
                is_error        = false;
                is_connect      = true;
                error_cod       = 0;

                size_t need_cnt =  cnt;

                if (need_cnt) {
                    if (size_rb() > 0) {
                        if (size_rb() < need_cnt) {
                            need_cnt = need_cnt - size_rb();
                            get_rb(vl);}
                        else {
                            get_rb(vl, need_cnt);
                            return 0;}}}

                try {

                    io_service_.reset();

                    //DEBUG_STR_DVNCI(SET ASYNCWRITE)

                    read_impl(need_cnt);

                    //DEBUG_STR_DVNCI(SET ASYNCTIME)

                    tmout_timer_.expires_from_now(boost::posix_time::milliseconds( tmout ?  tmout : timout()));
                    tmout_timer_.async_wait(boost::bind(
                            &basis_iostream::io_handle_timout_expire, shared_from_this(),
                            boost::asio::placeholders::error));

                    //DEBUG_STR_DVNCI(SET RUN)


                    io_service_.run();}
                catch (dvncierror& errd) {
                    if (errd.code() == ERROR_IO_SERVICE_LOCK) throw errd;
                    return (errd.code());}
                catch (...) {
                    DEBUG_STR_DVNCI(ERROR RESULT);
                    return NS_ERROR_NODEF;}

                //DEBUG_STR_DVNCI(SET RESULT)

                if (is_timout) {
                    error_cod = ERROR_IO_TIMOUT_EXPIRE;
                    return error_cod;}

                if (is_error) {
                    error_cod = ERROR_FAILNET_CONNECTED;
                    return error_cod;}

                if (!is_data_ready) return ERROR_NULLRESPONSE;

                if (size_rb() < need_cnt) return ERROR_NULLRESPONSE;

                if (need_cnt)
                    get_rb(vl, need_cnt);
                else
                    get_rb(vl);


                return 0;}
            return ERROR_IO_LINK_NOT_CONNECTION;}

        std::string::size_type basis_iostream::get_rb(std::string& vl, std::string::size_type cnt) {
            check_rb(vl, cnt);
            return clear_rb(cnt);}

        std::string::size_type basis_iostream::check_rb(std::string& vl, std::string::size_type cnt) {
            cnt = (cnt == 0) ? readbuffer.size() : cnt;
            cnt = (cnt > readbuffer.size()) ? readbuffer.size() : cnt;
            vl = vl + std::string(boost::asio::buffer_cast<const char*>(readbuffer.data()), cnt);
            return cnt;}

        std::string::size_type basis_iostream::clear_rb(std::string::size_type cnt) {
            cnt = (cnt == 0) ? readbuffer.size() : cnt;
            cnt = (cnt > readbuffer.size()) ? readbuffer.size() : cnt;
            readbuffer.consume(cnt);
            return cnt;}

        std::string::size_type basis_iostream::set_wb(const std::string& vl, std::string::size_type cnt) {
            clear_wb();
            return add_wb(vl);}

        std::string::size_type basis_iostream::add_wb(const std::string& vl, std::string::size_type cnt) {
            cnt = (cnt == 0) ? vl.size() : cnt;
            cnt = (cnt > vl.size()) ? vl.size() : cnt;
            std::ostream os(&writebuffer);
            os << vl.substr(0, cnt);
            return cnt;}

        std::string::size_type basis_iostream::clear_wb(std::string::size_type cnt) {
            cnt = (cnt == 0) ? writebuffer.size() : cnt;
            cnt = (cnt > writebuffer.size()) ? writebuffer.size() : cnt;
            writebuffer.consume(cnt);
            return cnt;}




        //////////////////////////////////////////////////////////////////////////////////////////////

        void udpip_iostream::handle_read(const boost::system::error_code& err, size_t bytes_transferred) {
            if (!err) {
                tmout_timer_.cancel();
                io_service_.stop();
                bytes_trans = bytes_transferred;
                is_timout = false;
                is_data_ready = (bytes_transferred > 0);
                readbuffer.commit(bytes_transferred);
                is_error = false;}
            else {
                DEBUG_VAL_DVNCI(err.message())
                tmout_timer_.cancel();
                checkerror(err);
                error_cod = err.value();
                is_error = true;
                io_service_.stop();
                is_data_ready = false;}}



        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





}}
