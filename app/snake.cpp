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
    updateGrow(frameDeltaTimeMs);
    updateMove(frameDeltaTimeMs);
}

void Snake::updateGrow(int frameDeltaTimeMs)
{
    m_msSinceLastGrow += frameDeltaTimeMs;
    if (m_msSinceLastGrow > GROW_INTERVAL_MS) {
        increaseLength();
        m_msSinceLastGrow = 0;
    }
}

void Snake::updateMove(int frameDeltaTimeMs)
{
    m_msSinceLastMove += frameDeltaTimeMs;
    if (m_msSinceLastMove > m_moveIntervalMs) {
        move();
        m_msSinceLastMove = 0;
    }
}

void Snake::move()
{
    m_oldDirtyIndexes.push_back(tail());

    Index2D newIndex2d(head());
    newIndex2d += Index2D(0, 1);

    push(newIndex2d);

    m_newDirtyIndexes.push_back(newIndex2d);

    std::cout << "move snake to=" << newIndex2d << std::endl;
    m_hasDirtyIndexes = true;
}

void Snake::takeDirtyIndexes(std::vector<Index2D>& oldIndexes, std::vector<Index2D>& newIndexes)
{
    oldIndexes.clear();
    newIndexes.clear();

    std::swap(oldIndexes, m_oldDirtyIndexes);
    std::swap(newIndexes, m_newDirtyIndexes);

    m_hasDirtyIndexes = false;
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
