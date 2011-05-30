/* 
 * File:   form_admin.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 27 Ноябрь 2009 г., 19:15
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H







#include <kernel/constdef.h>
#include <admin/factory.h>
#include <admin/importutil.h>

#include "viewmodels.h"
#include "uiuitil.h"

#include <QtGui/QTreeWidgetItem>
#include <QtGui/QIcon>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMenu>
#include <QList>
#include <QTime>
#include <QSize>
#include <QPixmap>
#include <QPainter>
#include <QListWidgetItem>
#include <QCustomEvent>
#include <QAbstractSlider>

#include "interfaceproccessor.h"
#include "interfacetransaction.h"

#include "form_addserver.h"
#include "form_filter.h"

#include "uiwidgetitem.h"
#include "admin_configer.h"
#include "ui_form_admin.h"
#include "form_import.h"
#include "form_setvalue.h"

namespace dvnci {
    namespace admin {


        const guiaction NT_VIS_CASCADE = 0x4001;
        const guiaction NT_VIS_LINE = 0x4002;
        const guiaction ACTION_SETFILTERED_ON = 0x4003;
        const guiaction ACTION_SETFILTERED_OFF = 0x4004;

        const guiaction ACTION_ERRORITEM = 0x4005;
        const guiaction ACTION_OKITEM = 0x4006;
        const guiaction ACTION_LOGSCREANALL = 0x4007;
        const guiaction ACTION_LOGSCREANERROR = 0x4008;
        const guiaction ACTION_LOGSCREANCLEAR = 0x4009;


        typedef std::vector<adminintf_ptr>             adminintf_vect;

        typedef boost::shared_ptr<registry_filter_map> registry_filter_ptr;
        typedef std::vector<registry_filter_ptr>       registry_filter_vect;

        // абстрастный медиатор управленя видом правой панели

        class abstractmediator {
        public:

            abstractmediator() {}

            virtual ~abstractmediator() {};

            virtual void init() {};

            virtual void uninit() {};} ;

        typedef boost::shared_ptr<abstractmediator> viewmediator_ptr;

        typedef std::pair<guiaction, viewmediator_ptr> mediator_pair;
        typedef std::map<guiaction , viewmediator_ptr, std::less<guiaction>, std::allocator<mediator_pair > > mediator_map;

        class form_admin : public QMainWindow {

            Q_OBJECT
        public:
            enum logscreen {
                lserror, lsallways} ;

            form_admin();
            virtual ~form_admin();
            
            void   registmediator(nodetype tp, abstractmediator* medr);
            void   registmediator(nodetype* tp, size_t cnt, abstractmediator* medr);
            void   registicon(int tp, QIcon& icn);
            void   registicon(int* tp, size_t cnt, QIcon& icn);
            QIcon  getIcon(int tp);
            void   mediator(abstractmediator* medr);
            void   mediator(nodetype tp);
            abstractmediator* mediator() const { return currentmediator;}
            void   loaditem(uiwidgetitem* item = 0);
            Ui::form_admin*  mainwidget() { return &widget;}


            void  addtransaction(basetransaction* transact_cl);
            void  inserttransaction(guiaction tp, std::string val = "");
            void  addviewtransaction(viewtransaction* transact_cl);
            void  insertviewtransaction(guiaction tp);

            void  currenttransaction(guiaction val ) {
                currtransact = val;}

            guiaction   currenttransaction() const {
                return currtransact;}

            uiwidgetitem* curitem() const {
                return curitem_;}




        protected:
            // состояние окна логирования

            void   createmenue();

            logscreen screanopt() const {
                return screanOpt_;}
            void screanopt(logscreen val);
            // закрытие окна логирования

            void logscreenclose() {
                widget.ErrorWidget->setVisible((screanOpt_ == lsallways));}
            // очистка лог сообщений
            void clearlogscreen();
            void readserverfromconfigurator();
            void loadserver(adminintf_ptr intf);
            void loadserver(uiwidgetitem* item, adminintf_ptr intf);

            void addserver(std::string constr = "") {
                (constr == "") ?
                        loadserver(admin::factory::build(getlocalbasepath(), NS_ADMIN_APPLICATION )) :
                        loadserver(admin::factory::build((const char*) constr.c_str()));}

            void addserver(uiwidgetitem* item, std::string constr = "") {
                (constr == "") ?
                        loadserver(item, admin::factory::build(getlocalbasepath(),  NS_ADMIN_APPLICATION )) :
                        loadserver(item, admin::factory::build((const char*) constr.c_str()));}

            void addloglist( int_dvncierror_map val, guiaction trasact_ = 0);
            void showmessagebox( int_dvncierror_map val, guiaction trasact_ = 0);
            virtual void customEvent(QEvent * event);
            void updateitemexs(indx_widgit_map* items, iteminfo_map& map_);
            void removeitems(indx_widgit_map* items);
            void additem_to_parent(nodetype type, indx id);
            indx_widgit_map* curitems() const;
            entity_map* nodesmap()  const;
            indx_set* nodesset() const;
            void select_and_loaditem(uiwidgetitem* item = 0);

            QTreeWidget* curtreewidget() const {
                return (!curtreewidget_) ? widget.treeWidget : curtreewidget_;};

        private:

            bool isLoading;
            mutable uiwidgetitem* curitem_;
            mutable entity_map nodemap_;
            mutable indx_set nodeset_;
            mutable indx_widgit_map curitems_;
            mutable indx_set viewset_;
            QMenu* mainTreeMenue;
            Ui::form_admin widget;
            mediator_map* mediators;
            icon_map* icons;
            registry_filter_vect filter_vect;
            adminintf_vect intf_vect;
            abstractmediator* currentmediator;

            QTreeWidget* curtreewidget_;
            indx transact_key2;
            indx toprow_;
            indx countrow_;
            guiaction currtransact;
            logscreen screanOpt_;
            uiwidgetitem* rootitem;
            indx intfcnt;

            QIcon* nillIcon;
            QIcon* filterIcon;

            int_treewidget_map treewidgetsmap;
            callable_transactionmain infproccess;
            callable_transactionview viewproccess;

            form_getstring addItemForm;
            form_addserver addserverForm;
            form_import importform;
            form_setvalue setvalform;
            form_filter treeFilterForm;
            QFileDialog fileDialog;
            admin_configer configurator;
            boost::thread thmain;
            boost::thread thview;

            nodetype_actionmap_map actionregistry;
            guiaction_action_map   actionmaps;

            //  контекстное меню дерева
            void invisibletreemenue();
            void drawtable();
            bool needmerge();

            guiaction_action_map* getactionregistry(nodetype val);
            void registrate_action(guiaction id, nodetype val);
            bool isaction(guiaction id, nodetype val);

            void propertytab(propertytable_map& tabl);
            propertytable_map& propertytab() const;

            void updateproperty(propedittype type, QString val);
            void updateproperty(propedittype type, bool cheched_);
            void updateproperty(propedittype type, int val);

            void resetnavigator() {
                widget.btnkindview->setIcon(getIcon(curitem()->viewtype() != uiwidgetitem::tvline
                        ? NT_VIS_LINE : NT_VIS_CASCADE));
                widget.btnkindview->setToolTip(curitem()->viewtype() != uiwidgetitem::tvline
                        ? qtstr_translate(QString::fromStdString("toolmenue.setviewkindline")) :
                        qtstr_translate(QString::fromStdString("toolmenue.setviewkindcascade")));}

            void settoolbars();

            QList<QAction*>* treeMenuList;
            QAction* unmapprj_action;
            QAction* mapprj_action;
            QAction* newprj_action;
            QAction* import_action;
            QAction* export_action;
            QAction* createentity_action;
            QAction* eraseentity_action;
            QAction* setfilter_action;
            QAction* addserver_action;
            QAction* removeserver_action;
            QAction* duplicate_action;
            QAction* connect_action;
            QAction* disconnect_action;
            QAction* startservice_action;
            QAction* stopservice_action;

            QMenu* changegroup_menu;
            QMenu* changeagroup_menu;

            propertytable_map propertytab_in;
            mutable propertytable_map propertytab_out;

        public slots:

            void proc_treeclick(QTreeWidgetItem* item, int val);
            void proc_mergeclick();
            void proc_changeviewkindclick();
            void proc_itchange( QTableWidgetItem* item_);
            void proc_rowcountchange ( int oldCount, int newCount ) {};
            void proc_valuechange ( int value );
            void proc_treecontext ( const QPoint& val);
            void proc_unmapprj();
            void proc_mapprj();
            void proc_newprj();
            void proc_createentety();
            void proc_eraseentety();
            void proc_addserver();
            void proc_removeserver();
            void proc_connectserver();
            void proc_disconnectserver();
            void proc_import();
            void proc_export();
            void proc_setfilter();
            void proc_resetfilter();
            void proc_changegroup(QAction* action);
            void proc_changeagroup(QAction* action);
            void proc_logclick();
            void proc_error();
            void proc_incallcount();
            void proc_decallcount();
            void proc_setallvalid();
            void proc_setallinvalid();
            void proc_kvit();
            void proc_startservice();
            void proc_stopservice();
            void proc_groupkvit() {}
            void proc_agroupkvit() {}
            void proc_viewdouble( const QModelIndex & index );
            void proc_duplicate();} ;

        class rootmediator : public abstractmediator {
        public:

            rootmediator(form_admin* mw_) {
                mw = mw_;}

        protected:
            form_admin* mw;
            guiaction transactid;} ;

        class entetymediator : public rootmediator {
        public:

            entetymediator(form_admin* mw_) : rootmediator(mw_) {
                transactid = 0;}


            virtual void init() {
                mw->mainwidget()->propertyframe->setVisible(true);}

            virtual void uninit() {
                mw->mainwidget()->propertyframe->setVisible(false);}} ;

        class nullviewmediator : public rootmediator {
        public:

            nullviewmediator(form_admin* mw_,  guiaction transid = 0) : rootmediator(mw_) {
                transactid = transid;}


            virtual void init() {
                mw->mainwidget()->propertyframe->setVisible(false);
                mw->mainwidget()->viewframe->setVisible(false);
                mw->mainwidget()->nillframe->setVisible(true);}

            virtual void uninit() {
                mw->mainwidget()->nillframe->setVisible(false);}} ;

        class defaultviewmediator : public rootmediator {
        public:

            defaultviewmediator(form_admin* mw_,  guiaction transid = 0) : rootmediator(mw_) {
                transactid = transid;}

            virtual void init() {
                mw->mainwidget()->propertyframe->setVisible(true);
                mw->loaditem(mw->curitem());}

            virtual void uninit() {
                mw->mainwidget()->propertyframe->setVisible(false);}} ;

        class findermediator : public rootmediator {
        public:

            findermediator(form_admin* mw_,  guiaction transid = 0) : rootmediator(mw_) {
                transactid = transid;}

            virtual void init() {
                mw->mainwidget()->propertyframe->setVisible(false);
                if (mw->curitem()->viewtype() == uiwidgetitem::tvcascade)
                    mw->inserttransaction(ACTION_SETFILTERED);}

            virtual void uninit() {
                ;}} ;

        class utilmediator : public rootmediator {
        public:

            utilmediator(form_admin* mw_, baseviewmodel* mod_, guiaction transid = 0) : rootmediator(mw_) {
                transactid = transid;
                mod = mod_;}

            virtual ~utilmediator() {
                delete mod;}

            virtual void init() {
                mw->mainwidget()->viewframe->setVisible(true);
                mw->mainwidget()->treeframe1->setVisible(false);
                mw->mainwidget()->treeframe2->setVisible(false);
                mw->mainwidget()->tableview->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
                mod->interfs(mw->curitem()->intf());
                if (mod->mbDelegate)
                    mw->mainwidget()->tableview->setItemDelegate(mod->mbDelegate);
                mw->mainwidget()->btnsetfilterview->setVisible((mw->curitem()->nodetp() == NT_UTIL_MAINTABLE) || (mw->curitem()->nodetp() == NT_UTIL_GROUPTABLE));
                mw->mainwidget()->btndeccnt->setVisible(mw->curitem()->nodetp() == NT_UTIL_MAINTABLE);
                mw->mainwidget()->btninccnt->setVisible(mw->curitem()->nodetp() == NT_UTIL_MAINTABLE);
                mw->mainwidget()->btnsetallinvalid->setVisible(mw->curitem()->nodetp() == NT_UTIL_MAINTABLE);
                mw->mainwidget()->btnsetallvalid->setVisible(mw->curitem()->nodetp() == NT_UTIL_MAINTABLE);
                mw->mainwidget()->btnkvit->setVisible((mw->curitem()->nodetp() == NT_UTIL_MAINTABLE) || (mw->curitem()->nodetp() == NT_UTIL_JOURNAL) || (mw->curitem()->nodetp() == NT_UTIL_ALARM));
                if (transactid) {
                    mw->currenttransaction(transactid);
                    mw->insertviewtransaction(transactid);}}

            virtual void uninit() {
                mw->currenttransaction(0);
                mw->mainwidget()->tableview->setModel(0);
                mw->mainwidget()->viewframe->setVisible(false);}

            baseviewmodel* mod;} ;
}}



#endif	/* _MAINWINDOW_H */
