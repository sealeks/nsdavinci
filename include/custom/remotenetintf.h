
/* 
 * File:   netintf.h
 * Author: Serg
 *
 * Created on 20 Р пїЅРЎР‹Р В»РЎРЉ 2010 Р С–., 14:24
 */

#ifndef _DVNCI_REMOTENETINTF_H
#define	_DVNCI_REMOTENETINTF_H



#include <custom/netintf.h>
#include <kernel/rpcioclient.h>


#include <sstream>


namespace dvnci {
    namespace custom {
        namespace net {

            class remotenetintf : public netintf {
            public:

                remotenetintf(const std::string hst, const std::string prt, const std::string usr,
                        const std::string pswrd,   timeouttype tmo = DEFAULT_DVNCI_TIMOUT) : netintf(), client_io( new dvnci::rpc::rpcioclient()),
                host(hst), port(prt), user(usr), password(pswrd), tmout(tmo) {}

                virtual  ~remotenetintf() {};

                virtual ns_error auth_req( const std::string& user, const std::string& pass);
                virtual ns_error add_items( const vect_cid_key& cids, vect_sid_key& sids,  vect_error_item& errors);
                virtual ns_error add_items_ex( const vect_cid_key_ex cids, vect_sid_key_ex& sids,  vect_error_ex_item& errors);
                virtual ns_error remove_items( const vect_num64& sids,  vect_num64& succ_sids , vect_error_item& errors);
                virtual ns_error read_values( const vect_num64& sids, vect_data_item& lines , vect_data_item_str& linesstr, vect_error_item& errors);
                virtual ns_error read_values(vect_data_item& lines , vect_data_item_str& linesstr, vect_error_item& errors);
                virtual ns_error read_values_ex(const vect_num64& rsids, vect_data_item& lines , vect_data_item_str& linesstr, vect_sid_key_ex& sids, vect_error_item& errors);
                virtual ns_error read_values_ex(vect_data_item& lines , vect_data_item_str& linesstr, vect_sid_key_ex& sids, vect_error_item& errors);
                virtual ns_error send_commands(const vect_command_data& cmds, vect_error_item& errors);
                virtual ns_error read_report(const vect_reporttask& tasks , vect_report_value_data& dt, vect_error_item& errors);
                virtual ns_error read_events(const vect_eventtask& tasks , vect_event_value_item& dt, vect_error_item& errors);
                virtual ns_error read_trend(const vect_trendtask& tasks, vect_trend_value_data& dt , vect_error_item& errors);
                virtual ns_error read_alarms(const unum64& giud, vect_alarms_data& dt);
                virtual ns_error read_journal(const unum64& guid, const unum64& cursor, const unum64& cnt, vect_journal_data& dt);


            protected:
                
                
                virtual ns_error connect_impl();

                virtual ns_error disconnect_impl();

                template<class REQSTRUCT, class RESPSTRUCT, num16 reqtp, num16 resptp>
                bool querytmpl(REQSTRUCT& reqstruct, RESPSTRUCT& respstruct) {

                    try {
                        std::ostringstream out_archive_stream(std::ostringstream::binary);
                        std::istringstream in_archive_stream(std::istringstream::binary);
                        boost::archive::binary_oarchive out_archive(out_archive_stream);
                        out_archive << reqstruct;
                        dvnci::rpc::rpcmessage out_mess(out_archive_stream.str(), reqtp);
                        dvnci::rpc::rpcmessage in_mess;
                        client_io->req(out_mess, in_mess);
                        std::cout.flush();
                        if (in_mess.type() == resptp) {
                            in_archive_stream.str(in_mess.message());
                            boost::archive::binary_iarchive in_archive(in_archive_stream);
                            in_archive >> respstruct;}
                        else {
                            if (in_mess.type() == RPC_OPERATION_ERROR_OUTSIDE) {
                                error_outside tmperr;
                                in_archive_stream.str(in_mess.message());
                                boost::archive::binary_iarchive in_archive(in_archive_stream);
                                in_archive >> tmperr;
                                dvncierror err(static_cast<ns_error> (tmperr.error));
                            }}}
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
                timeouttype                   tmout;

} ;}}}

#endif	/* NETINTF_H */