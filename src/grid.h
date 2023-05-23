#ifndef GRID_H
#define GRID_H

#include <vector>

class Grid
{
public:
    Grid(int rows, int columns);
    ~Grid();

    int rows() const { return m_rows; }
    int columns() const { return m_columns; }

private:
    int m_rows = -1;
    int m_columns = -1;
    std::vector<int> m_array;
};

#endif // GRID_H

