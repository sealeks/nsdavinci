/* 
 * File:   NSLoaderThread.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 * 
 * Created on 22 Декабрь 2009 г., 22:19
 */

#include <admin/adminintf.h>

#include "interfaceproccessor.h"
#include "form_admin.h"

namespace dvnci {
    namespace admin {

        bool transactionmain_proccess::operator()() {
            while (!terminated()) {
                boost::xtime xt;
                if (init()) {
                    basetransaction_ptr transact;
                    if (gettransaction(transact)) {
                        invoke(transact);
                        addmillisec_to_now(xt, 50);}
                    else addmillisec_to_now(xt, 200);}
                else addmillisec_to_now(xt, 1000);
                boost::thread::sleep(xt);}
            return true;}

        void transactionmain_proccess::invoke(basetransaction_ptr& transact) {

            QApplication::postEvent(targetWidget,
                    new utevent(ACTION_TRANSACTIONSTART, "Start transaction"));

            btevent* event = 0;

            try {
                adminintf_ptr intf = transact->intf;
                if (intf) {
                    event = new btevent(transact);
                    switch (transact->transactid) {

                        case ACTION_SHORTITEMINFO:{
                            intf->select_entities(transact->entity_type, event->infomap, transact->entity_index,
                                                                transact->parameter_str);
                            break;}

                        case ACTION_SETFILTERED:{
                            if ((nodetp_child_by_parent(transact->entity_findertype)) && (!transact->filter_str.empty()))
                                intf->find_entities(nodetp_child_by_parent(transact->entity_findertype) ,
                                    event->infomap, transact->filter_str);
                            else event->infomap.clear();
                            break;}

                        case ACTION_FULLITEMINFO:{
                            intf->load_entities(transact->entity_type, event->indexset);
                            propman.intf(intf);
                            propman.parsenodes(transact->nodesmap, event->property_map);
                            break;}

                        case ACTION_SETFULLITEMINFO:{
                            propman.intf(intf);
                            propman.merge(transact->nodesmap, transact->propertymap);
                            intf->merge_entities(transact->entity_type, event->indexset, event->infomap);
                            break;}

                        case ACTION_CREATEITEM:{
                            intf->insert_entity(nodetp_child_by_parent(transact->entity_type),
                                        transact->entity_index, event->infopair, transact->parameter_str);
                            break;}

                        case ACTION_DELETEITEM:{
                            intf->delete_entities(transact->entity_type, event->indexset);
                            break;}

                        case ACTION_CHANGEGROUP:{
                            intf->change_parent_entities(NT_TAG, event->indexset, transact->parameter_index);
                            event->parameter_index = transact->parameter_index;
                            break;}

                        case ACTION_CHANGEALARMGROUP:{
                            intf->change_parent_entities(NT_ATAG, event->indexset, transact->parameter_index);
                            event->parameter_index = transact->parameter_index;
                            break;}

                        case ACTION_DUPLICATEITEM:{
                            intf->duplicate_entity(NT_GROUP, transact->entity_index , transact->parameter_str, event->infopair);
                            event->parameter_index= transact->parameter_index;
                            break;}

                        case ACTION_CONNECTSERVER:{
                            if (intf->state() ==adminintf::disconnected) {
                                std::string host = "";
                                std::string port = "";
                                unsigned int tout;
                                std::string admin = "";
                                std::string password = "";
                                parse_servinfo(transact->parameter_str, host, port, tout, admin, password);
                                intf->host(host, port, tout);
                                intf->connect(admin, password);
                                event->result = (intf->state() ==adminintf::connected);}
                            else event->result = false;
                            break;}

                        case ACTION_DISCONNECTSERVER:{
                            if (intf->state() ==adminintf::connected) {
                                intf->disconnect();
                                event->result = (intf->state() ==adminintf::disconnected);}
                            else event->result = false;
                            break;}

                        case ACTION_MAPPROJECT:{
                            if (intf->state() ==adminintf::disconnected) {
                                intf->connect();
                                event->result = (intf->state() ==adminintf::connected);}
                            else event->result = false;
                            break;}

                        case ACTION_UNMAAPPROJECT:{
                            if (intf->state() ==adminintf::connected) {
                                intf->operation_unmapprj();
                                event->result = (intf->state() ==adminintf::disconnected);}
                            else event->result = false;
                            break;}

                        case ACTION_NEWPROJECT:{
                            if (intf->state() ==adminintf::disconnected) {
                                intf->connect();
                                event->result = (intf->state() ==adminintf::connected);}
                            else event->result = false;
                            break;}

                        case ACTION_INCCOUNTALL:{
                            intf->operation_setallcounter();
                            break;}

                        case ACTION_DECCOUNTALL:{
                            intf->operation_setallcounter(false);
                            break;}

                        case ACTION_SETALL_VALID:{
                            intf->operation_setallvalid(100);
                            break;}

                        case ACTION_SETALL_INVALID:{
                            intf->operation_setallvalid(0);
                            break;}

                        case ACTION_KVIT:{
                            intf->operation_kvit();
                            break;}

                        case ACTION_KVIT_GROUP:{
                            intf->operation_kvitgroup(transact->parameter_index);
                            break;}

                        case ACTION_KVIT_AGROUP:{
                            intf->operation_kvitagroup(transact->parameter_index);
                            break;}

                        case ACTION_INCCOUNT:{
                            intf->operation_setcounter(transact->parameter_index);
                            break;}

                        case ACTION_DECCOUNT:{
                            intf->operation_setcounter(transact->parameter_index, false);
                            break;}

                        case ACTION_SET_VALID:{
                            intf->operation_setvalid(transact->parameter_index, FULL_VALID);
                            break;}

                        case ACTION_SET_INVALID:{
                            intf->operation_setvalid(transact->parameter_index, NULL_VALID);
                            break;}

                        case ACTION_SET_VALUE:{
                            intf->operation_setvalue(transact->parameter_index, transact->parameter_str, FULL_VALID);
                            break;}

                        case ACTION_SET_COMMAND:{
                            intf->operation_send_command(transact->parameter_index, transact->parameter_str, true);
                            break;}

                        case ACTION_SET_STARTSERVICE:{
                            intf->operation_startservice(transact->entity_index);
                            break;}

                        case ACTION_SET_STOPSERVICE:{
                            intf->operation_stopservice(transact->entity_index);
                            break;}}}}

            catch (dvncierror& err) {
                if (event) delete event;
                entity_map mp;
                event = new btevent(ACTION_FAILCONNECT, mp);
                if (transact->curitem) event->curitem = transact->curitem->intfroot();
                if (transact->intf) err.str(transact->intf->named());
               /*transact->intf->adderror(err);*/}



            if (event) QApplication::postEvent(targetWidget, event);
            QApplication::postEvent(targetWidget,
                    new utevent(ACTION_ALLTRANSDONE, "Transaction success"));};

