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
    m_msSinceLastGrow += frameDeltaTimeMs;
    if (m_msSinceLastGrow > GROW_INTERVAL_MS) {
        //increaseLength();
        m_msSinceLastGrow = 0;
    }
    //std::cout<<"snake " << id() << " update"<<std::endl;
}

void Snake::increaseLength()
{
    int lengthCandidate = maxLength()+1;
    if (lengthCandidate <= LENGTH_MAX) {
        setMaxLength(lengthCandidate);
    }
}

void Snake::decreaseLength()
{
    int lengthCandidate = maxLength()-1;
    std::cout<<"try snake decreaseLength to" << lengthCandidate << std::endl;
    if (lengthCandidate > LENGTH_MIN) {
        std::cout<<"snake decreaseLength to" << lengthCandidate << std::endl;
        setMaxLength(lengthCandidate);
    }
}

} // namespace core
