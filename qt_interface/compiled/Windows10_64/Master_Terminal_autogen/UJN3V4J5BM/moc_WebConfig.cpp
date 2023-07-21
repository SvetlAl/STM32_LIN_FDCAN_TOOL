/****************************************************************************
** Meta object code from reading C++ file 'WebConfig.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/web/WebConfig.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WebConfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WebConfig_t {
    const uint offsetsAndSize[16];
    char stringdata0[124];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_WebConfig_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_WebConfig_t qt_meta_stringdata_WebConfig = {
    {
QT_MOC_LITERAL(0, 9), // "WebConfig"
QT_MOC_LITERAL(10, 23), // "version_info_urlChanged"
QT_MOC_LITERAL(34, 0), // ""
QT_MOC_LITERAL(35, 17), // "update_urlChanged"
QT_MOC_LITERAL(53, 24), // "code_override_urlChanged"
QT_MOC_LITERAL(78, 16), // "version_info_url"
QT_MOC_LITERAL(95, 10), // "update_url"
QT_MOC_LITERAL(106, 17) // "code_override_url"

    },
    "WebConfig\0version_info_urlChanged\0\0"
    "update_urlChanged\0code_override_urlChanged\0"
    "version_info_url\0update_url\0"
    "code_override_url"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WebConfig[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       3,   35, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x06,    4 /* Public */,
       3,    0,   33,    2, 0x06,    5 /* Public */,
       4,    0,   34,    2, 0x06,    6 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       5, QMetaType::QString, 0x00015103, uint(0), 0,
       6, QMetaType::QString, 0x00015103, uint(1), 0,
       7, QMetaType::QString, 0x00015103, uint(2), 0,

       0        // eod
};

void WebConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WebConfig *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->version_info_urlChanged(); break;
        case 1: _t->update_urlChanged(); break;
        case 2: _t->code_override_urlChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WebConfig::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebConfig::version_info_urlChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WebConfig::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebConfig::update_urlChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WebConfig::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebConfig::code_override_urlChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<WebConfig *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->version_info_url(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->update_url(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->code_override_url(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<WebConfig *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setVersion_info_url(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setUpdate_url(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setCode_override_url(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

const QMetaObject WebConfig::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_WebConfig.offsetsAndSize,
    qt_meta_data_WebConfig,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_WebConfig_t
, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<WebConfig, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *WebConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WebConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WebConfig.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WebConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void WebConfig::version_info_urlChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WebConfig::update_urlChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WebConfig::code_override_urlChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
