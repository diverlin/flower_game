#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "../gridmap.h"

#include <QGraphicsScene>
#include <QTimer>
#include <QMap>

namespace view {

//class TextInformationItem;
class PixmapItem;

class GraphicsScene : public QGraphicsScene
{
Q_OBJECT
public:
    GraphicsScene(int x, int y, int width, int height, QObject* parent = nullptr);
private:
//    TextInformationItem* textInformationItem;

    core::GridMap m_gridMap;
    QTimer m_gameLoopTimer;
    QMap<size_t, PixmapItem*> m_tilesViews;
    
    void addObject(const core::StaticObject& object);
    void addTile(const core::Tile& tile);

    void create();
    void createTilesViews();
    void clear();

    void updateGameLoop();
};

} // namespace view

#endif // GRAPHICSSCENE_H
