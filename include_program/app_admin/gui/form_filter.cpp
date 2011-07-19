/*
 * File:   form_filter.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 4 Март 2010 г., 3:05
 */

#include "form_filter.h"

namespace dvnci {
    namespace admin {

        form_filter::form_filter() {
            widget.setupUi(this);

            disableStyle = "background-color: rgb(236, 236, 236);";
            enableStyle = "background-color: rgb(236, 252, 236);";
            disableinsiteStyle = "border-color: rgb(221, 221, 221);\nbackground-color: rgb(230, 230, 230);";
            enableinsiteStyle = "background-color: rgb(255, 255, 255);\nborder-color: rgb(74, 255, 46);";
            setWindowTitle(qtstr_translate(QString::fromStdString("filterform")));
            widget.HeadLineLable->setText(qtstr_translate(QString::fromStdString("filterform.title")));
            widget.labelbyName->setText(qtstr_translate(QString::fromStdString("filterform.name")));
            widget.labelbyComment->setText(qtstr_translate(QString::fromStdString("filterform.comment")));
            widget.labelbyBind->setText(qtstr_translate(QString::fromStdString("filterform.bind")));
            widget.labelbynodetype->setText(qtstr_translate(QString::fromStdString("filterform.typefilter")));
            widget.labelbyGroup->setText(qtstr_translate(QString::fromStdString("filterform.group")));
            widget.labelbyRtType->setText(qtstr_translate(QString::fromStdString("filterform.itemtype")));
            widget.labelbyGroupType->setText(qtstr_translate(QString::fromStdString("filterform.grouptype")));
            widget.BtnClear->setText(qtstr_translate(QString::fromStdString("filterform.clear")));}

        form_filter::~form_filter() {}

        void form_filter::connectSlot() {
            connect(widget.lineEditbyName,        SIGNAL(textEdited ( const QString & ) ),          this, SLOT(proc_lineEditbyName( const QString& )));
            connect(widget.lineEditbyComment,     SIGNAL(textEdited ( const QString & ) ),          this, SLOT(proc_lineEditbyComment( const QString& )));
            connect(widget.lineEditbyBind ,       SIGNAL(textEdited ( const QString & ) ),          this, SLOT(proc_lineEditbyBind( const QString& )));
            connect(widget.comboBoxbynodetype ,   SIGNAL(currentIndexChanged( int ) ),              this, SLOT(proc_setnodetp(int )));
            connect(widget.BntOk ,                SIGNAL(clicked() ),                               this, SLOT(proc_btnOkclick()));
            connect(widget.BtnCancel ,            SIGNAL(clicked() ),                               this, SLOT(proc_btnCancelclick()));
            connect(widget.BtnClear ,             SIGNAL(clicked() ),                               this, SLOT(proc_btnClearclick()));
            connect(widget.listWidgetbyGroup ,    SIGNAL(itemClicked ( QListWidgetItem *  ) ),      this, SLOT(proc_itemGroupChanged ( QListWidgetItem *  )));
            connect(widget.listWidgetbyGroupType, SIGNAL(itemClicked  ( QListWidgetItem *  ) ),      this, SLOT(proc_itemGroupTypeChanged ( QListWidgetItem *  )));
            connect(widget.listWidgetbyRtType ,   SIGNAL(itemClicked ( QListWidgetItem *  ) ),      this, SLOT(proc_itemRtTypeChanged ( QListWidgetItem *  )));}

        void form_filter::disconnectSlot() {
            disconnect(widget.lineEditbyName,         SIGNAL(textEdited ( const QString & ) ));
            disconnect(widget.lineEditbyComment,      SIGNAL(textEdited ( const QString & ) ));
            disconnect(widget.lineEditbyBind ,        SIGNAL(textEdited ( const QString & ) ));
            disconnect(widget.comboBoxbynodetype ,    SIGNAL(currentIndexChanged( int ) ));
            disconnect(widget.BntOk ,                 SIGNAL(clicked() ));
            disconnect(widget.BtnCancel ,             SIGNAL(clicked() ));
            disconnect(widget.BtnClear ,              SIGNAL(clicked() ));
            disconnect(widget.listWidgetbyGroup ,     SIGNAL(itemClicked ( QListWidgetItem *  ) ));
            disconnect(widget.listWidgetbyGroupType,  SIGNAL(itemClicked ( QListWidgetItem *  ) ));
            disconnect(widget.listWidgetbyRtType ,    SIGNAL(itemClicked  ( QListWidgetItem *  ) ));}

        bool form_filter::execs(nodetype ndtype, std::string& val, const iteminfo_map& grp) {
            global = false;
            std::string tmp_str = val;
            filtercl = new stringed_filterclass(tmp_str);
            tmpcriteria_ = val;
            setVisibleFrame(ndtype);
            tmpnodetype_ = ndtype;

            filtercl = new stringed_filterclass(tmp_str);


            setGroupList(grp, filtercl->idxcriteria(GROUP_CRITERIA));
            ;
            connectSlot();

            UpdateGroupList();
            setEdit();
            adjustSizeAll();

            exec();
            bool result_ = (QDialog::Accepted == result());
            if (result_) {
                val = filtercl->criterias();}
            delete filtercl;
            filtercl = NULL;
            disconnectSlot();
            return result_;}

