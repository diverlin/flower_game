#include "graphicsscene.h"
#include "pixmapitem.h"
#include "pixmapprovider.h"
//#include "textinformationitem.h"

#include "../tilelayer.h"
#include "../gameobject.h"

#include <QApplication>

GraphicsScene::GraphicsScene(int x, int y, int width, int height, QObject* parent)
    : QGraphicsScene(x, y, width, height, parent)
    , m_gridMap(16, 12, Size(800, 600))
{
    create();
//    textInformationItem = new TextInformationItem();

//    textInformationItem->setMessage(QString("Hello world!"), false);
//    textInformationItem->setPos(backgroundItem->boundingRect().center().x(),
//                                backgroundItem->boundingRect().height()* 3 / 4);

    m_gameLoopTimer.setInterval(20);
    m_gameLoopTimer.start();

    QObject::connect(&m_gameLoopTimer, &QTimer::timeout, this, &GraphicsScene::updateGameLoop);
}

void GraphicsScene::addObject(const StaticObject& object)
{
    for (const Tile& tile: object.tiles()) {
        addTile(tile);
    }
}

void GraphicsScene::addTile(const Tile& tile)
{
    PixmapItem* tile_view = new PixmapItem(PixmapProvider::instance().getPixmap(tile.imageFilePath().c_str(), m_gridMap.tileSize()));
    tile_view->setZValue(static_cast<int>(tile.layer()));
    vec2 pos = m_gridMap.worldCoordFromIndex(tile.mapLocation());
    tile_view->setPos(pos.x(), pos.y());
    addItem(tile_view);
}

void GraphicsScene::updateGameLoop()
{
    qInfo() << "---tick";
    const Grid& grid = m_gridMap.grid();
    for (std::size_t i=0; i<grid.size(); ++i) {
        Index2D index2d = grid.getIndex2D(i);
        PixmapItem* item = m_overlay[i];
        if (m_gridMap.grid().isIndexPassable(index2d)) {
            item->setPixmap(PixmapProvider::instance().getPixmap(":/tiles/frame.png", m_gridMap.tileSize()));
        } else {
            item->setPixmap(PixmapProvider::instance().getPixmap(":/tiles/frame_red.png", m_gridMap.tileSize()));
        }
        //qInfo() << i << index2d.i() << index2d.j() << grid.value(i);
    }
}

void GraphicsScene::create()
{
    m_gridMap.create();
    for (const Tile& tile: m_gridMap.tiles()) {
        addTile(tile);
    }
    for (const StaticObject& object: m_gridMap.staticObjects()) {
        addObject(object);
    }

    createTilesOverlays();
}

void GraphicsScene::createTilesOverlays()
{
    const Grid& grid = m_gridMap.grid();
    for (std::size_t i=0; i<grid.size(); ++i) {
        PixmapItem* tileOverlay = new PixmapItem(PixmapProvider::instance().getPixmap(":/tiles/frame.png", m_gridMap.tileSize()));
        tileOverlay->setZValue(static_cast<int>(TileLayer::OVERLAY_LAYER));
        vec2 pos = m_gridMap.worldCoordFromIndex(i);
        tileOverlay->setPos(pos.x(), pos.y());
        //tileOverlay->setOpacity(0.5f);
        m_overlay[i] = tileOverlay;
        addItem(tileOverlay);
    }
}

void GraphicsScene::addItem(QGraphicsItem* item)
{
    QGraphicsScene::addItem(item);
}

void GraphicsScene::removeItem(QGraphicsItem* item)
{
    QGraphicsScene::removeItem(item);
}

void GraphicsScene::clear()
{
    QGraphicsScene::clear();
}
