
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
            
            void netintf::assign_req_auth(req_auth& req, num64 ver,  num64 intftp, const std::string& user, const std::string& pass) {
                req.intftp= intftp;
                req.user=user;
                req.pass=pass;}

            ns_error netintf::assign_resp_auth( resp_auth& resp) {
                return static_cast<ns_error>(resp.rslt);}

            void netintf::assign_req_items(req_add_items& req, const vect_cid_key& cids) {
                req.cids = cids;}

            ns_error netintf::assign_resp_items( resp_add_items& resp, vect_sid_key& sids,  vect_error_item& errors) {
                sids.swap(resp.sids);
                errors.swap(resp.errors);
                return static_cast<ns_error>(resp.rslt);}

            void netintf::assign_req_items(req_add_items_ex& req, const vect_cid_key_ex& cids) {
                req.cids = cids;}

            ns_error netintf::assign_resp_items( resp_add_items_ex& resp, vect_sid_key_ex& sids,  vect_error_ex_item& errors) {
                sids.swap(resp.sids);
                errors.swap(resp.errors);
                return static_cast<ns_error>(resp.rslt);}                

            void netintf::assign_req_remitems(req_remove_items& req, const vect_num64& cids) {
                req.cids = cids;}

            ns_error netintf::assign_resp_remitems( resp_remove_items& resp, vect_num64& succ_sids , vect_error_item& errors) {
                succ_sids.swap(resp.cids);
                errors.swap(resp.errors);
                return static_cast<ns_error>(resp.rslt);}

            void netintf::assign_req_values(req_data_item& req) {
                req.stub = 0;}

            void netintf::assign_req_values(req_data_item1& req, const vect_num64& sids) {
                req.sids = sids;}

            ns_error netintf::assign_resp_values( resp_data_item& resp, vect_data_item& lines , vect_data_item_str& linesstr, vect_error_item& errors) {
                lines.swap(resp.lines);
                linesstr.swap(resp.linesstr);
                errors.swap(resp.errors);
                 return static_cast<ns_error>(resp.rslt);}           

            void netintf::assign_req_values(req_data_item_ex& req) {
                req.stub = 0;}

            void netintf::assign_req_values(req_data_item_ex1& req, const vect_num64& sids) {
                req.sids = sids;}

            ns_error netintf::assign_resp_values( resp_data_item_ex& resp, vect_data_item& lines , vect_data_item_str& linesstr, vect_sid_key_ex& sids, vect_error_item& errors) {
                lines.swap(resp.lines);
                linesstr.swap(resp.linesstr);
                sids.swap(resp.fulllines);
                errors.swap(resp.errors);
                return static_cast<ns_error>(resp.rslt);}

            void netintf::assign_req_commands(req_send_commands& req, const vect_command_data& cmds) {
                req.cmds = cmds;}

            ns_error netintf::assign_resp_commands( resp_send_commands& resp, vect_error_item& errors) {
                errors.swap(resp.errors);
                return static_cast<ns_error>(resp.rslt);}               

            void netintf::assign_req_reports(req_reporttask& req, const vect_reporttask& tasks) {
                req.tasks = tasks;}

            ns_error netintf::assign_resp_reports( resp_reporttask& resp, vect_report_value_data& dt, vect_error_item& errors) {
                dt.swap(resp.datas);
                errors.swap(resp.errors);
                return static_cast<ns_error>(resp.rslt);}               

            void netintf::assign_req_events(req_eventtask& req, const vect_eventtask& tasks) {
                req.tasks = tasks;}

            ns_error netintf::assign_resp_events( resp_eventtask& resp, vect_event_value_item& dt, vect_error_item& errors) {
                dt.swap(resp.data);
                errors.swap(resp.errors);
                return static_cast<ns_error>(resp.rslt);}
            
            void netintf::assign_req_trends(req_trendtask& req, const vect_trendtask& tasks) {
                req.tasks = tasks;}

            ns_error netintf::assign_resp_trends( resp_trendtask& resp, vect_trend_value_data& dt , vect_error_item& errors) {
                dt.swap(resp.datas);
                errors.swap(resp.errors);
                return static_cast<ns_error>(resp.rslt);}               

            void netintf::assign_read_alarms(req_alarms& req, const unum64& guid) {
                req.vers = guid;}

            ns_error netintf::assign_resp_alarms( resp_alarms& resp, vect_alarms_data& dt) {
                dt.swap(resp.lines);
                return static_cast<ns_error>(resp.rslt);}                

            void netintf::assign_read_journal(req_journal& req, const unum64& guid, const unum64& cursor, const unum64& cnt) {
                req.guid = guid;
                req.cursor = cursor;
                req.cnt = cnt;}

            ns_error netintf::assign_resp_journal( resp_journal& resp, vect_journal_data& dt) {
                dt.swap(resp.lines);
                return static_cast<ns_error>(resp.rslt);}
            

            num16 netintf::generate_impl(req_auth& req, resp_auth& resp) {
                resp.rslt = auth_req(req.pass, req.user);
                return RPC_OPERATION_RESP_AUTH;}

            num16 netintf::generate_impl(req_add_items& req, resp_add_items& resp) {
                resp.rslt=static_cast<num64>(add_items(req.cids, resp.sids, resp.errors));
                return RPC_OPERATION_RESP_ADD_ITEMS;}

            num16 netintf::generate_impl(req_add_items_ex& req, resp_add_items_ex& resp) {
                resp.rslt=static_cast<num64>(add_items_ex(req.cids, resp.sids, resp.errors));
                return RPC_OPERATION_RESP_ADD_ITEMS_EX;}

            num16 netintf::generate_impl(req_remove_items& req, resp_remove_items& resp) {
                resp.rslt=static_cast<num64>(remove_items(req.cids, resp.cids, resp.errors));
                return RPC_OPERATION_RESP_REMOVE_ITEMS;}

            num16 netintf::generate_impl(req_data_item& req, resp_data_item& resp) {
                resp.rslt=static_cast<num64>(read_values(resp.lines, resp.linesstr, resp.errors));
                return RPC_OPERATION_RESP_DATA_ITEM;}

            num16 netintf::generate_impl(req_data_item1& req, resp_data_item& resp) {
                resp.rslt=static_cast<num64>(read_values(req.sids, resp.lines, resp.linesstr, resp.errors));
                return RPC_OPERATION_RESP_DATA_ITEM;}

            num16 netintf::generate_impl(req_data_item_ex& req, resp_data_item_ex& resp) {
                resp.rslt=static_cast<num64>(read_values_ex(resp.lines,  resp.linesstr, resp.fulllines, resp.errors));
                return RPC_OPERATION_RESP_DATA_ITEM_EX;}

            num16 netintf::generate_impl(req_data_item_ex1& req, resp_data_item_ex& resp) {
                resp.rslt=static_cast<num64>(read_values_ex(req.sids, resp.lines,  resp.linesstr, resp.fulllines, resp.errors));
                return RPC_OPERATION_RESP_DATA_ITEM_EX;}

            num16 netintf::generate_impl(req_send_commands& req, resp_send_commands& resp) {
                resp.rslt=static_cast<num64>(send_commands(req.cmds, resp.errors));
                return RPC_OPERATION_RESP_SEND_COMMANDS;}

            num16 netintf::generate_impl(req_reporttask& req, resp_reporttask& resp) {
                resp.rslt=static_cast<num64>(read_report(req.tasks , resp.datas, resp.errors));
                return RPC_OPERATION_RESP_REPORTTASK;}

            num16 netintf::generate_impl(req_eventtask& req, resp_eventtask& resp) {
                resp.rslt=static_cast<num64>(read_events(req.tasks , resp.data, resp.errors));
                return RPC_OPERATION_RESP_EVENTTASK;}

            num16 netintf::generate_impl(req_trendtask& req, resp_trendtask& resp) {
                resp.rslt=static_cast<num64>(read_trend(req.tasks , resp.datas, resp.errors));
                return RPC_OPERATION_RESP_TRENDTASK;}

            num16 netintf::generate_impl(req_alarms& req, resp_alarms& resp) {
                resp.rslt=static_cast<num64>(read_alarms(req.vers , resp.lines));
                return RPC_OPERATION_RESP_ALARMS;}

            num16 netintf::generate_impl(req_journal& req, resp_journal& resp) {
                resp.rslt=static_cast<num64>(read_journal(req.guid , req.cursor, req.cnt, resp.lines));
                return RPC_OPERATION_RESP_JOURNAL;}
}}}

