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
#include "opc/opcda.h"
#include "opc/opcda_i.c"
#include "opc/opcerror.h"


namespace dvnci {
    namespace external {
    namespace opc {





        class transaction_mng_map {

            struct transactstruct {
                DWORD ok_transact;
                DWORD cancel_transact;
                boost::xtime tm;} ;

            typedef std::pair<DWORD, transactstruct > dword_transact_pair;
            typedef std::map< DWORD, transactstruct , std::less<DWORD>,
            std::allocator<dword_transact_pair > > dword_transact_map;

        public:

            bool add(DWORD ok_transact, DWORD cancel_transact, boost::xtime tm = utc_now()) {
                if ((!find_by_cancel(cancel_transact)) && (!find_by_ok(ok_transact))) {
                    transactstruct tmp = { ok_transact , cancel_transact, tm };
                    ok_map.insert(dword_transact_pair(ok_transact, tmp));
                    cancel_map.insert(dword_transact_pair(cancel_transact, tmp));
                    return true;}
                return false;}

            bool find_by_cancel(DWORD cancel_transact, transactstruct& transact) {
                dword_transact_map::iterator it = cancel_map.find(cancel_transact);
                if (it == cancel_map.end()) return false;
                transact = it->second;
                return true;}

            bool find_by_cancel(DWORD cancel_transact) {
                transactstruct transact;
                return find_by_cancel(cancel_transact, transact);}

            bool find_by_ok(DWORD ok_transact, transactstruct& transact) {
                dword_transact_map::iterator it = ok_map.find(ok_transact);
                if (it == ok_map.end()) return false;
                transact = it->second;
                return true;}

            bool find_by_ok(DWORD ok_transact) {
                transactstruct transact;
                return find_by_ok(ok_transact, transact);}

            bool remove_by_cancel(DWORD cancel_transact) {
                dword_transact_map::iterator it = cancel_map.find(cancel_transact);
                if (it == cancel_map.end()) return false;
                DWORD ok_transact = it->second.ok_transact;
                cancel_map.erase(it->first);
                it = ok_map.find(ok_transact);
                if (it == ok_map.end()) return false;
                ok_map.erase(it->first);
                return true;}

            bool remove_by_ok(DWORD ok_transact) {
                dword_transact_map::iterator it = ok_map.find(ok_transact);
                if (it == ok_map.end()) return false;
                DWORD cancel_transact = it->second.cancel_transact;
                ok_map.erase(it->first);
                it = cancel_map.find(cancel_transact);
                if (it == cancel_map.end()) return false;
                cancel_map.erase(it->first);
                return true;}

            bool expiretimout(num32 tmo, DWORD& canceltract) {
                for (dword_transact_map::iterator it = ok_map.begin(); it != ok_map.end(); ++it) {
                    if (expire_from_utc_millsec(it->second.tm,tmo)) {
                        DWORD oktract = it->second.ok_transact;
                        transactstruct transacttmp;
                        if (find_by_ok(oktract, transacttmp)) {
                            canceltract = transacttmp.cancel_transact;
                            remove_by_ok(oktract);
                            return true;}
                        remove_by_ok(oktract);
                        return false;}}
                return false;}

            size_t size() {
                return ok_map.size();}

            bool empty() {
                return ok_map.empty();}

        private:
            dword_transact_map ok_map;
            dword_transact_map cancel_map;} ;


        class opcintf;



        typedef intrusive_sync_share_ptr_tmpl<opcintf> opcintf_ptr;

        class abstract_opc_util {
        public:

            static const int NONEOPC = 0;
            static const int SUBSCROPC = 1;
            static const int ASYNOPC = 2;
            static const int SYNOPC = 4;



            abstract_opc_util() {};

            virtual ~abstract_opc_util() {};
            // инициализация
            virtual bool setinit() = 0;
            // деинициализация
            virtual bool resetinit() = 0;
            // выставить подписку
            virtual bool setadvice(bool& vl) = 0;
            // снять подписку
            virtual bool resetadvice() = 0;
            // поддерживаемые версии протокола 1, 2, 3
            virtual int native_ver() = 0;
            // поддерживаемые типы обмена подписка, асинхр, синх
            virtual int kindcange() = 0;
            // поддерживаемые типы обмена подписка, асинхр, синх
            virtual bool isasync() = 0;} ;

        typedef boost::shared_ptr<abstract_opc_util> abstr_opc_util_ptr;

        class opcintf  : public extintf_wraper<OPCHANDLE> {
        public:

            static const size_t MAX_WRITE_TRANSACTION = 10;
            static const size_t MAX_READ_TRANSACTION = 1;
            
            friend  class Callback;


            opcintf(tagsbase_ptr intf_, executor* exctr, indx grp) : 
             extintf_wraper<OPCHANDLE>(intf_, exctr, grp, TYPE_SIMPLE_REQ, intf_ ? intf_->groups()->synctype(grp) : CONTYPE_SYNOPC ) ,
               transactid_(1) ,  setadviceactive(false) {
               update_dog();}

            virtual ~opcintf();

            virtual bool connect();

