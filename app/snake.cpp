#include "snake.h"

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

} // namespace core
