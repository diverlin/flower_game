#ifndef GRIDMAP_H
#define GRIDMAP_H

#include <vector>

#include "index2d.h"
#include "tilelayer.h"
#include "tile.h"

class GameObject;

class GridMap
{
public:
    GridMap(int rows, int columns);
    ~GridMap();

    void create();

    bool hasTile(int i, int j, TileLayer tileLayer);
    void addTile(Tile& tile, int i, int j);
    void addTile(Tile& tile, const Index2D&);
    void removeTile(int i, int j, TileLayer tileLayer);

    bool isTilePassble(const Index2D&) const;

    void addObject(GameObject&, const Index2D&);
    void addObject(GameObject&, int i, int j);

    const std::vector<Tile>& tiles() const { return m_tiles; }
    const std::vector<GameObject>& objects() const { return m_objects; }

private:
    int m_rows = -1;
    int m_columns = -1;
    std::vector<int> m_array;
    std::vector<int> m_randomIndexes;

    std::vector<Tile> m_tiles;
    std::vector<GameObject> m_objects;

    std::size_t getIndex1D(int i, int j) const;
    std::size_t getIndex1D(const Index2D&) const;
    Index2D getIndex2D(size_t index1D) const;

    void createGroundLayer();
    void createGrassLayer(int numMin, int numMax);
    void createRockLayer(int numMin, int numMax);
    void createWoodLayer(int numMin, int numMax);
    void createTreeLayer(int numMin, int numMax);

    Index2D getFreeRandomIndex(const std::vector<Index2D>& localOffsets = {}) const;
};

#endif // GRIDMAP_H