            virtual bool disconnect();

            int native_ver() {
                return opc_spec ? opc_spec->native_ver() : 0;};


            //virtual bool add_commands(const vect_opccommand_item& commanditem, vect_opcerror_item& errors);
            //virtual bool add_report_task(indx  key, datetime start, datetime stop) {return true;}

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
                return (writetractmap.size()>=MAX_WRITE_TRANSACTION);}
            
            bool iswriteexpiretimout(num32 tmo, DWORD& tract) {
                DEBUG_STR_DVNCI(iswriteexpiretimout);
                THD_EXCLUSIVE_LOCK(mutex);
                return writetractmap.expiretimout(tmo, tract);}

 /*           void addvalmap(indx sid, opcvalue_item& val) {
                opcvalue_item_map::iterator itval = valitemmap.find(sid);
                if (itval != valitemmap.end())
                    itval->second = val;
                else
                    valitemmap.insert(opcvalue_item_pair(sid, val));}

            bool find_by_clid(indx clid, opcclient_item& itm) {
                opcclient_item_map::iterator it = clt_servermap.find(clid);
                if (it == clt_servermap.end()) return false;
                itm = it->second;
                return true;}

            bool find_by_clid(indx clid) {
                opcclient_item itm;
                return find_by_clid(clid, itm);}

            bool find_by_sid(indx sid, opcclient_item& itm) {
                opcserver_item_map::iterator it = srv_clientmap.find(sid);
                if (it == srv_clientmap.end()) return false;
                itm = it->second;
                return true;}

            bool find_by_sid(indx sid) {
                opcclient_item itm;
                return find_by_sid(sid, itm);}

            bool remove_by_clid(indx clid) {
                opcclient_item_map::iterator it = clt_servermap.find(clid);
                if (it == clt_servermap.end()) return false;
                clt_servermap.erase(it);
                return true;}

            bool remove_by_sid(indx sid) {
                opcserver_item_map::iterator it = srv_clientmap.find(sid);
                if (it == srv_clientmap.end()) return false;
                srv_clientmap.erase(it);
                return true;}

            bool additem(indx sid, indx clid, opcclient_item& itm) {
                opcserver_item_map::iterator it = srv_clientmap.find(sid);
                if (it == srv_clientmap.end())
                    srv_clientmap.insert(opcserver_item_pair(sid, itm));
                else
                    it->second = itm;
                opcclient_item_map::iterator it2 = clt_servermap.find(clid);
                if (it2 == clt_servermap.end())
                    clt_servermap.insert(opcclient_item_pair(clid, itm));
                else
                    it2->second = itm;
                return true;}

            bool needreqcheck(indx clid, const std::wstring& bnd) {
                opcclient_item itm;
                if (!find_by_clid(clid, itm)) return true;
                if (itm.bind == bnd) return false;
                return true;}

/*            bool setopcvalue(indx clid, num64 val, num64 valid, num64 time, num64 tp) {
                opcclient_item itmtmp;
                if (find_by_clid(clid, itmtmp)) {
			  tp = ((intf) && (intf->exists(clid)) && (intf->type(clid)==TYPE_NODEF)) ? TYPE_NODEF : tp;
                    opcvalue_item tmp = {itmtmp.outkey,val, valid, 0, tp};
                    addvalmap(static_cast<indx> (itmtmp.outkey), tmp);
                    return true;}
                return false;}*/

//            boost::mutex mutex;

            void update_dog(){
               dogtm=utc_now();}

            bool dog_time_expired(num32 tmout){
                return expire_from_utc_millsec(dogtm, tmout);}

            bool dog_time_expired(){
                return expire_from_utc_millsec(dogtm, maintimeout);}

            bool checkconnection(){
                  THD_EXCLUSIVE_LOCK(mutex);
                  if (!dog_time_expired()) return true;
                  if (checkserverstatus()) return true;
				  throw dvncierror(ERROR_FAILNET_CONNECTED);
                  return false;}


        protected:
            
            
            virtual ns_error add_request_impl();
            
            virtual ns_error remove_request_impl();
            
            virtual ns_error value_request_impl();
            
            virtual ns_error report_request_impl(){ return 0;}
            
            virtual ns_error event_request_impl(){ return 0;}
            
            virtual ns_error command_request_impl(const sidcmd_map& cmd);
            

            bool cnangeactiveItems();

            bool read_valuesSync1();
            bool read_valuesASync2();

            bool setValuesSync1(const sidcmd_map& cmd);
            bool setValuesASync2(const sidcmd_map& cmd);

            bool cancelTransact(DWORD tract);

            bool checkserverstatus() const;




            DWORD               transactid_;
            abstr_opc_util_ptr  opc_spec;
            transaction_mng_map readtractmap;
            transaction_mng_map writetractmap;
            num32               connecttype;
            num32               ver;
            num32               maintimeout;
            num32               tracttimeout;
            bool                usehda;
            float               deadband;
            bool                setadviceactive;
            DWORD               updaterate;
            boost::xtime        dogtm;} ;}}}

#endif	/* NETINTF_H */

