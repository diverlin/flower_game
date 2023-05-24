#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "../gridmap.h"

#include <QGraphicsScene>
#include <QSet>

class TextInformationItem;

class GraphicsScene : public QGraphicsScene
{
Q_OBJECT
public:
    GraphicsScene(int x, int y, int width, int height, QObject* parent = nullptr);

    void createScene();
    void clearScene();

private:
//    TextInformationItem* textInformationItem;

    GridMap m_gridMap;
//    void isTileFree(int i, int j) const;
//    void createScene();
    void addTile(const Tile& tile);
    void addItem(QGraphicsItem* item);
};

#endif // GRAPHICSSCENE_H
