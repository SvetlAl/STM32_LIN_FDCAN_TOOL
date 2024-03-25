/****************************************************************************
** Meta object code from reading C++ file 'MemoryManager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/memory/MemoryManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MemoryManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MemoryManager_t {
    const uint offsetsAndSize[20];
    char stringdata0[195];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MemoryManager_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MemoryManager_t qt_meta_stringdata_MemoryManager = {
    {
QT_MOC_LITERAL(0, 13), // "MemoryManager"
QT_MOC_LITERAL(14, 19), // "error_statusChanged"
QT_MOC_LITERAL(34, 0), // ""
QT_MOC_LITERAL(35, 23), // "resetFlashSpi_DataModel"
QT_MOC_LITERAL(59, 30), // "string_from_FlashSpiMemoryData"
QT_MOC_LITERAL(90, 34), // "write_FlashSpiMemoryData_into..."
QT_MOC_LITERAL(125, 9), // "_filename"
QT_MOC_LITERAL(135, 18), // "FlashSpi_DataModel"
QT_MOC_LITERAL(154, 27), // "FlashSpiMemoryDataProperty*"
QT_MOC_LITERAL(182, 12) // "error_status"

    },
    "MemoryManager\0error_statusChanged\0\0"
    "resetFlashSpi_DataModel\0"
    "string_from_FlashSpiMemoryData\0"
    "write_FlashSpiMemoryData_into_file\0"
    "_filename\0FlashSpi_DataModel\0"
    "FlashSpiMemoryDataProperty*\0error_status"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MemoryManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       2,   44, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   39,    2, 0x0a,    4 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,   40,    2, 0x02,    5 /* Public */,
       5,    1,   41,    2, 0x02,    6 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::QString,
    QMetaType::Bool, QMetaType::QString,    6,

 // properties: name, type, flags
       7, 0x80000000 | 8, 0x00015409, uint(-1), 0,
       9, QMetaType::QString, 0x00015107, uint(0), 0,

       0        // eod
};

void MemoryManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MemoryManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->error_statusChanged(); break;
        case 1: _t->resetFlashSpi_DataModel(); break;
        case 2: { QString _r = _t->string_from_FlashSpiMemoryData();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->write_FlashSpiMemoryData_into_file((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MemoryManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MemoryManager::error_statusChanged)) {
                *result = 0;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< FlashSpiMemoryDataProperty* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<MemoryManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< FlashSpiMemoryDataProperty**>(_v) = _t->FlashSpi_DataModel(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->error_status(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<MemoryManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setError_status(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
        auto *_t = static_cast<MemoryManager *>(_o);
        (void)_t;
        switch (_id) {
        case 1: _t->resetError_status(); break;
        default: break;
        }
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject MemoryManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MemoryManager.offsetsAndSize,
    qt_meta_data_MemoryManager,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MemoryManager_t
, QtPrivate::TypeAndForceComplete<FlashSpiMemoryDataProperty*, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<MemoryManager, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>

>,
    nullptr
} };


const QMetaObject *MemoryManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MemoryManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MemoryManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MemoryManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void MemoryManager::error_statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
