# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = ../../bin/WIN32
TARGET = app_admin
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
QT = core gui xml
SOURCES += ../../include_program/app_admin/gui/NSTreeFilterForm.cpp ../../include_program/app_admin/gui/MainWindow.cpp ../../include_program/app_admin/gui/RU_dict.cpp ../../include_program/app_admin/gui/appadminconfigurator.cpp ../../include_program/app_admin/main.cpp ../../include_program/app_admin/gui/main_translate.cpp ../../include_program/app_admin/gui/StringTranslator.cpp ../../include_program/app_admin/gui/MemBaseModel.cpp ../../include_program/app_admin/gui/AddServerForm.cpp ../../include_program/app_admin/gui/uiwidgetitem.cpp ../../include_program/app_admin/gui/ViewBaseModel.cpp ../../include_program/app_admin/gui/AbstractRtBaseModel.cpp ../../include_program/app_admin/gui/esdfilterForm.cpp ../../include_program/app_admin/gui/TableDelegate.cpp ../../include_program/app_admin/gui/setvalueform.cpp ../../include_program/app_admin/gui/getstringForm.cpp ../../include_program/app_admin/gui/ImportForm.cpp ../../include_program/app_admin/gui/interfaceproccessor.cpp
HEADERS += ../../include_program/app_admin/gui/appadminconfigurator.h ../../include_program/app_admin/gui/interfacetransaction.h ../../include_program/app_admin/gui/uiwidgetitem.h ../../include_program/app_admin/gui/TableDelegate.h ../../include_program/app_admin/gui/ViewBaseModel.h ../../include_program/app_admin/gui/StringTranslator.h ../../include_program/app_admin/gui/setvalueform.h ../../include_program/app_admin/gui/RU_dict.h ../../include_program/app_admin/gui/MemBaseModel.h ../../include_program/app_admin/gui/interfaceproccessor.h ../../include_program/app_admin/gui/getstringForm.h ../../include_program/app_admin/gui/AbstractRtBaseModel.h ../../include_program/app_admin/gui/main_translate.h ../../include_program/app_admin/gui/MainWindow.h ../../include_program/app_admin/gui/NSTreeFilterForm.h ../../include_program/app_admin/gui/esdfilterForm.h ../../include_program/app_admin/gui/AddServerForm.h ../../include_program/app_admin/gui/ImportForm.h
FORMS +=
RESOURCES += resourse/mainresource.qrc
TRANSLATIONS +=
OBJECTS_DIR = build/WIN32/MinGW-Windows
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc.exe
QMAKE_CXX = g++.exe
DEFINES += 
INCLUDEPATH += ../../include 
LIBS += ../../lib/WIN32/lib_nskernel.a ../../lib/WIN32/lib_nsadmininterface.a ../../lib/WIN32/lib_nskernel.a ../../lib/WIN32/plagixml.a E:/Project/davinci/lib/WIN32/boost/debug/libboost_system-mgw44-mt-d-1_42.lib E:/Project/davinci/lib/WIN32/boost/debug/libboost_date_time-mgw44-mt-d-1_42.lib E:/Project/davinci/lib/WIN32/boost/debug/libboost_filesystem-mgw44-mt-d-1_42.lib E:/Project/davinci/lib/WIN32/boost/debug/libboost_iostreams-mgw44-mt-d-1_42.lib E:/Project/davinci/lib/WIN32/boost/debug/libboost_program_options-mgw44-mt-d-1_42.lib E:/Project/davinci/lib/WIN32/boost/debug/libboost_regex-mgw44-mt-d-1_42.lib E:/Project/davinci/lib/WIN32/boost/debug/libboost_serialization-mgw44-mt-d-1_42.lib E:/Project/davinci/lib/WIN32/boost/debug/libboost_thread-mgw44-mt-d-1_42.lib -lws2_32 -lwsock32  
