/****************************************************************************
** Meta object code from reading C++ file 'MemoryTablemodel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Master_Terminal/src/engine/memory/MemoryTablemodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MemoryTablemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MemoryTablemodel_t {
    const uint offsetsAndSize[6];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MemoryTablemodel_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MemoryTablemodel_t qt_meta_stringdata_MemoryTablemodel = {
    {
QT_MOC_LITERAL(0, 16), // "MemoryTablemodel"
QT_MOC_LITERAL(17, 11), // "QML.Element"
QT_MOC_LITERAL(29, 4) // "auto"

    },
    "MemoryTablemodel\0QML.Element\0auto"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MemoryTablemodel[] = {

 // content:
      10,       // revision
       0,       // classname
       1,   14, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // classinfo: key, value
       1,    2,

       0        // eod
};

void MemoryTablemodel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject MemoryTablemodel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractTableModel::staticMetaObject>(),
    qt_meta_stringdata_MemoryTablemodel.offsetsAndSize,
    qt_meta_data_MemoryTablemodel,
    qt_static_metacall,
    nullptr,
qt_metaTypeArray<
MemoryTablemodel



>,
    nullptr
} };


const QMetaObject *MemoryTablemodel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MemoryTablemodel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MemoryTablemodel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int MemoryTablemodel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
