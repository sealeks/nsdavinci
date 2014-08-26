/* 
 * File:   extnetintf.h
 * Author: Alexeev
 *
 * Created on 14 �?юнь 2011 г., 16:16
 */

#ifndef IEC60850INTF_H
#define	IEC60850INTF_H

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

    namespace prot80670 {




        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec69870intf
        /////////////////////////////////////////////////////////////////////////////////////////////////        


        class iec69870intf;
        typedef boost::shared_ptr<iec69870intf> iec69870intf_ptr;

        class iec69870intf {

        public:

            enum intfstate {

                disconnected, connected
            };

            iec69870intf(const std::string hst, const std::string prt, timeouttype tmo = DEFAULT_DVNCI_TIMOUT);

            virtual ~iec69870intf() {
            };

            static iec69870intf_ptr build(const std::string host, const std::string port, timeouttype tmout = DEFAULT_DVNCI_TIMOUT);

            bool isconnected() {
                return ((state_ == connected) || (!error(connect_impl())));
            };

            bool disconnect() {
                return ((state_ != connected) || (!error(disconnect_impl())));
            }

            ns_error error() const {
                return error_;
            }

            ns_error add_items(const dataobject_set& cids, dataobject_set& errors);
            ns_error remove_items(const dataobject_set& cids, dataobject_set& errors);
            ns_error read_values(const dataobject_set& cids, dataobject_set& errors);
            ns_error send_commands(/*const mmscommand_vct& cmds, accesserror_map& errors*/);



        protected:

            virtual ns_error connect_impl();

            virtual ns_error disconnect_impl();

            ns_error error(ns_error err) {
                return error_ = err;
            }

            intfstate state_;
            ns_error error_;

        private:

            //void parse_error(const boost::itu::error_code& errcode);
            void check_connecton_state();

            iec60870ioclient_ptr client_io;
            std::string host;
            std::string port;
            timeouttype tmout;
        };

    }

}

#endif	/* EXTNETINTF_H */

