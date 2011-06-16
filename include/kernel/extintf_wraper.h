/* 
 * File:   extintf_wraper.h
 * Author: Alexeev
 *
 * Created on 7 Р�СЋРЅСЊ 2011 Рі., 13:58
 */

#ifndef EXTINTF_WRAPER_H
#define	EXTINTF_WRAPER_H

#include <kernel/interface_proccesstmpl.h>
#include <kernel/constdef.h>
#include <iterator>

#include <boost/bimap/multiset_of.hpp>

namespace dvnci {
    namespace external {
    
template <typename SERVERKEY>
class extintf_wraper : public externalintf {
    
public:
    
    typedef SERVERKEY                                                                      serverkey_type;
    typedef boost::bimaps::set_of<serverkey_type, std::less<serverkey_type> >              serverkeys_setof;
    typedef boost::bimaps::multiset_of<indx, std::less<indx> >                             tags_multisetof;
    typedef boost::bimaps::bimap<serverkeys_setof, tags_multisetof>                        serverkeys_tags_map;
    typedef typename serverkeys_tags_map::left_map                                         serverkeys_map;
    typedef typename serverkeys_tags_map::right_map                                        tags_map;
    typedef typename serverkeys_tags_map::left_iterator                                    serverkey_iterator;
    typedef typename serverkeys_tags_map::left_const_iterator                              serverkey_const_iterator;
    typedef typename serverkeys_tags_map::right_iterator                                   tag_iterator;
    typedef typename serverkeys_tags_map::right_const_iterator                             tag_const_iterator;
    typedef typename tag_iterator::difference_type                                         tag_iterator_diff;
    typedef typename tags_map::const_range_type                                            const_tag_range;
    typedef typename serverkeys_tags_map::value_type                                       serverkey_tag_pair;
    
    typedef std::set<serverkey_type , std::less<serverkey_type>, 
    std::allocator<serverkey_type> >                                                       serverkey_set;
    
    
    typedef std::pair<serverkey_type, short_value >                                        sidcmd_pair;
    typedef std::map<serverkey_type, short_value, 
                     std::less<serverkey_type>, std::allocator<sidcmd_pair > >             sidcmd_map;
    
    
    extintf_wraper(tagsbase_ptr inf, executor* exctr, indx grp, tagtype provide_man, subcripttype subsrcr = CONTYPE_SYNC) :  
    externalintf(inf,  exctr,  grp, provide_man, subsrcr){
      next_simple_iterator=simple_req_map.left.end();
      next_event_iterator=event_req_map.left.end();
      next_report_iterator=report_req_map.left.end();}      
    
    virtual ~extintf_wraper() {};
    
    
    virtual void insert(const indx_set& idset) {
        for (indx_set::const_iterator it=idset.begin();it!=idset.end();++it){
            if ((error_set.find(*it)==error_set.end()) &&
                (need_remove_set.find(*it)==need_remove_set.end()) &&
                (simple_req_map.right.find(*it)==simple_req_map.right.end()) &&
                (report_req_map.right.find(*it)==report_req_map.right.end()) &&
                (event_req_map.right.find(*it)==event_req_map.right.end())){
                            need_add_set.insert(*it);}}}
    
    
    virtual void remove(const indx_set& idset){
        for (indx_set::const_iterator it=idset.begin();it!=idset.end();++it){
            if (error_set.find(*it)!=error_set.end()){
                error_set.erase(*it);
                exectr->error(*it, 0);}
            else{
               if (simple_req_map.right.find(*it)!=simple_req_map.right.end()) {
                   tag_const_iterator beg = simple_req_map.right.lower_bound(*it);
                   tag_const_iterator end = simple_req_map.right.upper_bound(*it);
                   tag_iterator_diff diff=dvnci::abs(std::distance(beg,end));
                   if (diff){
                       simple_req_map.right.erase(*it);
                       next_simple_iterator=simple_req_map.left.end();
                       serverkey_type  deleted = beg->second;   
                       if (diff==1){
                            need_remove_set.insert(deleted);}}}
               if (report_req_map.right.find(*it)!=report_req_map.right.end()){
                   tag_const_iterator beg = report_req_map.right.lower_bound(*it);
                   tag_const_iterator end = report_req_map.right.upper_bound(*it);
                   tag_iterator_diff diff=dvnci::abs(std::distance(beg,end));     
                   if (diff){
                       serverkey_type  deleted = beg->second;  
                       report_req_map.right.erase(*it);
                       next_report_iterator=report_req_map.left.end();
                       if (diff==1){
                            need_remove_set.insert(deleted);}}}
               if (event_req_map.right.find(*it)!=event_req_map.right.end()){
                   tag_const_iterator beg = event_req_map.right.lower_bound(*it);
                   tag_const_iterator end = event_req_map.right.upper_bound(*it);
                   tag_iterator_diff diff=dvnci::abs(std::distance(beg,end));
                       serverkey_type  deleted = beg->second;
                       event_req_map.right.erase(*it);
                       next_event_iterator=event_req_map.left.end();
                       if (diff==1){
                            need_remove_set.insert(deleted);}}}}}
    
    
    virtual bool operator()(){
        try{
            checkserverstatus();          
            remove_request();
            add_request();
            value_request();
            report_request();
            event_request();
	    command_request();}
        catch(dvncierror& errd){
            if ((errd.code()==ERROR_IO_LINK_NOT_CONNECTION) || 
                (errd.code()==ERROR_FAILNET_CONNECTED) || 
                (errd.code()==ERROR_NONET_CONNECTED) ||
                (errd.code()==ERROR_IO_SERVICE_LOCK)){
                try{
                    disconnect();}
                catch(...){}}
            error(errd.code());
            throw errd;}    
            return true;}   
    
    
    
protected:
    
    
    virtual ns_error checkserverstatus(){
        return error(0);} 
    
