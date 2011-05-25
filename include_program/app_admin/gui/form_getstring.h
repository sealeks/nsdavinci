/* 
 * File:   form_getstring.h
 * Author: Serg
 *
 * Created on 9 Апрель 2010 г., 19:35
 */

#ifndef _GETSTRINGFORM_H
#define	_GETSTRINGFORM_H

#include "ui_form_getstring.h"
#include "uiuitil.h"


namespace dvnci {
    namespace admin {

        class form_getstring : public QDialog {
            Q_OBJECT
        public:
            form_getstring();
            virtual ~form_getstring();

            bool execs(std::string& val, const std::string caption = "inputtext" , const std::string header = "headertext", bool isutf = false) {
                bool result_ = false;
                widget.lineEdit->setText(QString(val.c_str()));
                widget.label->setText(qtstr_translate(QString::fromStdString(header)));
                setWindowTitle(qtstr_translate(QString::fromStdString(caption)));
                exec();
                result_ = (QDialog::Accepted == result());
                if ( result_) {
                    if (isutf)
                        val = str_from_qtstr_utf8(widget.lineEdit->text());
                    else
                        val = widget.lineEdit->text().toStdString();}
                return result_;}

        private:
            Ui::form_getstring widget;} ;
}}

#endif	/* _GETSTRINGFORM_H */
