/****************************************************************************
** Meta object code from reading C++ file 'LinBusItem.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/bus/LinBusItem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LinBusItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LinBusItem_t {
    const uint offsetsAndSize[26];
    char stringdata0[113];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_LinBusItem_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_LinBusItem_t qt_meta_stringdata_LinBusItem = {
    {
QT_MOC_LITERAL(0, 10), // "LinBusItem"
QT_MOC_LITERAL(11, 17), // "isSelectedChanged"
QT_MOC_LITERAL(29, 0), // ""
QT_MOC_LITERAL(30, 11), // "timeChanged"
QT_MOC_LITERAL(42, 10), // "linChanged"
QT_MOC_LITERAL(53, 9), // "idChanged"
QT_MOC_LITERAL(63, 13), // "lengthChanged"
QT_MOC_LITERAL(77, 11), // "dataChanged"
QT_MOC_LITERAL(89, 4), // "Time"
QT_MOC_LITERAL(94, 3), // "LIN"
QT_MOC_LITERAL(98, 2), // "ID"
QT_MOC_LITERAL(101, 6), // "Length"
QT_MOC_LITERAL(108, 4) // "Data"

    },
    "LinBusItem\0isSelectedChanged\0\0timeChanged\0"
    "linChanged\0idChanged\0lengthChanged\0"
    "dataChanged\0Time\0LIN\0ID\0Length\0Data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LinBusItem[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       5,   56, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    6 /* Public */,
       3,    0,   51,    2, 0x06,    7 /* Public */,
       4,    0,   52,    2, 0x06,    8 /* Public */,
       5,    0,   53,    2, 0x06,    9 /* Public */,
       6,    0,   54,    2, 0x06,   10 /* Public */,
       7,    0,   55,    2, 0x06,   11 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       8, QMetaType::QString, 0x00015103, uint(1), 0,
       9, QMetaType::QString, 0x00015003, uint(2), 0,
      10, QMetaType::QString, 0x00015003, uint(3), 0,
      11, QMetaType::QString, 0x00015103, uint(4), 0,
      12, QMetaType::QString, 0x00015103, uint(5), 0,

       0        // eod
};

void LinBusItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LinBusItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->isSelectedChanged(); break;
        case 1: _t->timeChanged(); break;
        case 2: _t->linChanged(); break;
        case 3: _t->idChanged(); break;
        case 4: _t->lengthChanged(); break;
        case 5: _t->dataChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LinBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinBusItem::isSelectedChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LinBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinBusItem::timeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LinBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinBusItem::linChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (LinBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinBusItem::idChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (LinBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinBusItem::lengthChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (LinBusItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinBusItem::dataChanged)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<LinBusItem *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->time(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->lin(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->id(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->length(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->data(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<LinBusItem *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setTime(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setLin(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setId(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setLength(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setData(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

const QMetaObject LinBusItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_LinBusItem.offsetsAndSize,
    qt_meta_data_LinBusItem,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_LinBusItem_t
, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<LinBusItem, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *LinBusItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LinBusItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LinBusItem.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LinBusItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void LinBusItem::isSelectedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LinBusItem::timeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void LinBusItem::linChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void LinBusItem::idChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void LinBusItem::lengthChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void LinBusItem::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
struct qt_meta_stringdata_LinBusItemMonitor_t {
    const uint offsetsAndSize[30];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_LinBusItemMonitor_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_LinBusItemMonitor_t qt_meta_stringdata_LinBusItemMonitor = {
    {
QT_MOC_LITERAL(0, 17), // "LinBusItemMonitor"
QT_MOC_LITERAL(18, 7), // "changed"
QT_MOC_LITERAL(26, 0), // ""
QT_MOC_LITERAL(27, 10), // "linChanged"
QT_MOC_LITERAL(38, 9), // "idChanged"
QT_MOC_LITERAL(48, 13), // "lengthChanged"
QT_MOC_LITERAL(62, 12), // "countChanged"
QT_MOC_LITERAL(75, 13), // "periodChanged"
QT_MOC_LITERAL(89, 11), // "dataChanged"
QT_MOC_LITERAL(101, 3), // "lin"
QT_MOC_LITERAL(105, 2), // "id"
QT_MOC_LITERAL(108, 6), // "length"
QT_MOC_LITERAL(115, 5), // "count"
QT_MOC_LITERAL(121, 6), // "period"
QT_MOC_LITERAL(128, 4) // "data"

    },
    "LinBusItemMonitor\0changed\0\0linChanged\0"
    "idChanged\0lengthChanged\0countChanged\0"
    "periodChanged\0dataChanged\0lin\0id\0"
    "length\0count\0period\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LinBusItemMonitor[] = {

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

void LinBusItemMonitor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LinBusItemMonitor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->linChanged(); break;
        case 2: _t->idChanged(); break;
        case 3: _t->lengthChanged(); break;
        case 4: _t->countChanged(); break;
        case 5: _t->periodChanged(); break;
        case 6: _t->dataChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LinBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinBusItemMonitor::changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LinBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinBusItemMonitor::linChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LinBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinBusItemMonitor::idChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (LinBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinBusItemMonitor::lengthChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (LinBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinBusItemMonitor::countChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (LinBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinBusItemMonitor::periodChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (LinBusItemMonitor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinBusItemMonitor::dataChanged)) {
                *result = 6;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<LinBusItemMonitor *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->lin(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->id(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->length(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->count(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->period(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->data(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<LinBusItemMonitor *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setLin(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setId(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setLength(*reinterpret_cast< QString*>(_v)); break;
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

const QMetaObject LinBusItemMonitor::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_LinBusItemMonitor.offsetsAndSize,
    qt_meta_data_LinBusItemMonitor,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_LinBusItemMonitor_t
, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<LinBusItemMonitor, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *LinBusItemMonitor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LinBusItemMonitor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LinBusItemMonitor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LinBusItemMonitor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void LinBusItemMonitor::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LinBusItemMonitor::linChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void LinBusItemMonitor::idChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void LinBusItemMonitor::lengthChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void LinBusItemMonitor::countChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void LinBusItemMonitor::periodChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void LinBusItemMonitor::dataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
