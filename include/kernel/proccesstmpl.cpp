/* 
 * File:   group_proccessor.cpp
 * Author: Serg
 * 
 * Created on 23 Р?СЋР»СЊ 2010 Рі., 10:47
 */

#include <kernel/proccesstmpl.h>

namespace dvnci {

    executor::executor(tagsbase_ptr inf, tagtype provide_man ) :
    executable(),  intf(inf), isconnected_(false), provide_(provide_man) {}


    void executor::add_tag(indx id) {
        if (type_supported(id)){
           indx_set tmp;
           tmp.insert(id);
           add_tags(tmp);}
        else error(id,ERROR_TYPENOPROCCESS);}

    void executor::remove_tag(indx id) {
        indx_set tmp;
        tmp.insert(id);
        error(id,0);
        remove_tags(tmp);}

    void executor::add_tags(const indx_set& idset) {
            if (provide_==TYPE_FULL)
                add_tags_impl(idset);
            else{
                indx_set idsetchecked;
                for (indx_set::const_iterator it=idset.begin();it!=idset.end();++it){
                   if (type_supported(*it)){
                       idsetchecked.insert(*it);}
                   else{
                       error(*it,ERROR_TYPENOPROCCESS);}}
                if (!idsetchecked.empty()) add_tags_impl(idset);}}


    bool executor::requested(indx id) {
        if (intf) {
            if (IN_EVENTSET(intf->type(id))) return true;
            if (IN_REPORTSET(intf->type(id))) return report_requested(id);
            return (intf->refcnt(id)>0);}
        return false;};

    void executor::write_val_event(indx id, datetime dt, double vl) {
        error(id, 0);
        if (intf) intf->write_val_event(id, dt,  vl);}
    
    void executor::write_val_event(indx id, const dt_val_pair& val) {
        error(id, 0);
        if (intf) intf->write_val_event(id, val);}

    void executor::error(indx id, ns_error err) {
        if (intf) {
            if (err){
               intf->error(id, err);
               tag_errorset.insert(id);}
            else{
                if (tag_errorset.find(id)!=tag_errorset.end()) {
                intf->error(id, 0);
                tag_errorset.erase(id);}}}}

    void executor::clear_errors() {
        if (intf) {
            for (indx_set::iterator it = tag_errorset.begin(); it!=tag_errorset.end(); ++it)
                if (intf->exists(*it)) intf->error(*it, 0);}
        tag_errorset.clear();}



    // запись доставленного значения в карту

    void executor::write_val(indx id, const short_value& val) {
	   if (intf->refcnt(id)){
		intf->write_val(id, val);}}

   void executor::write_val(indx id, const std::string& val, vlvtype valid , datetime time , ns_error err){
	   if (intf->refcnt(id)){
		intf->write_val(id, val, valid, time, err);}}

    // запись доставленного отчетного значения в карту

    void executor::write_val_report(indx id, const dt_val_map& values) {
        if (intf->reportbuffered(id)) {
            intf->write_vals_report(id, values);}
        else{
            indx_dtvalmap_map::iterator it = reportvalues_map.find(id);
            if (it==reportvalues_map.end())
                  reportvalues_map.insert(indx_dtvalmap_pair(id, values));
            else it->second.insert(values.begin(), values.end());}}

    void executor::write_val_report(indx id, datetime tm , double val) {
        if (intf->reportbuffered(id)){
             intf->write_val_report(id, tm, val);}
        else{
             dt_val_map tmp;
             tmp.insert(dt_val_pair(tm, val));
             write_val_report(id, tmp);}}


    // чтение отчетного значения из внутреннего хранилища

    bool executor::getreportvalue(indx id, dt_val_pair& value) {
        if (reportvalues_map.empty()) return false;
        indx_dtvalmap_map::iterator it = reportvalues_map.find(id);
        if (it!=reportvalues_map.end()) {
            dt_val_map tmpreportline = it->second;
            if (tmpreportline.empty()) return false;
            dt_val_map::iterator itval = tmpreportline.begin();
            if (itval==tmpreportline.end()) return false;
            value.first = itval->first;
            value.second = itval->second;
            return true;}
        return false;}

    bool executor::buffer_of_reporttag_empty(indx id) {
        if (reportvalues_map.empty()) return true;
        indx_dtvalmap_map::iterator it = reportvalues_map.find(id);
        if (it==reportvalues_map.end()) return true;
        return it->second.empty();}

    // необходим опрос по отчетному итемсу

