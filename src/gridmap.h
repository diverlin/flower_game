#ifndef GRIDMAP_H
#define GRIDMAP_H

#include <vector>

#include "index2d.h"
#include "tilelayer.h"
#include "tile.h"

class GridMap
{
public:
    GridMap(int rows, int columns);
    ~GridMap();

    void create();

    bool hasTile(int i, int j, TileLayer tileLayer);
    void addTile(const Tile& tile, int i, int j);
    void removeTile(int i, int j, TileLayer tileLayer);

    bool isTilePassble(const Index2D&) const;
//    bool isTilePassble(int index1D) const;

    const std::vector<Tile>& tiles() const { return m_tiles; }

private:
    int m_rows = -1;
    int m_columns = -1;
    std::vector<int> m_array;
    std::vector<int> m_randomIndexes;

    std::vector<Tile> m_tiles;

    std::size_t getIndex1D(int i, int j) const;
    std::size_t getIndex1D(const Index2D&) const;
    Index2D getIndex2D(size_t index1D) const;

    void createGroundLayer();
    void createGrassLayer(int numMin, int numMax);
    void createRockLayer(int numMin, int numMax);
    void createWoodLayer(int numMin, int numMax);
    void createTreeLayer(int numMin, int numMax);

    Index2D getFreeRandomIndex(const Index2D& offsetFromTopLeftCorner = Index2D(0,0)) const;
};

#endif // GRIDMAP_H

