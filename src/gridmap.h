#ifndef GRIDMAP_H
#define GRIDMAP_H

#include "grid.h"
#include "index2d.h"
#include "tilelayer.h"
#include "tile.h"

#include <vector>

class GameObject;

class GridMap
{
public:
    GridMap(int rows, int columns);
    ~GridMap();

    void create();

    void addTile(Tile& tile, int i, int j);
    void addTile(Tile& tile, const Index2D&);
    void removeTile(int i, int j, TileLayer tileLayer);

    void addObject(GameObject&, const Index2D&);
    void addObject(GameObject&, int i, int j);

    const std::vector<Tile>& tiles() const { return m_tiles; }
    const std::vector<GameObject>& objects() const { return m_objects; }

private:
    Grid m_grid;
    std::vector<Tile> m_tiles;
    std::vector<GameObject> m_objects;

    void createGroundLayer();
    void createGrassLayer(int numMin, int numMax);
    void createRockLayer(int numMin, int numMax);
    void createWoodLayer(int numMin, int numMax);
    void createTreeLayer(int numMin, int numMax);
};

#endif // GRIDMAP_H