    bool executor::report_requested(indx id) {
        if (intf->reportbuffered(id)) {
            return ((IN_REPORTSET(intf->type(id))) && (intf->report_history_empty(id)) && (intf->time_log(id) < now()));}
        else{
        if (!buffer_of_reporttag_empty(id)) {
            dt_val_pair tmpval;
            if (getreportvalue(id, tmpval)) {
                switch (intf->valid(id)) {
                    case REPORT_NEEDREQUEST:
                    case REPORT_WAITSOURCE:{
                        intf->write_val_report(id, tmpval.first, tmpval.second);
                        remove_firstreporvalue_from_map(id);
                        break;}
                    case REPORT_NOACTIVE: {
                        remove_reporvalue_from_map(id);
                        intf->valid(id, REPORT_NEEDKHOWDEEP);
                        break;}}}
            return false;}
        if (intf->valid(id)==REPORT_NOACTIVE) {
            intf->valid(id, REPORT_NEEDKHOWDEEP);
            return false;}}
        return ((IN_REPORTSET(intf->type(id))) && ((intf->valid(id)==REPORT_NEEDREQUEST)));}


    // удаление крайнего отчетого значения итемса из карты

    void executor::remove_firstreporvalue_from_map(indx id) {
        if (reportvalues_map.empty()) return;
        indx_dtvalmap_map::iterator it = reportvalues_map.find(id);
        if (it!=reportvalues_map.end()) {
            if (it->second.empty()) return;
            dt_val_map::iterator itval = it->second.begin();
            if (itval==it->second.end()) return;
            it->second.erase(itval);}}

    // удаление всех отчетных значений итемса из карты

    void executor::remove_reporvalue_from_map(indx id) {
        if (reportvalues_map.empty()) return;
        indx_dtvalmap_map::iterator it = reportvalues_map.find(id);
        if (it!=reportvalues_map.end()) {
            reportvalues_map.erase(it);}}

    bool executor::push_all_report(indx id) {
        if (reportvalues_map.empty()) return false;
        indx_set idset;
        for (indx_dtvalmap_map::iterator it = reportvalues_map.begin(); it!=reportvalues_map.end(); ++it) {
            idset.insert(it->first);}
        if (!idset.empty()) {
            for (indx_set::iterator it = idset.begin(); it!=idset.end(); ++it) report_requested(*it);}
        return (idset.find(id)!=idset.end());}


    void executor::set_group_state(indx id, ns_error err , vlvtype valid) {
            indx_set tpmpset;
            if (id != npos) tpmpset.insert(id);
            const indx_set grst = (id!=npos) ? tpmpset: groupset();
            for (indx_set::const_iterator it = grst.begin(); it!=grst.end(); ++it) {
                if (!err) {
                    set_group_timeout(*it);
                    if (errors_set.find(*it)!=errors_set.end()) {
                        intf->groups()->error(*it, 0);
                        errors_set.erase(*it);}
                    if (active_set.find(*it)==active_set.end()) {
                        intf->groups()->active(*it, true);
                        intf->groups()->valid(*it, (valid==1) ? FULL_VALID : valid);
                        active_set.insert(*it);}}
                else {
                    intf->groups()->error(*it, err);
                    if (errors_set.find(*it)==errors_set.end()) {
                        errors_set.insert(*it);}
                    if (active_set.find(*it)!=active_set.end()) {
                        intf->groups()->active(*it, false);
                        intf->groups()->valid(*it, (valid==1) ? NULL_VALID : valid);
			intf->resettag_for_group(*it);
                        active_set.erase(*it);}}}}


    void executor::group_state_on(indx id){

         indx_set tpmpset;
         if (id!=npos){
            tpmpset.insert(id);
            if (active_set.find(id)==active_set.end())
                 active_set.insert(id);
            if (errors_set.find(id)!=errors_set.end())
                 errors_set.erase(id);}
         else{
            active_set.clear();
            errors_set.clear();}

         const indx_set grst = (id!=npos) ? tpmpset: groupset();

         for (indx_set::const_iterator it = grst.begin(); it!=grst.end(); ++it) {
                if (active_set.find(*it)==active_set.end())
                        active_set.insert(*it);
                intf->groups()->active(*it, true);
                intf->groups()->valid(*it, FULL_VALID);
                intf->groups()->error(*it, 0);}}


     void executor::group_state_off(indx id){
         indx_set tpmpset;
         if (id!=npos){
            tpmpset.insert(id);
            if (active_set.find(id)!=active_set.end())
                 active_set.erase(id);
            if (errors_set.find(id)!=errors_set.end())
                 errors_set.erase(id);}
         else{
             active_set.clear();
             errors_set.clear();}

         const indx_set grst = (id!=npos) ? tpmpset: groupset();

         for (indx_set::const_iterator it = grst.begin(); it!=grst.end(); ++it) {
                intf->groups()->active(*it, false);
                intf->groups()->valid(*it, NULL_VALID);
                intf->groups()->error(*it, 0);
                intf->resettag_for_group(*it);}}

