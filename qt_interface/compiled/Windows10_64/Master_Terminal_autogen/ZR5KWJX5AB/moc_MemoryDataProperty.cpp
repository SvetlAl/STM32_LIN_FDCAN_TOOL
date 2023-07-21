/****************************************************************************
** Meta object code from reading C++ file 'MemoryDataProperty.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/memory/MemoryDataProperty.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MemoryDataProperty.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MemoryDataProperty_t {
    const uint offsetsAndSize[14];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MemoryDataProperty_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MemoryDataProperty_t qt_meta_stringdata_MemoryDataProperty = {
    {
QT_MOC_LITERAL(0, 18), // "MemoryDataProperty"
QT_MOC_LITERAL(19, 7), // "changed"
QT_MOC_LITERAL(27, 0), // ""
QT_MOC_LITERAL(28, 4), // "item"
QT_MOC_LITERAL(33, 1), // "i"
QT_MOC_LITERAL(35, 6), // "length"
QT_MOC_LITERAL(42, 7) // "isEmpty"

    },
    "MemoryDataProperty\0changed\0\0item\0i\0"
    "length\0isEmpty"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MemoryDataProperty[] = {

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

void MemoryDataProperty::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MemoryDataProperty *>(_o);
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
            using _t = void (MemoryDataProperty::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MemoryDataProperty::changed)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<MemoryDataProperty *>(_o);
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

const QMetaObject MemoryDataProperty::staticMetaObject = { {
    QMetaObject::SuperData::link<Obj_List_Model<MemoryDataItem>::staticMetaObject>(),
    qt_meta_stringdata_MemoryDataProperty.offsetsAndSize,
    qt_meta_data_MemoryDataProperty,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MemoryDataProperty_t
, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<MemoryDataProperty, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

, QtPrivate::TypeAndForceComplete<QVariant, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>

>,
    nullptr
} };


const QMetaObject *MemoryDataProperty::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MemoryDataProperty::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MemoryDataProperty.stringdata0))
        return static_cast<void*>(this);
    return Obj_List_Model<MemoryDataItem>::qt_metacast(_clname);
}

int MemoryDataProperty::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Obj_List_Model<MemoryDataItem>::qt_metacall(_c, _id, _a);
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
void MemoryDataProperty::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_FlashSpiMemoryDataProperty_t {
    const uint offsetsAndSize[2];
    char stringdata0[27];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_FlashSpiMemoryDataProperty_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_FlashSpiMemoryDataProperty_t qt_meta_stringdata_FlashSpiMemoryDataProperty = {
    {
QT_MOC_LITERAL(0, 26) // "FlashSpiMemoryDataProperty"

    },
    "FlashSpiMemoryDataProperty"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlashSpiMemoryDataProperty[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void FlashSpiMemoryDataProperty::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject FlashSpiMemoryDataProperty::staticMetaObject = { {
    QMetaObject::SuperData::link<MemoryDataProperty::staticMetaObject>(),
    qt_meta_stringdata_FlashSpiMemoryDataProperty.offsetsAndSize,
    qt_meta_data_FlashSpiMemoryDataProperty,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_FlashSpiMemoryDataProperty_t
, QtPrivate::TypeAndForceComplete<FlashSpiMemoryDataProperty, std::true_type>



>,
    nullptr
} };


const QMetaObject *FlashSpiMemoryDataProperty::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlashSpiMemoryDataProperty::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FlashSpiMemoryDataProperty.stringdata0))
        return static_cast<void*>(this);
    return MemoryDataProperty::qt_metacast(_clname);
}

int FlashSpiMemoryDataProperty::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MemoryDataProperty::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
