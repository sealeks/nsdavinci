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

        void connect(std::string host, std::string port, timeouttype tmo = DEFAULT_DVNCI_TIMOUT);
        void disconnect();
        //bool req(rpcmessage& msg, rpcmessage& resp);


    private:

        void handle_resolve(const boost::system::error_code& err,
                boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

        void handle_connect(const boost::system::error_code& err,
                boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

        void handle_write(const boost::system::error_code& err);

        void handle_readheader(const boost::system::error_code& err);

        void handle_endreq(const boost::system::error_code& err);

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

