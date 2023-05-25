#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class QMouseEvent;

namespace view {

class GraphicsScene;

class GraphicsView final : public QGraphicsView
{
Q_OBJECT
public:
    GraphicsView(GraphicsScene* scene, QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override final;
    void mouseMoveEvent(QMouseEvent* event) override final;

private:
    GraphicsScene* m_scene = nullptr;
};

} // namespace view

#endif // GRAPHICSVIEW_H
