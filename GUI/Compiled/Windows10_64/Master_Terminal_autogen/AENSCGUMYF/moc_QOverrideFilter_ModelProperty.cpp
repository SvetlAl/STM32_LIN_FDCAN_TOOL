/****************************************************************************
** Meta object code from reading C++ file 'QOverrideFilter_ModelProperty.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/stm32_device/QML_Model/QOverrideFilter_ModelProperty.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QOverrideFilter_ModelProperty.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QOverrideFilter_ModelProperty_t {
    const uint offsetsAndSize[28];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QOverrideFilter_ModelProperty_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QOverrideFilter_ModelProperty_t qt_meta_stringdata_QOverrideFilter_ModelProperty = {
    {
QT_MOC_LITERAL(0, 29), // "QOverrideFilter_ModelProperty"
QT_MOC_LITERAL(30, 7), // "changed"
QT_MOC_LITERAL(38, 0), // ""
QT_MOC_LITERAL(39, 4), // "init"
QT_MOC_LITERAL(44, 19), // "fill_OverrideStatus"
QT_MOC_LITERAL(64, 15), // "OverrideStatus*"
QT_MOC_LITERAL(80, 7), // "ovr_sts"
QT_MOC_LITERAL(88, 32), // "update_model_from_OverrideStatus"
QT_MOC_LITERAL(121, 4), // "item"
QT_MOC_LITERAL(126, 1), // "i"
QT_MOC_LITERAL(128, 13), // "enable_filter"
QT_MOC_LITERAL(142, 6), // "_value"
QT_MOC_LITERAL(149, 6), // "length"
QT_MOC_LITERAL(156, 7) // "isEmpty"

    },
    "QOverrideFilter_ModelProperty\0changed\0"
    "\0init\0fill_OverrideStatus\0OverrideStatus*\0"
    "ovr_sts\0update_model_from_OverrideStatus\0"
    "item\0i\0enable_filter\0_value\0length\0"
    "isEmpty"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QOverrideFilter_ModelProperty[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       2,   66, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    3 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   51,    2, 0x02,    4 /* Public */,
       4,    1,   52,    2, 0x102,    5 /* Public | MethodIsConst  */,
       7,    1,   55,    2, 0x02,    7 /* Public */,
       8,    1,   58,    2, 0x02,    9 /* Public */,
      10,    2,   61,    2, 0x02,   11 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::QVariant, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    9,   11,

 // properties: name, type, flags
      12, QMetaType::Int, 0x00015001, uint(0), 0,
      13, QMetaType::Int, 0x00015001, uint(0), 0,

       0        // eod
};

void QOverrideFilter_ModelProperty::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QOverrideFilter_ModelProperty *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->init(); break;
        case 2: _t->fill_OverrideStatus((*reinterpret_cast< std::add_pointer_t<OverrideStatus*>>(_a[1]))); break;
        case 3: _t->update_model_from_OverrideStatus((*reinterpret_cast< std::add_pointer_t<OverrideStatus*>>(_a[1]))); break;
        case 4: { QVariant _r = _t->item((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->enable_filter((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QOverrideFilter_ModelProperty::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QOverrideFilter_ModelProperty::changed)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QOverrideFilter_ModelProperty *>(_o);
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

const QMetaObject QOverrideFilter_ModelProperty::staticMetaObject = { {
    QMetaObject::SuperData::link<Obj_List_Model<QOverrideFilter_ModelItem>::staticMetaObject>(),
    qt_meta_stringdata_QOverrideFilter_ModelProperty.offsetsAndSize,
    qt_meta_data_QOverrideFilter_ModelProperty,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QOverrideFilter_ModelProperty_t
, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<QOverrideFilter_ModelProperty, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<OverrideStatus *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<OverrideStatus *, std::false_type>, QtPrivate::TypeAndForceComplete<QVariant, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const int, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>

>,
    nullptr
} };


const QMetaObject *QOverrideFilter_ModelProperty::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QOverrideFilter_ModelProperty::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QOverrideFilter_ModelProperty.stringdata0))
        return static_cast<void*>(this);
    return Obj_List_Model<QOverrideFilter_ModelItem>::qt_metacast(_clname);
}

int QOverrideFilter_ModelProperty::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Obj_List_Model<QOverrideFilter_ModelItem>::qt_metacall(_c, _id, _a);
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
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QOverrideFilter_ModelProperty::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
