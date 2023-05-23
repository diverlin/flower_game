QT += statemachine widgets
HEADERS += \
    $$PWD/src/qtdependant/mainwindow.h \
    $$PWD/src/qtdependant/pixmapitem.h \
    $$PWD/src/qtdependant/graphicsscene.h \
    $$PWD/src/qtdependant/textinformationitem.h \
    $$PWD/src/grid.h \
    $$PWD/src/randutils.h \

SOURCES += \
    $$PWD/src/qtdependant/main.cpp \
    $$PWD/src/qtdependant/mainwindow.cpp \
    $$PWD/src/qtdependant/pixmapitem.cpp \
    $$PWD/src/qtdependant/graphicsscene.cpp \
    $$PWD/src/qtdependant/textinformationitem.cpp \
    $$PWD/src/grid.cpp \
    $$PWD/src/randutils.cpp \

RESOURCES += $$PWD/data/flower_game.qrc

# install
INSTALLS += target
