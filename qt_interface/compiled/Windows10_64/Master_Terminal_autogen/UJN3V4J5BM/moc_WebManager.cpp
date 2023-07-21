/****************************************************************************
** Meta object code from reading C++ file 'WebManager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/web/WebManager.h"
#include <QtNetwork/QSslError>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WebManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WebManager_t {
    const uint offsetsAndSize[20];
    char stringdata0[163];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_WebManager_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_WebManager_t qt_meta_stringdata_WebManager = {
    {
QT_MOC_LITERAL(0, 10), // "WebManager"
QT_MOC_LITERAL(11, 27), // "deviceVersionInfoDownloaded"
QT_MOC_LITERAL(39, 0), // ""
QT_MOC_LITERAL(40, 22), // "deviceUpdateDownloaded"
QT_MOC_LITERAL(63, 7), // "_string"
QT_MOC_LITERAL(71, 28), // "deviceCodeOverrideDownloaded"
QT_MOC_LITERAL(100, 12), // "resetOnError"
QT_MOC_LITERAL(113, 16), // "downloadFinished"
QT_MOC_LITERAL(130, 15), // "put_up_download"
QT_MOC_LITERAL(146, 16) // "_rq_target_value"

    },
    "WebManager\0deviceVersionInfoDownloaded\0"
    "\0deviceUpdateDownloaded\0_string\0"
    "deviceCodeOverrideDownloaded\0resetOnError\0"
    "downloadFinished\0put_up_download\0"
    "_rq_target_value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WebManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    1 /* Public */,
       3,    1,   51,    2, 0x06,    2 /* Public */,
       5,    0,   54,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   55,    2, 0x0a,    5 /* Public */,
       7,    0,   56,    2, 0x0a,    6 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       8,    1,   57,    2, 0x02,    7 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Bool, QMetaType::Int,    9,

       0        // eod
};

void WebManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WebManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->deviceVersionInfoDownloaded(); break;
        case 1: _t->deviceUpdateDownloaded((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->deviceCodeOverrideDownloaded(); break;
        case 3: _t->resetOnError(); break;
        case 4: _t->downloadFinished(); break;
        case 5: { bool _r = _t->put_up_download((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WebManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebManager::deviceVersionInfoDownloaded)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WebManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebManager::deviceUpdateDownloaded)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WebManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebManager::deviceCodeOverrideDownloaded)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject WebManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_WebManager.offsetsAndSize,
    qt_meta_data_WebManager,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_WebManager_t
, QtPrivate::TypeAndForceComplete<WebManager, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>

>,
    nullptr
} };


const QMetaObject *WebManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WebManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WebManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WebManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void WebManager::deviceVersionInfoDownloaded()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WebManager::deviceUpdateDownloaded(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WebManager::deviceCodeOverrideDownloaded()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
