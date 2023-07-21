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
    const uint offsetsAndSize[90];
    char stringdata0[635];
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
QT_MOC_LITERAL(98, 20), // "monitorScanOnChanged"
QT_MOC_LITERAL(119, 19), // "processIncomingData"
QT_MOC_LITERAL(139, 5), // "_data"
QT_MOC_LITERAL(145, 21), // "resetCanBusTraceModel"
QT_MOC_LITERAL(167, 12), // "setFilterCan"
QT_MOC_LITERAL(180, 7), // "can_num"
QT_MOC_LITERAL(188, 9), // "isEnabled"
QT_MOC_LITERAL(198, 14), // "setFilterRange"
QT_MOC_LITERAL(213, 5), // "start"
QT_MOC_LITERAL(219, 3), // "end"
QT_MOC_LITERAL(223, 18), // "createNewTraceItem"
QT_MOC_LITERAL(242, 7), // "newItem"
QT_MOC_LITERAL(250, 8), // "_default"
QT_MOC_LITERAL(259, 9), // "saveTrace"
QT_MOC_LITERAL(269, 8), // "filename"
QT_MOC_LITERAL(278, 9), // "loadTrace"
QT_MOC_LITERAL(288, 15), // "sortTraceColumn"
QT_MOC_LITERAL(304, 3), // "col"
QT_MOC_LITERAL(308, 15), // "fromTopToBottom"
QT_MOC_LITERAL(324, 21), // "switchSortTraceColumn"
QT_MOC_LITERAL(346, 14), // "clearSortTrace"
QT_MOC_LITERAL(361, 19), // "deleteSelectedTrace"
QT_MOC_LITERAL(381, 16), // "deleteRangeTrace"
QT_MOC_LITERAL(398, 5), // "begin"
QT_MOC_LITERAL(404, 19), // "setTraceIdDirection"
QT_MOC_LITERAL(424, 2), // "id"
QT_MOC_LITERAL(427, 5), // "can_n"
QT_MOC_LITERAL(433, 8), // "cropTime"
QT_MOC_LITERAL(442, 20), // "deleteTimeRangeTrace"
QT_MOC_LITERAL(463, 12), // "loadAuxTrace"
QT_MOC_LITERAL(476, 13), // "monitorScanOn"
QT_MOC_LITERAL(490, 16), // "CanBusTraceModel"
QT_MOC_LITERAL(507, 20), // "CanBusTraceProperty*"
QT_MOC_LITERAL(528, 19), // "max_can_trace_items"
QT_MOC_LITERAL(548, 15), // "cdc_trace_empty"
QT_MOC_LITERAL(564, 18), // "CanBusMonitorModel"
QT_MOC_LITERAL(583, 22), // "CanBusMonitorProperty*"
QT_MOC_LITERAL(606, 13), // "range_id_used"
QT_MOC_LITERAL(620, 14) // "aux_trace_size"

    },
    "BusManager\0use_range_changed\0\0"
    "max_TraceItems_Changed\0aux_trace_sizeChanged\0"
    "cdc_trace_emptyChanged\0monitorScanOnChanged\0"
    "processIncomingData\0_data\0"
    "resetCanBusTraceModel\0setFilterCan\0"
    "can_num\0isEnabled\0setFilterRange\0start\0"
    "end\0createNewTraceItem\0newItem\0_default\0"
    "saveTrace\0filename\0loadTrace\0"
    "sortTraceColumn\0col\0fromTopToBottom\0"
    "switchSortTraceColumn\0clearSortTrace\0"
    "deleteSelectedTrace\0deleteRangeTrace\0"
    "begin\0setTraceIdDirection\0id\0can_n\0"
    "cropTime\0deleteTimeRangeTrace\0"
    "loadAuxTrace\0monitorScanOn\0CanBusTraceModel\0"
    "CanBusTraceProperty*\0max_can_trace_items\0"
    "cdc_trace_empty\0CanBusMonitorModel\0"
    "CanBusMonitorProperty*\0range_id_used\0"
    "aux_trace_size"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BusManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       7,  210, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  146,    2, 0x06,    8 /* Public */,
       3,    0,  147,    2, 0x06,    9 /* Public */,
       4,    0,  148,    2, 0x06,   10 /* Public */,
       5,    0,  149,    2, 0x06,   11 /* Public */,
       6,    0,  150,    2, 0x06,   12 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    1,  151,    2, 0x0a,   13 /* Public */,
       9,    0,  154,    2, 0x0a,   15 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      10,    2,  155,    2, 0x02,   16 /* Public */,
      13,    3,  160,    2, 0x02,   19 /* Public */,
      16,    2,  167,    2, 0x02,   23 /* Public */,
      19,    1,  172,    2, 0x02,   26 /* Public */,
      21,    1,  175,    2, 0x02,   28 /* Public */,
      22,    2,  178,    2, 0x02,   30 /* Public */,
      22,    1,  183,    2, 0x22,   33 /* Public | MethodCloned */,
      25,    1,  186,    2, 0x02,   35 /* Public */,
      26,    0,  189,    2, 0x02,   37 /* Public */,
      27,    0,  190,    2, 0x02,   38 /* Public */,
      28,    2,  191,    2, 0x02,   39 /* Public */,
      30,    2,  196,    2, 0x02,   42 /* Public */,
      33,    0,  201,    2, 0x02,   45 /* Public */,
      34,    2,  202,    2, 0x02,   46 /* Public */,
      35,    1,  207,    2, 0x02,   49 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool, QMetaType::QByteArray,    8,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   11,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Bool,   14,   15,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   17,   18,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   23,   24,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   29,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   31,   32,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   29,   15,
    QMetaType::Void, QMetaType::QString,   20,

 // properties: name, type, flags
      36, QMetaType::Bool, 0x00015103, uint(4), 0,
      37, 0x80000000 | 38, 0x00015409, uint(-1), 0,
      39, QMetaType::QString, 0x00015003, uint(1), 0,
      40, QMetaType::Bool, 0x00015001, uint(3), 0,
      41, 0x80000000 | 42, 0x00015409, uint(-1), 0,
      43, QMetaType::Bool, 0x00015003, uint(0), 0,
      44, QMetaType::Int, 0x00015001, uint(2), 0,

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
        case 4: _t->monitorScanOnChanged(); break;
        case 5: { bool _r = _t->processIncomingData((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->resetCanBusTraceModel(); break;
        case 7: _t->setFilterCan((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 8: _t->setFilterRange((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3]))); break;
        case 9: _t->createNewTraceItem((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 10: _t->saveTrace((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->loadTrace((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->sortTraceColumn((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 13: _t->sortTraceColumn((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->switchSortTraceColumn((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 15: _t->clearSortTrace(); break;
        case 16: _t->deleteSelectedTrace(); break;
        case 17: _t->deleteRangeTrace((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 18: _t->setTraceIdDirection((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 19: _t->cropTime(); break;
        case 20: _t->deleteTimeRangeTrace((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 21: _t->loadAuxTrace((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BusManager::monitorScanOnChanged)) {
                *result = 4;
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
, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<CanBusTraceProperty*, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<CanBusMonitorProperty*, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<BusManager, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>

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
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 22;
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
void BusManager::monitorScanOnChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
