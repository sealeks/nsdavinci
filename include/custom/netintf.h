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
#include <kernel/memfile.h>
#include <kernel/systemutil.h>
#include <kernel/interface_proccesstmpl.h>

#include <custom/netstruct.h>





namespace dvnci {
    namespace custom {
        namespace net {
            
        const num64 NET_INTF_VERSION = 1;
            

        inline static num64 packdata(vlvtype vld, tagtype tp ){
            num64 vld64=static_cast<num64>(vld);
            return (((0xFF & vld64 ) <<32) & 0xFF00000000LL) | (0xFFFFFFFF & tp);}
        
        inline static vlvtype unpackvalid(num64 v ){
               return static_cast<vlvtype>(((v & 0xFF00000000LL) >> 32) & 0xFF);}
        
        inline static tagtype unpacktagtype(num64 v ){
               return static_cast<tagtype>(v & 0xFFFFFFFF);}
        
        inline static num64 packdata1(vlvtype vld, tagtype tp, bool al,  bool kv){
            num64 alinf=(al ? 0x1 : 0x0) | (kv ? 0x2 : 0x0);
            num64 vld64=static_cast<num64>(vld);
            return (((alinf <<48) & 0xF000000000000LL)) | ((vld64 <<32) & 0xFF00000000LL) | (0xFFFFFFFF & tp);}
        
        inline static bool unpackalarm(num64 v){
            num8 alinf=static_cast<num8>(v >> 48) & 0x3;
            return (alinf & 0x1);}
        
        inline static bool unpackkvit(num64 v){
            num8 vldinf=static_cast<num8>(v >> 48) & 0x3;
            return (vldinf & 0x2);}
        
        

            class netintf;

            typedef intrusive_sync_share_ptr_tmpl<netintf>      netintf_ptr;

            class netintf {
            public:
             

                netintf() {};
                
                virtual  ~netintf() {};

                //virtual netintf_ptr clone_share() {
                 //   throw dvncierror(ERROR_NO_CLONE);
                 //   return netintf_ptr();}

                virtual ns_error auth_req( const std::string& user, const std::string& user) = 0;
                virtual ns_error add_items( const vect_cid_key& cids, vect_sid_key& sids,  vect_error_info& errors) = 0;
                virtual ns_error add_items_ex( const vect_cid_key_ex& cids, vect_sid_key_ex& sids,  vect_error_ex_info& errors) = 0;  
                virtual ns_error remove_items( const vect_num64& sids,  vect_num64& succ_sids , vect_error_info& errors) = 0;
                virtual ns_error req_data_item( const vect_num64& cids, vect_data_item& lines , vect_data_item_str& linesstr, vect_error_info& errors) = 0;
                virtual ns_error req_data_item(vect_data_item& lines , vect_data_item_str& linesstr, vect_error_info& errors) = 0;                
                virtual ns_error req_data_item_ex( const vect_num64& cids, vect_data_item& lines , vect_data_item_str& linesstr, vect_sid_key_ex& sids, vect_error_info& errors) = 0;
                virtual ns_error req_data_item_ex(vect_data_item& lines , vect_data_item_str& linesstr, vect_sid_key_ex& sids, vect_error_info& errors) = 0;    
                virtual ns_error req_send_commands(const vect_command_data& cmds, vect_error_info& errors) = 0;                
                virtual ns_error req_report(const vect_reporttask& tasks ,vect_report_value_data& dt, vect_error_info& errors) = 0;                
                virtual ns_error req_event(const vect_eventtask& tasks ,vect_event_value_item& dt, vect_error_info& errors) = 0;
                virtual ns_error req_trend(const vect_trendtask& tasks,vect_report_value_data& dt , vect_error_info& errors) =  0;
                virtual ns_error req_alarms(const unum64& giud, vect_alarms_data& dt) =  0;
                virtual ns_error req_journal(const unum64& guid, const unum64& cursor, const unum64& cnt,vect_journal_data& dt) =  0;
   
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

            protected:

                void assign_req_items(req_add_items& req, const vect_cid_key& cids);
                void assign_resp_items(const resp_add_items& resp, vect_sid_key& sids,  vect_error_info& errors);
                void assign_req_items(req_add_items_ex& req, const vect_cid_key_ex& cids);
                void assign_resp_items(const resp_add_items_ex& resp, vect_sid_key& sids,  vect_error_info& errors);
                void assign_req_remitems(req_remove_items& req, const vect_num64& cids);
                void assign_resp_remitems(const resp_remove_items& resp, vect_num64& succ_sids , vect_error_info& errors);
                void assign_req_values(req_values& req, const num64_vect& servids);
                void assign_resp_values(const resp_values& resp, vect_value_item& values, vect_report_value_items& reportvalues, vect_error_item& errors);
                void assign_req_values_ex(req_values_ex& req);
                void assign_resp_values_ex(const resp_values_ex& resp, vect_value_item& values, vect_report_value_items& reportvalues);
                void assign_req_remitems(req_remitems& req, const num64_vect& delitem);
                void assign_resp_remitems(const resp_remitems& resp, vect_error_item& errors);
                void assign_req_commands(req_commands& req, const vect_command_item& commanditem);
                void assign_resp_remitems(const resp_commands& resp, vect_error_item& errors);
                void assign_req_reporttask(req_reporttask& req, indx  key, datetime start, datetime stop);
                void assign_resp_reporttask(const resp_reporttask& resp, ns_error& err);} ;
}}}

#endif	/* NETINTF_H */

