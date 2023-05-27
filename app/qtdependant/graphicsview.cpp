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
#ifdef Q_OS_ANDROID
    m_scene->onMouseRightButtonPress(scenePos); // right mouse button more functional than left mouse button according to requirements, and it's ok to use it as main tap handle event
#else
    if (event->button() == Qt::LeftButton) {
        m_scene->onMouseLeftButtonPress(scenePos);
    } else if (event->button() == Qt::RightButton) {
        m_scene->onMouseRightButtonPress(scenePos);
    }
#endif
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    QPointF scenePos = mapToScene(event->pos());
    m_scene->onMousePositionChanged(scenePos);
    QGraphicsView::mouseMoveEvent(event);
}

} // namespace view
