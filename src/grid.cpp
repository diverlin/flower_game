#include "gridmap.h"

#include <iostream>

GridMap::GridMap(int rows, int columns)
    :
    m_rows(rows),
    m_columns(columns),
    m_array(rows*columns)
{
    std::cout << "m_array.capacity=" << m_array.capacity() << std::endl;
}

GridMap::~GridMap()
{

}

bool GridMap::hasObject(int i, int j, ObjectLayer object)
{
    std::size_t _1d_index = getIndex1D(i, j);
    if (_1d_index < m_array.size()) {
        return static_cast<int>(object) & m_array[_1d_index];
    } else {
        std::cout << "ERROR:" << "cannot get 1D index from i=" << i << ", j=" << j << std::endl;
        return false;
    }
}

void GridMap::addObject(int i, int j, ObjectLayer value)
{
    std::size_t _1d_index = getIndex1D(i, j);
    if (_1d_index < m_array.size()) {
        m_array[_1d_index] |= static_cast<int>(value);
    } else {
        std::cout << "ERROR:" << "cannot get 1D index from i=" << i << ", j=" << j << std::endl;
    }
}

void GridMap::removeObject(int i, int j, ObjectLayer value)
{
    std::size_t _1d_index = getIndex1D(i, j);
    if (_1d_index < m_array.size()) {
        m_array[_1d_index] ^= static_cast<int>(value);
    } else {
        std::cout << "ERROR:" << "cannot get 1D index from i=" << i << ", j=" << j << std::endl;
    }
}

bool GridMap::isTilePassble(int i, int j) const
{
    std::size_t _1d_index = getIndex1D(i, j);
    if (_1d_index < m_array.size()) {
        int value = m_array.at(_1d_index);
        return (value == 0);
    } else {
        return false;
    }
}

std::size_t GridMap::getIndex1D(int i, int j) const
{
    return static_cast<std::size_t>(i * m_columns + j);
}
