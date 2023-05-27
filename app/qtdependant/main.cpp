#include <QtWidgets>

#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(flower_game);

    QScreen* screen = QGuiApplication::primaryScreen();

    QRect geometry = screen->geometry();

#ifdef Q_OS_ANDROID
    int width = 0.94*geometry.width();
    int height = 0.84*geometry.height();
#else
    int width = 0.8*geometry.width();
    int height = 0.8*geometry.height();
#endif

    view::MainWindow window(width, height);
    window.setFixedSize(1.01f*width, 1.01f*height);

    window.show();

    return app.exec();
}
