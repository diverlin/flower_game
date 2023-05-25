#ifndef GRIDMAP_H
#define GRIDMAP_H

#include "grid.h"
#include "index2d.h"
#include "tilelayer.h"
#include "tile.h"

#include <vector>

class StaticObject;

class GridMap
{
public:
    GridMap(int rows, int columns);
    ~GridMap();

    void create();

    void addTile(Tile& tile, int i, int j);
    void addTile(Tile& tile, const Index2D&);
    void removeTile(int i, int j, TileLayer tileLayer);
    
    void addStaticObject(StaticObject&, int i, int j);
    void addStaticObject(StaticObject&, const Index2D&);

    const std::vector<Tile>& tiles() const { return m_tiles; }
    const std::vector<StaticObject>& staticObjects() const { return m_staticObjects; }

private:
    Grid m_grid;
    std::vector<Tile> m_tiles;
    std::vector<StaticObject> m_staticObjects;

    void createGroundLayer();
    void createGrassLayer(int numMin, int numMax);
    void createRockLayer(int numMin, int numMax);
    void createWoodLayer(int numMin, int numMax);
    void createTreeLayer(int numMin, int numMax);
};

#endif // GRIDMAP_H

