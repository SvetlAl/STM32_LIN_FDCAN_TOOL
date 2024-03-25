/****************************************************************************
** Meta object code from reading C++ file 'FDCAN_CanBusItem.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/bus/FDCAN_CanBusItem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FDCAN_CanBusItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FDCAN_CanBusItem_t {
    const uint offsetsAndSize[52];
    char stringdata0[262];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_FDCAN_CanBusItem_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_FDCAN_CanBusItem_t qt_meta_stringdata_FDCAN_CanBusItem = {
    {
QT_MOC_LITERAL(0, 16), // "FDCAN_CanBusItem"
QT_MOC_LITERAL(17, 17), // "isSelectedChanged"
QT_MOC_LITERAL(35, 0), // ""
QT_MOC_LITERAL(36, 16), // "byteCountChanged"
QT_MOC_LITERAL(53, 11), // "timeChanged"
QT_MOC_LITERAL(65, 10), // "canChanged"
QT_MOC_LITERAL(76, 9), // "idChanged"
QT_MOC_LITERAL(86, 10), // "dlcChanged"
QT_MOC_LITERAL(97, 11), // "dataChanged"
QT_MOC_LITERAL(109, 14), // "ESIflagChanged"
QT_MOC_LITERAL(124, 14), // "XTDflagChanged"
QT_MOC_LITERAL(139, 14), // "FDFflagChanged"
QT_MOC_LITERAL(154, 14), // "BRSflagChanged"
QT_MOC_LITERAL(169, 12), // "colorChanged"
QT_MOC_LITERAL(182, 4), // "Time"
QT_MOC_LITERAL(187, 3), // "CAN"
QT_MOC_LITERAL(191, 2), // "ID"
QT_MOC_LITERAL(194, 3), // "DLC"
QT_MOC_LITERAL(198, 9), // "ByteCount"
QT_MOC_LITERAL(208, 7), // "ESIflag"
QT_MOC_LITERAL(216, 7), // "XTDflag"
QT_MOC_LITERAL(224, 7), // "FDFflag"
QT_MOC_LITERAL(232, 7), // "BRSflag"
QT_MOC_LITERAL(240, 4), // "Data"
QT_MOC_LITERAL(245, 10), // "isSelected"
QT_MOC_LITERAL(256, 5) // "Color"

    },
    "FDCAN_CanBusItem\0isSelectedChanged\0\0"
    "byteCountChanged\0timeChanged\0canChanged\0"
    "idChanged\0dlcChanged\0dataChanged\0"
    "ESIflagChanged\0XTDflagChanged\0"
    "FDFflagChanged\0BRSflagChanged\0"
    "colorChanged\0Time\0CAN\0ID\0DLC\0ByteCount\0"
    "ESIflag\0XTDflag\0FDFflag\0BRSflag\0Data\0"
    "isSelected\0Color"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FDCAN_CanBusItem[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
      12,   98, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x06,   13 /* Public */,
       3,    0,   87,    2, 0x06,   14 /* Public */,
       4,    0,   88,    2, 0x06,   15 /* Public */,
       5,    0,   89,    2, 0x06,   16 /* Public */,
       6,    0,   90,    2, 0x06,   17 /* Public */,
       7,    0,   91,    2, 0x06,   18 /* Public */,
       8,    0,   92,    2, 0x06,   19 /* Public */,
       9,    0,   93,    2, 0x06,   20 /* Public */,
      10,    0,   94,    2, 0x06,   21 /* Public */,
      11,    0,   95,    2, 0x06,   22 /* Public */,
      12,    0,   96,    2, 0x06,   23 /* Public */,
      13,    0,   97,    2, 0x06,   24 /* Public */,

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
    QMetaType::Void,

 // properties: name, type, flags
      14, QMetaType::QString, 0x00015103, uint(2), 0,
      15, QMetaType::QString, 0x00015003, uint(3), 0,
      16, QMetaType::QString, 0x00015003, uint(4), 0,
      17, QMetaType::QString, 0x00015003, uint(5), 0,
      18, QMetaType::Int, 0x00015001, uint(1), 0,
      19, QMetaType::QString, 0x00015103, uint(7), 0,
      20, QMetaType::QString, 0x00015103, uint(8), 0,
      21, QMetaType::QString, 0x00015103, uint(9), 0,
      22, QMetaType::QString, 0x00015103, uint(10), 0,
      23, QMetaType::QString, 0x00015103, uint(6), 0,
      24, QMetaType::Bool, 0x00015103, uint(0), 0,
      25, QMetaType::QString, 0x00015001, uint(11), 0,

       0        // eod
};

