/* 
 * File:   extnetintf.cpp
 * Author: Alexeev
 * 
 * Created on 14 Июнь 2011 г., 16:16
 */

#include "extmmsintf.h"

namespace dvnci {

    /////////////////////////////////////////////////////////////////////////////////////////////////
    //////// external::exmmsintf
    /////////////////////////////////////////////////////////////////////////////////////////////////

    namespace external {

        exmmsintf::exmmsintf(tagsbase_ptr intf_, executor* exctr, indx grp) :
        extintf_wraper<objectname_ptr>(intf_, exctr, grp, TYPE_SIMPLE_REQ, CONTYPE_SYNC) {
            ;
        }

        exmmsintf::~exmmsintf() {
            disconnect();
        };

        ns_error exmmsintf::checkserverstatus() {
            /* if ((!mmsintf->isconnected()))
                   throw dvncierror(ERROR_FAILNET_CONNECTED);*/
            return error(0);
        }

        ns_error exmmsintf::connect_impl() {
            try {
                //  port : aselector
                std::string port = intf->groups()->port(group());
                std::string asel;
                if (!port.empty()) {
                    std::string::size_type it = port.find_first_of(':', 0);
                    if (it != std::string::npos) {
                        if ((it + 1) < port.size())
                            asel = port.substr(it + 1);
                        else
                            asel = "";
                        port = port.substr(0, it);
                    }
                }
                if (port.empty())
                    port = "102";
                if (!remintf) {
                    remintf = dvnci::mmsintf::build(intf->groups()->host(group()),
                            fulltrim_copy(port),
                            fulltrim_copy(asel),
                            intf->groups()->blocksize(group()),
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

        ns_error exmmsintf::disconnect_impl() {
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

        ns_error exmmsintf::add_request_impl() {
            error(0);
            if (need_add().empty())
                return error();
            bindobject_map cids;
            indx_set tmpadd = need_add();
            for (indx_set::const_iterator it = tmpadd.begin(); it != tmpadd.end(); ++it) {
                if (intf->exists(*it)) {
                    objectname_ptr tmp = objectname::create_from_bind(intf->binding(*it), intf->groups()->topic(group()));
                    if (tmp)
                        cids.insert(bindobject_pair(*it, tmp));
                    else
                        req_error(*it, ERROR_BINDING);
                } else {
                    req_error(*it, ERROR_ENTNOEXIST);
                }
            }
            if (cids.empty()) return error(0);

            accessresult_map results;
            accesserror_map errors;

            if (!error(remintf->add_items(cids, results, errors))) {

                for (bindobject_map::const_iterator it = cids.begin(); it != cids.end(); ++it) {
                    if (results.find(it->second) != results.end()) {
                        add_simple(it->first, it->second);
                    } else if (errors.find(it->second) != errors.end()) {
                        req_error(it->first, ERROR_BINDING);
                    } else
                        req_error(it->first, ERROR_BINDING);
                }
            }

            return error();
        }

        ns_error exmmsintf::remove_request_impl() {

            error(0);
            if (need_remove().empty())
                return error();

            const objectname_set& sids = need_remove();
            accesserror_map errors;

            if (!error(remintf->remove_items(sids, errors))) {
                remove_clear();
            }

            return error();
        }

        ns_error exmmsintf::value_request_impl() {

            error(0);

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
            }

            return error();
        }

        ns_error exmmsintf::command_request_impl(const sidcmd_map& cmds) {

            error(0);
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

        ns_error exmmsintf::report_request_impl() {
            return error(0);
        }

        ns_error exmmsintf::event_request_impl() {
            return error(0);
        }

    }
}

