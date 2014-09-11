/* 
 * File:   extnetintf.h
 * Author: Alexeev
 *
 * Created on 14 Июнь 2011 г., 16:16
 */

#ifndef EXTMMSINTF_H
#define	EXTMMSINTF_H

#include "mmsintf.h"

namespace dvnci {

    namespace external {

        class exmmsintf : public extintf_wraper<objectname_ptr> {

        public:

            explicit exmmsintf(tagsbase_ptr intf_, executor* exctr, indx grp);
            explicit exmmsintf(tagsbase_ptr intf_, executor* exctr, const indx_set& grps, const metalink& lnk);

            virtual ~exmmsintf();


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
            
            mmsintf_ptr remintf;

        };
    }
}

#endif	/* EXTNETINTF_H */

