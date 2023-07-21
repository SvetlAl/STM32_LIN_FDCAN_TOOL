/****************************************************************************
** Meta object code from reading C++ file 'CommandManager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/command_manager/CommandManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CommandManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CommandManager_t {
    const uint offsetsAndSize[136];
    char stringdata0[1068];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_CommandManager_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_CommandManager_t qt_meta_stringdata_CommandManager = {
    {
QT_MOC_LITERAL(0, 14), // "CommandManager"
QT_MOC_LITERAL(15, 18), // "asynchronousDataIn"
QT_MOC_LITERAL(34, 0), // ""
QT_MOC_LITERAL(35, 5), // "_data"
QT_MOC_LITERAL(41, 20), // "connectStatusChanged"
QT_MOC_LITERAL(62, 17), // "asynchReadChanged"
QT_MOC_LITERAL(80, 24), // "cdc_injection_posChanged"
QT_MOC_LITERAL(105, 19), // "cdc_circularChanged"
QT_MOC_LITERAL(125, 23), // "cdc_stop_timeoutChanged"
QT_MOC_LITERAL(149, 18), // "cdc_pendingChanged"
QT_MOC_LITERAL(168, 24), // "onCanScannerDataRecieved"
QT_MOC_LITERAL(193, 24), // "readInjectionModeRequest"
QT_MOC_LITERAL(218, 17), // "refreshAsynchRead"
QT_MOC_LITERAL(236, 7), // "connect"
QT_MOC_LITERAL(244, 10), // "disconnect"
QT_MOC_LITERAL(255, 14), // "connect_switch"
QT_MOC_LITERAL(270, 24), // "reset_vehicleNames_Model"
QT_MOC_LITERAL(295, 23), // "init_vehicleNames_Model"
QT_MOC_LITERAL(319, 12), // "isAsynchRead"
QT_MOC_LITERAL(332, 17), // "start_asynch_read"
QT_MOC_LITERAL(350, 4), // "mode"
QT_MOC_LITERAL(355, 16), // "stop_asynch_read"
QT_MOC_LITERAL(372, 12), // "writeRawData"
QT_MOC_LITERAL(385, 8), // "uint32_t"
QT_MOC_LITERAL(394, 7), // "address"
QT_MOC_LITERAL(402, 4), // "data"
QT_MOC_LITERAL(407, 6), // "append"
QT_MOC_LITERAL(414, 5), // "value"
QT_MOC_LITERAL(420, 12), // "sendFromFile"
QT_MOC_LITERAL(433, 19), // "waitAndReadResponse"
QT_MOC_LITERAL(453, 7), // "timeout"
QT_MOC_LITERAL(461, 19), // "exchange_cmd_string"
QT_MOC_LITERAL(481, 11), // "_output_cmd"
QT_MOC_LITERAL(493, 5), // "print"
QT_MOC_LITERAL(499, 6), // "handle"
QT_MOC_LITERAL(506, 14), // "readMemoryData"
QT_MOC_LITERAL(521, 18), // "transaction_length"
QT_MOC_LITERAL(540, 22), // "setAndSaveVehicleModel"
QT_MOC_LITERAL(563, 8), // "uint16_t"
QT_MOC_LITERAL(572, 10), // "model_code"
QT_MOC_LITERAL(583, 19), // "updateVehicleStatus"
QT_MOC_LITERAL(603, 17), // "saveVehicleStatus"
QT_MOC_LITERAL(621, 12), // "initNewModel"
QT_MOC_LITERAL(634, 18), // "setCalibratorValue"
QT_MOC_LITERAL(653, 8), // "property"
QT_MOC_LITERAL(662, 18), // "updateDeviceStatus"
QT_MOC_LITERAL(681, 16), // "saveDeviceStatus"
QT_MOC_LITERAL(698, 14), // "setDeviceValue"
QT_MOC_LITERAL(713, 7), // "uint8_t"
QT_MOC_LITERAL(721, 22), // "startCDC_CAN_Injection"
QT_MOC_LITERAL(744, 20), // "updateOverrideStatus"
QT_MOC_LITERAL(765, 27), // "updateOverrideActiveFilters"
QT_MOC_LITERAL(793, 31), // "sendOverrideFilterConfiguration"
QT_MOC_LITERAL(825, 14), // "startWebUpdate"
QT_MOC_LITERAL(840, 21), // "startEmerencyProgramm"
QT_MOC_LITERAL(862, 9), // "_filename"
QT_MOC_LITERAL(872, 15), // "startFileUpdate"
QT_MOC_LITERAL(888, 19), // "startCdcCanInection"
QT_MOC_LITERAL(908, 9), // "isReverse"
QT_MOC_LITERAL(918, 18), // "stopCdcCanInection"
QT_MOC_LITERAL(937, 18), // "vehicleNames_Model"
QT_MOC_LITERAL(956, 28), // "QVehicleNames_ModelProperty*"
QT_MOC_LITERAL(985, 11), // "isConnected"
QT_MOC_LITERAL(997, 10), // "AsynchRead"
QT_MOC_LITERAL(1008, 17), // "cdc_injection_pos"
QT_MOC_LITERAL(1026, 12), // "cdc_circular"
QT_MOC_LITERAL(1039, 16), // "cdc_stop_timeout"
QT_MOC_LITERAL(1056, 11) // "cdc_pending"

    },
    "CommandManager\0asynchronousDataIn\0\0"
    "_data\0connectStatusChanged\0asynchReadChanged\0"
    "cdc_injection_posChanged\0cdc_circularChanged\0"
    "cdc_stop_timeoutChanged\0cdc_pendingChanged\0"
    "onCanScannerDataRecieved\0"
    "readInjectionModeRequest\0refreshAsynchRead\0"
    "connect\0disconnect\0connect_switch\0"
    "reset_vehicleNames_Model\0"
    "init_vehicleNames_Model\0isAsynchRead\0"
    "start_asynch_read\0mode\0stop_asynch_read\0"
    "writeRawData\0uint32_t\0address\0data\0"
    "append\0value\0sendFromFile\0waitAndReadResponse\0"
    "timeout\0exchange_cmd_string\0_output_cmd\0"
    "print\0handle\0readMemoryData\0"
    "transaction_length\0setAndSaveVehicleModel\0"
    "uint16_t\0model_code\0updateVehicleStatus\0"
    "saveVehicleStatus\0initNewModel\0"
    "setCalibratorValue\0property\0"
    "updateDeviceStatus\0saveDeviceStatus\0"
    "setDeviceValue\0uint8_t\0startCDC_CAN_Injection\0"
    "updateOverrideStatus\0updateOverrideActiveFilters\0"
    "sendOverrideFilterConfiguration\0"
    "startWebUpdate\0startEmerencyProgramm\0"
    "_filename\0startFileUpdate\0startCdcCanInection\0"
    "isReverse\0stopCdcCanInection\0"
    "vehicleNames_Model\0QVehicleNames_ModelProperty*\0"
    "isConnected\0AsynchRead\0cdc_injection_pos\0"
    "cdc_circular\0cdc_stop_timeout\0cdc_pending"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CommandManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      42,   14, // methods
       7,  374, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  266,    2, 0x06,    8 /* Public */,
       4,    0,  269,    2, 0x06,   10 /* Public */,
       5,    0,  270,    2, 0x06,   11 /* Public */,
       6,    0,  271,    2, 0x06,   12 /* Public */,
       7,    0,  272,    2, 0x06,   13 /* Public */,
       8,    0,  273,    2, 0x06,   14 /* Public */,
       9,    0,  274,    2, 0x06,   15 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    1,  275,    2, 0x0a,   16 /* Public */,
      11,    1,  278,    2, 0x0a,   18 /* Public */,
      12,    0,  281,    2, 0x0a,   20 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      13,    0,  282,    2, 0x02,   21 /* Public */,
      14,    0,  283,    2, 0x02,   22 /* Public */,
      15,    0,  284,    2, 0x02,   23 /* Public */,
      16,    0,  285,    2, 0x02,   24 /* Public */,
      17,    0,  286,    2, 0x02,   25 /* Public */,
      18,    0,  287,    2, 0x02,   26 /* Public */,
      19,    1,  288,    2, 0x02,   27 /* Public */,
      21,    1,  291,    2, 0x02,   29 /* Public */,
      22,    3,  294,    2, 0x02,   31 /* Public */,
      22,    2,  301,    2, 0x22,   35 /* Public | MethodCloned */,
      22,    4,  306,    2, 0x02,   38 /* Public */,
      29,    1,  315,    2, 0x02,   43 /* Public */,
      31,    3,  318,    2, 0x02,   45 /* Public */,
      31,    2,  325,    2, 0x22,   49 /* Public | MethodCloned */,
      31,    1,  330,    2, 0x22,   52 /* Public | MethodCloned */,
      35,    2,  333,    2, 0x02,   54 /* Public */,
      37,    1,  338,    2, 0x02,   57 /* Public */,
      40,    0,  341,    2, 0x02,   59 /* Public */,
      41,    1,  342,    2, 0x02,   60 /* Public */,
      43,    2,  345,    2, 0x02,   62 /* Public */,
      45,    0,  350,    2, 0x02,   65 /* Public */,
      46,    0,  351,    2, 0x02,   66 /* Public */,
      47,    2,  352,    2, 0x02,   67 /* Public */,
      49,    1,  357,    2, 0x02,   70 /* Public */,
      50,    0,  360,    2, 0x02,   72 /* Public */,
      51,    0,  361,    2, 0x02,   73 /* Public */,
      52,    0,  362,    2, 0x02,   74 /* Public */,
      53,    0,  363,    2, 0x02,   75 /* Public */,
      54,    1,  364,    2, 0x02,   76 /* Public */,
      56,    1,  367,    2, 0x02,   78 /* Public */,
      57,    1,  370,    2, 0x02,   80 /* Public */,
      59,    0,  373,    2, 0x02,   82 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Bool, 0x80000000 | 23, QMetaType::QByteArray, QMetaType::Bool,   24,   25,   26,
    QMetaType::Bool, 0x80000000 | 23, QMetaType::QByteArray,   24,   25,
    QMetaType::Bool, 0x80000000 | 23, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,   24,   27,   28,   26,
    QMetaType::QByteArray, QMetaType::Int,   30,
    QMetaType::QString, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,   32,   33,   34,
    QMetaType::QString, QMetaType::QString, QMetaType::Bool,   32,   33,
    QMetaType::QString, QMetaType::QString,   32,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,   24,   36,
    QMetaType::Bool, 0x80000000 | 38,   39,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::Bool,   42,
    QMetaType::Bool, 0x80000000 | 23, 0x80000000 | 23,   44,   27,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, 0x80000000 | 23, 0x80000000 | 48,   44,   27,
    QMetaType::Bool, 0x80000000 | 48,   27,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   55,
    QMetaType::Void, QMetaType::QString,   55,
    QMetaType::Void, QMetaType::Bool,   58,
    QMetaType::Void,

 // properties: name, type, flags
      60, 0x80000000 | 61, 0x00015409, uint(-1), 0,
      62, QMetaType::Bool, 0x00015001, uint(1), 0,
      63, QMetaType::Bool, 0x00015001, uint(2), 0,
      64, QMetaType::Int, 0x00015107, uint(3), 0,
      65, QMetaType::Bool, 0x00015107, uint(4), 0,
      66, QMetaType::Bool, 0x00015003, uint(5), 0,
      67, QMetaType::Bool, 0x00015003, uint(6), 0,

       0        // eod
};

void CommandManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CommandManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->asynchronousDataIn((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 1: _t->connectStatusChanged(); break;
        case 2: _t->asynchReadChanged(); break;
        case 3: _t->cdc_injection_posChanged(); break;
        case 4: _t->cdc_circularChanged(); break;
        case 5: _t->cdc_stop_timeoutChanged(); break;
        case 6: _t->cdc_pendingChanged(); break;
        case 7: _t->onCanScannerDataRecieved((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 8: _t->readInjectionModeRequest((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 9: _t->refreshAsynchRead(); break;
        case 10: { bool _r = _t->connect();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 11: { bool _r = _t->disconnect();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->connect_switch();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->reset_vehicleNames_Model(); break;
        case 14: _t->init_vehicleNames_Model(); break;
        case 15: { bool _r = _t->isAsynchRead();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->start_asynch_read((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 17: _t->stop_asynch_read((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 18: { bool _r = _t->writeRawData((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 19: { bool _r = _t->writeRawData((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 20: { bool _r = _t->writeRawData((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 21: { QByteArray _r = _t->waitAndReadResponse((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = std::move(_r); }  break;
        case 22: { QString _r = _t->exchange_cmd_string((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 23: { QString _r = _t->exchange_cmd_string((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 24: { QString _r = _t->exchange_cmd_string((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 25: { bool _r = _t->readMemoryData((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 26: { bool _r = _t->setAndSaveVehicleModel((*reinterpret_cast< std::add_pointer_t<uint16_t>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 27: _t->updateVehicleStatus(); break;
        case 28: { bool _r = _t->saveVehicleStatus((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 29: { bool _r = _t->setCalibratorValue((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 30: _t->updateDeviceStatus(); break;
        case 31: _t->saveDeviceStatus(); break;
        case 32: { bool _r = _t->setDeviceValue((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 33: { bool _r = _t->startCDC_CAN_Injection((*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 34: { bool _r = _t->updateOverrideStatus();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 35: { bool _r = _t->updateOverrideActiveFilters();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 36: { bool _r = _t->sendOverrideFilterConfiguration();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 37: _t->startWebUpdate(); break;
        case 38: _t->startEmerencyProgramm((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 39: _t->startFileUpdate((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 40: _t->startCdcCanInection((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 41: _t->stopCdcCanInection(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CommandManager::*)(const QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandManager::asynchronousDataIn)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CommandManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandManager::connectStatusChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CommandManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandManager::asynchReadChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CommandManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandManager::cdc_injection_posChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CommandManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandManager::cdc_circularChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CommandManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandManager::cdc_stop_timeoutChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (CommandManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandManager::cdc_pendingChanged)) {
                *result = 6;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVehicleNames_ModelProperty* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<CommandManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVehicleNames_ModelProperty**>(_v) = _t->vehicleNames_Model(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->isConnected(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->isAsynchRead(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->cdc_injection_pos(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->cdc_circular(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->cdc_stop_flag(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->cdc_pending_flag(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<CommandManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 3: _t->setCdc_injection_pos(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setCdc_circular(*reinterpret_cast< bool*>(_v)); break;
        case 5: _t->setCdc_stop_flag(*reinterpret_cast< bool*>(_v)); break;
        case 6: _t->setCdc_pending_flag(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
        auto *_t = static_cast<CommandManager *>(_o);
        (void)_t;
        switch (_id) {
        case 3: _t->resetCdc_injection_pos(); break;
        case 4: _t->resetCdc_circular(); break;
        default: break;
        }
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject CommandManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CommandManager.offsetsAndSize,
    qt_meta_data_CommandManager,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_CommandManager_t
, QtPrivate::TypeAndForceComplete<QVehicleNames_ModelProperty*, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<CommandManager, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<uint16_t, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>, QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>, QtPrivate::TypeAndForceComplete<uint8_t, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<uint8_t, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

>,
    nullptr
} };


const QMetaObject *CommandManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CommandManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CommandManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CommandManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 42)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 42;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 42)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 42;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void CommandManager::asynchronousDataIn(const QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CommandManager::connectStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CommandManager::asynchReadChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CommandManager::cdc_injection_posChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CommandManager::cdc_circularChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void CommandManager::cdc_stop_timeoutChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void CommandManager::cdc_pendingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
