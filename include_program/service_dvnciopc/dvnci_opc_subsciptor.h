/* 
 * File:   dvnci_net_subsciptor.h
 * Author: Serg
 *
 * Created on 23 Июль 2010 г., 18:51
 */

#ifndef DVNCI_OPC_SUBSCIPTOR_H
#define	DVNCI_OPC_SUBSCIPTOR_H



#include "kernel/interface_proccesstmpl.h"
#include "kernel/constdef.h"
#include "kernel/memfile.h"
#include "kernel/utils.h"
#include "kernel/systemutil.h"
#include "kernel/serviceapp.h"
#include "kernel/utils.h"
#include "opcintf.h"
#include <algorithm>


namespace dvnci {
    namespace opc {

        const short_value& operator<<(short_value& lv, const opcvalue_item&  rv);

        class dvnci_opc_subsciptor : public abstract_subscriptor<opcintf, TYPE_SIMPL> {
        public:

            dvnci_opc_subsciptor(tagsbase_ptr inf, indx grp, const metalink& lnk, tagtype provide_man = TYPE_SIMPL) : abstract_subscriptor<opcintf, TYPE_SIMPL>(inf, grp, metalink()) {}

        protected:

            virtual bool initialize_impl() {
                extinf = opcintf_ptr(new opcintf(intf, group));
                return extinf;}

            virtual bool  prepare_add_items(vect_opcclient_item& clientitems) {
                clientitems.clear();
                for (indx_set::iterator it = add_req_items.begin(); it != add_req_items.end(); ++it) {
                    if (intf->exists(*it)){
                    opcclient_item tmp = { *it, 0 , intf->type(*it), intf->binding(*it), intf[*it]->devdb(), L""};
                    clientitems.push_back(tmp);}
                return (!add_req_items.empty());}}

            virtual bool prepare_add_command(vect_opccommand_item& cmditems) {
                  cmditems.clear();
                  command_vector cmds;
                  intf->select_commands(cmds, group);
                  if (!cmds.empty()) {
                      cmditems.clear();
                      for (command_vector::const_iterator it = cmds.begin(); it != cmds.end(); ++it) {
                                indx servkey = serverkey(it->tagid());
                                DEBUG_STR_VAL_DVNCI(TGID, it->tagid())
                                DEBUG_STR_VAL_DVNCI(SERVKEY, servkey)
                                if ((intf->exists(it->tagid())) && (servkey>-1)) {
                                    opccommand_item tmp = { servkey, it->value_set<num64>() , 
                                                                     it->type(), true, "", ""};
                                    cmditems.push_back(tmp);}}}
                      return (!cmditems.empty());}

             virtual indx nill_server_key() const {return -1;}

};}}

#endif	/* DVNCI_NET_SUBSCIPTOR_H */

