/****************************************************************************
** Meta object code from reading C++ file 'ResourceExtractor.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/resource_extractor/ResourceExtractor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ResourceExtractor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ResourceExtractor_t {
    const uint offsetsAndSize[20];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ResourceExtractor_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ResourceExtractor_t qt_meta_stringdata_ResourceExtractor = {
    {
QT_MOC_LITERAL(0, 17), // "ResourceExtractor"
QT_MOC_LITERAL(18, 28), // "replacement_filename_changed"
QT_MOC_LITERAL(47, 0), // ""
QT_MOC_LITERAL(48, 23), // "target_filename_changed"
QT_MOC_LITERAL(72, 21), // "output_folder_changed"
QT_MOC_LITERAL(94, 24), // "operation_result_changed"
QT_MOC_LITERAL(119, 11), // "extract_all"
QT_MOC_LITERAL(131, 16), // "make_replacement"
QT_MOC_LITERAL(148, 6), // "size_t"
QT_MOC_LITERAL(155, 9) // "entry_num"

    },
    "ResourceExtractor\0replacement_filename_changed\0"
    "\0target_filename_changed\0output_folder_changed\0"
    "operation_result_changed\0extract_all\0"
    "make_replacement\0size_t\0entry_num"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ResourceExtractor[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    1 /* Public */,
       3,    0,   51,    2, 0x06,    2 /* Public */,
       4,    0,   52,    2, 0x06,    3 /* Public */,
       5,    0,   53,    2, 0x06,    4 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   54,    2, 0x02,    5 /* Public */,
       7,    1,   55,    2, 0x02,    6 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void ResourceExtractor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ResourceExtractor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->replacement_filename_changed(); break;
        case 1: _t->target_filename_changed(); break;
        case 2: _t->output_folder_changed(); break;
        case 3: _t->operation_result_changed(); break;
        case 4: _t->extract_all(); break;
        case 5: _t->make_replacement((*reinterpret_cast< std::add_pointer_t<size_t>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ResourceExtractor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ResourceExtractor::replacement_filename_changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ResourceExtractor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ResourceExtractor::target_filename_changed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ResourceExtractor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ResourceExtractor::output_folder_changed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ResourceExtractor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ResourceExtractor::operation_result_changed)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject ResourceExtractor::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ResourceExtractor.offsetsAndSize,
    qt_meta_data_ResourceExtractor,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ResourceExtractor_t
, QtPrivate::TypeAndForceComplete<ResourceExtractor, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<size_t, std::false_type>

>,
    nullptr
} };


const QMetaObject *ResourceExtractor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ResourceExtractor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ResourceExtractor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ResourceExtractor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ResourceExtractor::replacement_filename_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ResourceExtractor::target_filename_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ResourceExtractor::output_folder_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ResourceExtractor::operation_result_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
