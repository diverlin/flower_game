#include <QtWidgets>

#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(flower_game);

    MainWindow w;
    w.show();

    return app.exec();
}
