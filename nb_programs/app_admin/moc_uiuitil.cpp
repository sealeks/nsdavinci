/****************************************************************************
** Meta object code from reading C++ file 'uiuitil.h'
**
** Created: Wed 10. Oct 20:42:37 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include_program/app_admin/gui/uiuitil.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uiuitil.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_dvnci__admin__uitabdelegate[] = {

 // content:
       4,       // revision
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

static const char qt_meta_stringdata_dvnci__admin__uitabdelegate[] = {
    "dvnci::admin::uitabdelegate\0"
};

const QMetaObject dvnci::admin::uitabdelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_dvnci__admin__uitabdelegate,
      qt_meta_data_dvnci__admin__uitabdelegate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &dvnci::admin::uitabdelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *dvnci::admin::uitabdelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *dvnci::admin::uitabdelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dvnci__admin__uitabdelegate))
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
