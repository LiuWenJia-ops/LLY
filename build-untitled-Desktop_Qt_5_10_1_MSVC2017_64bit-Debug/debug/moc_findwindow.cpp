/****************************************************************************
** Meta object code from reading C++ file 'findwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../v3lww/findwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'findwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FindWindow_t {
    QByteArrayData data[5];
    char stringdata0[55];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FindWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FindWindow_t qt_meta_stringdata_FindWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "FindWindow"
QT_MOC_LITERAL(1, 11, 12), // "showFindText"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "modeChanged"
QT_MOC_LITERAL(4, 37, 17) // "renewSearchResult"

    },
    "FindWindow\0showFindText\0\0modeChanged\0"
    "renewSearchResult"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FindWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    1,   30,    2, 0x08 /* Private */,
       4,    0,   33,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void FindWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FindWindow *_t = static_cast<FindWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showFindText(); break;
        case 1: _t->modeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->renewSearchResult(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FindWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FindWindow.data,
      qt_meta_data_FindWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FindWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FindWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FindWindow.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int FindWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
