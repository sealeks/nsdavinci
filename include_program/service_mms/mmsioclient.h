/* 
 * File:   ns_ioclient.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 17 РњР°СЂС‚ 2010 Рі., 0:05
 */

#ifndef _DVNCI_KRNL_NS_MMSCLIENT_H
#define	_DVNCI_KRNL_NS_MMSCLIENT_H



#include <boost/asio/read_at.hpp>

#include <kernel/utils.h>
#include <kernel/error.h>
#include <kernel/constdef.h>
#include <mms/mmssocket.h>


namespace prot9506 {

    typedef iso9506 protocol_type;
    typedef protocol_type::socket socket_type;
    typedef protocol_type::acceptor acceptor_type;
    typedef protocol_type::endpoint endpoint_type;
    typedef protocol_type::resolver resolver_type;
    typedef protocol_type::application_selector application_selector;   

    using dvnci::DEFAULT_DVNCI_TIMOUT;
    using dvnci::timeouttype;

    class mmsioclient;
    typedef boost::shared_ptr<mmsioclient> mmsioclient_ptr;

    class mmsioclient : public boost::enable_shared_from_this<mmsioclient> {

    public:

        enum connectionState {
            connected, disconnected
        };

        mmsioclient();

        virtual ~mmsioclient();

        connectionState state() {
            return state_;
        }

        void connect(const std::string hst, const std::string prt, const std::string opt, 
        timeouttype tmo = DEFAULT_DVNCI_TIMOUT);
        void disconnect();

        template<typename T>
        bool req(boost::shared_ptr<T> operation) {
            
            if (state_ == connected) {

                is_timout = false;
                is_data_ready = false;
                is_error = false;
                is_connect = true;
                error_cod = 0;

                io_service_.reset();

                DEBUG_STR_DVNCI(SET ASYNCWRITE)

                socket_.async_confirm_request(operation,
                        boost::bind(&mmsioclient::handle_cofirmreq_end<T>, this, operation));

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
                        io_service_.stop();
                    } catch (...) {
                    };
                    DEBUG_STR_DVNCI(ERROR_FAILNET_CONNECTED THROWING)
                            throw dvnci::dvncierror(dvnci::ERROR_FAILNET_CONNECTED);
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
                                throw dvnci::dvncierror(dvnci::ERROR_FAILNET_CONNECTED);
                    } else DEBUG_STR_VAL_DVNCI(reqerr, error_cod)
                    }
                return true;
            } else {
                
            };
            return false;           
        }
        
        template<typename T>
        void handle_cofirmreq_end(boost::shared_ptr<T> operation){
            io_service_.stop();
            tmout_timer.cancel();
            is_timout      = false;
            is_data_ready  = true;
            is_error       = false;
        }        
        
              
        const protocol_option & mmsoption() const;
        
        bool can_identyfy() const;        
        
        bool can_read() const;  

        bool can_write() const; 

       bool can_namedlist() const;        

    private:

        void handle_resolve(const boost::system::error_code& err,
                boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

        void handle_connect(const boost::system::error_code& err,
                boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

        void handle_timout_expire(const boost::system::error_code& err);


        boost::asio::io_service io_service_;
        prot9506::mms_socket socket_;
        connectionState state_;
        boost::asio::deadline_timer tmout_timer;
        timeouttype timout;

        volatile bool is_data_ready;
        volatile bool is_timout;
        volatile bool is_connect;
        volatile bool is_error;
        volatile int error_cod;
    
    };
}


#endif	/* _NS_IOCLIENT_H */

