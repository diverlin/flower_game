#ifndef TILE_H
#define TILE_H

#include "index2d.h"
#include "tilelayer.h"

#include <string>

class Tile
{
public:
    Tile(const std::string& imageFilePath, TileLayer tileLayer, const Index2D& indexOffsetFromLeftTopCorner = Index2D(0,0));

    const std::string& imageFilePath() const { return m_imageFilePath; }
    const Index2D& mapLocation() const { return m_mapLocation; }
    TileLayer layer() const { return m_tileLayer; }

    const Index2D& indexOffsetFromLeftTopCorner() const { return m_indexOffsetFromLeftTopCorner; }
    void setMapLocation(int i, int j) {
        m_mapLocation.set(i, j);
        m_mapLocation += m_indexOffsetFromLeftTopCorner;
    }
    void updateMapLocation(const Index2D& rootMapLocation) {
        m_mapLocation.set(rootMapLocation.i(), rootMapLocation.j());
        m_mapLocation += m_indexOffsetFromLeftTopCorner;
    }

private:
    std::string m_imageFilePath;
    TileLayer m_tileLayer;
    Index2D m_indexOffsetFromLeftTopCorner;
    Index2D m_mapLocation;
};

#endif // TILE_H
