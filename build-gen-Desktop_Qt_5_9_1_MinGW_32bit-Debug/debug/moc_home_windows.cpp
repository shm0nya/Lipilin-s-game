/****************************************************************************
** Meta object code from reading C++ file 'home_windows.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qt/home_windows.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'home_windows.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Home_windows_t {
    QByteArrayData data[11];
    char stringdata0[230];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Home_windows_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Home_windows_t qt_meta_stringdata_Home_windows = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Home_windows"
QT_MOC_LITERAL(1, 13, 7), // "mistake"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 3), // "str"
QT_MOC_LITERAL(4, 26, 30), // "on_friend_edit_editingFinished"
QT_MOC_LITERAL(5, 57, 32), // "on_opponent_edit_editingFinished"
QT_MOC_LITERAL(6, 90, 33), // "on_P_key_size_slider_valueCha..."
QT_MOC_LITERAL(7, 124, 5), // "value"
QT_MOC_LITERAL(8, 130, 33), // "on_S_key_size_slider_valueCha..."
QT_MOC_LITERAL(9, 164, 32), // "on_P_key_generate_button_clicked"
QT_MOC_LITERAL(10, 197, 32) // "on_S_key_generate_button_clicked"

    },
    "Home_windows\0mistake\0\0str\0"
    "on_friend_edit_editingFinished\0"
    "on_opponent_edit_editingFinished\0"
    "on_P_key_size_slider_valueChanged\0"
    "value\0on_S_key_size_slider_valueChanged\0"
    "on_P_key_generate_button_clicked\0"
    "on_S_key_generate_button_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Home_windows[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   52,    2, 0x08 /* Private */,
       5,    0,   53,    2, 0x08 /* Private */,
       6,    1,   54,    2, 0x08 /* Private */,
       8,    1,   57,    2, 0x08 /* Private */,
       9,    0,   60,    2, 0x08 /* Private */,
      10,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Home_windows::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Home_windows *_t = static_cast<Home_windows *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mistake((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->on_friend_edit_editingFinished(); break;
        case 2: _t->on_opponent_edit_editingFinished(); break;
        case 3: _t->on_P_key_size_slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_S_key_size_slider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_P_key_generate_button_clicked(); break;
        case 6: _t->on_S_key_generate_button_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Home_windows::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Home_windows::mistake)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Home_windows::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Home_windows.data,
      qt_meta_data_Home_windows,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Home_windows::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Home_windows::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Home_windows.stringdata0))
        return static_cast<void*>(const_cast< Home_windows*>(this));
    return QWidget::qt_metacast(_clname);
}

int Home_windows::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Home_windows::mistake(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_error_t {
    QByteArrayData data[4];
    char stringdata0[22];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_error_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_error_t qt_meta_stringdata_error = {
    {
QT_MOC_LITERAL(0, 0, 5), // "error"
QT_MOC_LITERAL(1, 6, 10), // "send_error"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 3) // "str"

    },
    "error\0send_error\0\0str"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_error[] = {

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
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void error::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        error *_t = static_cast<error *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject error::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_error.data,
      qt_meta_data_error,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *error::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *error::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_error.stringdata0))
        return static_cast<void*>(const_cast< error*>(this));
    return QObject::qt_metacast(_clname);
}

int error::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
