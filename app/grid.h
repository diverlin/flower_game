#ifndef GRID_H
#define GRID_H

#include "index2d.h"
#include "pixmaplayer.h"

#include <vector>

namespace core {

class Grid {
public:
    Grid(int rows, int columns);

    void reset();
    void randomizeIndexes();

    int rows() const { return m_rows; }
    int columns() const { return m_columns; }

    std::size_t size() const { return m_elements.size(); }

    int value(std::size_t index1d) const {
        if (index1d >= size()) {
            return -1;
        }
        return m_elements.at(index1d);
    }
    bool isValid(const Index2D& index2d) const;
    bool isIndexPassable(const Index2D&) const;
    bool isIndexPassable(std::size_t index) const;
    bool isIndexFree(std::size_t index) const;

    bool hasLayer(std::size_t index1d, PixmapLayer layer) const;
    bool addLayer(std::size_t index1d, PixmapLayer layer);
    bool removeLayer(std::size_t index1d, PixmapLayer layer);

    std::size_t getIndex1D(int i, int j) const;
    std::size_t getIndex1D(const Index2D&) const;
    Index2D getIndex2D(std::size_t index1D) const;

    int getFreeRandomIndex(const std::vector<Index2D>& localOffsets = {}) const;
    Index2D getFreeRandomIndex2D(const std::vector<Index2D>& localOffsets = {}) const;

private:
    int m_rows = -1;
    int m_columns = -1;

    int m_obsticalsMask = 0;

    std::vector<int> m_elements;
    std::vector<int> m_randomIndexes; // used for randomization objects on the map

    bool contain(int layer, int value) const;
};

} // namespace core

#endif // GRID_H

