/* 
 * File:   extintf_wraper.h
 * Author: Alexeev
 *
 * Created on 7 Июнь 2011 г., 13:58
 */

#ifndef EXTINTF_WRAPER_H
#define	EXTINTF_WRAPER_H

#include <kernel/interface_proccesstmpl.h>
#include <kernel/constdef.h>

#include <boost/bimap/multiset_of.hpp>

namespace dvnci {
    namespace external {
    
template <typename SERVERKEY>
class extintf_wraper : public externalintf {
    
public:
    
    typedef SERVERKEY                                                                      serverkey_type;
    typedef boost::bimaps::set_of<serverkey_type, std::less<serverkey_type> >              serverkeys_setof;
    typedef boost::bimaps::multiset_of<indx, std::less<indx> >                             tags_multisetof;
    typedef boost::bimaps::bimap<serverkeys_setof, serverkeys_setof>                       serverkeys_tags_map;
    typedef serverkeys_tags_map::left_map                                                  serverkeys_map;
    typedef serverkeys_tags_map::right_map                                                 tags_map;
    typedef serverkeys_tags_map::left_iterator                                             serverkey_iterator;
    typedef serverkeys_tags_map::left_const_iterator                                       serverkey_const_iterator;
    typedef serverkeys_tags_map::right_iterator                                            tag_iterator;
    typedef serverkeys_tags_map::right_const_iterator                                      tag_const_iterator;
    
    extintf_wraper(tagsbase_ptr inf, executor* exctr, indx grp) :  
    externalintf(inf,  exctr,  grp){}      
    
    virtual ~extintf_wraper() {};
    
    virtual void insert(const indx_set& idset) {
        for (indx_set::const_iterator it=idset.begin();it!=idset.end();++it){
            if ((error_set.find(*it)==error_set.end()) &&
                (simple_req_map.right.find(*it)==simple_req_map.right.end()) &&
                (report_req_map.right.find(*it)==report_req_map.right.end()) &&
                (event_req_map.right.find(*it)==event_req_map.right.end())){
                            need_add_set.insert(*it);}}}
    
    
    virtual void remove(const indx_set& idset){
        for (indx_set::const_iterator it=idset.begin();it!=idset.end();++it){
            if (error_set.find(*it)!=error_set.end()){
                error_set.remove(*it);
                exectr->error(id, 0);}
            else{
               if ((simple_req_map.right.find(*it)!=simple_req_map.right.end()) ||
                   (report_req_map.right.find(*it)!=report_req_map.right.end()) ||
                   (event_req_map.right.find(*it)!=event_req_map.right.end())){
                need_remove_set.insert(*it);}}}}
    
    void req_error(indx id, ns_error err){
        if (err) {
            if (error_set.find(id)!=error_set.end()){
                error_set.insert(id);
                exectr->error(id, err);}}}
    
    
protected:
    
    indx_set             need_add_set;
    indx_set             need_remove_set;
    indx_set             error_set;
    
    serverkeys_tags_map  simple_req_map;
    serverkeys_tags_map  report_req_map;
    serverkeys_tags_map  event_req_map;
    
    

    
    
    indx_set need_req_set;;};

    }}



#endif	/* EXTINTF_WRAPER_H */