    //requests   add
    
    virtual ns_error add_request_impl() = 0; 
     
    
    //requests   remove    
    
    virtual ns_error remove_request_impl()  = 0;
    

    //requests   simple value       
    
    virtual ns_error value_request_impl() = 0; 
    
    
  
    //requests   report value         
    
    virtual ns_error report_request_impl() = 0; 
         
    bool report_requested(indx id) const{
        return ((exectr) && (exectr->report_requested(id)));}
    

    //requests   event value       
    
    virtual ns_error event_request_impl() = 0;
    

    //send   command value      
    
    virtual ns_error command_request_impl(const sidcmd_map& cmd) = 0; 
    
    
    
    

    const serverkeys_tags_map&  simple_req(){
        return simple_req_map;}

    const serverkeys_tags_map&  report_req(){
        return report_req_map;}
    
    const serverkeys_tags_map&  event_req(){
        return event_req_map;} 
    
    
    
    const indx_set& need_add(){
        return need_add_set;}
    
    const serverkey_set&  need_remove(){
        return need_remove_set;}
    

    
    void add_simple(indx id, serverkey_type sid){
            indx_set::iterator it = need_add_set.find(id);
            if (it!=need_add_set.end())
                need_add_set.erase(it);
            simple_req_map.insert(serverkey_tag_pair(sid,id));
            next_event_iterator=simple_req_map.left.end();}
    
    void add_report(indx id, serverkey_type sid){
            indx_set::iterator it = need_add_set.find(id);
            if (it!=need_add_set.end())
                need_add_set.erase(it);
            report_req_map.insert(serverkey_tag_pair(sid,id));
            next_report_iterator=report_req_map.left.end();}
    
    void add_event(indx id, serverkey_type sid){
            indx_set::iterator it = need_add_set.find(id);
            if (it!=need_add_set.end())
                need_add_set.erase(it);        
            event_req_map.insert(serverkey_tag_pair(sid,id));
            next_event_iterator=event_req_map.left.end();}  
    
    void remove_custom(serverkey_type sid){
        if (need_remove_set.find(sid)!=need_remove_set.end())
            need_remove_set.erase(sid);}

    void req_error(indx id, ns_error err){
        indx_set::iterator it = need_add_set.find(id);
        if (it!=need_add_set.end())
                need_add_set.erase(it);   
        //it = need_remove_set.find(id);
        //if (it!=need_remove_set.end())
        //        need_remove_set.erase(it);        
        if (err) {
            if (error_set.find(id)==error_set.end()){
                error_set.insert(id);
                exectr->error(id, err);}}} 
    
    
    
    
    void write_val_sid(serverkey_type sid, const short_value val){
       serverkey_const_iterator end = simple_req_map.left.upper_bound(sid);
       for (serverkey_const_iterator it=simple_req_map.left.lower_bound(sid);it!=end;++it){
               exectr->write_val(it->second, val);}}
    
    void write_val_report_sid(serverkey_type sid, const dt_val_map& val){
       serverkey_const_iterator end = report_req_map.left.upper_bound(sid);
       for (serverkey_const_iterator it=report_req_map.left.lower_bound(sid);it!=end;++it){
               exectr->write_val(it->second, val);}}
    
    void write_val_event_sid(serverkey_type sid, const dt_val_pair& val){
       serverkey_const_iterator end = event_req_map.left.upper_bound(sid);
       for (serverkey_const_iterator it=event_req_map.left.lower_bound(sid);it!=end;++it){
               exectr->write_val(it->second, val);}}
    
    
    
    
    void write_val_id(indx id, const short_value val){
       tag_const_iterator it = simple_req_map.right.find(id);
       if (it != simple_req_map.right.end()){
               exectr->write_val(it->first, val);}}
    
