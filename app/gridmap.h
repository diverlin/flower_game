#ifndef GRIDMAP_H
#define GRIDMAP_H

#include "grid.h"
#include "size.h"
#include "vec2.h"
#include "index2d.h"
#include "pixmaplayer.h"
#include "tile.h"
#include "snakespropertymodifier.h"
#include "snakespawner.h"

#include <vector>

namespace core {

class IBaseObject;
class StaticObject;
class Snake;
class Image;

struct Reward {
    std::size_t index;
    int coins;
    std::string colorCode;
};

class GridMap
{
public:
    static const int FLOWER_COST = 50;
    const int START_COINS_NUM = 150;

    GridMap(int rows, int columns, const Size& size);
    ~GridMap();

    void onStart();
    void reset();

    int coins() const { return m_coins; }

    const Size& tileSize() const { return m_tileSize; }
    const Grid& grid() const { return m_grid; }

    // map coordinates between index and word/map coords
    vec2 worldCoordFromIndex(std::size_t) const;
    vec2 worldCoordFromIndex(const Index2D&) const;
    int indexFromWorldCoord(const vec2&) const;
    //

    void takeRewards(std::vector<Reward>& reward);

    void tapOnBusyTile(std::size_t index1d);
    void createFlower(std::size_t index1d);
    void update(int frameDeltaTimeMs);

    const std::vector<Tile>& tiles() const { return m_tiles; }

    int snakesCounter() const { return m_snakesCounter; }
    int flowersCounter() const { return m_flowersCounter; }

private:
    Grid m_grid;
    Size m_tileSize = Size(10, 10);

    std::vector<Tile> m_tiles;
    std::vector<IBaseObject*> m_objects; // to loop over all objects
    std::vector<Reward> m_rewards;

    SnakesPropertyModifier m_snakesPropertyModifier;
    SnakeSpawner m_snakeSpawner;

    int m_coins = START_COINS_NUM;

    int m_snakesCounter = 0;
    int m_flowersCounter = 0;

    // these are temprorary buffers
    std::vector<Index2D> m_oldDirtyIndexesBuffer;
    std::vector<Index2D> m_newDirtyIndexesBuffer;
    std::vector<Index2D> m_eatenFlowerIndexesBuffer;
    //

    std::map<std::size_t, StaticObject*> m_staticObjectsMap; // to easy access staticobjects by map index

    void fillStaticObjects();
    void createGround();
    void createGrasses(int numMin, int numMax);
    void createRocks(int numMin, int numMax);
    void createWoods(int numMin, int numMax);
    void createTrees(int numMin, int numMax);
    void createSnake();

    bool addImageToTile(const Image& image, int index1d);
    bool removeImageFromTile(PixmapLayer layer, int index1d);

    void addStaticObject(StaticObject*, int index1d);
    void removeStaticObject(std::size_t index1d);
    void addSnake(Snake*);
};

} // namespace core

#endif // GRIDMAP_H

