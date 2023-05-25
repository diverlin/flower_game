QT += widgets

HEADERS += \
    $$PWD/qtdependant/mainwindow.h \
    $$PWD/qtdependant/pixmapitem.h \
    $$PWD/qtdependant/pixmapprovider.h \
    $$PWD/qtdependant/graphicsscene.h \
    $$PWD/qtdependant/graphicsview.h \
    $$PWD/qtdependant/textinformationitem.h \
    $$PWD/pixmaplayer.h \
    $$PWD/grid.h \
    $$PWD/index2d.h \
    $$PWD/vec2.h \
    $$PWD/size.h \
    $$PWD/gridmap.h \
    $$PWD/randutils.h \
    $$PWD/stringutils.h \
    $$PWD/tile.h \
    $$PWD/gameobject.h \
    $$PWD/fixedqueue.h \
    $$PWD/snake.h \

SOURCES += \
    $$PWD/qtdependant/mainwindow.cpp \
    $$PWD/qtdependant/pixmapitem.cpp \
    $$PWD/qtdependant/pixmapprovider.cpp \
    $$PWD/qtdependant/graphicsscene.cpp \
    $$PWD/qtdependant/graphicsview.cpp \
    $$PWD/qtdependant/textinformationitem.cpp \
    $$PWD/grid.cpp \
    $$PWD/gridmap.cpp \
    $$PWD/randutils.cpp \
    $$PWD/stringutils.cpp \
    $$PWD/tile.cpp \
    $$PWD/gameobject.cpp \
    $$PWD/snake.cpp \

RESOURCES += $$PWD/data/flower_game.qrc
