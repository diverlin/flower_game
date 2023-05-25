#include "mainwindow.h"
#include "graphicsscene.h"

#include <QApplication>
#include <QGraphicsView>

namespace view {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    m_scene = new GraphicsScene(0, 0, 800, 600, this);

    m_view = new QGraphicsView(m_scene, this);
    setCentralWidget(m_view);
}

} // namespace view
