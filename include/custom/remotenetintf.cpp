/* 
 * File:   netintf.cpp
 * Author: Serg
 * 
 * Created on 20 Р�СЋР»СЊ 2010 Рі., 14:24
 */

#include <custom/remotenetintf.h>


namespace dvnci {
    namespace custom {
        namespace net {

         ns_error remotenetintf::auth_req( const std::string& user, const std::string& user){
             return 0;}
         
         ns_error remotenetintf::add_items( const vect_cid_key& cids, vect_sid_key& sids,  vect_error_info& errors){
            try {
                req_add_items req;
                resp_add_items resp;
                assign_req_items(req, cids);
                DEBUG_STR_DVNCI(ADDITEMS)
                if (querytmpl<req_add_items, resp_add_items, RPC_OPERATION_REQ_ADD_ITEMS, RPC_OPERATION_RESP_ADD_ITEMS > (req, resp)) {
                    assign_resp_items(resp, sid, errors);}
                else
                    DEBUG_STR_DVNCI(querytmpl not success)}
            catch (dvncierror& err_) {
                if ((err_.code() == ERROR_FAILNET_CONNECTED) || (err_.code() == ERROR_NONET_CONNECTED)) throw err_;
                /*adderror(err_)*/;}
            catch (...) {
                dvncierror tmperr(NS_ERROR_ERRRESP);
                /*adderror(tmperr);*/;}
            return 0;}
         
         ns_error remotenetintf::add_items_ex( const vect_cid_key_ex& cids, vect_sid_key& sids,  vect_error_info& errors){
            try {
                req_add_items_ex req;
                resp_add_items_ex resp;
                assign_req_items(req, cids);
                DEBUG_STR_DVNCI(ADDITEMS)
                if (querytmpl<req_add_items, resp_add_items, RPC_OPERATION_REQ_ADD_ITEMS_EX, RPC_OPERATION_RESP_ADD_ITEMS_EX > (req, resp)) {
                    assign_resp_items(resp, sids, errors);}
                else
                    DEBUG_STR_DVNCI(querytmpl not success)}
            catch (dvncierror& err_) {
                if ((err_.code() == ERROR_FAILNET_CONNECTED) || (err_.code() == ERROR_NONET_CONNECTED)) throw err_;
                /*adderror(err_)*/;}
            catch (...) {
                dvncierror tmperr(NS_ERROR_ERRRESP);
                /*adderror(tmperr);*/;}
            return 0;}     
         
         
         ns_error remotenetintf::remove_items( const vect_num64& sids,  vect_num64& succ_sids , vect_error_info& errors){
            try {
                req_remove_items req;
                resp_remove_items resp;
                assign_req_remitems(req, sids);
                DEBUG_STR_DVNCI(ADDITEMS)
                if (querytmpl<req_remove_items, resp_remove_items, RPC_OPERATION_REQ_REMOVE_ITEMS, RPC_OPERATION_RESP_REMOVE_ITEMS > (req, resp)) {
                    assign_resp_remitems(resp, sid, errors);}
                else
                    DEBUG_STR_DVNCI(querytmpl not success)}
            catch (dvncierror& err_) {
                if ((err_.code() == ERROR_FAILNET_CONNECTED) || (err_.code() == ERROR_NONET_CONNECTED)) throw err_;
                /*adderror(err_)*/;}
            catch (...) {
                dvncierror tmperr(NS_ERROR_ERRRESP);
                /*adderror(tmperr);*/;}
            return 0;} 
         
         
      ns_error remotenetintf::add_items_ex( const vect_cid_key_ex cids, vect_sid_key_ex& sids,  vect_error_ex_info& errors){
              errors.clear();
              sids.clear();
              for (vect_cid_key::const_iterator it=cids.begin(); it!=cids.end(); ++it){
                 indx skey = intf(it->name);
                 if (skey!=npos) { 
                     tagtype ctype = static_cast<tagtype>(it->type);
                     tagtype stype = intf->type(skey);
                     if (!IN_EVENTSET(stype)){                    
                            if ((IN_REPORTSET(stype)) || (IN_REPORTSET(ctype))){
                                if (stype!=ctype){
                                    error_info err = { it->cid, static_cast<num64>(ERROR_TYPENOCAST)};
                                    errors.push_back(err);
                                    break;}}
                            indx_deadb_shv_map::iterator sit = value_map.find(skey);
                            if (sit!=value_map.end()){
                                 if (sit->second->db()>from_num64_cast(it->dbound))
                                     sit->second->db(from_num64_cast(it->dbound));}
                                 else{
                                     value_map.insert(indx_deadb_shv_pair(skey,
                                     deadbound_short_value(from_num64_cast(it->dbound))));
                                     sids.push_back(sid_key(it->cid,static_cast<num64>(skey)));}
                     if (IN_REPORTSET(stype)) {
                         
                     }}
                     else{
                          if (stype!=ctype){
                             error_info err = { it->cid, static_cast<num64>(ERROR_TYPENOCAST)};
                             errors.push_back(err);}}}
                 else{
                     error_info err = { it->cid, static_cast<num64>(ERROR_TAGNOEXIST)};
                     errors.push_back(err);}}
             return 0;}
      
      

