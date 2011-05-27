/* 
 * File:   netintf.h
 * Author: Serg
 *
 * Created on 20 Р�СЋР»СЊ 2010 Рі., 14:24
 */

#ifndef _DVNCI_LOCALNETINTF_H
#define	_DVNCI_LOCALNETINTF_H


#include <dbaccess/db_task_executor.h>

#include <netinterface/netintf.h>


namespace dvnci{
namespace net{


class localnetintf;

typedef dvnci::database::db_task_executor<localnetintf>  dbtsk_exec;
typedef callable_shared_ptr<dbtsk_exec> dbtsk_exec_ptr;

class localnetintf : public netintf {
public:


    typedef std::pair<indx,value_item> key_buffval_pair;
    typedef std::map<indx,value_item,std::less<indx>, std::allocator<key_buffval_pair > > key_buffval_map;

    typedef std::pair<indx,double> key_deadbound_pair;
    typedef std::map<indx,double,std::less<indx>, std::allocator<key_deadbound_pair > > key_deadbound_map;

    typedef std::pair<indx,dt_val_map> key_reports_pair;
    typedef std::map<indx,dt_val_map,std::less<indx>, std::allocator<key_reports_pair > > key_reports_map;
    
    typedef refcounter_templ<tagsbase>                                                    refcounter;
    typedef boost::shared_ptr<refcounter>                                                 refcounter_ptr;


    localnetintf(tagsbase_ptr intf_, dbtsk_exec_ptr repotr_task_exec = dbtsk_exec_ptr()) : netintf(), intf(intf_), dbexecutor(repotr_task_exec) {
        if (intf){
        THD_EXCLUSIVE_LOCK(intf);
        refcntr=refcounter_ptr(new refcounter(intf,true));};};

    virtual ~localnetintf(){}
    
    localnetintf(const localnetintf& other) {
        
	intf=other.intf;
        _state=other._state;
        dbexecutor=other.dbexecutor;
        refcntr=refcounter_ptr(new refcounter(intf,true));}

    virtual netintf_ptr clone_share(){
       THD_EXCLUSIVE_LOCK(mutex);
       boost::mutex::scoped_lock lockbase(intf);
       return netintf_ptr(new localnetintf(*this));}



    virtual bool connect(){
        if (_state==connected) return true;
        if (intf) {
            _state=connected;
            return true;}
        _state=disconnected;
        return false;}

    virtual bool disconnect(){
        _state=disconnected;
        return true;}


    virtual bool add_items(const vect_client_item& clientitem, vect_server_item& serveritem ,vect_error_item& errors){
        serveritem.clear();
        errors.clear();
        if (intf){
           THD_EXCLUSIVE_LOCK(intf);
           for(vect_client_item::const_iterator it=clientitem.begin();it!=clientitem.end();++it){
             if (intf[it->name]){

                server_item tmp;
                tmp.key=it->key;
                tmp.outkey=intf(it->name);
                tmp.tpitem=intf->type(static_cast<indx>(tmp.outkey));

                if (std::find(items_in_req.begin(),items_in_req.end(), tmp.outkey)==items_in_req.end()){
                items_in_req.push_back(tmp.outkey);
                refcntr->add(static_cast<indx>(tmp.outkey));}

                key_deadbound_map::iterator itdb=dbmap.find(static_cast<int>(tmp.outkey));
                if (itdb==dbmap.end())
                    dbmap.insert(key_deadbound_pair(static_cast<indx>(tmp.outkey),from_num64_cast<double>(it->dbound)));
                else itdb->second=from_num64_cast<double>(it->dbound);

                serveritem.push_back(tmp);}
             else{
                error_item tmperr;
                tmperr.key=it->key;
                tmperr.code=ERROR_TAGNOEXIST;
                errors.push_back(tmperr);}}}
        else {
                error_item tmperr;
                tmperr.key=npos;
                tmperr.code=ERROR_NILLINF;
                errors.push_back(tmperr);}
        return true;}

    virtual bool read_values(const num64_vect& servids, vect_value_item& values, vect_report_value_items& reportvalues, vect_event_value_item& eventvalues, vect_error_item& errors){
        values.clear();
        eventvalues.clear();
        if (intf){
            THD_EXCLUSIVE_LOCK(intf);
            for(num64_vect::const_iterator it=servids.begin();it!=servids.end();++it){
            if (intf->exists(static_cast<indx>(*it))){
                value_item tmp;
                if (get_buffer_tags(static_cast<indx>(*it),tmp)) values.push_back(tmp);}
            else{
                error_item tmperr;
                tmperr.key=*it;
                tmperr.code=ERROR_TAGNOEXIST;
                errors.push_back(tmperr);}}}
        else {
            error_item tmperr;
            tmperr.key=npos;
            tmperr.code=ERROR_NILLINF;
            errors.push_back(tmperr);}
        get_report_values(reportvalues);
        return true;}


