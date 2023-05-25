#ifndef SNAKE_H
#define SNAKE_H

#include "fixedqueue.h"
#include "index2d.h"

#include <vector>

namespace core {

class Snake : public FixedQueue<Index2D>
{
public:
    Snake(std::size_t maxLength, const std::vector<Index2D>& indexes);
    ~Snake()=default;
};

} // namespace core

#endif // SNAKE_H
