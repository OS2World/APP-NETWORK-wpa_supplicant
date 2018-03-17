/****************************************************************************
** Meta object code from reading C++ file 'wpagui.h'
**
** Created: Fri Mar 9 15:56:59 2018
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "wpagui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wpagui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WpaGuiApp[] = {

 // content:
       5,       // revision
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

static const char qt_meta_stringdata_WpaGuiApp[] = {
    "WpaGuiApp\0"
};

const QMetaObject WpaGuiApp::staticMetaObject = {
    { &QApplication::staticMetaObject, qt_meta_stringdata_WpaGuiApp,
      qt_meta_data_WpaGuiApp, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WpaGuiApp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WpaGuiApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WpaGuiApp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WpaGuiApp))
        return static_cast<void*>(const_cast< WpaGuiApp*>(this));
    return QApplication::qt_metacast(_clname);
}

int WpaGuiApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QApplication::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_WpaGui[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      45,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,
      21,    7,    7,    7, 0x0a,
      36,    7,    7,    7, 0x0a,
      53,    7,    7,    7, 0x0a,
      65,    7,    7,    7, 0x0a,
      80,    7,    7,    7, 0x0a,
      92,    7,    7,    7, 0x0a,
     105,    7,    7,    7, 0x0a,
     112,    7,    7,    7, 0x0a,
     127,    7,    7,    7, 0x0a,
     134,    7,    7,    7, 0x0a,
     158,  154,    7,    7, 0x0a,
     180,  176,    7,    7, 0x0a,
     208,    7,    7,    7, 0x0a,
     222,    7,    7,    7, 0x0a,
     237,  233,    7,    7, 0x0a,
     260,    7,    7,    7, 0x0a,
     282,    7,    7,    7, 0x0a,
     302,    7,    7,    7, 0x0a,
     326,    7,    7,    7, 0x0a,
     348,    7,    7,    7, 0x0a,
     361,    7,    7,    7, 0x0a,
     381,    7,    7,    7, 0x0a,
     402,    7,    7,    7, 0x0a,
     422,    7,    7,    7, 0x0a,
     435,  233,    7,    7, 0x0a,
     458,    7,    7,    7, 0x0a,
     488,    7,    7,    7, 0x0a,
     514,    7,    7,    7, 0x0a,
     554,  541,    7,    7, 0x0a,
     612,    7,    7,    7, 0x0a,
     634,  629,    7,    7, 0x0a,
     663,  154,    7,    7, 0x0a,
     711,  696,  690,    7, 0x0a,
     745,    7,    7,    7, 0x0a,
     757,    7,    7,    7, 0x0a,
     777,  771,    7,    7, 0x0a,
     793,    7,    7,    7, 0x0a,
     802,    7,    7,    7, 0x0a,
     824,  819,    7,    7, 0x0a,
     849,    7,    7,    7, 0x0a,
     860,    7,    7,    7, 0x0a,
     875,    7,    7,    7, 0x09,
     896,  892,    7,    7, 0x09,
     951,  945,    7,    7, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_WpaGui[] = {
    "WpaGui\0\0parse_argv()\0updateStatus()\0"
    "updateNetworks()\0helpIndex()\0"
    "helpContents()\0helpAbout()\0disconnect()\0"
    "scan()\0eventHistory()\0ping()\0"
    "signalMeterUpdate()\0msg\0processMsg(char*)\0"
    "req\0processCtrlReq(const char*)\0"
    "receiveMsgs()\0connectB()\0sel\0"
    "selectNetwork(QString)\0editSelectedNetwork()\0"
    "editListedNetwork()\0removeSelectedNetwork()\0"
    "removeListedNetwork()\0addNetwork()\0"
    "enableAllNetworks()\0disableAllNetworks()\0"
    "removeAllNetworks()\0saveConfig()\0"
    "selectAdapter(QString)\0"
    "updateNetworkDisabledStatus()\0"
    "enableListedNetwork(bool)\0"
    "disableListedNetwork(bool)\0type,sec,msg\0"
    "showTrayMessage(QSystemTrayIcon::MessageIcon,int,QString)\0"
    "showTrayStatus()\0type\0"
    "updateTrayIcon(TrayIconType)\0"
    "updateTrayToolTip(QString)\0QIcon\0"
    "names,fallback\0loadThemedIcon(QStringList,QIcon)\0"
    "wpsDialog()\0peersDialog()\0index\0"
    "tabChanged(int)\0wpsPbc()\0wpsGeneratePin()\0"
    "text\0wpsApPinChanged(QString)\0wpsApPin()\0"
    "addInterface()\0languageChange()\0how\0"
    "trayActivated(QSystemTrayIcon::ActivationReason)\0"
    "event\0closeEvent(QCloseEvent*)\0"
};

const QMetaObject WpaGui::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_WpaGui,
      qt_meta_data_WpaGui, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WpaGui::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WpaGui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WpaGui::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WpaGui))
        return static_cast<void*>(const_cast< WpaGui*>(this));
    if (!strcmp(_clname, "Ui::WpaGui"))
        return static_cast< Ui::WpaGui*>(const_cast< WpaGui*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int WpaGui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: parse_argv(); break;
        case 1: updateStatus(); break;
        case 2: updateNetworks(); break;
        case 3: helpIndex(); break;
        case 4: helpContents(); break;
        case 5: helpAbout(); break;
        case 6: disconnect(); break;
        case 7: scan(); break;
        case 8: eventHistory(); break;
        case 9: ping(); break;
        case 10: signalMeterUpdate(); break;
        case 11: processMsg((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 12: processCtrlReq((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 13: receiveMsgs(); break;
        case 14: connectB(); break;
        case 15: selectNetwork((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: editSelectedNetwork(); break;
        case 17: editListedNetwork(); break;
        case 18: removeSelectedNetwork(); break;
        case 19: removeListedNetwork(); break;
        case 20: addNetwork(); break;
        case 21: enableAllNetworks(); break;
        case 22: disableAllNetworks(); break;
        case 23: removeAllNetworks(); break;
        case 24: saveConfig(); break;
        case 25: selectAdapter((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 26: updateNetworkDisabledStatus(); break;
        case 27: enableListedNetwork((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: disableListedNetwork((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: showTrayMessage((*reinterpret_cast< QSystemTrayIcon::MessageIcon(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 30: showTrayStatus(); break;
        case 31: updateTrayIcon((*reinterpret_cast< TrayIconType(*)>(_a[1]))); break;
        case 32: updateTrayToolTip((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 33: { QIcon _r = loadThemedIcon((*reinterpret_cast< const QStringList(*)>(_a[1])),(*reinterpret_cast< const QIcon(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QIcon*>(_a[0]) = _r; }  break;
        case 34: wpsDialog(); break;
        case 35: peersDialog(); break;
        case 36: tabChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: wpsPbc(); break;
        case 38: wpsGeneratePin(); break;
        case 39: wpsApPinChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 40: wpsApPin(); break;
        case 41: addInterface(); break;
        case 42: languageChange(); break;
        case 43: trayActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 44: closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 45;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
