/****************************************************************************
** Meta object code from reading C++ file 'QOverrideFilter_ModelItem.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/stm32_device/QML_Model/QOverrideFilter_ModelItem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QOverrideFilter_ModelItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QOverrideFilter_ModelItem_t {
    const uint offsetsAndSize[46];
    char stringdata0[225];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QOverrideFilter_ModelItem_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QOverrideFilter_ModelItem_t qt_meta_stringdata_QOverrideFilter_ModelItem = {
    {
QT_MOC_LITERAL(0, 25), // "QOverrideFilter_ModelItem"
QT_MOC_LITERAL(26, 7), // "changed"
QT_MOC_LITERAL(34, 0), // ""
QT_MOC_LITERAL(35, 7), // "enabled"
QT_MOC_LITERAL(43, 9), // "dir_value"
QT_MOC_LITERAL(53, 10), // "isEditable"
QT_MOC_LITERAL(64, 8), // "id_value"
QT_MOC_LITERAL(73, 9), // "str_byte0"
QT_MOC_LITERAL(83, 9), // "str_byte1"
QT_MOC_LITERAL(93, 9), // "str_byte2"
QT_MOC_LITERAL(103, 9), // "str_byte3"
QT_MOC_LITERAL(113, 9), // "str_byte4"
QT_MOC_LITERAL(123, 9), // "str_byte5"
QT_MOC_LITERAL(133, 9), // "str_byte6"
QT_MOC_LITERAL(143, 9), // "str_byte7"
QT_MOC_LITERAL(153, 8), // "byte0_on"
QT_MOC_LITERAL(162, 8), // "byte1_on"
QT_MOC_LITERAL(171, 8), // "byte2_on"
QT_MOC_LITERAL(180, 8), // "byte3_on"
QT_MOC_LITERAL(189, 8), // "byte4_on"
QT_MOC_LITERAL(198, 8), // "byte5_on"
QT_MOC_LITERAL(207, 8), // "byte6_on"
QT_MOC_LITERAL(216, 8) // "byte7_on"

    },
    "QOverrideFilter_ModelItem\0changed\0\0"
    "enabled\0dir_value\0isEditable\0id_value\0"
    "str_byte0\0str_byte1\0str_byte2\0str_byte3\0"
    "str_byte4\0str_byte5\0str_byte6\0str_byte7\0"
    "byte0_on\0byte1_on\0byte2_on\0byte3_on\0"
    "byte4_on\0byte5_on\0byte6_on\0byte7_on"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QOverrideFilter_ModelItem[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
      20,   21, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x06,   21 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // properties: name, type, flags
       3, QMetaType::Bool, 0x00015103, uint(0), 0,
       4, QMetaType::Int, 0x00015103, uint(0), 0,
       5, QMetaType::Bool, 0x00015003, uint(0), 0,
       6, QMetaType::QString, 0x00015003, uint(0), 0,
       7, QMetaType::QString, 0x00015103, uint(0), 0,
       8, QMetaType::QString, 0x00015103, uint(0), 0,
       9, QMetaType::QString, 0x00015103, uint(0), 0,
      10, QMetaType::QString, 0x00015103, uint(0), 0,
      11, QMetaType::QString, 0x00015103, uint(0), 0,
      12, QMetaType::QString, 0x00015103, uint(0), 0,
      13, QMetaType::QString, 0x00015103, uint(0), 0,
      14, QMetaType::QString, 0x00015103, uint(0), 0,
      15, QMetaType::Bool, 0x00015103, uint(0), 0,
      16, QMetaType::Bool, 0x00015103, uint(0), 0,
      17, QMetaType::Bool, 0x00015103, uint(0), 0,
      18, QMetaType::Bool, 0x00015103, uint(0), 0,
      19, QMetaType::Bool, 0x00015103, uint(0), 0,
      20, QMetaType::Bool, 0x00015103, uint(0), 0,
      21, QMetaType::Bool, 0x00015103, uint(0), 0,
      22, QMetaType::Bool, 0x00015103, uint(0), 0,

       0        // eod
};

void QOverrideFilter_ModelItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QOverrideFilter_ModelItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QOverrideFilter_ModelItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QOverrideFilter_ModelItem::changed)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QOverrideFilter_ModelItem *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->enabled(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->dir_value(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->editable(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->str_id_value(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->str_byte0(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->str_byte1(); break;
        case 6: *reinterpret_cast< QString*>(_v) = _t->str_byte2(); break;
        case 7: *reinterpret_cast< QString*>(_v) = _t->str_byte3(); break;
        case 8: *reinterpret_cast< QString*>(_v) = _t->str_byte4(); break;
        case 9: *reinterpret_cast< QString*>(_v) = _t->str_byte5(); break;
        case 10: *reinterpret_cast< QString*>(_v) = _t->str_byte6(); break;
        case 11: *reinterpret_cast< QString*>(_v) = _t->str_byte7(); break;
        case 12: *reinterpret_cast< bool*>(_v) = _t->byte0_on(); break;
        case 13: *reinterpret_cast< bool*>(_v) = _t->byte1_on(); break;
        case 14: *reinterpret_cast< bool*>(_v) = _t->byte2_on(); break;
        case 15: *reinterpret_cast< bool*>(_v) = _t->byte3_on(); break;
        case 16: *reinterpret_cast< bool*>(_v) = _t->byte4_on(); break;
        case 17: *reinterpret_cast< bool*>(_v) = _t->byte5_on(); break;
        case 18: *reinterpret_cast< bool*>(_v) = _t->byte6_on(); break;
        case 19: *reinterpret_cast< bool*>(_v) = _t->byte7_on(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QOverrideFilter_ModelItem *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEnabled(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setDir_value(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setEditable(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->str_set_id_value(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setStr_byte0(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setStr_byte1(*reinterpret_cast< QString*>(_v)); break;
        case 6: _t->setStr_byte2(*reinterpret_cast< QString*>(_v)); break;
        case 7: _t->setStr_byte3(*reinterpret_cast< QString*>(_v)); break;
        case 8: _t->setStr_byte4(*reinterpret_cast< QString*>(_v)); break;
        case 9: _t->setStr_byte5(*reinterpret_cast< QString*>(_v)); break;
        case 10: _t->setStr_byte6(*reinterpret_cast< QString*>(_v)); break;
        case 11: _t->setStr_byte7(*reinterpret_cast< QString*>(_v)); break;
        case 12: _t->setByte0_on(*reinterpret_cast< bool*>(_v)); break;
        case 13: _t->setByte1_on(*reinterpret_cast< bool*>(_v)); break;
        case 14: _t->setByte2_on(*reinterpret_cast< bool*>(_v)); break;
        case 15: _t->setByte3_on(*reinterpret_cast< bool*>(_v)); break;
        case 16: _t->setByte4_on(*reinterpret_cast< bool*>(_v)); break;
        case 17: _t->setByte5_on(*reinterpret_cast< bool*>(_v)); break;
        case 18: _t->setByte6_on(*reinterpret_cast< bool*>(_v)); break;
        case 19: _t->setByte7_on(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

const QMetaObject QOverrideFilter_ModelItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QOverrideFilter_ModelItem.offsetsAndSize,
    qt_meta_data_QOverrideFilter_ModelItem,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QOverrideFilter_ModelItem_t
, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<QOverrideFilter_ModelItem, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *QOverrideFilter_ModelItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QOverrideFilter_ModelItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QOverrideFilter_ModelItem.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QOverrideFilter_ModelItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QOverrideFilter_ModelItem::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
