#include "flower.h"
#include "image.h"

#include <iostream>

namespace core {

Flower::Flower(const std::vector<Image>& images)
    :
    StaticObject(images)
{

}

void Flower::update(int frameDeltaTimeMs)
{
    std::cout<<"flower " << id() << " update"<<std::endl;
}

} // namespace core