    virtual bool read_values(vect_value_item& values, vect_report_value_items& reportvalues, vect_event_value_item& eventvalues){
        vect_error_item errors;
        return read_values(items_in_req ,values,reportvalues, eventvalues, errors);}

    virtual bool get_report_values(vect_report_value_items& reportvalues){
        THD_EXCLUSIVE_LOCK(mtx);
        key_reports_map::iterator it=reports.begin();
        while (it!=reports.end()){
           report_value_items tmp;
           tmp.outkey=static_cast<num64>(it->first);
           tmp.values.clear();
           for (dt_val_map::iterator itv=it->second.begin();itv!=it->second.end();++itv){
                report_value_item tmpv;
                tmpv.type=0;
                tmpv.valid=100;
                tmpv.time=castnum64_from_datetime(itv->first);
                tmpv.val=num64_cast<double>(itv->second);
                tmp.values.push_back(tmpv);}
           remove_report_task(it->first);
           reportvalues.push_back(tmp);
           reports.erase(it++);}
        return true;}


    virtual bool remove_items(const num64_vect& delitem, vect_error_item& errors){
        for(num64_vect::const_iterator it=delitem.begin();it!=delitem.end();++it){
            refcntr->remove(static_cast<indx>(*it));
            items_in_req.erase(std::remove(items_in_req.begin(),items_in_req.end(),*it), items_in_req.end());}
        return true;}

    virtual bool add_commands(const vect_command_item& commanditem, vect_error_item& errors){
        if (!intf) return false;
        THD_EXCLUSIVE_LOCK(intf);
        for (vect_command_item::const_iterator it=commanditem.begin();it!=commanditem.end();++it){
            if (intf->exists(static_cast<indx>(it->outkey))) {
                short_value tmp=short_value(it->val, static_cast<tagtype>(it->type), FULL_VALID);
                intf->send_command(static_cast<indx>(it->outkey),tmp,static_cast<bool>(it->queue));}}
        return true;}

    virtual bool add_report_task(num64  key, datetime start, datetime stop) {
           DEBUG_STR_DVNCI(ADD_LOCAL_REPORT_TASK);
           DEBUG_VAL_DVNCI(key);
           DEBUG_VAL_DVNCI(start);
           DEBUG_VAL_DVNCI(stop);
           report_task_pair newtask=std::make_pair(static_cast<indx>(key),date_time_pair(start,stop));
           report_tasks.insert(newtask);;
           DEBUG_STR_VAL_DVNCI(NOT_EXECUTOR_DB,dbexecutor);
           dbexecutor->addtask(intf->name(static_cast<indx>(key)),intf->type(static_cast<indx>(key)),start,stop, const_cast<localnetintf*>(this));
           return true;}

    virtual bool remove_report_task(indx  key) {
           DEBUG_STR_DVNCI(REMOVE_LOCAL_REPORT_TASK);
           DEBUG_VAL_DVNCI(key);
           if (report_tasks.find(key)!=report_tasks.end()) report_tasks.erase(key);
           return true;}

    void report_executed(std::string tag, dt_val_map& datamap){
          THD_EXCLUSIVE_LOCK(intf);
          indx id=intf(tag);
          if (id!=npos) {
          if (reports.find(id)==reports.end()) {
              reports.insert(key_reports_pair(id,datamap));}}}
    
    boost::mutex   mtx;
    
protected:

    bool get_buffer_tags(const indx key,value_item& val){
       key_buffval_map::iterator it=buffervals.find(key);
       if (intf->exists(key)){
       if (it==buffervals.end()) {
              val.outkey=key;
              val.val=intf[key]->value<num64>();
              val.valid=intf->valid(key);
              val.time=intf[key]->time_n64();
              val.type=intf->type(key);
              buffervals.insert(key_buffval_pair(key,val));
            return true;}
       else {
          key_deadbound_map::iterator itdb=dbmap.find(key);
          bool diff_tmp= true;/*itdb!=dbmap.end() ? 
                             bynum64_and_type_outbound(
                             intf[key]->mineu<num64>(), intf[key]->maxeu<num64>(),
                             it->second.val,   intf[key]->value<num64>(),
                             intf->type(key), itdb->second ) : 0;*/
          if ((it->second.valid!=intf->valid(key)) || (secondsbetween(it->second.time,intf[key]->time_n64())>600) || (diff_tmp)){
                 it->second.val=intf[key]->value<num64>();
                 it->second.valid=intf->valid(key);
                 it->second.time=intf[key]->time_n64();
                 val=it->second;
                 return true;}}}
     return false;}
    

    tagsbase_ptr                                intf;
    num64_vect                                  items_in_req;
    key_buffval_map                             buffervals;
    key_deadbound_map                           dbmap;
    refcounter_ptr                              refcntr;
    report_task_map                             report_tasks;
    key_reports_map                             reports;
    dbtsk_exec_ptr                              dbexecutor;
    boost::thread                               th;
};


}
}

#endif	/* NETINTF_H */

