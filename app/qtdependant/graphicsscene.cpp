#include "graphicsscene.h"
#include "pixmapitem.h"
#include "pixmapprovider.h"
#include "textinformationitem.h"
#include "textinformationpopupitem.h"

#include <QApplication>

namespace view {

GraphicsScene::GraphicsScene(int x, int y, int width, int height, QObject* parent)
    : QGraphicsScene(x, y, width, height, parent)
    , m_world(16, 12, core::Size(800, 600))
{
    createTilesViews();

    m_textInformationItem = new TextInformationItem();
    addItem(m_textInformationItem);

    const int icoSize = 20;
    const float hudOpacity = 0.8;

    // coin ico
    m_coinIcoItem = new PixmapItem;
    m_coinIcoItem->setPixmap(PixmapProvider::instance().getPixmap(":/tiles/coin.png", core::Size(icoSize, icoSize)), core::PixmapLayer::HUD_LAYER);
    m_coinIcoItem->setPos(5, 5);
    m_coinIcoItem->setOpacity(hudOpacity);
    addItem(m_coinIcoItem);

    // coin label
    m_textInformationItem->setPos(1.2*icoSize, 0);
    m_textInformationItem->setOpacity(hudOpacity);

    QObject::connect(&m_gameLoopTimer, &QTimer::timeout, this, &GraphicsScene::updateGameLoop);
    m_gameLoopTimer.setInterval(20);
    m_gameLoopTimer.start();

    m_frameElapsedTimer.start();
}

void GraphicsScene::onMousePositionChanged(const QPointF& scenePos)
{
    m_tileIndexUnderCursor = m_world.indexFromWorldCoord(core::vec2(scenePos.x(), scenePos.y()));
}

void GraphicsScene::onMousePress(const QPointF& /*scenePos*/)
{
    if (m_tileIndexUnderCursor != -1) {
        if (m_world.grid().isIndexPassable(m_tileIndexUnderCursor)) {
            m_world.createFlower(m_tileIndexUnderCursor);
        } else {
            m_world.tapOnBusyTile(m_tileIndexUnderCursor);
        }
    }
}

void GraphicsScene::updateGameLoop()
{
    qint64 frameDeltaTimeMs = m_frameElapsedTimer.elapsed();

    m_textInformationItem->setMessage(QString("x%1").arg(m_world.coins()));

    m_world.update(frameDeltaTimeMs);
    updateTilesViews(m_world.tiles());
    updateOverlay();

    handleRewards();
    updatePopUps(frameDeltaTimeMs);

    m_frameElapsedTimer.restart();
}

void GraphicsScene::handleRewards()
{
    std::vector<core::Reward> rewards;
    m_world.takeRewards(rewards);
    for (const core::Reward& reward: rewards) {
        core::vec2 pos = m_world.worldCoordFromIndex(reward.index);
        TextInformationPopupItem* popUp = new TextInformationPopupItem(QPointF(pos.x(), pos.y()), QString::number(reward.coins), reward.colorCode.c_str());
        addItem(popUp);
        m_popUps.push_back(popUp);
    }
}

void GraphicsScene::updatePopUps(int frameDeltaTimeMs)
{
    std::vector<TextInformationPopupItem*>::iterator it = m_popUps.begin();
    for (; it != m_popUps.end();) {
        TextInformationPopupItem* popUp = *it;
        popUp->update(frameDeltaTimeMs);
        if (popUp->isDone()) {
            it = m_popUps.erase(it);
            removeItem(popUp);
            delete popUp;
        } else {
            ++it;
        }
    }
}

void GraphicsScene::updateOverlay()
{
    const core::Grid& world = m_world.grid();
    for (std::size_t i=0; i<world.size(); ++i) {
        PixmapItem* tileView = m_tilesViews[i];
        if ((m_tileIndexUnderCursor != -1) && (i == static_cast<std::size_t>(m_tileIndexUnderCursor))) {
            if (m_world.grid().isIndexPassable(m_tileIndexUnderCursor)) {
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
