#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GraphicsScene;

QT_BEGIN_NAMESPACE
class QGraphicsView;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

private:
    GraphicsScene* m_scene = nullptr;
    QGraphicsView* m_view = nullptr;
};

#endif // MAINWINDOW_H
