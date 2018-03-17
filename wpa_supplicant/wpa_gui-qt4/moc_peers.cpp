/****************************************************************************
** Meta object code from reading C++ file 'peers.h'
**
** Created: Fri Mar 9 15:57:24 2018
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "peers.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'peers.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Peers[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,    7,    6,    6, 0x0a,
      32,    6,    6,    6, 0x0a,
      44,    6,    6,    6, 0x0a,
      58,    6,    6,    6, 0x0a,
      76,    6,    6,    6, 0x0a,
      90,    6,    6,    6, 0x0a,
     106,    6,    6,    6, 0x0a,
     121,    6,    6,    6, 0x0a,
     138,    6,    6,    6, 0x0a,
     160,    6,    6,    6, 0x0a,
     183,    6,    6,    6, 0x0a,
     201,    6,    6,    6, 0x0a,
     219,    6,    6,    6, 0x0a,
     238,    6,    6,    6, 0x0a,
     260,    6,    6,    6, 0x0a,
     285,    6,    6,    6, 0x0a,
     305,    6,    6,    6, 0x0a,
     318,    6,    6,    6, 0x0a,
     332,    6,    6,    6, 0x0a,
     346,    6,    6,    6, 0x0a,
     372,    6,    6,    6, 0x0a,
     399,    6,    6,    6, 0x0a,
     416,    6,    6,    6, 0x0a,
     433,    6,    6,    6, 0x09,
     456,  450,    6,    6, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_Peers[] = {
    "Peers\0\0pos\0context_menu(QPoint)\0"
    "enter_pin()\0connect_pbc()\0learn_ap_config()\0"
    "ctx_refresh()\0ctx_p2p_start()\0"
    "ctx_p2p_stop()\0ctx_p2p_listen()\0"
    "ctx_p2p_start_group()\0ctx_p2p_remove_group()\0"
    "ctx_p2p_connect()\0ctx_p2p_req_pin()\0"
    "ctx_p2p_show_pin()\0ctx_p2p_display_pin()\0"
    "ctx_p2p_display_pin_pd()\0ctx_p2p_enter_pin()\0"
    "properties()\0ctx_hide_ap()\0ctx_show_ap()\0"
    "ctx_p2p_show_passphrase()\0"
    "ctx_p2p_start_persistent()\0ctx_p2p_invite()\0"
    "ctx_p2p_delete()\0languageChange()\0"
    "event\0closeEvent(QCloseEvent*)\0"
};

const QMetaObject Peers::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Peers,
      qt_meta_data_Peers, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Peers::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Peers::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Peers::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Peers))
        return static_cast<void*>(const_cast< Peers*>(this));
    if (!strcmp(_clname, "Ui::Peers"))
        return static_cast< Ui::Peers*>(const_cast< Peers*>(this));
    return QDialog::qt_metacast(_clname);
}

int Peers::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: context_menu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: enter_pin(); break;
        case 2: connect_pbc(); break;
        case 3: learn_ap_config(); break;
        case 4: ctx_refresh(); break;
        case 5: ctx_p2p_start(); break;
        case 6: ctx_p2p_stop(); break;
        case 7: ctx_p2p_listen(); break;
        case 8: ctx_p2p_start_group(); break;
        case 9: ctx_p2p_remove_group(); break;
        case 10: ctx_p2p_connect(); break;
        case 11: ctx_p2p_req_pin(); break;
        case 12: ctx_p2p_show_pin(); break;
        case 13: ctx_p2p_display_pin(); break;
        case 14: ctx_p2p_display_pin_pd(); break;
        case 15: ctx_p2p_enter_pin(); break;
        case 16: properties(); break;
        case 17: ctx_hide_ap(); break;
        case 18: ctx_show_ap(); break;
        case 19: ctx_p2p_show_passphrase(); break;
        case 20: ctx_p2p_start_persistent(); break;
        case 21: ctx_p2p_invite(); break;
        case 22: ctx_p2p_delete(); break;
        case 23: languageChange(); break;
        case 24: closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 25;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