        void transactionmain_proccess::addtransaction(basetransaction_ptr transact) {
            THD_EXCLUSIVE_LOCK(mtx);
            transactions.push_back(transact);};

        bool transactionmain_proccess::gettransaction(basetransaction_ptr& transact) {
            THD_EXCLUSIVE_LOCK(mtx);
            if (transactions.empty()) return false;
            basetransaction_ptr_vect::iterator it = transactions.begin();
            if (it == transactions.end()) return false;
            transact = *it;
            transactions.erase(it);
            return static_cast<bool>(transact);}

        bool transactionview_proccess::operator()() {

            while (!terminated()) {
                boost::xtime xt;
                if (init()) {
                    viewtransaction_ptr transact;
                    if (gettransaction(transact)) {
                        invoke(transact);
                        addmillisec_to_now(xt, 50);}
                    else addmillisec_to_now(xt, 200);}
                else addmillisec_to_now(xt, 1000);
                boost::thread::sleep(xt);}
            return true;}

        void transactionview_proccess::invoke(viewtransaction_ptr& transact) {

            vtevent* event=0;

            try {
               
                adminintf_ptr intf = transact->intf;
                if (intf) {
                    event = new vtevent(transact);
                    switch (transact->transactid) {


                        case ACTION_VIEWTAG:{
                            intf->find_entities(NT_TAG, event->infomap, transact->parameter_str);
                            intf->load_entities(NT_TAG, transact->inputset);
                            break;}

                        case ACTION_VIEWGROUP:{
                            intf->find_entities(NT_GROUP, event->infomap, transact->parameter_str);
                            intf->load_entities(NT_GROUP, transact->inputset);
                            break;}

                        case ACTION_VIEWACCESSRULE:{
                            intf->find_entities(NT_ACCESSRULE, event->infomap);
                            intf->load_entities(NT_ACCESSRULE, transact->inputset);
                            break;}

                        case ACTION_VIEWREGISTRY:{
                            intf->read_view(NT_REGISTRY);
                            break;}

                        case ACTION_VIEWALARMS:{
                            intf->read_view( NT_ALARM);
                            break;}

                        case ACTION_VIEWCLIENTS:{
                            intf->read_view(NT_CLIENT);
                            break;}

                        case ACTION_VIEWCOMMANDS:{
                            intf->read_view(NT_COMMAND);
                            break;}

                        case ACTION_VIEWDEBUG:{
                            intf->read_view(NT_LOG);
                            break;}

                        case ACTION_VIEWJOURNAL:{
                            intf->read_view(NT_JOURNAL);
                            break;}}}}

            catch (dvncierror& err) {
                if (event) delete event;
                event = new vtevent(ACTION_FAILCONNECT);
                if (transact->curitem) event->curitem = transact->curitem->intfroot();
                if (transact->intf) err.str(transact->intf->named());
                /*transact->intf->adderror(err);*/}

            if (event) QApplication::postEvent(targetWidget, event);};

        void transactionview_proccess::addtransaction(viewtransaction_ptr transact) {
            THD_EXCLUSIVE_LOCK(mtx);
            transactions.push_back(transact);};

        bool transactionview_proccess::gettransaction(viewtransaction_ptr& transact) {
            THD_EXCLUSIVE_LOCK(mtx);
            if (transactions.empty()) return false;
            viewtransaction_ptr_vect::iterator it = transactions.begin();
            if (it == transactions.end()) return false;
            transact = *it;
            transactions.erase(it);
            return static_cast<bool>(transact);
        }

}}