#include "gridmap.h"
#include "randutils.h"
#include "stringutils.h"
#include "gameobject.h"

#include <algorithm>
#include <iostream>

GridMap::GridMap(int rows, int columns)
    :
    m_rows(rows),
    m_columns(columns),
    m_array(rows*columns)
{
    for (int i=0; i<rows*columns; ++i) {
        m_randomIndexes.push_back(i);
    }
    randomizeVector(m_randomIndexes);

    std::cout << "m_array.capacity=" << m_array.capacity() << std::endl;
}

GridMap::~GridMap()
{

}

void GridMap::create()
{
    m_tiles.clear();
    createGroundLayer();
    createGrassLayer(20,40);
    createRockLayer(3,6);
    createWoodLayer(1,1);
    createTreeLayer(2,4);
}

void GridMap::createGroundLayer()
{
    for (int i=0; i<m_rows; ++i) {
        for (int j=0; j<m_columns; ++j) {
            Tile tile(":/tiles/ground.png", TileLayer::GROUND_LAYER);
            addTile(tile, i, j);
        }
    }
}

void GridMap::createGrassLayer(int numMin, int numMax)
{
    int num = getRandomInt(numMin, numMax);
    for (int i=0; i<num; ++i) {
        Index2D randMapIndex = getFreeRandomIndex();
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
        Index2D randMapIndex = getFreeRandomIndex();
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
            Index2D randMapIndex = getFreeRandomIndex(object.localOffsets());
            if (randMapIndex.isValid()) {
                addObject(object, randMapIndex);
            } else {
                std::cout << "no free slots for tile wood" << std::endl;
            }
        } else {
            Tile tileTop(":/tiles/wood_vertical_t.png", TileLayer::WOOD_LAYER);
            Tile tileBottom(":/tiles/wood_vertical_b.png", TileLayer::WOOD_LAYER, Index2D(0,1));
            GameObject object(std::vector<Tile>{tileTop, tileBottom});
            Index2D randMapIndex = getFreeRandomIndex(object.localOffsets());
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
        Index2D randMapIndex = getFreeRandomIndex(object.localOffsets());
        if (randMapIndex.isValid()) {
            addObject(object, randMapIndex);
        } else {
            std::cout << "no free slots for tile tree" << std::endl;
        }
    }
}

bool GridMap::hasTile(int i, int j, TileLayer tileLayer)
{
    std::size_t _1d_index = getIndex1D(i, j);
    if (_1d_index < m_array.size()) {
        return static_cast<int>(tileLayer) & m_array[_1d_index];
    } else {
        std::cout << "ERROR:" << "cannot get 1D index from i=" << i << ", j=" << j << std::endl;
        return false;
    }
}

void GridMap::addTile(Tile& tile, const Index2D& mapIndex2D)
{
    addTile(tile, mapIndex2D.i(), mapIndex2D.j());
}

void GridMap::addTile(Tile& tile, int i, int j)
{
    std::size_t _1d_index = getIndex1D(i, j);
    if (_1d_index < m_array.size()) {
        tile.setMapLocation(i, j);
        m_array[_1d_index] |= static_cast<int>(tile.layer());
        m_tiles.push_back(tile);
    } else {
        std::cout << "ERROR:" << "cannot get 1D index from i=" << i << ", j=" << j << std::endl;
    }
}

void GridMap::addObject(GameObject& object, const Index2D& indexMap2D)
{
    addObject(object, indexMap2D.i(), indexMap2D.j());
}

void GridMap::addObject(GameObject& object, int i, int j)
{
    object.setMapLocation(i, j);
    m_objects.push_back(object);
}

void GridMap::removeTile(int i, int j, TileLayer tileLayer)
{
    std::size_t _1d_index = getIndex1D(i, j);
    if (_1d_index < m_array.size()) {
        m_array[_1d_index] ^= static_cast<int>(tileLayer);
    } else {
        std::cout << "ERROR:" << "cannot get 1D index from i=" << i << ", j=" << j << std::endl;
    }
}

bool GridMap::isTilePassble(const Index2D& index2D) const
{
    std::size_t _1d_index = getIndex1D(index2D.i(), index2D.j());
    if (_1d_index < m_array.size()) {
        int value = m_array.at(_1d_index);
        return (value == 0);
    } else {
        return false;
    }
}

std::size_t GridMap::getIndex1D(int i, int j) const
{
    return static_cast<std::size_t>(i * m_columns + j);
}

std::size_t GridMap::getIndex1D(const Index2D& index2d) const
{
    return static_cast<std::size_t>(index2d.i() * m_columns + index2d.j());
}

Index2D GridMap::getIndex2D(size_t index1D) const
{
    return Index2D(index1D / m_rows, index1D % m_rows);
}

Index2D GridMap::getFreeRandomIndex(const std::vector<Index2D>& localOffsets) const
{
    for (int randIndex1D: m_randomIndexes) {
        Index2D topLeftIndex = getIndex2D(randIndex1D);
        if (isTilePassble(topLeftIndex)) {
            if (localOffsets.empty()) {
                return topLeftIndex;
            } else {
                bool at_least_one_offset_slot_busy = false;
                for (const Index2D& localOffset: localOffsets) {
                    Index2D nextIndex(localOffset);
                    nextIndex += topLeftIndex;
                    if (!isTilePassble(nextIndex)) {
                        at_least_one_offset_slot_busy = true;
                    }
                }

                if (!at_least_one_offset_slot_busy) {
                    return topLeftIndex;
                }
            }
        }
    }

    return Index2D(); // return ivalid index
}
