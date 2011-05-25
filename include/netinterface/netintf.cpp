/* 
 * File:   netintf.cpp
 * Author: Serg
 * 
 * Created on 20 Р�СЋР»СЊ 2010 Рі., 14:24
 */

#include <netinterface/netintf.h>

namespace dvnci{
namespace net{

void netintf::assign_req_items(req_items& req,const vect_client_item& clientitem){
    req.ver=NET_INTF_VERSION;
    req.cl_items.assign(clientitem.begin(),clientitem.end());}

void netintf::assign_resp_items(const resp_items& resp,vect_server_item& serveritem,vect_error_item& errors){
    serveritem.assign(resp.srv_items.begin(),resp.srv_items.end());
    errors.assign(resp.errors.begin(),resp.errors.end());}

void netintf::assign_req_values(req_values& req,const num64_vect& servids){
    req.ver=NET_INTF_VERSION;
    req.srv_ids.assign(servids.begin(),servids.end());}

void netintf::assign_resp_values(const resp_values& resp, vect_value_item& values, vect_report_value_items& reportvalues, vect_error_item& errors){
    values.assign(resp.items.begin(),resp.items.end());
    reportvalues.assign(resp.repitems.begin(),resp.repitems.end());
    errors.assign(resp.errors.begin(),resp.errors.end());}

void netintf::assign_req_values_ex(req_values_ex& req){
    req.ver=NET_INTF_VERSION;}

void netintf::assign_resp_values_ex(const resp_values_ex& resp, vect_value_item& values, vect_report_value_items& reportvalues){
    values.assign(resp.items.begin(),resp.items.end());
	//if (!resp.repitems.empty())
    reportvalues.assign(resp.repitems.begin(),resp.repitems.end());}

void netintf::assign_req_remitems(req_remitems& req,const num64_vect& delitem){
    req.ver=NET_INTF_VERSION;
    req.outkey.assign(delitem.begin(),delitem.end());}

void netintf::assign_resp_remitems(const resp_remitems& resp,vect_error_item& errors){
    errors.assign(resp.errors.begin(),resp.errors.end());}

void netintf::assign_req_commands(req_commands& req, const vect_command_item& commanditem){
    req.ver=NET_INTF_VERSION;
    req.commands.assign(commanditem.begin(),commanditem.end());}

void netintf::assign_resp_remitems(const resp_commands& resp,vect_error_item& errors){
       errors.assign(resp.errors.begin(),resp.errors.end());}

void netintf::assign_req_reporttask(req_reporttask& req,indx  key, datetime start, datetime stop){
    req.ver=NET_INTF_VERSION;
    req.key=static_cast<num64>(key);
    req.start=castnum64_from_datetime(start);
    req.stop=castnum64_from_datetime(stop);}

void netintf::assign_resp_reporttask(const resp_reporttask& resp, ns_error& err){
    err=static_cast<ns_error>(resp.error);}

num16 netintf::generate_impl(req_items& req, resp_items& resp){
     add_items(req.cl_items, resp.srv_items, resp.errors);
     return RPC_OPERATION_RESP_ITEMS;
 }

num16 netintf::generate_impl(req_values& req, resp_values& resp){
    vect_event_value_item tmpstub;
     read_values(req.srv_ids, resp.items, resp.repitems, tmpstub, resp.errors);
     return RPC_OPERATION_RESP_VALUES;
 }

num16 netintf::generate_impl(req_values_ex& req, resp_values_ex& resp){
     vect_event_value_item tmpstub;
     read_values(resp.items, resp.repitems, tmpstub);
     return RPC_OPERATION_RESP_VALUES_EX;
 }

num16 netintf::generate_impl(req_remitems& req, resp_remitems& resp){
     remove_items(req.outkey, resp.errors);
     return RPC_OPERATION_RESP_REMITEMS;
}

num16 netintf::generate_impl(req_commands& req, resp_commands& resp){
     add_commands(req.commands, resp.errors);
     return RPC_OPERATION_RESP_COMMANDS;
}

num16 netintf::generate_impl(req_reporttask& req, resp_reporttask& resp){
      add_report_task(static_cast<num64>(req.key), cast_datetime_fromnum64(req.start), cast_datetime_fromnum64(req.stop));
      resp.error=0;
      return RPC_OPERATION_RESP_REPORTTASK;
}



}
}

