/* 
 * File:   extnetintf.cpp
 * Author: Alexeev
 * 
 * Created on 14 Июнь 2011 г., 16:16
 */

#include "mmsintf.h"

namespace dvnci {


    objectname::objectname() : internal_(new objectname_type()){}  

    objectname::objectname( const std::string& id, const std::string& domain) :
    internal_(domain.size() ? new objectname_type(MMS::ObjectName::Domain_specific_type(mmsidentifier_type(domain),
    mmsidentifier_type(id)), MMS::ObjectName_domain_specific) : new objectname_type(mmsidentifier_type(id), MMS::ObjectName_vmd_specific)) {
    }

    objectname objectname::create(const std::string& id, const std::string& domain) {
        return objectname(id, domain);
    }

    objectname  objectname::create_aa(const std::string& id) {
        objectname obj;
        obj.internal_=objectname_ptr(new objectname_type(mmsidentifier_type(id), MMS::ObjectName_aa_specific));
        return obj;
    }

        // 1 @bind and @domain  =>  domainspesific : @domain | @bind
        // 2 only @bind a) "xxxx" => vmdspesific
        //                         b) "xxxx : yyyy" domain specific @xxxx | @yyyy !!!! high prior,  defdomain ignore if exists
        //                         c) "@xxxx" application spesific @xxxx    
    objectname objectname::create_from_bind(const std::string& id, const std::string& defdomain) {
        std::string tstid =fulltrim_copy(id);
        std::string tstdom =fulltrim_copy(defdomain);
        std::string::size_type it=tstid.find(':');
        std::string::size_type ita=tstid.find('@');
        if (ita == 0) {
            if (tstid.size() > 0)
                return create_aa(tstid.substr(1));
        }
        else if ((it!=std::string::npos) && (it!=(tstid.size()-1))){
            tstdom = tstid.substr(0,it);
            tstid = tstid.substr(it+1);
        }
        if (tstid.size())
            return objectname(tstid, tstdom);
        return objectname();
    }

    objectname::operator bool() const {
        return (internal_ && (internal_->type() != MMS::ObjectName_null));
    }   
    


    bool operator==(const objectname& ls, const objectname& rs) {
        if (ls.internal_ && rs.internal_) {
            if (ls.internal_->type() == rs.internal_->type()) {
                switch (ls.internal_->type()) {
                    case MMS::ObjectName_vmd_specific:
                        return *(ls.internal_->vmd_specific()) == *(rs.internal_->vmd_specific());
                    case MMS::ObjectName_domain_specific:
                        return ((ls.internal_->domain_specific()->domainID() == rs.internal_->domain_specific()->domainID()) &&
                                (ls.internal_->domain_specific()->itemID() == rs.internal_->domain_specific()->itemID()));
                    case MMS::ObjectName_aa_specific:
                        return *(ls.internal_->aa_specific()) == *(rs.internal_->aa_specific());
                    default:
                    {
                    }
                        return true;
                }
            }
            return false;
        } else if (!ls.internal_ && !rs.internal_)
            return true;
        return false;
    }

    bool operator<(const objectname& ls, const objectname& rs) {
        if (ls.internal_ && rs.internal_) {
            if (ls.internal_->type() == rs.internal_->type()) {
                switch (ls.internal_->type()) {
                    case MMS::ObjectName_vmd_specific:
                        return *(ls.internal_->vmd_specific()) < *(rs.internal_->vmd_specific());
                    case MMS::ObjectName_domain_specific:
                    {
                        if (ls.internal_->domain_specific()->domainID() == rs.internal_->domain_specific()->domainID())
                            return (ls.internal_->domain_specific()->itemID() < rs.internal_->domain_specific()->itemID());
                        return (ls.internal_->domain_specific()->domainID() < rs.internal_->domain_specific()->domainID());
                    }
                    case MMS::ObjectName_aa_specific:
                        return *(ls.internal_->aa_specific()) < *(rs.internal_->aa_specific());
                    default:
                    {
                    }
                        return false;
                }
            } else if (ls.internal_->type() == MMS::ObjectName_null)
                return true;
            else if (rs.internal_->type() == MMS::ObjectName_null)
                return false;
            return (int) ls.internal_->type() < (int) rs.internal_->type();
        } else if (ls.internal_ && !rs.internal_)
            return false;
        else if (ls.internal_ && !rs.internal_)
            return false;
        else if (!ls.internal_ && !rs.internal_)
            return true;
        return false;
    }
    


    namespace external {

        exmmsintf::exmmsintf(tagsbase_ptr intf_, executor* exctr, indx grp) :
        extintf_wraper<objectname>(intf_, exctr, grp, TYPE_SIMPLE_REQ, CONTYPE_SYNC) {
            ;
        }

        exmmsintf::~exmmsintf() {
            disconnect();
        };

        ns_error exmmsintf::checkserverstatus() {
            /*  if ((!netintf->isconnected()))
                  throw dvncierror(ERROR_FAILNET_CONNECTED);*/
            return error(0);
        }

