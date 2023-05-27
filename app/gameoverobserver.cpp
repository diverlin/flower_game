#include "gameoverobserver.h"

#include "gridmap.h"

namespace core {

GameOverObserver::GameOverObserver(GridMap* world)
    :
    m_world(world)
{

}

void GameOverObserver::onStart()
{
    m_hadFlowerAfterRestartGame = false;
    m_gameOverRequested = false;
}

void GameOverObserver::update()
{
    if (m_hadFlowerAfterRestartGame) {
        if ((m_world->flowersCounter() == 0) && (m_world->coins() < GridMap::FLOWER_COST)) {
            m_gameOverRequested = true;
        }
    } else {
        if (m_world->flowersCounter() > 0) {
            m_hadFlowerAfterRestartGame = true;
        }
    }
}

} // namespace core
