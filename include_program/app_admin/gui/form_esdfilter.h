/* 
 * File:   form_esdfilter.h
 * Author: Serg
 *
 * Created on 8 Апрель 2010 г., 13:25
 */

#ifndef _ESDFILTERFORM_H
#define	_ESDFILTERFORM_H

#include <admin/importutil.h>

#include "uiuitil.h"
#include "ui_form_esdfilter.h"

namespace dvnci {
    namespace admin {

        class form_esdfilter : public QDialog {
            Q_OBJECT
        public:
            form_esdfilter();
            virtual ~form_esdfilter();
            bool execs(num64& val);
            void setparam(num64 val);
            void getparam(num64& val);
            QString gettype(num64 val);
            num64 settype(QString val);
        private:
            Ui::form_esdfilter widget;} ; }}

#endif	/* _ESDFILTERFORM_H */
