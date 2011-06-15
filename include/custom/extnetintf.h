/* 
 * File:   extnetintf.h
 * Author: Alexeev
 *
 * Created on 14 Июнь 2011 г., 16:16
 */

#ifndef EXTNETINTF_H
#define	EXTNETINTF_H

#include "kernel/constdef.h"
#include "kernel/error.h"
#include "kernel/memfile.h"
#include "kernel/templ.h"
#include "kernel/utils.h"
#include "kernel/short_value.h"
#include "kernel/interface_proccesstmpl.h"
#include "kernel/extintf_wraper.h"

#include "custom/netfactory.h"

namespace dvnci {
    namespace external {
        namespace net {

    class extnetintf  :  public extintf_wraper<num64>{
        
    public:
        
        extnetintf(tagsbase_ptr intf_, executor* exctr, indx grp);

        virtual ~extnetintf();



    protected:
                

        virtual ns_error checkserverstatus(); 
                

        virtual ns_error connect_impl();

        virtual ns_error disconnect_impl();


        virtual ns_error add_request_impl();

        virtual ns_error remove_request_impl();

        virtual ns_error value_request_impl();
        
        virtual ns_error command_request_impl(const sidcmd_map& cmds); 

        virtual ns_error report_request_impl();

        virtual ns_error event_request_impl();
        
        dvnci::custom::net::netintf_ptr   netintf;};


        }}}

#endif	/* EXTNETINTF_H */

