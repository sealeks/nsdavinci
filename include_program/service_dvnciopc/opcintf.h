/* 
 * File:   netintf.h
 * Author: Serg
 *
 * Created on 20 пїЅ?СЋР»СЊ 2010 Рі., 14:24
 */

#ifndef _DVNCI_OPCINTF_H
#define	_DVNCI_OPCINTF_H

#include "kernel/constdef.h"
#include "kernel/error.h"
#include "kernel/memfile.h"
#include "kernel/templ.h"
#include "kernel/utils.h"
#include "kernel/short_value.h"
#include "kernel/interface_proccesstmpl.h"
#include "kernel/extintf_wraper.h"


#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <objbase.h>
#include <olectl.h>
#include <comcat.h>
#include <opc/opcda.h>

namespace dvnci {
    namespace external {
        namespace opc {

            class opcintf;
            typedef intrusive_sync_share_ptr_tmpl<opcintf> opcintf_ptr;




            class transaction_mng_map {

                struct transactstruct {
                    DWORD ok_transact;
                    DWORD cancel_transact;
                    boost::xtime tm;} ;

                typedef std::pair<DWORD, transactstruct >                    dword_transact_pair;
                typedef std::map< DWORD, transactstruct , std::less<DWORD>,
                std::allocator<dword_transact_pair > >                       dword_transact_map;

            public:
                
                transaction_mng_map(){};
                
                virtual ~transaction_mng_map(){};

                bool add(DWORD ok_transact, DWORD cancel_transact, boost::xtime tm = utc_now());

                bool remove_by_cancel(DWORD cancel_transact);

                bool remove_by_ok(DWORD ok_transact);

                bool expiretimout(timeouttype tmo, DWORD& canceltract);

                size_t size() {
                    return ok_map.size();}

                bool empty() {
                    return ok_map.empty();}

                void clear() {
                    ok_map.clear();
		    cancel_map.clear();}
                

            private:
                
                bool find_by_cancel(DWORD cancel_transact, transactstruct& transact);

                bool find_by_cancel(DWORD cancel_transact) {
                    transactstruct transact;
                    return find_by_cancel(cancel_transact, transact);}

                bool find_by_ok(DWORD ok_transact, transactstruct& transact);
                
                bool find_by_ok(DWORD ok_transact) {
                    transactstruct transact;
                    return find_by_ok(ok_transact, transact);}                
                
                dword_transact_map ok_map;
                dword_transact_map cancel_map;};
                
                

 

            class abstract_opc_util {
            public:


                abstract_opc_util() {};

                virtual ~abstract_opc_util() {};
                
                // инициализация
                virtual bool init() = 0;
                // деинициализация
                virtual bool uninit() = 0;
                // выставить подписку
                virtual bool advice(bool& vl) = 0;
                // снять подписку
                virtual bool unadvice() = 0;
                // поддерживаемые версии протокола 1, 2, 3
                virtual intfvertype native_ver() const = 0;
                // поддерживаемые типы обмена подписка, асинхр, синх
                virtual bool isasync() = 0;} ;

            typedef boost::shared_ptr<abstract_opc_util> abstr_opc_util_ptr;
            
            
            
            
            
            //  main interface
            
            

            class opcintf  : public extintf_wraper<OPCHANDLE> {
            public:

                static const size_t MAX_WRITE_TRANSACTION = 10;
                static const size_t MAX_READ_TRANSACTION  = 1;

                friend  class opc_callback;

                opcintf(tagsbase_ptr intf_, executor* exctr, indx grp);

                virtual ~opcintf();

                int native_ver() {
                    return opc_spec ? opc_spec->native_ver() : 0;};

            protected:
                

                virtual ns_error checkserverstatus(); 
                

                virtual ns_error connect_impl();

                virtual ns_error disconnect_impl();


                virtual ns_error add_request_impl();

                virtual ns_error remove_request_impl();

                virtual ns_error value_request_impl();

                virtual ns_error report_request_impl() {
                    return 0;}

                virtual ns_error event_request_impl() {
                    return 0;}

                virtual ns_error command_request_impl(const sidcmd_map& cmd);



