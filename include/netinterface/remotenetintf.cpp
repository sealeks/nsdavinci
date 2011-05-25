/* 
 * File:   netintf.cpp
 * Author: Serg
 * 
 * Created on 20 Июль 2010 г., 14:24
 */



#include <netinterface/remotenetintf.h>

namespace dvnci {
    namespace net {

        bool remotenetintf::connect_() {
            try {
                DEBUG_STR_DVNCI(connect_)
                client_io->connect(host, port, tmout);
                _state = (client_io->state() == client_io->connected ) ? connected :  disconnected;
                if (client_io->state() == client_io->connected) {}
                else {
                    dvncierror tmperr(ERROR_BASENOTFOUND);
                    /*adderror(tmperr);*/}}

            catch (...) {
                _state = (client_io->state() == client_io->connected ) ? connected :  disconnected;
                if (client_io->state() == client_io->connected) {
                    dvncierror tmperr(ERROR_BASENOTFOUND);
                    /*adderror(tmperr);*/;}}

            return (_state == connected);}

        bool remotenetintf::disconnect_() {
            try {
                client_io->disconnect();
                _state = (client_io->state() == client_io->connected ) ? connected :  disconnected;}
            catch (...) {
                _state = (client_io->state() == client_io->connected ) ? connected :  disconnected;}

            return (_state == disconnected);}

        bool remotenetintf::add_items(const vect_client_item& clientitem, vect_server_item& serveritem , vect_error_item& errors) {
            try {
                req_items req;
                resp_items resp;
                assign_req_items(req, clientitem);
                DEBUG_STR_DVNCI(ADDITEMS)
                DEBUG_VAL_DVNCI(req.cl_items.size())
                if (querytmpl<req_items, resp_items, RPC_OPERATION_REQ_ITEMS, RPC_OPERATION_RESP_ITEMS > (req, resp)) {
                    assign_resp_items(resp, serveritem, errors);}
                else
                    DEBUG_STR_DVNCI(querytmpl not success)}
            catch (dvncierror& err_) {
                if ((err_.code() == ERROR_FAILNET_CONNECTED) || (err_.code() == ERROR_NONET_CONNECTED)) throw err_;
                /*adderror(err_)*/;}
            catch (...) {
                dvncierror tmperr(NS_ERROR_ERRRESP);
                /*adderror(tmperr);*/;}
            return true;}

        bool remotenetintf::read_values(const num64_vect& servids, vect_value_item& values, vect_report_value_items& reportvalues,  vect_event_value_item& eventvalues, vect_error_item& errors) {
            eventvalues.clear();
            try {
                req_values req;
                resp_values resp;
                assign_req_values(req, servids);
                if (querytmpl<req_values, resp_values, RPC_OPERATION_REQ_VALUES, RPC_OPERATION_RESP_VALUES > (req, resp)) {
                    assign_resp_values(resp, values, reportvalues, errors);}}
            catch (dvncierror& err_) {
                if ((err_.code() == ERROR_FAILNET_CONNECTED) || (err_.code() == ERROR_NONET_CONNECTED)) throw err_;
                /*adderror(err_)*/;}
            catch (...) {
                dvncierror tmperr(NS_ERROR_ERRRESP);
                /*adderror(tmperr);*/;}
            return true;}

        bool remotenetintf::read_values(vect_value_item& values, vect_report_value_items& reportvalues, vect_event_value_item& eventvalues) {
            eventvalues.clear();
            try {
                req_values_ex req;
                resp_values_ex resp;
                assign_req_values_ex(req);
                if (querytmpl<req_values_ex, resp_values_ex, RPC_OPERATION_REQ_VALUES_EX, RPC_OPERATION_RESP_VALUES_EX > (req, resp)) {
                    assign_resp_values_ex(resp, values, reportvalues);}}
            catch (dvncierror& err_) {
                if ((err_.code() == ERROR_FAILNET_CONNECTED) || (err_.code() == ERROR_NONET_CONNECTED)) throw err_;
                /*adderror(err_)*/;}
            catch (...) {
                dvncierror tmperr(NS_ERROR_ERRRESP);
                /*adderror(tmperr);*/;}
            return true;}

        bool remotenetintf::remove_items(const num64_vect& delitem, vect_error_item& errors) {
            try {
                req_remitems req;
                resp_remitems resp;
                assign_req_remitems(req, delitem);
                DEBUG_STR_DVNCI(DELITEMS)
                DEBUG_VAL_DVNCI(req.outkey.size())
                if (querytmpl<req_remitems, resp_remitems, RPC_OPERATION_REQ_REMITEMS, RPC_OPERATION_RESP_REMITEMS > (req, resp)) {
                    assign_resp_remitems(resp, errors);}}
            catch (dvncierror& err_) {
                if ((err_.code() == ERROR_FAILNET_CONNECTED) || (err_.code() == ERROR_NONET_CONNECTED)) throw err_;
                /*adderror(err_)*/;}
            catch (...) {
                dvncierror tmperr(NS_ERROR_ERRRESP);
                /*adderror(tmperr);*/;}
            return true;}

        bool remotenetintf::add_commands(const vect_command_item& commanditem, vect_error_item& errors) {
            try {
                req_commands req;
                resp_commands resp;
                assign_req_commands(req, commanditem);
                if (querytmpl<req_commands, resp_commands, RPC_OPERATION_REQ_COMMANDS, RPC_OPERATION_RESP_COMMANDS > (req, resp)) {
                    assign_resp_remitems(resp, errors);}}
            catch (dvncierror& err_) {
                if ((err_.code() == ERROR_FAILNET_CONNECTED) || (err_.code() == ERROR_NONET_CONNECTED)) throw err_;
                /*adderror(err_)*/;}
            catch (...) {
                dvncierror tmperr(NS_ERROR_ERRRESP);
                /*adderror(tmperr);*/;}
            return true;}

        bool remotenetintf::add_report_task(num64  key, datetime start, datetime stop) {
            try {
                req_reporttask req;
                resp_reporttask resp;
                assign_req_reporttask(req, key, start, stop);
                DEBUG_STR_DVNCI(ADDREPORTTASK)
                if (querytmpl<req_reporttask, resp_reporttask, RPC_OPERATION_REQ_REPORTTASK, RPC_OPERATION_RESP_REPORTTASK > (req, resp)) {
                    ns_error error;
                    DEBUG_STR_DVNCI(ADDREPORTTASK SUCCESS)
                    assign_resp_reporttask(resp, error);}}
            catch (dvncierror& err_) {
                if ((err_.code() == ERROR_FAILNET_CONNECTED) || (err_.code() == ERROR_NONET_CONNECTED)) throw err_;
                /*adderror(err_)*/;}
            catch (...) {
                dvncierror tmperr(NS_ERROR_ERRRESP);
                /*adderror(tmperr);*/;}
            return true;}}}

