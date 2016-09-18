/****************************************************************************
** Meta object code from reading C++ file 'Game.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SequenceGame/Game.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Game.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Game_t {
    QByteArrayData data[21];
    char stringdata0[221];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Game_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Game_t qt_meta_stringdata_Game = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Game"
QT_MOC_LITERAL(1, 5, 8), // "mainMenu"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 9), // "startGame"
QT_MOC_LITERAL(4, 25, 12), // "selectPlayer"
QT_MOC_LITERAL(5, 38, 12), // "createPlayer"
QT_MOC_LITERAL(6, 51, 13), // "numberPlayers"
QT_MOC_LITERAL(7, 65, 9), // "getPlayer"
QT_MOC_LITERAL(8, 75, 8), // "playerId"
QT_MOC_LITERAL(9, 84, 5), // "error"
QT_MOC_LITERAL(10, 90, 9), // "addPlayer"
QT_MOC_LITERAL(11, 100, 10), // "changeName"
QT_MOC_LITERAL(12, 111, 4), // "name"
QT_MOC_LITERAL(13, 116, 11), // "startRounds"
QT_MOC_LITERAL(14, 128, 11), // "changeToken"
QT_MOC_LITERAL(15, 140, 14), // "randomizeBoard"
QT_MOC_LITERAL(16, 155, 12), // "undoFunction"
QT_MOC_LITERAL(17, 168, 12), // "redoFunction"
QT_MOC_LITERAL(18, 181, 17), // "resetContinueGame"
QT_MOC_LITERAL(19, 199, 9), // "resetGame"
QT_MOC_LITERAL(20, 209, 11) // "newGameSlot"

    },
    "Game\0mainMenu\0\0startGame\0selectPlayer\0"
    "createPlayer\0numberPlayers\0getPlayer\0"
    "playerId\0error\0addPlayer\0changeName\0"
    "name\0startRounds\0changeToken\0"
    "randomizeBoard\0undoFunction\0redoFunction\0"
    "resetContinueGame\0resetGame\0newGameSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Game[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       3,    0,   95,    2, 0x0a /* Public */,
       4,    0,   96,    2, 0x0a /* Public */,
       5,    1,   97,    2, 0x0a /* Public */,
       7,    2,  100,    2, 0x0a /* Public */,
       7,    1,  105,    2, 0x2a /* Public | MethodCloned */,
      10,    1,  108,    2, 0x0a /* Public */,
      11,    1,  111,    2, 0x0a /* Public */,
      13,    0,  114,    2, 0x0a /* Public */,
      14,    0,  115,    2, 0x0a /* Public */,
      15,    0,  116,    2, 0x0a /* Public */,
      16,    0,  117,    2, 0x0a /* Public */,
      17,    0,  118,    2, 0x0a /* Public */,
      18,    0,  119,    2, 0x0a /* Public */,
      19,    0,  120,    2, 0x0a /* Public */,
      20,    0,  121,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    8,    9,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Game *_t = static_cast<Game *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mainMenu(); break;
        case 1: _t->startGame(); break;
        case 2: _t->selectPlayer(); break;
        case 3: _t->createPlayer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->getPlayer((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->getPlayer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->addPlayer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->changeName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->startRounds(); break;
        case 9: _t->changeToken(); break;
        case 10: _t->randomizeBoard(); break;
        case 11: _t->undoFunction(); break;
        case 12: _t->redoFunction(); break;
        case 13: _t->resetContinueGame(); break;
        case 14: _t->resetGame(); break;
        case 15: _t->newGameSlot(); break;
        default: ;
        }
    }
}

const QMetaObject Game::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_Game.data,
      qt_meta_data_Game,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Game::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Game::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Game.stringdata0))
        return static_cast<void*>(const_cast< Game*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int Game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
