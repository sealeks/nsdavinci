/****************************************************************************
** Meta object code from reading C++ file 'form_admin.h'
**
** Created: Wed 29. Jun 16:20:24 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include_program/app_admin/gui/form_admin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'form_admin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_dvnci__admin__form_admin[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      35,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      35,   26,   25,   25, 0x0a,
      72,   25,   25,   25, 0x0a,
      90,   25,   25,   25, 0x0a,
     123,  117,   25,   25, 0x0a,
     174,  156,   25,   25, 0x0a,
     209,  203,   25,   25, 0x0a,
     235,  231,   25,   25, 0x0a,
     260,   25,   25,   25, 0x0a,
     276,   25,   25,   25, 0x0a,
     290,   25,   25,   25, 0x0a,
     304,   25,   25,   25, 0x0a,
     324,   25,   25,   25, 0x0a,
     343,   25,   25,   25, 0x0a,
     360,   25,   25,   25, 0x0a,
     380,   25,   25,   25, 0x0a,
     401,   25,   25,   25, 0x0a,
     425,   25,   25,   25, 0x0a,
     439,   25,   25,   25, 0x0a,
     453,   25,   25,   25, 0x0a,
     470,   25,   25,   25, 0x0a,
     496,  489,   25,   25, 0x0a,
     523,  489,   25,   25, 0x0a,
     551,   25,   25,   25, 0x0a,
     567,   25,   25,   25, 0x0a,
     580,   25,   25,   25, 0x0a,
     599,   25,   25,   25, 0x0a,
     618,   25,   25,   25, 0x0a,
     637,   25,   25,   25, 0x0a,
     658,   25,   25,   25, 0x0a,
     670,   25,   25,   25, 0x0a,
     690,   25,   25,   25, 0x0a,
     709,   25,   25,   25, 0x0a,
     726,   25,   25,   25, 0x0a,
     750,  744,   25,   25, 0x0a,
     779,   25,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_dvnci__admin__form_admin[] = {
    "dvnci::admin::form_admin\0\0item,val\0"
    "proc_treeclick(QTreeWidgetItem*,int)\0"
    "proc_mergeclick()\0proc_changeviewkindclick()\0"
    "item_\0proc_itchange(QTableWidgetItem*)\0"
    "oldCount,newCount\0proc_rowcountchange(int,int)\0"
    "value\0proc_valuechange(int)\0val\0"
    "proc_treecontext(QPoint)\0proc_unmapprj()\0"
    "proc_mapprj()\0proc_newprj()\0"
    "proc_createentety()\0proc_eraseentety()\0"
    "proc_addserver()\0proc_removeserver()\0"
    "proc_connectserver()\0proc_disconnectserver()\0"
    "proc_import()\0proc_export()\0"
    "proc_setfilter()\0proc_resetfilter()\0"
    "action\0proc_changegroup(QAction*)\0"
    "proc_changeagroup(QAction*)\0proc_logclick()\0"
    "proc_error()\0proc_incallcount()\0"
    "proc_decallcount()\0proc_setallvalid()\0"
    "proc_setallinvalid()\0proc_kvit()\0"
    "proc_startservice()\0proc_stopservice()\0"
    "proc_groupkvit()\0proc_agroupkvit()\0"
    "index\0proc_viewdouble(QModelIndex)\0"
    "proc_duplicate()\0"
};

const QMetaObject dvnci::admin::form_admin::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_dvnci__admin__form_admin,
      qt_meta_data_dvnci__admin__form_admin, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &dvnci::admin::form_admin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *dvnci::admin::form_admin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *dvnci::admin::form_admin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dvnci__admin__form_admin))
        return static_cast<void*>(const_cast< form_admin*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int dvnci::admin::form_admin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: proc_treeclick((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: proc_mergeclick(); break;
        case 2: proc_changeviewkindclick(); break;
        case 3: proc_itchange((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 4: proc_rowcountchange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: proc_valuechange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: proc_treecontext((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 7: proc_unmapprj(); break;
        case 8: proc_mapprj(); break;
        case 9: proc_newprj(); break;
        case 10: proc_createentety(); break;
        case 11: proc_eraseentety(); break;
        case 12: proc_addserver(); break;
        case 13: proc_removeserver(); break;
        case 14: proc_connectserver(); break;
        case 15: proc_disconnectserver(); break;
        case 16: proc_import(); break;
        case 17: proc_export(); break;
        case 18: proc_setfilter(); break;
        case 19: proc_resetfilter(); break;
        case 20: proc_changegroup((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 21: proc_changeagroup((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 22: proc_logclick(); break;
        case 23: proc_error(); break;
        case 24: proc_incallcount(); break;
        case 25: proc_decallcount(); break;
        case 26: proc_setallvalid(); break;
        case 27: proc_setallinvalid(); break;
        case 28: proc_kvit(); break;
        case 29: proc_startservice(); break;
        case 30: proc_stopservice(); break;
        case 31: proc_groupkvit(); break;
        case 32: proc_agroupkvit(); break;
        case 33: proc_viewdouble((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 34: proc_duplicate(); break;
        default: ;
        }
        _id -= 35;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
