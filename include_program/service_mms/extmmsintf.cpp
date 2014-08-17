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
                            2,
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
                //disconnect_util();
                /*real_repval_map.clear();;
                rep_tasks_set.clear();
                evnt_tasks_set.clear();
                state_ = disconnected;
                if (netintf->isconnected()){
                  netintf->disconnect();
                  return error(0);}*/
            } catch (...) {
                state_ = disconnected;
            }
            return error(0);
        }

        ns_error exmmsintf::add_request_impl() {
            error(0);
            if (need_add().empty())
                return error();
            bindobject_map cids;
            for (indx_set::const_iterator it = need_add().begin(); it != need_add().end(); ++it) {
                if (intf->exists(*it)) {
                    objectname_ptr tmp = objectname::create_from_bind(intf->binding(*it), intf->groups()->topic(group()));
                    cids.insert(bindobject_pair(*it, tmp));
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
                sids.insert(accessresult_pair(it->first, accessresult_ptr()));
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

            /*error(0);
            if (cmds.empty())  
                return error();
                           
            vect_command_data reqcmds; 
            vect_error_item   errors;
                
            for (sidcmd_map::const_iterator it = cmds.begin(); it != cmds.end(); ++it) {
                if (it->second.type()!=TYPE_TEXT){
                     command_data cmd = { it->first, it->second.value64(), static_cast<num64>(it->second.type()), 0, "" };
                     reqcmds.push_back(cmd);}
                else {
                     command_data cmd = { it->first, 0, static_cast<num64>(TYPE_TEXT), 0, it->second.value<std::string>() };
                     reqcmds.push_back(cmd);}}
                
            if (reqcmds.empty())
                return error(ERROR_NODATA);
                
            return error(netintf->send_commands(reqcmds, errors));}
                       

        ns_error exmmsintf::report_request_impl() {
                
            error(0);                
            serverkey_const_iterator it=report_next();
            if (it==report_end()) 
                return  error(ERROR_NODATA);
            indx cid=it->second;
            num64 sid=it->first;
                
            if ((report_requested(cid)) && (!is_report_task(cid))){
                sid_rl_report_val_map::iterator rit=real_repval_map.find(sid);
                if (rit!=real_repval_map.end()){
                    if ((rit->second.vld==FULL_VALID)){
                        if ((rit->second.tm<intf->time_log(cid)))
                            return error();
                        if ((rit->second.tm==intf->time_log(cid))){
                            dt_val_map repval;
                            repval.insert(dt_val_pair(rit->second.tm,rit->second.value));
                            write_val_report_id(cid,repval);
                            return error();}
                        else{
                            vect_report_value_data dt;
                            vect_error_item errors;
                                
                            datetime starttm = intf->time(cid);
                            normalizereporttime(starttm, intf->type(cid));
                            datetime stoptm = starttm;
                            increporttime(stoptm, intf->type(cid), 20);
                            starttm = incsecond(starttm);                          
                                
                            reporttask tsk = { sid, static_cast<num64>(cid) , starttm, stoptm };
                            vect_reporttask tasks;
                            tasks.push_back(tsk);
                            error(netintf->read_report(tasks , dt, errors));
                            add_report_task(cid);
                                
                            for (vect_report_value_data::const_iterator rit=dt.begin(); rit!=dt.end(); ++rit){
                                remove_report_task(static_cast<indx>(rit->cid));
                                dt_val_map repval;
                                for (vect_report_value_item::const_iterator vit=rit->data.begin(); vit!=rit->data.end(); ++vit){
                                     repval.insert(dt_val_pair(vit->time,vit->val));}
                                write_val_report_id(static_cast<indx>(rit->cid),repval);}
                            for (vect_error_item::const_iterator eit=errors.begin(); eit!=errors.end(); ++eit){
                                remove_report_task(static_cast<indx>(eit->id));}}}}}*/
            return error();
        }

        ns_error exmmsintf::report_request_impl() {
            return error(0);
        }

        ns_error exmmsintf::event_request_impl() {
            return error(0);
        }

    }
}

