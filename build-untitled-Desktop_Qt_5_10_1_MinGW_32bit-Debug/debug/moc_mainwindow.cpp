/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../release3.0/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dialog_t {
    QByteArrayData data[3];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_t qt_meta_stringdata_Dialog = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Dialog"
QT_MOC_LITERAL(1, 7, 8), // "showFile"
QT_MOC_LITERAL(2, 16, 0) // ""

    },
    "Dialog\0showFile\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dialog *_t = static_cast<Dialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showFile(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog.data,
      qt_meta_data_Dialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[27];
    char stringdata0[464];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 23), // "on_actionopen_triggered"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 22), // "on_actionnew_triggered"
QT_MOC_LITERAL(4, 59, 23), // "on_actionfind_triggered"
QT_MOC_LITERAL(5, 83, 26), // "on_actionreplace_triggered"
QT_MOC_LITERAL(6, 110, 22), // "on_actioncut_triggered"
QT_MOC_LITERAL(7, 133, 24), // "on_actionpaste_triggered"
QT_MOC_LITERAL(8, 158, 23), // "on_actioncopy_triggered"
QT_MOC_LITERAL(9, 182, 24), // "ShowCurrentFormatChanged"
QT_MOC_LITERAL(10, 207, 3), // "fmt"
QT_MOC_LITERAL(11, 211, 15), // "ShowSizeSpinBox"
QT_MOC_LITERAL(12, 227, 16), // "ShowFontComboBox"
QT_MOC_LITERAL(13, 244, 16), // "ShowItalictooBar"
QT_MOC_LITERAL(14, 261, 14), // "ShowBoldtooBar"
QT_MOC_LITERAL(15, 276, 19), // "ShowUnderlinetooBar"
QT_MOC_LITERAL(16, 296, 14), // "ShowWraptooBar"
QT_MOC_LITERAL(17, 311, 14), // "ShowTextRowCol"
QT_MOC_LITERAL(18, 326, 10), // "upSyncFile"
QT_MOC_LITERAL(19, 337, 12), // "downSyncFile"
QT_MOC_LITERAL(20, 350, 13), // "getServerFile"
QT_MOC_LITERAL(21, 364, 8), // "localAdd"
QT_MOC_LITERAL(22, 373, 10), // "serverFile"
QT_MOC_LITERAL(23, 384, 11), // "readContent"
QT_MOC_LITERAL(24, 396, 13), // "putServerFile"
QT_MOC_LITERAL(25, 410, 25), // "on_actionupload_triggered"
QT_MOC_LITERAL(26, 436, 27) // "on_actiondownload_triggered"

    },
    "MainWindow\0on_actionopen_triggered\0\0"
    "on_actionnew_triggered\0on_actionfind_triggered\0"
    "on_actionreplace_triggered\0"
    "on_actioncut_triggered\0on_actionpaste_triggered\0"
    "on_actioncopy_triggered\0"
    "ShowCurrentFormatChanged\0fmt\0"
    "ShowSizeSpinBox\0ShowFontComboBox\0"
    "ShowItalictooBar\0ShowBoldtooBar\0"
    "ShowUnderlinetooBar\0ShowWraptooBar\0"
    "ShowTextRowCol\0upSyncFile\0downSyncFile\0"
    "getServerFile\0localAdd\0serverFile\0"
    "readContent\0putServerFile\0"
    "on_actionupload_triggered\0"
    "on_actiondownload_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  124,    2, 0x08 /* Private */,
       3,    0,  125,    2, 0x08 /* Private */,
       4,    0,  126,    2, 0x08 /* Private */,
       5,    0,  127,    2, 0x08 /* Private */,
       6,    0,  128,    2, 0x08 /* Private */,
       7,    0,  129,    2, 0x08 /* Private */,
       8,    0,  130,    2, 0x08 /* Private */,
       9,    1,  131,    2, 0x08 /* Private */,
      11,    1,  134,    2, 0x08 /* Private */,
      12,    1,  137,    2, 0x08 /* Private */,
      13,    0,  140,    2, 0x08 /* Private */,
      14,    0,  141,    2, 0x08 /* Private */,
      15,    0,  142,    2, 0x08 /* Private */,
      16,    0,  143,    2, 0x08 /* Private */,
      17,    0,  144,    2, 0x08 /* Private */,
      18,    0,  145,    2, 0x08 /* Private */,
      19,    0,  146,    2, 0x08 /* Private */,
      20,    2,  147,    2, 0x08 /* Private */,
      23,    0,  152,    2, 0x08 /* Private */,
      24,    2,  153,    2, 0x08 /* Private */,
      25,    0,  158,    2, 0x08 /* Private */,
      26,    0,  159,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QFont,   10,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   21,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   21,   22,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionopen_triggered(); break;
        case 1: _t->on_actionnew_triggered(); break;
        case 2: _t->on_actionfind_triggered(); break;
        case 3: _t->on_actionreplace_triggered(); break;
        case 4: _t->on_actioncut_triggered(); break;
        case 5: _t->on_actionpaste_triggered(); break;
        case 6: _t->on_actioncopy_triggered(); break;
        case 7: _t->ShowCurrentFormatChanged((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 8: _t->ShowSizeSpinBox((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->ShowFontComboBox((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->ShowItalictooBar(); break;
        case 11: _t->ShowBoldtooBar(); break;
        case 12: _t->ShowUnderlinetooBar(); break;
        case 13: _t->ShowWraptooBar(); break;
        case 14: _t->ShowTextRowCol(); break;
        case 15: _t->upSyncFile(); break;
        case 16: _t->downSyncFile(); break;
        case 17: _t->getServerFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 18: _t->readContent(); break;
        case 19: _t->putServerFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 20: _t->on_actionupload_triggered(); break;
        case 21: _t->on_actiondownload_triggered(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 22;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
