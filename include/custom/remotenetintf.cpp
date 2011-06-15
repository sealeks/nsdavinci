/* 
 * File:   netintf.cpp
 * Author: Serg
 * 
 * Created on 20 Р�СЋР»СЊ 2010 Рі., 14:24
 */

#include <custom/remotenetintf.h>


namespace dvnci {
    namespace custom {
        namespace net {

            ns_error remotenetintf::auth_req( const std::string& user, const std::string& pass) {
                return 0;}

            ns_error remotenetintf::add_items( const vect_cid_key& cids, vect_sid_key& sids,  vect_error_item& errors) {
                try {
                    error(0);
                    req_add_items req;
                    resp_add_items resp;
                    assign_req_items(req, cids);
                    if (querytmpl<req_add_items, resp_add_items, RPC_OPERATION_REQ_ADD_ITEMS, RPC_OPERATION_RESP_ADD_ITEMS > (req, resp)) {
                        error(assign_resp_items(resp, sids, errors));}
                    else
                        error(ERROR_IO_NO_DATA);}
                catch (dvncierror& err_) {
                    error(err_.code());
                    if ((err_.code() == ERROR_FAILNET_CONNECTED) || 
                            (err_.code() == ERROR_NONET_CONNECTED)) 
                        throw err_;;}
                catch (...) {
                    error(NS_ERROR_ERRRESP);}
                return error();}

            ns_error remotenetintf::add_items_ex( const vect_cid_key_ex cids, vect_sid_key_ex& sids,  vect_error_ex_item& errors) {
                try {
                    error(0);
                    req_add_items_ex req;
                    resp_add_items_ex resp;
                    assign_req_items(req, cids);
                    if (querytmpl<req_add_items_ex, resp_add_items_ex, RPC_OPERATION_REQ_ADD_ITEMS_EX, RPC_OPERATION_RESP_ADD_ITEMS_EX > (req, resp)) {
                        error(assign_resp_items(resp, sids, errors));}
                    else
                        error(ERROR_IO_NO_DATA);}
                catch (dvncierror& err_) {
                    error(err_.code());
                    if ((err_.code() == ERROR_FAILNET_CONNECTED) || 
                            (err_.code() == ERROR_NONET_CONNECTED)) 
                        throw err_;}
                catch (...) {
                    error(NS_ERROR_ERRRESP);}
                return error();}

            ns_error remotenetintf::remove_items( const vect_num64& sids,  vect_num64& succ_sids , vect_error_item& errors) {
                try {
                    error(0);
                    req_remove_items req;
                    resp_remove_items resp;
                    assign_req_remitems(req, sids);
                    if (querytmpl<req_remove_items, resp_remove_items, RPC_OPERATION_REQ_REMOVE_ITEMS, RPC_OPERATION_RESP_REMOVE_ITEMS > (req, resp)) {
                        error(assign_resp_remitems(resp, succ_sids, errors));}
                    else
                        error(ERROR_IO_NO_DATA);}
                catch (dvncierror& err_) {
                    error(err_.code());
                    if ((err_.code() == ERROR_FAILNET_CONNECTED) || 
                            (err_.code() == ERROR_NONET_CONNECTED)) 
                        throw err_;}
                catch (...) {
                    error(NS_ERROR_ERRRESP);}
                return error();}

            ns_error remotenetintf::read_values (const vect_num64& sids, vect_data_item& lines , vect_data_item_str& linesstr, vect_error_item& errors) {
                try {
                    error(0);
                    req_data_item1 req;
                    resp_data_item resp;
                    assign_req_values(req, sids);
                    if (querytmpl<req_data_item1, resp_data_item , RPC_OPERATION_REQ_DATA_ITEM1, RPC_OPERATION_RESP_DATA_ITEM > (req, resp)) {
                        error(assign_resp_values(resp, lines , linesstr, errors));}
                    else
                        error(ERROR_IO_NO_DATA);}
                catch (dvncierror& err_) {
                    error(err_.code());
                    if ((err_.code() == ERROR_FAILNET_CONNECTED) || 
                            (err_.code() == ERROR_NONET_CONNECTED)) 
                        throw err_;}
                catch (...) {
                    error(NS_ERROR_ERRRESP);}
                return error();}

