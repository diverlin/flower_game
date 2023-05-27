QT += testlib

include($$PWD/../app/app.pri)

INCLUDEPATH += $$PWD/../app

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/gridtest.cpp \
    $$PWD/fixedqueuetest.cpp \

HEADERS += \
    $$PWD/gridtest.h \
    $$PWD/fixedqueuetest.h \

TARGET = flower_game_tests




