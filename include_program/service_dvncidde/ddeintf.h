/* 
 * File:   netintf.h
 * Author: Serg
 *
 * Created on 20 пїЅ?СЋР»СЊ 2010 Рі., 14:24
 */

#ifndef _DVNCI_DDEINTF_H
#define	_DVNCI_DDEINTF_H

#include <kernel/constdef.h>
#include <kernel/error.h>
#include <kernel/memfile.h>
#include <kernel/templ.h>
#include <kernel/interface_proccesstmpl.h>


#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <objbase.h>
#include <olectl.h>
#include <comcat.h>

#include <dde.h>
#include <ddeml.h>


namespace dvnci {
    namespace dde {


        struct ddevalue_item {
            std::string    outkey;
            num64          val;
            num64          valid;
            num64          type;};

        typedef std::vector<ddevalue_item > vect_ddevalue_item;

        typedef std::pair<std::string, ddevalue_item > ddevalue_item_pair;
        typedef std::map<std::string, ddevalue_item, std::less<std::string>,
        std::allocator<ddevalue_item_pair > > ddevalue_item_map;

        struct ddereport_value_item {
          num64  val;
          num64  valid;
          num64  time;
          num64  type;};

        typedef std::vector<ddereport_value_item > vect_ddereport_value_item;

        struct ddereport_value_items {
          num64  outkey;
          vect_ddereport_value_item  values;};

        typedef std::vector<ddereport_value_items > vect_ddereport_value_items;

        struct ddeevent_value_item {
         num64  outkey;
         num64  val;
         num64  time;};

        typedef std::vector<ddeevent_value_item > vect_ddeevent_value_item;

        struct ddeclient_item {
            indx         key;
            num64        tpitem;
            std::string  name;};

        typedef std::vector<ddeclient_item > vect_ddeclient_item;

        typedef std::pair<indx, ddeclient_item > ddeclient_item_pair;
        typedef std::map<indx, ddeclient_item, std::less<indx>,
        std::allocator<ddeclient_item_pair > > ddeclient_item_map;

        typedef std::pair<std::string, ddeclient_item > ddeserver_item_pair;
        typedef std::map<std::string, ddeclient_item, std::less<std::string>,
        std::allocator<ddeserver_item_pair > > ddeserver_item_map;

        struct ddeerror_item {
            indx code;
            indx key;};

        typedef std::vector<ddeerror_item > vect_ddeerror_item;

        struct ddecommand_item {
            std::string  outkey;
            num64        val;
            num64        type;
            num64        queue;
            std::string  user;
            std::string  pass;};

        typedef std::vector<ddecommand_item > vect_ddecommand_item;

        class ddeintf;

        typedef intrusive_sync_share_ptr_tmpl<ddeintf> ddeintf_ptr;

        class abstract_dde_util {
        public:

            static const int NONEDDE = 0;
            static const int SUBSCRDDE = 1;
            static const int ASYNDDE = 2;
            static const int SYNDDE = 4;

            abstract_dde_util() {};

            virtual ~abstract_dde_util() {};
            virtual bool setinit() = 0;
            virtual bool resetinit() = 0;};

        typedef boost::shared_ptr<abstract_dde_util> abstr_dde_util_ptr;

