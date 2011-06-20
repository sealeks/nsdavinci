
/* 
 * File:   netintf.cpp
 * Author: Serg
 * 
 * Created on 20 Р�СЋР»СЊ 2010 Рі., 14:24
 */

#include <custom/localnetintf.h>


namespace dvnci {
    namespace custom {
        namespace net {
            
            
            ns_error localnetintf::connect_impl() {
                if (intf) {
                    state_ = connected;
                    return error(0);}
                return error(ERROR_NOINTF_CONNECTED);}

            ns_error localnetintf::disconnect_impl() {
                value_map.clear();
                event_task_map.clear();
                report_task_map.clear();
                if (regclid){ 
                    intf->unregclient(regclid);}
                state_ = disconnected;
                return error(0);}
            
            
            

            ns_error localnetintf::auth_req( const std::string& user, const std::string& pass) {
                if (!isautorizate_){
                    regclid=intf->regclient(address.to_string(),"IP",user, pass);
                    if (regclid) {
                        isautorizate_=true;
                        return error(0);}
                    else{
                      isautorizate_=false;
                      error(ERROR_AUTORIZATION_FAIL);}}      
                return error(0);}

            ns_error localnetintf::add_items( const vect_cid_key& cids, vect_sid_key& sids,  vect_error_item& errors) {
                errors.clear();
                sids.clear();
                error(0);
                for (vect_cid_key::const_iterator it = cids.begin(); it != cids.end(); ++it) {
                    indx skey = intf(it->name);
                    if (skey != npos) {
                        tagtype ctype = static_cast<tagtype> (it->type);
                        tagtype stype = intf->type(skey);
                        if (!IN_EVENTSET(stype)) {
                            if ((IN_REPORTSET(stype)) || (IN_REPORTSET(ctype))) {
                                if (stype != ctype) {
                                    error_item err = { it->cid, static_cast<num64> (ERROR_TYPENOCAST)};
                                    errors.push_back(err);
                                    break;}}
                            if (!IN_REPORTSET(stype))
                                refcntr->add(skey);
                            indx_deadb_shv_map::iterator sit = value_map.find(skey);
                            if (sit != value_map.end()) {
                                if (sit->second.db() > from_num64_cast<double>(it->dbound))
                                    sit->second.db(from_num64_cast<double>(it->dbound));}
                            else {
                                value_map.insert(indx_deadb_shv_pair(skey,
                                        deadbound_short_value(from_num64_cast<double>(it->dbound))));
                                sid_key tmp = {it->cid, static_cast<num64> (skey)};
                                sids.push_back(tmp);}
                            if (IN_REPORTSET(stype)) {}}
                        else {
                            if (stype != ctype) {
                                error_item err = { it->cid, static_cast<num64> (ERROR_TYPENOCAST)};
                                errors.push_back(err);}}}
                    else {
                        error_item err = { it->cid, static_cast<num64> (ERROR_TAGNOEXIST)};
                        errors.push_back(err);}}
                return error();}

            ns_error localnetintf::add_items_ex( const vect_cid_key_ex cids, vect_sid_key_ex& sids,  vect_error_ex_item& errors) {
                errors.clear();
                sids.clear();
                return 0;}

            ns_error localnetintf::remove_items( const vect_num64& sids,  vect_num64& succ_sids , vect_error_item& errors) {
                errors.clear();
                succ_sids.clear();
                error(0);
                for (vect_num64::const_iterator it = sids.begin(); it != sids.end(); ++it) {
                    indx_deadb_shv_map::iterator sit = value_map.find(static_cast<indx> (*it));
                    if (sit != value_map.end()) {
                        refcntr->remove(static_cast<indx> (*it));
                        value_map.erase(sit);}
                    else {
                        error_item err = { *it , static_cast<num64> (ERROR_NODATA)};
                        errors.push_back(err);}}
                succ_sids = sids;
                return error();}

