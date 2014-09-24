/****************************************************************************
** Meta object code from reading C++ file 'form_setvalue.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include_program/app_admin/gui/form_setvalue.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'form_setvalue.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_dvnci__admin__form_setvalue_t {
    QByteArrayData data[10];
    char stringdata[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dvnci__admin__form_setvalue_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dvnci__admin__form_setvalue_t qt_meta_stringdata_dvnci__admin__form_setvalue = {
    {
QT_MOC_LITERAL(0, 0, 27),
QT_MOC_LITERAL(1, 28, 15),
QT_MOC_LITERAL(2, 44, 0),
QT_MOC_LITERAL(3, 45, 19),
QT_MOC_LITERAL(4, 65, 20),
QT_MOC_LITERAL(5, 86, 19),
QT_MOC_LITERAL(6, 106, 18),
QT_MOC_LITERAL(7, 125, 18),
QT_MOC_LITERAL(8, 144, 17),
QT_MOC_LITERAL(9, 162, 19)
    },
    "dvnci::admin::form_setvalue\0proc_btnOkclick\0"
    "\0proc_btnCancelclick\0proc_rbsetvalueclick\0"
    "proc_rbcommandclick\0proc_rbincvntclick\0"
    "proc_rbdeccntclick\0proc_rbvalidclick\0"
    "proc_rbinvalidclick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dvnci__admin__form_setvalue[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void dvnci::admin::form_setvalue::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        form_setvalue *_t = static_cast<form_setvalue *>(_o);
        switch (_id) {
        case 0: _t->proc_btnOkclick(); break;
        case 1: _t->proc_btnCancelclick(); break;
        case 2: _t->proc_rbsetvalueclick(); break;
        case 3: _t->proc_rbcommandclick(); break;
        case 4: _t->proc_rbincvntclick(); break;
        case 5: _t->proc_rbdeccntclick(); break;
        case 6: _t->proc_rbvalidclick(); break;
        case 7: _t->proc_rbinvalidclick(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject dvnci::admin::form_setvalue::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dvnci__admin__form_setvalue.data,
      qt_meta_data_dvnci__admin__form_setvalue,  qt_static_metacall, 0, 0}
};


const QMetaObject *dvnci::admin::form_setvalue::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dvnci::admin::form_setvalue::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dvnci__admin__form_setvalue.stringdata))
        return static_cast<void*>(const_cast< form_setvalue*>(this));
    return QDialog::qt_metacast(_clname);
}

int dvnci::admin::form_setvalue::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
