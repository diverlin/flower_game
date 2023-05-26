#include "snake.h"
#include "grid.h"
#include "randutils.h"

#include <iostream>

namespace core {

Snake::Snake(Grid* grid, const Image& image, std::size_t maxLength, const std::vector<Index2D>& indexes)
    :
    FixedQueue<Index2D>(maxLength)
    , m_grid(grid)
    , m_image(image)
{
    for (const Index2D& index: indexes) {
        push(index);
        m_newDirtyIndexes.push_back(index);
    }

    m_hasDirtyIndexes = true;
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
        handleMove();
        m_msSinceLastMove = 0;
    }
}

bool Snake::tryMoveUp()
{
    if (probeUpIndex()) {
        m_direction = UP;
        move(nextUpIndex());
        return true;
    }
    return false;
}

bool Snake::tryMoveDown()
{
    if (probeDownIndex()) {
        m_direction = DOWN;
        move(nextDownIndex());
        return true;
    }
    return false;
}

bool Snake::tryMoveRight()
{
    if (probeRightIndex()) {
        m_direction = RIGHT;
        move(nextRightIndex());
        return true;
    }
    return false;
}

bool Snake::tryMoveLeft()
{
    if (probeLeftIndex()) {
        m_direction = LEFT;
        move(nextLeftIndex());
        return true;
    }
    return false;
}

bool Snake::tryMoveLeftOrRight()
{
    bool dice = getRandomBool();
    if (dice) {
        if (!tryMoveLeft()) {
            if (!tryMoveRight()) {
                return false;
            }
        }
    } else {
        if (!tryMoveRight()) {
            if (!tryMoveLeft()) {
                return false;
            }
        }
    }
    return true;
}

bool Snake::tryMoveUpOrDown()
{
    bool dice = getRandomBool();
    if (dice) {
        if (!tryMoveUp()) {
            if (!tryMoveDown()) {
                return false;
            }
        }
    } else {
        if (!tryMoveDown()) {
            if (!tryMoveUp()) {
                return false;
            }
        }
    }
    return true;
}

void Snake::handleMove()
{
    if (m_direction == UP) {
        if (!tryMoveUp()) {
            if (!tryMoveLeftOrRight()) {
                std::cout << "WARNING: snake="<< id() << " is blocked" << std::endl;
            }
        }
    } else if (m_direction == DOWN) {
        if (!tryMoveDown()) {
            if (!tryMoveLeftOrRight()) {
                std::cout << "WARNING: snake="<< id() << " is blocked" << std::endl;
            }
        }
    } else if (m_direction == LEFT) {
        if (!tryMoveLeft()) {
            if (!tryMoveUpOrDown()) {
                std::cout << "WARNING: snake="<< id() << " is blocked" << std::endl;
            }
        }
    } else if (m_direction == RIGHT) {
        if (!tryMoveRight()) {
            if (!tryMoveUpOrDown()) {
                std::cout << "WARNING: snake="<< id() << " is blocked" << std::endl;
            }
        }
    }
}

void Snake::move(const Index2D& newIndex2d)
{
    m_oldDirtyIndexes.push_back(tail());
    push(newIndex2d);
    m_newDirtyIndexes.push_back(newIndex2d);

    m_hasDirtyIndexes = true;
}

bool Snake::checkIndex(const Index2D& index2d) const
{
    if (m_grid->isValid(index2d) && m_grid->isIndexPassable(index2d)) {
        return true;
    }
    return false;
}

bool Snake::probeUpIndex() const
{
    return checkIndex(nextUpIndex());
}

bool Snake::probeDownIndex() const
{
    return checkIndex(nextDownIndex());
}

bool Snake::probeLeftIndex() const
{
    return checkIndex(nextLeftIndex());
}

bool Snake::probeRightIndex() const
{
    return checkIndex(nextRightIndex());
}

Index2D Snake::nextUpIndex() const
{
    return Index2D(head() + Index2D(0,-1));
}

Index2D Snake::nextDownIndex() const
{
    return Index2D(head()+Index2D(0,1));
}

Index2D Snake::nextLeftIndex() const
{
    return Index2D(head()+Index2D(-1,0));
}

Index2D Snake::nextRightIndex() const
{
    return Index2D(head()+Index2D(1,0));
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
    //std::cout<<"try snake decreaseLength to=" << lengthCandidate << std::endl;
    if (lengthCandidate >= LENGTH_MIN) {
        //std::cout<<"snake decreaseLength to=" << lengthCandidate << std::endl;
        if (size() >= lengthCandidate) {
            m_oldDirtyIndexes.push_back(tail());
            m_hasDirtyIndexes = true;
        }
        setMaxLength(lengthCandidate);
    }
}

} // namespace core
