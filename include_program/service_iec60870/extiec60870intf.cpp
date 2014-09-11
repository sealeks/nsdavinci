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
        using dvnci::prot80670::indx_dataobject_pair;
        using dvnci::prot80670::indx_dataobject_vct;
        



        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// external::exiec870intf
        /////////////////////////////////////////////////////////////////////////////////////////////////

        extiec60870intf::extiec60870intf(tagsbase_ptr intf_, executor* exctr, indx grp) :
        extintf_wraper<dvnci::prot80670::dataobject_ptr>(intf_, exctr, grp, TYPE_SIMPLE_REQ, CONTYPE_ASYNC), iec60870_data_listener(), fatal_() {
        }
        
        extiec60870intf::extiec60870intf(tagsbase_ptr intf_, executor* exctr, const indx_set& grps, const metalink& lnk) :
        extintf_wraper<dvnci::prot80670::dataobject_ptr>(intf_, exctr, grps, lnk, TYPE_SIMPLE_REQ, CONTYPE_ASYNC), iec60870_data_listener(), fatal_() {    
        }       

        extiec60870intf::~extiec60870intf() {
            disconnect();
        }
        
        void extiec60870intf::execute60870(dataobject_ptr vl, const ns_error&  err) {
            write_val_sid(vl, dvnci::prot80670::to_short_value(vl));
        };        

        void extiec60870intf::execute60870(const dataobject_vct& vl, const ns_error&  err) {
            for (dataobject_vct::const_iterator it = vl.begin(); it != vl.end(); ++it)
                execute60870(*it);
        }        

        void extiec60870intf::execute60870(device_address dev,  const ns_error& err) {          
            error(ERROR_NONET_CONNECTED);
        };

        void extiec60870intf::execute60870(const boost::system::error_code& err) {
            error(ERROR_NONET_CONNECTED);
        }
        

        void extiec60870intf::terminate60870() {
            fatal_=dvnci::dvncierror(ERROR_NONET_CONNECTED);  
        }

        ns_error extiec60870intf::checkserverstatus() {
            if (fatal_) {
                kill_pm();
                dvnci::dvncierror tmp = fatal_;
                fatal_ = dvnci::dvncierror();
                throw dvnci::dvncierror(ERROR_NONET_CONNECTED);
            }
           return error(pm_connected() ? 0 :  ERROR_IO_LINK_NOT_CONNECTION);
        }

        ns_error extiec60870intf::connect_impl() {           
            try {
                std::string port = "2404"; 
                if (port.empty())
                    port = "2404";
                if (!thread_io) {
                    thread_io = create_pm(intf->groups()->host(group()),
                            fulltrim_copy(port), intf->groups()->timeout(group()),
                            iec60870_data_listener::shared_from_this());
                }
                state_ = connected;
                return error(pm_connected() ? 0 : ERROR_IO_LINK_NOT_CONNECTION);
            } catch (...) {
            }
            state_ = disconnected;
            return error(ERROR_BASENOTFOUND);
        }

        ns_error extiec60870intf::disconnect_impl() {
            try {
                if (thread_io) {
                    thread_io->pm()->disconnect();
                    thread_io->join();
                }
            } catch (...) {
            }
            kill_pm();
            return error(0);
        }

        ns_error extiec60870intf::add_request_impl() {
            error(0);
            if (pm_connected()) {
                if (need_add().empty())
                    return error();
                indx_dataobject_vct cids;
                indx_dataobject_vct command_cids;
                indx_set tmpadd = need_add();
                for (indx_set::const_iterator it = tmpadd.begin(); it != tmpadd.end(); ++it) {
                    if (intf->exists(*it)) {
                        dataobject_ptr tmp = dataobject::build_from_bind(0, intf->binding(*it));
                        if (tmp) {
                            if (tmp->readable())
                                cids.push_back(indx_dataobject_pair(*it, tmp));
                            else
                                command_cids.push_back(indx_dataobject_pair(*it, tmp));
                        }
                        else
                            req_error(*it, ERROR_BINDING);
                    } else {
                        req_error(*it, ERROR_ENTNOEXIST);
                    }
                }
                if (cids.empty()) return error(0);
                
                indx_dataobject_vct rslt;
                thread_io->pm()->add_items(cids, rslt);

                for (indx_dataobject_vct::const_iterator it = cids.begin(); it != cids.end(); ++it) 
                    add_simple(it->first, it->second);
                for (indx_dataobject_vct::const_iterator it = command_cids.begin(); it != command_cids.end(); ++it) 
                    add_simple(it->first, it->second);       
                for (indx_dataobject_vct::const_iterator it = rslt.begin(); it != rslt.end(); ++it)
                    write_val_id(it->first, dvnci::prot80670::to_short_value(it->second));
            }
            return error();
        }

        ns_error extiec60870intf::remove_request_impl() {

            error(0);
            if (need_remove().empty())
                return error();

            const dataobject_set& sids = need_remove();

            thread_io->pm()->remove_items(sids);
            remove_clear();

            return error();
        }

        ns_error extiec60870intf::value_request_impl() {
            
            error(0);

             const serverkeys_tags_map& simpreq = simple_req();
             dataobject_set sids;

             for (serverkey_const_iterator it = simpreq.left.begin(); it != simpreq.left.end(); ++it) 
                 sids.insert(it->first);
             
             thread_io->pm()->read_items(sids);

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

        iec60870_thread_ptr extiec60870intf::create_pm(std::string host, std::string port, timeouttype tmo, dvnci::prot80670::iec60870_data_listener_ptr listr) {
            return iec60870_thread::create(host, port, tmo, listr);
        }

        bool extiec60870intf::pm_connected() const {
            return ((thread_io) && (thread_io->pm()->state() == dvnci::prot80670::iec60870_104PM::connected));
        }

        void extiec60870intf::kill_pm() {
            disconnect_util();
            if (thread_io)
                thread_io.reset();
            state_ = disconnected;
        }

    }
}

