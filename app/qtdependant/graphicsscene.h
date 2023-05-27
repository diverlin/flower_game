#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "../gridmap.h"

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

public:
    GraphicsScene(int x, int y, int width, int height, QObject* parent = nullptr);

    void onMousePositionChanged(const QPointF&);
    void onMouseLeftButtonPress(const QPointF&);
    void onMouseRightButtonPress(const QPointF&);

private:
    TextInformationItem* m_textInformationItem;
    PixmapItem* m_coinIcoItem = nullptr;

    int m_tileIndexUnderCursor;
    core::GridMap m_world;
    QTimer m_gameLoopTimer;
    QMap<size_t, PixmapItem*> m_tilesViews;

    std::vector<TextInformationPopupItem*> m_popUps;

    QElapsedTimer m_frameElapsedTimer;
    
    void createTilesViews();
    void updateOverlay();
    void updateTilesViews(const std::vector<core::Tile>&);
    void handleRewards();
    void updatePopUps(int frameDeltaTimeMs);

    void updateGameLoop();
};

} // namespace view

#endif // GRAPHICSSCENE_H
