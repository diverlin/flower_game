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
    const int FLOWER_COST = 50;
    const int START_COINS_NUM = 150;
    const int SNAKE_OCCUR_INTERVAL_MS = 5000;
    const int SNAKE_SPEED_MULTIPLIER_EXPIRATION_MS = 5000;

    GridMap(int rows, int columns, const Size& size);
    ~GridMap();

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

private:
    Grid m_grid;
    Size m_tileSize = Size(10, 10);

    std::vector<Tile> m_tiles;
    std::vector<IBaseObject*> m_objects;
    std::vector<Reward> m_rewards;

    int m_msSinceLastSnakesOccur = 0;
    int m_snakeOccurIntervalMs = 0;
    int m_moveSpeedRatioDurationMs = -1;
    float m_snakeMoveSpeedMultiplier = 1.0f;
    float m_snakeMaxLengthMultiplier = 1.0f;

    int m_coins = START_COINS_NUM;

    std::vector<Index2D> m_oldDirtyIndexesBuffer;
    std::vector<Index2D> m_newDirtyIndexesBuffer;
    std::vector<Index2D> m_eatenFlowerIndexesBuffer;

    std::map<std::size_t, StaticObject*> m_staticObjectsMap; // to get fast access to flowers

    void create();

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

