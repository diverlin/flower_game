#include "gridmap.h"
#include "randutils.h"
#include "stringutils.h"
#include "gameobject.h"
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

    create();
}

GridMap::~GridMap()
{
    for (Snake* snake: m_snakes) {
        delete snake;
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
    createRocks(3,6);
    createWoods(1,1);
    createTrees(1,2);
    createSnake();
}

void GridMap::createGround()
{
    for (int i=0; i<m_grid.size(); ++i) {
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
            const bool rock_variant = getRandomBool();
            std::string imageFilePath = core::stringutils::replace(std::string(":/tiles/rock_%1.png"), "%1", rock_variant?"big":"middle");
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
    Index2D randMapIndex = m_grid.getFreeRandomIndex2D({Index2D(0,1)});
    Image image(":/tiles/snake_segment_texture.png", PixmapLayer::SNAKE_LAYER);
    Snake* snake = new Snake(image, 2, {randMapIndex, randMapIndex+Index2D(0,1)});
    addSnake(snake);
}

void GridMap::createFlower(std::size_t index1d)
{
    int flower_variant = getRandomInt(1, 3);
    std::string imageFilePath = core::stringutils::replace(std::string(":/tiles/flower_%1.png"), "%1", std::to_string(flower_variant));
    Image imageTopLeft(imageFilePath, PixmapLayer::FLOWER_LAYER);
    Flower* flower = new Flower(std::vector<Image>{imageTopLeft});
    addStaticObject(flower, index1d);
}

void GridMap::addImageToTile(const Image& image, int index1d)
{
    if (m_grid.addLayer(index1d, image.layer())) {
        Tile& tile = m_tiles[index1d];
        tile.addImage(image);
    }
}

void GridMap::removeImageFromTile(PixmapLayer layer, int index1d)
{
    if (m_grid.removeLayer(index1d, layer)) {
        Tile& tile = m_tiles[index1d];
        tile.removeImage(layer);
    }
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
    m_staticObjects.push_back(object);
}

void GridMap::addSnake(Snake* snake)
{
    m_snakes.push_back(snake);
    for (const Index2D& index2d: *snake) {
        addImageToTile(snake->image(), m_grid.getIndex1D(index2d));
    }
}

void GridMap::update(int frameDeltaTimeMs)
{
    for (StaticObject* object: m_staticObjects) {
        object->update(frameDeltaTimeMs);
    }

    // TODO: move this into snake::update
    m_msSinceLastSnakesMoveUpdate += int(frameDeltaTimeMs);
    if (m_msSinceLastSnakesMoveUpdate >= SNAKE_MOVE_UPDATE_INTERVAL) {
        for (Snake* snake: m_snakes) {
            Index2D lastTailIndex2d = snake->last();
            Index2D headIndex2d = snake->first();
            Index2D newIndex2d = headIndex2d;
            newIndex2d += Index2D(0, 1);
            snake->push(newIndex2d);

            removeImageFromTile(snake->image().layer(), m_grid.getIndex1D(lastTailIndex2d));
            addImageToTile(snake->image(), m_grid.getIndex1D(newIndex2d));
        }

        m_msSinceLastSnakesMoveUpdate = 0;
    }
}

} // namespace core

