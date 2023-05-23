#ifndef GRID_H
#define GRID_H

#include <vector>

class Grid
{
public:
    Grid(int rows, int columns);
    ~Grid();

    bool setTileBusy(int i, int j, int value);
    bool isTileFree(int i, int j) const;

    int rows() const { return m_rows; }
    int columns() const { return m_columns; }

private:
    int m_rows = -1;
    int m_columns = -1;
    std::vector<int> m_array;

    int getIndex1D(int i, int j) const;
};

#endif // GRID_H

