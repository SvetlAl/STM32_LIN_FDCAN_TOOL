/****************************************************************************
** Meta object code from reading C++ file 'MemoryDataItem.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/memory/MemoryDataItem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MemoryDataItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MemoryDataItem_t {
    const uint offsetsAndSize[24];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MemoryDataItem_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MemoryDataItem_t qt_meta_stringdata_MemoryDataItem = {
    {
QT_MOC_LITERAL(0, 14), // "MemoryDataItem"
QT_MOC_LITERAL(15, 14), // "AddressChanged"
QT_MOC_LITERAL(30, 0), // ""
QT_MOC_LITERAL(31, 15), // "TheBytesChanged"
QT_MOC_LITERAL(47, 12), // "AsciiChanged"
QT_MOC_LITERAL(60, 5), // "print"
QT_MOC_LITERAL(66, 7), // "Address"
QT_MOC_LITERAL(74, 5), // "Byte0"
QT_MOC_LITERAL(80, 5), // "Byte4"
QT_MOC_LITERAL(86, 5), // "Byte8"
QT_MOC_LITERAL(92, 5), // "ByteC"
QT_MOC_LITERAL(98, 5) // "Ascii"

    },
    "MemoryDataItem\0AddressChanged\0\0"
    "TheBytesChanged\0AsciiChanged\0print\0"
    "Address\0Byte0\0Byte4\0Byte8\0ByteC\0Ascii"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MemoryDataItem[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       6,   42, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x06,    7 /* Public */,
       3,    0,   39,    2, 0x06,    8 /* Public */,
       4,    0,   40,    2, 0x06,    9 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   41,    2, 0x102,   10 /* Public | MethodIsConst  */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::QString,

 // properties: name, type, flags
       6, QMetaType::QString, 0x00015103, uint(0), 0,
       7, QMetaType::QString, 0x00015103, uint(1), 0,
       8, QMetaType::QString, 0x00015103, uint(1), 0,
       9, QMetaType::QString, 0x00015103, uint(1), 0,
      10, QMetaType::QString, 0x00015103, uint(1), 0,
      11, QMetaType::QString, 0x00015103, uint(2), 0,

       0        // eod
};

void MemoryDataItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MemoryDataItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->AddressChanged(); break;
        case 1: _t->TheBytesChanged(); break;
        case 2: _t->AsciiChanged(); break;
        case 3: { QString _r = _t->print();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MemoryDataItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MemoryDataItem::AddressChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MemoryDataItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MemoryDataItem::TheBytesChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MemoryDataItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MemoryDataItem::AsciiChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<MemoryDataItem *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->Address(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->Byte0(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->Byte4(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->Byte8(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->ByteC(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->Ascii(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<MemoryDataItem *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAddress(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setByte0(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setByte4(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setByte8(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setByteC(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setAscii(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject MemoryDataItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MemoryDataItem.offsetsAndSize,
    qt_meta_data_MemoryDataItem,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MemoryDataItem_t
, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<MemoryDataItem, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

, QtPrivate::TypeAndForceComplete<QString, std::false_type>

>,
    nullptr
} };


const QMetaObject *MemoryDataItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MemoryDataItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MemoryDataItem.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MemoryDataItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void MemoryDataItem::AddressChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MemoryDataItem::TheBytesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MemoryDataItem::AsciiChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
