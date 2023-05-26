#ifndef SNAKE_H
#define SNAKE_H

#include "ibaseobject.h"
#include "fixedqueue.h"
#include "index2d.h"
#include "image.h"

#include <vector>

namespace core {

class Snake : public FixedQueue<Index2D>, public IBaseObject
{
    const int GROW_INTERVAL_MS = 4000;
    const int DEFAULT_MOVE_INTERVAL_MS = 2000;
    const int LENGTH_MIN = 2;
    const int LENGTH_MAX = 5;

public:
    Snake(const Image& image, std::size_t maxLength, const std::vector<Index2D>& indexes);
    ~Snake()=default;

    bool hasDirtyIndexes() const { return m_hasDirtyIndexes; }

    const Image& image() const { return m_image; }
    void update(int frameDeltaTimeMs) override final;

    void decreaseLength();

    const Index2D& head() const { return first(); }
    const Index2D& tail() const { return last(); }

    void takeDirtyIndexes(std::vector<Index2D>& oldIndexes, std::vector<Index2D>& newIndexes);

private:
    bool m_hasDirtyIndexes = false;
    Image m_image;
    int m_msSinceLastGrow = 0;
    int m_msSinceLastMove = 0;
    int m_moveIntervalMs = DEFAULT_MOVE_INTERVAL_MS;

    // used to notify render to add/remove snake segment
    std::vector<Index2D> m_oldDirtyIndexes;
    std::vector<Index2D> m_newDirtyIndexes;
    //

    void increaseLength();

    void updateGrow(int frameDeltaTimeMs);
    void updateMove(int frameDeltaTimeMs);
    void move();
};

} // namespace core

#endif // SNAKE_H
