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
    const int GROW_INTERVAL_MS = 2000;
    const int LENGTH_GROW_LIMIT = 5;

public:
    Snake(const Image& image, std::size_t maxLength, const std::vector<Index2D>& indexes);
    ~Snake()=default;

    const Image& image() const { return m_image; }
    void update(int frameDeltaTimeMs);

private:
    Image m_image;
    int m_msSinceLastGrow = 0;
};

} // namespace core

#endif // SNAKE_H
