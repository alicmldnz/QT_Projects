/****************************************************************************
** Meta object code from reading C++ file 'streamer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../streamer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'streamer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Streamer_t {
    QByteArrayData data[8];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Streamer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Streamer_t qt_meta_stringdata_Streamer = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Streamer"
QT_MOC_LITERAL(1, 9, 15), // "gst_start_timer"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 14), // "gst_stop_timer"
QT_MOC_LITERAL(4, 41, 10), // "initStream"
QT_MOC_LITERAL(5, 52, 11), // "streamFrame"
QT_MOC_LITERAL(6, 64, 11), // "updateFrame"
QT_MOC_LITERAL(7, 76, 7) // "cv::Mat"

    },
    "Streamer\0gst_start_timer\0\0gst_stop_timer\0"
    "initStream\0streamFrame\0updateFrame\0"
    "cv::Mat"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Streamer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    0,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   43,    2, 0x0a /* Public */,
       5,    0,   44,    2, 0x0a /* Public */,
       6,    1,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,

       0        // eod
};

void Streamer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Streamer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->gst_start_timer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->gst_stop_timer(); break;
        case 2: _t->initStream(); break;
        case 3: _t->streamFrame(); break;
        case 4: _t->updateFrame((*reinterpret_cast< cv::Mat(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Streamer::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Streamer::gst_start_timer)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Streamer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Streamer::gst_stop_timer)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Streamer::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Streamer.data,
    qt_meta_data_Streamer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Streamer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Streamer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Streamer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Streamer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Streamer::gst_start_timer(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Streamer::gst_stop_timer()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
