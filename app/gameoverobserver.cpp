#include "gameoverobserver.h"

#include "gridmap.h"

namespace core {

GameOverObserver::GameOverObserver(GridMap* world)
    :
    m_world(world)
{

}

void GameOverObserver::restart()
{
    m_hadFlowerAfterRestartGame = false;
    m_isGameOver = false;
}

void GameOverObserver::update()
{
    if (m_hadFlowerAfterRestartGame) {
        if ((m_world->flowersCounter() == 0) && (m_world->coins() < GridMap::FLOWER_COST)) {
            m_isGameOver = true;
        }
    } else {
        if (m_world->flowersCounter() > 0) {
            m_hadFlowerAfterRestartGame = true;
            // m_isGameOver = true; // uncomment for test screen transition
        }
    }
}

} // namespace core
