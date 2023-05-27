#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "../gridmap.h"
#include "../gameoverobserver.h"

#include <QGraphicsScene>
#include <QTimer>
#include <QMap>
#include <QElapsedTimer>

namespace view {

class TextInformationPopupItem;
class TextInformationItem;
class PixmapItem;

class GraphicsScene : public QGraphicsScene
{
Q_OBJECT

#ifdef Q_OS_ANDROID
    const int TILES_IN_ROW_NUM = 18;
#else
    const int TILES_IN_ROW_NUM = 24;
#endif

    const float HUD_OPACITY = 0.8f;
    const int ICON_SIZE = 20;
    const int FONT_SIZE = 14;
    const int PROMPT_LABEL_FONT_SIZE = 18;
    const int GAMEOVER_LABEL_FONT_SIZE = 42;

public:
    GraphicsScene(int x, int y, int width, int height, QObject* parent = nullptr);

    void showGamePlayScreen();
    void showStartupScreen();

    void onMousePositionChanged(const QPointF&);
    void onMouseLeftButtonPress(const QPointF&);
    void onMouseRightButtonPress(const QPointF&);

private:
    bool m_isStartUpScreen = true;
    int m_screenWidth = 0;
    int m_screenHeight = 0;

    PixmapItem* m_coinIcoItem = nullptr;
    TextInformationItem* m_coinsCounterTextItem = nullptr;
    TextInformationItem* m_promptTextItem = nullptr;
    TextInformationItem* m_gameOverTextItem = nullptr;

    int m_tileIndexUnderCursor;
    core::GridMap m_world;
    QTimer m_gameLoopTimer;
    QMap<size_t, PixmapItem*> m_tilesViews;

    std::vector<TextInformationPopupItem*> m_popUps;

    QElapsedTimer m_frameElapsedTimer;

    core::GameOverObserver m_gameOverObserver;

    void restartGamePlay();
    void startGamePlay();
    void stopGamePlay();
    void clearSession();

    void createTilesViews();
    void updateOverlay();
    void resetTileViews();
    void updateTilesViews(const std::vector<core::Tile>&);
    void handleRewards();
    void updatePopUps(int frameDeltaTimeMs);

    void updateGameLoop();
};

} // namespace view

#endif // GRAPHICSSCENE_H
