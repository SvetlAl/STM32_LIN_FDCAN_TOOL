/****************************************************************************
** Meta object code from reading C++ file 'DeviceManager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/stm32_device/DeviceManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DeviceManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DeviceManager_t {
    const uint offsetsAndSize[68];
    char stringdata0[586];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_DeviceManager_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_DeviceManager_t qt_meta_stringdata_DeviceManager = {
    {
QT_MOC_LITERAL(0, 13), // "DeviceManager"
QT_MOC_LITERAL(14, 7), // "changed"
QT_MOC_LITERAL(22, 0), // ""
QT_MOC_LITERAL(23, 15), // "memchip_changed"
QT_MOC_LITERAL(39, 21), // "refreshOverrideStatus"
QT_MOC_LITERAL(61, 4), // "data"
QT_MOC_LITERAL(66, 20), // "refreshActiveFilters"
QT_MOC_LITERAL(87, 25), // "fill_OvrSts_from_DscModel"
QT_MOC_LITERAL(113, 27), // "update_DscModel_from_OvrSts"
QT_MOC_LITERAL(141, 25), // "fill_OvrSts_from_OvrModel"
QT_MOC_LITERAL(167, 27), // "update_OvrModel_from_OvrSts"
QT_MOC_LITERAL(195, 15), // "canGateway_Mode"
QT_MOC_LITERAL(211, 21), // "calibratorFilter_Mode"
QT_MOC_LITERAL(233, 16), // "canOverride_Mode"
QT_MOC_LITERAL(250, 15), // "canScanner_Mode"
QT_MOC_LITERAL(266, 16), // "can2Scanner_Mode"
QT_MOC_LITERAL(283, 21), // "memoryPrograming_Mode"
QT_MOC_LITERAL(305, 17), // "canInjection_Mode"
QT_MOC_LITERAL(323, 14), // "customBTR_Mode"
QT_MOC_LITERAL(338, 11), // "val_BTR_PSC"
QT_MOC_LITERAL(350, 11), // "val_BTR_BS1"
QT_MOC_LITERAL(362, 11), // "val_BTR_BS2"
QT_MOC_LITERAL(374, 11), // "val_BTR_SJW"
QT_MOC_LITERAL(386, 16), // "customBTR_Mode_2"
QT_MOC_LITERAL(403, 13), // "val_BTR_PSC_2"
QT_MOC_LITERAL(417, 13), // "val_BTR_BS1_2"
QT_MOC_LITERAL(431, 13), // "val_BTR_BS2_2"
QT_MOC_LITERAL(445, 13), // "val_BTR_SJW_2"
QT_MOC_LITERAL(459, 21), // "canInjection_Mode_CDC"
QT_MOC_LITERAL(481, 12), // "memchip_name"
QT_MOC_LITERAL(494, 14), // "DiscardIdModel"
QT_MOC_LITERAL(509, 25), // "QDiscardId_ModelProperty*"
QT_MOC_LITERAL(535, 19), // "OverrideFilterModel"
QT_MOC_LITERAL(555, 30) // "QOverrideFilter_ModelProperty*"

    },
    "DeviceManager\0changed\0\0memchip_changed\0"
    "refreshOverrideStatus\0data\0"
    "refreshActiveFilters\0fill_OvrSts_from_DscModel\0"
    "update_DscModel_from_OvrSts\0"
    "fill_OvrSts_from_OvrModel\0"
    "update_OvrModel_from_OvrSts\0canGateway_Mode\0"
    "calibratorFilter_Mode\0canOverride_Mode\0"
    "canScanner_Mode\0can2Scanner_Mode\0"
    "memoryPrograming_Mode\0canInjection_Mode\0"
    "customBTR_Mode\0val_BTR_PSC\0val_BTR_BS1\0"
    "val_BTR_BS2\0val_BTR_SJW\0customBTR_Mode_2\0"
    "val_BTR_PSC_2\0val_BTR_BS1_2\0val_BTR_BS2_2\0"
    "val_BTR_SJW_2\0canInjection_Mode_CDC\0"
    "memchip_name\0DiscardIdModel\0"
    "QDiscardId_ModelProperty*\0OverrideFilterModel\0"
    "QOverrideFilter_ModelProperty*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeviceManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
      21,   74, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,   22 /* Public */,
       3,    0,   63,    2, 0x06,   23 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    1,   64,    2, 0x0a,   24 /* Public */,
       6,    1,   67,    2, 0x0a,   26 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,   70,    2, 0x02,   28 /* Public */,
       8,    0,   71,    2, 0x02,   29 /* Public */,
       9,    0,   72,    2, 0x02,   30 /* Public */,
      10,    0,   73,    2, 0x02,   31 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void, QMetaType::QByteArray,    5,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      11, QMetaType::Int, 0x00015103, uint(0), 0,
      12, QMetaType::Int, 0x00015103, uint(0), 0,
      13, QMetaType::Int, 0x00015103, uint(0), 0,
      14, QMetaType::Int, 0x00015103, uint(0), 0,
      15, QMetaType::Int, 0x00015103, uint(0), 0,
      16, QMetaType::Int, 0x00015001, uint(0), 0,
      17, QMetaType::Int, 0x00015001, uint(0), 0,
      18, QMetaType::Int, 0x00015103, uint(0), 0,
      19, QMetaType::Int, 0x00015103, uint(0), 0,
      20, QMetaType::Int, 0x00015103, uint(0), 0,
      21, QMetaType::Int, 0x00015103, uint(0), 0,
      22, QMetaType::Int, 0x00015103, uint(0), 0,
      23, QMetaType::Int, 0x00015103, uint(0), 0,
      24, QMetaType::Int, 0x00015103, uint(0), 0,
      25, QMetaType::Int, 0x00015103, uint(0), 0,
      26, QMetaType::Int, 0x00015103, uint(0), 0,
      27, QMetaType::Int, 0x00015103, uint(0), 0,
      28, QMetaType::Int, 0x00015001, uint(0), 0,
      29, QMetaType::QString, 0x00015001, uint(1), 0,
      30, 0x80000000 | 31, 0x00015409, uint(-1), 0,
      32, 0x80000000 | 33, 0x00015409, uint(-1), 0,

       0        // eod
};

void DeviceManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DeviceManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->memchip_changed(); break;
        case 2: _t->refreshOverrideStatus((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 3: _t->refreshActiveFilters((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 4: _t->fill_OvrSts_from_DscModel(); break;
        case 5: _t->update_DscModel_from_OvrSts(); break;
        case 6: _t->fill_OvrSts_from_OvrModel(); break;
        case 7: _t->update_OvrModel_from_OvrSts(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DeviceManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceManager::changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DeviceManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceManager::memchip_changed)) {
                *result = 1;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 19:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QDiscardId_ModelProperty* >(); break;
        case 20:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QOverrideFilter_ModelProperty* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<DeviceManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->canGateway_Mode(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->calibratorFilter_Mode(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->canOverride_Mode(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->canScanner_Mode(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->can2Scanner_Mode(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->memoryPrograming_Mode(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->canInjection_Mode(); break;
        case 7: *reinterpret_cast< int*>(_v) = _t->customBTR_Mode(); break;
        case 8: *reinterpret_cast< int*>(_v) = _t->val_BTR_PSC(); break;
        case 9: *reinterpret_cast< int*>(_v) = _t->val_BTR_BS1(); break;
        case 10: *reinterpret_cast< int*>(_v) = _t->val_BTR_BS2(); break;
        case 11: *reinterpret_cast< int*>(_v) = _t->val_BTR_SJW(); break;
        case 12: *reinterpret_cast< int*>(_v) = _t->customBTR_Mode_2(); break;
        case 13: *reinterpret_cast< int*>(_v) = _t->val_BTR_PSC_2(); break;
        case 14: *reinterpret_cast< int*>(_v) = _t->val_BTR_BS1_2(); break;
        case 15: *reinterpret_cast< int*>(_v) = _t->val_BTR_BS2_2(); break;
        case 16: *reinterpret_cast< int*>(_v) = _t->val_BTR_SJW_2(); break;
        case 17: *reinterpret_cast< int*>(_v) = _t->canInjection_Mode_CDC(); break;
        case 18: *reinterpret_cast< QString*>(_v) = _t->memchip_name(); break;
        case 19: *reinterpret_cast< QDiscardId_ModelProperty**>(_v) = _t->DiscardIdModel(); break;
        case 20: *reinterpret_cast< QOverrideFilter_ModelProperty**>(_v) = _t->OverrideFilterModel(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<DeviceManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCanGateway_Mode(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setCalibratorFilter_Mode(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setCanOverride_Mode(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setCanScanner_Mode(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setCan2Scanner_Mode(*reinterpret_cast< int*>(_v)); break;
        case 7: _t->setCustomBTR_Mode(*reinterpret_cast< int*>(_v)); break;
        case 8: _t->setVal_BTR_PSC(*reinterpret_cast< int*>(_v)); break;
        case 9: _t->setVal_BTR_BS1(*reinterpret_cast< int*>(_v)); break;
        case 10: _t->setVal_BTR_BS2(*reinterpret_cast< int*>(_v)); break;
        case 11: _t->setVal_BTR_SJW(*reinterpret_cast< int*>(_v)); break;
        case 12: _t->setCustomBTR_Mode_2(*reinterpret_cast< int*>(_v)); break;
        case 13: _t->setVal_BTR_PSC_2(*reinterpret_cast< int*>(_v)); break;
        case 14: _t->setVal_BTR_BS1_2(*reinterpret_cast< int*>(_v)); break;
        case 15: _t->setVal_BTR_BS2_2(*reinterpret_cast< int*>(_v)); break;
        case 16: _t->setVal_BTR_SJW_2(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject DeviceManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DeviceManager.offsetsAndSize,
    qt_meta_data_DeviceManager,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_DeviceManager_t
, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QDiscardId_ModelProperty*, std::true_type>, QtPrivate::TypeAndForceComplete<QOverrideFilter_ModelProperty*, std::true_type>, QtPrivate::TypeAndForceComplete<DeviceManager, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray &, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

>,
    nullptr
} };


const QMetaObject *DeviceManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeviceManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DeviceManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void DeviceManager::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DeviceManager::memchip_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
