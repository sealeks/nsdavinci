/* 
 * File:   MainNsTransaction.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 26 Февраль 2010 г., 1:12
 */

#ifndef _MAINNSTRANSACTION_H
#define	_MAINNSTRANSACTION_H


#include <kernel/memfile.h>
#include <kernel/constdef.h>

#include <admin/propertymanager.h>

#include "uiwidgetitem.h"



namespace dvnci {
    namespace admin {

        typedef int guiaction;

        const guiaction ACTION_USERDEF = 1000;
        const guiaction ACTION_TRANSACTIONSTART = ACTION_USERDEF + 0x1;
        const guiaction ACTION_ALLTRANSDONE = ACTION_USERDEF + 0x2;
        const guiaction ACTION_ADDSERVER = ACTION_USERDEF + 0x5;
        const guiaction ACTION_REMOVESERVER = ACTION_USERDEF + 0x15;
        const guiaction ACTION_CONNECTSERVER = ACTION_USERDEF + 0x6;
        const guiaction ACTION_DISCONNECTSERVER = ACTION_USERDEF + 0x7;
        const guiaction ACTION_UNMAAPPROJECT = ACTION_USERDEF + 0x21;
        const guiaction ACTION_MAPPROJECT = ACTION_USERDEF + 0x22;
        const guiaction ACTION_NEWPROJECT = ACTION_USERDEF + 0x23;
        const guiaction ACTION_SHORTITEMINFO = ACTION_USERDEF + 0x11;
        const guiaction ACTION_FULLITEMINFO = ACTION_USERDEF + 0x12;
        const guiaction ACTION_SETFULLITEMINFO = ACTION_USERDEF + 0x13;
        const guiaction ACTION_VIEWTREEITEM = ACTION_USERDEF + 0x14;
        const guiaction ACTION_IMPORT = ACTION_USERDEF + 0x24;
        const guiaction ACTION_EXPORT = ACTION_USERDEF + 0x25;
        const guiaction ACTION_CREATEITEM = ACTION_USERDEF + 0x27;
        const guiaction ACTION_DELETEITEM = ACTION_USERDEF + 0x28;
        const guiaction ACTION_CHANGEGROUP = ACTION_USERDEF + 0x29;
        const guiaction ACTION_CHANGEALARMGROUP = ACTION_USERDEF + 0x30;
        const guiaction ACTION_SETFILTERED = ACTION_USERDEF + 0x31;
        const guiaction ACTION_INCCOUNTALL = ACTION_USERDEF + 0x32;
        const guiaction ACTION_DECCOUNTALL = ACTION_USERDEF + 0x33;
        const guiaction ACTION_SETALL_VALID = ACTION_USERDEF + 0x34;
        const guiaction ACTION_SETALL_INVALID = ACTION_USERDEF + 0x35;
        const guiaction ACTION_KVIT = ACTION_USERDEF + 0x36;
        const guiaction ACTION_KVIT_GROUP = ACTION_USERDEF + 0x37;
        const guiaction ACTION_KVIT_AGROUP = ACTION_USERDEF + 0x38;
        const guiaction ACTION_INCCOUNT = ACTION_USERDEF + 0x39;
        const guiaction ACTION_DECCOUNT = ACTION_USERDEF + 0x3A;
        const guiaction ACTION_SET_VALID = ACTION_USERDEF + 0x3B;
        const guiaction ACTION_SET_INVALID = ACTION_USERDEF + 0x3C;
        const guiaction ACTION_SET_VALUE = ACTION_USERDEF + 0x3D;
        const guiaction ACTION_SET_COMMAND = ACTION_USERDEF + 0x3E;
        const guiaction ACTION_SET_STARTSERVICE = ACTION_USERDEF + 0x50;
        const guiaction ACTION_SET_STOPSERVICE = ACTION_USERDEF + 0x51;
        const guiaction ACTION_DUPLICATEITEM = ACTION_USERDEF + 0x52;

        const guiaction ACTION_VIEWTAG = ACTION_USERDEF + 0x41;
        const guiaction ACTION_VIEWGROUP = ACTION_USERDEF + 0x42;
        const guiaction ACTION_VIEWREGISTRY = ACTION_USERDEF + 0x43;
        const guiaction ACTION_VIEWDEBUG = ACTION_USERDEF + 0x44;
        const guiaction ACTION_VIEWCOMMANDS = ACTION_USERDEF + 0x45;
        const guiaction ACTION_VIEWJOURNAL = ACTION_USERDEF + 0x46;
        const guiaction ACTION_VIEWALARMS = ACTION_USERDEF + 0x47;
        const guiaction ACTION_VIEWACCESSRULE = ACTION_USERDEF + 0x49;
        const guiaction ACTION_VIEWCLIENTS = ACTION_USERDEF + 0x4A;

        const guiaction ACTION_FAILCONNECT = ACTION_USERDEF + 0x48;


