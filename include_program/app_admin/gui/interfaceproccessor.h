/* 
 * File:   NSLoaderThread.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 22 Декабрь 2009 г., 22:19
 */

#ifndef _NSLOADERTHREAD_H
#define	_NSLOADERTHREAD_H



#include <kernel/constdef.h>
#include <kernel/systemutil.h>

#include <admin/propertymanager.h>
#include <admin/entitywraper.h>

#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMainWindow>
//#include <QCustomEvent>

#include "interfacetransaction.h"
#include "uiwidgetitem.h"


namespace dvnci {
    namespace admin {

        class transactionmain_proccess;
        class transactionview_proccess;

        typedef callable_shared_ptr<transactionmain_proccess> callable_transactionmain;
        typedef callable_shared_ptr<transactionview_proccess> callable_transactionview;

        class transactionmain_proccess : public executable {
        public:

            transactionmain_proccess(QWidget *widget) : executable() {
                targetWidget = widget;}
            virtual bool operator()();
            void addtransaction(basetransaction_ptr transact);
            bool gettransaction(basetransaction_ptr& transact);
        protected:

            virtual bool initialize() {
                return true;}

            virtual bool uninitialize() {
                return true;}
            void         invoke(basetransaction_ptr& transact);
        private:
            QWidget*                      targetWidget;
            boost::mutex                  mtx;
            basetransaction_ptr_vect      transactions;
            propertymanager propman;} ;

        class transactionview_proccess : public executable {
        public:

            transactionview_proccess(QWidget *widget) : executable(), needstop(false) {
                targetWidget = widget;}
            virtual bool operator()();
            void addtransaction(viewtransaction_ptr transact);
            bool gettransaction(viewtransaction_ptr& transact);
        protected:

            virtual bool initialize() {
                return true;}

            virtual bool uninitialize() {
                return true;}
            void         invoke(viewtransaction_ptr& transact);
        private:
            QWidget*                      targetWidget;
            boost::mutex                  mtx;
            viewtransaction_ptr_vect      transactions;
            bool                          needstop;} ;}}


#endif	/* _NSLOADERTHREAD_H */

