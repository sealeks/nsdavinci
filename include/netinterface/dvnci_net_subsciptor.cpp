/* 
 * File:   dvnci_net_subsciptor.cpp
 * Author: Serg
 * 
 * Created on 23 Р�СЋР»СЊ 2010 Рі., 18:51
 */

#include <netinterface/dvnci_net_subsciptor.h>

namespace dvnci {
    namespace net {

        bool dvnci_net_subsciptor::initialize_impl() {
                extinf = factory::build(intf->groups()->host(group),
                        intf->groups()->port(group),
                        intf->groups()->user(group),
                        intf->groups()->password(group),
                        intf->groups()->timeout(group));
                return extinf;}


        bool dvnci_net_subsciptor::prepare_add_items(vect_client_item& clientitems) {
            clientitems.clear();
            for (indx_set::iterator it = add_req_items.begin(); it != add_req_items.end(); ++it) {
                if (intf->exists(*it)){
                client_item tmp = {*it, intf->binding(*it), intf->type(*it),
                                    num64_cast<double>(intf[*it]->devdb())};
                clientitems.push_back(tmp);}}
            return (!add_req_items.empty());}

        bool dvnci_net_subsciptor::prepare_add_command(vect_command_item& cmditems) {
                  cmditems.clear();
                  command_vector cmds;
                  intf->select_commands(cmds, group);
                  if (!cmds.empty()) {
                      cmditems.clear();
                      for (command_vector::const_iterator it = cmds.begin(); it != cmds.end(); ++it) {
                                num64 servkey = serverkey(it->tagid());
                                DEBUG_STR_VAL_DVNCI(TGID, it->tagid())
                                DEBUG_STR_VAL_DVNCI(SERVKEY, servkey)
                                if ((intf->exists(it->tagid())) && (servkey>-1)) {
                                    command_item tmp = { servkey, it->value_set<num64>(), intf->type(it->tagid()), true, "" , ""};
                                    cmditems.push_back(tmp);}}}
                      return (!cmditems.empty());}



        short_value & operator<<(short_value& lv, const value_item&  rv) {
            return lv/*short_value()(rv.val, rv.type, rv.valid, 0, cast_datetime_fromnum64(rv.time))*/;}


}}