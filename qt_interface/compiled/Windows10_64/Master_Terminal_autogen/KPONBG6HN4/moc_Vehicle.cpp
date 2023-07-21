/****************************************************************************
** Meta object code from reading C++ file 'Vehicle.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/vehicle/Vehicle.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Vehicle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Vehicle_t {
    const uint offsetsAndSize[68];
    char stringdata0[638];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Vehicle_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Vehicle_t qt_meta_stringdata_Vehicle = {
    {
QT_MOC_LITERAL(0, 7), // "Vehicle"
QT_MOC_LITERAL(8, 18), // "model_name_changed"
QT_MOC_LITERAL(27, 0), // ""
QT_MOC_LITERAL(28, 13), // "model_changed"
QT_MOC_LITERAL(42, 13), // "modes_changed"
QT_MOC_LITERAL(56, 23), // "speedometer_mlt_changed"
QT_MOC_LITERAL(80, 20), // "odometer_mlt_changed"
QT_MOC_LITERAL(101, 18), // "cruise_mlt_changed"
QT_MOC_LITERAL(120, 23), // "tyres_threshold_changed"
QT_MOC_LITERAL(144, 22), // "id_speedometer_changed"
QT_MOC_LITERAL(167, 28), // "id_speedometer_extra_changed"
QT_MOC_LITERAL(196, 19), // "id_odometer_changed"
QT_MOC_LITERAL(216, 17), // "id_cruise_changed"
QT_MOC_LITERAL(234, 35), // "is_speedometer_mlt_availableC..."
QT_MOC_LITERAL(270, 32), // "is_odometer_mlt_availableChanged"
QT_MOC_LITERAL(303, 30), // "is_cruise_mlt_availableChanged"
QT_MOC_LITERAL(334, 35), // "is_tyres_threshold_availableC..."
QT_MOC_LITERAL(370, 10), // "model_name"
QT_MOC_LITERAL(381, 5), // "model"
QT_MOC_LITERAL(387, 5), // "modes"
QT_MOC_LITERAL(393, 11), // "isOdoFreeze"
QT_MOC_LITERAL(405, 10), // "isTestMode"
QT_MOC_LITERAL(416, 15), // "speedometer_mlt"
QT_MOC_LITERAL(432, 12), // "odometer_mlt"
QT_MOC_LITERAL(445, 10), // "cruise_mlt"
QT_MOC_LITERAL(456, 15), // "tyres_threshold"
QT_MOC_LITERAL(472, 14), // "id_speedometer"
QT_MOC_LITERAL(487, 20), // "id_speedometer_extra"
QT_MOC_LITERAL(508, 11), // "id_odometer"
QT_MOC_LITERAL(520, 9), // "id_cruise"
QT_MOC_LITERAL(530, 28), // "is_speedometer_mlt_available"
QT_MOC_LITERAL(559, 25), // "is_odometer_mlt_available"
QT_MOC_LITERAL(585, 23), // "is_cruise_mlt_available"
QT_MOC_LITERAL(609, 28) // "is_tyres_threshold_available"

    },
    "Vehicle\0model_name_changed\0\0model_changed\0"
    "modes_changed\0speedometer_mlt_changed\0"
    "odometer_mlt_changed\0cruise_mlt_changed\0"
    "tyres_threshold_changed\0id_speedometer_changed\0"
    "id_speedometer_extra_changed\0"
    "id_odometer_changed\0id_cruise_changed\0"
    "is_speedometer_mlt_availableChanged\0"
    "is_odometer_mlt_availableChanged\0"
    "is_cruise_mlt_availableChanged\0"
    "is_tyres_threshold_availableChanged\0"
    "model_name\0model\0modes\0isOdoFreeze\0"
    "isTestMode\0speedometer_mlt\0odometer_mlt\0"
    "cruise_mlt\0tyres_threshold\0id_speedometer\0"
    "id_speedometer_extra\0id_odometer\0"
    "id_cruise\0is_speedometer_mlt_available\0"
    "is_odometer_mlt_available\0"
    "is_cruise_mlt_available\0"
    "is_tyres_threshold_available"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Vehicle[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
      17,  119, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  104,    2, 0x06,   18 /* Public */,
       3,    0,  105,    2, 0x06,   19 /* Public */,
       4,    0,  106,    2, 0x06,   20 /* Public */,
       5,    0,  107,    2, 0x06,   21 /* Public */,
       6,    0,  108,    2, 0x06,   22 /* Public */,
       7,    0,  109,    2, 0x06,   23 /* Public */,
       8,    0,  110,    2, 0x06,   24 /* Public */,
       9,    0,  111,    2, 0x06,   25 /* Public */,
      10,    0,  112,    2, 0x06,   26 /* Public */,
      11,    0,  113,    2, 0x06,   27 /* Public */,
      12,    0,  114,    2, 0x06,   28 /* Public */,
      13,    0,  115,    2, 0x06,   29 /* Public */,
      14,    0,  116,    2, 0x06,   30 /* Public */,
      15,    0,  117,    2, 0x06,   31 /* Public */,
      16,    0,  118,    2, 0x06,   32 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      17, QMetaType::QString, 0x00015001, uint(0), 0,
      18, QMetaType::Int, 0x00015003, uint(1), 0,
      19, QMetaType::Int, 0x00015003, uint(2), 0,
      20, QMetaType::Bool, 0x00015001, uint(2), 0,
      21, QMetaType::Bool, 0x00015001, uint(2), 0,
      22, QMetaType::Int, 0x00015003, uint(3), 0,
      23, QMetaType::Int, 0x00015003, uint(4), 0,
      24, QMetaType::Int, 0x00015003, uint(5), 0,
      25, QMetaType::Int, 0x00015003, uint(6), 0,
      26, QMetaType::Int, 0x00015003, uint(7), 0,
      27, QMetaType::Int, 0x00015003, uint(8), 0,
      28, QMetaType::Int, 0x00015003, uint(9), 0,
      29, QMetaType::Int, 0x00015003, uint(10), 0,
      30, QMetaType::Bool, 0x00015003, uint(11), 0,
      31, QMetaType::Bool, 0x00015003, uint(12), 0,
      32, QMetaType::Bool, 0x00015003, uint(13), 0,
      33, QMetaType::Bool, 0x00015003, uint(14), 0,

       0        // eod
};

