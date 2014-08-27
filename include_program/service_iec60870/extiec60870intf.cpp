/* 
 * File:   extnetintf.cpp
 * Author: Alexeev
 * 
 * Created on 14 �?юнь 2011 г., 16:16
 */

#include "extiec60870intf.h"

namespace dvnci {


    namespace external {

        using dvnci::prot80670::dataobject;
        using dvnci::prot80670::dataobject_ptr;
        using dvnci::prot80670::dataobject_set;
        using dvnci::prot80670::iec60870intf_ptr;



        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// external::exiec870intf
        /////////////////////////////////////////////////////////////////////////////////////////////////

        extiec60870intf::extiec60870intf(tagsbase_ptr intf_, executor* exctr, indx grp) :
        extintf_wraper<dvnci::prot80670::dataobject_ptr>(intf_, exctr, grp, TYPE_SIMPLE_REQ, CONTYPE_SYNC) {
        }

        extiec60870intf::~extiec60870intf() {
            disconnect();
        }

        ns_error extiec60870intf::checkserverstatus() {
            /* if ((!iec60870intf->isconnected()))
                   throw dvncierror(ERROR_FAILNET_CONNECTED);*/
            return error(0);
        }

        ns_error extiec60870intf::connect_impl() {
            try {
                //  port : aselector
                std::string port = "2404";//intf->groups()->port(group());
                if (port.empty())
                    port = "2404";
                if (!remintf) {
                    remintf = dvnci::prot80670::iec60870intf::build(intf->groups()->host(group()),
                            fulltrim_copy(port),
                            intf->groups()->timeout(group()));
                }
                if (!remintf) {
                    state_ = disconnected;
                    return error(ERROR_NOINTF_CONNECTED);
                }

                if (!remintf->isconnected()) {
                    state_ = disconnected;
                    return error(remintf->error());
                } else {
                    state_ = connected;
                    return error(0);
                }
            } catch (...) {
                state_ = disconnected;
                return error(ERROR_NOINTF_CONNECTED);
            }
            state_ = disconnected;
            return error(remintf->error());
        }

        ns_error extiec60870intf::disconnect_impl() {
            try {
                disconnect_util();
                state_ = disconnected;
                if (remintf->isconnected()) {
                    remintf->disconnect();
                    remintf.reset();
                    return error(0);
                }
            } catch (...) {
                remintf.reset();
                state_ = disconnected;
            }
            return error(0);
        }

        ns_error extiec60870intf::add_request_impl() {
            error(0);
               if (need_add().empty())
                   return error();
               dataobject_set cids;
               indx_set tmpadd=need_add();
               for (indx_set::const_iterator it = tmpadd.begin(); it != tmpadd.end(); ++it) {
                   if (intf->exists(*it)) {
                       dataobject_ptr tmp = dataobject::build_from_bind(intf->groups()->devnum(group()), intf->binding(*it));
                    if (tmp)
                        cids.insert(tmp);
                    else
                        req_error(*it, ERROR_BINDING);
                   } else {
                       req_error(*it, ERROR_ENTNOEXIST);
                   }
               }
               if (cids.empty()) return error(0);

               dataobject_set errors;

               if (!error(remintf->add_items(cids, errors))) {

                   for (dataobject_set::const_iterator it = cids.begin(); it != cids.end(); ++it) {
                       if (errors.find(*it) == errors.end()) {
                           //add_simple(it->first, it->second);
                       } else {}
                           //req_error(it->first, ERROR_BINDING);
                   }
               }

            return error();
        }

        ns_error extiec60870intf::remove_request_impl() {

            /* error(0);
             if (need_remove().empty())
                 return error();

             const objectname_set& sids = need_remove();
             accesserror_map errors;

             if (!error(remintf->remove_items(sids, errors))) {
                 remove_clear();
             }*/

            return error();
        }

        ns_error extiec60870intf::value_request_impl() {

            /* error(0);

             const serverkeys_tags_map& simpreq = simple_req();
             accessresult_map sids;

             for (serverkey_const_iterator it = simpreq.left.begin(); it != simpreq.left.end(); ++it) {
                 sids.insert(accessresult_pair(it->first, mmsresult_ptr()));
             }

             error(remintf->read_values(sids));
             //this->

             for (accessresult_map::const_iterator it = sids.begin(); it != sids.end(); ++it) {
                 if (it->second)
                     write_val_sid(it->first, from_mms_result(it->second));
                 else
                     write_val_sid(it->first, short_value());
             }*/

            return error();
        }

        ns_error extiec60870intf::command_request_impl(const sidcmd_map& cmds) {

            /*   error(0);
               if (cmds.empty())  
                   return error();
                           
               mmscommand_vct reqcmds; 
               accesserror_map   errors;

               for (sidcmd_map::const_iterator it = cmds.begin(); it != cmds.end(); ++it) {
                   mmscommand_pair cmd = mmscommand_pair(it->first, it->second);
                   reqcmds.push_back(cmd);
               }
                
               if (reqcmds.empty())
                   return error(ERROR_NODATA);
                
               return error(remintf->send_commands(reqcmds, errors));}

           ns_error extiec60870intf::report_request_impl() {
               return error(0);
           }

           ns_error extiec60870intf::event_request_impl() {
               return error(0);
           }*/

            return error();
        }

        ns_error extiec60870intf::report_request_impl() {
            return error();
        };

        ns_error extiec60870intf::event_request_impl() {
            return error();
        };

    }
}

