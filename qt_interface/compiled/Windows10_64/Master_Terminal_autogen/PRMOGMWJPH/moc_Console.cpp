/****************************************************************************
** Meta object code from reading C++ file 'Console.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/core/Console.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Console.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Console_t {
    const uint offsetsAndSize[36];
    char stringdata0[394];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Console_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Console_t qt_meta_stringdata_Console = {
    {
QT_MOC_LITERAL(0, 7), // "Console"
QT_MOC_LITERAL(8, 14), // "cdc_new_string"
QT_MOC_LITERAL(23, 0), // ""
QT_MOC_LITERAL(24, 26), // "manual_override_new_string"
QT_MOC_LITERAL(51, 26), // "firmware_update_new_string"
QT_MOC_LITERAL(78, 37), // "connection_status_description..."
QT_MOC_LITERAL(116, 22), // "append_firmware_update"
QT_MOC_LITERAL(139, 7), // "_string"
QT_MOC_LITERAL(147, 31), // "read_serialport_and_append_data"
QT_MOC_LITERAL(179, 16), // "reset_cdc_string"
QT_MOC_LITERAL(196, 28), // "reset_manual_override_string"
QT_MOC_LITERAL(225, 28), // "reset_firmware_update_string"
QT_MOC_LITERAL(254, 17), // "cached_cdc_string"
QT_MOC_LITERAL(272, 29), // "cached_manual_override_string"
QT_MOC_LITERAL(302, 33), // "cached_manual_override_string..."
QT_MOC_LITERAL(336, 15), // "firmware_update"
QT_MOC_LITERAL(352, 29), // "connection_status_description"
QT_MOC_LITERAL(382, 11) // "isConnected"

    },
    "Console\0cdc_new_string\0\0"
    "manual_override_new_string\0"
    "firmware_update_new_string\0"
    "connection_status_description_changed\0"
    "append_firmware_update\0_string\0"
    "read_serialport_and_append_data\0"
    "reset_cdc_string\0reset_manual_override_string\0"
    "reset_firmware_update_string\0"
    "cached_cdc_string\0cached_manual_override_string\0"
    "cached_manual_override_string_hex\0"
    "firmware_update\0connection_status_description\0"
    "isConnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Console[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       6,   79, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x06,    7 /* Public */,
       3,    0,   69,    2, 0x06,    8 /* Public */,
       4,    0,   70,    2, 0x06,    9 /* Public */,
       5,    0,   71,    2, 0x06,   10 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,   72,    2, 0x0a,   11 /* Public */,
       8,    0,   75,    2, 0x0a,   13 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,   76,    2, 0x02,   14 /* Public */,
      10,    0,   77,    2, 0x02,   15 /* Public */,
      11,    0,   78,    2, 0x02,   16 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      12, QMetaType::QString, 0x00015003, uint(0), 0,
      13, QMetaType::QString, 0x00015003, uint(1), 0,
      14, QMetaType::QString, 0x00015001, uint(1), 0,
      15, QMetaType::QString, 0x00015003, uint(2), 0,
      16, QMetaType::QStringList, 0x00015001, uint(3), 0,
      17, QMetaType::Bool, 0x00015001, uint(3), 0,

       0        // eod
};

void Console::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Console *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->cdc_new_string(); break;
        case 1: _t->manual_override_new_string(); break;
        case 2: _t->firmware_update_new_string(); break;
        case 3: _t->connection_status_description_changed(); break;
        case 4: _t->append_firmware_update((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->read_serialport_and_append_data(); break;
        case 6: _t->reset_cdc_string(); break;
        case 7: _t->reset_manual_override_string(); break;
        case 8: _t->reset_firmware_update_string(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Console::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Console::cdc_new_string)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Console::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Console::manual_override_new_string)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Console::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Console::firmware_update_new_string)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Console::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Console::connection_status_description_changed)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Console *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->Cdc_string(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->Manual_override(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->Manual_override_string_hex(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->firmware_update(); break;
        case 4: *reinterpret_cast< QStringList*>(_v) = _t->Connection_status_description(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->isConnected(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Console *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->set_cdc_string(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->set_manual_override(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->set_firmware_update(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject Console::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Console.offsetsAndSize,
    qt_meta_data_Console,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Console_t
, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QStringList, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<Console, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

>,
    nullptr
} };


const QMetaObject *Console::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Console::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Console.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Console::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Console::cdc_new_string()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Console::manual_override_new_string()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Console::firmware_update_new_string()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Console::connection_status_description_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
