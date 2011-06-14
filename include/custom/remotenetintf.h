/* 
 * File:   netintf.h
 * Author: Serg
 *
 * Created on 20 Р пїЅРЎР‹Р В»РЎРЉ 2010 Р С–., 14:24
 */

#ifndef _DVNCI_REMOTENETINTF_H
#define	_DVNCI_REMOTENETINTF_H



#include <custom/netintf.h>



namespace dvnci {
    namespace custom {
        namespace net {



            class remotenetintf : public netintf {
                
         
                    
            public:

                    
                remotenetintf(tagsbase_ptr inf) : netintf()  {};
                
                virtual  ~remotenetintf() {};



                virtual ns_error auth_req( const std::string& user, const std::string& user);
                virtual ns_error add_items( const vect_cid_key& cids, vect_sid_key& sids,  vect_error_info& errors);
                virtual ns_error add_items_ex( const vect_cid_key_ex cids, vect_sid_key_ex& sids,  vect_error_ex_info& errors);  
                virtual ns_error remove_items( const vect_num64& sids,  vect_num64& succ_sids , vect_error_info& errors);
                virtual ns_error req_data_item( const vect_num64& sids, vect_data_item& lines , vect_data_item_str& linesstr, vect_error_info& errors);
                virtual ns_error req_data_item(vect_data_item& lines , vect_data_item_str& linesstr, vect_error_info& errors);                
                virtual ns_error req_data_item_ex( const vect_num64& sids, vect_data_item& lines , vect_data_item_str& linesstr, vect_sid_key_ex& sids, vect_error_info& errors);
                virtual ns_error req_data_item_ex(vect_data_item& lines , vect_data_item_str& linesstr, vect_sid_key_ex& sids, vect_error_info& errors);    
                virtual ns_error req_send_commands(const vect_command_data& cmds, vect_error_info& errors);                
                virtual ns_error req_report(const vect_reporttask& tasks ,vect_report_value_data& dt, vect_error_info& errors);                
                virtual ns_error req_event(const vect_eventtask& tasks ,vect_event_value_item& dt, vect_error_info& errors);
                virtual ns_error req_trend(const vect_trendtask& tasks,vect_report_value_data& dt , vect_error_info& errors);
                virtual ns_error req_alarms(const unum64& giud, vect_alarms_data& dt);
                virtual ns_error req_journal(const unum64& guid, const unum64& cursor, const unum64& cnt,vect_journal_data& dt);
   


} ;
}}}

#endif	/* NETINTF_H */

