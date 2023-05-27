#include "flower.h"
#include "image.h"

#include <iostream>

namespace core {

Flower::Flower(const std::vector<Image>& images, const std::string& colorCode)
    :
    StaticObject(images)
    , m_colorCode(colorCode)
{

}

Flower::~Flower()
{
}

void Flower::update(int frameDeltaTimeMs)
{
    if (isAlive()) {
        StaticObject::update(frameDeltaTimeMs);
        m_msSinceLastCoinProduce += frameDeltaTimeMs;
        if (m_msSinceLastCoinProduce > PRODUCE_COIN_INTERVAL_MS) {
            m_coins += PRODUCE_COIN_AMOUNT;
            m_msSinceLastCoinProduce = 0;
        }
    }
}

int Flower::takeCoins()
{
    int result = m_coins;
    m_coins = 0;
    return result;
}

} // namespace core
