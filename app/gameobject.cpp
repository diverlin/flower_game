#include "gameobject.h"

#include "tile.h"

StaticObject::StaticObject(const std::vector<Tile>& tiles)
    :
    m_tiles(tiles)
{
}

void StaticObject::setMapLocation(int i, int j)
{
    if (m_mapLocation.isMach(i, j)) {
        return;
    }
    m_mapLocation.set(i, j);
    for (Tile& tile: m_tiles) {
        if (!tile.indexOffsetFromLeftTopCorner().isNull()) {
            m_localOffsets.push_back(tile.indexOffsetFromLeftTopCorner());
        }
        tile.updateMapLocation(m_mapLocation);
    }
}
