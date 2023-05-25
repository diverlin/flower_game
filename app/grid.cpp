#include "grid.h"
#include "randutils.h"

#include <algorithm>
#include <iostream>

namespace core {

Grid::Grid(int rows, int columns)
    :
    m_rows(rows),
    m_columns(columns),
    m_elements(rows*columns)
{
    for (int i=0; i<rows*columns; ++i) {
        m_randomIndexes.push_back(i);
    }
    randomizeVector(m_randomIndexes);
    std::cout << "m_array.capacity=" << m_elements.capacity() << std::endl;
}

bool Grid::hasLayer(std::size_t index1d, PixmapLayer PixmapLayer) const
{
    if (index1d < m_elements.size()) {
        return static_cast<int>(PixmapLayer) & m_elements[index1d];
    } else {
        std::cout << "ERROR:" << "index1d=" << index1d << "bigger than array size" << std::endl;
        return false;
    }
}

bool Grid::addLayer(std::size_t index1d, PixmapLayer layer)
{
    if (index1d < size()) {
        m_elements[index1d] |= static_cast<int>(layer);
        return true;
    } else {
        std::cout << "ERROR:" << "index1d=" << index1d << "bigger than array size" << std::endl;
    }
    return false;
}

bool Grid::removeLayer(std::size_t index1d, PixmapLayer layer)
{
    if (index1d < m_elements.size()) {
        m_elements[index1d] ^= static_cast<int>(layer);
        return true;
    } else {
        std::cout << "ERROR:" << "index1d=" << index1d << "bigger than array size" << std::endl;
    }
    return false;
}

bool Grid::isIndexFree(const Index2D& index2d) const
{
    if (index2d.i() >= m_columns || index2d.j() >= m_rows) {
        return false;
    }
    std::size_t index1d = getIndex1D(index2d.i(), index2d.j());
    if (index1d < m_elements.size()) {
        int value = m_elements.at(index1d);
        return (value == 0);
    } else {
        return false;
    }
}

bool Grid::isIndexPassable(const Index2D& index2D) const
{
    std::size_t index1d = getIndex1D(index2D.i(), index2D.j());
    if (index1d < m_elements.size()) {
        int value = m_elements.at(index1d);
        return (value == 0); // check bitmask here
    } else {
        return false;
    }
}

std::size_t Grid::getIndex1D(int i, int j) const
{
    return static_cast<std::size_t>(i * m_columns + j);
}

std::size_t Grid::getIndex1D(const Index2D& index2d) const
{
    return getIndex1D(index2d.i(), index2d.j());
}

Index2D Grid::getIndex2D(size_t index1d) const
{
    return Index2D(index1d / m_columns, index1d % m_columns);
}

int Grid::getFreeRandomIndex(const std::vector<Index2D>& localOffsets) const
{
    for (int randIndex1D: m_randomIndexes) {
        Index2D topLeftIndex = getIndex2D(randIndex1D);
        if (isIndexFree(topLeftIndex)) {
            if (localOffsets.empty()) {
                return randIndex1D;
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
                    return randIndex1D;
                }
            }
        }
    }

    return -1; // return ivalid index
}

Index2D Grid::getFreeRandomIndex2D(const std::vector<Index2D>& localOffsets) const
{
    int index1d = getFreeRandomIndex(localOffsets);
    if (index1d != -1) {
        return getIndex2D(index1d);
    } else {
        return Index2D();
    }
}

} // namespace core
