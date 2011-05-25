/* 
 * File:   form_addserver.h
 * Author: Serg
 *
 * Created on 31 Март 2010 г., 20:40
 */

#ifndef _ADDSERVERFORM_H
#define	_ADDSERVERFORM_H



#include "ui_form_addserver.h"
#include "uiuitil.h"


namespace dvnci {
    namespace admin {

        class form_addserver : public QDialog {
            Q_OBJECT
        public:
            form_addserver();
            virtual ~form_addserver();
            bool execs( std::string& val, bool canlocal = false);

            void setcheck(bool val) {
                widget.verticalLayoutadmin->setEnabled(widget.checkboxlocal->checkState() == Qt::Checked);
                widget.verticallayoutpassword->setEnabled(widget.checkboxlocal->checkState() == Qt::Checked);
                widget.verticallayoutconstr->setEnabled(widget.checkboxlocal->checkState() == Qt::Checked);}
            void connectSlot();
            void disconnectSlot();
        private:
            Ui::form_addserver widget;

        public slots:

            void setChecked ( bool val) {
                setcheck( val);};

            void proc_btnOkclick() {
                accept();};

            void proc_btnCancelclick() {
                reject();};} ;}}

#endif	/* _ADDSERVERFORM_H */
