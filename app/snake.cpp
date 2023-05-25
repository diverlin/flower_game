#include "snake.h"

namespace core {

Snake::Snake(std::size_t maxLength, const std::vector<Index2D>& indexes)
    :
    FixedQueue<Index2D>(maxLength)
{
    for (const Index2D& index: indexes) {
        push(index);
    }
}

} // namespace core
