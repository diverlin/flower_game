#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "../grid.h"

#include <QGraphicsScene>
#include <QSet>

class TextInformationItem;

class GraphicsScene : public QGraphicsScene
{
Q_OBJECT
public:
    GraphicsScene(int x, int y, int width, int height, QObject* parent = nullptr);

    void addItem(QGraphicsItem* item);
    void clearScene();

private:
//    TextInformationItem* textInformationItem;

    Grid m_grid;
//    void isTileFree(int i, int j) const;
    void createScene();
};

#endif // GRAPHICSSCENE_H