        bool form_filter::execs(std::string& val, nodetype& ndtype, const iteminfo_map& grp) {
            global = true;
            std::string tmp_str = val;
            filtercl = new stringed_filterclass(tmp_str);
            tmpcriteria_ = val;
            setVisibleFrame(ndtype);
            setnodetp(ndtype);
            tmpnodetype_ = ndtype;




            setGroupList(grp, filtercl->idxcriteria(GROUP_CRITERIA));

            connectSlot();

            UpdateGroupList();
            setEdit();
            adjustSizeAll();

            exec();
            bool result_ = (QDialog::Accepted == result());
            if (result_) {
                val = filtercl->criterias();
                ndtype = nodeType();}
            delete filtercl;
            filtercl = NULL;
            disconnectSlot();
            return result_;}

        void form_filter::setEdit() {
            widget.lineEditbyName->setText(qtstr_from_str_loc(filtercl->criteria(NAME_CRITERIA)));
            setStateFrame(widget.framebyName, filtercl->iscriteria(NAME_CRITERIA));
            widget.lineEditbyComment->setText(qtstr_from_str_loc(filtercl->criteria(COMMENT_CRITERIA)));
            setStateFrame(widget.framebyComment, filtercl->iscriteria(COMMENT_CRITERIA));
            widget.lineEditbyBind->setText(qtstr_from_str_loc(filtercl->criteria(BIND_CRITERIA)));
            setStateFrame(widget.framebyBind, filtercl->iscriteria(BIND_CRITERIA));
            setStateFrame(widget.framebyGroup, filtercl->isidxcriteria(GROUP_CRITERIA));
            adjustSizeAll();}

        void form_filter::setnodetp(nodetype val, bool  _nosteinbox ) {
            if (nodetype_ != val) {
                nodetype_ = val;
                int tmpindx = 0;
                switch (nodetype_) {
                    case NT_ROOT_GROUPS:{
                        tmpindx = 3;
                        break;};
                    case NT_GROUP:{
                        tmpindx = 1;
                        break;};
                    case NT_ROOT_AGROUPS:{
                        tmpindx = 4;
                        break;};
                    case NT_AGROUP:{
                        tmpindx = 2;
                        break;};
                    case NT_ROOT_USERS:{
                        tmpindx = 5;
                        break;};}
                if (!_nosteinbox) {
                    widget.comboBoxbynodetype->setCurrentIndex(tmpindx);}
                setVisibleFrame(nodetype_);}}

        void form_filter::setnodetypeIndex(int val) {

            if (filtercl != NULL) {
                filtercl->clearcriteria();
                tmpcriteria_ = "";}

            switch (val) {
                case 3:{
                    setnodetp(NT_ROOT_GROUPS, true);
                    break;};
                case 1:{
                    setnodetp(NT_GROUP, true);
                    break;};
                case 4:{
                    setnodetp(NT_ROOT_AGROUPS, true);
                    break;};
                case 2:{
                    setnodetp(NT_AGROUP, true);
                    break;};
                case 5:{
                    setnodetp(NT_ROOT_USERS, true);
                    break;};
                default:{
                    setnodetp(0, true);
                    break;};}}

        void form_filter::setStateFrame(QFrame* fr_ , bool val) {
            if (fr_ == widget.framebyName) {
                widget.framebyName->setStyleSheet(val ? enableStyle : disableStyle);
                widget.lineEditbyName->setStyleSheet(val ? enableinsiteStyle : disableinsiteStyle);}
            if (fr_ == widget.framebyBind) {
                widget.framebyBind->setStyleSheet(val ? enableStyle : disableStyle);
                widget.lineEditbyBind->setStyleSheet(val ? enableinsiteStyle : disableinsiteStyle);}
            if (fr_ == widget.framebyComment) {
                widget.framebyComment->setStyleSheet(val ? enableStyle : disableStyle);
                widget.lineEditbyComment->setStyleSheet(val ? enableinsiteStyle : disableinsiteStyle);}
            if (fr_ == widget.framebynodetype) {
                widget.framebynodetype->setStyleSheet(val ? enableStyle : disableStyle);
                widget.comboBoxbynodetype->setStyleSheet(val ? enableinsiteStyle : disableinsiteStyle);}
            if (fr_ == widget.framebyGroupType) {
                widget.framebyGroupType->setStyleSheet(val ? enableStyle : disableStyle);
                widget.listWidgetbyGroupType->setStyleSheet(val ? enableinsiteStyle : disableinsiteStyle);}
            if (fr_ == widget.framebyRtType) {
                widget.framebyRtType->setStyleSheet(val ? enableStyle : disableStyle);
                widget.listWidgetbyRtType->setStyleSheet(val ? enableinsiteStyle : disableinsiteStyle);}
            if (fr_ == widget.framebyGroup) {
                widget.framebyGroup->setStyleSheet(val ? enableStyle : disableStyle);
                widget.listWidgetbyGroup->setStyleSheet(val ? enableinsiteStyle : disableinsiteStyle);}
            widget.BntOk->setEnabled(okisActive());
            widget.BtnClear->setEnabled(clearisActive());}

