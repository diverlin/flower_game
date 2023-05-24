#ifndef GRID_H
#define GRID_H

#include <vector>

#include "objectlayer.h"

class Grid
{
public:
    Grid(int rows, int columns);
    ~Grid();

    bool hasObject(int i, int j, ObjectLayer object);
    void addObject(int i, int j, ObjectLayer object);
    void removeObject(int i, int j, ObjectLayer object);
    bool isTilePassble(int i, int j) const;

    int rows() const { return m_rows; }
    int columns() const { return m_columns; }

private:
    int m_rows = -1;
    int m_columns = -1;
    std::vector<int> m_array;

    std::size_t getIndex1D(int i, int j) const;
};

#endif // GRID_H

