
/* 
 * File:   netintf.h
 * Author: Serg
 *
 * Created on 20 Р пїЅРЎР‹Р В»РЎРЉ 2010 Р С–., 14:24
 */

#ifndef _DVNCI_NETINTF_H
#define	_DVNCI_NETINTF_H

#include <kernel/constdef.h>
#include <kernel/error.h>
#include <kernel/systemutil.h>
#include <kernel/utils.h>
#include <kernel/interface_proccesstmpl.h>

#include <custom/netstruct.h>





namespace dvnci {
    namespace custom {
        namespace net {

            const num64 NET_INTF_VERSION = 1;

            inline static num64 packdata(vlvtype vld, tagtype tp,  ns_error err, bool al=false,  bool kv=false) {
                return  (((0xF & static_cast<num64> ((al ? 0x1 : 0x0) | (kv ? 0x2 : 0x0)) ) << 48) & 0xF000000000000LL) |
                        (((0xFFFF & static_cast<num64> (err) ) << 32) & 0xFFFF00000000LL) |
                        (((0xFF & static_cast<num64> (vld) ) << 16) & 0xFF0000LL) | 
                        (0xFFFF & tp);}

            inline static vlvtype unpackvalid(num64 v ) {
                return static_cast<vlvtype> (((v & 0xFF0000LL) >> 16) & 0xFF);}

            inline static tagtype unpacktagtype(num64 v ) {
                return static_cast<tagtype> (v & 0xFFFF);}
            
            inline static ns_error unpackerror(num64 v ) {
                return static_cast<ns_error> (((v & 0xFFFF00000000LL) >> 32) & 0xFFFF);}

            inline static bool unpackalarm(num64 v) {
                return ((static_cast<num8> (v >> 48) & 0x3) & 0x1);}

            inline static bool unpackkvit(num64 v) {
                return ((static_cast<num8> (v >> 48) & 0x3) & 0x2);}



            class netintf {
            public:
                
                friend class netsession;
                
                enum intfstate {
                     disconnected, connected};

                netintf() : state_(disconnected), error_(ERROR_NONET_CONNECTED)  {};

                virtual  ~netintf() {};
                
                bool isconnected(){
                     return ((state_ == connected) || (!error(connect_impl())));};
   
                bool disconnect(){
                     return ((state_ != connected) || (!error(disconnect_impl())));}
                
                ns_error  error() const {
                     return error_;}

                
                virtual ns_error auth_req( const std::string& user, const std::string& pass) = 0;
                
                virtual ns_error add_items( const vect_cid_key& cids, vect_sid_key& sids,  vect_error_item& errors) = 0;

                virtual ns_error add_items_ex( const vect_cid_key_ex& cids, vect_sid_key_ex& sids,  vect_error_ex_item& errors) {
                    return 0;};
                virtual ns_error remove_items( const vect_num64& sids,  vect_num64& succ_sids , vect_error_item& errors) = 0;
                virtual ns_error read_values( const vect_num64& sids, vect_data_item& lines , vect_data_item_str& linesstr, vect_error_item& errors) = 0;
                virtual ns_error read_values(vect_data_item& lines , vect_data_item_str& linesstr, vect_error_item& errors) = 0;
                virtual ns_error read_values_ex(const vect_num64& rsids, vect_data_item& lines , vect_data_item_str& linesstr, vect_sid_key_ex& sids, vect_error_item& errors) = 0;
                virtual ns_error read_values_ex(vect_data_item& lines , vect_data_item_str& linesstr, vect_sid_key_ex& sids, vect_error_item& errors) = 0;
                virtual ns_error send_commands(const vect_command_data& cmds, vect_error_item& errors) = 0;
                virtual ns_error read_report(const vect_reporttask& tasks , vect_report_value_data& dt, vect_error_item& errors) = 0;
                virtual ns_error read_events(const vect_eventtask& tasks , vect_event_value_item& dt, vect_error_item& errors) = 0;
                virtual ns_error read_trend(const vect_trendtask& tasks, vect_trend_value_data& dt , vect_error_item& errors) =  0;
                virtual ns_error read_alarms(const unum64& giud, vect_alarms_data& dt) =  0;
                virtual ns_error read_journal(const unum64& guid, const unum64& cursor, const unum64& cnt, vect_journal_data& dt) =  0;

