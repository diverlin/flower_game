#ifndef GRIDMAP_H
#define GRIDMAP_H

#include "grid.h"
#include "size.h"
#include "vec2.h"
#include "index2d.h"
#include "pixmaplayer.h"
#include "tile.h"

#include <vector>

namespace core {

class StaticObject;
class Snake;
class Image;

class GridMap
{
public:
    GridMap(int rows, int columns, const Size& size);
    ~GridMap();

    const Size& tileSize() const { return m_tileSize; }
    const Grid& grid() const { return m_grid; }

    // map coordinates between index and word/map coords
    vec2 worldCoordFromIndex(std::size_t) const;
    vec2 worldCoordFromIndex(const Index2D&) const;
    Index2D index2dFromWorldCoord(const vec2&) const;
    //

    const std::vector<Tile>& tiles() const { return m_tiles; }

private:
    Grid m_grid;
    Size m_tileSize = Size(10, 10);

    std::vector<Tile> m_tiles;
    std::vector<StaticObject> m_staticObjects;
//    std::vector<Snake*> m_snakes;

    void create();

    void createGround();
    void createGrasses(int numMin, int numMax);
    void createRocks(int numMin, int numMax);
    void createWoods(int numMin, int numMax);
    void createTrees(int numMin, int numMax);

    void addImageToTile(Image& image, int i);
    void addStaticObject(StaticObject&, int i);
    void addSnake(Snake*);
};

} // namespace core

#endif // GRIDMAP_H

