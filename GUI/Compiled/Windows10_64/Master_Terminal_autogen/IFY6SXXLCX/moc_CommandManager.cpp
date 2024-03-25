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
    const uint offsetsAndSize[174];
    char stringdata0[1416];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_CommandManager_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_CommandManager_t qt_meta_stringdata_CommandManager = {
    {
QT_MOC_LITERAL(0, 14), // "CommandManager"
QT_MOC_LITERAL(15, 22), // "memoryReadProgressSend"
QT_MOC_LITERAL(38, 0), // ""
QT_MOC_LITERAL(39, 7), // "_status"
QT_MOC_LITERAL(47, 18), // "asynchronousDataIn"
QT_MOC_LITERAL(66, 5), // "_data"
QT_MOC_LITERAL(72, 20), // "connectStatusChanged"
QT_MOC_LITERAL(93, 17), // "asynchReadChanged"
QT_MOC_LITERAL(111, 24), // "cdc_injection_posChanged"
QT_MOC_LITERAL(136, 19), // "cdc_circularChanged"
QT_MOC_LITERAL(156, 23), // "cdc_stop_timeoutChanged"
QT_MOC_LITERAL(180, 18), // "cdc_pendingChanged"
QT_MOC_LITERAL(199, 24), // "onCanScannerDataRecieved"
QT_MOC_LITERAL(224, 24), // "readInjectionModeRequest"
QT_MOC_LITERAL(249, 17), // "refreshAsynchRead"
QT_MOC_LITERAL(267, 7), // "connect"
QT_MOC_LITERAL(275, 10), // "disconnect"
QT_MOC_LITERAL(286, 14), // "connect_switch"
QT_MOC_LITERAL(301, 24), // "reset_vehicleNames_Model"
QT_MOC_LITERAL(326, 23), // "init_vehicleNames_Model"
QT_MOC_LITERAL(350, 12), // "isAsynchRead"
QT_MOC_LITERAL(363, 17), // "start_asynch_read"
QT_MOC_LITERAL(381, 4), // "mode"
QT_MOC_LITERAL(386, 16), // "stop_asynch_read"
QT_MOC_LITERAL(403, 12), // "writeRawData"
QT_MOC_LITERAL(416, 8), // "uint32_t"
QT_MOC_LITERAL(425, 7), // "address"
QT_MOC_LITERAL(433, 4), // "data"
QT_MOC_LITERAL(438, 6), // "append"
QT_MOC_LITERAL(445, 5), // "value"
QT_MOC_LITERAL(451, 12), // "sendFromFile"
QT_MOC_LITERAL(464, 19), // "waitAndReadResponse"
QT_MOC_LITERAL(484, 7), // "timeout"
QT_MOC_LITERAL(492, 19), // "exchange_cmd_string"
QT_MOC_LITERAL(512, 11), // "_output_cmd"
QT_MOC_LITERAL(524, 5), // "print"
QT_MOC_LITERAL(530, 6), // "handle"
QT_MOC_LITERAL(537, 14), // "readMemoryData"
QT_MOC_LITERAL(552, 18), // "transaction_length"
QT_MOC_LITERAL(571, 22), // "setAndSaveVehicleModel"
QT_MOC_LITERAL(594, 8), // "uint16_t"
QT_MOC_LITERAL(603, 10), // "model_code"
QT_MOC_LITERAL(614, 19), // "updateVehicleStatus"
QT_MOC_LITERAL(634, 17), // "saveVehicleStatus"
QT_MOC_LITERAL(652, 12), // "initNewModel"
QT_MOC_LITERAL(665, 18), // "setCalibratorValue"
QT_MOC_LITERAL(684, 8), // "property"
QT_MOC_LITERAL(693, 18), // "updateDeviceStatus"
QT_MOC_LITERAL(712, 16), // "saveDeviceStatus"
QT_MOC_LITERAL(729, 14), // "setDeviceValue"
QT_MOC_LITERAL(744, 7), // "uint8_t"
QT_MOC_LITERAL(752, 22), // "startCDC_CAN_Injection"
QT_MOC_LITERAL(775, 32), // "refresh_hardware_scanner_filters"
QT_MOC_LITERAL(808, 13), // "isLowerThresh"
QT_MOC_LITERAL(822, 19), // "read_fdcan_settings"
QT_MOC_LITERAL(842, 20), // "write_fdcan_settings"
QT_MOC_LITERAL(863, 13), // "restart_fdcan"
QT_MOC_LITERAL(877, 21), // "fdcan_send_single_msg"
QT_MOC_LITERAL(899, 7), // "can_num"
QT_MOC_LITERAL(907, 19), // "save_FDCAN_settings"
QT_MOC_LITERAL(927, 18), // "set_LIN_validation"
QT_MOC_LITERAL(946, 12), // "set_LIN_mode"
QT_MOC_LITERAL(959, 4), // "_set"
QT_MOC_LITERAL(964, 23), // "refresh_LIN_poll_period"
QT_MOC_LITERAL(988, 14), // "get_LIN_filter"
QT_MOC_LITERAL(1003, 8), // "dir_mosi"
QT_MOC_LITERAL(1012, 14), // "set_LIN_filter"
QT_MOC_LITERAL(1027, 20), // "updateOverrideStatus"
QT_MOC_LITERAL(1048, 27), // "updateOverrideActiveFilters"
QT_MOC_LITERAL(1076, 31), // "sendOverrideFilterConfiguration"
QT_MOC_LITERAL(1108, 26), // "fdcan_updateOverrideStatus"
QT_MOC_LITERAL(1135, 37), // "fdcan_sendOverrideFilterConfi..."
QT_MOC_LITERAL(1173, 14), // "startWebUpdate"
QT_MOC_LITERAL(1188, 21), // "startEmerencyProgramm"
QT_MOC_LITERAL(1210, 9), // "_filename"
QT_MOC_LITERAL(1220, 15), // "startFileUpdate"
QT_MOC_LITERAL(1236, 19), // "startCdcCanInection"
QT_MOC_LITERAL(1256, 9), // "isReverse"
QT_MOC_LITERAL(1266, 18), // "stopCdcCanInection"
QT_MOC_LITERAL(1285, 18), // "vehicleNames_Model"
QT_MOC_LITERAL(1304, 28), // "QVehicleNames_ModelProperty*"
QT_MOC_LITERAL(1333, 11), // "isConnected"
QT_MOC_LITERAL(1345, 10), // "AsynchRead"
QT_MOC_LITERAL(1356, 17), // "cdc_injection_pos"
QT_MOC_LITERAL(1374, 12), // "cdc_circular"
QT_MOC_LITERAL(1387, 16), // "cdc_stop_timeout"
QT_MOC_LITERAL(1404, 11) // "cdc_pending"

    },
    "CommandManager\0memoryReadProgressSend\0"
    "\0_status\0asynchronousDataIn\0_data\0"
    "connectStatusChanged\0asynchReadChanged\0"
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
    "refresh_hardware_scanner_filters\0"
    "isLowerThresh\0read_fdcan_settings\0"
    "write_fdcan_settings\0restart_fdcan\0"
    "fdcan_send_single_msg\0can_num\0"
    "save_FDCAN_settings\0set_LIN_validation\0"
    "set_LIN_mode\0_set\0refresh_LIN_poll_period\0"
    "get_LIN_filter\0dir_mosi\0set_LIN_filter\0"
    "updateOverrideStatus\0updateOverrideActiveFilters\0"
    "sendOverrideFilterConfiguration\0"
    "fdcan_updateOverrideStatus\0"
    "fdcan_sendOverrideFilterConfiguration\0"
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
      56,   14, // methods
       7,  490, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  350,    2, 0x06,    8 /* Public */,
       4,    1,  353,    2, 0x06,   10 /* Public */,
       6,    0,  356,    2, 0x06,   12 /* Public */,
       7,    0,  357,    2, 0x06,   13 /* Public */,
       8,    0,  358,    2, 0x06,   14 /* Public */,
       9,    0,  359,    2, 0x06,   15 /* Public */,
      10,    0,  360,    2, 0x06,   16 /* Public */,
      11,    0,  361,    2, 0x06,   17 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      12,    1,  362,    2, 0x0a,   18 /* Public */,
      13,    1,  365,    2, 0x0a,   20 /* Public */,
      14,    0,  368,    2, 0x0a,   22 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      15,    0,  369,    2, 0x02,   23 /* Public */,
      16,    0,  370,    2, 0x02,   24 /* Public */,
      17,    0,  371,    2, 0x02,   25 /* Public */,
      18,    0,  372,    2, 0x02,   26 /* Public */,
      19,    0,  373,    2, 0x02,   27 /* Public */,
      20,    0,  374,    2, 0x02,   28 /* Public */,
      21,    1,  375,    2, 0x02,   29 /* Public */,
      23,    1,  378,    2, 0x02,   31 /* Public */,
      24,    3,  381,    2, 0x02,   33 /* Public */,
      24,    2,  388,    2, 0x22,   37 /* Public | MethodCloned */,
      24,    4,  393,    2, 0x02,   40 /* Public */,
      31,    1,  402,    2, 0x02,   45 /* Public */,
      33,    3,  405,    2, 0x02,   47 /* Public */,
      33,    2,  412,    2, 0x22,   51 /* Public | MethodCloned */,
      33,    1,  417,    2, 0x22,   54 /* Public | MethodCloned */,
      37,    2,  420,    2, 0x02,   56 /* Public */,
      39,    1,  425,    2, 0x02,   59 /* Public */,
      42,    0,  428,    2, 0x02,   61 /* Public */,
      43,    1,  429,    2, 0x02,   62 /* Public */,
      45,    2,  432,    2, 0x02,   64 /* Public */,
      47,    0,  437,    2, 0x02,   67 /* Public */,
      48,    0,  438,    2, 0x02,   68 /* Public */,
      49,    2,  439,    2, 0x02,   69 /* Public */,
      51,    1,  444,    2, 0x02,   72 /* Public */,
      52,    1,  447,    2, 0x02,   74 /* Public */,
      54,    0,  450,    2, 0x02,   76 /* Public */,
      55,    0,  451,    2, 0x02,   77 /* Public */,
      56,    0,  452,    2, 0x02,   78 /* Public */,
      57,    1,  453,    2, 0x02,   79 /* Public */,
      59,    0,  456,    2, 0x02,   81 /* Public */,
      60,    1,  457,    2, 0x02,   82 /* Public */,
      61,    2,  460,    2, 0x02,   84 /* Public */,
      63,    1,  465,    2, 0x02,   87 /* Public */,
      64,    1,  468,    2, 0x02,   89 /* Public */,
      66,    1,  471,    2, 0x02,   91 /* Public */,
      67,    0,  474,    2, 0x02,   93 /* Public */,
      68,    0,  475,    2, 0x02,   94 /* Public */,
      69,    0,  476,    2, 0x02,   95 /* Public */,
      70,    0,  477,    2, 0x02,   96 /* Public */,
      71,    0,  478,    2, 0x02,   97 /* Public */,
      72,    0,  479,    2, 0x02,   98 /* Public */,
      73,    1,  480,    2, 0x02,   99 /* Public */,
      75,    1,  483,    2, 0x02,  101 /* Public */,
      76,    1,  486,    2, 0x02,  103 /* Public */,
      78,    0,  489,    2, 0x02,  105 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Bool, 0x80000000 | 25, QMetaType::QByteArray, QMetaType::Bool,   26,   27,   28,
    QMetaType::Bool, 0x80000000 | 25, QMetaType::QByteArray,   26,   27,
    QMetaType::Bool, 0x80000000 | 25, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,   26,   29,   30,   28,
    QMetaType::QByteArray, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,   34,   35,   36,
    QMetaType::QString, QMetaType::QString, QMetaType::Bool,   34,   35,
    QMetaType::QString, QMetaType::QString,   34,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,   26,   38,
    QMetaType::Bool, 0x80000000 | 40,   41,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::Bool,   44,
    QMetaType::Bool, 0x80000000 | 25, 0x80000000 | 25,   46,   29,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, 0x80000000 | 25, 0x80000000 | 50,   46,   29,
    QMetaType::Bool, 0x80000000 | 50,   29,
    QMetaType::Void, QMetaType::Bool,   53,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::Int,   58,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::Bool,   29,
    QMetaType::Bool, QMetaType::Int, QMetaType::Bool,   29,   62,
    QMetaType::Void, 0x80000000 | 40,   29,
    QMetaType::Bool, QMetaType::Bool,   65,
    QMetaType::Bool, QMetaType::Bool,   65,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   74,
    QMetaType::Void, QMetaType::QString,   74,
    QMetaType::Void, QMetaType::Bool,   77,
    QMetaType::Void,

 // properties: name, type, flags
      79, 0x80000000 | 80, 0x00015409, uint(-1), 0,
      81, QMetaType::Bool, 0x00015001, uint(2), 0,
      82, QMetaType::Bool, 0x00015001, uint(3), 0,
      83, QMetaType::Int, 0x00015107, uint(4), 0,
      84, QMetaType::Bool, 0x00015107, uint(5), 0,
      85, QMetaType::Bool, 0x00015003, uint(6), 0,
      86, QMetaType::Bool, 0x00015003, uint(7), 0,

       0        // eod
};

void CommandManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CommandManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->memoryReadProgressSend((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->asynchronousDataIn((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 2: _t->connectStatusChanged(); break;
        case 3: _t->asynchReadChanged(); break;
        case 4: _t->cdc_injection_posChanged(); break;
        case 5: _t->cdc_circularChanged(); break;
        case 6: _t->cdc_stop_timeoutChanged(); break;
        case 7: _t->cdc_pendingChanged(); break;
        case 8: _t->onCanScannerDataRecieved((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 9: _t->readInjectionModeRequest((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 10: _t->refreshAsynchRead(); break;
        case 11: { bool _r = _t->connect();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->disconnect();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: { bool _r = _t->connect_switch();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->reset_vehicleNames_Model(); break;
        case 15: _t->init_vehicleNames_Model(); break;
        case 16: { bool _r = _t->isAsynchRead();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 17: _t->start_asynch_read((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 18: _t->stop_asynch_read((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 19: { bool _r = _t->writeRawData((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 20: { bool _r = _t->writeRawData((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 21: { bool _r = _t->writeRawData((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 22: { QByteArray _r = _t->waitAndReadResponse((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = std::move(_r); }  break;
        case 23: { QString _r = _t->exchange_cmd_string((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 24: { QString _r = _t->exchange_cmd_string((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 25: { QString _r = _t->exchange_cmd_string((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 26: { bool _r = _t->readMemoryData((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 27: { bool _r = _t->setAndSaveVehicleModel((*reinterpret_cast< std::add_pointer_t<uint16_t>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 28: _t->updateVehicleStatus(); break;
        case 29: { bool _r = _t->saveVehicleStatus((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 30: { bool _r = _t->setCalibratorValue((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 31: _t->updateDeviceStatus(); break;
        case 32: _t->saveDeviceStatus(); break;
        case 33: { bool _r = _t->setDeviceValue((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 34: { bool _r = _t->startCDC_CAN_Injection((*reinterpret_cast< std::add_pointer_t<uint8_t>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 35: _t->refresh_hardware_scanner_filters((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 36: _t->read_fdcan_settings(); break;
        case 37: { bool _r = _t->write_fdcan_settings();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 38: { bool _r = _t->restart_fdcan();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 39: { bool _r = _t->fdcan_send_single_msg((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 40: { bool _r = _t->save_FDCAN_settings();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 41: { bool _r = _t->set_LIN_validation((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 42: { bool _r = _t->set_LIN_mode((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 43: _t->refresh_LIN_poll_period((*reinterpret_cast< std::add_pointer_t<uint16_t>>(_a[1]))); break;
        case 44: { bool _r = _t->get_LIN_filter((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 45: { bool _r = _t->set_LIN_filter((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 46: { bool _r = _t->updateOverrideStatus();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 47: { bool _r = _t->updateOverrideActiveFilters();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 48: { bool _r = _t->sendOverrideFilterConfiguration();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 49: { bool _r = _t->fdcan_updateOverrideStatus();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 50: { bool _r = _t->fdcan_sendOverrideFilterConfiguration();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 51: _t->startWebUpdate(); break;
        case 52: _t->startEmerencyProgramm((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 53: _t->startFileUpdate((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 54: _t->startCdcCanInection((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 55: _t->stopCdcCanInection(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CommandManager::*)(const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandManager::memoryReadProgressSend)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CommandManager::*)(const QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandManager::asynchronousDataIn)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CommandManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandManager::connectStatusChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CommandManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandManager::asynchReadChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CommandManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandManager::cdc_injection_posChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CommandManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandManager::cdc_circularChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (CommandManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandManager::cdc_stop_timeoutChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (CommandManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CommandManager::cdc_pendingChanged)) {
                *result = 7;
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
, QtPrivate::TypeAndForceComplete<QVehicleNames_ModelProperty*, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<CommandManager, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<uint16_t, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>, QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<uint32_t, std::false_type>, QtPrivate::TypeAndForceComplete<uint8_t, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<uint8_t, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<uint16_t, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

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
        if (_id < 56)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 56;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 56)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 56;
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
void CommandManager::memoryReadProgressSend(const QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CommandManager::asynchronousDataIn(const QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CommandManager::connectStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CommandManager::asynchReadChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CommandManager::cdc_injection_posChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void CommandManager::cdc_circularChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void CommandManager::cdc_stop_timeoutChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void CommandManager::cdc_pendingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