void Vehicle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Vehicle *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->model_name_changed(); break;
        case 1: _t->model_changed(); break;
        case 2: _t->modes_changed(); break;
        case 3: _t->speedometer_mlt_changed(); break;
        case 4: _t->odometer_mlt_changed(); break;
        case 5: _t->cruise_mlt_changed(); break;
        case 6: _t->tyres_threshold_changed(); break;
        case 7: _t->id_speedometer_changed(); break;
        case 8: _t->id_speedometer_extra_changed(); break;
        case 9: _t->id_odometer_changed(); break;
        case 10: _t->id_cruise_changed(); break;
        case 11: _t->is_speedometer_mlt_availableChanged(); break;
        case 12: _t->is_odometer_mlt_availableChanged(); break;
        case 13: _t->is_cruise_mlt_availableChanged(); break;
        case 14: _t->is_tyres_threshold_availableChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Vehicle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Vehicle::model_name_changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Vehicle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Vehicle::model_changed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Vehicle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Vehicle::modes_changed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Vehicle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Vehicle::speedometer_mlt_changed)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Vehicle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Vehicle::odometer_mlt_changed)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Vehicle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Vehicle::cruise_mlt_changed)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Vehicle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Vehicle::tyres_threshold_changed)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Vehicle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Vehicle::id_speedometer_changed)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Vehicle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Vehicle::id_speedometer_extra_changed)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Vehicle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Vehicle::id_odometer_changed)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (Vehicle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Vehicle::id_cruise_changed)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (Vehicle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Vehicle::is_speedometer_mlt_availableChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (Vehicle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Vehicle::is_odometer_mlt_availableChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (Vehicle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Vehicle::is_cruise_mlt_availableChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (Vehicle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Vehicle::is_tyres_threshold_availableChanged)) {
                *result = 14;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Vehicle *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->model_name(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->model(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->modes(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->isOdoFreeze(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->isTestMode(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->speedometer_mlt(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->odometer_mlt(); break;
        case 7: *reinterpret_cast< int*>(_v) = _t->cruise_mlt(); break;
        case 8: *reinterpret_cast< int*>(_v) = _t->tyres_threshold(); break;
        case 9: *reinterpret_cast< int*>(_v) = _t->id_speedometer(); break;
        case 10: *reinterpret_cast< int*>(_v) = _t->id_speedometer_extra(); break;
        case 11: *reinterpret_cast< int*>(_v) = _t->id_odometer(); break;
        case 12: *reinterpret_cast< int*>(_v) = _t->id_cruise(); break;
        case 13: *reinterpret_cast< bool*>(_v) = _t->speedometer_mlt_available(); break;
        case 14: *reinterpret_cast< bool*>(_v) = _t->odometer_mlt_available(); break;
        case 15: *reinterpret_cast< bool*>(_v) = _t->cruise_mlt_available(); break;
        case 16: *reinterpret_cast< bool*>(_v) = _t->tyres_threshold_available(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Vehicle *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->set_model(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->set_modes(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->set_speedometer_mlt(*reinterpret_cast< int*>(_v)); break;
        case 6: _t->set_odometer_mlt(*reinterpret_cast< int*>(_v)); break;
        case 7: _t->set_cruise_mlt(*reinterpret_cast< int*>(_v)); break;
        case 8: _t->set_tyres_threshold(*reinterpret_cast< int*>(_v)); break;
        case 9: _t->set_id_speedometer(*reinterpret_cast< int*>(_v)); break;
        case 10: _t->set_id_speedometer_extra(*reinterpret_cast< int*>(_v)); break;
        case 11: _t->set_id_odometer(*reinterpret_cast< int*>(_v)); break;
        case 12: _t->set_id_cruise(*reinterpret_cast< int*>(_v)); break;
        case 13:
            if (_t->is_speedometer_mlt_available != *reinterpret_cast< bool*>(_v)) {
                _t->is_speedometer_mlt_available = *reinterpret_cast< bool*>(_v);
                Q_EMIT _t->is_speedometer_mlt_availableChanged();
            }
            break;
        case 14:
            if (_t->is_odometer_mlt_available != *reinterpret_cast< bool*>(_v)) {
                _t->is_odometer_mlt_available = *reinterpret_cast< bool*>(_v);
                Q_EMIT _t->is_odometer_mlt_availableChanged();
            }
            break;
        case 15:
            if (_t->is_cruise_mlt_available != *reinterpret_cast< bool*>(_v)) {
                _t->is_cruise_mlt_available = *reinterpret_cast< bool*>(_v);
                Q_EMIT _t->is_cruise_mlt_availableChanged();
            }
            break;
        case 16:
            if (_t->is_tyres_threshold_available != *reinterpret_cast< bool*>(_v)) {
                _t->is_tyres_threshold_available = *reinterpret_cast< bool*>(_v);
                Q_EMIT _t->is_tyres_threshold_availableChanged();
            }
            break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

const QMetaObject Vehicle::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Vehicle.offsetsAndSize,
    qt_meta_data_Vehicle,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Vehicle_t
, QtPrivate::TypeAndForceComplete<QString, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<int, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<bool, std::true_type>, QtPrivate::TypeAndForceComplete<Vehicle, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *Vehicle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Vehicle::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Vehicle.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Vehicle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Vehicle::model_name_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Vehicle::model_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Vehicle::modes_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Vehicle::speedometer_mlt_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Vehicle::odometer_mlt_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Vehicle::cruise_mlt_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Vehicle::tyres_threshold_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Vehicle::id_speedometer_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Vehicle::id_speedometer_extra_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void Vehicle::id_odometer_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void Vehicle::id_cruise_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void Vehicle::is_speedometer_mlt_availableChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void Vehicle::is_odometer_mlt_availableChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void Vehicle::is_cruise_mlt_availableChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void Vehicle::is_tyres_threshold_availableChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
