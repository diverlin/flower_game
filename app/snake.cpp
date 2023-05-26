#include "snake.h"

#include <iostream>

namespace core {

Snake::Snake(const Image& image, std::size_t maxLength, const std::vector<Index2D>& indexes)
    :
    FixedQueue<Index2D>(maxLength)
    , m_image(image)
{
    for (const Index2D& index: indexes) {
        push(index);
    }
}

void Snake::update(int frameDeltaTimeMs)
{
    //std::cout<<"snake " << id() << " update"<<std::endl;
}

} // namespace core
