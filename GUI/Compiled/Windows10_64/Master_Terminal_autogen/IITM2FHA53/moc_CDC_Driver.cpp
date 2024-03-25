/****************************************************************************
** Meta object code from reading C++ file 'CDC_Driver.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/serial_port/CDC_Driver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CDC_Driver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CDC_Driver_t {
    const uint offsetsAndSize[12];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_CDC_Driver_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_CDC_Driver_t qt_meta_stringdata_CDC_Driver = {
    {
QT_MOC_LITERAL(0, 10), // "CDC_Driver"
QT_MOC_LITERAL(11, 25), // "connection_status_changed"
QT_MOC_LITERAL(37, 0), // ""
QT_MOC_LITERAL(38, 18), // "async_read_changed"
QT_MOC_LITERAL(57, 19), // "async_data_passover"
QT_MOC_LITERAL(77, 3) // "arr"

    },
    "CDC_Driver\0connection_status_changed\0"
    "\0async_read_changed\0async_data_passover\0"
    "arr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CDC_Driver[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x06,    1 /* Public */,
       3,    0,   33,    2, 0x06,    2 /* Public */,
       4,    1,   34,    2, 0x06,    3 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    5,

       0        // eod
};

void CDC_Driver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CDC_Driver *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connection_status_changed(); break;
        case 1: _t->async_read_changed(); break;
        case 2: _t->async_data_passover((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CDC_Driver::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CDC_Driver::connection_status_changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CDC_Driver::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CDC_Driver::async_read_changed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CDC_Driver::*)(const QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CDC_Driver::async_data_passover)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject CDC_Driver::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CDC_Driver.offsetsAndSize,
    qt_meta_data_CDC_Driver,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_CDC_Driver_t
, QtPrivate::TypeAndForceComplete<CDC_Driver, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QByteArray, std::false_type>



>,
    nullptr
} };


const QMetaObject *CDC_Driver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CDC_Driver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CDC_Driver.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CDC_Driver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
    return _id;
}

// SIGNAL 0
void CDC_Driver::connection_status_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CDC_Driver::async_read_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CDC_Driver::async_data_passover(const QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
