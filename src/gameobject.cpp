#include "gameobject.h"

#include "tiledescriptor.h"

GameObject::GameObject(const std::vector<TileDescriptor>& tiles, ObjectLayer layer)
    :
    m_tiles(tiles)
    , m_layer(layer)
{
    m_occupiedIndexes.resize(tiles.size());
}

GameObject::GameObject(const std::string& imageFilePath, ObjectLayer layer)
:
    m_layer(layer)
{
    m_tiles.emplace_back(TileDescriptor(imageFilePath));
    m_occupiedIndexes.resize(1);
}

void GameObject::setMapLocation(int i, int j)
{
    if (m_mapLocation.isMach(i, j)) {
        return;
    }
    m_occupiedIndexes.clear();
    m_mapLocation.set(i, j);
    for (const TileDescriptor& tile: m_tiles) {
        Index2D location(tile.indexOffsetFromLeftTopCorner());
        location += m_mapLocation;
        m_occupiedIndexes.emplace_back(location);
    }
}
