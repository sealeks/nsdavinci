/****************************************************************************
** Meta object code from reading C++ file 'form_filter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include_program/app_admin/gui/form_filter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'form_filter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_dvnci__admin__form_filter_t {
    QByteArrayData data[16];
    char stringdata[264];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dvnci__admin__form_filter_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dvnci__admin__form_filter_t qt_meta_stringdata_dvnci__admin__form_filter = {
    {
QT_MOC_LITERAL(0, 0, 25),
QT_MOC_LITERAL(1, 26, 19),
QT_MOC_LITERAL(2, 46, 0),
QT_MOC_LITERAL(3, 47, 4),
QT_MOC_LITERAL(4, 52, 22),
QT_MOC_LITERAL(5, 75, 19),
QT_MOC_LITERAL(6, 95, 14),
QT_MOC_LITERAL(7, 110, 5),
QT_MOC_LITERAL(8, 116, 15),
QT_MOC_LITERAL(9, 132, 19),
QT_MOC_LITERAL(10, 152, 18),
QT_MOC_LITERAL(11, 171, 21),
QT_MOC_LITERAL(12, 193, 16),
QT_MOC_LITERAL(13, 210, 4),
QT_MOC_LITERAL(14, 215, 25),
QT_MOC_LITERAL(15, 241, 22)
    },
    "dvnci::admin::form_filter\0proc_lineEditbyName\0"
    "\0text\0proc_lineEditbyComment\0"
    "proc_lineEditbyBind\0proc_setnodetp\0"
    "index\0proc_btnOkclick\0proc_btnCancelclick\0"
    "proc_btnClearclick\0proc_itemGroupChanged\0"
    "QListWidgetItem*\0item\0proc_itemGroupTypeChanged\0"
    "proc_itemRtTypeChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dvnci__admin__form_filter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x0a /* Public */,
       4,    1,   67,    2, 0x0a /* Public */,
       5,    1,   70,    2, 0x0a /* Public */,
       6,    1,   73,    2, 0x0a /* Public */,
       8,    0,   76,    2, 0x0a /* Public */,
       9,    0,   77,    2, 0x0a /* Public */,
      10,    0,   78,    2, 0x0a /* Public */,
      11,    1,   79,    2, 0x0a /* Public */,
      14,    1,   82,    2, 0x0a /* Public */,
      15,    1,   85,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,

       0        // eod
};

void dvnci::admin::form_filter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        form_filter *_t = static_cast<form_filter *>(_o);
        switch (_id) {
        case 0: _t->proc_lineEditbyName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->proc_lineEditbyComment((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->proc_lineEditbyBind((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->proc_setnodetp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->proc_btnOkclick(); break;
        case 5: _t->proc_btnCancelclick(); break;
        case 6: _t->proc_btnClearclick(); break;
        case 7: _t->proc_itemGroupChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 8: _t->proc_itemGroupTypeChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 9: _t->proc_itemRtTypeChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject dvnci::admin::form_filter::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dvnci__admin__form_filter.data,
      qt_meta_data_dvnci__admin__form_filter,  qt_static_metacall, 0, 0}
};


const QMetaObject *dvnci::admin::form_filter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dvnci::admin::form_filter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dvnci__admin__form_filter.stringdata))
        return static_cast<void*>(const_cast< form_filter*>(this));
    return QDialog::qt_metacast(_clname);
}

int dvnci::admin::form_filter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
