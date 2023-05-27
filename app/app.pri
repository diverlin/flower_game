QT += widgets

HEADERS += \
    $$PWD/qtdependant/mainwindow.h \
    $$PWD/qtdependant/pixmapitem.h \
    $$PWD/qtdependant/pixmapprovider.h \
    $$PWD/qtdependant/graphicsscene.h \
    $$PWD/qtdependant/graphicsview.h \
    $$PWD/qtdependant/textinformationitem.h \
    $$PWD/qtdependant/textinformationpopupitem.h \
    $$PWD/pixmaplayer.h \
    $$PWD/grid.h \
    $$PWD/gameoverobserverobserver.h \
    $$PWD/index2d.h \
    $$PWD/vec2.h \
    $$PWD/size.h \
    $$PWD/gridmap.h \
    $$PWD/randutils.h \
    $$PWD/stringutils.h \
    $$PWD/tile.h \
    $$PWD/image.h \
    $$PWD/ibaseobject.h \
    $$PWD/staticobject.h \
    $$PWD/flower.h \
    $$PWD/fixedqueue.h \
    $$PWD/snake.h \
    $$PWD/snakespropertymodifier.h \
    $$PWD/snakespawner.h \

SOURCES += \
    $$PWD/qtdependant/mainwindow.cpp \
    $$PWD/qtdependant/pixmapitem.cpp \
    $$PWD/qtdependant/pixmapprovider.cpp \
    $$PWD/qtdependant/graphicsscene.cpp \
    $$PWD/qtdependant/graphicsview.cpp \
    $$PWD/qtdependant/textinformationitem.cpp \
    $$PWD/qtdependant/textinformationpopupitem.cpp \
    $$PWD/gameoverobserver.cpp \
    $$PWD/grid.cpp \
    $$PWD/gridmap.cpp \
    $$PWD/randutils.cpp \
    $$PWD/stringutils.cpp \
    $$PWD/tile.cpp \
    $$PWD/image.cpp \
    $$PWD/ibaseobject.cpp \
    $$PWD/staticobject.cpp \
    $$PWD/flower.cpp \
    $$PWD/snake.cpp \
    $$PWD/snakespropertymodifier.cpp \
    $$PWD/snakespawner.cpp \

RESOURCES += $$PWD/data/flower_game.qrc

TARGET = flower_game
