/****************************************************************************
** Meta object code from reading C++ file 'QVehicle_ModelProperty.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/vehicle/QML_Model/QVehicle_ModelProperty.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QVehicle_ModelProperty.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QVehicle_ModelProperty_t {
    const uint offsetsAndSize[24];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QVehicle_ModelProperty_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QVehicle_ModelProperty_t qt_meta_stringdata_QVehicle_ModelProperty = {
    {
QT_MOC_LITERAL(0, 22), // "QVehicle_ModelProperty"
QT_MOC_LITERAL(23, 7), // "changed"
QT_MOC_LITERAL(31, 0), // ""
QT_MOC_LITERAL(32, 4), // "item"
QT_MOC_LITERAL(37, 1), // "i"
QT_MOC_LITERAL(39, 12), // "current_item"
QT_MOC_LITERAL(52, 15), // "getCurrentIndex"
QT_MOC_LITERAL(68, 15), // "setCurrentIndex"
QT_MOC_LITERAL(84, 6), // "_index"
QT_MOC_LITERAL(91, 6), // "length"
QT_MOC_LITERAL(98, 7), // "isEmpty"
QT_MOC_LITERAL(106, 13) // "current_index"

    },
    "QVehicle_ModelProperty\0changed\0\0item\0"
    "i\0current_item\0getCurrentIndex\0"
    "setCurrentIndex\0_index\0length\0isEmpty\0"
    "current_index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QVehicle_ModelProperty[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       4,   53, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x06,    5 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,   45,    2, 0x02,    6 /* Public */,
       5,    0,   48,    2, 0x02,    8 /* Public */,
       6,    0,   49,    2, 0x102,    9 /* Public | MethodIsConst  */,
       7,    1,   50,    2, 0x02,   10 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::QVariant, QMetaType::Int,    4,
    QMetaType::QVariant,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,    8,

 // properties: name, type, flags
       9, QMetaType::Int, 0x00015001, uint(0), 0,
      10, QMetaType::Int, 0x00015001, uint(0), 0,
       5, QMetaType::QVariant, 0x00015001, uint(0), 0,
      11, QMetaType::Int, 0x00015001, uint(0), 0,

       0        // eod
};

void QVehicle_ModelProperty::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QVehicle_ModelProperty *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: { QVariant _r = _t->item((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 2: { QVariant _r = _t->current_item();
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 3: { int _r = _t->getCurrentIndex();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->setCurrentIndex((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QVehicle_ModelProperty::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QVehicle_ModelProperty::changed)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QVehicle_ModelProperty *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->count(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->isEmpty(); break;
        case 2: *reinterpret_cast< QVariant*>(_v) = _t->current_item(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->getCurrentIndex(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject QVehicle_ModelProperty::staticMetaObject = { {
    QMetaObject::SuperData::link<Obj_List_Model<QVehicle_ModelItem>::staticMetaObject>(),
    qt_meta_stringdata_QVehicle_ModelProperty.offsetsAndSize,
    qt_meta_data_QVehicle_ModelProperty,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QVehicle_ModelProperty_t
, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<QVariant, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<QVehicle_ModelProperty, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

, QtPrivate::TypeAndForceComplete<QVariant, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QVariant, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>

>,
    nullptr
} };


const QMetaObject *QVehicle_ModelProperty::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QVehicle_ModelProperty::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QVehicle_ModelProperty.stringdata0))
        return static_cast<void*>(this);
    return Obj_List_Model<QVehicle_ModelItem>::qt_metacast(_clname);
}

int QVehicle_ModelProperty::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Obj_List_Model<QVehicle_ModelItem>::qt_metacall(_c, _id, _a);
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
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QVehicle_ModelProperty::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_QVehicleNames_ModelProperty_t {
    const uint offsetsAndSize[2];
    char stringdata0[28];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QVehicleNames_ModelProperty_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QVehicleNames_ModelProperty_t qt_meta_stringdata_QVehicleNames_ModelProperty = {
    {
QT_MOC_LITERAL(0, 27) // "QVehicleNames_ModelProperty"

    },
    "QVehicleNames_ModelProperty"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QVehicleNames_ModelProperty[] = {

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

void QVehicleNames_ModelProperty::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject QVehicleNames_ModelProperty::staticMetaObject = { {
    QMetaObject::SuperData::link<QVehicle_ModelProperty::staticMetaObject>(),
    qt_meta_stringdata_QVehicleNames_ModelProperty.offsetsAndSize,
    qt_meta_data_QVehicleNames_ModelProperty,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QVehicleNames_ModelProperty_t
, QtPrivate::TypeAndForceComplete<QVehicleNames_ModelProperty, std::true_type>



>,
    nullptr
} };


const QMetaObject *QVehicleNames_ModelProperty::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QVehicleNames_ModelProperty::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QVehicleNames_ModelProperty.stringdata0))
        return static_cast<void*>(this);
    return QVehicle_ModelProperty::qt_metacast(_clname);
}

int QVehicleNames_ModelProperty::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QVehicle_ModelProperty::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
