#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QGraphicsView;
QT_END_NAMESPACE

namespace view {

class GraphicsScene;
class GraphicsView;

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    MainWindow(int width, int height);

    void startNewGame();

private:
    GraphicsScene* m_scene = nullptr;
    GraphicsView* m_view = nullptr;
};

} // namespace view

#endif // MAINWINDOW_H
