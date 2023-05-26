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

void Flower::update(int frameDeltaTimeMs)
{
    m_msSinceLastCoinProduce += frameDeltaTimeMs;
    if (m_msSinceLastCoinProduce > PRODUCE_COIN_INTERVAL_MS) {
        m_coins += PRODUCE_COIN_AMOUNT;
        m_msSinceLastCoinProduce = 0;
        //std::cout<<"flower " << id() << " got coins" << m_coins << std::endl;
    }
    //std::cout<<"flower " << id() << " update"<<std::endl;
}

int Flower::takeCoins()
{
    int result = m_coins;
    m_coins = 0;
    return result;
}

} // namespace core
