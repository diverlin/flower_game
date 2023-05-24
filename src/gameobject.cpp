#include "gameobject.h"

#include "tiledescriptor.h"

GameObject::GameObject(const std::vector<TileDescriptor>& tiles, ObjectLayer layer)
    :
    m_tiles(tiles)
    , m_layer(layer)
{
}

GameObject::GameObject(const std::string& imageFilePath, ObjectLayer layer)
:
    m_layer(layer)
{
    m_tiles.emplace_back(TileDescriptor(imageFilePath));
}

void GameObject::setMapLocation(int i, int j)
{
    if (m_mapLocation.isMach(i, j)) {
        return;
    }
    m_mapLocation.set(i, j);
    for (TileDescriptor& tile: m_tiles) {
        tile.updateMapLocation(m_mapLocation);
    }
}