            ns_error localnetintf::read_values( const vect_num64& sids, vect_data_item& lines , vect_data_item_str& linesstr, vect_error_item& errors) {
                errors.clear();
                lines.clear();
                linesstr.clear();
                error(0);
                for (vect_num64::const_iterator it = sids.begin(); it != sids.end(); ++it) {
                    indx skey = static_cast<indx> (*it);
                    if (intf->exists(skey)) {
                        tagtype stype = intf->type(skey);
                        if (IN_TEXTSET(stype)) {
                            data_item_str vl = { *it, intf->value<std::string > (skey),
                                packdata(intf->valid(skey), intf->type(skey), intf->error(skey)),
                                num64_cast<datetime > (intf->time(skey))};
                            linesstr.push_back(vl);}
                        else {
                            data_item vl = { *it, intf->value_n64(skey), num64_cast<datetime > (intf->time(skey)),
                                packdata(intf->valid(skey), intf->type(skey), intf->error(skey))};
                            lines.push_back(vl);}}
                    else {
                        error_item err = { *it , static_cast<num64> (ERROR_TYPENOCAST)};
                        errors.push_back(err);}}
                return error();}

            ns_error localnetintf::read_values(vect_data_item& lines , vect_data_item_str& linesstr, vect_error_item& errors) {
                errors.clear();
                lines.clear();
                linesstr.clear();
                error(0);
                for (indx_deadb_shv_map::iterator it = value_map.begin(); it != value_map.end(); ++it) {
                    indx skey = it->first;
                    if (intf->exists(skey)) {
                        tagtype stype = intf->type(skey);
                        if (intf->value_expiered(skey, it->second.value(), it->second.db())) {
                            if (IN_TEXTSET(stype)) {
                                data_item_str vl = { static_cast<num64> (it->first) , intf->value<std::string > (skey),
                                    num64_cast<datetime > (intf->time(skey))};
                                it->second.value(intf->value_shv(skey));
                                linesstr.push_back(vl);}
                            else {
                                data_item vl = { static_cast<num64> (it->first) , intf->value_n64(skey),
                                    num64_cast<datetime > (intf->time(skey)),
                                    packdata(intf->valid(skey), intf->type(skey), intf->error(skey))};
                                it->second.value(intf->value_shv(skey));
                                lines.push_back(vl);}}}
                    else {
                        error_item err = { static_cast<num64> (it->first) , static_cast<num64> (ERROR_TYPENOCAST)};
                        errors.push_back(err);}}
                return error();}
            
            
            

            ns_error localnetintf::read_values_ex(const vect_num64& rsids, vect_data_item& lines , vect_data_item_str& linesstr, vect_sid_key_ex& sids, vect_error_item& errors) {
                return 0;}

            ns_error localnetintf::read_values_ex(vect_data_item& lines , vect_data_item_str& linesstr, vect_sid_key_ex& sids, vect_error_item& errors) {
                return 0;}
            
            

            ns_error localnetintf::send_commands(const vect_command_data& cmds, vect_error_item& errors) {
                errors.clear();
                error(0);
                for (vect_command_data::const_iterator it = cmds.begin(); it != cmds.end(); ++it) {
                    indx skey = static_cast<indx> (it->sid);
                    tagtype tp = static_cast<indx> (it->type);
                    if (tp == TYPE_TEXT) {
                        intf->send_command(skey, it->valstr);}
                    else
                        intf->send_command(skey, short_value(it->val, it->type));}
                return error();}
            
            

            ns_error localnetintf::read_report(const vect_reporttask& tasks , vect_report_value_data& dt, vect_error_item& errors) {
                errors.clear();
                dt.clear();
                error(0);
                for (vect_reporttask::const_iterator it = tasks.begin(); it != tasks.end(); ++it) {
                    indx skey = static_cast<indx> (it->sid);
                    if (intf->exists(skey) && (IN_REPORTSET(intf->type(skey)))) {
                        if ((MAX_TASK_SIZE > report_task_map.size()) && (report_task_map.find(skey) == report_task_map.end())) {
                            report_task tmp = {it->cid, now(), from_num64_cast<datetime > (it->start), from_num64_cast<datetime > (it->stop)};
                            report_task_map.insert(indx_reporttask_pair(skey, tmp));}
                        else {
                            error_item err = { it->cid , static_cast<num64> (ERROR_SOURSEBUSY)};
                            errors.push_back(err);}}
                    else {
                        error_item err = { it->cid , static_cast<num64> (ERROR_TYPENOCAST)};
                        errors.push_back(err);}}


                return error(execute_report(dt, errors));}
            
            

