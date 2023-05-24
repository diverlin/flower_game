#include "gridmap.h"
#include "randutils.h"
#include "stringutils.h"

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
    createGrassLayer(4,8);
    createRockLayer(3,6);
    createWoodLayer(1,2);
    createTreeLayer(1,2);
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
        Index2D randIndex = getFreeRandomIndex();
        if (randIndex.isValid()) {
            const int grass_variant = getRandomInt(1,2);
            std::string imageFilePath = utils::replace(std::string(":/tiles/grass%1.png"), "%1", std::to_string(grass_variant));
            Tile ground_tile(imageFilePath, TileLayer::GRASS_LAYER);
            addTile(tile, i, j);
        } else {
            std::cout << "no free slots for tile" << std::endl;
            break;
        }
    }
}

void GridMap::createRockLayer(int numMin, int numMax)
{
    int num = getRandomInt(numMin, numMax);
    for (int i=0; i<num; ++i) {

    }
}

void GridMap::createWoodLayer(int numMin, int numMax)
{
    int num = getRandomInt(numMin, numMax);
    for (int i=0; i<num; ++i) {

    }
}

void GridMap::createTreeLayer(int numMin, int numMax)
{
    int num = getRandomInt(numMin, numMax);
    for (int i=0; i<num; ++i) {

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

void GridMap::addTile(const Tile& tile, int i, int j)
{
    tile.setMapLocation(i, j);
    std::size_t _1d_index = getIndex1D(i, j);
    if (_1d_index < m_array.size()) {
        m_array[_1d_index] |= static_cast<int>(tile.layer());
    } else {
        std::cout << "ERROR:" << "cannot get 1D index from i=" << i << ", j=" << j << std::endl;
    }
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

Index2D GridMap::getFreeRandomIndex(const Index2D& offsetFromTopLeftCorner) const
{
    for (int randIndex1D: m_randomIndexes) {
        Index2D topLeft = getIndex2D(randIndex1D);
        if (isTilePassble(topLeft)) {
            if (offsetFromTopLeftCorner.isNull()) {
                return topLeft;
            } else {
                bool at_least_one_neigbor_tile_busy = false;
                for (int i=0; i<=offsetFromTopLeftCorner.i(); ++i) {
                    for (int j=0; j<=offsetFromTopLeftCorner.j(); ++j) {
                        Index2D nextIndex = Index2D(i, j);
                        nextIndex += topLeft;
                        if (!isTilePassble(topLeft)) {
                            at_least_one_neigbor_tile_busy = true;
                        }
                    }

                }
                if (!at_least_one_neigbor_tile_busy) {
                    return topLeft;
                }
            }
        }
    }

    return Index2D(); // return ivalid index
}
