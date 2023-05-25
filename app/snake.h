#ifndef SNAKE_H
#define SNAKE_H

#include "fixedqueue.h"
#include "index2d.h"
#include "image.h"

#include <vector>

namespace core {

class Snake : public FixedQueue<Index2D>
{
public:
    Snake(const Image& image, std::size_t maxLength, const std::vector<Index2D>& indexes);
    ~Snake()=default;

    const Image& image() const { return m_image; }

private:
    Image m_image;
};

} // namespace core

#endif // SNAKE_H
