/* 
 * File:   form_setvalue.h
 * Author: Serg
 *
 * Created on 25 Май 2010 г., 19:15
 */

#ifndef _SETVALUEFORM_H
#define	_SETVALUEFORM_H


#include <kernel/constdef.h>
#include <kernel/utils.h>

#include "interfacetransaction.h"
#include "uiuitil.h"
#include "ui_form_setvalue.h"



namespace dvnci {
    namespace admin {

        class form_setvalue : public QDialog {
            Q_OBJECT
        public:

            form_setvalue();
            virtual ~form_setvalue();

            bool execs(indx key, std::string& val,  int& oper);
            void setstate(int operation_);

        public slots:

            void proc_btnOkclick() {
                accept();};

            void proc_btnCancelclick() {
                reject();};

            void proc_rbsetvalueclick() {
                setstate(ACTION_SET_VALUE);};

            void proc_rbcommandclick() {
                setstate(ACTION_SET_COMMAND);};

            void proc_rbincvntclick() {
                setstate(ACTION_INCCOUNT);};

            void proc_rbdeccntclick() {
                setstate(ACTION_DECCOUNT);};

            void proc_rbvalidclick() {
                setstate(ACTION_SET_VALID);};

            void proc_rbinvalidclick() {
                setstate(ACTION_SET_INVALID);};

        private:
            int operation;
            Ui::form_setvalue widget;} ;}}

#endif	/* _SETVALUEFORM_H */
