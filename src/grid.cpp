#include "grid.h"

#include <iostream>

Grid::Grid(int rows, int columns)
    :
    m_rows(rows),
    m_columns(columns),
    m_array(rows*columns)
{
    std::cout << "m_array.capacity=" << m_array.capacity() << std::endl;
}

Grid::~Grid()
{

}

bool Grid::setTileBusy(int i, int j, int value)
{
    int _1d_index = getIndex1D(i, j);
    if (_1d_index < m_array.size()) {
        m_array[_1d_index] = value;
    } else {
        std::cout << "ERROR:" << "cannot get 1D index from i=" << i << ", j=" << j << std::endl;
    }
}

bool Grid::isTileFree(int i, int j) const
{
    int _1d_index = getIndex1D(i, j);
    if (_1d_index < m_array.size()) {
        int value = m_array.at(_1d_index);
        return (value == 0);
    } else {
        return false;
    }
}

int Grid::getIndex1D(int i, int j) const
{
    return i * m_columns + j;
}