                bool read_valuessync1();
                bool read_valuesasync2();

                bool setvaluessync1(const sidcmd_map& cmd);
                bool setvaluesasync2(const sidcmd_map& cmd);

                bool cancelTransact(DWORD tract);

                
                
                

                DWORD transactid() {
                    if (transactid_ > 0xFFFFFF) transactid_ = 1;
                    return transactid_++;}

                bool addreadtransaction(DWORD ok_transact, DWORD cancel_transact, boost::xtime tm = utc_now()) {
                    //DEBUG_STR_DVNCI(addreadtransaction);
                    THD_EXCLUSIVE_LOCK(mutex);
                    return readtractmap.add(ok_transact, cancel_transact);}

                bool readtransaction_ok(DWORD ok_transact) {
                    DEBUG_STR_DVNCI(readtransaction_ok)
                    THD_EXCLUSIVE_LOCK(mutex);
                    update_dog();
                    return readtractmap.remove_by_ok(ok_transact);}

                bool readtransaction_cancel(DWORD cancel_transact) {
                    THD_EXCLUSIVE_LOCK(mutex);
                    update_dog();
                    return readtractmap.remove_by_cancel(cancel_transact);}

                bool isreadtransaction() {
                    THD_EXCLUSIVE_LOCK(mutex);
                    //DEBUG_STR_VAL_DVNCI(isreadtransaction, readtractmap.size());
                    return (!readtractmap.empty());}

                bool isreadexpiretimout(num32 tmo, DWORD& tract) {
                    DEBUG_STR_DVNCI(isreadexpiretimout);
                    THD_EXCLUSIVE_LOCK(mutex);
                    return readtractmap.expiretimout(tmo, tract);}

                bool addwritetransaction(DWORD ok_transact, DWORD cancel_transact, boost::xtime tm = utc_now()) {
                    //DEBUG_STR_DVNCI(addwritetransaction);
                    THD_EXCLUSIVE_LOCK(mutex);
                    return writetractmap.add(ok_transact, cancel_transact);}

                bool writetransaction_ok(DWORD ok_transact) {
                    DEBUG_STR_DVNCI(writetransaction_ok);
                    THD_EXCLUSIVE_LOCK(mutex);
                    update_dog();
                    return writetractmap.remove_by_ok(ok_transact);}

                bool writetransaction_cancel(DWORD cancel_transact) {
                    //DEBUG_STR_DVNCI(writetransaction_cancel);
                    THD_EXCLUSIVE_LOCK(mutex);
                    update_dog();
                    return writetractmap.remove_by_cancel(cancel_transact);}

                bool iswritetransaction() {
                    THD_EXCLUSIVE_LOCK(mutex);
                    DEBUG_STR_VAL_DVNCI(iswritetransaction, writetractmap.size());
                    return (writetractmap.size() >= MAX_WRITE_TRANSACTION);}

                bool iswriteexpiretimout(num32 tmo, DWORD& tract) {
                    DEBUG_STR_DVNCI(iswriteexpiretimout);
                    THD_EXCLUSIVE_LOCK(mutex);
                    return writetractmap.expiretimout(tmo, tract);}

                void update_dog() {
                    dogtm = utc_now();}

                bool dog_time_expired(num32 tmout) {
                    return expire_from_utc_millsec(dogtm, tmout);}

                bool dog_time_expired() {
                    return expire_from_utc_millsec(dogtm, maintimeout);}

                bool checkconnection() {
                    THD_EXCLUSIVE_LOCK(mutex);
                    if (!dog_time_expired()) return true;
                    if (checkserverstatus()) return true;
                    throw dvncierror(ERROR_FAILNET_CONNECTED);
                    return false;}



                DWORD               transactid_;
                abstr_opc_util_ptr  opc_spec;
                transaction_mng_map readtractmap;
                transaction_mng_map writetractmap;
                intfvertype         ver;
                timeouttype         maintimeout;
                timeouttype         tracttimeout;
                bool                usehda;
                double              deadband;
                bool                setadviceactive;
                gratetype           updaterate;
                boost::xtime        dogtm;} ;}}}

#endif	/* NETINTF_H */