        ns_error exmmsintf::connect_impl() {
            /* try{
                 if (!netintf) {
                        netintf= dvnci::custom::net::netintf_ptr( dvnci::custom::net::factory::build(intf->groups()->host(group()),
                                                                                         intf->groups()->port(group()).empty() ? "9050" : intf->groups()->port(group()),
                                                                                         intf->groups()->user(group()),intf->groups()->password(group()),
                                                                                         intf->groups()->timeout(group())));}
                 if (!netintf) {
                     state_=disconnected;
                     return error(ERROR_NOINTF_CONNECTED);}
                    
                 if (!netintf->isconnected()){
                     state_=disconnected;
                     return error(netintf->error());}
                 else{
                     state_=connected;
                     return error(0);}}
             catch(...){
                 state_=disconnected;
                 return error(ERROR_NOINTF_CONNECTED);}
         state_=disconnected;*/
            return error(0/*netintf->error()*/);
        }

        ns_error exmmsintf::disconnect_impl() {
            /* try{
             disconnect_util();
             real_repval_map.clear();;
             rep_tasks_set.clear();
             evnt_tasks_set.clear();
             state_ = disconnected;
             if (netintf->isconnected()){
               netintf->disconnect();
               return error(0);}}
             catch(...){
             state_ = disconnected;}*/
            return error(0);
        }

        ns_error exmmsintf::add_request_impl() {
            /*error(0); 
            if (need_add().empty()) 
                return error();
            vect_cid_key cids;
            for (indx_set::const_iterator it = need_add().begin(); it != need_add().end(); ++it) {
                 if (intf->exists(*it)) {
                     cid_key tmp ={static_cast<num64>(*it),intf->binding(*it), 
                         static_cast<num64>(intf->type(*it)),  
                         intf->devdb(*it)};
                     cids.push_back(tmp);}
                 else{
                     req_error(*it, ERROR_ENTNOEXIST);}}
            if (cids.empty()) return error(0);
               
            vect_sid_key sids;  
            vect_error_item errors;
               
               
            error(netintf->add_items(cids,sids,errors));
               
            for (vect_sid_key::const_iterator it = sids.begin(); it != sids.end(); ++it) {
                  switch (SUPER_TYPE(intf->type(static_cast<indx> (it->cid)))){
                          case TYPE_EVENT:{
                              add_event(static_cast<indx> (it->cid), it->sid);
                              break;}
                          case TYPE_REPORT:{
                              add_report(static_cast<indx> (it->cid), it->sid);
                              real_report_value rlrpv = {NULL_DOUBLE,0, nill_time};
                              real_repval_map.insert(sid_rl_report_val_pair(it->sid, rlrpv));
                              break;}
                          default:{
                              add_simple(static_cast<indx> (it->cid), it->sid);}}}
               
            for (vect_error_item::const_iterator it = errors.begin(); it != errors.end(); ++it) {
                  req_error(static_cast<indx> (it->id), static_cast<ns_error>(it->code));} */


            return error();
        }

        ns_error exmmsintf::remove_request_impl() {

            /*error(0); 
            if (need_remove().empty())  
                return error();

            vect_num64 sids;
                
            for (serverkey_set::const_iterator it = need_remove().begin(); it != need_remove().end(); ++it) {
               sids.push_back(*it);}

            if (sids.empty())  
                return error(0);
                
            vect_num64 cids;  
            vect_error_item errors;
                
            error(netintf->remove_items(sids,cids,errors));
                
            for (vect_num64::const_iterator it = sids.begin(); it != sids.end(); ++it) {
               if (real_repval_map.find(*it)!=real_repval_map.end())
                   real_repval_map.erase(*it);
               remove_custom(*it);}*/

            return error();
        }

        ns_error exmmsintf::value_request_impl() {


            /*error(0); 
            vect_data_item lines;
            vect_data_item_str linesstr;
            vect_error_item errors;
                
            error(netintf->read_values(lines , linesstr, errors));
       
            for (vect_data_item::const_iterator it = lines.begin(); it != lines.end(); ++it) {
                 tagtype rettp=unpacktagtype(it->pack);
                 switch(SUPER_TYPE(rettp)){
                     case TYPE_EVENT:{
                             break;}
                     case TYPE_REPORT:{  
                         sid_rl_report_val_map::iterator rit=real_repval_map.find(it->sid);
                         if (rit!=real_repval_map.end()){
                             rit->second.value=from_num64_cast<double>(it->val);
                             rit->second.vld=unpackvalid(it->pack);
                             rit->second.tm=it->time;}
                         break;}
                     default: {write_val_sid(it->sid, short_value(it->val, 
                         unpacktagtype(it->pack), 
                         unpackvalid(it->pack),
                         unpackerror(it->pack),
                         it->time));}}}
                      
            for (vect_data_item_str::const_iterator it = linesstr.begin(); it != linesstr.end(); ++it) {
                 write_val_sid(it->sid, short_value(it->val, unpackvalid(it->pack), unpackerror(it->pack), it->time));}*/

            //for (vect_error_item::const_iterator it = errors.begin(); it != errors.end(); ++it) {
            //     write_val_sid(it->sid, short_value(it->val, static_cast<vlvtype>(it->vld), 0, from_num64_cast<datetime>(time)));}


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
            return error();
        }

        ns_error exmmsintf::event_request_impl() {
            return error();
        }

    }
}

