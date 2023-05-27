#include "mainwindow.h"
#include "graphicsscene.h"
#include "graphicsview.h"

#include <QApplication>

namespace view {

MainWindow::MainWindow(int width, int height)
    : QMainWindow()
{
    m_scene = new GraphicsScene(0, 0, width, height, this);

    m_view = new GraphicsView(m_scene, this);
    setCentralWidget(m_view);
}

void MainWindow::startNewGame()
{
    m_scene->restart();
}

} // namespace view
