#ifndef SNAKE_H
#define SNAKE_H

#include "fixedqueue.h"
#include "index2d.h"

class Snake : public FixedQueue<Index2D>
{
public:
    Snake(std::size_t maxLength): FixedQueue<Index2D>(maxLength) {}
    ~Snake()=default;
};

#endif // SNAKE_H
