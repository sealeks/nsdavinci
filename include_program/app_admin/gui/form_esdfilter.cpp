/*
 * File:   form_esdfilter.cpp
 * Author: Serg
 *
 * Created on 8 Апрель 2010 г., 13:25
 */

#include "form_esdfilter.h"


namespace dvnci {
    namespace admin {

        form_esdfilter::form_esdfilter() {
            widget.setupUi(this);
            setWindowTitle(qtstr_translate(QString::fromStdString("esdfilter")));
            widget.label->setText(qtstr_translate(QString::fromStdString("esdfilter.title")));
            widget.labeltype->setText(qtstr_translate(QString::fromStdString("esdfilter.type")));
            widget.labelrange->setText(qtstr_translate(QString::fromStdString("esdfilter.range")));
            widget.labelstart->setText(qtstr_translate(QString::fromStdString("esdfilter.start")));
            widget.labelstop->setText(qtstr_translate(QString::fromStdString("esdfilter.stop")));}

        form_esdfilter::~form_esdfilter() {}

        bool form_esdfilter::execs(num64& val) {
            val = setesdnumcriteria(0, 060000, 0);
            setparam(val);
            exec();
            if (QDialog::Accepted == result()) {
                getparam(val);
                return true;}
            return false;}

        void form_esdfilter::setparam(num64 val) {
            widget.comboBoxtype->setItemText(0, gettype(val));
            widget.lineEditmin->setText(QString::number(((val & 0xFFFF0000) >> 16), 8));
            widget.lineEditmax->setText(QString::number((val & 0xFFFF), 8));}

        void form_esdfilter::getparam(num64& val) {
            num64 type = settype(widget.comboBoxtype->currentText());
            bool ok = true;
            num64 min = widget.lineEditmin->text().toInt(&ok, 8);
            if (!ok) min = 0;
            num64 max = widget.lineEditmax->text().toInt(&ok, 8);
            if (!ok) max = 060000;
            val = setesdnumcriteria(min, max, type);}

        QString form_esdfilter::gettype(num64 val) {
            num64 type = val;
            type = (type >> 32);
            switch (type) {
                case 8: return "X";
                case 9: return "Y";
                case 10: return "C";
                case 12: return "S";
                case 13: return "T";
                case 15: return "GX";
                case 16: return "GY";
                case 17: return "V";
                case 22: return "SP";
                case 27: return "B";}
            return "All";}

        num64 form_esdfilter::settype(QString val) {
            if (val == "X")  return 8;
            if (val == "Y")  return 9;
            if (val == "C")  return 10;
            if (val == "S")  return 12;
            if (val == "T")  return 13;
            if (val == "GX")  return 15;
            if (val == "GY")  return 16;
            if (val == "V")  return 17;
            if (val == "SP")  return 22;
            if (val == "B")  return 27;
            return 0;}
}}