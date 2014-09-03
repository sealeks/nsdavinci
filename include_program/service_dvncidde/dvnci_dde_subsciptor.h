/* 
 * File:   dvnci_net_subsciptor.h
 * Author: Serg
 *
 * Created on 23 �?юль 2010 г., 18:51
 */

#ifndef DVNCI_DDE_SUBSCIPTOR_H
#define	DVNCI_DDE_SUBSCIPTOR_H



#include <kernel/utils.h>

#include "ddeintf.h"


namespace dvnci {
    namespace dde {

        short_value& operator<<(short_value& lv, const ddevalue_item& rv);

        class dvnci_dde_subsciptor : public abstract_subscriptor<ddeintf> {

        public:

            dvnci_dde_subsciptor(tagsbase_ptr inf, indx grp, const metalink& lnk, tagtype provide_man = TYPE_SIMPL) :
            abstract_subscriptor<ddeintf>(inf, grp, metalink()) {
            }

        protected:

            virtual bool initialize_impl() {
                extinf = ddeintf_ptr(new ddeintf(intf, group));
                return extinf;
            }

            /*virtual bool invokereq() {


                if (!init()) {
                    DEBUG_STR_DVNCI(NOTINIT);
                    return false;}

                try {
                    vect_ddeclient_item req_add;
                    if (prepare_add_items(req_add)) {

                        vect_ddeclient_item serveritem_tmp;
                        vect_ddeerror_item errors_tmp;

                        if (extinf->add_items(req_add, serveritem_tmp, errors_tmp)) {
                            for (vect_ddeclient_item::const_iterator it = serveritem_tmp.begin(); it != serveritem_tmp.end(); ++it) {
                                sid_clid_registry.add(it->name, static_cast<indx> (it->key));}

                            for (vect_ddeerror_item::const_iterator iter = errors_tmp.begin(); iter != errors_tmp.end(); ++iter) {
                                error(static_cast<indx>(iter->key), static_cast<ns_error>(iter->code));}}
                        add_req_items.clear();}


                    if (group!=npos) {
                        command_vector cmds;
                        intf->getcommandmap(cmds, group);
                        if (!cmds.empty()) {
                            vect_ddecommand_item commanditem;
                            for (command_vector::const_iterator it = cmds.begin(); it != cmds.end(); ++it) {
                                ddecommand_item tmp;
                                std::string servkey = serverkey(it->tagid());
                                DEBUG_STR_VAL_DVNCI(TGID, it->tagid())
                                DEBUG_STR_VAL_DVNCI(SERVKEY, servkey)
                                if ((intf->exists(it->tagid())) && (servkey!="")) {
                                    tmp.outkey = servkey;
                                    tmp.val = it->value_set<num64>();
                                    tmp.type = intf->type(it->tagid());
                                    tmp.queue = true;
                                    tmp.user = it->user();
                                    tmp.pass = "";
                                    commanditem.push_back(tmp);}}
                            if (!commanditem.empty()) {
                                vect_ddeerror_item errors_tmp;
                                DEBUG_STR_VAL_DVNCI(FINDCOMMAND, commanditem.size())
                                extinf->add_commands(commanditem, errors_tmp);}}}

                    if (!sid_clid_registry.empty()) {
                        str_vect sids;
                        vect_ddeerror_item terrors;
                        typedef std::pair<indx, std::string> testpair;
                        typedef std::map<indx, std::string, std::less<indx>, std::allocator<testpair> >::const_iterator testiterator;
                        for (testiterator it = sid_clid_registry.secondmap().begin();
                                it != sid_clid_registry.secondmap().end(); ++it) {
                            sids.push_back(it->second);}

                        vect_ddevalue_item values_tmp;
                        vect_ddereport_value_items report_values_tmp;
                        vect_ddeevent_value_item eventval_tmp;

                        bool tmp = false;
                        tmp = extinf->read_values(sids, values_tmp, report_values_tmp, eventval_tmp,  terrors);
                        if (tmp) {
                            set_values(values_tmp);}}


                    str_vect delitems;
                    if (prepare_del_items(delitems)) {
                        vect_ddeerror_item errors_tmp;
                        if (extinf->remove_items(delitems, errors_tmp)) {
                            del_req_items.clear();}}}
                catch (dvncierror& err_) {
                    if ((err_.code() == ERROR_FAILNET_CONNECTED) || (err_.code() == ERROR_NONET_CONNECTED)) {
                        DEBUG_STR_DVNCI(THROWING RICH invokereq)
                        uninit();
                        return false;}} catch (...) {}
                return true;}*/



            bool prepare_add_items(vect_ddeclient_item& clientitems) {
                clientitems.clear();
                for (indx_set::iterator it = add_req_items.begin(); it != add_req_items.end(); ++it) {
                    ddeclient_item tmp;
                    tmp.key = *it;
                    tmp.name = intf->binding(*it);
                    tmp.tpitem = intf->type(*it);
                    clientitems.push_back(tmp);
                }
                return (!add_req_items.empty());
            }

            virtual std::string nill_server_key() const {
                return "";
            }

        };
    }
}

#endif	/* DVNCI_NET_SUBSCIPTOR_H */

