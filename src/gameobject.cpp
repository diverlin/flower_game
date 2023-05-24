#include "gameobject.h"

#include "tile.h"

GameObject::GameObject(const std::vector<Tile>& tiles)
    :
    m_tiles(tiles)
{
}

void GameObject::setMapLocation(int i, int j)
{
    if (m_mapLocation.isMach(i, j)) {
        return;
    }
    m_mapLocation.set(i, j);
    for (Tile& tile: m_tiles) {
        tile.updateMapLocation(m_mapLocation);
    }
}
