/****************************************************************************
** Meta object code from reading C++ file 'QSerialPortConfigProperty.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/serial_port/QSerialPortConfigProperty.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSerialPortConfigProperty.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QSerialPortConfigProperty_t {
    const uint offsetsAndSize[24];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QSerialPortConfigProperty_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QSerialPortConfigProperty_t qt_meta_stringdata_QSerialPortConfigProperty = {
    {
QT_MOC_LITERAL(0, 25), // "QSerialPortConfigProperty"
QT_MOC_LITERAL(26, 7), // "changed"
QT_MOC_LITERAL(34, 0), // ""
QT_MOC_LITERAL(35, 4), // "item"
QT_MOC_LITERAL(40, 1), // "i"
QT_MOC_LITERAL(42, 12), // "current_item"
QT_MOC_LITERAL(55, 15), // "getCurrentIndex"
QT_MOC_LITERAL(71, 15), // "setCurrentIndex"
QT_MOC_LITERAL(87, 6), // "_index"
QT_MOC_LITERAL(94, 6), // "length"
QT_MOC_LITERAL(101, 7), // "isEmpty"
QT_MOC_LITERAL(109, 13) // "current_index"

    },
    "QSerialPortConfigProperty\0changed\0\0"
    "item\0i\0current_item\0getCurrentIndex\0"
    "setCurrentIndex\0_index\0length\0isEmpty\0"
    "current_index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSerialPortConfigProperty[] = {

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

void QSerialPortConfigProperty::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QSerialPortConfigProperty *>(_o);
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
            using _t = void (QSerialPortConfigProperty::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QSerialPortConfigProperty::changed)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QSerialPortConfigProperty *>(_o);
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

const QMetaObject QSerialPortConfigProperty::staticMetaObject = { {
    QMetaObject::SuperData::link<Obj_List_Model<QSerialPortConfigItem>::staticMetaObject>(),
    qt_meta_stringdata_QSerialPortConfigProperty.offsetsAndSize,
    qt_meta_data_QSerialPortConfigProperty,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QSerialPortConfigProperty_t
, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<QVariant, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<QSerialPortConfigProperty, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

, QtPrivate::TypeAndForceComplete<QVariant, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<QVariant, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>

>,
    nullptr
} };


const QMetaObject *QSerialPortConfigProperty::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QSerialPortConfigProperty::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QSerialPortConfigProperty.stringdata0))
        return static_cast<void*>(this);
    return Obj_List_Model<QSerialPortConfigItem>::qt_metacast(_clname);
}

int QSerialPortConfigProperty::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Obj_List_Model<QSerialPortConfigItem>::qt_metacall(_c, _id, _a);
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
void QSerialPortConfigProperty::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_QSerialPortConfigProperty_PortNumber_t {
    const uint offsetsAndSize[2];
    char stringdata0[37];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QSerialPortConfigProperty_PortNumber_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QSerialPortConfigProperty_PortNumber_t qt_meta_stringdata_QSerialPortConfigProperty_PortNumber = {
    {
QT_MOC_LITERAL(0, 36) // "QSerialPortConfigProperty_Por..."

    },
    "QSerialPortConfigProperty_PortNumber"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSerialPortConfigProperty_PortNumber[] = {

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

void QSerialPortConfigProperty_PortNumber::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject QSerialPortConfigProperty_PortNumber::staticMetaObject = { {
    QMetaObject::SuperData::link<QSerialPortConfigProperty::staticMetaObject>(),
    qt_meta_stringdata_QSerialPortConfigProperty_PortNumber.offsetsAndSize,
    qt_meta_data_QSerialPortConfigProperty_PortNumber,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QSerialPortConfigProperty_PortNumber_t
, QtPrivate::TypeAndForceComplete<QSerialPortConfigProperty_PortNumber, std::true_type>



>,
    nullptr
} };


const QMetaObject *QSerialPortConfigProperty_PortNumber::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QSerialPortConfigProperty_PortNumber::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QSerialPortConfigProperty_PortNumber.stringdata0))
        return static_cast<void*>(this);
    return QSerialPortConfigProperty::qt_metacast(_clname);
}

int QSerialPortConfigProperty_PortNumber::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSerialPortConfigProperty::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_QSerialPortConfigProperty_FlowControl_t {
    const uint offsetsAndSize[2];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QSerialPortConfigProperty_FlowControl_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QSerialPortConfigProperty_FlowControl_t qt_meta_stringdata_QSerialPortConfigProperty_FlowControl = {
    {
QT_MOC_LITERAL(0, 37) // "QSerialPortConfigProperty_Flo..."

    },
    "QSerialPortConfigProperty_FlowControl"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSerialPortConfigProperty_FlowControl[] = {

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

void QSerialPortConfigProperty_FlowControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject QSerialPortConfigProperty_FlowControl::staticMetaObject = { {
    QMetaObject::SuperData::link<QSerialPortConfigProperty::staticMetaObject>(),
    qt_meta_stringdata_QSerialPortConfigProperty_FlowControl.offsetsAndSize,
    qt_meta_data_QSerialPortConfigProperty_FlowControl,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QSerialPortConfigProperty_FlowControl_t
, QtPrivate::TypeAndForceComplete<QSerialPortConfigProperty_FlowControl, std::true_type>



>,
    nullptr
} };


const QMetaObject *QSerialPortConfigProperty_FlowControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QSerialPortConfigProperty_FlowControl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QSerialPortConfigProperty_FlowControl.stringdata0))
        return static_cast<void*>(this);
    return QSerialPortConfigProperty::qt_metacast(_clname);
}

int QSerialPortConfigProperty_FlowControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSerialPortConfigProperty::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_QSerialPortConfigProperty_BaudRate_t {
    const uint offsetsAndSize[6];
    char stringdata0[56];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QSerialPortConfigProperty_BaudRate_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QSerialPortConfigProperty_BaudRate_t qt_meta_stringdata_QSerialPortConfigProperty_BaudRate = {
    {
QT_MOC_LITERAL(0, 34), // "QSerialPortConfigProperty_Bau..."
QT_MOC_LITERAL(35, 7), // "changed"
QT_MOC_LITERAL(43, 12) // "custom_value"

    },
    "QSerialPortConfigProperty_BaudRate\0"
    "changed\0custom_value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSerialPortConfigProperty_BaudRate[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       1,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       2, QMetaType::Int, 0x00015003, uint(1879048193), 0,

       0        // eod
};

void QSerialPortConfigProperty_BaudRate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QSerialPortConfigProperty_BaudRate *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->custom_value(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QSerialPortConfigProperty_BaudRate *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->set_custom_value(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject QSerialPortConfigProperty_BaudRate::staticMetaObject = { {
    QMetaObject::SuperData::link<QSerialPortConfigProperty::staticMetaObject>(),
    qt_meta_stringdata_QSerialPortConfigProperty_BaudRate.offsetsAndSize,
    qt_meta_data_QSerialPortConfigProperty_BaudRate,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QSerialPortConfigProperty_BaudRate_t
, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<QSerialPortConfigProperty_BaudRate, std::true_type>



>,
    nullptr
} };


const QMetaObject *QSerialPortConfigProperty_BaudRate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QSerialPortConfigProperty_BaudRate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QSerialPortConfigProperty_BaudRate.stringdata0))
        return static_cast<void*>(this);
    return QSerialPortConfigProperty::qt_metacast(_clname);
}

int QSerialPortConfigProperty_BaudRate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSerialPortConfigProperty::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
// If you get a compile error in this function it can be because either
//     a) You are using a NOTIFY signal that does not exist. Fix it.
//     b) You are using a NOTIFY signal that does exist (in a parent class) but has a non-empty parameter list. This is a moc limitation.
[[maybe_unused]] static void checkNotifySignalValidity_QSerialPortConfigProperty_BaudRate(QSerialPortConfigProperty_BaudRate *t) {
    t->changed();
}
struct qt_meta_stringdata_QSerialPortConfigProperty_StopBits_t {
    const uint offsetsAndSize[2];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QSerialPortConfigProperty_StopBits_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QSerialPortConfigProperty_StopBits_t qt_meta_stringdata_QSerialPortConfigProperty_StopBits = {
    {
QT_MOC_LITERAL(0, 34) // "QSerialPortConfigProperty_Sto..."

    },
    "QSerialPortConfigProperty_StopBits"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSerialPortConfigProperty_StopBits[] = {

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

void QSerialPortConfigProperty_StopBits::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject QSerialPortConfigProperty_StopBits::staticMetaObject = { {
    QMetaObject::SuperData::link<QSerialPortConfigProperty::staticMetaObject>(),
    qt_meta_stringdata_QSerialPortConfigProperty_StopBits.offsetsAndSize,
    qt_meta_data_QSerialPortConfigProperty_StopBits,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QSerialPortConfigProperty_StopBits_t
, QtPrivate::TypeAndForceComplete<QSerialPortConfigProperty_StopBits, std::true_type>



>,
    nullptr
} };


const QMetaObject *QSerialPortConfigProperty_StopBits::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QSerialPortConfigProperty_StopBits::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QSerialPortConfigProperty_StopBits.stringdata0))
        return static_cast<void*>(this);
    return QSerialPortConfigProperty::qt_metacast(_clname);
}

int QSerialPortConfigProperty_StopBits::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSerialPortConfigProperty::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_QSerialPortConfigProperty_Parity_t {
    const uint offsetsAndSize[2];
    char stringdata0[33];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QSerialPortConfigProperty_Parity_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QSerialPortConfigProperty_Parity_t qt_meta_stringdata_QSerialPortConfigProperty_Parity = {
    {
QT_MOC_LITERAL(0, 32) // "QSerialPortConfigProperty_Parity"

    },
    "QSerialPortConfigProperty_Parity"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSerialPortConfigProperty_Parity[] = {

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

void QSerialPortConfigProperty_Parity::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject QSerialPortConfigProperty_Parity::staticMetaObject = { {
    QMetaObject::SuperData::link<QSerialPortConfigProperty::staticMetaObject>(),
    qt_meta_stringdata_QSerialPortConfigProperty_Parity.offsetsAndSize,
    qt_meta_data_QSerialPortConfigProperty_Parity,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QSerialPortConfigProperty_Parity_t
, QtPrivate::TypeAndForceComplete<QSerialPortConfigProperty_Parity, std::true_type>



>,
    nullptr
} };


const QMetaObject *QSerialPortConfigProperty_Parity::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QSerialPortConfigProperty_Parity::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QSerialPortConfigProperty_Parity.stringdata0))
        return static_cast<void*>(this);
    return QSerialPortConfigProperty::qt_metacast(_clname);
}

int QSerialPortConfigProperty_Parity::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSerialPortConfigProperty::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_QSerialPortConfigProperty_DataBits_t {
    const uint offsetsAndSize[2];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QSerialPortConfigProperty_DataBits_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QSerialPortConfigProperty_DataBits_t qt_meta_stringdata_QSerialPortConfigProperty_DataBits = {
    {
QT_MOC_LITERAL(0, 34) // "QSerialPortConfigProperty_Dat..."

    },
    "QSerialPortConfigProperty_DataBits"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSerialPortConfigProperty_DataBits[] = {

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

void QSerialPortConfigProperty_DataBits::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject QSerialPortConfigProperty_DataBits::staticMetaObject = { {
    QMetaObject::SuperData::link<QSerialPortConfigProperty::staticMetaObject>(),
    qt_meta_stringdata_QSerialPortConfigProperty_DataBits.offsetsAndSize,
    qt_meta_data_QSerialPortConfigProperty_DataBits,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QSerialPortConfigProperty_DataBits_t
, QtPrivate::TypeAndForceComplete<QSerialPortConfigProperty_DataBits, std::true_type>



>,
    nullptr
} };


const QMetaObject *QSerialPortConfigProperty_DataBits::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QSerialPortConfigProperty_DataBits::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QSerialPortConfigProperty_DataBits.stringdata0))
        return static_cast<void*>(this);
    return QSerialPortConfigProperty::qt_metacast(_clname);
}

int QSerialPortConfigProperty_DataBits::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSerialPortConfigProperty::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