    void write_val_report_id(indx id, const dt_val_map& val){
       tag_const_iterator it = report_req_map.right.find(id);
       if (it != report_req_map.right.end()){
               exectr->write_val_report(it->first, val);
               return;}}
    
    void write_val_event_id(indx id, const dt_val_pair& val){
       tag_const_iterator it = event_req_map.right.find(id);
       if (it != simple_req_map.right.end()){
               exectr->write_val_event(it->first, val);
               return;}}
    
    
    

 
    
     serverkey_const_iterator simple_next(bool move = true) {
            if (simple_req_map.empty()) 
                return simple_req_map.left.end();
            if (next_simple_iterator==simple_req_map.left.end())
                next_simple_iterator=simple_req_map.left.begin();
            serverkey_const_iterator it=next_simple_iterator;
            if (move) 
                next_simple_iterator++;
            return it;}
        
     serverkey_const_iterator simple_end() const{
            return simple_req_map.left.end();}  
     
     
     
    
    
     serverkey_const_iterator report_next(bool move = true) {
            if (report_req_map.empty()) 
                return report_req_map.left.end();
            if (next_report_iterator==report_req_map.left.end())
                next_report_iterator=report_req_map.left.begin();
            serverkey_const_iterator it=next_report_iterator;
            if (move) 
                next_report_iterator++;
            return it;}
     
     serverkey_const_iterator report_end() const{
            return report_req_map.left.end();}
     
     
     
     
     
     serverkey_const_iterator event_next(bool move = false) {
            if (event_req_map.empty()) 
                return event_req_map.left.end();
            if (next_event_iterator==event_req_map.left.end())
                next_event_iterator=event_req_map.left.begin();
            serverkey_const_iterator it=next_event_iterator;
            if (move) 
                next_event_iterator++;
            return it;}            
        
     serverkey_const_iterator event_end() const{
            return event_req_map.left.end();}
     
     
     
     
      
     void disconnect_util(){
        need_add_set.clear();
        for (tag_const_iterator it=simple_req_map.right.begin();it!=simple_req_map.right.end();++it){
             need_add_set.insert(it->first);}
        simple_req_map.clear();
        for (tag_const_iterator it=report_req_map.right.begin();it!=report_req_map.right.end();++it){
             need_add_set.insert(it->first);}
        report_req_map.clear();
        for (tag_const_iterator it=event_req_map.right.begin();it!=event_req_map.right.end();++it){
             need_add_set.insert(it->first);}
        event_req_map.clear();
        error_set.clear();
        need_remove_set.clear();
        next_simple_iterator=simple_req_map.left.end();
        next_event_iterator=event_req_map.left.end();
        next_report_iterator=report_req_map.left.end();}


    private:
        
        
    ns_error add_request(){
        return (need_add_set.empty()) ? 0 : add_request_impl();}
          
    ns_error remove_request(){
        return (need_remove_set.empty()) ? 0 : remove_request_impl();}
    
    ns_error value_request(){
        return ((!(provide() & TYPE_SIMPLE_REQ)) || 
                (simple_req_map.empty())) ? 
                    0 : value_request_impl();}
    
    ns_error report_request(){
        return ((!(provide() & TYPE_REPORT)) || 
                (report_req_map.empty())) ? 
                    0 : report_request_impl();}
    
      
    ns_error event_request(){
         return ((!(provide() & TYPE_EVENT)) || 
                (report_req_map.empty())) ? 
                    0 : event_request_impl();}   
    
    
    ns_error command_request(){
         command_vector cmds;
         intf->select_commands(cmds, exectr->groupset());
         if (!cmds.empty()) {
                sidcmd_map sidcmds;
                for (command_vector::const_iterator it = cmds.begin(); it != cmds.end(); ++it) {
                    tag_const_iterator itsid = simple_req_map.right.find(it->tagid());
                    if (itsid != simple_req_map.right.end()) {
                        if (it->type() != TYPE_TEXT)
			    sidcmds.insert(std::make_pair(itsid->second,short_value(it->value_set<num64 > (), it->type())));
                        else
                            sidcmds.insert(std::make_pair(itsid->second, short_value(it->strvalue())));}}
                return (sidcmds.empty()) ? 0 : command_request_impl(sidcmds) ;}
            return 0;}    
    
        
    indx_set                   need_add_set;
    serverkey_set              need_remove_set;
    indx_set                   error_set;    
        
    serverkeys_tags_map        simple_req_map;
    serverkeys_tags_map        report_req_map;
    serverkeys_tags_map        event_req_map;
    
    serverkey_const_iterator   next_simple_iterator;    
    serverkey_const_iterator   next_report_iterator;
    serverkey_const_iterator   next_event_iterator;

    
    
    indx_set need_req_set;;};

    }}



#endif	/* EXTINTF_WRAPER_H */

