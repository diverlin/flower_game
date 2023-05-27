#include "graphicsscene.h"
#include "pixmapitem.h"
#include "pixmapprovider.h"
#include "textinformationitem.h"
#include "textinformationpopupitem.h"

#include <QApplication>

namespace view {

GraphicsScene::GraphicsScene(int x, int y, int width, int height, QObject* parent)
    :
    QGraphicsScene(x, y, width, height, parent)
    , m_screenWidth(width)
    , m_screenHeight(height)
#ifdef Q_OS_ANDROID
    , m_world(TILES_IN_ROW_NUM*width/float(height), TILES_IN_ROW_NUM, core::Size(width, height))
#else
    , m_world(TILES_IN_ROW_NUM, TILES_IN_ROW_NUM*height/float(width), core::Size(width, height))
#endif
    , m_gameOverObserver(&m_world)

{
    createTilesViews();

    // coin ico
    m_coinIcoItem = new PixmapItem;
    m_coinIcoItem->setPixmap(PixmapProvider::instance().getPixmap(":/tiles/coin.png", core::Size(ICON_SIZE, ICON_SIZE)), core::PixmapLayer::HUD_LAYER);
    m_coinIcoItem->setPos(5, 5);
    addItem(m_coinIcoItem);

    // coin label
    m_coinsCounterTextItem = new TextInformationItem(FONT_SIZE);
    m_coinsCounterTextItem->setPos(1.2*ICON_SIZE, 0);
    addItem(m_coinsCounterTextItem);

    // prompt label
    m_promptTextItem = new TextInformationItem(PROMPT_LABEL_FONT_SIZE);
    addItem(m_promptTextItem);

    // gameover label
    m_gameOverTextItem = new TextInformationItem(GAMEOVER_LABEL_FONT_SIZE);
    m_gameOverTextItem->setMessage("GAME OVER");
    m_gameOverTextItem->setPos(m_screenWidth/2 - m_gameOverTextItem->width()/2, 0.33f*m_screenHeight);
    addItem(m_gameOverTextItem);

    QObject::connect(&m_gameLoopTimer, &QTimer::timeout, this, &GraphicsScene::updateGameLoop);

    m_gameLoopTimer.setInterval(20);

    showStartupScreen();
}

void GraphicsScene::showGamePlayScreen()
{
    restartGamePlay();

    // hide
    m_promptTextItem->setOpacity(0.0f);
    m_gameOverTextItem->setOpacity(0.0f);

    // show
    m_coinIcoItem->setOpacity(HUD_OPACITY);
    m_coinsCounterTextItem->setOpacity(HUD_OPACITY);

    m_gameOverTextItem->setOpacity(0.0f);

    m_isStartUpScreen = false;
}

void GraphicsScene::showStartupScreen()
{
    // hide
    m_coinIcoItem->setOpacity(0.0f);
    m_coinsCounterTextItem->setOpacity(0.0f);

    // show
    m_promptTextItem->setOpacity(HUD_OPACITY);

#ifdef Q_OS_ANDROID
    QString msg = "TAP on screen to start NEW GAME";
#else
    QString msg = "Press MOUSE BUTTON to start NEW GAME";
#endif

    if (m_gameOverObserver.isGameOver()) {
        m_gameOverTextItem->setOpacity(HUD_OPACITY);
    } else {
        m_gameOverTextItem->setOpacity(0.0f);
    }
    m_promptTextItem->setMessage(msg);
    m_promptTextItem->setPos(m_screenWidth/2 - m_promptTextItem->width()/2, m_screenHeight/2);

    stopGamePlay();
    m_isStartUpScreen = true;
}

void GraphicsScene::clearSession()
{
    m_world.reset();
}

void GraphicsScene::stopGamePlay()
{
    m_gameLoopTimer.stop();
}

void GraphicsScene::startGamePlay()
{
    m_world.onStart();
    m_gameLoopTimer.start();
    m_frameElapsedTimer.start();
    m_gameOverObserver.restart();
}

void GraphicsScene::restartGamePlay()
{
    stopGamePlay();
    clearSession();
    startGamePlay();
}

void GraphicsScene::onMousePositionChanged(const QPointF& scenePos)
{
    if (m_isStartUpScreen) {
        return;
    }
    m_tileIndexUnderCursor = m_world.indexFromWorldCoord(core::vec2(scenePos.x(), scenePos.y()));
}

void GraphicsScene::onMouseLeftButtonPress(const QPointF& /*scenePos*/)
{
    if (m_isStartUpScreen) {
        showGamePlayScreen();
        return;
    }

    if (m_tileIndexUnderCursor != -1) {
        m_world.tapOnBusyTile(m_tileIndexUnderCursor);
    }
}

void GraphicsScene::onMouseRightButtonPress(const QPointF& /*scenePos*/)
{
    if (m_isStartUpScreen) {
        showGamePlayScreen();
        return;
    }

    if (m_tileIndexUnderCursor != -1) {
        if (m_world.grid().isIndexFree(m_tileIndexUnderCursor)) {
            m_world.createFlower(m_tileIndexUnderCursor);
        } else {
            m_world.tapOnBusyTile(m_tileIndexUnderCursor);
        }
    }
}

void GraphicsScene::updateGameLoop()
{
    qint64 frameDeltaTimeMs = m_frameElapsedTimer.elapsed();

    m_coinsCounterTextItem->setMessage(QString("x%1").arg(m_world.coins()));

    m_world.update(frameDeltaTimeMs);
    updateTilesViews(m_world.tiles());
    updateOverlay();

    handleRewards();
    updatePopUps(frameDeltaTimeMs);

    m_gameOverObserver.update();
    if (m_gameOverObserver.isGameOver()) {
        resetTileViews();
        showStartupScreen();
    }

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
            if (m_world.grid().isIndexFree(m_tileIndexUnderCursor)) {
                tileView->setPixmap(PixmapProvider::instance().getPixmap(":/tiles/frame_blue_blurred.png", m_world.tileSize()), core::PixmapLayer::OVERLAY_LAYER);
            } else {
                tileView->setPixmap(PixmapProvider::instance().getPixmap(":/tiles/frame_red_blurred.png", m_world.tileSize()), core::PixmapLayer::OVERLAY_LAYER);
            }
        } else {
            tileView->removePixmap(core::PixmapLayer::OVERLAY_LAYER);
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

void GraphicsScene::resetTileViews()
{
    for (PixmapItem* view: m_tilesViews.values()) {
        view->clear();
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
                if (!imageFilePath.empty()) { // sometimes we clear the image path in tile for a specific layer in order to remove it
                    view->setPixmap(PixmapProvider::instance().getPixmap(imageFilePath.c_str(), m_world.tileSize()), layer);
                } else {
                    view->removePixmap(layer);
                }
            }
            tile.resetIsDirtyFlag();
        }
    }
}

} // namespace view
