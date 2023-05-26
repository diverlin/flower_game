#include "gridmap.h"
#include "randutils.h"
#include "stringutils.h"
#include "staticobject.h"
#include "flower.h"
#include "snake.h"
#include "image.h"
#include "findastar.h"

#include <algorithm>
#include <iostream>

namespace core {

GridMap::GridMap(int rows, int columns, const Size& size)
    :
    m_grid(rows, columns)
    , m_snakeObsticlesMap(rows*columns)
{
    m_tileSize = Size(size.width()/rows, size.height()/columns);
    for (std::size_t i=0; i<m_grid.size(); ++i) {
        m_tiles.emplace_back(Tile(i));
    }

    create();
}

GridMap::~GridMap()
{
    for (IBaseObject* object: m_objects) {
        delete object;
    }
}

vec2 GridMap::worldCoordFromIndex(std::size_t index1d) const
{
    Index2D index2d = m_grid.getIndex2D(index1d);
    return worldCoordFromIndex(index2d);
}

vec2 GridMap::worldCoordFromIndex(const Index2D& index2d) const
{
    return vec2(index2d.i()*m_tileSize.width(), index2d.j()*m_tileSize.height());
}

int GridMap::indexFromWorldCoord(const vec2& worldCoord) const
{
    Index2D index2d(static_cast<int>(worldCoord.x()/m_tileSize.width()), static_cast<int>(worldCoord.y()/m_tileSize.height()));
    if (index2d.isValid()) {
        return m_grid.getIndex1D(index2d);
    }
    return -1;
}

void GridMap::create()
{
    createGround();
    createGrasses(10,20);
//    createRocks(3,6);
//    createWoods(1,1);
//    createTrees(1,2);
    createSnake();
}

void GridMap::createGround()
{
    for (std::size_t i=0; i<m_grid.size(); ++i) {
        Image image(":/tiles/ground.png", PixmapLayer::GROUND_LAYER);
        addImageToTile(image, i);
    }
}

void GridMap::createGrasses(int numMin, int numMax)
{
    int num = getRandomInt(numMin, numMax);
    for (int i=0; i<num; ++i) {
        int randMapIndex = m_grid.getFreeRandomIndex();
        if (randMapIndex != -1) {
            const int grass_variant = getRandomInt(1,2);
            std::string imageFilePath = core::stringutils::replace(std::string(":/tiles/grass%1.png"), "%1", std::to_string(grass_variant));
            Image image(imageFilePath, PixmapLayer::GRASS_LAYER);
            addImageToTile(image, randMapIndex);
        } else {
            std::cout << "no free slots for tile grass" << std::endl;
            break;
        }
    }
}

void GridMap::createRocks(int numMin, int numMax)
{
    int num = getRandomInt(numMin, numMax);
    for (int i=0; i<num; ++i) {
        int randMapIndex = m_grid.getFreeRandomIndex();
        if (randMapIndex != -1) {
            const bool rockVariant = getRandomBool();
            std::string imageFilePath = core::stringutils::replace(std::string(":/tiles/rock_%1.png"), "%1", rockVariant?"big":"middle");
            Image image(imageFilePath, PixmapLayer::ROCK_LAYER);
            addImageToTile(image, randMapIndex);
        } else {
            std::cout << "no free slots for tile rock" << std::endl;
            break;
        }
    }
}

void GridMap::createWoods(int numMin, int numMax)
{
    int num = getRandomInt(numMin, numMax);
    for (int i=0; i<num; ++i) {
        const bool wood_variant = getRandomBool();
        if (wood_variant) {
            Image imageLeft(":/tiles/wood_horizontal_l.png", PixmapLayer::WOOD_LAYER);
            Image imageRight(":/tiles/wood_horizontal_r.png", PixmapLayer::WOOD_LAYER, Index2D(1,0));
            StaticObject* object = new StaticObject(std::vector<Image>{imageLeft, imageRight});
            int randMapIndex = m_grid.getFreeRandomIndex(object->localOffsets());
            if (randMapIndex != -1) {
                addStaticObject(object, randMapIndex);
            } else {
                std::cout << "no free slots for tile wood" << std::endl;
            }
        } else {
            Image imageTop(":/tiles/wood_vertical_t.png", PixmapLayer::WOOD_LAYER);
            Image imageBottom(":/tiles/wood_vertical_b.png", PixmapLayer::WOOD_LAYER, Index2D(0,1));
            StaticObject* object = new StaticObject(std::vector<Image>{imageTop, imageBottom});
            int randMapIndex = m_grid.getFreeRandomIndex(object->localOffsets());
            if (randMapIndex != -1) {
                addStaticObject(object, randMapIndex);
            } else {
                std::cout << "no free slots for tile wood" << std::endl;
            }
        }
    }
}

void GridMap::createTrees(int numMin, int numMax)
{
    int num = getRandomInt(numMin, numMax);
    for (int i=0; i<num; ++i) {
        Image imageTopLeft(":/tiles/tree_0_tl.png", PixmapLayer::TREE_LAYER);
        Image imageTopRight(":/tiles/tree_0_tr.png", PixmapLayer::TREE_LAYER, Index2D(1,0));
        Image imageBottomLeft(":/tiles/tree_0_bl.png", PixmapLayer::TREE_LAYER, Index2D(0,1));
        Image imageBottomRight(":/tiles/tree_0_br.png", PixmapLayer::TREE_LAYER, Index2D(1,1));
        StaticObject* object = new StaticObject(std::vector<Image>{imageTopLeft, imageTopRight, imageBottomLeft, imageBottomRight});
        int randMapIndex = m_grid.getFreeRandomIndex(object->localOffsets());
        if (randMapIndex != -1) {
            addStaticObject(object, randMapIndex);
        } else {
            std::cout << "no free slots for tile tree" << std::endl;
        }
    }
}

void GridMap::createSnake()
{
//    Index2D randMapIndex = m_grid.getFreeRandomIndex2D({Index2D(0,1)});
    Index2D randMapIndex(1,1);
    const int snakeVariant = getRandomInt(1,2);
    std::string imageFilePath = core::stringutils::replace(std::string(":/tiles/snake_segment_%1.png"), "%1", std::to_string(snakeVariant));

    Image image(imageFilePath, PixmapLayer::SNAKE_LAYER);
    Snake* snake = new Snake(image, 2, {randMapIndex+Index2D(0,-1), randMapIndex});
    addSnake(snake);
}

void GridMap::tapOnBusyTile(std::size_t index1d)
{
    Index2D index2d = m_grid.getIndex2D(index1d);
    for (IBaseObject* object: m_objects) {
        if (typeid(*object) == typeid(Snake)) {
            Snake* snake = static_cast<Snake*>(object);
            if (snake) {
                if (snake->contain(index2d)) {
                    std::cout << "gotcha snake=" << snake->id() << " on index=" << index1d << std::endl;
                    snake->decreaseLength();
                    return;
                }
            }
        }
    }
}

void GridMap::createFlower(std::size_t index1d)
{
    if (m_grid.hasLayer(index1d, PixmapLayer::FLOWER_LAYER)) {
        return;
    }
    if (m_coins >= FLOWER_COST) {
        m_coins -= FLOWER_COST;
        int flowerVariant = getRandomInt(1, 3);
        std::string imageFilePath = core::stringutils::replace(std::string(":/tiles/flower_%1.png"), "%1", std::to_string(flowerVariant));
        Image imageTopLeft(imageFilePath, PixmapLayer::FLOWER_LAYER);
        static std::map<int, std::string> colorMap = {{1,"#8A6000"}, {2,"#0042F2"}, {3,"#AF2D00"}};
        Flower* flower = new Flower(std::vector<Image>{imageTopLeft}, colorMap[flowerVariant]);
        addStaticObject(flower, index1d);
    }
}

bool GridMap::addImageToTile(const Image& image, int index1d)
{
    if (m_grid.addLayer(index1d, image.layer())) {
        Tile& tile = m_tiles[index1d];
        return tile.addImage(image);
    }
    return false;
}

bool  GridMap::removeImageFromTile(PixmapLayer layer, int index1d)
{
    if (m_grid.removeLayer(index1d, layer)) {
        Tile& tile = m_tiles[index1d];
        return tile.removeImage(layer);
    }
    return false;
}

void GridMap::addStaticObject(StaticObject* object, int index1d)
{
    object->setMapTileIndex(index1d);
    for (const Image& image: object->images()) {
        Index2D index2d = m_grid.getIndex2D(index1d);
        index2d += image.indexOffsetFromLeftTopCorner();
        int index1d = m_grid.getIndex1D(index2d);
        if (m_grid.addLayer(index1d, image.layer())) {
            Tile& tile = m_tiles[index1d];
            tile.addImage(image);
        }
    }
    m_objects.push_back(object);
}

void GridMap::addSnake(Snake* snake)
{
    m_objects.push_back(snake);
}

void GridMap::takeRewards(std::vector<Reward>& rewards)
{
    rewards.clear();
    for (const Reward& reward: m_rewards) {
        m_coins += reward.coins;
    }
    std::swap(rewards, m_rewards);
}

void GridMap::update(int frameDeltaTimeMs)
{
    m_grid.updateSnakeObsticlesRawMap(m_snakeObsticlesMap);
    m_grid.randomizeIndexes();

    for (IBaseObject* object: m_objects) {
        object->update(frameDeltaTimeMs);

        if (typeid(*object) == typeid(Flower)) {
            Flower* flower = static_cast<Flower*>(object);
            if (flower) {
                int coins = flower->takeCoins();
                if (coins > 0) {
                    m_rewards.emplace_back(Reward{flower->mapTileIndex(), coins, flower->colorCode()});
                }
            }
        } else if (typeid(*object) == typeid(Snake)) {
            Snake* snake = static_cast<Snake*>(object);
            if (snake) {
                if (snake->hasDirtyIndexes()) {
                    snake->takeDirtyIndexes(m_oldDirtyIndexes, m_newDirtyIndexes);
                    for (Index2D& index2d: m_oldDirtyIndexes) {
                        std::size_t index1d = m_grid.getIndex1D(index2d);
                        if (!removeImageFromTile(PixmapLayer::SNAKE_LAYER, index1d)) {
                            std::cout<<"ERROR: to remove" << index2d << std::endl;
                        }
                    }
                    for (Index2D& index2d: m_newDirtyIndexes) {
                        std::size_t index1d = m_grid.getIndex1D(index2d);
                        if (!addImageToTile(snake->image(), index1d)) {
                            std::cout<<"ERROR: to add" << index2d << std::endl;
                        }
                    }
                }

                if (!snake->hasPath()) {
                    m_pathBuffer.clear();

                    Index2D fromIndex2D = snake->head();
                    Index2D targetIndex2D = m_grid.getFreeRandomIndex2D();

                    int result = findPathAStar(fromIndex2D.i(), fromIndex2D.j(),
                                               targetIndex2D.i(), targetIndex2D.j(),
                                               m_snakeObsticlesMap.data(),
                                               m_grid.columns(), m_grid.rows(),
                                               m_pathBuffer);
                    std::cout << "found path for snake path size=" << m_pathBuffer.size() << std::endl;

                    std::vector<Index2D> path;
                    for (int element: m_pathBuffer) {
                        path.push_back(m_grid.getIndex2D(element));
                    }
                    std::reverse(path.begin(), path.end());
                    snake->setPath(path);
                }
            }
        }
    }
}

} // namespace core

