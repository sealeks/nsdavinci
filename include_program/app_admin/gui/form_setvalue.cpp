/*
 * File:   form_setvalue.cpp
 * Author: Serg
 *
 * Created on 25 Май 2010 г., 19:15
 */

#include "form_setvalue.h"

namespace dvnci {
    namespace admin {

        form_setvalue::form_setvalue() {
            widget.setupUi(this);
            connect(widget.btncancel,   SIGNAL(clicked() ),     this, SLOT(proc_btnCancelclick()));
            connect(widget.btnok ,      SIGNAL(clicked() ),     this, SLOT(proc_btnOkclick()));
            connect(widget.rbsetvalue,   SIGNAL(clicked() ),     this, SLOT(proc_rbsetvalueclick()));
            connect(widget.rbcommand,   SIGNAL(clicked() ),     this, SLOT(proc_rbcommandclick()));
            connect(widget.rbincvnt,   SIGNAL(clicked() ),     this, SLOT(proc_rbincvntclick()));
            connect(widget.rbdeccnt,   SIGNAL(clicked() ),     this, SLOT(proc_rbdeccntclick()));
            connect(widget.rbvalid,   SIGNAL(clicked() ),     this, SLOT(proc_rbvalidclick()));
            connect(widget.rbinvalid,   SIGNAL(clicked() ),     this, SLOT(proc_rbinvalidclick()));
            setWindowTitle(qtstr_translate(QString::fromStdString("setvalue.header")));
            widget.labelHeader->setText(qtstr_translate(QString::fromStdString("setvalue.header")));
            widget.rbsetvalue->setText(qtstr_translate(QString::fromStdString("setvalue.setvalue")));
            widget.rbcommand->setText(qtstr_translate(QString::fromStdString("setvalue.setcommand")));
            widget.rbincvnt->setText(qtstr_translate(QString::fromStdString("setvalue.inccnt")));
            widget.rbdeccnt->setText(qtstr_translate(QString::fromStdString("setvalue.deccnt")));
            widget.rbvalid->setText(qtstr_translate(QString::fromStdString("setvalue.valid")));
            widget.rbinvalid->setText(qtstr_translate(QString::fromStdString("setvalue.invalid")));}

        form_setvalue::~form_setvalue() {}

        bool form_setvalue::execs(indx key, std::string& val,  guiaction& oper) {
            setstate(oper);
            exec();
            bool result_ = (QDialog::Accepted == result());
            if (result_) {
                val = str_from_qtstr_loc(widget.valueedit->text());
                oper = operation;
                return true;}
            return false;}

        void form_setvalue::setstate(int oper) {
            bool tmp = ((operation != ACTION_DECCOUNT) && (operation != ACTION_INCCOUNT) &&
                        (operation != ACTION_SET_INVALID) && (operation != ACTION_SET_VALID));
            if ((tmp) &&  (operation != ACTION_SET_COMMAND) && (operation != ACTION_SET_VALUE)) oper = ACTION_SET_VALUE;
            operation = oper;
            widget.rbsetvalue->setChecked(operation == ACTION_SET_VALUE);
            widget.rbcommand->setChecked(operation == ACTION_SET_COMMAND);
            widget.rbincvnt->setChecked(operation == ACTION_INCCOUNT);
            widget.rbdeccnt->setChecked(operation == ACTION_DECCOUNT);
            widget.rbvalid->setChecked(operation == ACTION_SET_VALID);
            widget.rbinvalid->setChecked(operation == ACTION_SET_INVALID);
            widget.valueedit->setEnabled((operation == ACTION_SET_VALUE) || (operation == ACTION_SET_COMMAND));}}}