#ifndef GRIDMAP_H
#define GRIDMAP_H

#include <vector>

#include "objectlayer.h"

class GridMap
{
public:
    GridMap(int rows, int columns);
    ~GridMap();

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

#endif // GRIDMAP_H

