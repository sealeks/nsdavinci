
#include "mmsioclient.h"


namespace prot9506 {

    const service_option_type MMS_SERVICE_OPTOION_CLNT = MMSO::serviceSupportOptions_status | MMSO::serviceSupportOptions_getNameList | MMSO::serviceSupportOptions_identify | MMSO::serviceSupportOptions_read | MMSO::serviceSupportOptions_write |
            MMSO::serviceSupportOptions_rename | MMSO::serviceSupportOptions_deleteNamedVariableList | MMSO::serviceSupportOptions_getVariableAccessAttributes | MMSO::serviceSupportOptions_informationReport;
    const parameter_option_type MMS_CBB_OPTION_CLNT = MMSO::parameterSupportOptions_str1 | MMSO::parameterSupportOptions_str2 | MMSO::parameterSupportOptions_valt | MMSO::parameterSupportOptions_valt |
            MMSO::parameterSupportOptions_vnam | MMSO::parameterSupportOptions_vadr | MMSO::parameterSupportOptions_tpy | MMSO::parameterSupportOptions_vlis;

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

    const protocol_option & mmsioclient::mmsoption() const {
        return socket_.mmsoption();
    }

    bool mmsioclient::can_identyfy() const {
        return !((protocol_option().service() | MMSO::serviceSupportOptions_identify).dynamic_bitset().none());
    }

    bool mmsioclient::can_read() const {
        return !((protocol_option().service() | MMSO::serviceSupportOptions_identify).dynamic_bitset().none());
    }

    bool mmsioclient::can_write() const {
        return !((protocol_option().service() | MMSO::serviceSupportOptions_identify).dynamic_bitset().none());
    }

    bool mmsioclient::can_namedlist() const {
        return !((protocol_option().service() | MMSO::serviceSupportOptions_identify).dynamic_bitset().none());
    }             
    
}



