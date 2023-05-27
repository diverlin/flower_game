#ifndef GAMEOVEROBSERVER_H
#define GAMEOVEROBSERVER_H

namespace core {

class GridMap;

class GameOverObserver
{
public:
    GameOverObserver(GridMap* world);
    ~GameOverObserver()=default;

    void onStart();

    bool gameOverRequested() const { return m_gameOverRequested; }

    void update();

private:
    bool m_isGamePlayRunning = false;

    GridMap* m_world = nullptr;

    bool m_hadFlowerAfterRestartGame = false;
    bool m_gameOverRequested = false;
};

} // namespace core

#endif // GAMEOVEROBSERVER_H
