#ifndef GRID_H
#define GRID_H

#include "index2d.h"
#include "tilelayer.h"

#include <vector>

class Grid {
public:
    Grid(int rows, int columns);

    int rows() const { return m_rows; }
    int columns() const { return m_columns; }

    std::size_t size() const { return m_elements.size(); }

    int value(std::size_t index1d) const {
        if (index1d >= size()) {
            return -1;
        }
        return m_elements.at(index1d);
    }
    bool isIndexPassable(const Index2D& index2D) const;
    bool isIndexFree(const Index2D& index2D) const;

    bool addLayer(const Index2D& index2d, TileLayer layer);
    bool addLayer(int i, int j, TileLayer layer);
    void removeLayer(int i, int j, TileLayer layer);

    bool hasLayer(int i, int j, TileLayer layer) const;

    std::size_t getIndex1D(int i, int j) const;
    std::size_t getIndex1D(const Index2D&) const;
    Index2D getIndex2D(std::size_t index1D) const;

    Index2D getFreeRandomIndex(const std::vector<Index2D>& localOffsets = {}) const;

private:
    int m_rows = -1;
    int m_columns = -1;

    std::vector<int> m_elements;
    std::vector<int> m_randomIndexes;
};

#endif // GRID_H

