/* 
 * File:   netintf.h
 * Author: Serg
 *
 * Created on 20 Р�СЋР»СЊ 2010 Рі., 14:24
 */

#ifndef _DVNCI_NETINTF_H
#define	_DVNCI_NETINTF_H

#include <kernel/constdef.h>
#include <kernel/error.h>
#include <kernel/memfile.h>
#include <kernel/systemutil.h>
#include <kernel/interface_proccesstmpl.h>

#include <netinterface/rpcnetstruct.h>




namespace dvnci{
namespace net{

const num64 NET_INTF_VERSION=1;

struct event_value_item {
  num64  outkey;
  num64  val;
  num64  time;};

typedef std::vector<event_value_item > vect_event_value_item;

class netintf;

typedef intrusive_sync_share_ptr_tmpl<netintf>      netintf_ptr;

class netintf : public externalintf< client_item, server_item, error_item,
                                    num64, value_item, report_value_items, 
                                    report_value_item, event_value_item,
                                    command_item > {
public:


    netintf() : externalintf< client_item, server_item, error_item,
                                    num64, value_item, report_value_items,
                                    report_value_item, event_value_item,
                                    command_item >(){};

    virtual netintf_ptr clone_share(){
       throw dvncierror(ERROR_NO_CLONE);
       return netintf_ptr();}

    
    num16 generate_impl(req_items& req, resp_items& resp);
    num16 generate_impl(req_values& req, resp_values& resp);
    num16 generate_impl(req_values_ex& req, resp_values_ex& resp);
    num16 generate_impl(req_remitems& req, resp_remitems& resp);
    num16 generate_impl(req_commands& req, resp_commands& resp);
    num16 generate_impl(req_reporttask& req, resp_reporttask& resp);

protected:

    void assign_req_items(req_items& req, const vect_client_item& clientitem);
    void assign_resp_items(const resp_items& resp,vect_server_item& serveritem,vect_error_item& errors);
    void assign_req_values(req_values& req,const num64_vect& servids);
    void assign_resp_values(const resp_values& resp, vect_value_item& values, vect_report_value_items& reportvalues, vect_error_item& errors);
    void assign_req_values_ex(req_values_ex& req);
    void assign_resp_values_ex(const resp_values_ex& resp, vect_value_item& values, vect_report_value_items& reportvalues);
    void assign_req_remitems(req_remitems& req,const num64_vect& delitem);
    void assign_resp_remitems(const resp_remitems& resp,vect_error_item& errors);
    void assign_req_commands(req_commands& req, const vect_command_item& commanditem);
    void assign_resp_remitems(const resp_commands& resp,vect_error_item& errors);
    void assign_req_reporttask(req_reporttask& req,indx  key, datetime start, datetime stop);
    void assign_resp_reporttask(const resp_reporttask& resp, ns_error& err);
};

}
}

#endif	/* NETINTF_H */

