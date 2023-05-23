#include "graphicsscene.h"
#include "pixmapitem.h"
#include "textinformationitem.h"
#include "../randutils.h"

#include <QAction>
#include <QApplication>

GraphicsScene::GraphicsScene(int x, int y, int width, int height, QObject* parent)
    : QGraphicsScene(x, y, width, height, parent)
    , m_grid(24, 16)
{
    createScene();

    textInformationItem = new TextInformationItem();

//    textInformationItem->setMessage(QString("Hello world!"), false);
//    textInformationItem->setPos(backgroundItem->boundingRect().center().x(),
//                                backgroundItem->boundingRect().height()* 3 / 4);
}

void GraphicsScene::createScene()
{
    const int size = 48;
    for (int i=0; i<m_grid.rows(); ++i) {
        for (int j=0; j<m_grid.columns(); ++j) {
            PixmapItem* ground_tile = new PixmapItem(":/tiles/ground.png");
            ground_tile->setZValue(GROUND_LAYER);
            ground_tile->setPos(i*size, j*size);
            ground_tile->fit(size);
            addItem(ground_tile);

            const bool is_covered_with_grass = (getRandomInt(10) == 0);
            if (is_covered_with_grass) {
                const int grass_variant = getRandomInt(1,2);

                QString pixmapLocation = QString(":/tiles/grass%1.png").arg(grass_variant);
                PixmapItem* grass_tile = new PixmapItem(pixmapLocation);
                grass_tile->setZValue(ROCK_LAYER);
                grass_tile->setPos(i*size, j*size);
                grass_tile->fit(size);
                addItem(grass_tile);
            } else {
                const bool is_covered_with_rock = (getRandomInt(30) == 0);
                if (is_covered_with_rock) {
                    const int rock_variant = getRandomInt(0,1);

                    QString pixmapLocation = QString(":/tiles/rock_%1.png").arg(rock_variant?"big":"middle");
                    PixmapItem* rock_tile = new PixmapItem(pixmapLocation);
                    rock_tile->setZValue(ROCK_LAYER);
                    rock_tile->setPos(i*size, j*size);
                    rock_tile->fit(size);
                    addItem(rock_tile);
                }
            }
        }
    }
}

void GraphicsScene::addItem(QGraphicsItem* item)
{
    QGraphicsScene::addItem(item);
}

void GraphicsScene::clearScene()
{
    QGraphicsScene::clear();
}
