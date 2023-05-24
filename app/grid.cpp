#include "grid.h"
#include "randutils.h"

#include <algorithm>
#include <iostream>

Grid::Grid(int rows, int columns)
    :
    m_rows(rows),
    m_columns(columns),
    m_array(rows*columns)
{
    for (int i=0; i<rows*columns; ++i) {
        m_randomIndexes.push_back(i);
    }
    randomizeVector(m_randomIndexes);
    std::cout << "m_array.capacity=" << m_array.capacity() << std::endl;
}

bool Grid::hasLayer(int i, int j, TileLayer tileLayer) const
{
    std::size_t _1d_index = getIndex1D(i, j);
    if (_1d_index < m_array.size()) {
        return static_cast<int>(tileLayer) & m_array[_1d_index];
    } else {
        std::cout << "ERROR:" << "cannot get 1D index from i=" << i << ", j=" << j << std::endl;
        return false;
    }
}

bool Grid::addLayer(int i, int j, TileLayer layer)
{
    std::size_t index1d = getIndex1D(i, j);
    if (index1d < size()) {
        m_array[index1d] |= static_cast<int>(layer);
        return true;
    } else {
        std::cout << "ERROR:" << "cannot get 1D index from i=" << i << ", j=" << j << std::endl;
        return false;
    }
}

void Grid::removeLayer(int i, int j, TileLayer layer)
{
    std::size_t index1d = getIndex1D(i, j);
    if (index1d < m_array.size()) {
        m_array[index1d] ^= static_cast<int>(layer);
    } else {
        std::cout << "ERROR:" << "cannot get 1D index from i=" << i << ", j=" << j << std::endl;
    }
}

bool Grid::isIndexFree(const Index2D& index2D) const
{
    std::size_t index1d = getIndex1D(index2D.i(), index2D.j());
    if (index1d < m_array.size()) {
        int value = m_array.at(index1d);
        return (value == 0);
    } else {
        return false;
    }
}

//bool Grid::isIndexPassible(const Index2D& index2D) const
//{
//    std::size_t index1d = getIndex1D(index2D.i(), index2D.j());
//    if (index1d < m_array.size()) {
//        int value = m_array.at(index1d);
//        return (value == 0); // check bitmask here
//    } else {
//        return false;
//    }
//}

std::size_t Grid::getIndex1D(int i, int j) const
{
    return static_cast<std::size_t>(i * m_columns + j);
}

std::size_t Grid::getIndex1D(const Index2D& index2d) const
{
    return static_cast<std::size_t>(index2d.i() * m_columns + index2d.j());
}

Index2D Grid::getIndex2D(size_t index1D) const
{
    return Index2D(index1D / m_rows, index1D % m_rows);
}

Index2D Grid::getFreeRandomIndex(const std::vector<Index2D>& localOffsets) const
{
    for (int randIndex1D: m_randomIndexes) {
        Index2D topLeftIndex = getIndex2D(randIndex1D);
        if (isIndexFree(topLeftIndex)) {
            if (localOffsets.empty()) {
                return topLeftIndex;
            } else {
                bool at_least_one_offset_slot_busy = false;
                for (const Index2D& localOffset: localOffsets) {
                    Index2D nextIndex(localOffset);
                    nextIndex += topLeftIndex;
                    if (!isIndexFree(nextIndex)) {
                        at_least_one_offset_slot_busy = true;
                    }
                }

                if (!at_least_one_offset_slot_busy) {
                    return topLeftIndex;
                }
            }
        }
    }

    return Index2D(); // return ivalid index
}

