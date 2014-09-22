# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = ../../bin/nb_gcc_db_LIN64
TARGET = app_admin
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui opengl xml
SOURCES += ../../include_program/app_admin/gui/RU_dict.cpp ../../include_program/app_admin/gui/admin_configer.cpp ../../include_program/app_admin/gui/form_addserver.cpp ../../include_program/app_admin/gui/form_admin.cpp ../../include_program/app_admin/gui/form_esdfilter.cpp ../../include_program/app_admin/gui/form_filter.cpp ../../include_program/app_admin/gui/form_getstring.cpp ../../include_program/app_admin/gui/form_import.cpp ../../include_program/app_admin/gui/form_setvalue.cpp ../../include_program/app_admin/gui/interfaceproccessor.cpp ../../include_program/app_admin/gui/uiuitil.cpp ../../include_program/app_admin/gui/uiwidgetitem.cpp ../../include_program/app_admin/gui/viewmodels.cpp ../../include_program/app_admin/main.cpp
HEADERS += ../../include_program/app_admin/gui/RU_dict.h ../../include_program/app_admin/gui/admin_configer.h ../../include_program/app_admin/gui/form_addserver.h ../../include_program/app_admin/gui/form_admin.h ../../include_program/app_admin/gui/form_esdfilter.h ../../include_program/app_admin/gui/form_filter.h ../../include_program/app_admin/gui/form_getstring.h ../../include_program/app_admin/gui/form_import.h ../../include_program/app_admin/gui/form_setvalue.h ../../include_program/app_admin/gui/interfaceproccessor.h ../../include_program/app_admin/gui/interfacetransaction.h ../../include_program/app_admin/gui/uiuitil.h ../../include_program/app_admin/gui/uiwidgetitem.h ../../include_program/app_admin/gui/viewmodels.h
FORMS += ../../include_program/app_admin/gui/form_addserver.ui ../../include_program/app_admin/gui/form_admin.ui ../../include_program/app_admin/gui/form_esdfilter.ui ../../include_program/app_admin/gui/form_filter.ui ../../include_program/app_admin/gui/form_getstring.ui ../../include_program/app_admin/gui/form_import.ui ../../include_program/app_admin/gui/form_setvalue.ui
RESOURCES += ../../include_program/app_admin/resourse/mainresource.qrc
TRANSLATIONS +=
OBJECTS_DIR = build/nb_gcc_db_LIN64/GNU-Windows
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += DVNCI_DEDUG 
INCLUDEPATH += ../../include ${BOOST_DIR} 
LIBS += ../../lib/nb_gcc_db_LIN64/libnsadmin.a ../../lib/nb_gcc_db_LIN64/libnskernel.a ../../lib/nb_gcc_db_LIN64/libnsadmin.a ../../lib/nb_gcc_db_LIN64/libmeta.a ../../lib/boost/nb_gcc_db_LIN64/libboost_date_time.a ../../lib/boost/nb_gcc_db_LIN64/libboost_filesystem.a ../../lib/boost/nb_gcc_db_LIN64/libboost_prg_exec_monitor.a ../../lib/boost/nb_gcc_db_LIN64/libboost_program_options.a ../../lib/boost/nb_gcc_db_LIN64/libboost_random.a ../../lib/boost/nb_gcc_db_LIN64/libboost_regex.a ../../lib/boost/nb_gcc_db_LIN64/libboost_serialization.a ../../lib/boost/nb_gcc_db_LIN64/libboost_signals.a ../../lib/boost/nb_gcc_db_LIN64/libboost_system.a ../../lib/boost/nb_gcc_db_LIN64/libboost_test_exec_monitor.a ../../lib/boost/nb_gcc_db_LIN64/libboost_thread.a ../../lib/boost/nb_gcc_db_LIN64/libboost_chrono.a ../../lib/boost/nb_gcc_db_LIN64/libboost_unit_test_framework.a ../../lib/boost/nb_gcc_db_LIN64/libboost_wserialization.a -lrt  