        class ddeintf : public externalintf< ddeclient_item, ddeclient_item, ddeerror_item,
                                    std::string , ddevalue_item, ddereport_value_items, ddereport_value_item, ddeevent_value_item,
                                    ddecommand_item >{
        public:


            ddeintf(tagsbase_ptr inf, indx grp) : externalintf< ddeclient_item, ddeclient_item, ddeerror_item,
                                    std::string , ddevalue_item, ddereport_value_items, ddereport_value_item, ddeevent_value_item,
                                    ddecommand_item >() , intf(inf), group(grp) {}

            virtual ~ddeintf();

            virtual bool connect();

            virtual bool disconnect();

           /* interfacestate state() {
                return state_;}*/

          /*  void adderror(dvncierror& val) {}

            void clearerrors() {
                errmap.clear();}

            boost::mutex* mtx_internal() {
                return &mutex;}*/


            virtual bool add_items(const vect_ddeclient_item& clientitem, vect_ddeclient_item& serveritem, vect_ddeerror_item& errors);
            virtual bool read_values(const str_vect& servids, vect_ddevalue_item& values, vect_ddereport_value_items& reportvalues, vect_ddeevent_value_item& eventvalues, vect_ddeerror_item& errors);
            virtual bool read_values(vect_ddevalue_item& values, vect_ddereport_value_items& reportvalues, vect_ddeevent_value_item& eventvalues);
            virtual bool remove_items(const str_vect& delitem, vect_ddeerror_item& errors);
            virtual bool add_commands(const vect_ddecommand_item& commanditem, vect_ddeerror_item& errors);
            virtual bool add_report_task(indx  key, datetime start, datetime stop) {return true;}

			
            void addvalmap(std::string sid, ddevalue_item& val) {
                ddevalue_item_map::iterator itval = valitemmap.find(sid);
                if (itval != valitemmap.end())
                    itval->second = val;
                else
                    valitemmap.insert(ddevalue_item_pair(sid, val));}

            void addvalmap( HSZ hsz, HDDEDATA hData);

            bool find_by_clid(indx clid, ddeclient_item& itm) {
                ddeclient_item_map::iterator it = clt_servermap.find(clid);
                if (it == clt_servermap.end()) return false;
                itm = it->second;
                return true;}

            bool find_by_clid(indx clid) {
                ddeclient_item itm;
                return find_by_clid(clid, itm);}

            bool find_by_sid(std::string sid, ddeclient_item& itm) {
                ddeserver_item_map::iterator it = srv_clientmap.find(sid);
                if (it == srv_clientmap.end()) return false;
                itm = it->second;
                return true;}

            bool find_by_sid(std::string sid) {
                ddeclient_item itm;
                return find_by_sid(sid, itm);}

            bool remove_by_clid(indx clid) {
                ddeclient_item_map::iterator it = clt_servermap.find(clid);
                if (it == clt_servermap.end()) return false;
                clt_servermap.erase(it);
                return true;}

            bool remove_by_sid(std::string sid) {
                ddeserver_item_map::iterator it = srv_clientmap.find(sid);
                if (it == srv_clientmap.end()) return false;
                srv_clientmap.erase(it);
                return true;}

            bool additem(std::string sid, indx clid, ddeclient_item& itm) {
                ddeserver_item_map::iterator it = srv_clientmap.find(sid);
                if (it == srv_clientmap.end())
                    srv_clientmap.insert(ddeserver_item_pair(sid, itm));
                else
                    it->second = itm;

                ddeclient_item_map::iterator it2 = clt_servermap.find(clid);
                if (it2 == clt_servermap.end())
                    clt_servermap.insert(ddeclient_item_pair(clid, itm));
                else
                    it2->second = itm;
                return true;}

            bool needreqcheck(indx clid, const std::string& bnd) {
                ddeclient_item itm;
                if (!find_by_clid(clid, itm)) return true;
                return true;}

            bool setddevalue(indx clid, num64 val, num64 valid, num64 time, num64 type) {
                ddeclient_item itmtmp;
                if (find_by_clid(clid, itmtmp)) {
                    ddevalue_item tmp = {itmtmp.name,
                        val,
                        valid,
                        type};
                    addvalmap(itmtmp.name, tmp);
                    return true;}
                return false;}




        protected:

            bool cnangeactiveItems(const str_vect& chitem, vect_ddeclient_item& serveritem, vect_ddeerror_item& errors, bool active);

           // boost::mutex mutex;
          //  interfacestate state_;
            tagsbase_ptr intf;
            indx group;
            int_dvncierror_map errmap;
            abstr_dde_util_ptr dde_spec;
            ddevalue_item_map valitemmap;
            ddeclient_item_map  clt_servermap;
            ddeserver_item_map  srv_clientmap;
            //num32 connecttype;
        };}}

#endif	/* NETINTF_H */

