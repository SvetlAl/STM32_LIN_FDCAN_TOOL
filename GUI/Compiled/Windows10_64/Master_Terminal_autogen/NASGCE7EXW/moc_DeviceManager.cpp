/****************************************************************************
** Meta object code from reading C++ file 'DeviceManager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/stm32_device/DeviceManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DeviceManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DeviceManager_t {
    const uint offsetsAndSize[192];
    char stringdata0[1719];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_DeviceManager_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_DeviceManager_t qt_meta_stringdata_DeviceManager = {
    {
QT_MOC_LITERAL(0, 13), // "DeviceManager"
QT_MOC_LITERAL(14, 7), // "changed"
QT_MOC_LITERAL(22, 0), // ""
QT_MOC_LITERAL(23, 15), // "memchip_changed"
QT_MOC_LITERAL(39, 14), // "lin_pp_changed"
QT_MOC_LITERAL(54, 22), // "canfd_settings_changed"
QT_MOC_LITERAL(77, 21), // "refreshOverrideStatus"
QT_MOC_LITERAL(99, 4), // "data"
QT_MOC_LITERAL(104, 26), // "refreshFdcanOverrideStatus"
QT_MOC_LITERAL(131, 20), // "refreshActiveFilters"
QT_MOC_LITERAL(152, 10), // "refreshLIN"
QT_MOC_LITERAL(163, 25), // "fill_OvrSts_from_DscModel"
QT_MOC_LITERAL(189, 27), // "update_DscModel_from_OvrSts"
QT_MOC_LITERAL(217, 25), // "fill_OvrSts_from_OvrModel"
QT_MOC_LITERAL(243, 27), // "update_OvrModel_from_OvrSts"
QT_MOC_LITERAL(271, 31), // "fdcan_fill_OvrSts_from_OvrModel"
QT_MOC_LITERAL(303, 33), // "fdcan_update_OvrModel_from_Ov..."
QT_MOC_LITERAL(337, 32), // "get_harware_scanner_filter_value"
QT_MOC_LITERAL(370, 6), // "byte_n"
QT_MOC_LITERAL(377, 12), // "isLowerBound"
QT_MOC_LITERAL(390, 15), // "canGateway_Mode"
QT_MOC_LITERAL(406, 21), // "calibratorFilter_Mode"
QT_MOC_LITERAL(428, 16), // "canOverride_Mode"
QT_MOC_LITERAL(445, 15), // "canScanner_Mode"
QT_MOC_LITERAL(461, 16), // "can2Scanner_Mode"
QT_MOC_LITERAL(478, 21), // "memoryPrograming_Mode"
QT_MOC_LITERAL(500, 17), // "canInjection_Mode"
QT_MOC_LITERAL(518, 14), // "customBTR_Mode"
QT_MOC_LITERAL(533, 11), // "val_BTR_PSC"
QT_MOC_LITERAL(545, 11), // "val_BTR_BS1"
QT_MOC_LITERAL(557, 11), // "val_BTR_BS2"
QT_MOC_LITERAL(569, 11), // "val_BTR_SJW"
QT_MOC_LITERAL(581, 16), // "customBTR_Mode_2"
QT_MOC_LITERAL(598, 13), // "val_BTR_PSC_2"
QT_MOC_LITERAL(612, 13), // "val_BTR_BS1_2"
QT_MOC_LITERAL(626, 13), // "val_BTR_BS2_2"
QT_MOC_LITERAL(640, 13), // "val_BTR_SJW_2"
QT_MOC_LITERAL(654, 21), // "canInjection_Mode_CDC"
QT_MOC_LITERAL(676, 12), // "memchip_name"
QT_MOC_LITERAL(689, 28), // "cdc_injection_threshold_mode"
QT_MOC_LITERAL(718, 29), // "cdc_injection_threshold_value"
QT_MOC_LITERAL(748, 23), // "scanner_hardware_filter"
QT_MOC_LITERAL(772, 31), // "str_scanner_hardware_filter_lwr"
QT_MOC_LITERAL(804, 31), // "str_scanner_hardware_filter_hgr"
QT_MOC_LITERAL(836, 14), // "lin_validation"
QT_MOC_LITERAL(851, 8), // "lin_mode"
QT_MOC_LITERAL(860, 16), // "lin_mode_gateway"
QT_MOC_LITERAL(877, 15), // "lin_mode_filter"
QT_MOC_LITERAL(893, 16), // "lin_mode_scanner"
QT_MOC_LITERAL(910, 15), // "lin_mode_device"
QT_MOC_LITERAL(926, 15), // "lin_poll_period"
QT_MOC_LITERAL(942, 12), // "lin_baudrate"
QT_MOC_LITERAL(955, 28), // "QLinConfigProperty_BaudRate*"
QT_MOC_LITERAL(984, 17), // "lin_filter_preset"
QT_MOC_LITERAL(1002, 32), // "QLinConfigProperty_FilterPreset*"
QT_MOC_LITERAL(1035, 14), // "val_FDCAN_freq"
QT_MOC_LITERAL(1050, 14), // "DiscardIdModel"
QT_MOC_LITERAL(1065, 25), // "QDiscardId_ModelProperty*"
QT_MOC_LITERAL(1091, 19), // "OverrideFilterModel"
QT_MOC_LITERAL(1111, 30), // "QOverrideFilter_ModelProperty*"
QT_MOC_LITERAL(1142, 22), // "OverrideLINFilterModel"
QT_MOC_LITERAL(1165, 33), // "QLinOverrideFilter_ModelPrope..."
QT_MOC_LITERAL(1199, 24), // "FdcanOverrideFilterModel"
QT_MOC_LITERAL(1224, 36), // "QFDCAN_OverrideFilter_ModelPr..."
QT_MOC_LITERAL(1261, 15), // "canfd1_nbtr_psc"
QT_MOC_LITERAL(1277, 17), // "canfd1_nbtr_tseg1"
QT_MOC_LITERAL(1295, 17), // "canfd1_nbtr_tseg2"
QT_MOC_LITERAL(1313, 15), // "canfd1_nbtr_sjw"
QT_MOC_LITERAL(1329, 15), // "canfd1_dbtr_psc"
QT_MOC_LITERAL(1345, 17), // "canfd1_dbtr_tseg1"
QT_MOC_LITERAL(1363, 17), // "canfd1_dbtr_tseg2"
QT_MOC_LITERAL(1381, 15), // "canfd1_dbtr_sjw"
QT_MOC_LITERAL(1397, 10), // "canfd1_ASM"
QT_MOC_LITERAL(1408, 10), // "canfd1_DAR"
QT_MOC_LITERAL(1419, 11), // "canfd1_FDOE"
QT_MOC_LITERAL(1431, 11), // "canfd1_BRSE"
QT_MOC_LITERAL(1443, 11), // "canfd1_PXHD"
QT_MOC_LITERAL(1455, 11), // "canfd1_EFBI"
QT_MOC_LITERAL(1467, 10), // "canfd1_TXP"
QT_MOC_LITERAL(1478, 11), // "canfd1_NISO"
QT_MOC_LITERAL(1490, 15), // "canfd2_nbtr_psc"
QT_MOC_LITERAL(1506, 17), // "canfd2_nbtr_tseg1"
QT_MOC_LITERAL(1524, 17), // "canfd2_nbtr_tseg2"
QT_MOC_LITERAL(1542, 15), // "canfd2_nbtr_sjw"
QT_MOC_LITERAL(1558, 15), // "canfd2_dbtr_psc"
QT_MOC_LITERAL(1574, 17), // "canfd2_dbtr_tseg1"
QT_MOC_LITERAL(1592, 17), // "canfd2_dbtr_tseg2"
QT_MOC_LITERAL(1610, 15), // "canfd2_dbtr_sjw"
QT_MOC_LITERAL(1626, 10), // "canfd2_ASM"
QT_MOC_LITERAL(1637, 10), // "canfd2_DAR"
QT_MOC_LITERAL(1648, 11), // "canfd2_FDOE"
QT_MOC_LITERAL(1660, 11), // "canfd2_BRSE"
QT_MOC_LITERAL(1672, 11), // "canfd2_PXHD"
QT_MOC_LITERAL(1684, 11), // "canfd2_EFBI"
QT_MOC_LITERAL(1696, 10), // "canfd2_TXP"
QT_MOC_LITERAL(1707, 11) // "canfd2_NISO"

    },
    "DeviceManager\0changed\0\0memchip_changed\0"
    "lin_pp_changed\0canfd_settings_changed\0"
    "refreshOverrideStatus\0data\0"
    "refreshFdcanOverrideStatus\0"
    "refreshActiveFilters\0refreshLIN\0"
    "fill_OvrSts_from_DscModel\0"
    "update_DscModel_from_OvrSts\0"
    "fill_OvrSts_from_OvrModel\0"
    "update_OvrModel_from_OvrSts\0"
    "fdcan_fill_OvrSts_from_OvrModel\0"
    "fdcan_update_OvrModel_from_OvrSts\0"
    "get_harware_scanner_filter_value\0"
    "byte_n\0isLowerBound\0canGateway_Mode\0"
    "calibratorFilter_Mode\0canOverride_Mode\0"
    "canScanner_Mode\0can2Scanner_Mode\0"
    "memoryPrograming_Mode\0canInjection_Mode\0"
    "customBTR_Mode\0val_BTR_PSC\0val_BTR_BS1\0"
    "val_BTR_BS2\0val_BTR_SJW\0customBTR_Mode_2\0"
    "val_BTR_PSC_2\0val_BTR_BS1_2\0val_BTR_BS2_2\0"
    "val_BTR_SJW_2\0canInjection_Mode_CDC\0"
    "memchip_name\0cdc_injection_threshold_mode\0"
    "cdc_injection_threshold_value\0"
    "scanner_hardware_filter\0"
    "str_scanner_hardware_filter_lwr\0"
    "str_scanner_hardware_filter_hgr\0"
    "lin_validation\0lin_mode\0lin_mode_gateway\0"
    "lin_mode_filter\0lin_mode_scanner\0"
    "lin_mode_device\0lin_poll_period\0"
    "lin_baudrate\0QLinConfigProperty_BaudRate*\0"
    "lin_filter_preset\0QLinConfigProperty_FilterPreset*\0"
    "val_FDCAN_freq\0DiscardIdModel\0"
    "QDiscardId_ModelProperty*\0OverrideFilterModel\0"
    "QOverrideFilter_ModelProperty*\0"
    "OverrideLINFilterModel\0"
    "QLinOverrideFilter_ModelProperty*\0"
    "FdcanOverrideFilterModel\0"
    "QFDCAN_OverrideFilter_ModelProperty*\0"
    "canfd1_nbtr_psc\0canfd1_nbtr_tseg1\0"
    "canfd1_nbtr_tseg2\0canfd1_nbtr_sjw\0"
    "canfd1_dbtr_psc\0canfd1_dbtr_tseg1\0"
    "canfd1_dbtr_tseg2\0canfd1_dbtr_sjw\0"
    "canfd1_ASM\0canfd1_DAR\0canfd1_FDOE\0"
    "canfd1_BRSE\0canfd1_PXHD\0canfd1_EFBI\0"
    "canfd1_TXP\0canfd1_NISO\0canfd2_nbtr_psc\0"
    "canfd2_nbtr_tseg1\0canfd2_nbtr_tseg2\0"
    "canfd2_nbtr_sjw\0canfd2_dbtr_psc\0"
    "canfd2_dbtr_tseg1\0canfd2_dbtr_tseg2\0"
    "canfd2_dbtr_sjw\0canfd2_ASM\0canfd2_DAR\0"
    "canfd2_FDOE\0canfd2_BRSE\0canfd2_PXHD\0"
    "canfd2_EFBI\0canfd2_TXP\0canfd2_NISO"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeviceManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
      70,  129, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  104,    2, 0x06,   71 /* Public */,
       3,    0,  105,    2, 0x06,   72 /* Public */,
       4,    0,  106,    2, 0x06,   73 /* Public */,
       5,    0,  107,    2, 0x06,   74 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,  108,    2, 0x0a,   75 /* Public */,
       8,    1,  111,    2, 0x0a,   77 /* Public */,
       9,    1,  114,    2, 0x0a,   79 /* Public */,
      10,    0,  117,    2, 0x0a,   81 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      11,    0,  118,    2, 0x02,   82 /* Public */,
      12,    0,  119,    2, 0x02,   83 /* Public */,
      13,    0,  120,    2, 0x02,   84 /* Public */,
      14,    0,  121,    2, 0x02,   85 /* Public */,
      15,    0,  122,    2, 0x02,   86 /* Public */,
      16,    0,  123,    2, 0x02,   87 /* Public */,
      17,    2,  124,    2, 0x02,   88 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    7,
    QMetaType::Void, QMetaType::QByteArray,    7,
    QMetaType::Void, QMetaType::QByteArray,    7,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int, QMetaType::Bool,   18,   19,

 // properties: name, type, flags
      20, QMetaType::Int, 0x00015103, uint(0), 0,
      21, QMetaType::Int, 0x00015103, uint(0), 0,
      22, QMetaType::Int, 0x00015103, uint(0), 0,
      23, QMetaType::Int, 0x00015103, uint(0), 0,
      24, QMetaType::Int, 0x00015103, uint(0), 0,
      25, QMetaType::Int, 0x00015001, uint(0), 0,
      26, QMetaType::Int, 0x00015001, uint(0), 0,
      27, QMetaType::Int, 0x00015103, uint(0), 0,
      28, QMetaType::Int, 0x00015103, uint(0), 0,
      29, QMetaType::Int, 0x00015103, uint(0), 0,
      30, QMetaType::Int, 0x00015103, uint(0), 0,
      31, QMetaType::Int, 0x00015103, uint(0), 0,
      32, QMetaType::Int, 0x00015103, uint(0), 0,
      33, QMetaType::Int, 0x00015103, uint(0), 0,
      34, QMetaType::Int, 0x00015103, uint(0), 0,
      35, QMetaType::Int, 0x00015103, uint(0), 0,
      36, QMetaType::Int, 0x00015103, uint(0), 0,
      37, QMetaType::Int, 0x00015001, uint(0), 0,
      38, QMetaType::QString, 0x00015001, uint(1), 0,
      39, QMetaType::Int, 0x00015003, uint(0), 0,
      40, QMetaType::Int, 0x00015003, uint(0), 0,
      41, QMetaType::Int, 0x00015003, uint(0), 0,
      42, QMetaType::QString, 0x00015003, uint(0), 0,
      43, QMetaType::QString, 0x00015003, uint(0), 0,
      44, QMetaType::Bool, 0x00015003, uint(0), 0,
      45, QMetaType::Int, 0x00015003, uint(0), 0,
      46, QMetaType::Bool, 0x00015001, uint(0), 0,
      47, QMetaType::Bool, 0x00015001, uint(0), 0,
      48, QMetaType::Bool, 0x00015001, uint(0), 0,
      49, QMetaType::Bool, 0x00015001, uint(0), 0,
      50, QMetaType::Int, 0x00015003, uint(2), 0,
      51, 0x80000000 | 52, 0x00015409, uint(-1), 0,
      53, 0x80000000 | 54, 0x00015409, uint(-1), 0,
      55, QMetaType::Int, 0x00015103, uint(0), 0,
      56, 0x80000000 | 57, 0x00015409, uint(-1), 0,
      58, 0x80000000 | 59, 0x00015409, uint(-1), 0,
      60, 0x80000000 | 61, 0x00015409, uint(-1), 0,
      62, 0x80000000 | 63, 0x00015409, uint(-1), 0,
      64, QMetaType::Int, 0x00015003, uint(3), 0,
      65, QMetaType::Int, 0x00015003, uint(3), 0,
      66, QMetaType::Int, 0x00015003, uint(3), 0,
      67, QMetaType::Int, 0x00015003, uint(3), 0,
      68, QMetaType::Int, 0x00015003, uint(3), 0,
      69, QMetaType::Int, 0x00015003, uint(3), 0,
      70, QMetaType::Int, 0x00015003, uint(3), 0,
      71, QMetaType::Int, 0x00015003, uint(3), 0,
      72, QMetaType::Bool, 0x00015003, uint(3), 0,
      73, QMetaType::Bool, 0x00015003, uint(3), 0,
      74, QMetaType::Bool, 0x00015003, uint(3), 0,
      75, QMetaType::Bool, 0x00015003, uint(3), 0,
      76, QMetaType::Bool, 0x00015003, uint(3), 0,
      77, QMetaType::Bool, 0x00015003, uint(3), 0,
      78, QMetaType::Bool, 0x00015003, uint(3), 0,
      79, QMetaType::Bool, 0x00015003, uint(3), 0,
      80, QMetaType::Int, 0x00015003, uint(3), 0,
      81, QMetaType::Int, 0x00015003, uint(3), 0,
      82, QMetaType::Int, 0x00015003, uint(3), 0,
      83, QMetaType::Int, 0x00015003, uint(3), 0,
      84, QMetaType::Int, 0x00015003, uint(3), 0,
      85, QMetaType::Int, 0x00015003, uint(3), 0,
      86, QMetaType::Int, 0x00015003, uint(3), 0,
      87, QMetaType::Int, 0x00015003, uint(3), 0,
      88, QMetaType::Bool, 0x00015003, uint(3), 0,
      89, QMetaType::Bool, 0x00015003, uint(3), 0,
      90, QMetaType::Bool, 0x00015003, uint(3), 0,
      91, QMetaType::Bool, 0x00015003, uint(3), 0,
      92, QMetaType::Bool, 0x00015003, uint(3), 0,
      93, QMetaType::Bool, 0x00015003, uint(3), 0,
      94, QMetaType::Bool, 0x00015003, uint(3), 0,
      95, QMetaType::Bool, 0x00015003, uint(3), 0,

       0        // eod
};

void DeviceManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DeviceManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->memchip_changed(); break;
        case 2: _t->lin_pp_changed(); break;
        case 3: _t->canfd_settings_changed(); break;
        case 4: _t->refreshOverrideStatus((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 5: _t->refreshFdcanOverrideStatus((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 6: _t->refreshActiveFilters((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 7: _t->refreshLIN(); break;
        case 8: _t->fill_OvrSts_from_DscModel(); break;
        case 9: _t->update_DscModel_from_OvrSts(); break;
        case 10: _t->fill_OvrSts_from_OvrModel(); break;
        case 11: _t->update_OvrModel_from_OvrSts(); break;
        case 12: _t->fdcan_fill_OvrSts_from_OvrModel(); break;
        case 13: _t->fdcan_update_OvrModel_from_OvrSts(); break;
        case 14: { int _r = _t->get_harware_scanner_filter_value((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DeviceManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceManager::changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DeviceManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceManager::memchip_changed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DeviceManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceManager::lin_pp_changed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DeviceManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceManager::canfd_settings_changed)) {
                *result = 3;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 34:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QDiscardId_ModelProperty* >(); break;
        case 37:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QFDCAN_OverrideFilter_ModelProperty* >(); break;
        case 31:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLinConfigProperty_BaudRate* >(); break;
        case 32:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLinConfigProperty_FilterPreset* >(); break;
        case 36:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QLinOverrideFilter_ModelProperty* >(); break;
        case 35:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QOverrideFilter_ModelProperty* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<DeviceManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->canGateway_Mode(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->calibratorFilter_Mode(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->canOverride_Mode(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->canScanner_Mode(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->can2Scanner_Mode(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->memoryPrograming_Mode(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->canInjection_Mode(); break;
        case 7: *reinterpret_cast< int*>(_v) = _t->customBTR_Mode(); break;
        case 8: *reinterpret_cast< int*>(_v) = _t->val_BTR_PSC(); break;
        case 9: *reinterpret_cast< int*>(_v) = _t->val_BTR_BS1(); break;
        case 10: *reinterpret_cast< int*>(_v) = _t->val_BTR_BS2(); break;
        case 11: *reinterpret_cast< int*>(_v) = _t->val_BTR_SJW(); break;
        case 12: *reinterpret_cast< int*>(_v) = _t->customBTR_Mode_2(); break;
        case 13: *reinterpret_cast< int*>(_v) = _t->val_BTR_PSC_2(); break;
        case 14: *reinterpret_cast< int*>(_v) = _t->val_BTR_BS1_2(); break;
        case 15: *reinterpret_cast< int*>(_v) = _t->val_BTR_BS2_2(); break;
        case 16: *reinterpret_cast< int*>(_v) = _t->val_BTR_SJW_2(); break;
        case 17: *reinterpret_cast< int*>(_v) = _t->canInjection_Mode_CDC(); break;
        case 18: *reinterpret_cast< QString*>(_v) = _t->memchip_name(); break;
        case 19: *reinterpret_cast< int*>(_v) = _t->cdc_injection_threshold_mode(); break;
        case 20: *reinterpret_cast< int*>(_v) = _t->cdc_injection_threshold_value(); break;
        case 21: *reinterpret_cast< int*>(_v) = _t->scanner_hardware_filter(); break;
        case 22: *reinterpret_cast< QString*>(_v) = _t->str_scanner_hardware_filter_lwr(); break;
        case 23: *reinterpret_cast< QString*>(_v) = _t->str_scanner_hardware_filter_hgr(); break;
        case 24: *reinterpret_cast< bool*>(_v) = _t->lin_validation(); break;
        case 25: *reinterpret_cast< int*>(_v) = _t->lin_mode(); break;
        case 26: *reinterpret_cast< bool*>(_v) = _t->lin_mode_gateway(); break;
        case 27: *reinterpret_cast< bool*>(_v) = _t->lin_mode_filter(); break;
        case 28: *reinterpret_cast< bool*>(_v) = _t->lin_mode_scanner(); break;
        case 29: *reinterpret_cast< bool*>(_v) = _t->lin_mode_device(); break;
        case 30: *reinterpret_cast< int*>(_v) = _t->lin_poll_period(); break;
        case 31: *reinterpret_cast< QLinConfigProperty_BaudRate**>(_v) = _t->lin_baudrate(); break;
        case 32: *reinterpret_cast< QLinConfigProperty_FilterPreset**>(_v) = _t->lin_filter_preset(); break;
        case 33: *reinterpret_cast< int*>(_v) = _t->val_FDCAN_freq(); break;
        case 34: *reinterpret_cast< QDiscardId_ModelProperty**>(_v) = _t->DiscardIdModel(); break;
        case 35: *reinterpret_cast< QOverrideFilter_ModelProperty**>(_v) = _t->OverrideFilterModel(); break;
        case 36: *reinterpret_cast< QLinOverrideFilter_ModelProperty**>(_v) = _t->OverrideLINFilterModel(); break;
        case 37: *reinterpret_cast< QFDCAN_OverrideFilter_ModelProperty**>(_v) = _t->FdcanOverrideFilterModel(); break;
        case 38: *reinterpret_cast< int*>(_v) = _t->canfd1_nbtr_psc(); break;
        case 39: *reinterpret_cast< int*>(_v) = _t->canfd1_nbtr_tseg1(); break;
        case 40: *reinterpret_cast< int*>(_v) = _t->canfd1_nbtr_tseg2(); break;
        case 41: *reinterpret_cast< int*>(_v) = _t->canfd1_nbtr_sjw(); break;
        case 42: *reinterpret_cast< int*>(_v) = _t->canfd1_dbtr_psc(); break;
        case 43: *reinterpret_cast< int*>(_v) = _t->canfd1_dbtr_tseg1(); break;
        case 44: *reinterpret_cast< int*>(_v) = _t->canfd1_dbtr_tseg2(); break;
        case 45: *reinterpret_cast< int*>(_v) = _t->canfd1_dbtr_sjw(); break;
        case 46: *reinterpret_cast< bool*>(_v) = _t->canfd1_ASM(); break;
        case 47: *reinterpret_cast< bool*>(_v) = _t->canfd1_DAR(); break;
        case 48: *reinterpret_cast< bool*>(_v) = _t->canfd1_FDOE(); break;
        case 49: *reinterpret_cast< bool*>(_v) = _t->canfd1_BRSE(); break;
        case 50: *reinterpret_cast< bool*>(_v) = _t->canfd1_PXHD(); break;
        case 51: *reinterpret_cast< bool*>(_v) = _t->canfd1_EFBI(); break;
        case 52: *reinterpret_cast< bool*>(_v) = _t->canfd1_TXP(); break;
        case 53: *reinterpret_cast< bool*>(_v) = _t->canfd1_NISO(); break;
        case 54: *reinterpret_cast< int*>(_v) = _t->canfd2_nbtr_psc(); break;
        case 55: *reinterpret_cast< int*>(_v) = _t->canfd2_nbtr_tseg1(); break;
        case 56: *reinterpret_cast< int*>(_v) = _t->canfd2_nbtr_tseg2(); break;
        case 57: *reinterpret_cast< int*>(_v) = _t->canfd2_nbtr_sjw(); break;
        case 58: *reinterpret_cast< int*>(_v) = _t->canfd2_dbtr_psc(); break;
        case 59: *reinterpret_cast< int*>(_v) = _t->canfd2_dbtr_tseg1(); break;
        case 60: *reinterpret_cast< int*>(_v) = _t->canfd2_dbtr_tseg2(); break;
        case 61: *reinterpret_cast< int*>(_v) = _t->canfd2_dbtr_sjw(); break;
        case 62: *reinterpret_cast< bool*>(_v) = _t->canfd2_ASM(); break;
        case 63: *reinterpret_cast< bool*>(_v) = _t->canfd2_DAR(); break;
        case 64: *reinterpret_cast< bool*>(_v) = _t->canfd2_FDOE(); break;
        case 65: *reinterpret_cast< bool*>(_v) = _t->canfd2_BRSE(); break;
        case 66: *reinterpret_cast< bool*>(_v) = _t->canfd2_PXHD(); break;
        case 67: *reinterpret_cast< bool*>(_v) = _t->canfd2_EFBI(); break;
        case 68: *reinterpret_cast< bool*>(_v) = _t->canfd2_TXP(); break;
        case 69: *reinterpret_cast< bool*>(_v) = _t->canfd2_NISO(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<DeviceManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCanGateway_Mode(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setCalibratorFilter_Mode(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setCanOverride_Mode(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setCanScanner_Mode(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setCan2Scanner_Mode(*reinterpret_cast< int*>(_v)); break;
        case 7: _t->setCustomBTR_Mode(*reinterpret_cast< int*>(_v)); break;
        case 8: _t->setVal_BTR_PSC(*reinterpret_cast< int*>(_v)); break;
        case 9: _t->setVal_BTR_BS1(*reinterpret_cast< int*>(_v)); break;
        case 10: _t->setVal_BTR_BS2(*reinterpret_cast< int*>(_v)); break;
        case 11: _t->setVal_BTR_SJW(*reinterpret_cast< int*>(_v)); break;
        case 12: _t->setCustomBTR_Mode_2(*reinterpret_cast< int*>(_v)); break;
        case 13: _t->setVal_BTR_PSC_2(*reinterpret_cast< int*>(_v)); break;
        case 14: _t->setVal_BTR_BS1_2(*reinterpret_cast< int*>(_v)); break;
        case 15: _t->setVal_BTR_BS2_2(*reinterpret_cast< int*>(_v)); break;
        case 16: _t->setVal_BTR_SJW_2(*reinterpret_cast< int*>(_v)); break;
        case 19: _t->set_cdc_injection_threshold_mode(*reinterpret_cast< int*>(_v)); break;
        case 20: _t->set_cdc_injection_threshold_value(*reinterpret_cast< int*>(_v)); break;
        case 21: _t->set_scanner_hardware_filter(*reinterpret_cast< int*>(_v)); break;
        case 22: _t->set_str_scanner_hardware_filter_lwr(*reinterpret_cast< QString*>(_v)); break;
        case 23: _t->set_str_scanner_hardware_filter_hgr(*reinterpret_cast< QString*>(_v)); break;
        case 24: _t->set_lin_validation(*reinterpret_cast< bool*>(_v)); break;
        case 25: _t->set_lin_mode(*reinterpret_cast< int*>(_v)); break;
        case 30: _t->set_lin_poll_period(*reinterpret_cast< int*>(_v)); break;
        case 33: _t->setVal_FDCAN_freq(*reinterpret_cast< int*>(_v)); break;
        case 38: _t->set_canfd1_nbtr_psc(*reinterpret_cast< int*>(_v)); break;
        case 39: _t->set_canfd1_nbtr_tseg1(*reinterpret_cast< int*>(_v)); break;
        case 40: _t->set_canfd1_nbtr_tseg2(*reinterpret_cast< int*>(_v)); break;
        case 41: _t->set_canfd1_nbtr_sjw(*reinterpret_cast< int*>(_v)); break;
        case 42: _t->set_canfd1_dbtr_psc(*reinterpret_cast< int*>(_v)); break;
        case 43: _t->set_canfd1_dbtr_tseg1(*reinterpret_cast< int*>(_v)); break;
        case 44: _t->set_canfd1_dbtr_tseg2(*reinterpret_cast< int*>(_v)); break;
        case 45: _t->set_canfd1_dbtr_sjw(*reinterpret_cast< int*>(_v)); break;
        case 46: _t->set_canfd1_ASM(*reinterpret_cast< bool*>(_v)); break;
        case 47: _t->set_canfd1_DAR(*reinterpret_cast< bool*>(_v)); break;
        case 48: _t->set_canfd1_FDOE(*reinterpret_cast< bool*>(_v)); break;
        case 49: _t->set_canfd1_BRSE(*reinterpret_cast< bool*>(_v)); break;
        case 50: _t->set_canfd1_PXHD(*reinterpret_cast< bool*>(_v)); break;
        case 51: _t->set_canfd1_EFBI(*reinterpret_cast< bool*>(_v)); break;
        case 52: _t->set_canfd1_TXP(*reinterpret_cast< bool*>(_v)); break;
        case 53: _t->set_canfd1_NISO(*reinterpret_cast< bool*>(_v)); break;
        case 54: _t->set_canfd2_nbtr_psc(*reinterpret_cast< int*>(_v)); break;
        case 55: _t->set_canfd2_nbtr_tseg1(*reinterpret_cast< int*>(_v)); break;
        case 56: _t->set_canfd2_nbtr_tseg2(*reinterpret_cast< int*>(_v)); break;
        case 57: _t->set_canfd2_nbtr_sjw(*reinterpret_cast< int*>(_v)); break;
        case 58: _t->set_canfd2_dbtr_psc(*reinterpret_cast< int*>(_v)); break;
        case 59: _t->set_canfd2_dbtr_tseg1(*reinterpret_cast< int*>(_v)); break;
        case 60: _t->set_canfd2_dbtr_tseg2(*reinterpret_cast< int*>(_v)); break;
        case 61: _t->set_canfd2_dbtr_sjw(*reinterpret_cast< int*>(_v)); break;
        case 62: _t->set_canfd2_ASM(*reinterpret_cast< bool*>(_v)); break;
        case 63: _t->set_canfd2_DAR(*reinterpret_cast< bool*>(_v)); break;
        case 64: _t->set_canfd2_FDOE(*reinterpret_cast< bool*>(_v)); break;
        case 65: _t->set_canfd2_BRSE(*reinterpret_cast< bool*>(_v)); break;
        case 66: _t->set_canfd2_PXHD(*reinterpret_cast< bool*>(_v)); break;
        case 67: _t->set_canfd2_EFBI(*reinterpret_cast< bool*>(_v)); break;
        case 68: _t->set_canfd2_TXP(*reinterpret_cast< bool*>(_v)); break;
        case 69: _t->set_canfd2_NISO(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject DeviceManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DeviceManager.offsetsAndSize,
    qt_meta_data_DeviceManager,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_DeviceManager_t
, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<QLinConfigProperty_BaudRate*, std::true_type>, QtPrivate::TypeAndForceComplete<QLinConfigProperty_FilterPreset*, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<QDiscardId_ModelProperty*, std::true_type>, QtPrivate::TypeAndForceComplete<QOverrideFilter_ModelProperty*, std::true_type>, QtPrivate::TypeAndForceComplete<QLinOverrideFilter_ModelProperty*, std::true_type>, QtPrivate::TypeAndForceComplete<QFDCAN_OverrideFilter_ModelProperty*, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<DeviceManager, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>

>,
    nullptr
} };


const QMetaObject *DeviceManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeviceManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DeviceManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 70;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void DeviceManager::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DeviceManager::memchip_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DeviceManager::lin_pp_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void DeviceManager::canfd_settings_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
