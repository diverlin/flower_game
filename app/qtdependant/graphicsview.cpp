#include "graphicsview.h"
#include "graphicsscene.h"

#include <QMouseEvent>

namespace view {

GraphicsView::GraphicsView(GraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
    , m_scene(scene)
{
    setMouseTracking(true); // Enable mouse tracking for the widget
}

void GraphicsView::mousePressEvent(QMouseEvent* event)
{
    QPointF scenePos = mapToScene(event->pos());
    if (event->button() == Qt::LeftButton) {
        m_scene->onMouseLeftButtonPress(scenePos);
    } else if (event->button() == Qt::RightButton) {
        m_scene->onMouseRightButtonPress(scenePos);
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    QPointF scenePos = mapToScene(event->pos());
    m_scene->onMousePositionChanged(scenePos);
    QGraphicsView::mouseMoveEvent(event);
}

} // namespace view
