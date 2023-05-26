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
    std::vector<core::PixmapLayer> obsticles = {
        core::PixmapLayer::ROCK_LAYER,
        core::PixmapLayer::WOOD_LAYER,
        core::PixmapLayer::SNAKE_LAYER,
        core::PixmapLayer::TREE_BOTTOM_LAYER
    };
    for (core::PixmapLayer layer: obsticles) {
        m_obsticalsMask |= static_cast<int>(layer);
    }

    for (int i=0; i<rows*columns; ++i) {
        m_randomIndexes.push_back(i);
    }

    randomizeIndexes();
    std::cout << "m_array.capacity=" << m_elements.capacity() << std::endl;
}

void Grid::randomizeIndexes()
{
    randomizeVector(m_randomIndexes);
}

bool Grid::hasLayer(std::size_t index1d, PixmapLayer layer) const
{
    if (index1d < size()) {
        return static_cast<int>(layer) & m_elements[index1d];
    }
    return false;
}

bool Grid::contain(int layer, int value) const
{
    return layer & value;
}

bool Grid::addLayer(std::size_t index1d, PixmapLayer layer)
{
    if (index1d < size()) {
        int l = static_cast<int>(layer);
        if (!contain(l, m_elements[index1d])) {
            m_elements[index1d] |= l;
            return true;
        }
    } else {
        std::cout << "ERROR:" << "index1d=" << index1d << " bigger than array size" << std::endl;
    }
    return false;
}

bool Grid::removeLayer(std::size_t index1d, PixmapLayer layer)
{
    if (index1d < m_elements.size()) {
        int l = static_cast<int>(layer);
        if (contain(l, m_elements[index1d])) {
            m_elements[index1d] ^= static_cast<int>(layer);
            return true;
        }
    } else {
        std::cout << "ERROR:" << "index1d=" << index1d << " bigger than array size" << std::endl;
    }
    return false;
}

bool Grid::isIndexFree(std::size_t index1d) const
{
    if (index1d < m_elements.size()) {
        int value = m_elements.at(index1d);
        return (value == 0) || (value == static_cast<int>(PixmapLayer::GROUND_LAYER));
    } else {
        return false;
    }
}

bool Grid::isValid(const Index2D& index2d) const
{
    if (!index2d.isValid()) {
        return false;
    }
    if ((index2d.i() >= m_rows) || (index2d.j() >= m_columns)) {
        return false;
    }
    return true;
}

bool Grid::isIndexPassable(const Index2D& index2d) const
{
    std::size_t index1d = getIndex1D(index2d);
    if (index1d < m_elements.size()) {
        int value = m_elements.at(index1d);
        return !(value & m_obsticalsMask);
    } else {
        return false;
    }
}

bool Grid::isIndexPassable(std::size_t index1d) const
{
    if (index1d < m_elements.size()) {
        int value = m_elements.at(index1d);
        return !(value & m_obsticalsMask);
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
    for (int topLeftIndex1d: m_randomIndexes) {
        Index2D topLeftIndex2d = getIndex2D(topLeftIndex1d);
        if (isIndexFree(topLeftIndex1d)) {
            if (localOffsets.empty()) {
                return topLeftIndex1d;
            } else {
                bool at_least_one_offset_slot_busy = false;
                for (const Index2D& localOffset: localOffsets) {
                    Index2D nextIndex2d(localOffset);
                    nextIndex2d += topLeftIndex2d;
                    std::size_t nextIndex1D = getIndex1D(nextIndex2d);
                    if (!isIndexFree(nextIndex1D)) {
                        at_least_one_offset_slot_busy = true;
                    }
                }

                if (!at_least_one_offset_slot_busy) {
                    return topLeftIndex1d;
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
