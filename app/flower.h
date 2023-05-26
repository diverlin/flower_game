#ifndef FLOWER_H
#define FLOWER_H

#include "staticobject.h"

#include <string>
#include <vector>

namespace core {

class Image;

class Flower final: public StaticObject
{
public:
    Flower(const std::vector<Image>& images);
    ~Flower() override final = default;

    void update(int frameDeltaTimeMs) override final;
};

} // namespace core

#endif // FLOWER_H
