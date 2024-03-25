/****************************************************************************
** Meta object code from reading C++ file 'QFDCAN_OverrideFilter_ModelProperty.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/stm32_device/QML_Model/QFDCAN_OverrideFilter_ModelProperty.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QFDCAN_OverrideFilter_ModelProperty.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QFDCAN_OverrideFilter_ModelProperty_t {
    const uint offsetsAndSize[34];
    char stringdata0[212];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QFDCAN_OverrideFilter_ModelProperty_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QFDCAN_OverrideFilter_ModelProperty_t qt_meta_stringdata_QFDCAN_OverrideFilter_ModelProperty = {
    {
QT_MOC_LITERAL(0, 35), // "QFDCAN_OverrideFilter_ModelPr..."
QT_MOC_LITERAL(36, 7), // "changed"
QT_MOC_LITERAL(44, 0), // ""
QT_MOC_LITERAL(45, 4), // "init"
QT_MOC_LITERAL(50, 19), // "fill_OverrideStatus"
QT_MOC_LITERAL(70, 21), // "FDCAN_OverrideStatus*"
QT_MOC_LITERAL(92, 7), // "ovr_sts"
QT_MOC_LITERAL(100, 32), // "update_model_from_OverrideStatus"
QT_MOC_LITERAL(133, 4), // "item"
QT_MOC_LITERAL(138, 1), // "i"
QT_MOC_LITERAL(140, 6), // "length"
QT_MOC_LITERAL(147, 7), // "isEmpty"
QT_MOC_LITERAL(155, 8), // "id_begin"
QT_MOC_LITERAL(164, 6), // "id_end"
QT_MOC_LITERAL(171, 14), // "can1tocan2_dir"
QT_MOC_LITERAL(186, 14), // "can2tocan1_dir"
QT_MOC_LITERAL(201, 10) // "range_used"

    },
    "QFDCAN_OverrideFilter_ModelProperty\0"
    "changed\0\0init\0fill_OverrideStatus\0"
    "FDCAN_OverrideStatus*\0ovr_sts\0"
    "update_model_from_OverrideStatus\0item\0"
    "i\0length\0isEmpty\0id_begin\0id_end\0"
    "can1tocan2_dir\0can2tocan1_dir\0range_used"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QFDCAN_OverrideFilter_ModelProperty[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       7,   55, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x06,    8 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   45,    2, 0x02,    9 /* Public */,
       4,    1,   46,    2, 0x102,   10 /* Public | MethodIsConst  */,
       7,    1,   49,    2, 0x02,   12 /* Public */,
       8,    1,   52,    2, 0x02,   14 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::QVariant, QMetaType::Int,    9,

 // properties: name, type, flags
      10, QMetaType::Int, 0x00015001, uint(0), 0,
      11, QMetaType::Int, 0x00015001, uint(0), 0,
      12, QMetaType::QString, 0x00015003, uint(0), 0,
      13, QMetaType::QString, 0x00015003, uint(0), 0,
      14, QMetaType::Bool, 0x00015003, uint(0), 0,
      15, QMetaType::Bool, 0x00015003, uint(0), 0,
      16, QMetaType::Bool, 0x00015003, uint(0), 0,

       0        // eod
};

void QFDCAN_OverrideFilter_ModelProperty::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QFDCAN_OverrideFilter_ModelProperty *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->init(); break;
        case 2: _t->fill_OverrideStatus((*reinterpret_cast< std::add_pointer_t<FDCAN_OverrideStatus*>>(_a[1]))); break;
        case 3: _t->update_model_from_OverrideStatus((*reinterpret_cast< std::add_pointer_t<FDCAN_OverrideStatus*>>(_a[1]))); break;
        case 4: { QVariant _r = _t->item((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QFDCAN_OverrideFilter_ModelProperty::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QFDCAN_OverrideFilter_ModelProperty::changed)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QFDCAN_OverrideFilter_ModelProperty *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->count(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->isEmpty(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->id_begin(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->id_end(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->can1tocan2_dir(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->can2tocan1_dir(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->range_used(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QFDCAN_OverrideFilter_ModelProperty *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->set_id_begin(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->set_id_end(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->set_can1tocan2_dir(*reinterpret_cast< bool*>(_v)); break;
        case 5: _t->set_can2tocan1_dir(*reinterpret_cast< bool*>(_v)); break;
        case 6: _t->set_range_used(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject QFDCAN_OverrideFilter_ModelProperty::staticMetaObject = { {
    QMetaObject::SuperData::link<Obj_List_Model<QFDCAN_OverrideFilter_ModelItem>::staticMetaObject>(),
    qt_meta_stringdata_QFDCAN_OverrideFilter_ModelProperty.offsetsAndSize,
    qt_meta_data_QFDCAN_OverrideFilter_ModelProperty,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QFDCAN_OverrideFilter_ModelProperty_t
, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<QFDCAN_OverrideFilter_ModelProperty, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<FDCAN_OverrideStatus *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<FDCAN_OverrideStatus *, std::false_type>, QtPrivate::TypeAndForceComplete<QVariant, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>

>,
    nullptr
} };


const QMetaObject *QFDCAN_OverrideFilter_ModelProperty::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QFDCAN_OverrideFilter_ModelProperty::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QFDCAN_OverrideFilter_ModelProperty.stringdata0))
        return static_cast<void*>(this);
    return Obj_List_Model<QFDCAN_OverrideFilter_ModelItem>::qt_metacast(_clname);
}

int QFDCAN_OverrideFilter_ModelProperty::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Obj_List_Model<QFDCAN_OverrideFilter_ModelItem>::qt_metacall(_c, _id, _a);
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
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QFDCAN_OverrideFilter_ModelProperty::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
