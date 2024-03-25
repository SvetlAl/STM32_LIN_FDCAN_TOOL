/****************************************************************************
** Meta object code from reading C++ file 'LinBusDataProperty.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/bus/LinBusDataProperty.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LinBusDataProperty.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LinBusTraceProperty_t {
    const uint offsetsAndSize[18];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_LinBusTraceProperty_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_LinBusTraceProperty_t qt_meta_stringdata_LinBusTraceProperty = {
    {
QT_MOC_LITERAL(0, 19), // "LinBusTraceProperty"
QT_MOC_LITERAL(20, 7), // "changed"
QT_MOC_LITERAL(28, 0), // ""
QT_MOC_LITERAL(29, 12), // "b_isSelected"
QT_MOC_LITERAL(42, 1), // "i"
QT_MOC_LITERAL(44, 6), // "getLin"
QT_MOC_LITERAL(51, 4), // "item"
QT_MOC_LITERAL(56, 6), // "length"
QT_MOC_LITERAL(63, 7) // "isEmpty"

    },
    "LinBusTraceProperty\0changed\0\0b_isSelected\0"
    "i\0getLin\0item\0length\0isEmpty"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LinBusTraceProperty[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       2,   48, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x06,    3 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,   39,    2, 0x102,    4 /* Public | MethodIsConst  */,
       5,    1,   42,    2, 0x102,    6 /* Public | MethodIsConst  */,
       6,    1,   45,    2, 0x02,    8 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Bool, QMetaType::Int,    4,
    QMetaType::QString, QMetaType::Int,    4,
    QMetaType::QVariant, QMetaType::Int,    4,

 // properties: name, type, flags
       7, QMetaType::Int, 0x00015001, uint(0), 0,
       8, QMetaType::Int, 0x00015001, uint(0), 0,

       0        // eod
};

void LinBusTraceProperty::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LinBusTraceProperty *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: { bool _r = _t->b_isSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { QString _r = _t->getLin((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 3: { QVariant _r = _t->item((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LinBusTraceProperty::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinBusTraceProperty::changed)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<LinBusTraceProperty *>(_o);
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

const QMetaObject LinBusTraceProperty::staticMetaObject = { {
    QMetaObject::SuperData::link<Obj_List_Model<LinBusItem>::staticMetaObject>(),
    qt_meta_stringdata_LinBusTraceProperty.offsetsAndSize,
    qt_meta_data_LinBusTraceProperty,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_LinBusTraceProperty_t
, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<LinBusTraceProperty, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<const QString, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<QVariant, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>

>,
    nullptr
} };


const QMetaObject *LinBusTraceProperty::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LinBusTraceProperty::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LinBusTraceProperty.stringdata0))
        return static_cast<void*>(this);
    return Obj_List_Model<LinBusItem>::qt_metacast(_clname);
}

int LinBusTraceProperty::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Obj_List_Model<LinBusItem>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
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
void LinBusTraceProperty::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_LinBusMonitorProperty_t {
    const uint offsetsAndSize[14];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_LinBusMonitorProperty_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_LinBusMonitorProperty_t qt_meta_stringdata_LinBusMonitorProperty = {
    {
QT_MOC_LITERAL(0, 21), // "LinBusMonitorProperty"
QT_MOC_LITERAL(22, 7), // "changed"
QT_MOC_LITERAL(30, 0), // ""
QT_MOC_LITERAL(31, 4), // "item"
QT_MOC_LITERAL(36, 1), // "i"
QT_MOC_LITERAL(38, 6), // "length"
QT_MOC_LITERAL(45, 7) // "isEmpty"

    },
    "LinBusMonitorProperty\0changed\0\0item\0"
    "i\0length\0isEmpty"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LinBusMonitorProperty[] = {

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

void LinBusMonitorProperty::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LinBusMonitorProperty *>(_o);
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
            using _t = void (LinBusMonitorProperty::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LinBusMonitorProperty::changed)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<LinBusMonitorProperty *>(_o);
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

const QMetaObject LinBusMonitorProperty::staticMetaObject = { {
    QMetaObject::SuperData::link<Obj_List_Model<LinBusItemMonitor>::staticMetaObject>(),
    qt_meta_stringdata_LinBusMonitorProperty.offsetsAndSize,
    qt_meta_data_LinBusMonitorProperty,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_LinBusMonitorProperty_t
, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<LinBusMonitorProperty, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

, QtPrivate::TypeAndForceComplete<QVariant, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>

>,
    nullptr
} };


const QMetaObject *LinBusMonitorProperty::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LinBusMonitorProperty::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LinBusMonitorProperty.stringdata0))
        return static_cast<void*>(this);
    return Obj_List_Model<LinBusItemMonitor>::qt_metacast(_clname);
}

int LinBusMonitorProperty::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Obj_List_Model<LinBusItemMonitor>::qt_metacall(_c, _id, _a);
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
void LinBusMonitorProperty::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
