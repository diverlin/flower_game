#include "graphicsscene.h"
#include "pixmapitem.h"
//#include "textinformationitem.h"

#include "../tilelayer.h"
#include "../gameobject.h"

#include <QApplication>

GraphicsScene::GraphicsScene(int x, int y, int width, int height, QObject* parent)
    : QGraphicsScene(x, y, width, height, parent)
    , m_gridMap(16, 12)
{
    m_gridMap.create();
    for (const Tile& tile: m_gridMap.tiles()) {
        addTile(tile);
    }
    for (const StaticObject& object: m_gridMap.staticObjects()) {
        addObject(object);
    }
//    textInformationItem = new TextInformationItem();

//    textInformationItem->setMessage(QString("Hello world!"), false);
//    textInformationItem->setPos(backgroundItem->boundingRect().center().x(),
//                                backgroundItem->boundingRect().height()* 3 / 4);
}

void GraphicsScene::addObject(const StaticObject& object)
{
    for (const Tile& tile: object.tiles()) {
        addTile(tile);
    }
}

void GraphicsScene::addTile(const Tile& tile)
{
    static int size = 48;

    PixmapItem* tile_view = new PixmapItem(tile.imageFilePath().c_str());
    tile_view->setZValue(static_cast<int>(tile.layer()));
    tile_view->setPos(tile.mapLocation().i()*size, tile.mapLocation().j()*size);
    tile_view->fit(size);
    addItem(tile_view);

    // overlay
    PixmapItem* overlay = new PixmapItem(":/tiles/frame.png");
    overlay->setZValue(static_cast<int>(TileLayer::OVERLAY_LAYER));
    overlay->setPos(tile.mapLocation().i()*size, tile.mapLocation().j()*size);
    overlay->fit(size);
    addItem(overlay);
}

void GraphicsScene::createScene()
{
//    for (int i=0; i<m_grid.rows(); ++i) {
//        for (int j=0; j<m_grid.columns(); ++j) {
//            GameObject ground(":/tiles/ground.png", ObjectLayer::GROUND_LAYER);

//            PixmapItem* ground_tile = new PixmapItem();


//            const bool is_covered_with_grass = (getRandomInt(10) == 0);
//            if (is_covered_with_grass) {
//                const int grass_variant = getRandomInt(1,2);

//                QString pixmapLocation = QString(":/tiles/grass%1.png").arg(grass_variant);
//                PixmapItem* grass_tile = new PixmapItem(pixmapLocation);
//                grass_tile->setZValue(GRASS_LAYER);
//                grass_tile->setPos(i*size, j*size);
//                grass_tile->fit(size);
//                addItem(grass_tile);
//            } else {
//                const bool is_covered_with_rock = (getRandomInt(30) == 0);
//                if (is_covered_with_rock) {
//                    const int rock_variant = getRandomInt(0,1);

//                    QString pixmapLocation = QString(":/tiles/rock_%1.png").arg(rock_variant?"big":"middle");
//                    PixmapItem* rock_tile = new PixmapItem(pixmapLocation);
//                    rock_tile->setZValue(ROCK_LAYER);
//                    rock_tile->setPos(i*size, j*size);
//                    rock_tile->fit(size);
//                    addItem(rock_tile);
//                }
//            }
//        }
//    }
}

void GraphicsScene::addItem(QGraphicsItem* item)
{
    QGraphicsScene::addItem(item);
}

void GraphicsScene::clearScene()
{
    QGraphicsScene::clear();
}
