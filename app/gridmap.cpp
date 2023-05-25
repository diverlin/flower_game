#include "gridmap.h"
#include "randutils.h"
#include "stringutils.h"
#include "gameobject.h"

#include <algorithm>
#include <iostream>


GridMap::GridMap(int rows, int columns)
    :
    m_grid(rows, columns)
{

}

GridMap::~GridMap()
{

}

void GridMap::create()
{
    m_tiles.clear();
    createGroundLayer();
    createGrassLayer(10,20);
    createRockLayer(3,6);
    createWoodLayer(1,1);
    createTreeLayer(1,2);
}

void GridMap::createGroundLayer()
{
    for (int i=0; i<m_grid.rows(); ++i) {
        for (int j=0; j<m_grid.columns(); ++j) {
            Tile tile(":/tiles/ground.png", TileLayer::GROUND_LAYER);
            addTile(tile, i, j);
        }
    }
}

void GridMap::createGrassLayer(int numMin, int numMax)
{
    int num = getRandomInt(numMin, numMax);
    for (int i=0; i<num; ++i) {
        Index2D randMapIndex = m_grid.getFreeRandomIndex();
        if (randMapIndex.isValid()) {
            const int grass_variant = getRandomInt(1,2);
            std::string imageFilePath = utils::replace(std::string(":/tiles/grass%1.png"), "%1", std::to_string(grass_variant));
            Tile tile(imageFilePath, TileLayer::GRASS_LAYER);
            addTile(tile, randMapIndex);
        } else {
            std::cout << "no free slots for tile grass" << std::endl;
            break;
        }
    }
}

void GridMap::createRockLayer(int numMin, int numMax)
{
    int num = getRandomInt(numMin, numMax);
    for (int i=0; i<num; ++i) {
        Index2D randMapIndex = m_grid.getFreeRandomIndex();
        if (randMapIndex.isValid()) {
            const bool rock_variant = getRandomBool();
            std::string imageFilePath = utils::replace(std::string(":/tiles/rock_%1.png"), "%1", rock_variant?"big":"middle");
            Tile tile(imageFilePath, TileLayer::ROCK_LAYER);
            addTile(tile, randMapIndex);
        } else {
            std::cout << "no free slots for tile rock" << std::endl;
            break;
        }
    }
}

void GridMap::createWoodLayer(int numMin, int numMax)
{
    int num = getRandomInt(numMin, numMax);
    for (int i=0; i<num; ++i) {
        const bool wood_variant = getRandomBool();
        if (wood_variant) {
            Tile tileLeft(":/tiles/wood_horizontal_l.png", TileLayer::WOOD_LAYER);
            Tile tileRight(":/tiles/wood_horizontal_r.png", TileLayer::WOOD_LAYER, Index2D(1,0));
            GameObject object(std::vector<Tile>{tileLeft, tileRight});
            Index2D randMapIndex = m_grid.getFreeRandomIndex(object.localOffsets());
            if (randMapIndex.isValid()) {
                addObject(object, randMapIndex);
            } else {
                std::cout << "no free slots for tile wood" << std::endl;
            }
        } else {
            Tile tileTop(":/tiles/wood_vertical_t.png", TileLayer::WOOD_LAYER);
            Tile tileBottom(":/tiles/wood_vertical_b.png", TileLayer::WOOD_LAYER, Index2D(0,1));
            GameObject object(std::vector<Tile>{tileTop, tileBottom});
            Index2D randMapIndex = m_grid.getFreeRandomIndex(object.localOffsets());
            if (randMapIndex.isValid()) {
                addObject(object, randMapIndex);
            } else {
                std::cout << "no free slots for tile wood" << std::endl;
            }
        }
    }
}

void GridMap::createTreeLayer(int numMin, int numMax)
{
    int num = getRandomInt(numMin, numMax);
    for (int i=0; i<num; ++i) {
        Tile tileTopLeft(":/tiles/tree_0_tl.png", TileLayer::TREE_LAYER);
        Tile tileTopRight(":/tiles/tree_0_tr.png", TileLayer::TREE_LAYER, Index2D(1,0));
        Tile tileBottomLeft(":/tiles/tree_0_bl.png", TileLayer::TREE_LAYER, Index2D(0,1));
        Tile tileBottomRight(":/tiles/tree_0_br.png", TileLayer::TREE_LAYER, Index2D(1,1));
        GameObject object(std::vector<Tile>{tileTopLeft, tileTopRight, tileBottomLeft, tileBottomRight});
        Index2D randMapIndex = m_grid.getFreeRandomIndex(object.localOffsets());
        if (randMapIndex.isValid()) {
            addObject(object, randMapIndex);
        } else {
            std::cout << "no free slots for tile tree" << std::endl;
        }
    }
}

void GridMap::addTile(Tile& tile, const Index2D& mapIndex2D)
{
    addTile(tile, mapIndex2D.i(), mapIndex2D.j());
}

void GridMap::addTile(Tile& tile, int i, int j)
{
    if (m_grid.addLayer(i, j, tile.layer())) {
        tile.setMapLocation(i, j);
        m_tiles.push_back(tile);
    }
}

void GridMap::addObject(GameObject& object, const Index2D& indexMap2D)
{
    addObject(object, indexMap2D.i(), indexMap2D.j());
}

void GridMap::addObject(GameObject& object, int i, int j)
{
    object.setMapLocation(i, j);
    for (const Tile& tile: object.tiles()) {
        m_grid.addLayer(tile.mapLocation(), tile.layer());
    }
    m_objects.push_back(object);
}




