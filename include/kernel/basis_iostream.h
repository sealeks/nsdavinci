/* 
 * File:   driver_iostream.h
 * Author: Serg
 *
 * Created on 26 Октябрь 2010 г., 12:54
 */



#ifndef _DVNCI_KRNL_LINK_IO_SERVICE_H
#define	_DVNCI_KRNL_LINK_IO_SERVICE_H

#include <kernel/constdef.h>
#include <kernel/error.h>
#include <kernel/utils.h>
#include <kernel/mainstruct.h>

#include <boost/asio/read_at.hpp>
#include <boost/asio/serial_port.hpp>

#if defined(_DVN_WIN_)
#include <winbase.h>
#elif defined(_DVN_LIN_)
#include <termios.h>
#include <unistd.h>
#else
#error Error define OS spec
#endif



namespace dvnci {
    namespace driver {

#if defined(_DVN_WIN_)        
        typedef ::DCB com_port_option;
#elif defined(_DVN_LIN_)
        typedef ::termios com_port_option;
#endif       

        void set_rs232_cominill(com_port_option& opt);
        void set_rs232_baudrate(com_port_option& opt, const baudratetype& br);
        void set_rs232_comoption(com_port_option& opt, size_t databit, const rsparitytype& prt, const rsstopbittype&  stpbt);
        void set_rs232_flowcontrol(com_port_option& opt, bool vl);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Базовый установщик настроек com  -  порта*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct com_option_setter {

            com_option_setter(const metalink & lnk) : link(lnk) {};

            virtual ~com_option_setter() {};

            virtual boost::system::error_code store(com_port_option& opt, boost::system::error_code & ec) const {
                return boost::system::error_code();}

            virtual boost::system::error_code load(com_port_option& opt, boost::system::error_code & ec) {
                return boost::system::error_code();}

            virtual baudratetype boundrate() const {
                return link.inf().cominf.boundrate;}

            void reset_default_nill(com_port_option & opt) const {
                set_rs232_cominill(opt);}

        protected:
            metalink link;} ;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Базовый класс потока ввода-вывода*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class basis_iostream : public boost::enable_shared_from_this<basis_iostream> {
        public:

            enum connectionstate {
                connected, disconnected} ;

            basis_iostream(timeouttype tout, bool echor = false);

            virtual ~basis_iostream() {};

            ns_error open();

            ns_error close();

            connectionstate state() const {
                return state_;}

            bool isconnected() const {
                return (state() == connected);}


            virtual ns_error write(const std::string& vl, timeouttype tmout = 0);
            virtual ns_error read(std::string& vl, size_t cnt = 0, timeouttype tmout = 0);

            virtual ns_error read_until(std::string& vl, const char delim, timeouttype tmout = 0) {
                return read_until_tmpl<const char>(vl, delim, tmout);}

            virtual ns_error read_until(std::string& vl, const std::string& delim, timeouttype tmout = 0) {
                return read_until_tmpl<const std::string&>(vl, delim, tmout);}

            virtual ns_error read_until(std::string& vl, const boost::regex& rgx, timeouttype tmout = 0) {
                return read_until_tmpl<const boost::regex&>(vl, rgx, tmout);}

            virtual bool char_silence(double charcout) {
                return true;}

            ns_error error() const {
                return error_cod;}

            ns_error error(ns_error err) {
                return error_cod = err;}

            timeouttype timout() const {
                return timout_;}

            void clearbuff();

            virtual size_t clearbuff_deep(timeouttype tmo = 10, size_t cnt = 1);

        protected:

            boost::asio::io_service& io_service() {
                return io_service_;}

            ns_error checkconnect() {
                return error ( state() == connected ? 0 : connect_impl());}

            virtual bool connect_impl() = 0;

            virtual bool disconnect_impl() = 0;

            virtual void write_impl() = 0;
            virtual void cancel_impl() = 0;
            virtual void read_impl(size_t cnt) = 0;

            virtual void read_until_impl(const char criteria) = 0;
            virtual void read_until_impl(const std::string& criteria) = 0;
            virtual void read_until_impl(const boost::regex& criteria) = 0;

            bool timout_sec(timeouttype sec);
            bool timout_millisec(timeouttype mls);
            bool timout_micsec(timeouttype mcs);

            virtual void checkerror(const boost::system::error_code& err) {};

            template <typename criteriatype>
            ns_error read_until_tmpl(std::string& vl, criteriatype criteria, timeouttype tmout = 0) {

                checkconnect();

                if (state_ == connected) {


                    is_timout = false;
                    is_data_ready = false;
                    is_error = false;
                    is_connect = true;
                    error_cod = 0;

                    try {

                        io_service_.reset();

                        //DEBUG_STR_DVNCI(SET ASYNCREADUNTIL)

                        read_until_impl(criteria);

                        //DEBUG_STR_DVNCI(SET ASYNCTIME)

                        tmout_timer_.expires_from_now(boost::posix_time::milliseconds( (!tmout) ? timout() : tmout));
                        tmout_timer_.async_wait(boost::bind(
                                &basis_iostream::io_handle_timout_expire, shared_from_this(),
                                boost::asio::placeholders::error));


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

                    get_rb(vl);
                    error_cod = 0;

                    return 0;}
                return ERROR_IO_LINK_NOT_CONNECTION;}

            void io_handle_timout_expire(const boost::system::error_code& err);
            void tm_handle_timout_expire(const boost::system::error_code& err);

            virtual void handle_read(const boost::system::error_code& err, size_t bytes_transferred);
            void handle_write(const boost::system::error_code& err, size_t bytes_transferred);

            std::string::size_type size_rb() const {
                return readbuffer.size();}

            std::string::size_type get_rb(std::string& vl, std::string::size_type cnt = 0);

            std::string::size_type check_rb(std::string& vl, std::string::size_type cnt = 0);

            std::string::size_type clear_rb(std::string::size_type cnt = 0);

            std::string::size_type size_wb() const {
                return writebuffer.size();}

            std::string::size_type set_wb(const std::string& vl, std::string::size_type cnt = 0);

            std::string::size_type add_wb(const std::string& vl, std::string::size_type cnt = 0);

            std::string::size_type clear_wb(std::string::size_type cnt = 0);




            boost::asio::io_service     io_service_;
            boost::asio::deadline_timer tmout_timer_;
            size_t                      bytes_trans;
            volatile bool               is_data_ready;
            volatile bool               is_timout;
            volatile bool               is_connect;
            volatile bool               is_error;
            volatile ns_error           error_cod;
            volatile connectionstate    state_;
            timeouttype                 timout_;
            bool                        echorespopse_;
            boost::asio::streambuf      readbuffer;
            boost::asio::streambuf      writebuffer;} ;

        typedef boost::shared_ptr<basis_iostream> basis_iostream_ptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Базовый шаблон  потока ввода-вывода IP*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template<typename SOCKETIMPL>
        class ip_iostream : public basis_iostream {
        protected:

            typedef SOCKETIMPL                                                       socket_type;
            typedef typename SOCKETIMPL::protocol_type                               protocol_type;
            typedef boost::asio::ip::basic_endpoint<protocol_type>                   endpoint_type;
            typedef boost::asio::ip::basic_resolver<protocol_type>                   resolver_type;
            typedef boost::asio::ip::basic_resolver_query<protocol_type>             resolver_query_type;
            typedef typename boost::asio::ip::basic_resolver_iterator<protocol_type> resolver_iterator_type;

        public:

            ip_iostream(timeouttype tout, std::string hst, std::string prt) :
            basis_iostream(tout, false), socket_(io_service_), host(hst), port(prt) {}

            boost::shared_ptr<ip_iostream> shared_from_this() {
                return boost::static_pointer_cast<ip_iostream > (basis_iostream::shared_from_this());}


        protected:

            void handle_resolve(const boost::system::error_code& err,
                    resolver_iterator_type endpoint_iterator) {
                if (!err) {

                    endpoint_type endpoint = *endpoint_iterator;
                    socket_.async_connect(endpoint,
                            boost::bind(&ip_iostream::handle_connect, shared_from_this(),
                            boost::asio::placeholders::error, ++endpoint_iterator));}
                else {
                    tmout_timer_.cancel();
                    is_timout = false;
                    is_connect = false;
                    error_cod = err.value();
                    is_error = true;
                    io_service_.stop();
                    DEBUG_STR_DVNCI(isErrorReesolve!!!)}}

            void handle_connect(const boost::system::error_code& err,
                    resolver_iterator_type endpoint_iterator) {

                if (!err) {
                    tmout_timer_.cancel();
                    is_timout = false;
                    is_connect = true;
                    is_error = false;
                    io_service_.stop();
                    DEBUG_STR_DVNCI(isConnected!!!)}
                else
                    if (endpoint_iterator != resolver_iterator_type()) {
                    socket_.close();
                    endpoint_type endpoint = *endpoint_iterator;
                    socket_.async_connect(endpoint,
                            boost::bind(&ip_iostream::handle_connect, shared_from_this(),
                            boost::asio::placeholders::error, ++endpoint_iterator));}
                else {
                    tmout_timer_.cancel();
                    is_timout = false;
                    is_connect = false;
                    is_error = false;
                    io_service_.stop();}}

            void connect_handle_timout_expire(const boost::system::error_code& err) {

                if (!err) {
                    if (is_timout) {
                        io_service_.stop();
                        throw dvncierror(ERROR_IO_SERVICE_LOCK);}
                    socket_.close();
                    is_timout = true;
                    is_data_ready = false;
                    is_connect = false;
                    is_error = true;
                    tmout_timer_.expires_from_now(boost::posix_time::milliseconds(1000));
                    tmout_timer_.async_wait(boost::bind(
                            &ip_iostream::connect_handle_timout_expire, shared_from_this(),
                            boost::asio::placeholders::error));
                    DEBUG_STR_DVNCI(TM_TIMEOUT EXPIRE)}
                else {
                    is_timout = false;
                    is_data_ready = false;
                    error_cod = err.value();
                    is_error = false;}}

            virtual void cancel_impl() {
                socket_.cancel();}

            virtual void checkerror(const boost::system::error_code& err) {
                if ((err.value() == 10053) || (err.value() == 10054)) {
                    socket_.close();
                    state_ = disconnected;
                    error_cod = ERROR_NONET_CONNECTED;
                    is_connect = false;}}

            virtual bool connect_impl() {
                if (isconnected()) return true;
                timeouttype tim_out = in_bounded<timeouttype > (50, 600000, timout());
                DEBUG_STR_DVNCI(ioclient connect)
                DEBUG_VAL_DVNCI(host)
                DEBUG_VAL_DVNCI(port)
                DEBUG_VAL_DVNCI(tim_out)
                resolver_type resolver(io_service_);
                resolver_query_type query(host.c_str(), port.c_str());

                is_timout = false;
                is_connect = false;
                is_error = false;
                error_cod = 0;

                try {

                    io_service_.reset();

                    //DEBUG_STR_DVNCI(START ASYNC RESOLVER)

                    resolver.async_resolve(query,
                            boost::bind(&ip_iostream::handle_resolve, shared_from_this(),
                            boost::asio::placeholders::error, boost::asio::placeholders::iterator));

                    //DEBUG_STR_DVNCI(START ASYNC CONNECTTIMER)

                    tmout_timer_.expires_from_now(boost::posix_time::milliseconds(tim_out));
                    tmout_timer_.async_wait(boost::bind(
                            &ip_iostream::connect_handle_timout_expire, shared_from_this(),
                            boost::asio::placeholders::error));

                    //DEBUG_STR_DVNCI(START WAIT)

                    io_service_.run();}
                catch (...) {
                    state_ = disconnected;
                    error_cod = ERROR_NONET_CONNECTED;
                    return false;}


                if (!is_connect) {
                    state_ = disconnected;
                    error_cod = ERROR_NONET_CONNECTED;
                    return false;}
                error_cod = NS_ERROR_SUCCESS;
                state_ = connected;
                clearbuff();
                return true;}

            virtual bool disconnect_impl() {
                if (isconnected()) return true;
                state_ = disconnected;
                socket_.close();
                io_service_.stop();
                return true;}


            socket_type socket_;
            std::string host;
            std::string port;} ;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Класс потока ввода-вывода TCP/IP*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class tcpip_iostream : public ip_iostream<boost::asio::ip::tcp::socket> {
        public:

            tcpip_iostream(timeouttype tout, std::string hst, std::string prt) :
            ip_iostream<boost::asio::ip::tcp::socket>(tout, hst, prt) {}

            boost::shared_ptr<tcpip_iostream> shared_from_this() {
                return boost::static_pointer_cast<tcpip_iostream > (basis_iostream::shared_from_this());}

        protected:

            virtual void read_impl(size_t cnt) {
                if (cnt == 0) boost::asio::async_read(socket_, readbuffer, boost::asio::transfer_all(),
                        boost::bind(&tcpip_iostream::handle_read, shared_from_this(), boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
                else boost::asio::async_read(socket_, readbuffer, boost::asio::transfer_at_least(cnt),
                        boost::bind(&tcpip_iostream::handle_read, shared_from_this(), boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));}

            virtual void write_impl() {
                boost::asio::async_write(socket_, writebuffer,
                        boost::bind(&tcpip_iostream::handle_write, shared_from_this(),
                        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));}

            virtual void read_until_impl(const char criteria) {
                boost::asio::async_read_until(socket_, readbuffer, criteria,
                        boost::bind(&tcpip_iostream::handle_read, shared_from_this(), boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));}

            virtual void read_until_impl(const std::string& criteria) {
                boost::asio::async_read_until(socket_, readbuffer, criteria,
                        boost::bind(&tcpip_iostream::handle_read, shared_from_this(), boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));}

            virtual void read_until_impl(const boost::regex& criteria) {
                boost::asio::async_read_until(socket_, readbuffer, criteria,
                        boost::bind(&tcpip_iostream::handle_read, shared_from_this(), boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));}} ;



        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Класс потока ввода-вывода UDP/IP*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class udpip_iostream : public ip_iostream<boost::asio::ip::udp::socket> {
        public:

            udpip_iostream(timeouttype tout, std::string hst, std::string prt, size_t defbuffsz = 1024) :
            ip_iostream<boost::asio::ip::udp::socket>( tout, hst, prt), defbuffsize_(defbuffsz)/*,
				udpreadbufs(readbuffer.prepare(defbuffsize_)) */ {
                ;}

            boost::shared_ptr<udpip_iostream> shared_from_this() {
                return boost::static_pointer_cast<udpip_iostream > (basis_iostream::shared_from_this());}



        protected:

            virtual void write_impl() {

                socket_.async_send(writebuffer.data(),
                        boost::bind(&udpip_iostream::handle_write, shared_from_this(),
                        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));}

            virtual void read_impl(size_t cnt) {
                readbuffer.consume(readbuffer.size());
                socket_.async_receive(readbuffer.prepare(defbuffsize_),
                        boost::bind(&udpip_iostream::handle_read, shared_from_this(), boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));}

            virtual void read_until_impl(const char criteria) {
                read_impl(0);}

            virtual void read_until_impl(const std::string& criteria) {
                read_impl(0);}

            virtual void read_until_impl(const boost::regex& criteria) {
                read_impl(0);}

            virtual void handle_read(const boost::system::error_code& err, size_t bytes_transferred);

        private:

            size_t defbuffsize_;} ;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Класс потока ввода-вывода Com порта*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template<typename OPTIONSETTER>
        class rs_iostream : public basis_iostream {
        public:

            rs_iostream(const metalink& lnk, timeouttype tout, chnlnumtype chnum, bool echor = false) :
            basis_iostream(tout, echor), serialport_(io_service_), serialport_io_sevice(io_service_), chnum_(chnum), optsetter(lnk) {}

            boost::shared_ptr<rs_iostream> shared_from_this() {
                return boost::static_pointer_cast<rs_iostream > (basis_iostream::shared_from_this());}

            bool setoption(const OPTIONSETTER& opt) {
                try {
                    serialport_.set_option<OPTIONSETTER > (opt);
                    boundrate_ = opt.boundrate();
                    return true;}
                catch (...) {
                    return false;}};

            virtual bool char_silence(double charcout) {
                double silenseto_tmp = (boundrate_ * 1.0) / 8;
                if (silenseto_tmp <= 10) return false;
                silenseto_tmp = 1000.0 / silenseto_tmp * charcout;
                timeouttype silenseto_msec = static_cast<timeouttype> (silenseto_tmp);
                return timout_millisec(silenseto_msec);}


        protected:

            virtual bool  connect_impl() {
                if (isconnected()) return true;
                timeouttype timout = in_bounded<timeouttype > (10, 600000, timout_);
                DEBUG_STR_DVNCI(ioclient connect)
                DEBUG_VAL_DVNCI(chnum_)
                DEBUG_VAL_DVNCI(timout)
                if (!chnum_) {
                    state_ = disconnected;
                    error_cod = ERROR_IO_CHANNOOPEN;
                    return false;}
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
                        return false;}
                    try {
                        if (!setoption(optsetter)) {
                            serialport_.close();
                            state_ = disconnected;
                            error_cod = ERROR_IO_CHANNOOPEN;}}
                    catch (boost::system::system_error err) {
                        serialport_.close();
                        state_ = disconnected;
                        error_cod = ERROR_IO_CHANNOOPEN;}}
                catch (boost::system::system_error err) {
                    state_ = disconnected;
                    error_cod = ERROR_IO_CHANNOOPEN;
                    return false;}
                catch (...) {
                    state_ = disconnected;
                    error_cod = ERROR_IO_CHANNOOPEN;
                    return false;}
                state_ = connected;
                /*COMMTIMEOUTS cmt;
                cmt.ReadIntervalTimeout=MAXDWORD;
                cmt.ReadTotalTimeoutMultiplier=MAXDWORD;
                cmt.ReadTotalTimeoutConstant=0;
                cmt.WriteTotalTimeoutMultiplier=MAXDWORD;
                cmt.WriteTotalTimeoutConstant=0;
                SetCommTimeouts(serialport_.native(),&cmt);*/
                error_cod = 0;
                clearbuff();
                return true;}

            virtual bool disconnect_impl() {
                if (!isconnected()) return true;
                state_ = disconnected;
                serialport_.close();
                io_service_.stop();
                return true;}

            virtual void write_impl() {
                boost::asio::async_write(serialport_, writebuffer,
                        boost::bind(&rs_iostream<OPTIONSETTER>::handle_write, basis_iostream::shared_from_this(),
                        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));}

            virtual void read_impl(size_t cnt) {
                if (cnt == 0) boost::asio::async_read(serialport_, readbuffer, boost::asio::transfer_all(),
                        boost::bind(&rs_iostream<OPTIONSETTER>::handle_read, shared_from_this(), boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
                else boost::asio::async_read(serialport_, readbuffer, boost::asio::transfer_at_least(cnt),
                        boost::bind(&rs_iostream<OPTIONSETTER>::handle_read, shared_from_this(), boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));}

            virtual void cancel_impl() {
                serialport_.cancel();}

            virtual void read_until_impl(const char criteria) {
                boost::asio::async_read_until(serialport_, readbuffer, criteria,
                        boost::bind(&rs_iostream<OPTIONSETTER>::handle_read, shared_from_this(), boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));}

            virtual void read_until_impl(const std::string& criteria) {
                boost::asio::async_read_until(serialport_, readbuffer, criteria,
                        boost::bind(&rs_iostream<OPTIONSETTER>::handle_read, shared_from_this(), boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));}

            virtual void read_until_impl(const boost::regex& criteria) {
                boost::asio::async_read_until(serialport_, readbuffer, criteria,
                        boost::bind(&rs_iostream<OPTIONSETTER>::handle_read, shared_from_this(), boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));}

            boost::asio::serial_port         serialport_;
            boost::asio::serial_port_service serialport_io_sevice;
            chnlnumtype                      chnum_;
            bool                             flowcontrol_;
            OPTIONSETTER                     optsetter;
            baudratetype                     boundrate_;} ;}}

#endif	/* driver_service.h_H */