        void form_filter::setVisibleFrame(nodetype val) {
            if ((global) && (nodeType() == 0)) {
                widget.framebynodetype->setVisible(true);
                widget.framebyName->setVisible(false);
                widget.framebyBind->setVisible(false);
                widget.framebyComment->setVisible(false);
                widget.framebyGroupType->setVisible(false);
                widget.framebyRtType->setVisible(false);
                widget.framebyGroup->setVisible(false);
                adjustSizeAll();
                return;}
            switch (val) {
                case NT_ROOT_GROUPS:{
                    widget.framebyName->setVisible(true);
                    widget.framebyBind->setVisible(false);
                    widget.framebyComment->setVisible(false);
                    widget.framebyGroupType->setVisible(false);
                    widget.framebyRtType->setVisible(false);
                    widget.framebyGroup->setVisible(false);
                    break;}
                case NT_GROUP:{
                    widget.framebyName->setVisible(true);
                    widget.framebyBind->setVisible(true);
                    widget.framebyComment->setVisible(false);
                    widget.framebyGroupType->setVisible(false);
                    widget.framebyRtType->setVisible(false);
                    widget.framebyGroup->setVisible(global);
                    break;}
                case NT_UTIL_MAINTABLE:{
                    widget.framebyName->setVisible(true);
                    widget.framebyBind->setVisible(true);
                    widget.framebyComment->setVisible(false);
                    widget.framebyGroupType->setVisible(false);
                    widget.framebyRtType->setVisible(false);
                    widget.framebyGroup->setVisible(true);
                    break;}
                case NT_UTIL_GROUPTABLE:{
                    widget.framebyName->setVisible(true);
                    widget.framebyBind->setVisible(false);
                    widget.framebyComment->setVisible(false);
                    widget.framebyGroupType->setVisible(false);
                    widget.framebyRtType->setVisible(false);
                    widget.framebyGroup->setVisible(false);
                    break;}
                default:{
                    widget.framebyName->setVisible(true);
                    widget.framebyBind->setVisible(false);
                    widget.framebyComment->setVisible(false);
                    widget.framebyGroupType->setVisible(false);
                    widget.framebyRtType->setVisible(false);
                    widget.framebyGroup->setVisible(false);}}
            widget.framebynodetype->setVisible(global);

            adjustSizeAll();}

        void form_filter::setGroupList(const iteminfo_map& val, const indx_set* set_) {
            widget.listWidgetbyGroup->clear();
            iteminfo_map::const_iterator it = val.begin();
            QListWidgetItem* tmpqls = new QListWidgetItem(widget.listWidgetbyGroup, -1);
            tmpqls->setText(qtstr_translate(qtstr_from_str_loc("filterform.all")));
            widget.listWidgetbyGroup->addItem(tmpqls);
            while (it != val.end()) {
                tmpqls = new QListWidgetItem(widget.listWidgetbyGroup, it->first);
                tmpqls->setText(qtstr_from_str_loc(it->second.name()));
                widget.listWidgetbyGroup->addItem(tmpqls);
                ++it;}
            UpdateGroupList();}

        void form_filter::UpdateGroupList() {
            for (int i = 0; i < this->widget.listWidgetbyGroup->count(); i++) {
                if (widget.listWidgetbyGroup->item(i)->type() == -1) {
                    widget.listWidgetbyGroup->item(i)->setCheckState (!filtercl->isidxcriteria(GROUP_CRITERIA) ?
                            Qt::Checked : Qt::Unchecked);}
                else {
                    widget.listWidgetbyGroup->item(i)->setCheckState (((filtercl->idxcriteria(GROUP_CRITERIA) != NULL) &&
                                                                 (filtercl->idxcriteria(GROUP_CRITERIA)->find(widget.listWidgetbyGroup->item(i)->type())
                                                                  != filtercl->idxcriteria(GROUP_CRITERIA)->end())) ?
                            Qt::Checked : Qt::Unchecked);}}}

        void form_filter::proc_itemGroupChanged( QListWidgetItem * item ) {

            if (filtercl == NULL) return;

            if (item->checkState() == Qt::Unchecked) {
                if (item->type() != -1) {
                    filtercl->removeidxcriteria(GROUP_CRITERIA, item->type());}}
            else {
                if (item->type() != -1) {
                    filtercl->addidxcriteria(GROUP_CRITERIA, item->type());}
                else filtercl->clearidxcriteria(GROUP_CRITERIA);}

            UpdateGroupList();
            setEdit();};}}