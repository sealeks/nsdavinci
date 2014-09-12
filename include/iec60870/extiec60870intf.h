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

#include <iec60870/iec60870_PM.h>

namespace dvnci {

    namespace external {

        using dvnci::prot80670::iec60870_data_listener;
        using dvnci::prot80670::device_address;        
        using dvnci::prot80670::dataobject_ptr;
        using dvnci::prot80670::dataobject_vct;
        using dvnci::prot80670::iec60870_thread;
        using dvnci::prot80670::iec60870_thread_ptr;
        using dvnci::prot80670::iec_option;     
        using dvnci::prot80670::iec60870_data_listener_ptr;        

        class extiec60870intf : public extintf_wraper<dvnci::prot80670::dataobject_ptr>,
        public virtual iec60870_data_listener {

        public:

            extiec60870intf(tagsbase_ptr intf_, executor* exctr, indx grp);
            extiec60870intf(tagsbase_ptr intf_, executor* exctr, const indx_set& grps, const metalink& lnk);

            virtual ~extiec60870intf();
            
            virtual void execute60870(dataobject_ptr vl,  const ns_error& error = 0);            

            virtual void execute60870(const dataobject_vct& vl,  const ns_error& error = 0);

            virtual void execute60870(device_address dev,  const ns_error& error = 0);
            
            virtual void execute60870(const boost::system::error_code& err);

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

            iec60870_thread_ptr create_pm(const std::string& host, const std::string& port, const iec_option& opt, 
                    iec60870_data_listener_ptr listr);

            iec60870_thread_ptr create_pm(dvnci::prot80670::IEC_PROTOCOL prot, chnlnumtype chnm, const metalink & lnk, const iec_option& opt,
                    iec60870_data_listener_ptr listr);
            
            bool pm_connected() const;

            void kill_pm();

            iec60870_thread_ptr thread_io;
            dvnci::dvncierror fatal_;

        };
    }
}

#endif	/* EXTNETINTF_H */

