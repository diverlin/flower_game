#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QSet>

class TextInformationItem;

enum {
    GROUND_LAYER,
    GRASS_LAYER,
    ROCK_LAYER,
    WOOD_LAYER,
    FLOWER_LAYER,
    SNAKE_LAYER,
    TREE_LAYER
};

class GraphicsScene : public QGraphicsScene
{
Q_OBJECT
public:
    GraphicsScene(int x, int y, int width, int height, QObject* parent = nullptr);

    void addItem(QGraphicsItem* item);
    void clearScene();

private:
    TextInformationItem* textInformationItem;
};

#endif // GRAPHICSSCENE_H

