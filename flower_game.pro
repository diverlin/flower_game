QT += statemachine widgets
HEADERS += \
    $$PWD/src/qtdependant/mainwindow.h \
    $$PWD/src/qtdependant/pixmapitem.h \
    $$PWD/src/qtdependant/graphicsscene.h \
    $$PWD/src/qtdependant/textinformationitem.h \
    $$PWD/src/objectlayer.h \
    $$PWD/src/index2d.h \
    $$PWD/src/grid.h \
    $$PWD/src/randutils.h \
    $$PWD/src/tiledescriptor.h \
    $$PWD/src/gameobject.h \

SOURCES += \
    $$PWD/src/qtdependant/main.cpp \
    $$PWD/src/qtdependant/mainwindow.cpp \
    $$PWD/src/qtdependant/pixmapitem.cpp \
    $$PWD/src/qtdependant/graphicsscene.cpp \
    $$PWD/src/qtdependant/textinformationitem.cpp \
    $$PWD/src/index2d.cpp \
    $$PWD/src/grid.cpp \
    $$PWD/src/randutils.cpp \
    $$PWD/src/tiledescriptor.cpp \
    $$PWD/src/gameobject.cpp \

RESOURCES += $$PWD/data/flower_game.qrc

# install
INSTALLS += target
