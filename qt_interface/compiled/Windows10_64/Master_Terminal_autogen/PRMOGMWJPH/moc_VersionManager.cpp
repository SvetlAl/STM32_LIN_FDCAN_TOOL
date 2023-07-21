/****************************************************************************
** Meta object code from reading C++ file 'VersionManager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/core/VersionManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VersionManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VersionManager_t {
    const uint offsetsAndSize[38];
    char stringdata0[450];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_VersionManager_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_VersionManager_t qt_meta_stringdata_VersionManager = {
    {
QT_MOC_LITERAL(0, 14), // "VersionManager"
QT_MOC_LITERAL(15, 29), // "current_device_versionChanged"
QT_MOC_LITERAL(45, 0), // ""
QT_MOC_LITERAL(46, 28), // "hardware_device_modelChanged"
QT_MOC_LITERAL(75, 22), // "isCriticalAlertChanged"
QT_MOC_LITERAL(98, 30), // "isInterfaceInfoAppendedChanged"
QT_MOC_LITERAL(129, 27), // "isDeviceInfoAppendedChanged"
QT_MOC_LITERAL(157, 40), // "isNewHardwareApplicationAvail..."
QT_MOC_LITERAL(198, 23), // "handleDeviceVersionInfo"
QT_MOC_LITERAL(222, 22), // "printInterfaceVersions"
QT_MOC_LITERAL(245, 19), // "printDeviceVersions"
QT_MOC_LITERAL(265, 13), // "printOnUpdate"
QT_MOC_LITERAL(279, 25), // "current_interface_version"
QT_MOC_LITERAL(305, 22), // "current_device_version"
QT_MOC_LITERAL(328, 26), // "hardware_device_model_name"
QT_MOC_LITERAL(355, 15), // "isCriticalAlert"
QT_MOC_LITERAL(371, 23), // "isInterfaceInfoAppended"
QT_MOC_LITERAL(395, 20), // "isDeviceInfoAppended"
QT_MOC_LITERAL(416, 33) // "isNewHardwareApplicationAvail..."

    },
    "VersionManager\0current_device_versionChanged\0"
    "\0hardware_device_modelChanged\0"
    "isCriticalAlertChanged\0"
    "isInterfaceInfoAppendedChanged\0"
    "isDeviceInfoAppendedChanged\0"
    "isNewHardwareApplicationAvailableChanged\0"
    "handleDeviceVersionInfo\0printInterfaceVersions\0"
    "printDeviceVersions\0printOnUpdate\0"
    "current_interface_version\0"
    "current_device_version\0"
    "hardware_device_model_name\0isCriticalAlert\0"
    "isInterfaceInfoAppended\0isDeviceInfoAppended\0"
    "isNewHardwareApplicationAvailable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VersionManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       7,   84, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x06,    8 /* Public */,
       3,    0,   75,    2, 0x06,    9 /* Public */,
       4,    0,   76,    2, 0x06,   10 /* Public */,
       5,    0,   77,    2, 0x06,   11 /* Public */,
       6,    0,   78,    2, 0x06,   12 /* Public */,
       7,    0,   79,    2, 0x06,   13 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    0,   80,    2, 0x0a,   14 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,   81,    2, 0x02,   15 /* Public */,
      10,    0,   82,    2, 0x02,   16 /* Public */,
      11,    0,   83,    2, 0x02,   17 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      12, QMetaType::QString, 0x00015401, uint(-1), 0,
      13, QMetaType::QString, 0x00015001, uint(0), 0,
      14, QMetaType::QString, 0x00015001, uint(1), 0,
      15, QMetaType::Bool, 0x00015103, uint(2), 0,
      16, QMetaType::Bool, 0x00015103, uint(3), 0,
      17, QMetaType::Bool, 0x00015103, uint(4), 0,
      18, QMetaType::Bool, 0x00015001, uint(5), 0,

       0        // eod
};

void VersionManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VersionManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->current_device_versionChanged(); break;
        case 1: _t->hardware_device_modelChanged(); break;
        case 2: _t->isCriticalAlertChanged(); break;
        case 3: _t->isInterfaceInfoAppendedChanged(); break;
        case 4: _t->isDeviceInfoAppendedChanged(); break;
        case 5: _t->isNewHardwareApplicationAvailableChanged(); break;
        case 6: _t->handleDeviceVersionInfo(); break;
        case 7: _t->printInterfaceVersions(); break;
        case 8: _t->printDeviceVersions(); break;
        case 9: _t->printOnUpdate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VersionManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VersionManager::current_device_versionChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VersionManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VersionManager::hardware_device_modelChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (VersionManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VersionManager::isCriticalAlertChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (VersionManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VersionManager::isInterfaceInfoAppendedChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (VersionManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VersionManager::isDeviceInfoAppendedChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (VersionManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VersionManager::isNewHardwareApplicationAvailableChanged)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<VersionManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->current_interface_version(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->current_device_version(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->hardware_device_model_name(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->getIsCriticalAlert(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->getIsInterfaceInfoAppended(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->getIsDeviceInfoAppended(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->isNewHardwareApplicationAvailable(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<VersionManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 3: _t->setIsCriticalAlert(*reinterpret_cast< bool*>(_v)); break;
        case 4: _t->setIsInterfaceInfoAppended(*reinterpret_cast< bool*>(_v)); break;
        case 5: _t->setIsDeviceInfoAppended(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

const QMetaObject VersionManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_VersionManager.offsetsAndSize,
    qt_meta_data_VersionManager,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_VersionManager_t
, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<VersionManager, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

>,
    nullptr
} };


const QMetaObject *VersionManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VersionManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VersionManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VersionManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
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
void VersionManager::current_device_versionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void VersionManager::hardware_device_modelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void VersionManager::isCriticalAlertChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void VersionManager::isInterfaceInfoAppendedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void VersionManager::isDeviceInfoAppendedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void VersionManager::isNewHardwareApplicationAvailableChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
