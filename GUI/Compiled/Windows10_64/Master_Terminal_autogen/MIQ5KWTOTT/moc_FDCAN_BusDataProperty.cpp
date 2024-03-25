/****************************************************************************
** Meta object code from reading C++ file 'FDCAN_BusDataProperty.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/bus/FDCAN_BusDataProperty.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FDCAN_BusDataProperty.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FDCAN_CanBusTraceProperty_t {
    const uint offsetsAndSize[20];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_FDCAN_CanBusTraceProperty_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_FDCAN_CanBusTraceProperty_t qt_meta_stringdata_FDCAN_CanBusTraceProperty = {
    {
QT_MOC_LITERAL(0, 25), // "FDCAN_CanBusTraceProperty"
QT_MOC_LITERAL(26, 7), // "changed"
QT_MOC_LITERAL(34, 0), // ""
QT_MOC_LITERAL(35, 12), // "b_isSelected"
QT_MOC_LITERAL(48, 1), // "i"
QT_MOC_LITERAL(50, 6), // "getCan"
QT_MOC_LITERAL(57, 9), // "getIntDlc"
QT_MOC_LITERAL(67, 4), // "item"
QT_MOC_LITERAL(72, 6), // "length"
QT_MOC_LITERAL(79, 7) // "isEmpty"

    },
    "FDCAN_CanBusTraceProperty\0changed\0\0"
    "b_isSelected\0i\0getCan\0getIntDlc\0item\0"
    "length\0isEmpty"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FDCAN_CanBusTraceProperty[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       2,   57, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x06,    3 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,   45,    2, 0x102,    4 /* Public | MethodIsConst  */,
       5,    1,   48,    2, 0x102,    6 /* Public | MethodIsConst  */,
       6,    1,   51,    2, 0x102,    8 /* Public | MethodIsConst  */,
       7,    1,   54,    2, 0x02,   10 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Bool, QMetaType::Int,    4,
    QMetaType::QString, QMetaType::Int,    4,
    QMetaType::Int, QMetaType::Int,    4,
    QMetaType::QVariant, QMetaType::Int,    4,

 // properties: name, type, flags
       8, QMetaType::Int, 0x00015001, uint(0), 0,
       9, QMetaType::Int, 0x00015001, uint(0), 0,

       0        // eod
};

void FDCAN_CanBusTraceProperty::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FDCAN_CanBusTraceProperty *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: { bool _r = _t->b_isSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { QString _r = _t->getCan((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 3: { int _r = _t->getIntDlc((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: { QVariant _r = _t->item((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FDCAN_CanBusTraceProperty::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusTraceProperty::changed)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FDCAN_CanBusTraceProperty *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->count(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->isEmpty(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject FDCAN_CanBusTraceProperty::staticMetaObject = { {
    QMetaObject::SuperData::link<Obj_List_Model<FDCAN_CanBusItem>::staticMetaObject>(),
    qt_meta_stringdata_FDCAN_CanBusTraceProperty.offsetsAndSize,
    qt_meta_data_FDCAN_CanBusTraceProperty,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_FDCAN_CanBusTraceProperty_t
, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<FDCAN_CanBusTraceProperty, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<const QString, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<QVariant, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>

>,
    nullptr
} };


const QMetaObject *FDCAN_CanBusTraceProperty::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FDCAN_CanBusTraceProperty::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FDCAN_CanBusTraceProperty.stringdata0))
        return static_cast<void*>(this);
    return Obj_List_Model<FDCAN_CanBusItem>::qt_metacast(_clname);
}

int FDCAN_CanBusTraceProperty::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Obj_List_Model<FDCAN_CanBusItem>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void FDCAN_CanBusTraceProperty::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_FDCAN_CanBusMonitorProperty_t {
    const uint offsetsAndSize[14];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_FDCAN_CanBusMonitorProperty_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_FDCAN_CanBusMonitorProperty_t qt_meta_stringdata_FDCAN_CanBusMonitorProperty = {
    {
QT_MOC_LITERAL(0, 27), // "FDCAN_CanBusMonitorProperty"
QT_MOC_LITERAL(28, 7), // "changed"
QT_MOC_LITERAL(36, 0), // ""
QT_MOC_LITERAL(37, 4), // "item"
QT_MOC_LITERAL(42, 1), // "i"
QT_MOC_LITERAL(44, 6), // "length"
QT_MOC_LITERAL(51, 7) // "isEmpty"

    },
    "FDCAN_CanBusMonitorProperty\0changed\0"
    "\0item\0i\0length\0isEmpty"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FDCAN_CanBusMonitorProperty[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       2,   30, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   26,    2, 0x06,    3 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,   27,    2, 0x02,    4 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::QVariant, QMetaType::Int,    4,

 // properties: name, type, flags
       5, QMetaType::Int, 0x00015001, uint(0), 0,
       6, QMetaType::Int, 0x00015001, uint(0), 0,

       0        // eod
};

void FDCAN_CanBusMonitorProperty::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FDCAN_CanBusMonitorProperty *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: { QVariant _r = _t->item((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FDCAN_CanBusMonitorProperty::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FDCAN_CanBusMonitorProperty::changed)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FDCAN_CanBusMonitorProperty *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->count(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->isEmpty(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject FDCAN_CanBusMonitorProperty::staticMetaObject = { {
    QMetaObject::SuperData::link<Obj_List_Model<FDCAN_CanBusItemMonitor>::staticMetaObject>(),
    qt_meta_stringdata_FDCAN_CanBusMonitorProperty.offsetsAndSize,
    qt_meta_data_FDCAN_CanBusMonitorProperty,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_FDCAN_CanBusMonitorProperty_t
, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<FDCAN_CanBusMonitorProperty, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

, QtPrivate::TypeAndForceComplete<QVariant, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>

>,
    nullptr
} };


const QMetaObject *FDCAN_CanBusMonitorProperty::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FDCAN_CanBusMonitorProperty::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FDCAN_CanBusMonitorProperty.stringdata0))
        return static_cast<void*>(this);
    return Obj_List_Model<FDCAN_CanBusItemMonitor>::qt_metacast(_clname);
}

int FDCAN_CanBusMonitorProperty::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Obj_List_Model<FDCAN_CanBusItemMonitor>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void FDCAN_CanBusMonitorProperty::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
