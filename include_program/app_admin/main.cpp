/*
 * File:   main.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 29 Декабрь 2009 г., 15:18
 */

#include <QtGui/QApplication>
#include "gui/form_admin.h"
#include <kernel/constdef.h>
#include <kernel/serviceapp.h>
#if defined(_DVN_LIN_)
#include <sys/types.h> 
#include <sys/stat.h>
#endif 

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);
#if defined(_DVN_LIN_)
    umask(0);        
#endif            
    QApplication app(argc, argv);
    using namespace dvnci;
    using namespace dvnci::admin;
    appargumentparser(argc, argv);
    form_admin form;
    form.showMaximized();
    return app.exec();}
