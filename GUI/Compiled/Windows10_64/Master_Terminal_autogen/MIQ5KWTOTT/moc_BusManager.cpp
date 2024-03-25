/****************************************************************************
** Meta object code from reading C++ file 'BusManager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/bus/BusManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BusManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BusManager_t {
    const uint offsetsAndSize[172];
    char stringdata0[1485];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_BusManager_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_BusManager_t qt_meta_stringdata_BusManager = {
    {
QT_MOC_LITERAL(0, 10), // "BusManager"
QT_MOC_LITERAL(11, 17), // "use_range_changed"
QT_MOC_LITERAL(29, 0), // ""
QT_MOC_LITERAL(30, 22), // "max_TraceItems_Changed"
QT_MOC_LITERAL(53, 21), // "aux_trace_sizeChanged"
QT_MOC_LITERAL(75, 22), // "cdc_trace_emptyChanged"
QT_MOC_LITERAL(98, 20), // "fd_use_range_changed"
QT_MOC_LITERAL(119, 25), // "fd_max_TraceItems_Changed"
QT_MOC_LITERAL(145, 24), // "fd_aux_trace_sizeChanged"
QT_MOC_LITERAL(170, 25), // "fd_cdc_trace_emptyChanged"
QT_MOC_LITERAL(196, 20), // "monitorScanOnChanged"
QT_MOC_LITERAL(217, 23), // "fd_monitorScanOnChanged"
QT_MOC_LITERAL(241, 23), // "monitorLinScanOnChanged"
QT_MOC_LITERAL(265, 19), // "processIncomingData"
QT_MOC_LITERAL(285, 5), // "_data"
QT_MOC_LITERAL(291, 22), // "fd_processIncomingData"
QT_MOC_LITERAL(314, 22), // "processLinIncomingData"
QT_MOC_LITERAL(337, 21), // "resetCanBusTraceModel"
QT_MOC_LITERAL(359, 24), // "fd_resetCanBusTraceModel"
QT_MOC_LITERAL(384, 21), // "resetLinBusTraceModel"
QT_MOC_LITERAL(406, 12), // "setFilterCan"
QT_MOC_LITERAL(419, 7), // "can_num"
QT_MOC_LITERAL(427, 9), // "isEnabled"
QT_MOC_LITERAL(437, 14), // "setFilterRange"
QT_MOC_LITERAL(452, 5), // "start"
QT_MOC_LITERAL(458, 3), // "end"
QT_MOC_LITERAL(462, 15), // "fd_setFilterCan"
QT_MOC_LITERAL(478, 17), // "fd_setFilterRange"
QT_MOC_LITERAL(496, 18), // "createNewTraceItem"
QT_MOC_LITERAL(515, 7), // "newItem"
QT_MOC_LITERAL(523, 8), // "_default"
QT_MOC_LITERAL(532, 9), // "saveTrace"
QT_MOC_LITERAL(542, 8), // "filename"
QT_MOC_LITERAL(551, 9), // "loadTrace"
QT_MOC_LITERAL(561, 15), // "sortTraceColumn"
QT_MOC_LITERAL(577, 3), // "col"
QT_MOC_LITERAL(581, 15), // "fromTopToBottom"
QT_MOC_LITERAL(597, 21), // "switchSortTraceColumn"
QT_MOC_LITERAL(619, 14), // "clearSortTrace"
QT_MOC_LITERAL(634, 19), // "deleteSelectedTrace"
QT_MOC_LITERAL(654, 16), // "deleteRangeTrace"
QT_MOC_LITERAL(671, 5), // "begin"
QT_MOC_LITERAL(677, 19), // "setTraceIdDirection"
QT_MOC_LITERAL(697, 2), // "id"
QT_MOC_LITERAL(700, 5), // "can_n"
QT_MOC_LITERAL(706, 8), // "cropTime"
QT_MOC_LITERAL(715, 20), // "deleteTimeRangeTrace"
QT_MOC_LITERAL(736, 21), // "fd_createNewTraceItem"
QT_MOC_LITERAL(758, 12), // "fd_saveTrace"
QT_MOC_LITERAL(771, 12), // "fd_loadTrace"
QT_MOC_LITERAL(784, 18), // "fd_sortTraceColumn"
QT_MOC_LITERAL(803, 24), // "fd_switchSortTraceColumn"
QT_MOC_LITERAL(828, 17), // "fd_clearSortTrace"
QT_MOC_LITERAL(846, 22), // "fd_deleteSelectedTrace"
QT_MOC_LITERAL(869, 19), // "fd_deleteRangeTrace"
QT_MOC_LITERAL(889, 22), // "fd_setTraceIdDirection"
QT_MOC_LITERAL(912, 11), // "fd_cropTime"
QT_MOC_LITERAL(924, 23), // "fd_deleteTimeRangeTrace"
QT_MOC_LITERAL(948, 18), // "sortLinTraceColumn"
QT_MOC_LITERAL(967, 24), // "switchLinSortTraceColumn"
QT_MOC_LITERAL(992, 17), // "clearLinSortTrace"
QT_MOC_LITERAL(1010, 12), // "loadAuxTrace"
QT_MOC_LITERAL(1023, 15), // "fd_loadAuxTrace"
QT_MOC_LITERAL(1039, 13), // "monitorScanOn"
QT_MOC_LITERAL(1053, 16), // "CanBusTraceModel"
QT_MOC_LITERAL(1070, 20), // "CanBusTraceProperty*"
QT_MOC_LITERAL(1091, 19), // "max_can_trace_items"
QT_MOC_LITERAL(1111, 15), // "cdc_trace_empty"
QT_MOC_LITERAL(1127, 18), // "CanBusMonitorModel"
QT_MOC_LITERAL(1146, 22), // "CanBusMonitorProperty*"
QT_MOC_LITERAL(1169, 13), // "range_id_used"
QT_MOC_LITERAL(1183, 14), // "aux_trace_size"
QT_MOC_LITERAL(1198, 16), // "fd_monitorScanOn"
QT_MOC_LITERAL(1215, 18), // "FdCanBusTraceModel"
QT_MOC_LITERAL(1234, 26), // "FDCAN_CanBusTraceProperty*"
QT_MOC_LITERAL(1261, 22), // "fd_max_can_trace_items"
QT_MOC_LITERAL(1284, 18), // "fd_cdc_trace_empty"
QT_MOC_LITERAL(1303, 20), // "FdCanBusMonitorModel"
QT_MOC_LITERAL(1324, 28), // "FDCAN_CanBusMonitorProperty*"
QT_MOC_LITERAL(1353, 16), // "fd_range_id_used"
QT_MOC_LITERAL(1370, 17), // "fd_aux_trace_size"
QT_MOC_LITERAL(1388, 16), // "LinBusTraceModel"
QT_MOC_LITERAL(1405, 20), // "LinBusTraceProperty*"
QT_MOC_LITERAL(1426, 18), // "LinBusMonitorModel"
QT_MOC_LITERAL(1445, 22), // "LinBusMonitorProperty*"
QT_MOC_LITERAL(1468, 16) // "monitorLinScanOn"

    },
    "BusManager\0use_range_changed\0\0"
    "max_TraceItems_Changed\0aux_trace_sizeChanged\0"
    "cdc_trace_emptyChanged\0fd_use_range_changed\0"
    "fd_max_TraceItems_Changed\0"
    "fd_aux_trace_sizeChanged\0"
    "fd_cdc_trace_emptyChanged\0"
    "monitorScanOnChanged\0fd_monitorScanOnChanged\0"
    "monitorLinScanOnChanged\0processIncomingData\0"
    "_data\0fd_processIncomingData\0"
    "processLinIncomingData\0resetCanBusTraceModel\0"
    "fd_resetCanBusTraceModel\0resetLinBusTraceModel\0"
    "setFilterCan\0can_num\0isEnabled\0"
    "setFilterRange\0start\0end\0fd_setFilterCan\0"
    "fd_setFilterRange\0createNewTraceItem\0"
    "newItem\0_default\0saveTrace\0filename\0"
    "loadTrace\0sortTraceColumn\0col\0"
    "fromTopToBottom\0switchSortTraceColumn\0"
    "clearSortTrace\0deleteSelectedTrace\0"
    "deleteRangeTrace\0begin\0setTraceIdDirection\0"
    "id\0can_n\0cropTime\0deleteTimeRangeTrace\0"
    "fd_createNewTraceItem\0fd_saveTrace\0"
    "fd_loadTrace\0fd_sortTraceColumn\0"
    "fd_switchSortTraceColumn\0fd_clearSortTrace\0"
    "fd_deleteSelectedTrace\0fd_deleteRangeTrace\0"
    "fd_setTraceIdDirection\0fd_cropTime\0"
    "fd_deleteTimeRangeTrace\0sortLinTraceColumn\0"
    "switchLinSortTraceColumn\0clearLinSortTrace\0"
    "loadAuxTrace\0fd_loadAuxTrace\0monitorScanOn\0"
    "CanBusTraceModel\0CanBusTraceProperty*\0"
    "max_can_trace_items\0cdc_trace_empty\0"
    "CanBusMonitorModel\0CanBusMonitorProperty*\0"
    "range_id_used\0aux_trace_size\0"
    "fd_monitorScanOn\0FdCanBusTraceModel\0"
    "FDCAN_CanBusTraceProperty*\0"
    "fd_max_can_trace_items\0fd_cdc_trace_empty\0"
    "FdCanBusMonitorModel\0FDCAN_CanBusMonitorProperty*\0"
    "fd_range_id_used\0fd_aux_trace_size\0"
    "LinBusTraceModel\0LinBusTraceProperty*\0"
    "LinBusMonitorModel\0LinBusMonitorProperty*\0"
    "monitorLinScanOn"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BusManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      51,   14, // methods
      17,  465, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  320,    2, 0x06,   18 /* Public */,
       3,    0,  321,    2, 0x06,   19 /* Public */,
       4,    0,  322,    2, 0x06,   20 /* Public */,
       5,    0,  323,    2, 0x06,   21 /* Public */,
       6,    0,  324,    2, 0x06,   22 /* Public */,
       7,    0,  325,    2, 0x06,   23 /* Public */,
       8,    0,  326,    2, 0x06,   24 /* Public */,
       9,    0,  327,    2, 0x06,   25 /* Public */,
      10,    0,  328,    2, 0x06,   26 /* Public */,
      11,    0,  329,    2, 0x06,   27 /* Public */,
      12,    0,  330,    2, 0x06,   28 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      13,    1,  331,    2, 0x0a,   29 /* Public */,
      15,    1,  334,    2, 0x0a,   31 /* Public */,
      16,    1,  337,    2, 0x0a,   33 /* Public */,
      17,    0,  340,    2, 0x0a,   35 /* Public */,
      18,    0,  341,    2, 0x0a,   36 /* Public */,
      19,    0,  342,    2, 0x0a,   37 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      20,    2,  343,    2, 0x02,   38 /* Public */,
      23,    3,  348,    2, 0x02,   41 /* Public */,
      26,    2,  355,    2, 0x02,   45 /* Public */,
      27,    3,  360,    2, 0x02,   48 /* Public */,
      28,    2,  367,    2, 0x02,   52 /* Public */,
      31,    1,  372,    2, 0x02,   55 /* Public */,
      33,    1,  375,    2, 0x02,   57 /* Public */,
      34,    2,  378,    2, 0x02,   59 /* Public */,
      34,    1,  383,    2, 0x22,   62 /* Public | MethodCloned */,
      37,    1,  386,    2, 0x02,   64 /* Public */,
      38,    0,  389,    2, 0x02,   66 /* Public */,
      39,    0,  390,    2, 0x02,   67 /* Public */,
      40,    2,  391,    2, 0x02,   68 /* Public */,
      42,    2,  396,    2, 0x02,   71 /* Public */,
      45,    0,  401,    2, 0x02,   74 /* Public */,
      46,    2,  402,    2, 0x02,   75 /* Public */,
      47,    2,  407,    2, 0x02,   78 /* Public */,
      48,    1,  412,    2, 0x02,   81 /* Public */,
      49,    1,  415,    2, 0x02,   83 /* Public */,
      50,    2,  418,    2, 0x02,   85 /* Public */,
      50,    1,  423,    2, 0x22,   88 /* Public | MethodCloned */,
      51,    1,  426,    2, 0x02,   90 /* Public */,
      52,    0,  429,    2, 0x02,   92 /* Public */,
      53,    0,  430,    2, 0x02,   93 /* Public */,
      54,    2,  431,    2, 0x02,   94 /* Public */,
      55,    2,  436,    2, 0x02,   97 /* Public */,
      56,    0,  441,    2, 0x02,  100 /* Public */,
      57,    2,  442,    2, 0x02,  101 /* Public */,
      58,    2,  447,    2, 0x02,  104 /* Public */,
      58,    1,  452,    2, 0x22,  107 /* Public | MethodCloned */,
      59,    1,  455,    2, 0x02,  109 /* Public */,
      60,    0,  458,    2, 0x02,  111 /* Public */,
      61,    1,  459,    2, 0x02,  112 /* Public */,
      62,    1,  462,    2, 0x02,  114 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool, QMetaType::QByteArray,   14,
    QMetaType::Bool, QMetaType::QByteArray,   14,
    QMetaType::Bool, QMetaType::QByteArray,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   21,   22,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Bool,   24,   25,   22,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   21,   22,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Bool,   24,   25,   22,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   29,   30,
    QMetaType::Void, QMetaType::QString,   32,
    QMetaType::Void, QMetaType::QString,   32,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   35,   36,
    QMetaType::Void, QMetaType::Int,   35,
    QMetaType::Void, QMetaType::Int,   35,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   41,   25,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   43,   44,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   41,   25,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   29,   30,
    QMetaType::Void, QMetaType::QString,   32,
    QMetaType::Void, QMetaType::QString,   32,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   35,   36,
    QMetaType::Void, QMetaType::Int,   35,
    QMetaType::Void, QMetaType::Int,   35,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   41,   25,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   43,   44,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   41,   25,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   35,   36,
    QMetaType::Void, QMetaType::Int,   35,
    QMetaType::Void, QMetaType::Int,   35,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   32,
    QMetaType::Void, QMetaType::QString,   32,

 // properties: name, type, flags
      63, QMetaType::Bool, 0x00015103, uint(8), 0,
      64, 0x80000000 | 65, 0x00015409, uint(-1), 0,
      66, QMetaType::QString, 0x00015003, uint(1), 0,
      67, QMetaType::Bool, 0x00015001, uint(3), 0,
      68, 0x80000000 | 69, 0x00015409, uint(-1), 0,
      70, QMetaType::Bool, 0x00015003, uint(0), 0,
      71, QMetaType::Int, 0x00015001, uint(2), 0,
      72, QMetaType::Bool, 0x00015003, uint(9), 0,
      73, 0x80000000 | 74, 0x00015409, uint(-1), 0,
      75, QMetaType::QString, 0x00015003, uint(5), 0,
      76, QMetaType::Bool, 0x00015001, uint(7), 0,
      77, 0x80000000 | 78, 0x00015409, uint(-1), 0,
      79, QMetaType::Bool, 0x00015003, uint(4), 0,
      80, QMetaType::Int, 0x00015001, uint(6), 0,
      81, 0x80000000 | 82, 0x00015409, uint(-1), 0,
      83, 0x80000000 | 84, 0x00015409, uint(-1), 0,
      85, QMetaType::Bool, 0x00015103, uint(10), 0,

       0        // eod
};

void BusManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BusManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->use_range_changed(); break;
        case 1: _t->max_TraceItems_Changed(); break;
        case 2: _t->aux_trace_sizeChanged(); break;
        case 3: _t->cdc_trace_emptyChanged(); break;
        case 4: _t->fd_use_range_changed(); break;
        case 5: _t->fd_max_TraceItems_Changed(); break;
        case 6: _t->fd_aux_trace_sizeChanged(); break;
        case 7: _t->fd_cdc_trace_emptyChanged(); break;
        case 8: _t->monitorScanOnChanged(); break;
        case 9: _t->fd_monitorScanOnChanged(); break;
        case 10: _t->monitorLinScanOnChanged(); break;
        case 11: { bool _r = _t->processIncomingData((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->fd_processIncomingData((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: { bool _r = _t->processLinIncomingData((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->resetCanBusTraceModel(); break;
        case 15: _t->fd_resetCanBusTraceModel(); break;
        case 16: _t->resetLinBusTraceModel(); break;
        case 17: _t->setFilterCan((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 18: _t->setFilterRange((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3]))); break;
        case 19: _t->fd_setFilterCan((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 20: _t->fd_setFilterRange((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3]))); break;
        case 21: _t->createNewTraceItem((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 22: _t->saveTrace((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 23: _t->loadTrace((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 24: _t->sortTraceColumn((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 25: _t->sortTraceColumn((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 26: _t->switchSortTraceColumn((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 27: _t->clearSortTrace(); break;
        case 28: _t->deleteSelectedTrace(); break;
        case 29: _t->deleteRangeTrace((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 30: _t->setTraceIdDirection((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 31: _t->cropTime(); break;
        case 32: _t->deleteTimeRangeTrace((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 33: _t->fd_createNewTraceItem((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 34: _t->fd_saveTrace((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 35: _t->fd_loadTrace((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 36: _t->fd_sortTraceColumn((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 37: _t->fd_sortTraceColumn((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 38: _t->fd_switchSortTraceColumn((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 39: _t->fd_clearSortTrace(); break;
        case 40: _t->fd_deleteSelectedTrace(); break;
        case 41: _t->fd_deleteRangeTrace((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 42: _t->fd_setTraceIdDirection((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 43: _t->fd_cropTime(); break;
        case 44: _t->fd_deleteTimeRangeTrace((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 45: _t->sortLinTraceColumn((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 46: _t->sortLinTraceColumn((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 47: _t->switchLinSortTraceColumn((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 48: _t->clearLinSortTrace(); break;
        case 49: _t->loadAuxTrace((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 50: _t->fd_loadAuxTrace((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BusManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BusManager::use_range_changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BusManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BusManager::max_TraceItems_Changed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BusManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BusManager::aux_trace_sizeChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (BusManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BusManager::cdc_trace_emptyChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (BusManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BusManager::fd_use_range_changed)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (BusManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BusManager::fd_max_TraceItems_Changed)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (BusManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BusManager::fd_aux_trace_sizeChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (BusManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BusManager::fd_cdc_trace_emptyChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (BusManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BusManager::monitorScanOnChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (BusManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BusManager::fd_monitorScanOnChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (BusManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BusManager::monitorLinScanOnChanged)) {
                *result = 10;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CanBusMonitorProperty* >(); break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CanBusTraceProperty* >(); break;
        case 11:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< FDCAN_CanBusMonitorProperty* >(); break;
        case 8:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< FDCAN_CanBusTraceProperty* >(); break;
        case 15:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< LinBusMonitorProperty* >(); break;
        case 14:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< LinBusTraceProperty* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<BusManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->getMonitorScanOn(); break;
        case 1: *reinterpret_cast< CanBusTraceProperty**>(_v) = _t->CanBusTraceModel(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->max_TraceItems(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->cdc_trace_empty(); break;
        case 4: *reinterpret_cast< CanBusMonitorProperty**>(_v) = _t->CanBusMonitorModel(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->range_id_used(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->aux_trace_size(); break;
        case 7: *reinterpret_cast< bool*>(_v) = _t->fd_getMonitorScanOn(); break;
        case 8: *reinterpret_cast< FDCAN_CanBusTraceProperty**>(_v) = _t->FdCanBusTraceModel(); break;
        case 9: *reinterpret_cast< QString*>(_v) = _t->fd_max_TraceItems(); break;
        case 10: *reinterpret_cast< bool*>(_v) = _t->fd_cdc_trace_empty(); break;
        case 11: *reinterpret_cast< FDCAN_CanBusMonitorProperty**>(_v) = _t->FdCanBusMonitorModel(); break;
        case 12: *reinterpret_cast< bool*>(_v) = _t->fd_range_id_used(); break;
        case 13: *reinterpret_cast< int*>(_v) = _t->fd_aux_trace_size(); break;
        case 14: *reinterpret_cast< LinBusTraceProperty**>(_v) = _t->LinBusTraceModel(); break;
        case 15: *reinterpret_cast< LinBusMonitorProperty**>(_v) = _t->LinBusMonitorModel(); break;
        case 16: *reinterpret_cast< bool*>(_v) = _t->getMonitorLinScanOn(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<BusManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setMonitorScanOn(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setMaxTraceItems(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->set_range_id_used(*reinterpret_cast< bool*>(_v)); break;
        case 7: _t->fd_setMonitorScanOn(*reinterpret_cast< bool*>(_v)); break;
        case 9: _t->fd_setMaxTraceItems(*reinterpret_cast< QString*>(_v)); break;
        case 12: _t->fd_set_range_id_used(*reinterpret_cast< bool*>(_v)); break;
        case 16: _t->setMonitorLinScanOn(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject BusManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_BusManager.offsetsAndSize,
    qt_meta_data_BusManager,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_BusManager_t
, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<CanBusTraceProperty*, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<CanBusMonitorProperty*, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<FDCAN_CanBusTraceProperty*, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<FDCAN_CanBusMonitorProperty*, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<LinBusTraceProperty*, std::true_type>, QtPrivate::TypeAndForceComplete<LinBusMonitorProperty*, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<BusManager, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>

>,
    nullptr
} };


const QMetaObject *BusManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BusManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BusManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BusManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 51)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 51;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 51)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 51;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void BusManager::use_range_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void BusManager::max_TraceItems_Changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void BusManager::aux_trace_sizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void BusManager::cdc_trace_emptyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void BusManager::fd_use_range_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void BusManager::fd_max_TraceItems_Changed()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void BusManager::fd_aux_trace_sizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void BusManager::fd_cdc_trace_emptyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void BusManager::monitorScanOnChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void BusManager::fd_monitorScanOnChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void BusManager::monitorLinScanOnChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
