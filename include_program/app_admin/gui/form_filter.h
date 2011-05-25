/* 
 * File:   form_filter.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 4 Март 2010 г., 3:05
 */

#ifndef _NSTREEFILTERFORM_H
#define	_NSTREEFILTERFORM_H


#include <admin/propertymanager.h>

#include "ui_form_filter.h"
#include "uiuitil.h"



namespace dvnci {
    namespace admin {

        class form_filter : public QDialog {
            Q_OBJECT
        public:
            form_filter();
            virtual ~form_filter();
            bool execs(nodetype ndtype, std::string& val, const iteminfo_map& grp);
            bool execs(std::string& val, nodetype& ndtype, const iteminfo_map& grp);

            void setEdit();
        private:
            bool global;
            QString disableStyle;
            QString enableStyle;
            QString disableinsiteStyle;
            QString enableinsiteStyle;
            stringed_filterclass* filtercl;
            std::string tmpcriteria_;
            Ui::form_filter widget;
            nodetype nodetype_;
            nodetype tmpnodetype_;


            void setnodetp(nodetype val, bool  _nosteinbox = false);
            void setnodetypeIndex(int val);

            void adjustSizeAll() {
                widget.framebyBind->adjustSize();
                widget.framebyName->adjustSize();
                widget.framebyComment->adjustSize();
                widget.framebyGroupType->adjustSize();
                widget.framebyRtType->adjustSize();
                widget.framebynodetype->adjustSize();
                widget.frameHeader->adjustSize();
                widget.frameButton->adjustSize();
                adjustSize();
                this->resize(this->minimumSize());}

            nodetype nodeType() {
                return nodetype_;}

            bool editCriteria(const std::string name, const QString & text) {
                if (filtercl != NULL) {
                    filtercl->setcriteria(name, str_from_qtstr_loc(text));}
                return (text.trimmed() != "");}

            void setStateFrame(QFrame* fr_ , bool val);
            void setVisibleFrame(nodetype val);
            void connectSlot();
            void disconnectSlot();

            bool okisActive() {
                return  (((filtercl) && (tmpcriteria_ != filtercl->criterias()))
                         || (!filtercl->isEnable()));}

            bool clearisActive() {
                return  (!((filtercl) && (!filtercl->isEnable())));}

            void clearCriteria() {
                if (filtercl) filtercl->clearcriteria();
                setEdit();}

            void setGroupList(const iteminfo_map& val, const indx_set* set_);
            void UpdateGroupList();
        public slots:

            void proc_lineEditbyName( const QString & text ) {
                setStateFrame(widget.framebyName, editCriteria(stringed_filterclass::NAME_CRITERIA, text));
                ;}

            void proc_lineEditbyComment( const QString & text ) {
                setStateFrame(widget.framebyComment, editCriteria(stringed_filterclass::COMMENT_CRITERIA, text));}

            void proc_lineEditbyBind( const QString & text ) {
                setStateFrame(widget.framebyBind, editCriteria(stringed_filterclass::BIND_CRITERIA, text));}

            void proc_setnodetp(int index) {
                setnodetypeIndex(index);
                setEdit();};

            void proc_btnOkclick() {
                accept();};

            void proc_btnCancelclick() {
                reject();};

            void proc_btnClearclick() {
                clearCriteria();};
            void proc_itemGroupChanged( QListWidgetItem * item );

            void proc_itemGroupTypeChanged( QListWidgetItem * item ) {};

            void proc_itemRtTypeChanged( QListWidgetItem * item ) {};
} ;
}}

#endif	/* _NSTREEFILTERFORM_H */
