/* 
 * File:   netintf.h
 * Author: Serg
 *
 * Created on 20 Р�СЋР»СЊ 2010 Рі., 14:24
 */

#ifndef _DVNCI_REMOTENETINTF_H
#define	_DVNCI_REMOTENETINTF_H



#include <kernel/rpcioclient.h>

#include <netinterface/netintf.h>

#include <sstream>


namespace dvnci {
    namespace net {

        class remotenetintf : public netintf {

        public:

            remotenetintf(const std::string host_, const std::string port_, const std::string user_,
                    const std::string password_,   int tmout_ = DEFAULT_DVNCI_TIMOUT) : netintf(), client_io( new dvnci::rpc::rpcioclient()),
                            host(host_),port(port_),user(user_),password(password_),tmout(tmout_){}

            virtual ~remotenetintf() {};

            virtual bool connect() {
                DEBUG_VAL_DVNCI((_state == connected))
                if (_state == connected) {
                    return true;}
                connect_();
                return (_state == connected);};

            virtual bool disconnect() {
                if (_state == disconnected) {
                    return true;}
                disconnect_();
                return (_state == disconnected);};


            virtual bool add_items     (const vect_client_item& clientitem, vect_server_item& serveritem, vect_error_item& errors);
            virtual bool read_values    (const num64_vect& servids, vect_value_item& values, vect_report_value_items& reportvalues, vect_event_value_item& eventvalues, vect_error_item& errors);
            virtual bool read_values    (vect_value_item& values, vect_report_value_items& reportvalues, vect_event_value_item& eventvalues);
            virtual bool remove_items     (const num64_vect& delitem, vect_error_item& errors);
            virtual bool add_commands  (const vect_command_item& commanditem, vect_error_item& errors);
            virtual bool add_report_task(num64  key, datetime start, datetime stop);

        protected:

            bool connect_();
            bool disconnect_();

            template<class _REQSTRUCT, class _RESPSTRUCT, num16 _reqtp, num16 _resptp>
            bool querytmpl(_REQSTRUCT& reqstruct_, _RESPSTRUCT& respstruct_) {

                try {
                    std::ostringstream out_archive_stream(std::ostringstream::binary);
                    std::istringstream in_archive_stream(std::istringstream::binary);
                    boost::archive::binary_oarchive out_archive(out_archive_stream);
                    out_archive << reqstruct_;
                    dvnci::rpc::rpcmessage out_mess(out_archive_stream.str(), _reqtp);
                    dvnci::rpc::rpcmessage in_mess;
                    client_io->req(out_mess, in_mess);
                    std::cout.flush();
                    if (in_mess.type() == _resptp) {
                        in_archive_stream.str(in_mess.message());
                        boost::archive::binary_iarchive in_archive(in_archive_stream);
                        in_archive >> respstruct_;}
                    else {
                        if (in_mess.type() == RPC_OPERATION_ERROR_OUTSIDE) {
                            error_outside tmperr;
                            in_archive_stream.str(in_mess.message());
                            boost::archive::binary_iarchive in_archive(in_archive_stream);
                            in_archive >> tmperr;
                            dvncierror err(static_cast<ns_error> (tmperr.error));
                            /*adderror(err);*/}}}
                catch (dvncierror& err) {
                    if ((err.code() == ERROR_FAILNET_CONNECTED) || (err.code() == ERROR_NONET_CONNECTED)) throw err;
                    return false;}
                catch (...) {
                    return false;}
                return true;};


        private:
            dvnci::rpc::rpcioclient_ptr   client_io;
            std::string                   host;
            std::string                   port;
            std::string                   user;
            std::string                   password;
            int tmout;} ;}}

#endif	/* NETINTF_H */