                virtual void setaddress(const boost::asio::ip::address& adr){}

            protected:
                
                num16 generate_impl(req_auth& req, resp_auth& resp);
                num16 generate_impl(req_add_items& req, resp_add_items& resp);
                num16 generate_impl(req_add_items_ex& req, resp_add_items_ex& resp);
                num16 generate_impl(req_remove_items& req, resp_remove_items& resp);
                num16 generate_impl(req_data_item& req, resp_data_item& resp);
                num16 generate_impl(req_data_item1& req, resp_data_item& resp);
                num16 generate_impl(req_data_item_ex& req, resp_data_item_ex& resp);
                num16 generate_impl(req_data_item_ex1& req, resp_data_item_ex& resp);
                num16 generate_impl(req_send_commands& req, resp_send_commands& resp);
                num16 generate_impl(req_reporttask& req, resp_reporttask& resp);
                num16 generate_impl(req_eventtask& req, resp_eventtask& resp);
                num16 generate_impl(req_trendtask& req, resp_trendtask& resp);
                num16 generate_impl(req_alarms& req, resp_alarms& resp);
                num16 generate_impl(req_journal& req, resp_journal& resp);
                
                void assign_req_auth(req_auth& req, num64 ver,  num64 intftp, const std::string& user, const std::string& pass);
                ns_error assign_resp_auth(resp_auth& resp);
                void assign_req_items(req_add_items& req, const vect_cid_key& cids);
                ns_error assign_resp_items( resp_add_items& resp, vect_sid_key& sids,  vect_error_item& errors);
                void assign_req_items(req_add_items_ex& req, const vect_cid_key_ex& cids);
                ns_error assign_resp_items( resp_add_items_ex& resp, vect_sid_key_ex& sids,  vect_error_ex_item& errors);
                void assign_req_remitems(req_remove_items& req, const vect_num64& cids);
                ns_error assign_resp_remitems( resp_remove_items& resp, vect_num64& succ_sids , vect_error_item& errors);
                void assign_req_values(req_data_item& req);
                void assign_req_values(req_data_item1& req, const vect_num64& sids);
                ns_error assign_resp_values( resp_data_item& resp, vect_data_item& lines , vect_data_item_str& linesstr, vect_error_item& errors);
                void assign_req_values(req_data_item_ex& req);
                void assign_req_values(req_data_item_ex1& req, const vect_num64& sids);
                ns_error assign_resp_values( resp_data_item_ex& resp, vect_data_item& lines , vect_data_item_str& linesstr, vect_sid_key_ex& sids, vect_error_item& errors);
                void assign_req_commands(req_send_commands& req, const vect_command_data& cmds);
                ns_error assign_resp_commands( resp_send_commands& resp, vect_error_item& errors);
                void assign_req_reports(req_reporttask& req, const vect_reporttask& tasks);
                ns_error assign_resp_reports( resp_reporttask& resp, vect_report_value_data& dt, vect_error_item& errors);
                void assign_req_events(req_eventtask& req, const vect_eventtask& tasks);
                ns_error assign_resp_events( resp_eventtask& resp, vect_event_value_item& dt, vect_error_item& errors);
                void assign_req_trends(req_trendtask& req, const vect_trendtask& tasks);
                ns_error assign_resp_trends( resp_trendtask& resp, vect_trend_value_data& dt , vect_error_item& errors);
                void assign_read_alarms(req_alarms& req, const unum64& giud);
                ns_error assign_resp_alarms( resp_alarms& resp, vect_alarms_data& dt);
                void assign_read_journal(req_journal& req, const unum64& guid, const unum64& cursor, const unum64& cnt);
                ns_error assign_resp_journal( resp_journal& resp, vect_journal_data& dt);
                
                
                
                virtual ns_error connect_impl() = 0;

                virtual ns_error disconnect_impl() = 0;
                
                ns_error  error(ns_error err){
                          return error_=err;}
                
                intfstate          state_;
                ns_error           error_;};


}}}

#endif	/* NETINTF_H */
