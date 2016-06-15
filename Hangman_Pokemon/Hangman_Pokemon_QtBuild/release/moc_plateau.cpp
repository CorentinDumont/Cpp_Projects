/****************************************************************************
** Meta object code from reading C++ file 'plateau.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Hangman_Pokemon/plateau.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plateau.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Plateau_t {
    QByteArrayData data[8];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Plateau_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Plateau_t qt_meta_stringdata_Plateau = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Plateau"
QT_MOC_LITERAL(1, 8, 10), // "traitement"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 7), // "newGame"
QT_MOC_LITERAL(4, 28, 10), // "setplayer1"
QT_MOC_LITERAL(5, 39, 10), // "setplayer2"
QT_MOC_LITERAL(6, 50, 9), // "finpartie"
QT_MOC_LITERAL(7, 60, 11) // "recommencer"

    },
    "Plateau\0traitement\0\0newGame\0setplayer1\0"
    "setplayer2\0finpartie\0recommencer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Plateau[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       3,    0,   47,    2, 0x0a /* Public */,
       4,    0,   48,    2, 0x0a /* Public */,
       5,    0,   49,    2, 0x0a /* Public */,
       6,    0,   50,    2, 0x0a /* Public */,
       7,    0,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Plateau::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Plateau *_t = static_cast<Plateau *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->traitement((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->newGame(); break;
        case 2: _t->setplayer1(); break;
        case 3: _t->setplayer2(); break;
        case 4: _t->finpartie(); break;
        case 5: _t->recommencer(); break;
        default: ;
        }
    }
}

const QMetaObject Plateau::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Plateau.data,
      qt_meta_data_Plateau,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Plateau::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Plateau::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Plateau.stringdata0))
        return static_cast<void*>(const_cast< Plateau*>(this));
    return QWidget::qt_metacast(_clname);
}

int Plateau::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