     datetime executor::get_group_timeout(indx id) const {
            indx_dt_map::const_iterator it = timout_map.find(id);
            return (it!=timout_map.end()) ? it->second : datetime();}

     void executor::set_group_timeout(indx id)  {
            indx_dt_map::iterator it = timout_map.find(id);
            if (it!=timout_map.end())  it->second = now();
            else timout_map.insert(indx_dt_pair(id, now()));}

     void executor::clear_group_timeout(indx id) {
            indx_dt_map::iterator it = timout_map.find(id);
            if (it!=timout_map.end())  timout_map.erase(id);}

     bool executor::is_expire_group_timeout(indx id, num32 tout)  {
            datetime dtout = get_group_timeout(id);
            if (dtout.is_special()) {
                set_group_timeout(id);
                return false;}
            else {
                return ((dvnci::abs<num64>(millisecondsbetween(now(), dtout))>static_cast<num64> (tout)));}}


    ///////////////////////////////////////////

    group_proccessor::group_proccessor(tagsbase_ptr inf, tagselector_ptr selectr ) : executable(), strategy_(0),
    selector(selectr) {
        if (inf) {
            THD_EXCLUSIVE_LOCK(inf);
            intf=inf;}}

    bool group_proccessor::getmessage(messagestruct& mess) {
        THD_EXCLUSIVE_LOCK(*mtx_internal());
        if (managment.queue.empty()) return false;
        mess.id = managment.queue[0].id;
        mess.mess = managment.queue[0].mess;
        mess.some = managment.queue[0].some;
        managment.queue.pop_front();
        return true;}

    void group_proccessor::addmessage(num32  mess, indx id, indx some) {
        THD_EXCLUSIVE_LOCK(*mtx_internal());
        if (managment.queue.size() >= MAX_GROUPMESSAGE)
            managment.queue.pop_front();
        managment.queue.push_back(messagestruct(mess, id, some));}

    bool group_proccessor::clearmessage() {
        THD_EXCLUSIVE_LOCK(*mtx_internal());
        managment.queue.clear();
        return true;}

    bool group_proccessor::operator()() {

        boost::xtime xt;
        while (!terminated()) {
            try {
                if  (init()) {
                    while (getmessage(message)) {
                        if  (terminated()) break;
                        switch (strategy()){
                           case STRATEGY_TYPE_REPORT:{
                                if (message.mess==MSG_DVNCITAGREPORT){
                                    if (message.some){
                                       addtag(message.id);}
                                    else{
                                       removetag(message.id);}}
                                break;}
                           default: {
                               if (selector->group_included(message.some)) {
                                  switch (message.mess) {
                                       case MSG_DVNCTAGDELFROMGR:{
                                          removetag(message.id);
                                          break;}
                                       case MSG_DVNCTAGADDTOGR:{
                                          addtag(message.id);
                                          break;}
                                      default:{
                                          optinalchangeid(message.id);}}}
                               else {
                                  optinalchangeid(message.id);}
                                break;}}}
                    execute_impl();
                    addmillisec_to_now(xt, 1);}
                else
                    addmillisec_to_now(xt, 1000);
                boost::thread::sleep(xt);}
            catch (boost::system::system_error& boosterr) {
                if (intf) intf->debugerror("group_proccessor error what=" + std::string(boosterr.what()));}
            catch (...) {
                if (intf) intf->debugerror("group_proccessor NODEF error ");}}
        uninit();
        return true;}

    bool group_proccessor::initialize() {
        if (!intf) return false;
        if (!initialize_impl()) return false;
        #ifdef DVNCI_DEDUG
        intf->debugwarning("INITGROUP appid=" + to_str(appid()) + " grouid="  + (selector ? to_str(selector->group()) : "nodef"));
        #endif
        clearmessage();
        DEBUG_STR_DVNCI(INITGROUP)
        return true;}

    bool group_proccessor::uninitialize() {
        if (!intf) return false;
        #ifdef DVNCI_DEDUG
        intf->debugwarning("UNINIT GROUP appid=" + to_str(appid()) + " grouid="   + (selector ? to_str(selector->group()) : "nodef"));
        #endif
        if (!uninitialize_impl()) return false;
        DEBUG_STR_DVNCI(UNINITGROUP)
        return true;}}