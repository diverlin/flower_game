#include "graphicsscene.h"
#include "pixmapitem.h"
#include "pixmapprovider.h"
//#include "textinformationitem.h"

#include <QApplication>

namespace view {

GraphicsScene::GraphicsScene(int x, int y, int width, int height, QObject* parent)
    : QGraphicsScene(x, y, width, height, parent)
    , m_world(16, 12, core::Size(800, 600))
{
    createTilesViews();

    //    textInformationItem = new TextInformationItem();

//    textInformationItem->setMessage(QString("Hello world!"), false);
//    textInformationItem->setPos(backgroundItem->boundingRect().center().x(),
//                                backgroundItem->boundingRect().height()* 3 / 4);

    QObject::connect(&m_gameLoopTimer, &QTimer::timeout, this, &GraphicsScene::updateGameLoop);
    m_gameLoopTimer.setInterval(20);
    m_gameLoopTimer.start();

    m_elapsedTimer.start();
}

void GraphicsScene::onMousePositionChanged(const QPointF& scenePos)
{
    m_index2dUnderCursor = m_world.index2dFromWorldCoord(core::vec2(scenePos.x(), scenePos.y()));
}

void GraphicsScene::onMousePress(const QPointF& scenePos)
{
    m_index2dUnderCursor = m_world.index2dFromWorldCoord(core::vec2(scenePos.x(), scenePos.y()));
    m_isMousePressed = true;
}

void GraphicsScene::updateGameLoop()
{
    qint64 deltaTimeMs = m_elapsedTimer.elapsed();

    m_world.update(deltaTimeMs);
    updateTilesViews(m_world.tiles());
    updateOverlay();

    m_elapsedTimer.restart();
}

void GraphicsScene::updateOverlay()
{
    const core::Grid& world = m_world.grid();
    for (std::size_t i=0; i<world.size(); ++i) {
        core::Index2D index2d = world.getIndex2D(i);
        PixmapItem* tileView = m_tilesViews[i];
        if (m_index2dUnderCursor.isValid() && (index2d == m_index2dUnderCursor)) {
            if (m_world.grid().isIndexPassable(index2d)) {
                if (m_isMousePressed) {
                    // put flower
                }
                tileView->setPixmap(PixmapProvider::instance().getPixmap(":/tiles/frame_blue_blurred.png", m_world.tileSize()), core::PixmapLayer::OVERLAY_LAYER);
            } else {
                tileView->setPixmap(PixmapProvider::instance().getPixmap(":/tiles/frame_red_blurred.png", m_world.tileSize()), core::PixmapLayer::OVERLAY_LAYER);
            }
        } else {
            tileView->removePixmap(core::PixmapLayer::OVERLAY_LAYER);
            //if (m_gridMap.grid().isIndexPassable(index2d)) {
            //tileView->setPixmap(PixmapProvider::instance().getPixmap(":/tiles/frame_black_blurred.png", m_gridMap.tileSize()), core::PixmapLayer::OVERLAY_LAYER);
            //} else {
            //tileView->setPixmap(PixmapProvider::instance().getPixmap(":/tiles/frame_red_blurred.png", m_gridMap.tileSize()), core::PixmapLayer::OVERLAY_LAYER);
            //}
        }
    }

    m_isMousePressed = false;
}

void GraphicsScene::createTilesViews()
{
    const core::Grid& grid = m_world.grid();
    for (std::size_t i=0; i<grid.size(); ++i) {
        PixmapItem* tileView = new PixmapItem;
        core::vec2 pos = m_world.worldCoordFromIndex(i);
        tileView->setPos(pos.x(), pos.y());
        m_tilesViews[i] = tileView;
        addItem(tileView);
    }
}

void GraphicsScene::updateTilesViews(const std::vector<core::Tile>& tiles)
{
    for (const core::Tile& tile: tiles) {
        if (tile.isDirty()) {
//            qInfo() << "redraw tile" << tile.id();
            PixmapItem* view = m_tilesViews[tile.id()];
            const std::map<int, std::string>& data = tile.data();
            std::map<int, std::string>::const_iterator it = data.begin();
            for (; it != data.end(); ++it) {
                core::PixmapLayer layer = static_cast<core::PixmapLayer>(it->first);
                std::string imageFilePath = it->second;
                view->setPixmap(PixmapProvider::instance().getPixmap(imageFilePath.c_str(), m_world.tileSize()), layer);
            }
            tile.resetIsDirtyFlag();
        }
    }
}

} // namespace view