void FDCAN_CanBusItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FDCAN_CanBusItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->isSelectedChanged(); break;
        case 1: _t->byteCountChanged(); break;
        case 2: _t->timeChanged(); break;
        case 3: _t->canChanged(); break;
        case 4: _t->idChanged(); break;
        case 5: _t->dlcChanged(); break;
        case 6: _t->dataChanged(); break;
        case 7: _t->ESIflagChanged(); break;
        case 8: _t->XTDflagChanged(); break;
        case 9: _t->FDFflagChanged(); break;
        case 10: _t->BRSflagChanged(); break;
        case 11: _t->colorChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FDCAN_CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItem::isSelectedChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItem::byteCountChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItem::timeChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItem::canChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItem::idChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItem::dlcChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItem::dataChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItem::ESIflagChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItem::XTDflagChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItem::FDFflagChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItem::BRSflagChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItem::colorChanged)) {
                *result = 11;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FDCAN_CanBusItem *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->time(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->can(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->id(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->dlc(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->ByteCount(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->ESIflag(); break;
        case 6: *reinterpret_cast< QString*>(_v) = _t->XTDflag(); break;
        case 7: *reinterpret_cast< QString*>(_v) = _t->FDFflag(); break;
        case 8: *reinterpret_cast< QString*>(_v) = _t->BRSflag(); break;
        case 9: *reinterpret_cast< QString*>(_v) = _t->data(); break;
        case 10: *reinterpret_cast< bool*>(_v) = _t->isSelected(); break;
        case 11: *reinterpret_cast< QString*>(_v) = _t->color(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<FDCAN_CanBusItem *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setTime(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setCan(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setId(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setDlc(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setESIflag(*reinterpret_cast< QString*>(_v)); break;
        case 6: _t->setXTDflag(*reinterpret_cast< QString*>(_v)); break;
        case 7: _t->setFDFflag(*reinterpret_cast< QString*>(_v)); break;
        case 8: _t->setBRSflag(*reinterpret_cast< QString*>(_v)); break;
        case 9: _t->setData(*reinterpret_cast< QString*>(_v)); break;
        case 10: _t->setIsSelected(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

const QMetaObject FDCAN_CanBusItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_FDCAN_CanBusItem.offsetsAndSize,
    qt_meta_data_FDCAN_CanBusItem,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_FDCAN_CanBusItem_t
, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<FDCAN_CanBusItem, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *FDCAN_CanBusItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FDCAN_CanBusItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FDCAN_CanBusItem.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FDCAN_CanBusItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void FDCAN_CanBusItem::isSelectedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void FDCAN_CanBusItem::byteCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void FDCAN_CanBusItem::timeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void FDCAN_CanBusItem::canChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void FDCAN_CanBusItem::idChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void FDCAN_CanBusItem::dlcChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void FDCAN_CanBusItem::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void FDCAN_CanBusItem::ESIflagChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void FDCAN_CanBusItem::XTDflagChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void FDCAN_CanBusItem::FDFflagChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void FDCAN_CanBusItem::BRSflagChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void FDCAN_CanBusItem::colorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}
struct qt_meta_stringdata_FDCAN_CanBusItemMonitor_t {
    const uint offsetsAndSize[38];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_FDCAN_CanBusItemMonitor_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_FDCAN_CanBusItemMonitor_t qt_meta_stringdata_FDCAN_CanBusItemMonitor = {
    {
QT_MOC_LITERAL(0, 23), // "FDCAN_CanBusItemMonitor"
QT_MOC_LITERAL(24, 7), // "changed"
QT_MOC_LITERAL(32, 0), // ""
QT_MOC_LITERAL(33, 10), // "canChanged"
QT_MOC_LITERAL(44, 9), // "idChanged"
QT_MOC_LITERAL(54, 10), // "dlcChanged"
QT_MOC_LITERAL(65, 12), // "countChanged"
QT_MOC_LITERAL(78, 13), // "periodChanged"
QT_MOC_LITERAL(92, 11), // "dataChanged"
QT_MOC_LITERAL(104, 12), // "flagsChanged"
QT_MOC_LITERAL(117, 16), // "byteCountChanged"
QT_MOC_LITERAL(134, 3), // "can"
QT_MOC_LITERAL(138, 2), // "id"
QT_MOC_LITERAL(141, 3), // "dlc"
QT_MOC_LITERAL(145, 5), // "count"
QT_MOC_LITERAL(151, 6), // "period"
QT_MOC_LITERAL(158, 4), // "data"
QT_MOC_LITERAL(163, 5), // "flags"
QT_MOC_LITERAL(169, 9) // "ByteCount"

    },
    "FDCAN_CanBusItemMonitor\0changed\0\0"
    "canChanged\0idChanged\0dlcChanged\0"
    "countChanged\0periodChanged\0dataChanged\0"
    "flagsChanged\0byteCountChanged\0can\0id\0"
    "dlc\0count\0period\0data\0flags\0ByteCount"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FDCAN_CanBusItemMonitor[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       8,   77, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x06,    9 /* Public */,
       3,    0,   69,    2, 0x06,   10 /* Public */,
       4,    0,   70,    2, 0x06,   11 /* Public */,
       5,    0,   71,    2, 0x06,   12 /* Public */,
       6,    0,   72,    2, 0x06,   13 /* Public */,
       7,    0,   73,    2, 0x06,   14 /* Public */,
       8,    0,   74,    2, 0x06,   15 /* Public */,
       9,    0,   75,    2, 0x06,   16 /* Public */,
      10,    0,   76,    2, 0x06,   17 /* Public */,

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

 // properties: name, type, flags
      11, QMetaType::QString, 0x00015103, uint(1), 0,
      12, QMetaType::QString, 0x00015103, uint(2), 0,
      13, QMetaType::QString, 0x00015103, uint(3), 0,
      14, QMetaType::QString, 0x00015103, uint(4), 0,
      15, QMetaType::QString, 0x00015103, uint(5), 0,
      16, QMetaType::QString, 0x00015103, uint(6), 0,
      17, QMetaType::QString, 0x00015103, uint(7), 0,
      18, QMetaType::Int, 0x00015001, uint(8), 0,

       0        // eod
};

void FDCAN_CanBusItemMonitor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FDCAN_CanBusItemMonitor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->canChanged(); break;
        case 2: _t->idChanged(); break;
        case 3: _t->dlcChanged(); break;
        case 4: _t->countChanged(); break;
        case 5: _t->periodChanged(); break;
        case 6: _t->dataChanged(); break;
        case 7: _t->flagsChanged(); break;
        case 8: _t->byteCountChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FDCAN_CanBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItemMonitor::changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItemMonitor::canChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItemMonitor::idChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItemMonitor::dlcChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItemMonitor::countChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItemMonitor::periodChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItemMonitor::dataChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItemMonitor::flagsChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (FDCAN_CanBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusItemMonitor::byteCountChanged)) {
                *result = 8;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FDCAN_CanBusItemMonitor *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->can(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->id(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->dlc(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->count(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->period(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->data(); break;
        case 6: *reinterpret_cast< QString*>(_v) = _t->flags(); break;
        case 7: *reinterpret_cast< int*>(_v) = _t->ByteCount(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<FDCAN_CanBusItemMonitor *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCan(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setId(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setDlc(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setCount(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setPeriod(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setData(*reinterpret_cast< QString*>(_v)); break;
        case 6: _t->setFlags(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

const QMetaObject FDCAN_CanBusItemMonitor::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_FDCAN_CanBusItemMonitor.offsetsAndSize,
    qt_meta_data_FDCAN_CanBusItemMonitor,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_FDCAN_CanBusItemMonitor_t
, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<FDCAN_CanBusItemMonitor, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *FDCAN_CanBusItemMonitor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FDCAN_CanBusItemMonitor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FDCAN_CanBusItemMonitor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FDCAN_CanBusItemMonitor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void FDCAN_CanBusItemMonitor::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void FDCAN_CanBusItemMonitor::canChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void FDCAN_CanBusItemMonitor::idChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void FDCAN_CanBusItemMonitor::dlcChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void FDCAN_CanBusItemMonitor::countChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void FDCAN_CanBusItemMonitor::periodChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void FDCAN_CanBusItemMonitor::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void FDCAN_CanBusItemMonitor::flagsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void FDCAN_CanBusItemMonitor::byteCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
