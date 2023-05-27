#include "gridmap.h"
#include "randutils.h"
#include "stringutils.h"
#include "staticobject.h"
#include "flower.h"
#include "snake.h"
#include "image.h"

#include <algorithm>
#include <iostream>

namespace core {

GridMap::GridMap(int rows, int columns, const Size& size)
    :
    m_grid(rows, columns)
{
    m_tileSize = Size(size.width()/rows, size.height()/columns);
    for (std::size_t i=0; i<m_grid.size(); ++i) {
        m_tiles.emplace_back(Tile(i));
    }
}

GridMap::~GridMap()
{
    reset();
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

void GridMap::reset()
{
    m_snakesPropertyModifier.reset();
    m_snakeSpawner.reset();

    m_coins = START_COINS_NUM;

    m_snakesCounter = 0;
    m_flowersCounter = 0;

    m_oldDirtyIndexesBuffer.clear();
    m_newDirtyIndexesBuffer.clear();
    m_eatenFlowerIndexesBuffer.clear();

    for (std::size_t i=0; i<m_grid.size(); ++i) {
        Tile& tile = m_tiles.at(i);
        tile.clear();
    }

    m_rewards.clear();

    m_staticObjectsMap.clear();

    for (IBaseObject* object: m_objects) {
        delete object;
    }
    m_objects.clear();

    m_grid.reset();
}

void GridMap::onStart()
{
    fillStaticObjects();
}

void GridMap::fillStaticObjects()
{
    createGround();
    createGrasses(10,20);
#ifdef Q_OS_ANDROID
    createRocks(6,10);
    createWoods(1,1);
    createTrees(2,4);
#else
    createRocks(3,6);
    createWoods(1,1);
    createTrees(1,2);
#endif
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
        Image imageTopLeft(":/tiles/tree_0_tl.png", PixmapLayer::TREE_TOP_LAYER);
        Image imageTopRight(":/tiles/tree_0_tr.png", PixmapLayer::TREE_TOP_LAYER, Index2D(1,0));
        Image imageBottomLeft(":/tiles/tree_0_bl.png", PixmapLayer::TREE_BOTTOM_LAYER, Index2D(0,1));
        Image imageBottomRight(":/tiles/tree_0_br.png", PixmapLayer::TREE_BOTTOM_LAYER, Index2D(1,1));
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
    Index2D randMapIndex = m_grid.getFreeRandomIndex2D({Index2D(0,1)});
    const int snakeVariant = getRandomInt(1,2);
    std::string imageFilePath = core::stringutils::replace(std::string(":/tiles/snake_segment_%1.png"), "%1", std::to_string(snakeVariant));

    Image image(imageFilePath, PixmapLayer::SNAKE_LAYER);
    Snake* snake = new Snake(&m_grid, image, 2, {randMapIndex+Index2D(0,-1), randMapIndex});
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
#ifdef ENABLE_SNAKES_KILL
                    snake->hit();
#else
                    if (snake->maxLength() > 2) { snake->hit(); }
#endif
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

        Image imageTopLeft0(std::string(":/tiles/seed.png"), PixmapLayer::FLOWER_LAYER);
        static std::map<int, std::string> colorMap = {{1,"#8A6000"}, {2,"#0042F2"}, {3,"#AF2D00"}};
        Flower* flower = new Flower(std::vector<Image>{imageTopLeft0}, colorMap[flowerVariant]);

        switch(flowerVariant) {
        case 1:
            flower->addAnimationFrame(std::vector<Image>{Image(":/tiles/flower_1_a0.png", PixmapLayer::FLOWER_LAYER)}, 100);
            flower->addAnimationFrame(std::vector<Image>{Image(":/tiles/flower_1_a1.png", PixmapLayer::FLOWER_LAYER)}, 100);
            flower->addAnimationFrame(std::vector<Image>{Image(":/tiles/flower_1_a2.png", PixmapLayer::FLOWER_LAYER)}, 100);
            flower->addAnimationFrame(std::vector<Image>{Image(":/tiles/flower_1_a3.png", PixmapLayer::FLOWER_LAYER)}, 100);
            break;
        case 2:
            flower->addAnimationFrame(std::vector<Image>{Image(":/tiles/flower_2_a0.png", PixmapLayer::FLOWER_LAYER)}, 100);
            flower->addAnimationFrame(std::vector<Image>{Image(":/tiles/flower_2_a1.png", PixmapLayer::FLOWER_LAYER)}, 100);
            flower->addAnimationFrame(std::vector<Image>{Image(":/tiles/flower_2_a2.png", PixmapLayer::FLOWER_LAYER)}, 100);
            flower->addAnimationFrame(std::vector<Image>{Image(":/tiles/flower_2_a3.png", PixmapLayer::FLOWER_LAYER)}, 100);
            break;
        case 3:
            flower->addAnimationFrame(std::vector<Image>{Image(":/tiles/flower_3_a0.png", PixmapLayer::FLOWER_LAYER)}, 100);
            flower->addAnimationFrame(std::vector<Image>{Image(":/tiles/flower_3_a1.png", PixmapLayer::FLOWER_LAYER)}, 100);
            flower->addAnimationFrame(std::vector<Image>{Image(":/tiles/flower_3_a2.png", PixmapLayer::FLOWER_LAYER)}, 100);
            flower->addAnimationFrame(std::vector<Image>{Image(":/tiles/flower_3_a3.png", PixmapLayer::FLOWER_LAYER)}, 100);
            break;
        }

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
    m_staticObjectsMap[index1d] = object;
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

void GridMap::updateImagesForStaticObject(StaticObject* object)
{
    std::size_t topLeftIndex1d = object->mapTileIndex();
    Index2D topLeftIndex2d = m_grid.getIndex2D(topLeftIndex1d);

    for (const Image& image: object->images()) {
        Index2D imageIndex2d = topLeftIndex2d;
        imageIndex2d += image.indexOffsetFromLeftTopCorner();
        int index1d = m_grid.getIndex1D(imageIndex2d);
        Tile& tile = m_tiles[index1d];
        tile.addImage(image);
    }

    object->acceptNewImages();
}

void GridMap::removeStaticObject(std::size_t index1d)
{
    auto it_map = m_staticObjectsMap.find(index1d);
    if (it_map != m_staticObjectsMap.end()) {
        StaticObject* object = it_map->second;
        if (typeid(*object) == typeid(Flower)) {
            m_staticObjectsMap.erase(it_map);
            for (const Image& image: object->images()) {
                Index2D _index2d = m_grid.getIndex2D(index1d);
                _index2d += image.indexOffsetFromLeftTopCorner();
                int _index1d = m_grid.getIndex1D(_index2d);
                if (m_grid.removeLayer(_index1d, image.layer())) {
                    Tile& tile = m_tiles[_index1d];
                    tile.removeImage(PixmapLayer::FLOWER_LAYER);
                }
            }

            for (auto it_vec = m_objects.begin(); it_vec != m_objects.end(); ) {
                if (*it_vec == object) {
                    it_vec = m_objects.erase(it_vec);
                    delete object;
                    break;
                } else {
                    ++it_vec;
                }
            }
        }
    }
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
    m_snakesCounter = 0;
    m_flowersCounter = 0;

    bool atLeastOneFlowerWasEaten = false;

    m_eatenFlowerIndexesBuffer.clear();

    std::vector<IBaseObject*>::iterator it = m_objects.begin();
    for ( ; it != m_objects.end(); ) {
        IBaseObject* object = *it;
        object->update(frameDeltaTimeMs);

        if (typeid(*object) == typeid(Flower)) {
            Flower* flower = static_cast<Flower*>(object);
            if (flower) {
                m_flowersCounter++;
                int coins = flower->takeCoins();
                if (coins > 0) {
                    m_rewards.emplace_back(Reward{flower->mapTileIndex(), coins, flower->colorCode()});
                }
            }
        } else if (typeid(*object) == typeid(Snake)) {
            Snake* snake = static_cast<Snake*>(object);
            if (snake) {
                m_snakesCounter++;
                snake->setMoveSpeedMultiplier(m_snakesPropertyModifier.moveSpeedMultiplier());
                snake->setMaxLengthMultiplier(m_snakesPropertyModifier.maxLengthMultiplier());

                if (snake->hasDirtyIndexes()) {
                    snake->takeDirtyMoveIndexes(m_oldDirtyIndexesBuffer, m_newDirtyIndexesBuffer);
                    for (Index2D& index2d: m_oldDirtyIndexesBuffer) {
                        std::size_t index1d = m_grid.getIndex1D(index2d);
                        if (!removeImageFromTile(PixmapLayer::SNAKE_LAYER, index1d)) {
                            std::cout<<"ERROR: to remove" << index2d << std::endl;
                        }
                    }
                    for (Index2D& index2d: m_newDirtyIndexesBuffer) {
                        std::size_t index1d = m_grid.getIndex1D(index2d);
                        if (!addImageToTile(snake->image(), index1d)) {
                            std::cout<<"ERROR: to add" << index2d << std::endl;
                        }
                    }
                }

                if (snake->hasEatenFlowers()) {
                    snake->takeEatenFlowerIndexes(m_eatenFlowerIndexesBuffer);
                    atLeastOneFlowerWasEaten = true;
                }
            }
        }
        if (!object->isAlive() && typeid(*object) == typeid(Snake)) { // currently we remove dynamic objects as snakes in that way, for static objects we remove them differently
            it = m_objects.erase(it);
            delete object;
        } else {
            ++it;
        }
    }

    // update animations for staticobject
    for (auto it: m_staticObjectsMap) {
        StaticObject* object = it.second;
        if (object->isImagesChanged()) {
            updateImagesForStaticObject(object);
        }
    }
    //


    // remove dead flowers
    for (const Index2D& index2d: m_eatenFlowerIndexesBuffer) {
        removeStaticObject(m_grid.getIndex1D(index2d));
    }

    m_snakeSpawner.update(frameDeltaTimeMs, m_flowersCounter);
    if (m_snakeSpawner.isQueued()) {
        std::cout << "spawn!!!" << std::endl;
        createSnake();
        m_snakeSpawner.releaseQueued();
    }
    m_snakesPropertyModifier.update(frameDeltaTimeMs, m_flowersCounter, atLeastOneFlowerWasEaten);
}

} // namespace core

