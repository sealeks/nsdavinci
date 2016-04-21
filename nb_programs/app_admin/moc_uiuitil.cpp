/****************************************************************************
** Meta object code from reading C++ file 'uiuitil.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include_program/app_admin/gui/uiuitil.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uiuitil.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_dvnci__admin__uitabdelegate_t {
    QByteArrayData data[1];
    char stringdata[28];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dvnci__admin__uitabdelegate_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dvnci__admin__uitabdelegate_t qt_meta_stringdata_dvnci__admin__uitabdelegate = {
    {
QT_MOC_LITERAL(0, 0, 27)
    },
    "dvnci::admin::uitabdelegate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dvnci__admin__uitabdelegate[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void dvnci::admin::uitabdelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject dvnci::admin::uitabdelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_dvnci__admin__uitabdelegate.data,
      qt_meta_data_dvnci__admin__uitabdelegate,  qt_static_metacall, 0, 0}
};


const QMetaObject *dvnci::admin::uitabdelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dvnci::admin::uitabdelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dvnci__admin__uitabdelegate.stringdata))
        return static_cast<void*>(const_cast< uitabdelegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int dvnci::admin::uitabdelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
