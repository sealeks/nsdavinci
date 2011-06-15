/* 
 * File:   extnetintf.cpp
 * Author: Alexeev
 * 
 * Created on 14 Июнь 2011 г., 16:16
 */

#include <custom/extnetintf.h>
#include <kernel/rpcioclient.h>

namespace dvnci {
    namespace external {
        namespace net {
            
            using namespace dvnci::custom::net;
            
            extnetintf::extnetintf(tagsbase_ptr intf_, executor* exctr, indx grp) :
            extintf_wraper<num64>(intf_, exctr, grp, TYPE_SIMPLE_REQ, CONTYPE_SYNC ) {;}

            extnetintf::~extnetintf() {
                disconnect();};
                
            ns_error extnetintf::checkserverstatus(){
                return 0;}
                
            ns_error extnetintf::connect_impl(){
                try{
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
            state_=disconnected;    
            return error(netintf->error());}
            

            ns_error extnetintf::disconnect_impl(){
                try{
                disconnect_util();
                if (netintf->isconnected()){
                  netintf->disconnect();
                  return error(0);}
                state_ = disconnected;}
                catch(...){
                state_ = disconnected;}
                return error(0);}



            ns_error extnetintf::add_request_impl() {
                
               if (need_add_set.empty()) return 0;
               vect_cid_key cids;
               for (indx_set::const_iterator it = need_add_set.begin(); it != need_add_set.end(); ++it) {
                    if (intf->exists(*it)) {
                        cid_key tmp ={static_cast<num64>(*it),intf->binding(*it), static_cast<num64>(intf->type(*it)),  num64_cast<double>(intf->devdb(*it)) };
                        cids.push_back(tmp);}
                    else{
                        req_error(*it, ERROR_ENTNOEXIST);}}
               if (cids.empty()) return error(0);
               
               vect_sid_key sids;  
               vect_error_item errors;
               
               
               error(netintf->add_items(cids,sids,errors));
               
               for (vect_sid_key::const_iterator it = sids.begin(); it != sids.end(); ++it) {
                     add_simple(static_cast<indx> (it->cid), it->sid);}
               
               for (vect_error_item::const_iterator it = errors.begin(); it != errors.end(); ++it) {
                     req_error(static_cast<indx> (it->id), static_cast<ns_error>(it->code));} 
               
               
               return error();}
            
            
            

            ns_error extnetintf::remove_request_impl() {
                
                if (need_remove_set.empty())  
                    return error(0);

                vect_num64 sids;
                
                for (serverkey_set::const_iterator it = need_remove_set.begin(); it != need_remove_set.end(); ++it) {
                   sids.push_back(*it);}

                if (sids.empty())  
                    return error(0);
                
                vect_num64 cids;  
                vect_error_item errors;
                
                error(netintf->remove_items(sids,cids,errors));
                
                for (vect_num64::const_iterator it = sids.begin(); it != sids.end(); ++it) {
                   need_remove_set.erase(*it);}

            return error();}
            

            
            ns_error extnetintf::value_request_impl() {
                
                vect_data_item lines;
                vect_data_item_str linesstr;
                vect_error_item errors;
                
                error(netintf->read_values(lines , linesstr, errors));
       
                for (vect_data_item::const_iterator it = lines.begin(); it != lines.end(); ++it) {
                     write_val_sid(it->sid, short_value(it->val, 
                             unpacktagtype(it->pack), 
                             unpackvalid(it->pack),
                             unpackerror(it->pack),
                             from_num64_cast<datetime>(it->time)));}
                      
                for (vect_data_item_str::const_iterator it = linesstr.begin(); it != linesstr.end(); ++it) {
                     write_val_sid(it->sid, short_value(it->val, unpackvalid(it->pack), unpackerror(it->pack), from_num64_cast<datetime>(it->time)));}
                
                //for (vect_error_item::const_iterator it = errors.begin(); it != errors.end(); ++it) {
                //     write_val_sid(it->sid, short_value(it->val, static_cast<vlvtype>(it->vld), 0, from_num64_cast<datetime>(time)));}
                
                
                 return error();}    
            
            
            ns_error extnetintf::command_request_impl(const sidcmd_map& cmds){
                
                error(0);
                if (cmds.empty())  
                    return error(0);
                           
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
                       

            ns_error extnetintf::report_request_impl() {
                    return 0;}

            ns_error extnetintf::event_request_impl() {
                    return 0;}               
                
                
        }}}