        typedef std::pair<guiaction, QObject* > guiaction_action_pair;
        typedef std::map<guiaction, QObject*, std::less<guiaction>, std::allocator<guiaction_action_pair > > guiaction_action_map;

        typedef std::pair<nodetype, guiaction_action_map > nodetype_actionmap_pair;
        typedef std::map<nodetype, guiaction_action_map, std::less<nodetype>, std::allocator<nodetype_actionmap_pair > > nodetype_actionmap_map;

        class basetransaction {
        public:

            basetransaction( guiaction transid, indx_widgit_map* citms, uiwidgetitem* citm,
                    entity_map& nodesmp, propertytable_map& propertmp,
                    nodetype typend = 0, std::string str = "", indx ind = npos) :
                        nodesmap(nodesmp), propertymap(propertmp), intf(){
                
                transactid =        transid;
                curitems =          citms;
                curitem =           citm;
                entity_index =      citm ?  citm->key() : npos;
                entity_type =       typend;
                parameter_str  =    str;
                parameter_index =   ind;
                //strcriteria =       "";
                if (curitem) {
                    entity_findertype = curitem->filtertype();
                    intf = curitem->intf();}
                if (curitem->isfiltered()) filter_str = curitem->strciteria();}

            virtual ~basetransaction() {};

            guiaction          transactid;

            entity_map&        nodesmap;
            propertytable_map& propertymap;
            adminintf_ptr      intf;

            indx_widgit_map*  curitems;
            uiwidgetitem*     curitem;

            nodetype          entity_type;
            indx              entity_index;
            nodetype          entity_findertype;

            indx              parameter_index;
            std::string       parameter_str;
		    std::string       filter_str;} ;

        typedef boost::shared_ptr<basetransaction>          basetransaction_ptr;

        class viewtransaction {
        public:

            viewtransaction( guiaction transid, uiwidgetitem* curit, indx_set& st) : inputset(st) {
                transactid = transid;
                curitem = curit;
                if (curitem) {
                    intf = curitem->intf();}
                if (curitem->isfiltered()) 
                    parameter_str = curitem->strciteria();}

            virtual ~viewtransaction() {};

            indx_set&     inputset;
            guiaction     transactid;
            uiwidgetitem* curitem;
            adminintf_ptr intf;
            std::string   parameter_str;
		    std::string   filter_str;} ;

        typedef boost::shared_ptr<viewtransaction>          viewtransaction_ptr;

        class btevent : public QEvent  {
        public:

            btevent(guiaction transid, entity_map& mp) : QEvent(static_cast<QEvent::Type> (transid)) ,
                    transactid(transid), nodesmap(mp) {};

            btevent(basetransaction_ptr transact) : QEvent(static_cast<QEvent::Type> (transact->transactid)) ,
                   nodesmap(transact->nodesmap) {
                curitem =       transact->curitem;
                curitems =      transact->curitems;
                intf =          transact->intf;
                parameter_str = transact->parameter_str;
                nodesmap      = transact->nodesmap;
                entity_index  = transact->entity_index;
                parameter_index = transact->parameter_index;
				filter_str = transact->filter_str;
                result = false;
                entity_map::iterator it = nodesmap.begin();
                while (it != nodesmap.end()) {
                    indexset.insert(it->first);
                    it++;};
                typenode = transact->entity_type;
                infomap.clear();};

            guiaction transactid;

            QString message;

            nodetype          typenode;
            entity_map&       nodesmap;
            indx_widgit_map*  curitems;
            uiwidgetitem*     curitem;
            adminintf_ptr     intf;
            indx              entity_index;
            std::string       parameter_str;
			std::string       filter_str;
            indx              parameter_index;
            propertytable_map property_map;
            iteminfo_map      infomap;
            iteminfo_pair     infopair;
            indx_set          indexset;
            bool              result;} ;

        class vtevent : public QEvent  {
        public:

            vtevent(guiaction transactid_) : QEvent(static_cast<QEvent::Type> (transactid_)) , transactid(transactid_) {};

            vtevent(viewtransaction_ptr transact) : QEvent(static_cast<QEvent::Type> (transact->transactid)) {
                curitem = transact->curitem;
                intf = transact->intf;};

            guiaction        transactid;
            indx_widgit_map* curitems;
            uiwidgetitem*    curitem;
            adminintf_ptr    intf;
            indx_set         indexset;
            iteminfo_map     infomap;} ;



        class utevent : public QEvent {
        public:

            utevent(guiaction transactid, QString msg_, int progre_ = 0) :
            QEvent(static_cast<QEvent::Type> (transactid)) {
                msg = msg_;
                progress_ = progre_;};

            QString messagetxt() {
                return msg;}

            int progress() {
                return progress_;}
        private:
            QString msg;
            int progress_;} ;

        typedef std::vector<basetransaction_ptr>          basetransaction_ptr_vect;
        typedef std::vector<viewtransaction_ptr>          viewtransaction_ptr_vect;
}}

#endif	/* _MAINNSTRANSACTION_H */

