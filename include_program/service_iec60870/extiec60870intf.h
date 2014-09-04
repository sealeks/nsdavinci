/* 
 * File:   extnetintf.h
 * Author: Alexeev
 *
 * Created on 14 �?юнь 2011 г., 16:16
 */

#ifndef EXTIEC60850INTF_H
#define	EXTIEC60850INTF_H

#include <kernel/constdef.h>
#include <kernel/error.h>
#include <kernel/memfile.h>
#include <kernel/templ.h>
#include <kernel/utils.h>
#include <kernel/short_value.h>
#include <kernel/interface_proccesstmpl.h>
#include <kernel/extintf_wraper.h>

#include "iec60870ioclient.h"

namespace dvnci {

    namespace external {

        using dvnci::prot80670::iec60870_data_listener;
        using dvnci::prot80670::dataobject_ptr;
        using dvnci::prot80670::dataobject_vct;
        using dvnci::prot80670::iec60870_thread;
        using dvnci::prot80670::iec60870_thread_ptr;

        class extiec60870intf : public extintf_wraper<dvnci::prot80670::dataobject_ptr>,
        public virtual iec60870_data_listener {

        public:

            extiec60870intf(tagsbase_ptr intf_, executor* exctr, indx grp);

            virtual ~extiec60870intf();

            virtual void execute60870(dataobject_ptr vl);

            virtual void execute60870(const dataobject_vct& vl);

            virtual void execute60870(const boost::system::error_code& error);

            virtual void terminate60870();


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

        private:

            iec60870_thread_ptr create_pm(std::string host, std::string port, timeouttype tmo,
                    dvnci::prot80670::iec60870_data_listener_ptr listr);
            
            bool pm_connected() const;

            void kill_pm();

            iec60870_thread_ptr thread_io;
            dvnci::dvncierror fatal_;

        };
    }
}

#endif	/* EXTNETINTF_H */

