#include "graphicsscene.h"
#include "pixmapitem.h"
#include "textinformationitem.h"

#include <QAction>
#include <QApplication>
#include <QFile>

#include <QRandomGenerator>

int getRandomInt(int max)
{
    return QRandomGenerator::global()->bounded(0, max + 1);
}

int getRandomInt(int min, int max)
{
    return QRandomGenerator::global()->bounded(min, max + 1);
}

bool getRandomBool()
{
    return QRandomGenerator::global()->bounded(0, 100) >= 50;
}

GraphicsScene::GraphicsScene(int x, int y, int width, int height, QObject* parent)
    : QGraphicsScene(x, y, width, height, parent)
{
    const int rows = 24;
    const int cols = 16;

    const int size = 48;
    for (int i=0; i<rows; ++i) {
        for (int j=0; j<cols; ++j) {
            PixmapItem* ground_tile = new PixmapItem(":/tiles/ground.png");
            ground_tile->setZValue(GROUND_LAYER);
            ground_tile->setPos(i*size, j*size);
            ground_tile->fit(size);
            addItem(ground_tile);

            const bool is_covered_with_grass = (getRandomInt(10) == 0);
            if (is_covered_with_grass) {
                const int grass_variant = getRandomInt(1,2);
                PixmapItem* grass_tile = new PixmapItem(QString(":/tiles/grass%1.png").arg(grass_variant));
                grass_tile->setZValue(ROCK_LAYER);
                grass_tile->setPos(i*size, j*size);
                grass_tile->fit(size);
                addItem(grass_tile);
            } else {
                const bool is_covered_with_rock = (getRandomInt(30) == 0);
                if (is_covered_with_rock) {
                    const int rock_variant = getRandomInt(0,1);

                    PixmapItem* rock_tile = new PixmapItem(QString(":/tiles/rock_%1.png").arg(rock_variant?"big":"middle"));
                    rock_tile->setZValue(ROCK_LAYER);
                    rock_tile->setPos(i*size, j*size);
                    rock_tile->fit(size);
                    addItem(rock_tile);
                }
            }

        }
    }

    textInformationItem = new TextInformationItem();

//    textInformationItem->setMessage(QString("Hello world!"), false);
//    textInformationItem->setPos(backgroundItem->boundingRect().center().x(),
//                                backgroundItem->boundingRect().height()* 3 / 4);
}

void GraphicsScene::addItem(QGraphicsItem* item)
{
    QGraphicsScene::addItem(item);
}

void GraphicsScene::clearScene()
{
    QGraphicsScene::clear();
}
