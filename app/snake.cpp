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
        m_newPosDirtyIndexes.push_back(index);
    }

    m_hasPosDirtyIndexes = true;
}

void Snake::update(int frameDeltaTimeMs)
{
    if (isAlive()) {
        updateRandomMoveSwitch(frameDeltaTimeMs);
        updateGrow(frameDeltaTimeMs);
        updateMove(frameDeltaTimeMs);
    }
}

void Snake::updateRandomMoveSwitch(int frameDeltaTimeMs)
{
    m_sinceLastRandomDirectionChangeMs += frameDeltaTimeMs;
    if (m_sinceLastRandomDirectionChangeMs > m_moveRandomDirectionIntervalMs) {
        switch(m_direction) {
        case UP:
        case DOWN: m_direction = getRandomBool()? LEFT : RIGHT; break;
        case LEFT:
        case RIGHT: m_direction = getRandomBool()? UP : DOWN; break;
        }
        m_moveRandomDirectionIntervalMs = getRandomInt(0.5*DEFAULT_MOVE_RANDOM_DIRECTION_CHANGE_MS, 1.5*DEFAULT_MOVE_RANDOM_DIRECTION_CHANGE_MS);
        m_sinceLastRandomDirectionChangeMs = 0;
    }
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
    if (m_msSinceLastMove > int(m_moveIntervalMs / m_moveSpeedMultiplier)) {
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
    if (m_grid->hasLayer(m_grid->getIndex1D(newIndex2d), PixmapLayer::FLOWER_LAYER)) {
        m_eatenFlowerIndexes.push_back(newIndex2d);
    }

    m_oldPosDirtyIndexes.push_back(tail());
    push(newIndex2d);
    m_newPosDirtyIndexes.push_back(newIndex2d);

    m_hasPosDirtyIndexes = true;
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

void Snake::takeDirtyMoveIndexes(std::vector<Index2D>& oldIndexes, std::vector<Index2D>& newIndexes)
{
    oldIndexes.clear();
    newIndexes.clear();

    std::swap(oldIndexes, m_oldPosDirtyIndexes);
    std::swap(newIndexes, m_newPosDirtyIndexes);

    m_hasPosDirtyIndexes = false;
}

void Snake::takeEatenFlowerIndexes(std::vector<Index2D>& eatenIndexes)
{
    for (const Index2D& index2d: m_eatenFlowerIndexes) {
        eatenIndexes.push_back(index2d);
    }
    m_eatenFlowerIndexes.clear();
}

void Snake::hit()
{
    decreaseLength();
}

void Snake::increaseLength()
{
    int lengthCandidate = maxLength()+1;
    if (lengthCandidate <= int(LENGTH_MAX * m_maxLengthMultiplier)) {
        setMaxLength(lengthCandidate);
    }
}

void Snake::decreaseLength()
{
    int lengthCandidate = maxLength()-1;

    //std::cout<<"try snake decreaseLength to=" << lengthCandidate << std::endl;
    if (lengthCandidate > 0) {
        //std::cout<<"snake decreaseLength to=" << lengthCandidate << std::endl;
        if (size() >= lengthCandidate) {
            m_oldPosDirtyIndexes.push_back(tail());
            m_hasPosDirtyIndexes = true;
        }
        setMaxLength(lengthCandidate);
    } else {
        setDead();
    }
}

} // namespace core
