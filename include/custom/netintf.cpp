/* 
 * File:   netintf.cpp
 * Author: Serg
 * 
 * Created on 20 Р�СЋР»СЊ 2010 Рі., 14:24
 */

#include <custom/netintf.h>


namespace dvnci {
    namespace custom {
        namespace net {

            void netintf::assign_req_items(req_add_items& req, const vect_cid_key& cids) {
                req.cids = cids;}

            void netintf::assign_resp_items(const resp_add_items& resp, vect_sid_key& sids,  vect_error_info& errors) {
                sids=resp.sids;
                errors=resp.errors;}
            
            void netintf::assign_req_items(req_add_items_ex& req, const vect_cid_key_ex& cids) {
                req.cids = cids;}

            void netintf::assign_resp_items(const resp_add_items_ex& resp, vect_sid_key& sids,  vect_error_info& errors) {
                sids=resp.sids;
                errors=resp.errors;}
            
            void netintf::assign_req_remitems(req_remove_items& req, const vect_num64& cids){
                req.cids=cids;}
            
            void netintf::assign_resp_remitems(const resp_remove_items& resp, vect_num64& succ_sids , vect_error_info& errors){
                succ_sids=resp.cids;
                errors=resp.errors;}

            void netintf::assign_req_values(req_values& req, const num64_vect& servids) {
                req.ver = NET_INTF_VERSION;
                req.srv_ids.assign(servids.begin(), servids.end());}

            void netintf::assign_resp_values(const resp_values& resp, vect_value_item& values, vect_report_value_items& reportvalues, vect_error_item& errors) {
                values.assign(resp.items.begin(), resp.items.end());
                reportvalues.assign(resp.repitems.begin(), resp.repitems.end());
                errors.assign(resp.errors.begin(), resp.errors.end());}

            void netintf::assign_req_values_ex(req_values_ex& req) {
                req.ver = NET_INTF_VERSION;}

            void netintf::assign_resp_values_ex(const resp_values_ex& resp, vect_value_item& values, vect_report_value_items& reportvalues) {
                values.assign(resp.items.begin(), resp.items.end());
                //if (!resp.repitems.empty())
                reportvalues.assign(resp.repitems.begin(), resp.repitems.end());}

            void netintf::assign_req_remitems(req_remitems& req, const num64_vect& delitem) {
                req.ver = NET_INTF_VERSION;
                req.outkey.assign(delitem.begin(), delitem.end());}

            void netintf::assign_resp_remitems(const resp_remitems& resp, vect_error_item& errors) {
                errors.assign(resp.errors.begin(), resp.errors.end());}

            void netintf::assign_req_commands(req_commands& req, const vect_command_item& commanditem) {
                req.ver = NET_INTF_VERSION;
                req.commands.assign(commanditem.begin(), commanditem.end());}

            void netintf::assign_resp_remitems(const resp_commands& resp, vect_error_item& errors) {
                errors.assign(resp.errors.begin(), resp.errors.end());}

            void netintf::assign_req_reporttask(req_reporttask& req, indx  key, datetime start, datetime stop) {
                req.ver = NET_INTF_VERSION;
                req.key = static_cast<num64> (key);
                req.start = castnum64_from_datetime(start);
                req.stop = castnum64_from_datetime(stop);}

            void netintf::assign_resp_reporttask(const resp_reporttask& resp, ns_error& err) {
                err = static_cast<ns_error> (resp.error);}
            
            
            

            num16 netintf::generate_impl(req_auth& req, resp_auth& resp) {
                ns_error err = auth_req(req.pass,req.user);
                error_info err = {0 , 0};
                resp.error = err;
                return RPC_OPERATION_RESP_AUTH;}

            num16 netintf::generate_impl(req_add_items& req, resp_add_items& resp) {
                add_items(req.cids, resp.sids, resp.errors);
                return RPC_OPERATION_RESP_ADD_ITEMS;}

            num16 netintf::generate_impl(req_add_items_ex& req, resp_add_items_ex& resp) {
                add_items(req.cids, resp.sids, resp.errors);
                return RPC_OPERATION_RESP_ADD_ITEMS_EX;}

            num16 netintf::generate_impl(req_remove_items& req, resp_remove_items& resp) {
                remove_items(req.cids, resp.errors);
                return RPC_OPERATION_RESP_REMOVE_ITEMS;}

            num16 netintf::generate_impl(req_data_item& req, resp_data_item& resp) {
                req_data_item(resp.lines, resp.linesstr, resp.errors);
                return RPC_OPERATION_REQ_DATA_ITEM;}

            num16 netintf::generate_impl(req_data_item1& req, resp_data_item& resp) {
                req_data_item(req.sids, resp.lines, resp.linesstr, resp.errors);
                return RPC_OPERATION_REQ_DATA_ITEM;}
            
            num16 netintf::generate_impl(req_data_item_ex& req, resp_data_item_ex& resp) {
                req_data_item_ex(resp.lines,  resp.strlines, resp.fulllines, resp.errors);
                return RPC_OPERATION_REQ_DATA_ITEM_EX;}

            num16 netintf::generate_impl(req_data_item_ex1& req, resp_data_item_ex& resp) {
                req_data_item_ex(req.sids, resp.lines,  resp.strlines, resp.fulllines, resp.errors);
                return RPC_OPERATION_REQ_DATA_ITEM_EX;}
            
            num16 netintf::generate_impl(req_send_commands& req, resp_send_commands& resp) {
                req_send_commands(req.cmds, resp.errors);
                return RPC_OPERATION_RESP_SEND_COMMANDS;}
            
            num16 netintf::generate_impl(req_reporttask& req, resp_reporttask& resp) {
                req_report(req.tasks , resp.datas, resp.errors);
                return RPC_OPERATION_RESP_REPORTTASK;}
                 
            num16 netintf::generate_impl(req_eventtask& req, resp_eventtask& resp) {
                req_event(req.tasks , resp.data, resp.errors);
                return RPC_OPERATION_RESP_EVENTTASK;}  
            
            num16 netintf::generate_impl(req_trendtask& req, resp_trendtask& resp) {
                req_trend(req.tasks , resp.datas, resp.errors);
                return RPC_OPERATION_RESP_TRENDTASK;}  
            
            num16 netintf::generate_impl(req_alarms& req, resp_alarms& resp) {
                req_report(req.vers , resp.lines);
                return RPC_OPERATION_RESP_ALARMS;}  
            
            num16 netintf::generate_impl(req_journal& req, resp_journal& resp) {
                req_trend(req.guid , req.cursor, req.cnt, resp.lines);
                return RPC_OPERATION_RESP_JOURNAL;}             

}}}

