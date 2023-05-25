#include "graphicsscene.h"
#include "pixmapitem.h"
#include "pixmapprovider.h"
//#include "textinformationitem.h"

#include "../PixmapLayer.h"
#include "../gameobject.h"

#include <QApplication>

namespace view {

GraphicsScene::GraphicsScene(int x, int y, int width, int height, QObject* parent)
    : QGraphicsScene(x, y, width, height, parent)
    , m_gridMap(16, 12, core::Size(800, 600))
{
    createTilesViews();

    create();
//    textInformationItem = new TextInformationItem();

//    textInformationItem->setMessage(QString("Hello world!"), false);
//    textInformationItem->setPos(backgroundItem->boundingRect().center().x(),
//                                backgroundItem->boundingRect().height()* 3 / 4);

    m_gameLoopTimer.setInterval(20);
    m_gameLoopTimer.start();

    QObject::connect(&m_gameLoopTimer, &QTimer::timeout, this, &GraphicsScene::updateGameLoop);
}

void GraphicsScene::addObject(const core::StaticObject& object)
{
    for (const core::Tile& tile: object.tiles()) {
        addTile(tile);
    }
}

void GraphicsScene::addTile(const core::Tile& tile)
{
    core::Index2D index2d = tile.mapLocation();
    size_t index1d = m_gridMap.grid().getIndex1D(index2d);
    PixmapItem* tile_view = m_tilesViews[index1d];
    tile_view->setPixmap(PixmapProvider::instance().getPixmap(tile.imageFilePath().c_str(), m_gridMap.tileSize()), tile.layer());
}

void GraphicsScene::updateGameLoop()
{
    //qInfo() << "---tick";
    const core::Grid& grid = m_gridMap.grid();
    for (std::size_t i=0; i<grid.size(); ++i) {
        core::Index2D index2d = grid.getIndex2D(i);
        PixmapItem* tileView = m_tilesViews[i];
        if (m_gridMap.grid().isIndexPassable(index2d)) {
            tileView->setPixmap(PixmapProvider::instance().getPixmap(":/tiles/frame.png", m_gridMap.tileSize()), core::PixmapLayer::OVERLAY_LAYER);
        } else {
            tileView->setPixmap(PixmapProvider::instance().getPixmap(":/tiles/frame_red.png", m_gridMap.tileSize()), core::PixmapLayer::OVERLAY_LAYER);
        }
        //qInfo() << i << index2d.i() << index2d.j() << grid.value(i);
    }
}

void GraphicsScene::create()
{
    m_gridMap.create();
    for (const core::Tile& tile: m_gridMap.tiles()) {
        addTile(tile);
    }
    for (const core::StaticObject& object: m_gridMap.staticObjects()) {
        addObject(object);
    }
}

void GraphicsScene::createTilesViews()
{
    const core::Grid& grid = m_gridMap.grid();
    for (std::size_t i=0; i<grid.size(); ++i) {
        PixmapItem* tileView = new PixmapItem;
        core::vec2 pos = m_gridMap.worldCoordFromIndex(i);
        tileView->setPos(pos.x(), pos.y());
        m_tilesViews[i] = tileView;
        addItem(tileView);
    }
}

void GraphicsScene::clear()
{
    QGraphicsScene::clear();
}

} // namespace view
