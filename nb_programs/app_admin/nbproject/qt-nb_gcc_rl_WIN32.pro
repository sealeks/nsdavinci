# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = ../../bin/nb_gcc_rl_WIN32
TARGET = app_admin
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui opengl xml
SOURCES += ../../include_program/app_admin/gui/RU_dict.cpp ../../include_program/app_admin/gui/admin_configer.cpp ../../include_program/app_admin/gui/form_addserver.cpp ../../include_program/app_admin/gui/form_admin.cpp ../../include_program/app_admin/gui/form_esdfilter.cpp ../../include_program/app_admin/gui/form_filter.cpp ../../include_program/app_admin/gui/form_getstring.cpp ../../include_program/app_admin/gui/form_import.cpp ../../include_program/app_admin/gui/form_setvalue.cpp ../../include_program/app_admin/gui/interfaceproccessor.cpp ../../include_program/app_admin/gui/uiuitil.cpp ../../include_program/app_admin/gui/uiwidgetitem.cpp ../../include_program/app_admin/gui/viewmodels.cpp ../../include_program/app_admin/main.cpp
HEADERS += ../../include_program/app_admin/gui/RU_dict.h ../../include_program/app_admin/gui/admin_configer.h ../../include_program/app_admin/gui/form_addserver.h ../../include_program/app_admin/gui/form_admin.h ../../include_program/app_admin/gui/form_esdfilter.h ../../include_program/app_admin/gui/form_filter.h ../../include_program/app_admin/gui/form_getstring.h ../../include_program/app_admin/gui/form_import.h ../../include_program/app_admin/gui/form_setvalue.h ../../include_program/app_admin/gui/interfaceproccessor.h ../../include_program/app_admin/gui/interfacetransaction.h ../../include_program/app_admin/gui/uiuitil.h ../../include_program/app_admin/gui/uiwidgetitem.h ../../include_program/app_admin/gui/viewmodels.h
FORMS += ../../include_program/app_admin/gui/form_addserver.ui ../../include_program/app_admin/gui/form_admin.ui ../../include_program/app_admin/gui/form_esdfilter.ui ../../include_program/app_admin/gui/form_filter.ui ../../include_program/app_admin/gui/form_getstring.ui ../../include_program/app_admin/gui/form_import.ui ../../include_program/app_admin/gui/form_setvalue.ui
RESOURCES += ../../include_program/app_admin/resourse/mainresource.qrc
TRANSLATIONS +=
OBJECTS_DIR = build/nb_gcc_rl_WIN32/MinGW-Windows
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = i686-w64-mingw32-gcc-4.8.0
DEFINES += NS_ADMIN_RELEASE_BAG _WIN32_WINNT=0x0501 
INCLUDEPATH += ../../include ${BOOST_DIR} 
LIBS += F:/Project/davinci/nb_programs/libnsadmin/../../lib/nb_gcc_rl_WIN32/libnsadmin.a F:/Project/davinci/nb_programs/libnskernel/../../lib/nb_gcc_rl_WIN32/libnskernel.a F:/Project/davinci/nb_programs/libmeta/../../lib/nb_gcc_rl_WIN32/libmeta.a -lole32 -lwsock32 -loleaut32 -lws2_32 F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_atomic.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_chrono.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_coroutine.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_date_time.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_exception.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_filesystem.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_iostreams.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_locale.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_log.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_log_setup.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_prg_exec_monitor.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_program_options.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_random.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_regex.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_serialization.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_signals.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_system.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_test_exec_monitor.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_thread.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_timer.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_unit_test_framework.a F:/Project/davinci/lib/boost/nb_gcc_rl_WIN32/libboost_wserialization.a  
