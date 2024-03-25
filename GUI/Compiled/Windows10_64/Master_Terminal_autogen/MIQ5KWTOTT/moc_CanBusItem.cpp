/****************************************************************************
** Meta object code from reading C++ file 'CanBusItem.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/bus/CanBusItem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CanBusItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CanBusItem_t {
    const uint offsetsAndSize[32];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_CanBusItem_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_CanBusItem_t qt_meta_stringdata_CanBusItem = {
    {
QT_MOC_LITERAL(0, 10), // "CanBusItem"
QT_MOC_LITERAL(11, 17), // "isSelectedChanged"
QT_MOC_LITERAL(29, 0), // ""
QT_MOC_LITERAL(30, 11), // "timeChanged"
QT_MOC_LITERAL(42, 10), // "canChanged"
QT_MOC_LITERAL(53, 9), // "idChanged"
QT_MOC_LITERAL(63, 10), // "dlcChanged"
QT_MOC_LITERAL(74, 11), // "dataChanged"
QT_MOC_LITERAL(86, 10), // "ideChanged"
QT_MOC_LITERAL(97, 4), // "Time"
QT_MOC_LITERAL(102, 3), // "CAN"
QT_MOC_LITERAL(106, 3), // "IDE"
QT_MOC_LITERAL(110, 2), // "ID"
QT_MOC_LITERAL(113, 3), // "DLC"
QT_MOC_LITERAL(117, 4), // "Data"
QT_MOC_LITERAL(122, 10) // "isSelected"

    },
    "CanBusItem\0isSelectedChanged\0\0timeChanged\0"
    "canChanged\0idChanged\0dlcChanged\0"
    "dataChanged\0ideChanged\0Time\0CAN\0IDE\0"
    "ID\0DLC\0Data\0isSelected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CanBusItem[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       7,   63, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x06,    8 /* Public */,
       3,    0,   57,    2, 0x06,    9 /* Public */,
       4,    0,   58,    2, 0x06,   10 /* Public */,
       5,    0,   59,    2, 0x06,   11 /* Public */,
       6,    0,   60,    2, 0x06,   12 /* Public */,
       7,    0,   61,    2, 0x06,   13 /* Public */,
       8,    0,   62,    2, 0x06,   14 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       9, QMetaType::QString, 0x00015103, uint(1), 0,
      10, QMetaType::QString, 0x00015003, uint(2), 0,
      11, QMetaType::QString, 0x00015003, uint(6), 0,
      12, QMetaType::QString, 0x00015003, uint(3), 0,
      13, QMetaType::QString, 0x00015003, uint(4), 0,
      14, QMetaType::QString, 0x00015103, uint(5), 0,
      15, QMetaType::Bool, 0x00015103, uint(0), 0,

       0        // eod
};

void CanBusItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CanBusItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->isSelectedChanged(); break;
        case 1: _t->timeChanged(); break;
        case 2: _t->canChanged(); break;
        case 3: _t->idChanged(); break;
        case 4: _t->dlcChanged(); break;
        case 5: _t->dataChanged(); break;
        case 6: _t->ideChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanBusItem::isSelectedChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanBusItem::timeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanBusItem::canChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanBusItem::idChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanBusItem::dlcChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanBusItem::dataChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (CanBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanBusItem::ideChanged)) {
                *result = 6;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<CanBusItem *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->time(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->can(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->ide(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->id(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->dlc(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->data(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->isSelected(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<CanBusItem *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setTime(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setCan(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setIde(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setId(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setDlc(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setData(*reinterpret_cast< QString*>(_v)); break;
        case 6: _t->setIsSelected(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

const QMetaObject CanBusItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CanBusItem.offsetsAndSize,
    qt_meta_data_CanBusItem,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_CanBusItem_t
, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<CanBusItem, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *CanBusItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CanBusItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CanBusItem.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CanBusItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
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
void CanBusItem::isSelectedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CanBusItem::timeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CanBusItem::canChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CanBusItem::idChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CanBusItem::dlcChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void CanBusItem::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void CanBusItem::ideChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
struct qt_meta_stringdata_CanBusItemMonitor_t {
    const uint offsetsAndSize[30];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_CanBusItemMonitor_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_CanBusItemMonitor_t qt_meta_stringdata_CanBusItemMonitor = {
    {
QT_MOC_LITERAL(0, 17), // "CanBusItemMonitor"
QT_MOC_LITERAL(18, 7), // "changed"
QT_MOC_LITERAL(26, 0), // ""
QT_MOC_LITERAL(27, 10), // "canChanged"
QT_MOC_LITERAL(38, 9), // "idChanged"
QT_MOC_LITERAL(48, 10), // "dlcChanged"
QT_MOC_LITERAL(59, 12), // "countChanged"
QT_MOC_LITERAL(72, 13), // "periodChanged"
QT_MOC_LITERAL(86, 11), // "dataChanged"
QT_MOC_LITERAL(98, 3), // "can"
QT_MOC_LITERAL(102, 2), // "id"
QT_MOC_LITERAL(105, 3), // "dlc"
QT_MOC_LITERAL(109, 5), // "count"
QT_MOC_LITERAL(115, 6), // "period"
QT_MOC_LITERAL(122, 4) // "data"

    },
    "CanBusItemMonitor\0changed\0\0canChanged\0"
    "idChanged\0dlcChanged\0countChanged\0"
    "periodChanged\0dataChanged\0can\0id\0dlc\0"
    "count\0period\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CanBusItemMonitor[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       6,   63, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x06,    7 /* Public */,
       3,    0,   57,    2, 0x06,    8 /* Public */,
       4,    0,   58,    2, 0x06,    9 /* Public */,
       5,    0,   59,    2, 0x06,   10 /* Public */,
       6,    0,   60,    2, 0x06,   11 /* Public */,
       7,    0,   61,    2, 0x06,   12 /* Public */,
       8,    0,   62,    2, 0x06,   13 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       9, QMetaType::QString, 0x00015103, uint(1), 0,
      10, QMetaType::QString, 0x00015103, uint(2), 0,
      11, QMetaType::QString, 0x00015103, uint(3), 0,
      12, QMetaType::QString, 0x00015103, uint(4), 0,
      13, QMetaType::QString, 0x00015103, uint(5), 0,
      14, QMetaType::QString, 0x00015103, uint(6), 0,

       0        // eod
};

void CanBusItemMonitor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CanBusItemMonitor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->canChanged(); break;
        case 2: _t->idChanged(); break;
        case 3: _t->dlcChanged(); break;
        case 4: _t->countChanged(); break;
        case 5: _t->periodChanged(); break;
        case 6: _t->dataChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CanBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanBusItemMonitor::changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CanBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanBusItemMonitor::canChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CanBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanBusItemMonitor::idChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CanBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanBusItemMonitor::dlcChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CanBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanBusItemMonitor::countChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CanBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanBusItemMonitor::periodChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (CanBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CanBusItemMonitor::dataChanged)) {
                *result = 6;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<CanBusItemMonitor *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->can(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->id(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->dlc(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->count(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->period(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->data(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<CanBusItemMonitor *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCan(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setId(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setDlc(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setCount(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setPeriod(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setData(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

const QMetaObject CanBusItemMonitor::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CanBusItemMonitor.offsetsAndSize,
    qt_meta_data_CanBusItemMonitor,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_CanBusItemMonitor_t
, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<CanBusItemMonitor, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *CanBusItemMonitor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CanBusItemMonitor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CanBusItemMonitor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CanBusItemMonitor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void CanBusItemMonitor::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CanBusItemMonitor::canChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CanBusItemMonitor::idChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CanBusItemMonitor::dlcChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CanBusItemMonitor::countChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void CanBusItemMonitor::periodChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void CanBusItemMonitor::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
