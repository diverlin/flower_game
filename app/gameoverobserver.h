#ifndef GAMEOVEROBSERVER_H
#define GAMEOVEROBSERVER_H

namespace core {

class GridMap;

class GameOverObserver
{
public:
    GameOverObserver(GridMap* world);
    ~GameOverObserver()=default;

    void restart();

    bool isGameOver() const { return m_isGameOver; }

    void update();

private:
    bool m_isGamePlayRunning = false;

    GridMap* m_world = nullptr;

    bool m_hadFlowerAfterRestartGame = false;
    bool m_isGameOver = false;
};

} // namespace core

#endif // GAMEOVEROBSERVER_H