     ns_error remotenetintf::remove_items( const vect_num64& sids,  vect_num64& succ_sids , vect_error_info& errors){
          errors.clear();
          succ_sids.clear();
          for (vect_num64::const_iterator it=sids.begin(); it!=sids.end(); ++it){ 
              indx_deadb_shv_map::iterator sit = value_map.find(static_cast<indx>(*it));
              if (sit != value_map.end()) {
                   value_map.erase(sit);}
              else{
                   error_info err = { *it , static_cast<num64>(ERROR_NODATA)};
                   errors.push_back(err);}}
          succ_sids=sids;
          return 0;}   
     
     ns_error remotenetintf::req_data_item( const vect_num64& sids, vect_data_item& lines , vect_data_item_str& linesstr, vect_error_info& errors){
          errors.clear();
          lines.clear();
          linesstr.clear();
          for (vect_num64::const_iterator it=sids.begin(); it!=sids.end(); ++it){
              indx skey = static_cast<indx>(*it);
              if (intf->exists(skey)){
                  tagtype stype = intf->type(skey);
                  if (IN_TEXTSET(stype)) {
                         data_item_str vl = { *it, intf->value<std::string>(skey), 
                                               static_cast<num64>(intf->valid(skey)),
                                               num64_cast(intf->time(skey))};
                         linesstr.push_back(vl);}
                  else{
                         data_item vl = { *it, intf->value_n64(skey),
                                               num64_cast(intf->time(skey)), 
                                               packdata(intf->valid(skey), intf->type(skey))};
                         lines.push_back(vl);}}
                  else{
                     error_info err = { *it , static_cast<num64>(ERROR_TYPENOCAST)};
                     errors.push_back(err);}}}
     
    ns_error remotenetintf::req_data_item(vect_data_item& lines , vect_data_item_str& linesstr, vect_error_info& errors){
          errors.clear();
          lines.clear();
          linesstr.clear();
          for (indx_deadb_shv_map::const_iterator it=value_map.begin(); it!=value_map.end(); ++it){
              indx skey = it->first;
              if (intf->exists(skey)){
                  tagtype stype = intf->type(skey);
                  if (intf->value_expiered(skey, it->second->value(), it->second->db())){
                  if (IN_TEXTSET(stype)) {
                         data_item_str vl = { *it, intf->value<std::string>(skey),
                                               num64_cast(intf->time(skey))};
                         it->second->value(intf->value_shv(skey));
                         linesstr.push_back(vl);}
                  else{
                         data_item vl = { *it, intf->value_n64(skey), 
                                               num64_cast(intf->time(skey)), 
                                               packdata(intf->valid(skey), intf->type(skey))};
                         it->second->value(intf->value_shv(skey));
                         lines.push_back(vl);}}}
                  else{
                     error_info err = { *it , static_cast<num64>(ERROR_TYPENOCAST)};
                     errors.push_back(err);}}}
    
    ns_error remotenetintf::req_send_commands(const vect_command_data& cmds, vect_error_info& errors){
          errors.clear();
          for (vect_command_data::const_iterator it=cmds.begin(); it!=cmds.end(); ++it){
              indx skey = static_cast<indx>(it->sid);
              tagtype tp = static_cast<indx>(it->type);
              if (tp==TYPE_TEXT){
                  intf->send_command(skey,it->valstr);}
              else 
                  intf->send_command(skey,short_value(it->val, it->type));}
        return 0;}
    
    ns_error remotenetintf::req_report(const vect_reporttask& tasks ,vect_report_value_data& dt, vect_error_info& errors){
        return 0;}
           
    
    
    ns_error remotenetintf::req_event(const vect_eventtask& tasks ,vect_event_value_item& dt, vect_error_info& errors){
        return 0;}
    
    
    ns_error remotenetintf::req_trend(const vect_trendtask& tasks,vect_report_value_data& dt , vect_error_info& errors){
        return 0;}
    
    
    ns_error remotenetintf::req_alarms(const unum64& giud, vect_alarms_data& dt){
        return 0;}
    
    
    ns_error remotenetintf::req_journal(const unum64& guid, const unum64& cursor, const unum64& cnt,vect_journal_data& dt){
        return 0;}    
      
}}}

