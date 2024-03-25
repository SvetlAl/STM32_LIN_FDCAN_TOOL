/****************************************************************************
** Meta object code from reading C++ file 'PngExtractor.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/resource_extractor/PngExtractor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PngExtractor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PngExtractor_t {
    const uint offsetsAndSize[22];
    char stringdata0[192];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_PngExtractor_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_PngExtractor_t qt_meta_stringdata_PngExtractor = {
    {
QT_MOC_LITERAL(0, 12), // "PngExtractor"
QT_MOC_LITERAL(13, 9), // "comp_test"
QT_MOC_LITERAL(23, 0), // ""
QT_MOC_LITERAL(24, 24), // "operation_result_changed"
QT_MOC_LITERAL(49, 23), // "target_filename_changed"
QT_MOC_LITERAL(73, 28), // "replacement_filename_changed"
QT_MOC_LITERAL(102, 21), // "output_folder_changed"
QT_MOC_LITERAL(124, 16), // "operation_result"
QT_MOC_LITERAL(141, 15), // "target_filename"
QT_MOC_LITERAL(157, 20), // "replacement_filename"
QT_MOC_LITERAL(178, 13) // "output_folder"

    },
    "PngExtractor\0comp_test\0\0"
    "operation_result_changed\0"
    "target_filename_changed\0"
    "replacement_filename_changed\0"
    "output_folder_changed\0operation_result\0"
    "target_filename\0replacement_filename\0"
    "output_folder"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PngExtractor[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       4,   21, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x02,    5 /* Public */,

 // methods: parameters
    QMetaType::Void,

 // properties: name, type, flags
       7, QMetaType::QString, 0x00015003, uint(1879048195), 0,
       8, QMetaType::QString, 0x00015103, uint(1879048196), 0,
       9, QMetaType::QString, 0x00015103, uint(1879048197), 0,
      10, QMetaType::QString, 0x00015103, uint(1879048198), 0,

       0        // eod
};

void PngExtractor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PngExtractor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->comp_test(); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PngExtractor *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->op_result(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->target_filename(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->replacement_filename(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->output_folder(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<PngExtractor *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setOp_result(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setTarget_filename(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setReplacement_filename(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setOutput_folder(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

const QMetaObject PngExtractor::staticMetaObject = { {
    QMetaObject::SuperData::link<ResourceExtractor::staticMetaObject>(),
    qt_meta_stringdata_PngExtractor.offsetsAndSize,
    qt_meta_data_PngExtractor,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_PngExtractor_t
, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<PngExtractor, std::true_type>

, QtPrivate::TypeAndForceComplete<void, std::false_type>

>,
    nullptr
} };


const QMetaObject *PngExtractor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PngExtractor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PngExtractor.stringdata0))
        return static_cast<void*>(this);
    return ResourceExtractor::qt_metacast(_clname);
}

int PngExtractor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ResourceExtractor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
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
// If you get a compile error in this function it can be because either
//     a) You are using a NOTIFY signal that does not exist. Fix it.
//     b) You are using a NOTIFY signal that does exist (in a parent class) but has a non-empty parameter list. This is a moc limitation.
[[maybe_unused]] static void checkNotifySignalValidity_PngExtractor(PngExtractor *t) {
    t->operation_result_changed();
    t->target_filename_changed();
    t->replacement_filename_changed();
    t->output_folder_changed();
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
