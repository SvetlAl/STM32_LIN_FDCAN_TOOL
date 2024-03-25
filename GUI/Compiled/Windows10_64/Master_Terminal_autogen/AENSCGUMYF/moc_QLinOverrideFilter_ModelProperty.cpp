/****************************************************************************
** Meta object code from reading C++ file 'QLinOverrideFilter_ModelProperty.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/stm32_device/QML_Model/QLinOverrideFilter_ModelProperty.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QLinOverrideFilter_ModelProperty.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QLinOverrideFilter_ModelProperty_t {
    const uint offsetsAndSize[16];
    char stringdata0[69];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QLinOverrideFilter_ModelProperty_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QLinOverrideFilter_ModelProperty_t qt_meta_stringdata_QLinOverrideFilter_ModelProperty = {
    {
QT_MOC_LITERAL(0, 32), // "QLinOverrideFilter_ModelProperty"
QT_MOC_LITERAL(33, 7), // "changed"
QT_MOC_LITERAL(41, 0), // ""
QT_MOC_LITERAL(42, 4), // "init"
QT_MOC_LITERAL(47, 4), // "item"
QT_MOC_LITERAL(52, 1), // "i"
QT_MOC_LITERAL(54, 6), // "length"
QT_MOC_LITERAL(61, 7) // "isEmpty"

    },
    "QLinOverrideFilter_ModelProperty\0"
    "changed\0\0init\0item\0i\0length\0isEmpty"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QLinOverrideFilter_ModelProperty[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       2,   37, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x06,    3 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   33,    2, 0x02,    4 /* Public */,
       4,    1,   34,    2, 0x02,    5 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::QVariant, QMetaType::Int,    5,

 // properties: name, type, flags
       6, QMetaType::Int, 0x00015001, uint(0), 0,
       7, QMetaType::Int, 0x00015001, uint(0), 0,

       0        // eod
};

void QLinOverrideFilter_ModelProperty::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QLinOverrideFilter_ModelProperty *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->init(); break;
        case 2: { QVariant _r = _t->item((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QLinOverrideFilter_ModelProperty::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QLinOverrideFilter_ModelProperty::changed)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QLinOverrideFilter_ModelProperty *>(_o);
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

const QMetaObject QLinOverrideFilter_ModelProperty::staticMetaObject = { {
    QMetaObject::SuperData::link<Obj_List_Model<QLinOverrideFilter_ModelItem>::staticMetaObject>(),
    qt_meta_stringdata_QLinOverrideFilter_ModelProperty.offsetsAndSize,
    qt_meta_data_QLinOverrideFilter_ModelProperty,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QLinOverrideFilter_ModelProperty_t
, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<QLinOverrideFilter_ModelProperty, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QVariant, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>

>,
    nullptr
} };


const QMetaObject *QLinOverrideFilter_ModelProperty::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QLinOverrideFilter_ModelProperty::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QLinOverrideFilter_ModelProperty.stringdata0))
        return static_cast<void*>(this);
    return Obj_List_Model<QLinOverrideFilter_ModelItem>::qt_metacast(_clname);
}

int QLinOverrideFilter_ModelProperty::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Obj_List_Model<QLinOverrideFilter_ModelItem>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
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
void QLinOverrideFilter_ModelProperty::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
