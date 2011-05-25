/*
 * File:   form_addserver.cpp
 * Author: Serg
 *
 * Created on 31 Март 2010 г., 20:40
 */

#include "form_addserver.h"

namespace dvnci {
    namespace admin {

        void form_addserver::connectSlot() {
            connect(widget.checkboxlocal,  SIGNAL(clicked(bool) ), this, SLOT(setChecked( bool )));
            connect(widget.OKButton ,      SIGNAL(clicked() ),     this, SLOT(proc_btnOkclick()));
            connect(widget.CancelButton ,  SIGNAL(clicked() ),     this, SLOT(proc_btnCancelclick()));}

        void form_addserver::disconnectSlot() {
            disconnect(widget.checkboxlocal,  SIGNAL(clicked(bool) ));
            disconnect(widget.OKButton ,      SIGNAL(clicked() ));
            disconnect(widget.CancelButton ,  SIGNAL(clicked() ));}

        form_addserver::form_addserver() {
            widget.setupUi(this);
            connectSlot();
            setWindowTitle(qtstr_translate(QString::fromStdString("addserver")));
            widget.labelheader->setText(qtstr_translate(QString::fromStdString("addserver.header")));
            widget.labelconstr->setText(qtstr_translate(QString::fromStdString("addserver.host")));
            widget.labeladmin->setText(qtstr_translate(QString::fromStdString("addserver.admin")));
            widget.labelpassword->setText(qtstr_translate(QString::fromStdString("addserver.pass")));}

        form_addserver::~form_addserver() {
            disconnectSlot();}

        bool form_addserver::execs( std::string& val, bool canlocal) {
            widget.checkboxlocal->setCheckState(Qt::Unchecked);
            std::string host = "";
            std::string port = "";
            std::string admin = "";
            std::string password = "";
            unsigned int tout;
            parse_servinfo(val, host, port, tout, admin, password);
            if (host != "") val = tout == DEFAULT_DVNCI_TIMOUT ? host + ":" + port : host + ":" + port + ":" + to_str(tout);
            else val = "";
            widget.lineeditconstr->setText(qtstr_from_str_loc(val));
            widget.lineeditadmin->setText(qtstr_from_str_loc(admin));
            widget.lineditpassword->setText(qtstr_from_str_loc(password));
            widget.checkboxlocal->setVisible(false);
            exec();
            bool result_ = (QDialog::Accepted == result());
            if (widget.checkboxlocal->checkState() == Qt::Checked) val = "local";
            else val = str_from_qtstr_loc(widget.lineeditconstr->text()) + "\15" +
                widget.lineeditadmin->text().toStdString() + "\15" + widget.lineditpassword->text().toStdString();
            return result_;}}}