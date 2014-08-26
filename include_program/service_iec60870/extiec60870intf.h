/* 
 * File:   extnetintf.h
 * Author: Alexeev
 *
 * Created on 14 �?юнь 2011 г., 16:16
 */

#ifndef EXTIEC60850INTF_H
#define	EXTIEC60850INTF_H

#include "iec60870intf.h"

namespace dvnci {

    namespace external {

        class extiec60870intf : public extintf_wraper<dvnci::prot80670::dataobject_ptr> {

        public:

            extiec60870intf(tagsbase_ptr intf_, executor* exctr, indx grp);

            virtual ~extiec60870intf();


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

            dvnci::prot80670::iec60870intf_ptr remintf;

        };
    }
}

#endif	/* EXTNETINTF_H */

