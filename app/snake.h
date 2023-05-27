#ifndef SNAKE_H
#define SNAKE_H

#include "ibaseobject.h"
#include "fixedqueue.h"
#include "index2d.h"
#include "image.h"

#include <vector>

namespace core {

class Grid;

class Snake : public FixedQueue<Index2D>, public IBaseObject
{
    const int GROW_INTERVAL_MS = 3000;
    const int DEFAULT_MOVE_INTERVAL_MS = 500;
    const int LENGTH_MAX = 5;

    enum Direction { LEFT, RIGHT, UP, DOWN };

public:
    Snake(Grid* grid, const Image& image, std::size_t maxLength, const std::vector<Index2D>& indexes);
    ~Snake()=default;

    bool hasDirtyIndexes() const { return m_hasPosDirtyIndexes; }

    const Image& image() const { return m_image; }
    void update(int frameDeltaTimeMs) override final;

    void hit();

    const Index2D& head() const { return first(); }
    const Index2D& tail() const { return last(); }

    // we redraw only changed segments in order to minimize the tile redraw logic
    void takeDirtyMoveIndexes(std::vector<Index2D>& oldIndexes, std::vector<Index2D>& newIndexes);

    bool hasEatenFlowers() const { return !m_eatenFlowerIndexes.empty(); }
    void takeEatenFlowerIndexes(std::vector<Index2D>& eatenIndexes);

    void setMoveSpeedMultiplier(float moveSpeedMultiplier) { m_moveSpeedMultiplier = moveSpeedMultiplier; }
    void setMaxLengthMultiplier(float maxLengthMultiplier) { m_maxLengthMultiplier = maxLengthMultiplier; }

private:
    Grid* m_grid = nullptr;

    float m_moveSpeedMultiplier = 1.0f;
    float m_maxLengthMultiplier = 1.0f;

    Image m_image;
    int m_msSinceLastGrow = 0;
    int m_msSinceLastMove = 0;
    int m_moveIntervalMs = DEFAULT_MOVE_INTERVAL_MS;

    int m_direction = UP;

    // used to notify render to add/remove snake segment
    bool m_hasPosDirtyIndexes = false;
    std::vector<Index2D> m_oldPosDirtyIndexes;
    std::vector<Index2D> m_newPosDirtyIndexes;
    //

    // to check the eaten flowers
    std::vector<Index2D> m_eatenFlowerIndexes;

    void decreaseLength();
    void increaseLength();

    void updateGrow(int frameDeltaTimeMs);
    void updateMove(int frameDeltaTimeMs);
    void handleMove();
    void move(const Index2D&);

    bool checkIndex(const Index2D&) const;
    Index2D nextUpIndex() const;
    Index2D nextDownIndex() const;
    Index2D nextLeftIndex() const;
    Index2D nextRightIndex() const;

    bool probeUpIndex() const;
    bool probeDownIndex() const;
    bool probeLeftIndex() const;
    bool probeRightIndex() const;

    bool tryMoveUp();
    bool tryMoveDown();
    bool tryMoveRight();
    bool tryMoveLeft();
    bool tryMoveLeftOrRight();
    bool tryMoveUpOrDown();
};

} // namespace core

#endif // SNAKE_H