            ns_error localnetintf::execute_report(vect_report_value_data& dt, vect_error_item& errors) {
                if (report_task_map.empty())
                    return error();
                for (indx_reporttask_map::iterator it = report_task_map.begin(); it != report_task_map.end(); ++it) {
                    if (intf->exists(it->first) && (IN_REPORTSET(intf->type(it->first)))) {
                        num64 tmtsk = dvnci::abs(secondsbetween(now(), it->second.creatitime));
                        if (tmtsk < TASK_TIMOUT) {
                            dt_val_map vl;
                            intf->select_reportbuff(it->first, vl, it->second.begin, it->second.end);
                            report_value_data dttmp;
                            dttmp.cid = it->second.cid;
                            if (!vl.empty()) {
                                for (dt_val_map::const_iterator vit = vl.begin(); vit != vl.end(); ++vit) {
                                    report_value_item pvl = {num64_cast<double>(vit->second), num64_cast<datetime > (vit->first)};
                                    dttmp.data.push_back(pvl);}}
                            else {
                                datetime endtm = it->second.end;
                                normalizereporttime(endtm, intf->type(it->first));
                                if (endtm < now()) {
                                    report_value_item pvl = {num64_cast<double>(NULL_DOUBLE), num64_cast<datetime > (endtm)};
                                    dttmp.data.push_back(pvl);}}
                            dt.push_back(dttmp);
                            report_task_map.erase(it);
                            return error();}
                        else {
                            error_item err = { it->second.cid , static_cast<num64> (ERROR_TASKTIMEOUT)};
                            errors.push_back(err);
                            report_task_map.erase(it);
                            return error();}}
                    else {
                        error_item err = { it->second.cid , static_cast<num64> (ERROR_TYPENOCAST)};
                        errors.push_back(err);
                        report_task_map.erase(it);
                        return error();}}
                
                return error();}
            

            ns_error localnetintf::read_events(const vect_eventtask& tasks , vect_event_value_item& dt, vect_error_item& errors) {
                errors.clear();
                dt.clear();
                error(0);
                for (vect_eventtask::const_iterator it = tasks.begin(); it != tasks.end(); ++it) {
                    indx skey = static_cast<indx> (it->sid);
                    if (intf->exists(skey) && (IN_EVENTSET(intf->type(skey)))) {
                        if ((MAX_TASK_SIZE > event_task_map.size()) && (event_task_map.find(skey) == event_task_map.end())) {
                            event_task tmp = {it->cid, now(), from_num64_cast<datetime > (it->from)};
                            event_task_map.insert(indx_eventtask_pair(skey, tmp));}
                        else {
                            error_item err = { it->cid , static_cast<num64> (ERROR_SOURSEBUSY)};
                            errors.push_back(err);}}
                    else {
                        error_item err = { it->cid , static_cast<num64> (ERROR_TYPENOCAST)};
                        errors.push_back(err);}}
    

                return error(execute_event(dt, errors));}
            
            
             ns_error localnetintf::execute_event(vect_event_value_item& dt, vect_error_item& errors) {
                if (event_task_map.empty())
                    return error();
                for (indx_eventtask_map::iterator it = event_task_map.begin(); it != event_task_map.end(); ++it) {
                            error_item err = { it->second.cid , static_cast<num64> (ERROR_NODATA)};
                            errors.push_back(err);
                            event_task_map.erase(it);
                            return error();}   
                return error();}     
             
             
             

            ns_error localnetintf::read_trend(const vect_trendtask& tasks, vect_trend_value_data& dt , vect_error_item& errors) {
                return 0;}

            ns_error localnetintf::read_alarms(const unum64& giud, vect_alarms_data& dt) {
                return 0;}

            ns_error localnetintf::read_journal(const unum64& guid, const unum64& cursor, const unum64& cnt, vect_journal_data& dt) {
                return 0;}
            
            
}}}

