/****************************************************************************
** Meta object code from reading C++ file 'form_setvalue.h'
**
** Created: Mon 20. Jun 18:30:01 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include_program/app_admin/gui/form_setvalue.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'form_setvalue.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_dvnci__admin__form_setvalue[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   28,   28,   28, 0x0a,
      47,   28,   28,   28, 0x0a,
      69,   28,   28,   28, 0x0a,
      92,   28,   28,   28, 0x0a,
     114,   28,   28,   28, 0x0a,
     135,   28,   28,   28, 0x0a,
     156,   28,   28,   28, 0x0a,
     176,   28,   28,   28, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dvnci__admin__form_setvalue[] = {
    "dvnci::admin::form_setvalue\0\0"
    "proc_btnOkclick()\0proc_btnCancelclick()\0"
    "proc_rbsetvalueclick()\0proc_rbcommandclick()\0"
    "proc_rbincvntclick()\0proc_rbdeccntclick()\0"
    "proc_rbvalidclick()\0proc_rbinvalidclick()\0"
};

const QMetaObject dvnci::admin::form_setvalue::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dvnci__admin__form_setvalue,
      qt_meta_data_dvnci__admin__form_setvalue, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &dvnci::admin::form_setvalue::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *dvnci::admin::form_setvalue::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *dvnci::admin::form_setvalue::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dvnci__admin__form_setvalue))
        return static_cast<void*>(const_cast< form_setvalue*>(this));
    return QDialog::qt_metacast(_clname);
}

int dvnci::admin::form_setvalue::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: proc_btnOkclick(); break;
        case 1: proc_btnCancelclick(); break;
        case 2: proc_rbsetvalueclick(); break;
        case 3: proc_rbcommandclick(); break;
        case 4: proc_rbincvntclick(); break;
        case 5: proc_rbdeccntclick(); break;
        case 6: proc_rbvalidclick(); break;
        case 7: proc_rbinvalidclick(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
