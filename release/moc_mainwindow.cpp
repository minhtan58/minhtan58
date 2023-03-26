/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[33];
    char stringdata0[499];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "switchContent"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "value"
QT_MOC_LITERAL(4, 32, 24), // "saveTransmissionSettings"
QT_MOC_LITERAL(5, 57, 12), // "jsonSettings"
QT_MOC_LITERAL(6, 70, 26), // "importTransmissionSettings"
QT_MOC_LITERAL(7, 97, 3), // "url"
QT_MOC_LITERAL(8, 101, 26), // "exportTransmissionSettings"
QT_MOC_LITERAL(9, 128, 18), // "saveSystemSettings"
QT_MOC_LITERAL(10, 147, 20), // "importSystemSettings"
QT_MOC_LITERAL(11, 168, 20), // "exportSystemSettings"
QT_MOC_LITERAL(12, 189, 24), // "saveAnalogSensorSettings"
QT_MOC_LITERAL(13, 214, 24), // "loadAnalogSensorSettings"
QT_MOC_LITERAL(14, 239, 10), // "sensorName"
QT_MOC_LITERAL(15, 250, 25), // "saveDigitalSensorSettings"
QT_MOC_LITERAL(16, 276, 25), // "loadDigitalSensorSettings"
QT_MOC_LITERAL(17, 302, 24), // "saveSerialSensorSettings"
QT_MOC_LITERAL(18, 327, 24), // "loadSerialSensorSettings"
QT_MOC_LITERAL(19, 352, 25), // "saveVirtualSensorSettings"
QT_MOC_LITERAL(20, 378, 13), // "getSensorData"
QT_MOC_LITERAL(21, 392, 7), // "itemIdx"
QT_MOC_LITERAL(22, 400, 9), // "sensorIdx"
QT_MOC_LITERAL(23, 410, 12), // "dataFieldIdx"
QT_MOC_LITERAL(24, 423, 10), // "filterLogs"
QT_MOC_LITERAL(25, 434, 6), // "logKey"
QT_MOC_LITERAL(26, 441, 7), // "logName"
QT_MOC_LITERAL(27, 449, 4), // "from"
QT_MOC_LITERAL(28, 454, 2), // "to"
QT_MOC_LITERAL(29, 457, 9), // "saveOrder"
QT_MOC_LITERAL(30, 467, 9), // "loadOrder"
QT_MOC_LITERAL(31, 477, 15), // "setCellularMode"
QT_MOC_LITERAL(32, 493, 5) // "state"

    },
    "MainWindow\0switchContent\0\0value\0"
    "saveTransmissionSettings\0jsonSettings\0"
    "importTransmissionSettings\0url\0"
    "exportTransmissionSettings\0"
    "saveSystemSettings\0importSystemSettings\0"
    "exportSystemSettings\0saveAnalogSensorSettings\0"
    "loadAnalogSensorSettings\0sensorName\0"
    "saveDigitalSensorSettings\0"
    "loadDigitalSensorSettings\0"
    "saveSerialSensorSettings\0"
    "loadSerialSensorSettings\0"
    "saveVirtualSensorSettings\0getSensorData\0"
    "itemIdx\0sensorIdx\0dataFieldIdx\0"
    "filterLogs\0logKey\0logName\0from\0to\0"
    "saveOrder\0loadOrder\0setCellularMode\0"
    "state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  109,    2, 0x0a /* Public */,
       4,    1,  112,    2, 0x0a /* Public */,
       6,    1,  115,    2, 0x0a /* Public */,
       8,    2,  118,    2, 0x0a /* Public */,
       9,    1,  123,    2, 0x0a /* Public */,
      10,    1,  126,    2, 0x0a /* Public */,
      11,    2,  129,    2, 0x0a /* Public */,
      12,    1,  134,    2, 0x0a /* Public */,
      13,    1,  137,    2, 0x0a /* Public */,
      15,    1,  140,    2, 0x0a /* Public */,
      16,    1,  143,    2, 0x0a /* Public */,
      17,    1,  146,    2, 0x0a /* Public */,
      18,    1,  149,    2, 0x0a /* Public */,
      19,    1,  152,    2, 0x0a /* Public */,
      20,    3,  155,    2, 0x0a /* Public */,
      24,    4,  162,    2, 0x0a /* Public */,
      29,    1,  171,    2, 0x0a /* Public */,
      30,    0,  174,    2, 0x0a /* Public */,
      31,    1,  175,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    5,
    QMetaType::Bool, QMetaType::QString,    5,
    QMetaType::Bool, QMetaType::QString,   14,
    QMetaType::Bool, QMetaType::QString,    5,
    QMetaType::Bool, QMetaType::QString,   14,
    QMetaType::Bool, QMetaType::QString,    5,
    QMetaType::Bool, QMetaType::QString,   14,
    QMetaType::Bool, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   21,   22,   23,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   25,   26,   27,   28,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   32,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->switchContent((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->saveTransmissionSettings((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->importTransmissionSettings((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->exportTransmissionSettings((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->saveSystemSettings((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->importSystemSettings((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->exportSystemSettings((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: { bool _r = _t->saveAnalogSensorSettings((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->loadAnalogSensorSettings((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->saveDigitalSensorSettings((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->loadDigitalSensorSettings((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 11: { bool _r = _t->saveSerialSensorSettings((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->loadSerialSensorSettings((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: { bool _r = _t->saveVirtualSensorSettings((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->getSensorData((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 15: _t->filterLogs((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 16: _t->saveOrder((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: _t->loadOrder(); break;
        case 18: _t->setCellularMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
