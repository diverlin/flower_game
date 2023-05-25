#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "../gridmap.h"

#include <QGraphicsScene>
#include <QTimer>
#include <QMap>
#include <QElapsedTimer>

namespace view {

//class TextInformationItem;
class PixmapItem;

class GraphicsScene : public QGraphicsScene
{
Q_OBJECT
public:
    GraphicsScene(int x, int y, int width, int height, QObject* parent = nullptr);

    void onMousePositionChanged(const QPointF&);
    void onMousePress(const QPointF&);

private:
//    TextInformationItem* textInformationItem;
    bool m_isMousePressed = false;

    core::Index2D m_index2dUnderCursor;
    core::GridMap m_world;
    QTimer m_gameLoopTimer;
    QMap<size_t, PixmapItem*> m_tilesViews;

    QElapsedTimer m_elapsedTimer;
    
    void createTilesViews();
    void updateOverlay();
    void updateTilesViews(const std::vector<core::Tile>&);

    void updateGameLoop();
};

} // namespace view

#endif // GRAPHICSSCENE_H
