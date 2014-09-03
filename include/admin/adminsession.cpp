/* 
 * File:   ns_adminsession.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 * 
 * Created on 17 Март 2010 г., 19:01
 */

#include <admin/adminsession.h>

namespace dvnci {
    namespace admin {

        using namespace dvnci::rpc;

        bool adminsession::preparerequest(rpcmessage& in, rpcmessage& out) {


            switch (in.type()) {
                case RPC_OPERATION_REQ_ENTITYSIGS:
                {
                    generate<req_entitysigs, resp_entitysigs >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_TAGS:
                {
                    generate<req_tags, resp_tags >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_SENDTAGS:
                {
                    generate<req_sendtags, resp_sendtags >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_GROUPS:
                {
                    generate<req_groups, resp_groups >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_SENDGROUPS:
                {
                    generate<req_sendgroups, resp_sendgroups >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_AGROUPS:
                {
                    generate<req_agroups, resp_agroups >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_SENDAGROUPS:
                {
                    generate<req_sendagroups, resp_sendagroups >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_USERS:
                {
                    generate<req_users, resp_users >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_SENDUSERS:
                {
                    generate<req_sendusers, resp_sendusers >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_ACCESSRULES:
                {
                    generate<req_accessrules, resp_accessrules >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_SENDACCESSRULES:
                {
                    generate<req_sendaccessrules, resp_sendaccessrules >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_SERVICES:
                {
                    generate<req_services, resp_services >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_SENDSERVICES:
                {
                    generate<req_sendservices, resp_sendservices >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_METAS:
                {
                    generate<req_metas, resp_metas >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_SENDMETAS:
                {
                    generate<req_sendmetas, resp_sendmetas >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_ADDENTITY:
                {
                    generate<req_addentity, resp_addentity >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_DUPENTITY:
                {
                    generate<req_dupentity, resp_dupentity >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_REMOVEENTITY:
                {
                    generate<req_removeentity, resp_removeentity >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_CONFIG:
                {
                    generate<req_config, resp_config >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_SENDCONFIG:
                {
                    generate<req_sendconfig, resp_sendconfig >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_ADMINOPERATION:
                {
                    generate<req_adminoperation, resp_adminoperation>(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_AUTORIZATION:
                {
                    generate<req_autorization, resp_autorization >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_JOURNAL:
                {
                    generate<req_journal, resp_journal >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_DEBUG:
                {
                    generate<req_debug, resp_debug >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_ALARMS:
                {
                    generate<req_alarms, resp_alarms >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_REGISTRY:
                {
                    generate<req_registry, resp_registry >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_COMMANDS:
                {
                    generate<req_commands, resp_commands >(in, out);
                    break;
                }
                case RPC_OPERATION_REQ_CLIENTS:
                {
                    generate<req_clients, resp_clients >(in, out);
                    break;
                }
                default:
                {
                    out = rpcmessage();
                }
            }

            return true;
        }
    }
}




