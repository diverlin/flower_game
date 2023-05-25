#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "../gridmap.h"

#include <QGraphicsScene>
#include <QTimer>
#include <QSet>

class TextInformationItem;

class GraphicsScene : public QGraphicsScene
{
Q_OBJECT
public:
    GraphicsScene(int x, int y, int width, int height, QObject* parent = nullptr);
private:
//    TextInformationItem* textInformationItem;

    GridMap m_gridMap;
    QTimer m_gameLoopTimer;
    
    void addObject(const StaticObject& object);
    void addTile(const Tile& tile);
    void addItem(QGraphicsItem* item);
    void removeItem(QGraphicsItem* item);

    void create();
    void clear();

    void updateGameLoop();
};

#endif // GRAPHICSSCENE_H
