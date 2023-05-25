#ifndef TILE_H
#define TILE_H

#include "index2d.h"
#include "pixmaplayer.h"

#include <string>

namespace core {

class Tile
{
public:
    Tile(const std::string& imageFilePath, PixmapLayer PixmapLayer, const Index2D& indexOffsetFromLeftTopCorner = Index2D(0,0));

    const std::string& imageFilePath() const { return m_imageFilePath; }
    const Index2D& mapLocation() const { return m_mapLocation; }
    PixmapLayer layer() const { return m_PixmapLayer; }

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
    PixmapLayer m_PixmapLayer;
    Index2D m_indexOffsetFromLeftTopCorner;
    Index2D m_mapLocation;
};

} // namespace core

#endif // TILE_H
