/* 
 * File:   interface_proccesstmpl.h
 * Author: Serg
 *
 * Created on 23 Р пїЅРЎР‹Р В»РЎРЉ 2010 Р С–., 12:07
 */

#ifndef SUBSCRIPTGROUP_PROCCESSOR_TEMPLU_H
#define	SUBSCRIPTGROUP_PROCCESSOR_TEMPLU_H

#include <kernel/proccesstmpl.h>
#include <kernel/constdef.h>

namespace dvnci {
    namespace external {

    const blksizetype DEFAULT_ARCHIVEBS = 15;

    
    class externalintf {
        
    public:
  
        enum intfstate {
            disconnected, connected};

        externalintf(tagsbase_ptr inf, executor* exctr, indx grp, tagtype provide_man, subcripttype subsrcr = CONTYPE_SYNC) : 
             state_(disconnected), intf(inf), exectr(exctr), group_(grp), provide_(provide_man), subsrcript_(subsrcr), error_(0)  {};

        virtual ~externalintf() {};

        bool isconnected(){
            return ((state_ == connected) || (!error(connect_impl())));};
   
        bool disconnect(){
            return ((state_ != connected) || (!error(disconnect_impl())));}

        
        indx group() const {
            return group_;}
        
        tagtype provide() const {
            return provide_;}
        
        subcripttype  subsrcript() const {
            return subsrcript_;}

        boost::mutex* mtx_internal() {
            return &mutex;}
        
         ns_error  error() const {
                return error_;}
  
        virtual bool operator()(){
            return true;}
        
        virtual void insert(const indx_set& idset)= 0;
    
        virtual void remove(const indx_set& idset)= 0;

    protected:

        virtual ns_error connect_impl() = 0;
        
        virtual ns_error disconnect_impl() = 0;
        
        ns_error  error(ns_error err){
                return error_=err;}
        
        void  subsrcript(subcripttype val) {
            subsrcript_=val;}
        
        intfstate          state_;
        tagsbase_ptr       intf;
        executor*          exectr;
        indx               group_;
        tagtype            provide_;
        subcripttype       subsrcript_;
        ns_error           error_;
        boost::mutex       mutex;};
        
        
        
        
        
        
        
        template < typename EXTERNALINTF>
                class externalintf_executor : public executor {
            
            typedef boost::shared_ptr<EXTERNALINTF>    externintf_ptr;

        public:

            externalintf_executor(tagsbase_ptr inf, indx groupind, metalink lnk, tagtype provide_man = TYPE_SIMPL) :
            executor(inf, provide_man) {};

            virtual bool operator()() {
                if (init()) {
                    if (externmanager->isconnected()) {
                        try {
                            externmanager->operator()();
                            set_group_state(npos, externmanager->error(), FULL_VALID);
                           return true;}
                        catch (dvncierror& errd) {
                            error (errd.code());
                            intf->debugerror("externalintf_executor mainloop dvnci_error");
                            set_group_state(npos, externmanager->error(), FULL_VALID);
                            return false;}
                        catch (...) {
                            if (intf )
                                intf->debugerror("externalintf_executor mainloop undef error");
                            set_group_state(npos, externmanager->error(), FULL_VALID);
                            return false;}}
                    else {
                        set_group_state(npos, externmanager->error(), FULL_VALID);}}
                return false;}
                    
        protected:
            
                      

            virtual void add_tags_impl(const indx_set& idset) {
                if (init()) {
                    externmanager->insert(idset);}}

            virtual void remove_tags_impl(const indx_set& idset) {
                if (init()) {
                    externmanager->remove(idset);}}

            virtual bool initialize() {
                if (!externmanager)
                    externmanager = externintf_ptr(new EXTERNALINTF(intf, (executor*)this, group()));
                return externmanager;}

            virtual bool uninitialize() {
                if (externmanager) {
                    externmanager->disconnect();
                    externmanager.reset();}
                group_state_off();
                return true;}
            
            externintf_ptr               externmanager;} ;        




    }}

#endif	/* SUBSCRIPTGROUP_PROCCESSOR_TEMPL_H */