            ns_error remotenetintf::read_values(vect_data_item& lines , vect_data_item_str& linesstr, vect_error_item& errors) {
                try {
                    error(0);
                    req_data_item req;
                    resp_data_item resp;
                    assign_req_values(req);
                    if (querytmpl<req_data_item, resp_data_item , RPC_OPERATION_REQ_DATA_ITEM, RPC_OPERATION_RESP_DATA_ITEM > (req, resp)) {
                        error(assign_resp_values(resp, lines , linesstr, errors));}
                    else
                        error(ERROR_IO_NO_DATA);}
                catch (dvncierror& err_) {
                    error(err_.code());
                    if ((err_.code() == ERROR_FAILNET_CONNECTED) || 
                            (err_.code() == ERROR_NONET_CONNECTED)) 
                        throw err_;}
                catch (...) {
                    error(NS_ERROR_ERRRESP);}
                return error();}

            ns_error remotenetintf::read_values_ex(const vect_num64& rsids, vect_data_item& lines , vect_data_item_str& linesstr, vect_sid_key_ex& sids, vect_error_item& errors) {
                try {
                    error(0);
                    req_data_item_ex1 req;
                    resp_data_item_ex resp;
                    assign_req_values(req, rsids);
                    if (querytmpl<req_data_item_ex1, resp_data_item_ex , RPC_OPERATION_REQ_DATA_ITEM_EX1, RPC_OPERATION_RESP_DATA_ITEM_EX > (req, resp)) {
                        error(assign_resp_values(resp, lines , linesstr, sids, errors));}
                    else
                        error(ERROR_IO_NO_DATA);}
                catch (dvncierror& err_) {
                    error(err_.code());
                    if ((err_.code() == ERROR_FAILNET_CONNECTED) || 
                            (err_.code() == ERROR_NONET_CONNECTED)) 
                        throw err_;}
                catch (...) {
                    error(NS_ERROR_ERRRESP);}
                return error();}

            ns_error remotenetintf::read_values_ex(vect_data_item& lines , vect_data_item_str& linesstr, vect_sid_key_ex& sids, vect_error_item& errors) {
                try {
                    error(0);
                    req_data_item_ex req;
                    resp_data_item_ex resp;
                    assign_req_values(req);
                    if (querytmpl<req_data_item_ex, resp_data_item_ex , RPC_OPERATION_REQ_DATA_ITEM_EX, RPC_OPERATION_RESP_DATA_ITEM_EX > (req, resp)) {
                        assign_resp_values(resp, lines , linesstr, sids, errors);}
                    else
                        error(ERROR_IO_NO_DATA);}
                catch (dvncierror& err_) {
                    error(err_.code());
                    if ((err_.code() == ERROR_FAILNET_CONNECTED) || 
                            (err_.code() == ERROR_NONET_CONNECTED)) 
                        throw err_;}
                catch (...) {
                    error(NS_ERROR_ERRRESP);}
                return error();}

            ns_error remotenetintf::send_commands(const vect_command_data& cmds, vect_error_item& errors) {
                try {
                    error(0);
                    req_send_commands req;
                    resp_send_commands resp;
                    assign_req_commands(req, cmds);
                    if (querytmpl<req_send_commands, resp_send_commands , RPC_OPERATION_REQ_SEND_COMMANDS, RPC_OPERATION_RESP_SEND_COMMANDS > (req, resp)) {
                        assign_resp_commands(resp, errors);}
                    else
                        error(ERROR_IO_NO_DATA);}
                catch (dvncierror& err_) {
                    error(err_.code());
                    if ((err_.code() == ERROR_FAILNET_CONNECTED) || 
                            (err_.code() == ERROR_NONET_CONNECTED)) 
                        throw err_;}
                catch (...) {
                    error(NS_ERROR_ERRRESP);}
                return error();}

            ns_error remotenetintf::read_report(const vect_reporttask& tasks , vect_report_value_data& dt, vect_error_item& errors) {
                try {
                    error(0);
                    req_reporttask req;
                    resp_reporttask resp;
                    assign_req_reports(req, tasks);
                    if (querytmpl<req_reporttask, resp_reporttask , RPC_OPERATION_REQ_REPORTTASK, RPC_OPERATION_RESP_REPORTTASK > (req, resp)) {
                        error(assign_resp_reports(resp, dt,  errors));}
                    else
                        error(ERROR_IO_NO_DATA);}
                catch (dvncierror& err_) {
                    error(err_.code());
                    if ((err_.code() == ERROR_FAILNET_CONNECTED) || 
                            (err_.code() == ERROR_NONET_CONNECTED)) 
                        throw err_;}
                catch (...) {
                    error(NS_ERROR_ERRRESP);}
                return error();}

