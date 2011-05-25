/* 
 * File:   ns_adminsession.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 * 
 * Created on 17 Март 2010 г., 19:01
 */

#include <netinterface/netsession.h>

namespace dvnci {
    namespace net {

        using boost::asio::ip::tcp;
        using namespace dvnci::rpc;

        boost::mutex netsession::mutex;

        bool netsession::preparerequest(rpcmessage& in, rpcmessage& out) {


            switch (in.type()) {
                case RPC_OPERATION_REQ_ITEMS:{
                    generate<req_items, resp_items > (in, out);
                    break;}
                case RPC_OPERATION_REQ_VALUES:{
                    generate<req_values, resp_values > (in, out);
                    break;}
                case RPC_OPERATION_REQ_VALUES_EX:{
                    generate<req_values_ex, resp_values_ex > (in, out);
                    break;}
                case RPC_OPERATION_REQ_REMITEMS:{
                    generate<req_remitems, resp_remitems > (in, out);
                    break;}
                case RPC_OPERATION_REQ_COMMANDS:{
                    generate<req_commands, resp_commands > (in, out);
                    break;}
                case RPC_OPERATION_REQ_REPORTTASK:{
                    generate<req_reporttask, resp_reporttask > (in, out);
                    break;}
                default:{
                    out.build_message("", 0);}}

            return true;}}}




