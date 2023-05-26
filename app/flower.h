#ifndef FLOWER_H
#define FLOWER_H

#include "staticobject.h"

#include <string>
#include <vector>

namespace core {

class Image;

class Flower final: public StaticObject
{
    const int PRODUCE_COIN_INTERVAL_MS = 3000;
    const int PRODUCE_COIN_AMOUNT = 5;

public:
    Flower(const std::vector<Image>& images, const std::string& colorCode);
    ~Flower() override final;

    void update(int frameDeltaTimeMs) override final;
    int takeCoins();
    const std::string& colorCode() const { return m_colorCode; }

private:
    std::string m_colorCode;
    int m_coins = 0;
    int m_msSinceLastCoinProduce = 0;
};

} // namespace core

#endif // FLOWER_H
