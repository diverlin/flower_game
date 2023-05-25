#ifndef GRIDMAP_H
#define GRIDMAP_H

#include "grid.h"
#include "size.h"
#include "vec2.h"
#include "index2d.h"
#include "tilelayer.h"
#include "tile.h"

#include <vector>

class StaticObject;

class GridMap
{
public:
    GridMap(int rows, int columns, const Size& size);
    ~GridMap();

    void create();

    const Size& tileSize() const { return m_tileSize; }
    const Grid& grid() const { return m_grid; }

    vec2 worldCoordFromIndex(std::size_t) const;
    vec2 worldCoordFromIndex(const Index2D&) const;

    void addTile(Tile& tile, int i, int j);
    void addTile(Tile& tile, const Index2D&);
    void removeTile(int i, int j, TileLayer tileLayer);
    
    void addStaticObject(StaticObject&, int i, int j);
    void addStaticObject(StaticObject&, const Index2D&);

    const std::vector<Tile>& tiles() const { return m_tiles; }
    const std::vector<StaticObject>& staticObjects() const { return m_staticObjects; }

private:
    Grid m_grid;
    Size m_tileSize = Size(10, 10);
    std::vector<Tile> m_tiles;
    std::vector<StaticObject> m_staticObjects;

    void createGroundLayer();
    void createGrassLayer(int numMin, int numMax);
    void createRockLayer(int numMin, int numMax);
    void createWoodLayer(int numMin, int numMax);
    void createTreeLayer(int numMin, int numMax);
};

#endif // GRIDMAP_H

