QT += statemachine widgets
HEADERS += \
    $$PWD/src/mainwindow.h \
    $$PWD/src/pixmapitem.h \
    $$PWD/src/graphicsscene.h \
    $$PWD/src/textinformationitem.h \
    
SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/mainwindow.cpp \
    $$PWD/src/pixmapitem.cpp \
    $$PWD/src/graphicsscene.cpp \
    $$PWD/src/textinformationitem.cpp \
    
RESOURCES += $$PWD/data/flower_game.qrc

# install
INSTALLS += target
