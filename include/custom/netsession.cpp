/* 
 * File:   ns_adminsession.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 * 
 * Created on 17 Март 2010 г., 19:01
 */

#include <custom/netsession.h>

namespace dvnci {
    namespace custom {
        namespace net {

            using boost::asio::ip::tcp;
            using namespace dvnci::rpc;


            bool netsession::preparerequest(rpcmessage& in, rpcmessage& out) {


                switch (in.type()) {
                    case RPC_OPERATION_REQ_AUTH:{
                        generate<req_auth, resp_auth > (in, out);
                        break;}
                    case RPC_OPERATION_REQ_ADD_ITEMS:{
                        generate<req_add_items, resp_add_items > (in, out);
                        break;}
                    case RPC_OPERATION_REQ_ADD_ITEMS_EX:{
                        generate<req_add_items_ex, resp_add_items_ex > (in, out);
                        break;}
                    case RPC_OPERATION_REQ_REMOVE_ITEMS:{
                        generate<req_remove_items, resp_remove_items > (in, out);
                        break;}
                    case RPC_OPERATION_REQ_DATA_ITEM:{
                        generate<req_data_item, resp_data_item > (in, out);
                        break;}
                    case RPC_OPERATION_REQ_DATA_ITEM1:{
                        generate<req_data_item1, resp_data_item > (in, out);
                        break;}
                    case RPC_OPERATION_REQ_DATA_ITEM_EX:{
                        generate<req_data_item_ex, resp_data_item_ex > (in, out);
                        break;}
                    case RPC_OPERATION_REQ_DATA_ITEM_EX1:{
                        generate<req_data_item_ex1, resp_data_item_ex > (in, out);
                        break;}
                    case RPC_OPERATION_REQ_SEND_COMMANDS:{
                        generate<req_send_commands, resp_send_commands > (in, out);
                        break;}
                    case RPC_OPERATION_REQ_REPORTTASK:{
                        generate<req_reporttask, resp_reporttask > (in, out);
                        break;}
                    case RPC_OPERATION_REQ_EVENTTASK:{
                        generate<req_eventtask, resp_eventtask > (in, out);
                        break;}
                    case RPC_OPERATION_REQ_TRENDTASK:{
                        generate<req_trendtask, resp_trendtask > (in, out);
                        break;}
                    case RPC_OPERATION_REQ_ALARMS:{
                        generate<req_alarms, resp_alarms > (in, out);
                        break;}
                    case RPC_OPERATION_REQ_JOURNAL:{
                        generate<req_journal, resp_journal > (in, out);
                        break;}
                    default:{
                        out.build_message("", 0);}}

                return true;}}}}