            ns_error remotenetintf::read_events(const vect_eventtask& tasks , vect_event_value_item& dt, vect_error_item& errors) {
                try {
                    error(0);
                    req_eventtask req;
                    resp_eventtask resp;
                    assign_req_events(req, tasks);
                    if (querytmpl<req_eventtask, resp_eventtask , RPC_OPERATION_REQ_EVENTTASK, RPC_OPERATION_RESP_EVENTTASK > (req, resp)) {
                        error(assign_resp_events(resp, dt,  errors));}
                    else
                        error(ERROR_IO_NO_DATA);}
                catch (dvncierror& err_) {
                    error(err_.code());
                    if ((err_.code() == ERROR_FAILNET_CONNECTED) || 
                            (err_.code() == ERROR_NONET_CONNECTED)) 
                        throw err_;}
                catch (...) {
                    error(NS_ERROR_ERRRESP);}
                return error();}

            ns_error remotenetintf::read_trend(const vect_trendtask& tasks, vect_trend_value_data& dt , vect_error_item& errors) {
                try {
                    error(0);
                    req_trendtask req;
                    resp_trendtask resp;
                    assign_req_trends(req, tasks);
                    if (querytmpl<req_trendtask, resp_trendtask , RPC_OPERATION_REQ_TRENDTASK, RPC_OPERATION_RESP_TRENDTASK > (req, resp)) {
                        error(assign_resp_trends(resp, dt,  errors));}
                    else
                        error(ERROR_IO_NO_DATA);}
                catch (dvncierror& err_) {
                    error(err_.code());
                    if ((err_.code() == ERROR_FAILNET_CONNECTED) || 
                            (err_.code() == ERROR_NONET_CONNECTED)) 
                        throw err_;}
                catch (...) {
                    error(NS_ERROR_ERRRESP);}
                return error();}

            ns_error remotenetintf::read_alarms(const unum64& guid, vect_alarms_data& dt) {
                try {
                    error(0);
                    req_alarms req;
                    resp_alarms resp;
                    assign_read_alarms(req, guid);
                    if (querytmpl<req_alarms, resp_alarms , RPC_OPERATION_REQ_ALARMS, RPC_OPERATION_RESP_ALARMS > (req, resp)) {
                        error(assign_resp_alarms(resp, dt));}
                    else
                        error(ERROR_IO_NO_DATA);}
                catch (dvncierror& err_) {
                    error(err_.code());
                    if ((err_.code() == ERROR_FAILNET_CONNECTED) || 
                            (err_.code() == ERROR_NONET_CONNECTED)) 
                        throw err_;}
                catch (...) {
                    error(NS_ERROR_ERRRESP);}
                return error();}

            ns_error remotenetintf::read_journal(const unum64& guid, const unum64& cursor, const unum64& cnt, vect_journal_data& dt) {
                try {
                    error(0);
                    req_journal req;
                    resp_journal resp;
                    assign_read_journal(req, guid, cursor, cnt);
                    if (querytmpl<req_journal, resp_journal , RPC_OPERATION_REQ_JOURNAL, RPC_OPERATION_RESP_JOURNAL > (req, resp)) {
                        error(assign_resp_journal(resp, dt));}
                    else
                        error(ERROR_IO_NO_DATA);}
                catch (dvncierror& err_) {
                    error(err_.code());
                    if ((err_.code() == ERROR_FAILNET_CONNECTED) || 
                            (err_.code() == ERROR_NONET_CONNECTED)) 
                        throw err_;}
                catch (...) {
                    error(NS_ERROR_ERRRESP);}
                return error();}
            
            
           ns_error remotenetintf::connect_impl(){
               try{
                if (!client_io) return error(ERROR_IO_DEVICE_CHANAL_NOT_DEF);
                if (client_io->state() == client_io->connected){
                    state_ = connected;
                    return error(0);}
                client_io->connect(host, port, tmout);
                state_ = (client_io->state() == client_io->connected ) ? connected :  disconnected;
                if (state_ == connected) {
                     return error(0);}
                else {
                    state_ = disconnected;
                    return error(ERROR_IO_LINK_NOT_CONNECTION);}}
                catch (...) {}
                state_ = disconnected;
                return error(ERROR_BASENOTFOUND);}

           ns_error remotenetintf::disconnect_impl(){
               try{
               if ((client_io) && (client_io->state() == client_io->connected)){
                   client_io->disconnect();}}
               catch (...) {}
               state_ = disconnected;
               return error(0);}           
            
            
}}}

