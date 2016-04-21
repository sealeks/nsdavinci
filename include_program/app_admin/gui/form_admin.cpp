/*
 * File:   form_admin.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 27 Ноябрь 2009 г., 19:15
 */


#include "form_admin.h"

dvnci::executable_ptr   dvnci::mainserv;
std::string  dvnci::DVNCI_SERVICE_NAME="";
dvnci::appidtype dvnci::DVNCI_SERVICE_APPID=0;

#define REGIST_ADMIN_ACTION(act,actid,actname,btn)\
        act## = new QAction(getIcon(actid##),qtstr_translate(QString::fromStdString("#actname")), mainTreeMenue);\
        act##->connect(act##,SIGNAL(triggered()), this, SLOT(proc_act##()));\
        mainTreeMenue->addAction(act##);\
        treeMenuList->append(act##);\
        connect(widget.btn##, SIGNAL(clicked()),  this, SLOT(proc_act##()));\
        widget.btn##->setToolTip(qtstr_translate(QString::fromStdString("#actname")));\
        actionmaps.insert(guiaction_action_pair(actid##,act##));\




namespace dvnci {
    namespace admin {

        using namespace std;

        void registmainicon(icon_map* icons) {
            try {
                icons->insert(icon_pair(nodeinfotype(NT_VIS_CASCADE, 0),  QIcon(":icon/icon/cascadkind.png")));
                icons->insert(icon_pair(nodeinfotype(NT_VIS_LINE, 0), QIcon(":icon/icon/linekind.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_ADDSERVER, 0),  QIcon(":icon/icon/addserver.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_REMOVESERVER, 0), QIcon(":icon/icon/removeserver.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_CONNECTSERVER, 0), QIcon(":icon/icon/connectserver.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_DISCONNECTSERVER, 0), QIcon(":icon/icon/connectserver.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_UNMAAPPROJECT, 0), QIcon(":icon/icon/unmaproject.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_MAPPROJECT, 0), QIcon(":icon/icon/maproject.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_NEWPROJECT, 0), QIcon(":icon/icon/newproject.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_SETFILTERED, 0), QIcon(":icon/icon/addfilter.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_SETFILTERED_ON, 0), QIcon(":icon/icon/addfilter.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_SETFILTERED_OFF, 0), QIcon(":icon/icon/removefilter.png")));

                icons->insert(icon_pair(nodeinfotype(ACTION_IMPORT, 0), QIcon(":icon/icon/import.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_EXPORT, 0), QIcon(":icon/icon/export.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_CREATEITEM, 0), QIcon(":icon/icon/new.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_DELETEITEM, 0), QIcon(":icon/icon/delete.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_CHANGEGROUP, 0), QIcon(":icon/icon/changegroup.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_CHANGEALARMGROUP, 0), QIcon(":icon/icon/changeagroup.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_DUPLICATEITEM, 0), QIcon(":icon/icon/operation_clone.png")));

                icons->insert(icon_pair(nodeinfotype(ACTION_ERRORITEM, 0), QIcon(":icon/icon/erroritem.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_OKITEM, 0), QIcon(":icon/icon/okitem.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_LOGSCREANALL, 0), QIcon(":icon/icon/logscreanall.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_LOGSCREANERROR, 0), QIcon(":icon/icon/logscreanerror.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_LOGSCREANCLEAR, 0), QIcon(":icon/icon/logscreanclear.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_SET_STARTSERVICE, 0), QIcon(":icon/icon/startservice.png")));
                icons->insert(icon_pair(nodeinfotype(ACTION_SET_STOPSERVICE, 0), QIcon(":icon/icon/stopservice.png")));}
            catch (...) {}}

        std::string namebynodetp(nodetype val) {
            switch (val) {
                case NT_GROUP:  return ".group";
                case NT_AGROUP:  return ".agroup";
                case NT_USER:  return ".user";
                case NT_TAG:  return ".tag";
                case NT_ATAG:  return ".atag";
                case NT_MF_REPHEADER:  return ".repheader";
                case NT_MF_TRENDHEADER:  return ".trendheader";
                case NT_MF_MESSHEADER:  return ".messheader";
                case NT_MF_REPARR:  return ".reparr";
                case NT_MF_UNIT:  return ".unit";
                case NT_MF_TRENDARR:  return ".trendarr";
                case NT_MF_TREND:  return ".trend";
                case NT_MF_MESSARR:  return ".messarr";
                case NT_MF_MESSAGE:  return ".message";}
            return "";}


        form_admin::form_admin() : intfcnt(0) {

            isLoading = false;
            widget.setupUi(this);
            icons     = new icon_map;
            registmainicon(icons);

            test_immi_struct();

            setWindowTitle(qtstr_translate(QString::fromStdString("mainform")));

            mainTreeMenue = new QMenu(widget.treeWidget);
            treeMenuList  = new QList<QAction*>();
            createmenue();

            nillIcon = new QIcon(":icon/icon/PrjSome.bmp");
            filterIcon = new QIcon(":icon/icon/filter.bmp");

            currtransact = 0;

            infproccess = callable_transactionmain(new transactionmain_proccess(this));
            viewproccess = callable_transactionview(new transactionview_proccess(this));

            thmain = boost::thread(infproccess);
            thview = boost::thread(viewproccess);

            screanopt(lserror);

            curitem_ = 0;
            curtreewidget_ = widget.treeWidget;

            curitems_.clear();


            treewidgetsmap.insert(int_treewidget_pair(RANG_NODE_TYPE_0, widget.treeWidget));
            treewidgetsmap.insert(int_treewidget_pair(RANG_NODE_TYPE_1, widget.treeWidget1));
            treewidgetsmap.insert(int_treewidget_pair(RANG_NODE_TYPE_2, widget.treeWidget2));

            connect(widget.treeWidget,   SIGNAL(itemClicked( QTreeWidgetItem* , int)),          this, SLOT(proc_treeclick(QTreeWidgetItem* , int)));
            connect(widget.treeWidget,   SIGNAL(customContextMenuRequested ( const QPoint& )),  this, SLOT(proc_treecontext ( const QPoint& )));
            connect(widget.treeWidget1,  SIGNAL(itemClicked( QTreeWidgetItem* , int)),          this, SLOT(proc_treeclick(QTreeWidgetItem* , int)));
            connect(widget.treeWidget1,  SIGNAL(customContextMenuRequested ( const QPoint& )),  this, SLOT(proc_treecontext ( const QPoint& )));
            connect(widget.treeWidget2,  SIGNAL(itemClicked( QTreeWidgetItem* , int)),          this, SLOT(proc_treeclick(QTreeWidgetItem* , int)));
            connect(widget.treeWidget2,  SIGNAL(customContextMenuRequested ( const QPoint& )),  this, SLOT(proc_treecontext ( const QPoint& )));
            connect(widget.btnmerge,   SIGNAL(clicked()),                                       this, SLOT(proc_mergeclick()));
            connect(widget.btnkindview,   SIGNAL(clicked()),                                    this, SLOT(proc_changeviewkindclick()));
            connect(widget.tableproperty,  SIGNAL(itemChanged(QTableWidgetItem* )),             this, SLOT(proc_itchange (QTableWidgetItem* )));
            connect(widget.tableview ,SIGNAL( form_admin::proc_valuechange ( int)),       this, SLOT(form_admin::proc_valuechange ( int )  ));
            connect(widget.btnlogtype , SIGNAL( clicked()),                                     this, SLOT(proc_logclick()));
            connect(widget.btnclearlog , SIGNAL( clicked()),                                    this, SLOT(proc_error()));
            connect(widget.btninccnt , SIGNAL( clicked()),                                      this, SLOT(proc_incallcount()));
            connect(widget.btndeccnt , SIGNAL( clicked()),                                      this, SLOT(proc_decallcount()));
            connect(widget.btnsetallvalid , SIGNAL( clicked()),                                 this, SLOT(proc_setallvalid()));
            connect(widget.btnsetallinvalid, SIGNAL( clicked()),                                this, SLOT(proc_setallinvalid()));
            connect(widget.btnstartservice , SIGNAL( clicked()),                                this, SLOT(proc_startservice()));
            connect(widget.btnstopservice, SIGNAL( clicked()),                                  this, SLOT(proc_stopservice()));
            connect(widget.btnstartservice1 , SIGNAL( clicked()),                               this, SLOT(proc_startservice()));
            connect(widget.btnstopservice1, SIGNAL( clicked()),                                 this, SLOT(proc_stopservice()));
            connect(widget.btnkvit, SIGNAL( clicked()),                                         this, SLOT(proc_kvit()));
            connect(widget.tableview, SIGNAL( doubleClicked( const QModelIndex&  )),            this, SLOT(proc_viewdouble( const QModelIndex& )));


            registmediator(NT_UTIL_MAINTABLE, new utilmediator(this, new tagsviewmodel(), ACTION_VIEWTAG));
            registmediator(NT_UTIL_GROUPTABLE, new utilmediator(this, new groupsviewmodel(), ACTION_VIEWGROUP));
            registmediator(NT_UTIL_REGISTRY, new utilmediator(this, new regystry_viewmodel(), ACTION_VIEWREGISTRY));
            registmediator(NT_UTIL_ACCESSRULES, new utilmediator(this, new accessrulesviewmodel(), ACTION_VIEWACCESSRULE));
            registmediator(NT_UTIL_CLIENTS, new utilmediator(this, new client_viewmodel(), ACTION_VIEWCLIENTS));

            registmediator(NT_UTIL_DEBUG, new utilmediator(this, new debug_viewmodel(), ACTION_VIEWDEBUG));
            registmediator(NT_UTIL_COMMAND, new utilmediator(this, new command_viewmodel(), ACTION_VIEWCOMMANDS));
            registmediator(NT_UTIL_JOURNAL, new utilmediator(this, new journal_viewmodel(), ACTION_VIEWJOURNAL));
            registmediator(NT_UTIL_ALARM, new utilmediator(this, new alarm_viewmodel(), ACTION_VIEWALARMS));

            registmediator(NT_UTIL_FINDER, new findermediator(this, ACTION_SETFILTERED));
            abstractmediator* def_mediator = (abstractmediator*) (new nullviewmediator(this));
            nodetype val3[] = { NT_ROOT, NT_ROOT_NODEF, NT_ROOT_SERVERS_NOTAVAIL, NT_ROOT_SERVERS_NOTAVAIL_R};
            registmediator((nodetype*) & val3, 4, def_mediator);
            abstractmediator* item_mediator = (abstractmediator*) (new defaultviewmediator(this, ACTION_VIEWTREEITEM));
            nodetype val2[] = { NT_ROOT_GROUPS, NT_ROOT_USERS, NT_ROOT_AGROUPS, NT_GROUP, NT_AGROUP, NT_TAG,  NT_ATAG,
                NT_USER, NT_MF_ROOT , NT_MF_HOME, NT_MF_REPLIST , NT_MF_TRENDLIST , NT_MF_MESSLIST , NT_MF_REPHEADER, NT_MF_TRENDHEADER,
                NT_MF_MESSHEADER, NT_MF_REPARR, NT_MF_UNIT, NT_MF_TRENDARR, NT_MF_TREND, NT_MF_MESSARR, NT_MF_MESSAGE, NT_ROOT_SERVERS_AVAIL,
                NT_ROOT_SERVERS_AVAIL_R, NT_ROOT_SERVICES, NT_SERVICE, NT_ROOT_ACCESSRULES, NT_ACCESSRULE};
            registmediator(val2, 28, item_mediator);
            currentmediator = def_mediator;


            widget.treeWidget->header()->setSectionsClickable(true);
            widget.viewframe->setVisible(false);
            widget.treeframe1->setVisible(false);
            widget.treeframe2->setVisible(false);

            rootitem = new uiwidgetitem(widget.treeWidget, NT_ROOT);
            rootitem->treewidgets(&treewidgetsmap);
            rootitem->setText(0, qtstr_translate("maintree.servers"));

            mediator(def_mediator);
            clearlogscreen();
            addserver();
            readserverfromconfigurator();

            resetnavigator();
            screanopt(screanOpt_);
            settoolbars();}

        form_admin::~form_admin() {
            DEBUG_STR_DVNCI(destructor form_admin);
            infproccess.terminate();
            viewproccess.terminate();
            delete rootitem;

            widget.treeWidget->clear();
            widget.treeWidget1->clear();
            widget.treeWidget2->clear();
            intf_vect.clear();

            thmain.join();
            thview.join();
            delete nillIcon;
            delete filterIcon;
            delete mainTreeMenue;
            delete treeMenuList;
            viewproccess.reset();
            treewidgetsmap.clear();
            mediators.clear();
            delete icons;}

        guiaction_action_map* form_admin::getactionregistry(nodetype val) {
            nodetype_actionmap_map::iterator it = actionregistry.find(val);
            if (it == actionregistry.end()) return 0;
            return &it->second;}

        void form_admin::registrate_action(guiaction id, nodetype val) {
            guiaction_action_map* tmp_set = getactionregistry(val);
            if (!tmp_set) {
                guiaction_action_map tmp;
                actionregistry.insert(nodetype_actionmap_pair(val, tmp));}

            guiaction_action_map::iterator it = actionmaps.find(id);
            if (it != actionmaps.end()) {
                tmp_set = getactionregistry(val);
                if (!tmp_set) return;
                tmp_set->insert(guiaction_action_pair(id, it->second));}}

        bool form_admin::isaction(guiaction id, nodetype val) {
            guiaction_action_map* tmp = getactionregistry(val);
            if (!tmp) return false;
            return (tmp->find(id) != tmp->end());}

        void form_admin::loadserver(adminintf_ptr intf) {
            if (rootitem) {
                DEBUG_STR_DVNCI("loadserver 1 start");
                uiwidgetitem *item = new uiwidgetitem(rootitem, intfcnt++, NT_ROOT_NODEF);
                loadserver(item, intf);}}

        void form_admin::loadserver(uiwidgetitem* item, adminintf_ptr intf) {
            if (rootitem) {
                registry_filter_ptr ptr_filter(new registry_filter_map());
                filter_vect.push_back(ptr_filter);
                item->registryfilter(ptr_filter.get());
                intf_vect.push_back(intf);
                item->intf(intf);
                curitem_ = item;
                item->isloaded(false);
                loaditem(item);}
            if (!intf)
                addloglist(intf->errors(), ACTION_MAPPROJECT);}

        void form_admin::clearlogscreen() {
            widget.btnclearlog->setEnabled(false);
            widget.ErrorWidget->clear();
            logscreenclose();}

        void form_admin::readserverfromconfigurator() {
           /* serverinfo_vector serverstmp;
            configurator.servers(serverstmp);
            for (serverinfo_vector::iterator it = serverstmp.begin(); it != serverstmp.end(); ++it) {
                addserver(*it);}*/}

        indx_widgit_map* form_admin::curitems() const {
            curitems_.clear();
            for (int i = 0; i < curtreewidget()->selectedItems().count(); i++) {
                curitems_.insert(indx_widgit_pair(((uiwidgetitem*) curtreewidget()->selectedItems().at(i))->key(),
                        ((uiwidgetitem*) curtreewidget()->selectedItems().at(i))));}
            return &curitems_;};

        entity_map* form_admin::nodesmap() const{
            nodemap_.clear();
            for (int i = 0; i < curtreewidget()->selectedItems().count(); i++) {
                nodemap_.insert(((uiwidgetitem*) curtreewidget()->selectedItems().at(i))->infonode());}
            return &nodemap_;}

        indx_set* form_admin::nodesset()  const {
            nodesmap();
            nodeset_.clear();
            for (entity_map::iterator it = nodemap_.begin(); it != nodemap_.end(); ++it) {
                nodeset_.insert(it->first);}
            return &nodeset_;}

        void form_admin::select_and_loaditem(uiwidgetitem* item ) {
                if (item) curitem_ = item;
                curitem_->treeWidget()->setCurrentItem(curitem_);
                proc_treeclick(curitem_, 0);}

        void form_admin::registmediator(nodetype tp, abstractmediator* medr) {
			viewmediator_ptr ptr(medr);
            mediators.insert(mediator_pair((0xFFFF & tp), ptr));}

        void form_admin::registmediator(nodetype* tp, size_t cnt, abstractmediator* medr) {
            viewmediator_ptr ptr(medr);
			for (size_t i = 0; i < cnt; i++) {
                mediators.insert(mediator_pair((0xFFFF & *tp), ptr));
                tp++;}}

        void form_admin::mediator(abstractmediator* medr) {

            if (!medr) return;
            if (currentmediator)
                currentmediator->uninit();
            medr->init();
            currentmediator = medr;}

        void form_admin::mediator(nodetype tp) {
            mediator_map::iterator it = mediators.find(0xFFFF & tp);
            if (it != mediators.end()) mediator(it->second.get());}

        void form_admin::registicon(int tp, QIcon& icn) {
            icons->insert(icon_pair(nodeinfotype((0xFFFF & tp), 0), icn));}

        void form_admin::registicon(int* tp, size_t cnt, QIcon& icn) {
            for (size_t i = 0; i < cnt; i++) {
                registicon(*tp, icn);}}

        QIcon form_admin::getIcon(int tp) {
            icon_map::iterator it = icons->find(nodeinfotype((onum)tp,0));

            if (it != icons->end()) {
                return  it->second ;}
            return (*nillIcon);}

        void form_admin::createmenue() {

            widget.btnmerge->setToolTip(qtstr_translate(QString::fromStdString("maintool.merge")));

            addserver_action = new QAction(getIcon(ACTION_ADDSERVER), qtstr_translate(QString::fromStdString("maintree.addserver")), mainTreeMenue);
            addserver_action->connect(addserver_action, SIGNAL(triggered()), this, SLOT(proc_addserver()));
            mainTreeMenue->addAction(addserver_action);
            treeMenuList->append(addserver_action);
            connect(widget.btnaddserver, SIGNAL(clicked()),  this, SLOT(proc_addserver()));
            widget.btnaddserver->setToolTip(qtstr_translate(QString::fromStdString("maintree.addserver")));

            actionmaps.insert(guiaction_action_pair(ACTION_ADDSERVER, addserver_action));

            removeserver_action = new QAction(getIcon(ACTION_REMOVESERVER), qtstr_translate(QString::fromStdString("maintree.removeserver")), mainTreeMenue);
            removeserver_action->connect(removeserver_action, SIGNAL(triggered()), this, SLOT(proc_removeserver()));
            mainTreeMenue->addAction(removeserver_action);
            treeMenuList->append(removeserver_action);
            connect(widget.btnremoveserver, SIGNAL(clicked()),  this, SLOT(proc_removeserver()));
            widget.btnremoveserver->setToolTip(qtstr_translate(QString::fromStdString("maintree.removeserver")));

            actionmaps.insert(guiaction_action_pair(ACTION_REMOVESERVER, removeserver_action));


            connect_action = new QAction(getIcon(ACTION_CONNECTSERVER), qtstr_translate(QString::fromStdString("maintree.connectserver")), mainTreeMenue);
            connect_action->connect(connect_action, SIGNAL(triggered()), this, SLOT(proc_connectserver()));
            mainTreeMenue->addAction(connect_action);
            treeMenuList->append(connect_action);
            connect(widget.btnconnectserver, SIGNAL(clicked()),  this, SLOT(proc_connectserver()));
            widget.btnconnectserver->setToolTip(qtstr_translate(QString::fromStdString("maintree.connectserver")));

            actionmaps.insert(guiaction_action_pair(ACTION_CONNECTSERVER, connect_action));


            disconnect_action = new QAction(getIcon(ACTION_DISCONNECTSERVER), qtstr_translate(QString::fromStdString("maintree.disconnectserver")), mainTreeMenue);
            disconnect_action->connect(disconnect_action, SIGNAL(triggered()), this, SLOT(proc_disconnectserver()));
            mainTreeMenue->addAction(disconnect_action);
            treeMenuList->append(disconnect_action);
            connect(widget.btndisconnectserver, SIGNAL(clicked()),  this, SLOT(proc_disconnectserver()));
            widget.btndisconnectserver->setToolTip(qtstr_translate(QString::fromStdString("maintree.disconnectserver")));

            actionmaps.insert(guiaction_action_pair(ACTION_DISCONNECTSERVER, disconnect_action));

            unmapprj_action = new QAction(getIcon(ACTION_UNMAAPPROJECT), qtstr_translate(QString::fromStdString("maintree.unmapprj")), mainTreeMenue);
            unmapprj_action->connect(unmapprj_action, SIGNAL(triggered()), this, SLOT(proc_unmapprj()));
            mainTreeMenue->addAction(unmapprj_action);
            treeMenuList->append(unmapprj_action);
            connect(widget.btnunmapproject, SIGNAL(clicked()),  this, SLOT(proc_unmapprj()));
            widget.btnunmapproject->setToolTip(qtstr_translate(QString::fromStdString("maintree.unmapprj")));

            actionmaps.insert(guiaction_action_pair(ACTION_UNMAAPPROJECT, unmapprj_action));

            mapprj_action = new QAction(getIcon(ACTION_MAPPROJECT), qtstr_translate(QString::fromStdString("maintree.mapprj")), mainTreeMenue);
            mapprj_action->connect(mapprj_action, SIGNAL(triggered()), this, SLOT(proc_mapprj()));
            mainTreeMenue->addAction(mapprj_action);
            treeMenuList->append(mapprj_action);
            connect(widget.btnmapproject, SIGNAL(clicked()),  this, SLOT(proc_mapprj()));
            widget.btnmapproject->setToolTip(qtstr_translate(QString::fromStdString("maintree.mapprj")));

            actionmaps.insert(guiaction_action_pair(ACTION_MAPPROJECT, mapprj_action));

            newprj_action = new QAction(getIcon(ACTION_NEWPROJECT), qtstr_translate(QString::fromStdString("maintree.newprj")), mainTreeMenue);
            newprj_action->connect(newprj_action, SIGNAL(triggered()), this, SLOT(proc_newprj()));
            mainTreeMenue->addAction(newprj_action);
            treeMenuList->append(newprj_action);
            connect(widget.btnnewproject, SIGNAL(clicked()),  this, SLOT(proc_newprj()));
            widget.btnnewproject->setToolTip(qtstr_translate(QString::fromStdString("maintree.newprj")));

            actionmaps.insert(guiaction_action_pair(ACTION_NEWPROJECT, newprj_action));

            import_action = new QAction(getIcon(ACTION_IMPORT), qtstr_translate(QString::fromStdString("maintree.import")), mainTreeMenue);
            import_action->connect(import_action, SIGNAL(triggered()), this, SLOT(proc_import()));
            mainTreeMenue->addAction(import_action);
            treeMenuList->append(import_action);

            actionmaps.insert(guiaction_action_pair(ACTION_IMPORT, import_action));
            connect(widget.btnimport, SIGNAL(clicked()),  this, SLOT(proc_import()));
            connect(widget.btnimport1, SIGNAL(clicked()),  this, SLOT(proc_import()));
            connect(widget.btnimport2, SIGNAL(clicked()),  this, SLOT(proc_import()));
            widget.btnimport->setToolTip(qtstr_translate(QString::fromStdString("maintree.import")));
            widget.btnimport1->setToolTip(qtstr_translate(QString::fromStdString("maintree.import")));
            widget.btnimport2->setToolTip(qtstr_translate(QString::fromStdString("maintree.import")));


            duplicate_action = new QAction(getIcon(ACTION_DUPLICATEITEM), qtstr_translate(QString::fromStdString("maintree.duplicate")), mainTreeMenue);
            ;
            import_action->connect(duplicate_action, SIGNAL(triggered()), this, SLOT(proc_duplicate()));
            mainTreeMenue->addAction(duplicate_action);
            treeMenuList->append(duplicate_action);

            actionmaps.insert(guiaction_action_pair(ACTION_DUPLICATEITEM, duplicate_action));
            connect(widget.btnclone, SIGNAL(clicked()),  this, SLOT(proc_duplicate()));
            connect(widget.btnclone1, SIGNAL(clicked()),  this, SLOT(proc_duplicate()));
            widget.btnclone->setToolTip(qtstr_translate(QString::fromStdString("maintree.duplicate")));
            widget.btnclone1->setToolTip(qtstr_translate(QString::fromStdString("maintree.duplicate")));

            export_action = new QAction(getIcon(ACTION_EXPORT), qtstr_translate(QString::fromStdString("maintree.export")), mainTreeMenue);
            export_action->connect(export_action, SIGNAL(triggered()), this, SLOT(proc_export()));
            mainTreeMenue->addAction(export_action);
            treeMenuList->append(export_action);
            connect(widget.btnexport, SIGNAL(clicked()),  this, SLOT(proc_export()));
            connect(widget.btnexport1, SIGNAL(clicked()),  this, SLOT(proc_export()));
            connect(widget.btnexport2, SIGNAL(clicked()),  this, SLOT(proc_export()));
            widget.btnexport->setToolTip(qtstr_translate(QString::fromStdString("maintree.export")));
            widget.btnexport1->setToolTip(qtstr_translate(QString::fromStdString("maintree.export")));
            widget.btnexport2->setToolTip(qtstr_translate(QString::fromStdString("maintree.export")));

            actionmaps.insert(guiaction_action_pair(ACTION_EXPORT, export_action));


            createentity_action = new QAction(getIcon(ACTION_CREATEITEM), qtstr_translate(QString::fromStdString("maintree.additem")), mainTreeMenue);
            createentity_action->connect(createentity_action, SIGNAL(triggered()), this, SLOT(proc_createentety()));
            mainTreeMenue->addAction(createentity_action);
            treeMenuList->append(createentity_action);
            widget.btnadditem->setToolTip(qtstr_translate(QString::fromStdString("maintree.additem")));
            widget.btnadditem1->setToolTip(qtstr_translate(QString::fromStdString("maintree.additem")));
            widget.btnadditem2->setToolTip(qtstr_translate(QString::fromStdString("maintree.additem")));

            connect(widget.btnadditem, SIGNAL(clicked()),  this, SLOT(proc_createentety()));
            connect(widget.btnadditem1, SIGNAL(clicked()),  this, SLOT(proc_createentety()));
            connect(widget.btnadditem2, SIGNAL(clicked()),  this, SLOT(proc_createentety()));

            actionmaps.insert(guiaction_action_pair(ACTION_CREATEITEM, createentity_action));

            eraseentity_action = new QAction(getIcon(ACTION_DELETEITEM), qtstr_translate(QString::fromStdString("maintree.deleteitem")), mainTreeMenue);
            eraseentity_action->connect(eraseentity_action, SIGNAL(triggered()), this, SLOT(proc_eraseentety()));
            mainTreeMenue->addAction(eraseentity_action);
            treeMenuList->append(eraseentity_action);

            widget.btndeleteitem->setToolTip(qtstr_translate(QString::fromStdString("maintree.deleteitem")));
            widget.btndeleteitem1->setToolTip(qtstr_translate(QString::fromStdString("maintree.deleteitem")));
            widget.btndeleteitem2->setToolTip(qtstr_translate(QString::fromStdString("maintree.deleteitem")));

            connect(widget.btndeleteitem, SIGNAL(clicked()),  this, SLOT(proc_eraseentety()));
            connect(widget.btndeleteitem1, SIGNAL(clicked()),  this, SLOT(proc_eraseentety()));
            connect(widget.btndeleteitem2, SIGNAL(clicked()),  this, SLOT(proc_eraseentety()));

            actionmaps.insert(guiaction_action_pair(ACTION_DELETEITEM, eraseentity_action));


            changegroup_menu = new QMenu(qtstr_translate(QString::fromStdString("maintree.changegroup")), mainTreeMenue);
            connect( changegroup_menu , SIGNAL(triggered (QAction* )), this, SLOT(proc_changegroup(QAction* )));
            mainTreeMenue->addMenu(changegroup_menu);
            actionmaps.insert(guiaction_action_pair(ACTION_CHANGEGROUP, changegroup_menu));
            changeagroup_menu = new QMenu(qtstr_translate(QString::fromStdString("maintree.changeagroup")), mainTreeMenue);


            mainTreeMenue->addMenu(changeagroup_menu);
            connect( changeagroup_menu , SIGNAL(triggered (QAction* )), this, SLOT(proc_changeagroup(QAction* )));
            changegroup_menu->setVisible(false);
            changeagroup_menu->setVisible(false);
            actionmaps.insert(guiaction_action_pair(ACTION_CHANGEALARMGROUP, changeagroup_menu));


            setfilter_action = new QAction(getIcon(ACTION_SETFILTERED), qtstr_translate(QString::fromStdString("maintree.setfitered")), mainTreeMenue);
            setfilter_action->connect(setfilter_action, SIGNAL(triggered()), this, SLOT(proc_setfilter()));
            mainTreeMenue->addAction(setfilter_action);
            treeMenuList->append(setfilter_action);


            startservice_action = new QAction(getIcon(ACTION_SET_STARTSERVICE), qtstr_translate(QString::fromStdString("maintree.startservice")), mainTreeMenue);
            startservice_action->connect(startservice_action, SIGNAL(triggered()), this, SLOT(proc_startservice()));
            widget.btnstartservice->setToolTip(qtstr_translate(QString::fromStdString("maintree.startservice")));
            widget.btnstartservice1->setToolTip(qtstr_translate(QString::fromStdString("maintree.startservice")));
            mainTreeMenue->addAction(startservice_action);
            treeMenuList->append(startservice_action);

            actionmaps.insert(guiaction_action_pair(ACTION_SET_STARTSERVICE, startservice_action));


            stopservice_action = new QAction(getIcon(ACTION_SET_STOPSERVICE), qtstr_translate(QString::fromStdString("maintree.stopservice")), mainTreeMenue);
            stopservice_action->connect(stopservice_action, SIGNAL(triggered()), this, SLOT(proc_stopservice()));
            widget.btnstopservice->setToolTip(qtstr_translate(QString::fromStdString("maintree.stopservice")));
            widget.btnstopservice1->setToolTip(qtstr_translate(QString::fromStdString("maintree.stopservice")));
            mainTreeMenue->addAction(stopservice_action);
            treeMenuList->append(stopservice_action);

            actionmaps.insert(guiaction_action_pair(ACTION_SET_STOPSERVICE, stopservice_action));



            actionmaps.insert(guiaction_action_pair(ACTION_SETFILTERED, setfilter_action));

            connect(widget.btnsetfilter, SIGNAL(clicked()),  this, SLOT(proc_setfilter()));
            connect(widget.btnsetfilter1, SIGNAL(clicked()),  this, SLOT(proc_setfilter()));
            connect(widget.btnsetfilter2, SIGNAL(clicked()),  this, SLOT(proc_setfilter()));
            connect(widget.btnsetfilterview, SIGNAL(clicked()),  this, SLOT(proc_setfilter()));
            widget.btnsetfilter->setToolTip(qtstr_translate(QString::fromStdString("maintree.setfitered")));
            widget.btnsetfilter1->setToolTip(qtstr_translate(QString::fromStdString("maintree.setfitered")));
            widget.btnsetfilter2->setToolTip(qtstr_translate(QString::fromStdString("maintree.setfitered")));
            widget.btnsetfilterview->setToolTip(qtstr_translate(QString::fromStdString("maintree.setfitered")));



            connect(widget.btnresetfilter, SIGNAL(clicked()),  this, SLOT(proc_resetfilter()));
            connect(widget.btnresetfilter1, SIGNAL(clicked()),  this, SLOT(proc_resetfilter()));
            connect(widget.btnresetfilter2, SIGNAL(clicked()),  this, SLOT(proc_resetfilter()));

            widget.btnresetfilter->setToolTip(qtstr_translate(QString::fromStdString("maintree.resetfitered")));
            widget.btnresetfilter1->setToolTip(qtstr_translate(QString::fromStdString("maintree.resetfitered")));
            widget.btnresetfilter2->setToolTip(qtstr_translate(QString::fromStdString("maintree.resetfitered")));



            widget.btninccnt->setToolTip(qtstr_translate(QString::fromStdString("viewtable.inccnt")));
            widget.btndeccnt->setToolTip(qtstr_translate(QString::fromStdString("viewtable.deccnt")));
            widget.btnsetallvalid->setToolTip(qtstr_translate(QString::fromStdString("viewtable.allvalid")));
            widget.btnsetallinvalid->setToolTip(qtstr_translate(QString::fromStdString("viewtable.allinvalid")));
            widget.btnkvit->setToolTip(qtstr_translate(QString::fromStdString("viewtable.kvit")));
            widget.btngroupkvit->setToolTip(qtstr_translate(QString::fromStdString("viewtable.group_kvit")));
            widget.btnagroupkvit->setToolTip(qtstr_translate(QString::fromStdString("viewtable.agroup_kvit")));
            widget.btngroupkvit->setVisible(false);
            widget.btnagroupkvit->setVisible(false);


            connect(widget.btnstartservice, SIGNAL(clicked()),  this, SLOT(proc_startservice()));
            widget.btnstartservice->setToolTip(qtstr_translate(QString::fromStdString("maintree.startservice")));
            connect(widget.btnstartservice1, SIGNAL(clicked()),  this, SLOT(proc_startservice()));
            widget.btnstartservice1->setToolTip(qtstr_translate(QString::fromStdString("maintree.startservice")));
            connect(widget.btnstopservice, SIGNAL(clicked()),  this, SLOT(proc_stopservice()));
            widget.btnstopservice->setToolTip(qtstr_translate(QString::fromStdString("maintree.stopservice")));
            connect(widget.btnstopservice1, SIGNAL(clicked()),  this, SLOT(proc_stopservice()));
            widget.btnstopservice1->setToolTip(qtstr_translate(QString::fromStdString("maintree.stopservice")));

            registrate_action(ACTION_ADDSERVER, NT_ROOT);

            registrate_action(ACTION_REMOVESERVER, NT_ROOT_SERVERS_NOTAVAIL_R);
            registrate_action(ACTION_REMOVESERVER, NT_ROOT_SERVERS_AVAIL_R);

            registrate_action(ACTION_CONNECTSERVER, NT_ROOT_SERVERS_NOTAVAIL_R);
            registrate_action(ACTION_MAPPROJECT, NT_ROOT_SERVERS_NOTAVAIL);
            registrate_action(ACTION_NEWPROJECT, NT_ROOT_SERVERS_NOTAVAIL);

            registrate_action(ACTION_DISCONNECTSERVER, NT_ROOT_SERVERS_AVAIL_R);
            registrate_action(ACTION_UNMAAPPROJECT, NT_ROOT_SERVERS_AVAIL);

            registrate_action(ACTION_IMPORT, NT_ROOT_SERVERS_AVAIL_R);
            registrate_action(ACTION_IMPORT, NT_ROOT_SERVERS_AVAIL);
            registrate_action(ACTION_IMPORT, NT_ROOT_GROUPS);
            registrate_action(ACTION_IMPORT, NT_GROUP);

            registrate_action(ACTION_EXPORT, NT_ROOT_SERVERS_AVAIL_R);
            registrate_action(ACTION_EXPORT, NT_ROOT_SERVERS_AVAIL);
            registrate_action(ACTION_EXPORT, NT_ROOT_GROUPS);
            registrate_action(ACTION_EXPORT, NT_GROUP);


            registrate_action(ACTION_CREATEITEM, NT_GROUP);
            registrate_action(ACTION_CREATEITEM, NT_ROOT_GROUPS);
            registrate_action(ACTION_CREATEITEM, NT_ROOT_AGROUPS);
            registrate_action(ACTION_CREATEITEM, NT_AGROUP);
            registrate_action(ACTION_CREATEITEM, NT_MF_REPLIST);
            registrate_action(ACTION_CREATEITEM, NT_MF_TRENDLIST);
            registrate_action(ACTION_CREATEITEM, NT_MF_MESSLIST);
            registrate_action(ACTION_CREATEITEM, NT_MF_REPHEADER);
            registrate_action(ACTION_CREATEITEM, NT_MF_TRENDHEADER);
            registrate_action(ACTION_CREATEITEM, NT_MF_MESSHEADER);
            registrate_action(ACTION_CREATEITEM, NT_MF_REPARR);
            registrate_action(ACTION_CREATEITEM, NT_MF_TRENDARR);
            registrate_action(ACTION_CREATEITEM, NT_MF_MESSARR);
            registrate_action(ACTION_CREATEITEM, NT_ROOT_USERS);
            registrate_action(ACTION_CREATEITEM, NT_ROOT_ACCESSRULES);
            registrate_action(ACTION_DUPLICATEITEM, NT_GROUP);


            registrate_action(ACTION_DELETEITEM, NT_TAG);
            registrate_action(ACTION_DELETEITEM, NT_GROUP);
            registrate_action(ACTION_DELETEITEM, NT_AGROUP);
            registrate_action(ACTION_DELETEITEM, NT_USER);
            registrate_action(ACTION_DELETEITEM, NT_ROOT_ACCESSRULES);
            registrate_action(ACTION_DELETEITEM, NT_MF_REPLIST);
            registrate_action(ACTION_DELETEITEM, NT_MF_TRENDLIST);
            registrate_action(ACTION_DELETEITEM, NT_MF_MESSLIST);
            registrate_action(ACTION_DELETEITEM, NT_MF_REPHEADER);
            registrate_action(ACTION_DELETEITEM, NT_MF_TRENDHEADER);
            registrate_action(ACTION_DELETEITEM, NT_MF_MESSHEADER);
            registrate_action(ACTION_DELETEITEM, NT_MF_REPARR);
            registrate_action(ACTION_DELETEITEM, NT_MF_TRENDARR);
            registrate_action(ACTION_DELETEITEM, NT_MF_MESSARR);

            registrate_action(ACTION_CHANGEGROUP, NT_TAG);
            registrate_action(ACTION_CHANGEALARMGROUP, NT_TAG);

            registrate_action(ACTION_CHANGEALARMGROUP, NT_ATAG);


            registrate_action(ACTION_SETFILTERED, NT_ROOT_GROUPS);
            registrate_action(ACTION_SETFILTERED, NT_GROUP);
            registrate_action(ACTION_SETFILTERED, NT_ROOT_AGROUPS);
            registrate_action(ACTION_SETFILTERED, NT_AGROUP);
            registrate_action(ACTION_SETFILTERED, NT_ROOT_USERS);
            registrate_action(ACTION_SETFILTERED, NT_UTIL_FINDER);
            registrate_action(ACTION_SETFILTERED, NT_UTIL_MAINTABLE);
            registrate_action(ACTION_SETFILTERED, NT_UTIL_GROUPTABLE);
            registrate_action(ACTION_SET_STARTSERVICE, NT_SERVICE);
            registrate_action(ACTION_SET_STOPSERVICE, NT_SERVICE);}

        void form_admin::loaditem(uiwidgetitem* item) {
            if (item) curitem_ = item;
            inserttransaction(ACTION_SHORTITEMINFO);}

        void form_admin::proc_treeclick(QTreeWidgetItem* item, int val) {

            uiwidgetitem* item_ = (uiwidgetitem*) item;

            curtreewidget_ = item->treeWidget();

            for (int i = 0; i < item->treeWidget()->selectedItems().count(); i++)
                if (((uiwidgetitem*) item->treeWidget()->selectedItems().at(0))->nodetp() != item_->nodetp())
                    item->treeWidget()->selectedItems().at(0)->setSelected(false);
            curitem_ = item_;
            mediator(item_->nodetp());
            settoolbars();}

       void form_admin::proc_mergeclick() {
                inserttransaction(ACTION_SETFULLITEMINFO);};

        void form_admin::proc_changeviewkindclick() {
            if (curitem()) {
                curitem()->viewtype((curitem()->viewtype() == uiwidgetitem::tvcascade) ?
                        uiwidgetitem::tvline :  uiwidgetitem::tvcascade);
                uiwidgetitem* rootinfitem = curitem()->intfroot();
                resetnavigator();
                if (rootinfitem) loaditem(rootinfitem);
                settoolbars();}};

        void form_admin::invisibletreemenue() {

            for (QList<QAction*>::iterator it = treeMenuList->begin(); it != treeMenuList->end(); ++it) {
                (*it)->setVisible(false);}
            changegroup_menu->menuAction()->setVisible(false);
            changeagroup_menu->menuAction()->setVisible(false);}

        void form_admin::proc_treecontext ( const QPoint& val) {
            invisibletreemenue();
            QPoint val_ = curtreewidget()->mapToGlobal(val);
            val_.setX(val_.x() + 25);
            val_.setY(val_.y() + 5);
            uiwidgetitem* itemtmp = (uiwidgetitem*) curtreewidget()->itemAt(val);
            adminintf_ptr tmpintf;
            if (itemtmp->intf()) {
                tmpintf = itemtmp->intf();}

            curitem_ = itemtmp;
            if (itemtmp) {

                guiaction_action_map* tmp_set = getactionregistry(itemtmp->nodetp());
                if (tmp_set) {
                    guiaction_action_map::iterator it = tmp_set->begin();
                    while (it != tmp_set->end()) {

                        if (tmpintf) {

                            if (it->first == ACTION_CHANGEGROUP) {
                                changegroup_menu->clear();
                                iteminfo_map::const_iterator it1 = tmpintf->groupsmap().begin();
                                while (it1 != tmpintf->groupsmap().end()) {

                                    QAction* tmpchangegroup_menu = new QAction(qtstr_translate(QString::fromStdString(it1->second.name().c_str())), changegroup_menu);
                                    tmpchangegroup_menu->setIcon(uiwidgetitem::icon(nodeinfotype(NT_GROUP,0)));
                                    tmpchangegroup_menu->setData(static_cast<int>(it1->first));
                                    changegroup_menu->addAction(tmpchangegroup_menu);
                                    tmpchangegroup_menu->setVisible(true);
                                    ++it1;}

                                changegroup_menu->menuAction()->setVisible(true);}

                            if (it->first == ACTION_CHANGEALARMGROUP) {
                                changeagroup_menu->clear();
                                iteminfo_map::const_iterator it1 = tmpintf->agroupsmap().begin();
                                while (it1 != tmpintf->agroupsmap().end()) {

                                    QAction* tmpchangeagroup_menu = new QAction(qtstr_translate(QString::fromStdString(it1->second.name().c_str())), changeagroup_menu);
                                    tmpchangeagroup_menu->setIcon(uiwidgetitem::icon(nodeinfotype(NT_AGROUP,0)));
                                    changeagroup_menu->addAction(tmpchangeagroup_menu);
                                    tmpchangeagroup_menu->setData(static_cast<int>(it1->first));
                                    tmpchangeagroup_menu->setVisible(true);
                                    ++it1;}
                                changeagroup_menu->menuAction()->setVisible(true);}}

                        if ((it->first != ACTION_CHANGEGROUP) && (it->first != ACTION_CHANGEALARMGROUP))
                            (dynamic_cast<QAction*> (it->second))->setVisible(true);
                        ++it;}

                    mainTreeMenue->exec(val_);}}}

        void form_admin::proc_unmapprj() {
                inserttransaction(ACTION_UNMAAPPROJECT);}

        void form_admin::proc_addserver() {
            std::string tmp = "";
            if (addserverForm.execs(tmp)) {
                if (configurator.addserver(tmp))
                    addserver(tmp);}}

        void form_admin::proc_eraseentety() {
                inserttransaction(ACTION_DELETEITEM);}

        void form_admin::proc_removeserver() {
            if (curitem()) {
                if (curitem()->nodetp() == NT_ROOT_SERVERS_AVAIL_R) {
                    curitem()->intf()->disconnect();}
				configurator.removeserver(dvnci::trim_copy(curitem()->intf()->named()));
                curitem()->clear_child();
                uiwidgetitem* parent_ = (uiwidgetitem*) curitem()->parent();
                delete curitem();
                curitem_ = parent_;
                select_and_loaditem();}}


        void form_admin::proc_disconnectserver()  {
                inserttransaction(ACTION_DISCONNECTSERVER);}

        void form_admin::proc_connectserver() {
            std::string tmp = curitem()->intf()->fullnamed();
            ;
            if (addserverForm.execs(tmp)) {
                if (tmp != curitem()->intf()->fullnamed()) {
                    configurator.changeserver(curitem()->intf()->fullnamed(), tmp);
                    curitem()->intf()->fullnamed(tmp);}
                inserttransaction(ACTION_CONNECTSERVER, tmp);}}

        void form_admin::proc_setfilter() {
            if (curitem()) {
                string tmpcriteria = this->curitem()->strciteria();
                switch (curitem()->nodetp()) {
                    case NT_UTIL_FINDER:{
                        nodetype tmpnt = curitem()->filtertype();
                        if (treeFilterForm.execs(tmpcriteria, tmpnt, curitem()->intf()->groupsmap())) {
                            curitem()->strciteria(tmpcriteria);
                            curitem()->isloaded(false);
                            curitem()->filtertype(tmpnt);
                            inserttransaction(ACTION_SETFILTERED);}
                        break;}

                    case NT_UTIL_MAINTABLE:{
                        bool tmp_needstop = (currenttransaction() == ACTION_VIEWTAG);
                        if (tmp_needstop) currenttransaction(0);
                        if (treeFilterForm.execs(curitem()->nodetp(), tmpcriteria, curitem()->intf()->groupsmap()))
                            curitem()->strciteria(tmpcriteria);
                        if ((tmp_needstop) && (mediator())) {
                            mediator()->uninit();
                            mediator()->init();}
                        break;}

                    case NT_UTIL_GROUPTABLE:{
                        bool tmp_needstop = (currenttransaction() == ACTION_VIEWGROUP);
                        if (tmp_needstop) currenttransaction(0);
                        if (treeFilterForm.execs(curitem()->nodetp(), tmpcriteria, curitem()->intf()->groupsmap()))
                            curitem()->strciteria(tmpcriteria);
                        if ((tmp_needstop) && (mediator())) {
                            mediator()->uninit();
                            mediator()->init();}
                        break;}

                    default:{
                        if (treeFilterForm.execs(curitem()->nodetp(), tmpcriteria, curitem()->intf()->groupsmap())) {
                            curitem()->strciteria(tmpcriteria);
                            curitem()->isloaded(false);
                            inserttransaction(ACTION_SHORTITEMINFO);}}}}}

        void form_admin::proc_resetfilter() {
            if (curitem()) {
                string tmpcriteria = "";
                curitem()->strciteria(tmpcriteria);
                curitem()->isloaded(false);
                if ((curitem()->nodetp() == NT_UTIL_FINDER)) {
                    inserttransaction(ACTION_SETFILTERED);
                    return;};
                if (curitem()->nodetp() == NT_UTIL_MAINTABLE) {
                    bool tmp_needstop = (currenttransaction() == ACTION_VIEWTAG);
                    if (tmp_needstop) currenttransaction(0);
                    if ((tmp_needstop) && (mediator())) {
                        mediator()->uninit();
                        mediator()->init();}
                    return;}
                if (curitem()->nodetp() == NT_UTIL_GROUPTABLE) {
                    bool tmp_needstop = (currenttransaction() == ACTION_VIEWGROUP);
                    if (tmp_needstop) currenttransaction(0);
                    if ((tmp_needstop) && (mediator())) {
                        mediator()->uninit();
                        mediator()->init();}
                    return;}
                inserttransaction(ACTION_SHORTITEMINFO);}}

        void form_admin::proc_newprj() {
            fileDialog.setOptions(QFileDialog::ShowDirsOnly);
            fileDialog.setFileMode(QFileDialog::DirectoryOnly);
            fileDialog.setViewMode(QFileDialog::List);
            if (fileDialog.exec() == QDialog::Accepted) {
                QString tmp_dir = fileDialog.directory().absolutePath() + "/";
                inserttransaction(ACTION_NEWPROJECT, str_from_qtstr_loc(tmp_dir));};}

        void form_admin::proc_mapprj() {

            fileDialog.setOptions(QFileDialog::ShowDirsOnly);
            fileDialog.setFileMode(QFileDialog::DirectoryOnly);
            fileDialog.setViewMode(QFileDialog::List);
            if (fileDialog.exec() == QDialog::Accepted) {
                QString tmp_dir = fileDialog.directory().absolutePath() + "/";
                inserttransaction(ACTION_MAPPROJECT, str_from_qtstr_loc(tmp_dir));};}

        void form_admin::proc_createentety() {
            string str_tmp = "";
            if (addItemForm.execs(str_tmp, std::string("mainwindow.addobject"),
                    std::string("mainwindow.namenewobject") +
                    namebynodetp(nodetp_child_by_parent(curitem()->nodetp())),
                    (nodetp_is_meta(curitem()->nodetp()) || (curitem()->nodetp() == NT_ROOT_USERS) ||
                     (curitem()->nodetp() == NT_ROOT_ACCESSRULES))))
                inserttransaction(ACTION_CREATEITEM, str_tmp);}

        void form_admin::proc_import() {
            base_data tmp;
            if (importform.execs(&tmp, curitem()->text(0).toStdString(), curitem()->nodetp())) {
                curitem()->intf()->setimportbase(tmp);
                addloglist(curitem()->intf()->errors(), ACTION_IMPORT);
                curitem()->clear_child();
                curitem()->isloaded(false);
                loaditem();}}

        void form_admin::proc_export() {
            if (!curitem()) return;
            QString dFilter;
            if ((curitem()->nodetp() == NT_ROOT_GROUPS) ||  (curitem()->nodetp() == NT_GROUP))
                dFilter = "*.xml *.csv";
            else dFilter = "*.xml";

            QString tmp_dir = QFileDialog::getSaveFileName(0, "Export", "", dFilter);
            if (tmp_dir != "") {
                base_data base;
                if (curitem()->intf()->getexportbase(base, curitem()->nodetp(),
                        "" , curitem()->key())) {
                    if (gettipeimport(tmp_dir.toStdString()) == TIPE_NS_IMPORT_CSV)
                        form_import::changelocal(&base, 0 , 1);
                    setexportdata(tmp_dir.toStdString(), base);}}}

        void form_admin::proc_changegroup(QAction* action) {
            bool tmp_bool = true;
            if ((action) && (!action->data().isNull())) {
                transact_key2 = action->data().toInt(&tmp_bool);
                if (tmp_bool)
                    inserttransaction(ACTION_CHANGEGROUP);}}

        void form_admin::proc_changeagroup(QAction* action) {
            bool tmp_bool = true;
            if ((action) && (!action->data().isNull())) {
                transact_key2 = action->data().toInt(&tmp_bool);
                if (tmp_bool)
                    inserttransaction(ACTION_CHANGEALARMGROUP);}}

        void form_admin::proc_duplicate() {
            string str_tmp = "";
            if (addItemForm.execs(str_tmp, std::string("mainwindow.addobject"),
                    std::string("mainwindow.namenewobject.group"),
                    (nodetp_is_meta(curitem()->nodetp()) || (curitem()->nodetp() == NT_ROOT_USERS) ||
                     (curitem()->nodetp() == NT_ROOT_ACCESSRULES))))
                inserttransaction(ACTION_DUPLICATEITEM, str_tmp);}

        void form_admin::proc_itchange( QTableWidgetItem* item_)  {
            if (isLoading) return;
            if (item_->column() < 1) return;
            if (item_->data(Qt::CheckStateRole).isValid())
                updateproperty(item_->type(), (item_->checkState() == Qt::Checked));
            else {
                int indx = widget.tableproperty->row(item_);
                uitabdelegate * delegate_ = 0;
                if (indx>-1)
                    delegate_ = dynamic_cast<uitabdelegate*> (widget.tableproperty->itemDelegateForRow(indx));
                if (delegate_)
                    if (delegate_->_typeeditor() != uitabdelegate::TComboBox)
                        delegate_ = 0;
                if (delegate_)
                    updateproperty(item_->type(), delegate_->getval(item_->text()));
                else
                    updateproperty(item_->type(), item_->text());};
            widget.btnmerge->setEnabled(needmerge());}

        void form_admin::proc_valuechange ( int value ) {

            basetable* model_ = dynamic_cast<basetable*> (widget.tableview->model());
            if (model_) {
                model_->toprow( value );
                model_->visrow((widget.tableview->rowHeight(0) < 1) ? 0 :
                        (widget.tableview->height() / widget.tableview->rowHeight(0) + 10));}}

        void form_admin::proc_logclick() {
                (screanopt() == lserror) ? screanopt(lsallways) : screanopt(lserror);}

        void form_admin::proc_error() {
                clearlogscreen();}

        void form_admin::proc_incallcount() {
                inserttransaction(ACTION_INCCOUNTALL);}

        void form_admin::proc_decallcount() {
                inserttransaction(ACTION_DECCOUNTALL);}

        void form_admin::proc_setallvalid() {
                inserttransaction(ACTION_SETALL_VALID);}

        void form_admin::proc_setallinvalid() {
                inserttransaction(ACTION_SETALL_INVALID);}

        void form_admin::proc_kvit() {
                inserttransaction(ACTION_KVIT);}

        void form_admin::proc_startservice() {
                inserttransaction(ACTION_SET_STARTSERVICE);}

        void form_admin::proc_stopservice() {
                inserttransaction(ACTION_SET_STOPSERVICE);};

        void form_admin::customEvent(QEvent * event) {

            guiaction tpevent = static_cast<guiaction> (event->type());
            DEBUG_VAL_DVNCI(tpevent - 1000);

            if (tpevent > 1000) {
                if (tpevent == ACTION_TRANSACTIONSTART) {
                    widget.tableproperty->setEnabled(false);
                    widget.tableview->setEnabled(false);
                    return;}

                if (tpevent == ACTION_ALLTRANSDONE) {
                    widget.tableproperty->setEnabled(true);
                    widget.tableview->setEnabled(true);
                    return;}

                btevent*  baseevent = dynamic_cast<btevent*> (event);
                vtevent*  veiwevent = dynamic_cast<vtevent*> (event);

                switch (tpevent) {
                    case ACTION_CONNECTSERVER:{
                        if (baseevent) {
                            addloglist(baseevent->curitem->intf()->errors(), tpevent);
                            if (baseevent->result) {
                                baseevent->curitem->nodetp(NT_ROOT_NODEF);
                                curitem_ = baseevent->curitem;
                                loaditem();}}
                        break;}

                    case ACTION_DISCONNECTSERVER:{
                        if (baseevent) {
                            addloglist(baseevent->curitem->intf()->errors(), tpevent);
                            if (baseevent->result) {
                                baseevent->curitem->clear_child();
                                baseevent->curitem->nodetp(NT_ROOT_NODEF);
                                curitem_ = baseevent->curitem;
                                loaditem();}}
                        break;}

                    case ACTION_MAPPROJECT:{
                        if (baseevent) {
                            addloglist(baseevent->curitem->intf()->errors(), tpevent);
                            baseevent->curitem->clear_child();
                            baseevent->curitem->nodetp(NT_ROOT_NODEF);
                            curitem_ = baseevent->curitem;
#if defined(_MSC_VER) 
                            std::wstring rslt;
                            dvnci::utf8_to_wstr(baseevent->parameter_str, rslt);
                            setlocalbasepath(rslt);                            
#else                            
                            setlocalbasepath(baseevent-> parameter_str);
#endif                            
                            addserver(baseevent->curitem);}
                        break;}

                    case ACTION_UNMAAPPROJECT:{
                        if (baseevent) {
                            addloglist(baseevent->curitem->intf()->errors(), tpevent);
                            baseevent->curitem->clear_child();
                            baseevent->curitem->nodetp(NT_ROOT_NODEF);
                            curitem_ = baseevent->curitem;
                            setlocalbasepath("");
                            addserver(baseevent->curitem);}
                        break;}

                    case ACTION_NEWPROJECT:{
                        if (baseevent) {
                            addloglist(baseevent->curitem->intf()->errors(), tpevent);
                            baseevent->curitem->clear_child();
                            baseevent->curitem->nodetp(NT_ROOT_NODEF);
#if defined(_MSC_VER) 
                            std::wstring rslt;
                            dvnci::utf8_to_wstr(baseevent->parameter_str, rslt);
                            setlocalbasepath(rslt);
                            tagsbase::writezero(fspath(rslt));
#else
                            setlocalbasepath(baseevent->parameter_str);
                            tagsbase::writezero(fspath(baseevent-> parameter_str));
#endif                            
                            addserver(baseevent->curitem);}
                        break;}

                    case ACTION_SHORTITEMINFO:{
                        if (baseevent) {
                            baseevent->curitem->loadchlids(baseevent->infomap);
                            inserttransaction(ACTION_FULLITEMINFO);}
                        break;}

                    case ACTION_SETFILTERED:{
                        if (baseevent) {
                            baseevent->curitem->loadfindedchilds(baseevent->infomap);}
                        break;}

                    case ACTION_FULLITEMINFO:{
                        if (baseevent) {
                            propertytab(baseevent->property_map);
                            widget.btnmerge->setEnabled(needmerge());}
                        break;}

                    case ACTION_SETFULLITEMINFO:{
                        if (baseevent) {
                            addloglist(baseevent->curitem->intf()->errors(), tpevent);
                            updateitemexs(baseevent->curitems, baseevent->infomap);
                            loaditem();}
                        break;}

                    case ACTION_CREATEITEM:{
                        if (baseevent) {
                            addloglist(baseevent->curitem->intf()->errors(), tpevent);
                            if (!baseevent->curitem->intf()->iserror()) {
                                ((uiwidgetitem*) baseevent->curitem)->isloaded(false);
                                loaditem((uiwidgetitem*) baseevent->curitem);}}
                        break;}

                    case ACTION_DUPLICATEITEM:{
                        if (baseevent) {
                            addloglist(baseevent->curitem->intf()->errors(), tpevent);
                            if (!baseevent->curitem->intf()->iserror()) {
				if (dynamic_cast<uiwidgetitem*>(baseevent->curitem->virtualparent())){
                                      curitem_=dynamic_cast<uiwidgetitem*>(baseevent->curitem->virtualparent());
									  ((uiwidgetitem*) baseevent->curitem)->isloaded(false);
										  loaditem();}}}
                        break;}

                    case ACTION_DELETEITEM:{

                        if (baseevent) {
                            addloglist(baseevent->curitem->intf()->errors(), tpevent);
                            curitem_ = baseevent->curitem->virtualparent() ? baseevent->curitem->virtualparent() : rootitem;
                            if (!baseevent->curitem->intf()->iserror()) {
                                removeitems(baseevent->curitems);}
                            loaditem();}
                        break;}

                    case ACTION_CHANGEGROUP:{

                        if (baseevent) {
                            addloglist(baseevent->curitem->intf()->errors(), tpevent);
                            removeitems(baseevent->curitems);
                            additem_to_parent(NT_GROUP, baseevent->parameter_index);}
                        break;}

                    case ACTION_CHANGEALARMGROUP:{

                        if (baseevent) {
                            addloglist(baseevent->curitem->intf()->errors(), tpevent);
                            if (baseevent->curitem->nodetp() == NT_ATAG) removeitems(baseevent->curitems);
                            additem_to_parent(NT_AGROUP, baseevent->parameter_index);}
                        break;}

                    case ACTION_VIEWTAG: case ACTION_VIEWGROUP: case ACTION_VIEWACCESSRULE:{
                        if (currenttransaction() != (tpevent)) return;
                        if (veiwevent) {
                            utilmediator* tmpmediator = dynamic_cast<utilmediator*> (mediator());
                            if (tmpmediator) {
                                basetable* mod = dynamic_cast<basetable*> (tmpmediator->mod);
                                if (mod) {
                                    mod->setindex(veiwevent->infomap);
                                    if (widget.tableview->model() != mod)
                                        widget.tableview->setModel(mod);
                                    viewset_ = mod->getindex();
                                    toprow_ = mod->toprow();
                                    countrow_ = mod->visrow();
                                    insertviewtransaction(tpevent);
                                    widget.tableview->viewport()->update();}}}

                        break;}



                    case ACTION_SET_STARTSERVICE:case ACTION_SET_STOPSERVICE:{
                        if (baseevent) {
                            curitem_ = baseevent->curitem->virtualparent() ? baseevent->curitem->virtualparent() : rootitem;
                            loaditem();}
                        break;}

                    case ACTION_VIEWDEBUG: case ACTION_VIEWJOURNAL:{

                        if (currenttransaction() != (tpevent)) return;

                        if (veiwevent) {
                            utilmediator* tmpmediator = dynamic_cast<utilmediator*> (mediator());
                            if (tmpmediator) {
                                livetableview * mod = dynamic_cast<livetableview *> (tmpmediator->mod);
                                if (mod) {
                                    mod->resetview();
                                    if (widget.tableview->model() != mod)
                                        widget.tableview->setModel(mod);
                                    insertviewtransaction(tpevent);
                                    widget.tableview->viewport()->update();}}}
                        break;}

                    case ACTION_VIEWCOMMANDS: case ACTION_VIEWALARMS:
                    case ACTION_VIEWREGISTRY: case ACTION_VIEWCLIENTS:{

                        if (currenttransaction() != (tpevent)) return;

                        if (veiwevent) {
                            utilmediator* tmpmediator = dynamic_cast<utilmediator*> (mediator());
                            if (tmpmediator) {
                                livetableview * mod = dynamic_cast<livetableview *> (tmpmediator->mod);
                                if (mod) {
                                    mod->resetview();
                                    if (widget.tableview->model() != mod)
                                        widget.tableview->setModel(mod);
                                    insertviewtransaction(tpevent);
                                    widget.tableview->viewport()->update();}}}
                        break;}

                    case ACTION_FAILCONNECT:{
                        DEBUG_STR_DVNCI(DISCONNECT_OR_NOCONNECT);
                        if (baseevent) {
                            showmessagebox(baseevent->curitem->intf()->errors(), tpevent);
                            if (baseevent->curitem) {
                                baseevent->curitem->clear_child();
                                baseevent->curitem->nodetp(NT_ROOT_SERVERS_NOTAVAIL_R);
                                curitem_ = baseevent->curitem;
                                select_and_loaditem();}}
                        else {
                            if (veiwevent) {
                                showmessagebox(veiwevent->curitem->intf()->errors(), tpevent);
                                if (veiwevent->curitem) {
                                    veiwevent->curitem->clear_child();
                                    veiwevent->curitem->nodetp(NT_ROOT_SERVERS_NOTAVAIL_R);
                                    curitem_ = veiwevent->curitem;
                                    select_and_loaditem();}}}
                        break;}}

                settoolbars();}
            else QMainWindow::customEvent(event);}

        void form_admin::removeitems(indx_widgit_map* items) {
            for (indx_widgit_map::iterator it = items->begin(); it != items->end(); ++it) {
                ((uiwidgetitem*) it->second)->removeex();}}

        void form_admin::updateitemexs(indx_widgit_map* items, iteminfo_map& map_) {
            for (indx_widgit_map::iterator it = items->begin(); it != items->end(); ++it) {
                uiwidgetitem* item = (uiwidgetitem*) it->second;
                if (map_.find(item->key()) != map_.end())
                    item->updateitemex(*(map_.find(item->key())));}}

        void form_admin::additem_to_parent(nodetype type, indx id) {
            indx_widgit_map map;
            curitem()->additem_to_parent(type, id, map);
            if (map.size() > 0) {
                curitem_ = (uiwidgetitem*) map.begin()->second;
                loaditem();}}

        void form_admin::addtransaction(basetransaction* transact_cl) {
            basetransaction_ptr tmp(transact_cl);
            DEBUG_STR_VAL_DVNCI(inserttransaction, (tmp.use_count()));
            infproccess->addtransaction(tmp);}

        void form_admin::addviewtransaction(viewtransaction* transact_cl) {
            viewtransaction_ptr tmp(transact_cl);
            viewproccess->addtransaction(tmp);}

        void form_admin::inserttransaction(guiaction tp, string val) {
            addtransaction(new basetransaction(tp, curitems(), curitem(), *nodesmap(), propertytab(), (curitem()) ? curitem_->nodetp() : 0, val, transact_key2));}

        void form_admin::insertviewtransaction(guiaction tp) {
            addviewtransaction(new viewtransaction(tp, curitem(), viewset_));}

        void form_admin::drawtable() {
            int i = 0;
            isLoading = true;
            try {
                widget.tableproperty->clear();
                widget.tableproperty->setRowCount(propertytab_out.size());
                propertytable_map::iterator it = propertytab_out.begin();
                while (it != propertytab_out.end()) {
                    QString qs;
                    qs = "properties." + qs.setNum(it->first);
                    qs = qtstr_translate(qs);
                    QTableWidgetItem* tab_it1 = new QTableWidgetItem(qs);
                    tab_it1->setFlags(static_cast<Qt::ItemFlags> (static_cast<int> (tab_it1->flags()) & (!static_cast<int> (Qt::ItemIsEditable))));
                    widget.tableproperty->setItem(i, 0, tab_it1);
                    Qt::ItemFlags _fl;
                    QTableWidgetItem* tab_it2;
                    switch (it->second.type) {
                        case TYPE_PE_CHECKED:{
                            tab_it2 = new QTableWidgetItem("", it->first);
                            if ((it->second.value != "0") && (it->second.value != ""))
                                tab_it2->setCheckState(Qt::Checked);
                            else
                                tab_it2->setCheckState(Qt::Unchecked);
                            widget.tableproperty->setItem(i, 1, tab_it2);
                            tab_it2->setFlags(tab_it1->flags() | (Qt::ItemIsEnabled) | Qt::ItemIsUserCheckable);
                            break;}

                        case TYPE_PE_LIST:{

                            QString tmp_str;
                            tmp_str = QString::fromStdString(it->second.name + "." + it->second.value);
                            tab_it2 = new QTableWidgetItem(qtstr_translate(tmp_str), it->first);
                            uitabdelegate* delegate = new uitabdelegate(uitabdelegate::TComboBox, widget.tableproperty);
                            num64_set::iterator it1 = it->second.set.begin();
                            while (it1 != it->second.set.end()) {
                                tmp_str = QString::fromStdString(it->second.name) + "." + QString::number(*it1);
                                delegate->fillList(qtstr_translate(tmp_str), *it1);
                                it1++;}
                            widget.tableproperty->setItem(i, 1, tab_it2);
                            widget.tableproperty->setItemDelegateForRow(i, delegate);
                            break;}

                        default:{
                            tab_it2 = new QTableWidgetItem(qtstr_from_str_loc(it->second.value, it->second.local), it->first);
                            widget.tableproperty->setItem(i, 1, tab_it2);
                            widget.tableproperty->setItemDelegateForRow(i, widget.tableproperty->itemDelegate());}}
                    if (it->second.isDiff) tab_it2->setBackgroundColor(QColor::fromRgb(10, 10, 100, 50));
                    ++it;
                    i++;}}
            catch (...) {};
            isLoading = false;}

        void form_admin::updateproperty(propedittype type, QString val) {

            propertytable_map::iterator it1 = propertytab_out.find(type);
            propertytable_map::iterator it2 = propertytab_in.find(type);
            if (it1 == propertytab_out.end()) return;
            if (it2 == propertytab_in.end()) return;
            if (it1->second.value != str_from_qtstr_loc(val, it1->second.local)) {
                it1->second.value = str_from_qtstr_loc(val, it1->second.local);
                it1->second.inChange = (it1->second.value != it2->second.value);}}

        void form_admin::updateproperty(propedittype type, bool cheched_) {

            propertytable_map::iterator it1 = propertytab_out.find(type);
            propertytable_map::iterator it2 = propertytab_in.find(type);
            if (it1 == propertytab_out.end()) return;
            if (it2 == propertytab_in.end()) return;
            std::string val;
            val = (cheched_) ? "1" : "0";
            if (it1->second.value != val) {
                it1->second.value = val;
                it1->second.inChange = (it1->second.value != it2->second.value);}}

        void form_admin::updateproperty(propedittype type, int val) {

            propertytable_map::iterator it1 = propertytab_out.find(type);
            propertytable_map::iterator it2 = propertytab_in.find(type);
            if (it1 == propertytab_out.end()) return;
            if (it2 == propertytab_in.end()) return;
            if (it1->second.value != to_str(val)) {
                it1->second.value = to_str(val);
                it1->second.inChange = (it1->second.value != it2->second.value);}}

        void form_admin::addloglist( int_dvncierror_map val, guiaction trasact_) {

            for (int_dvncierror_map::iterator it = val.begin(); it != val.end(); ++it) {
                widget.btnclearlog->setEnabled(true);
                QString tmp = QString::number(it->second.code());
                tmp = "error." + tmp;
                tmp = qtstr_translate(tmp.toStdString().c_str());
                QTime tmptm = QTime::currentTime();
                tmp = tmptm.toString("hh:mm:ss") + "  " + tmp + " : ";
                QString tmppar = QString::fromUtf8(it->second.str().c_str());
                tmp = tmp + tmppar;

                widget.ErrorWidget->insertItem(0, tmp);
                if (widget.ErrorWidget->children().count() > 0)
                    widget.ErrorWidget->item(0)->setIcon(getIcon(ACTION_ERRORITEM));}

            if ((trasact_ != 0) && (val.size() == 0) && (screanOpt_ == lsallways)) {
                QString tmp = QString::number(trasact_);
                tmp = "trasaction." + tmp;
                tmp = qtstr_translate(tmp.toStdString().c_str());
                QTime tmptm = QTime::currentTime();
                tmp = tmptm.toString("hh:mm:ss") + "  " + tmp;

                widget.ErrorWidget->insertItem(0, tmp);
                if (widget.ErrorWidget->children().count() > 0)
                    widget.ErrorWidget->item(0)->setIcon(getIcon(ACTION_OKITEM));}
            widget.ErrorWidget->setVisible((widget.btnclearlog->isEnabled()) || (screanOpt_ == lsallways));}

        void form_admin::showmessagebox( int_dvncierror_map val, guiaction trasact_) {
            int_dvncierror_map::reverse_iterator it = val.rbegin();
            if (it != val.rend()) {
                QString tmp = QString::number(it->second.code());
                tmp = "error." + tmp;
                tmp = qtstr_translate(tmp.toStdString().c_str());
                tmp = tmp + " " + + it->second.str().c_str();
                QMessageBox tmpmsgbox;
                tmpmsgbox.setIcon(QMessageBox::Critical);
                tmpmsgbox.setText(tmp);
                tmpmsgbox.exec();}
            addloglist(val, trasact_);}

        void form_admin::propertytab(propertytable_map& tabl) {

            for (propertytable_map::iterator it = tabl.begin(); it != tabl.end(); ++it) {
                it->second.inChange = false;}
            propertytab_in = tabl;
            propertytab_out = tabl;
            drawtable();}

        propertytable_map& form_admin::propertytab() const{
            return propertytab_out;}

        bool form_admin::needmerge() {
            if (propertytab_in.size() != propertytab_out.size()) return false;
            propertytable_map::iterator it1 = propertytab_in.begin();
            propertytable_map::iterator it2 = propertytab_out.begin();
            while ((it1 != propertytab_in.end()) || (it2 != propertytab_out.end())) {
                if ((it1->second) != (it2->second)) return true;
                ++it1;
                ++it2;}
            return false;}

        void form_admin::settoolbars() {
            if (curtreewidget() == widget.treeWidget) {

                widget.btnaddserver->setVisible((isaction(ACTION_ADDSERVER, curitem()->nodetp())));
                widget.btnaddserver->setEnabled((curitems()->size() == 1));

                widget.btnremoveserver->setVisible((isaction(ACTION_REMOVESERVER, curitem()->nodetp())));
                widget.btnremoveserver->setEnabled((curitems()->size() == 1) );

                widget.btnmapproject->setVisible((isaction(ACTION_MAPPROJECT, curitem()->nodetp())));
                widget.btnmapproject->setEnabled((curitems()->size() == 1));

                widget.btnunmapproject->setVisible((isaction(ACTION_UNMAAPPROJECT, curitem()->nodetp())));
                widget.btnunmapproject->setEnabled((curitems()->size() == 1));

                widget.btnnewproject->setVisible( (isaction(ACTION_NEWPROJECT, curitem()->nodetp())));
                widget.btnnewproject->setEnabled((curitems()->size() == 1));

                widget.btnconnectserver->setVisible((isaction(ACTION_CONNECTSERVER, curitem()->nodetp())));
                widget.btnconnectserver->setEnabled((curitems()->size() == 1));

                widget.btndisconnectserver->setVisible((isaction(ACTION_DISCONNECTSERVER, curitem()->nodetp())));
                widget.btndisconnectserver->setEnabled((curitems()->size() == 1));

                widget.btnimport->setVisible((isaction(ACTION_IMPORT, curitem()->nodetp())));
                widget.btnimport->setEnabled((curitems()->size() == 1));

                widget.btnexport->setVisible((isaction(ACTION_EXPORT, curitem()->nodetp())));
                widget.btnexport->setEnabled((curitems()->size() == 1));

                widget.btnsetfilter->setVisible((isaction(ACTION_SETFILTERED, curitem()->nodetp())) && (curitem()->viewtype() == uiwidgetitem::tvline));
                widget.btnsetfilter->setEnabled((curitems()->size() == 1));

                widget.btnresetfilter->setVisible((isaction(ACTION_SETFILTERED, curitem()->nodetp())) && (curitem()->viewtype() == uiwidgetitem::tvline));
                widget.btnresetfilter->setEnabled((curitems()->size() == 1) && ((curitem()->filter() != "")) && (curitem()->viewtype() == uiwidgetitem::tvline));

                widget.btnadditem->setVisible((isaction(ACTION_CREATEITEM, curitem()->nodetp())));
                widget.btnadditem->setEnabled((curitems()->size() == 1) );

                widget.btndeleteitem->setVisible( (isaction(ACTION_DELETEITEM, curitem()->nodetp())));

                widget.btnchangegroup->setVisible((isaction(ACTION_CHANGEGROUP, curitem()->nodetp())));
                widget.btnchangegroup->setEnabled(curitems()->size() > 0);

                widget.btnchangeagroup->setVisible((isaction(ACTION_CHANGEALARMGROUP, curitem()->nodetp())));
                widget.btnchangeagroup->setEnabled(curitems()->size() > 0);

                widget.btnchangegroup->setVisible((isaction(ACTION_CHANGEGROUP, curitem()->nodetp())));
                widget.btnchangegroup->setEnabled(curitems()->size() > 0);

                widget.btnclone->setVisible((isaction(ACTION_DUPLICATEITEM, curitem()->nodetp())) && (curitem()->viewtype() == uiwidgetitem::tvline));

                widget.btnimport1->setEnabled(false);
                widget.btnimport2->setEnabled(false);

                widget.btnclone->setVisible(false);
                widget.btnclone1->setVisible(false);

                widget.btnexport1->setEnabled(false);
                widget.btnexport2->setEnabled(false);

                widget.btnsetfilter1->setVisible((isaction(ACTION_SETFILTERED, curitem()->nodetp())) && (curitem()->viewtype() == uiwidgetitem::tvline));
                widget.btnsetfilter1->setEnabled((curitems()->size() == 1));

                widget.btnsetfilter2->setVisible(false);

                widget.btnresetfilter1->setVisible((isaction(ACTION_SETFILTERED, curitem()->nodetp())) && (curitem()->viewtype() == uiwidgetitem::tvline));
                widget.btnresetfilter1->setEnabled((curitems()->size() == 1)  && (curitem()->filter() != ""));

                widget.btnresetfilter2->setVisible(false);
                widget.btnchangegroup2->setVisible(false);
                widget.btnchangeagroup2->setVisible(false);
                widget.btnchangegroup2->setEnabled(false);
                widget.btnchangeagroup2->setEnabled(false);

                widget.btnadditem1->setVisible(false);
                widget.btnadditem2->setVisible(false);

                widget.btndeleteitem1->setVisible(false);
                widget.btndeleteitem2->setVisible(false);
                widget.btnexport1->setVisible(false);
                widget.btnimport1->setVisible(false);
                widget.btnexport2->setVisible(false);
                widget.btnimport2->setVisible(false);

                widget.btnstartservice->setVisible((isaction(ACTION_SET_STARTSERVICE, curitem()->nodetp())) && (curitem()->viewtype() == uiwidgetitem::tvline));
                widget.btnstartservice->setEnabled((curitems()->size() == 1) && (curitem()->tgtype() == SERVICE_STATUS_STOPED));

                widget.btnstopservice->setVisible((isaction(ACTION_SET_STOPSERVICE, curitem()->nodetp())) && (curitem()->viewtype() == uiwidgetitem::tvline));
                widget.btnstopservice->setEnabled((curitems()->size() == 1)  && (curitem()->tgtype() == SERVICE_STATUS_RUN));

                widget.btnstartservice1->setVisible(false);
                widget.btnstopservice1->setVisible(false);}


            if (curtreewidget() == widget.treeWidget1) {
                widget.btnaddserver->setVisible(false);
                widget.btnremoveserver->setVisible(false);
                widget.btnmapproject->setVisible(false);
                widget.btnunmapproject->setVisible(false);
                widget.btnnewproject->setVisible(false);
                widget.btnconnectserver->setVisible(false);
                widget.btnimport->setVisible(false);
                widget.btnexport->setVisible(false);
                widget.btnsetfilter->setVisible(false);
                widget.btnresetfilter->setVisible(false);
                widget.btnresetfilter->setVisible(false);
                widget.btnadditem->setVisible(false);
                widget.btndeleteitem->setVisible(false);
                widget.btnchangegroup->setVisible(false);
                widget.btnchangeagroup->setVisible(false);
                widget.btnstartservice->setVisible(false);
                widget.btnstopservice->setVisible(false);
                widget.btnclone->setVisible(false);

                widget.btnexport1->setVisible((isaction(ACTION_EXPORT, curitem()->nodetp())));
                widget.btnexport1->setEnabled((curitems()->size() == 1));

                widget.btnimport1->setVisible((isaction(ACTION_IMPORT, curitem()->nodetp())));
                widget.btnimport1->setEnabled((curitems()->size() == 1));

                widget.btnstartservice1->setVisible((isaction(ACTION_SET_STARTSERVICE, curitem()->nodetp())));
                widget.btnstartservice1->setEnabled((curitems()->size() == 1)  && (curitem()->tgtype() == SERVICE_STATUS_STOPED));

                widget.btnstopservice1->setVisible((isaction(ACTION_SET_STOPSERVICE, curitem()->nodetp())));
                widget.btnstopservice1->setEnabled((curitems()->size() == 1)  && (curitem()->tgtype() == SERVICE_STATUS_RUN));

                widget.btnsetfilter1->setVisible(false);
                widget.btnresetfilter1->setVisible(false);

                widget.btnsetfilter2->setVisible((isaction(ACTION_SETFILTERED, curitem()->nodetp())));
                widget.btnsetfilter2->setEnabled((curitems()->size() == 1));

                widget.btnresetfilter2->setVisible((isaction(ACTION_SETFILTERED, curitem()->nodetp())));
                widget.btnresetfilter2->setEnabled((curitems()->size() == 1)  && (curitem()->filter() != ""));

                widget.btnadditem1->setVisible((isaction(ACTION_CREATEITEM, curitem()->nodetp())));
                widget.btnadditem1->setEnabled((curitems()->size() == 1));

                widget.btndeleteitem1->setVisible( (isaction(ACTION_DELETEITEM, curitem()->nodetp())));

                widget.btnclone1->setVisible((isaction(ACTION_DUPLICATEITEM, curitem()->nodetp())));

                widget.btnchangegroup2->setVisible(false);
                widget.btnchangeagroup2->setVisible(false);
                widget.btnchangegroup2->setEnabled(false);
                widget.btnchangeagroup2->setEnabled(false);
                widget.btnexport2->setVisible(false);
                widget.btnimport2->setVisible(false);
                widget.btndeleteitem2->setVisible(false);}

            if (curtreewidget() == widget.treeWidget2) {
                widget.btnaddserver->setVisible(false);
                widget.btnremoveserver->setVisible(false);
                widget.btnmapproject->setVisible(false);
                widget.btnunmapproject->setVisible(false);
                widget.btnnewproject->setVisible(false);
                widget.btnconnectserver->setVisible(false);
                widget.btnimport->setVisible(false);
                widget.btnexport->setVisible(false);
                widget.btnsetfilter->setVisible(false);
                widget.btnresetfilter->setVisible(false);
                widget.btnresetfilter->setVisible(false);
                widget.btnadditem->setVisible(false);
                widget.btndeleteitem->setVisible(false);
                widget.btnchangegroup->setVisible(false);
                widget.btnchangeagroup->setVisible(false);
                widget.btnexport1->setVisible(false);
                widget.btnimport1->setVisible(false);
                widget.btnsetfilter1->setVisible(false);
                widget.btnresetfilter1->setVisible(false);
                widget.btnsetfilter2->setVisible(false);
                widget.btnresetfilter2->setVisible(false);
                widget.btnadditem1->setVisible(false);
                widget.btndeleteitem1->setVisible(false);
                widget.btnexport1->setVisible(false);
                widget.btnimport1->setVisible(false);
                widget.btnexport2->setVisible(false);
                widget.btnimport2->setVisible(false);
                widget.btnclone->setVisible(false);
                widget.btnclone1->setVisible(false);
                widget.btndeleteitem2->setVisible((isaction(ACTION_DELETEITEM, curitem()->nodetp())));
                widget.btnchangegroup2->setVisible(isaction(ACTION_CHANGEGROUP, curitem()->nodetp()));
                widget.btnchangegroup2->setEnabled(isaction(ACTION_CHANGEGROUP, curitem()->nodetp()));
                widget.btnchangeagroup2->setVisible(isaction(ACTION_CHANGEALARMGROUP, curitem()->nodetp()));
                widget.btnchangeagroup2->setEnabled(isaction(ACTION_CHANGEALARMGROUP, curitem()->nodetp()));}}

        void form_admin::screanopt(logscreen val) {
            screanOpt_ = val;
            widget.btnlogtype->setIcon(getIcon((val == lserror) ?  ACTION_LOGSCREANALL : ACTION_LOGSCREANERROR ));
            widget.btnclearlog->setToolTip(qtstr_translate(QString::fromStdString("toolmenue.clearlog")));
            widget.btnlogtype->setToolTip((val == lserror)
                    ? qtstr_translate(QString::fromStdString("toolmenue.setlogtypeall")) :
                    qtstr_translate(QString::fromStdString("toolmenue.setlogtypeerror")));
            widget.ErrorWidget->setVisible((val == lsallways));}

        void form_admin::proc_viewdouble( const QModelIndex & index ) {
            tagsviewmodel* md = dynamic_cast<tagsviewmodel*> (const_cast<QAbstractItemModel*> (index.model()));
            if (md) {
                guiaction operat = ACTION_SET_VALUE;
                std::string val = "";
                if (setvalform.execs(index.internalId(), val, operat)) {
                    transact_key2 = index.internalId();
                    inserttransaction(operat, val);};};}}}