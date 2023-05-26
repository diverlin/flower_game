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
        m_newDirtyIndexes.push_back(index);
    }

    m_hasDirtyIndexes = true;
}

void Snake::setPath(std::vector<Index2D>& path)
{
    std::swap(path, m_path);
    m_currentPathIndex = 0;
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
        std::cout<<"snake id=" << id() <<" grow to size=" << size() << std::endl;
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
    if (m_path.empty()) {
        return;
    }
    if ((m_currentPathIndex != -1) && (m_currentPathIndex < m_path.size()-1)) {
        m_currentPathIndex++;

        m_oldDirtyIndexes.push_back(tail());

        Index2D newIndex2d(m_path[m_currentPathIndex]);

        push(newIndex2d);

        m_newDirtyIndexes.push_back(newIndex2d);

        std::cout << "move snake to=" << newIndex2d << std::endl;
        m_hasDirtyIndexes = true;
    } else {
        m_path.clear();
        m_currentPathIndex = -1;
    }
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
    std::cout<<"try snake decreaseLength to=" << lengthCandidate << std::endl;
    if (lengthCandidate >= LENGTH_MIN) {
        std::cout<<"snake decreaseLength to=" << lengthCandidate << std::endl;
        if (size() >= lengthCandidate) {
            m_oldDirtyIndexes.push_back(tail());
            m_hasDirtyIndexes = true;
        }
        setMaxLength(lengthCandidate);
    }
}

} // namespace core
