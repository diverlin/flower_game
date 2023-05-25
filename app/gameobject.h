#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "index2d.h"

#include <string>
#include <vector>

namespace core {

class Tile;

class StaticObject
{
public:
    StaticObject(const std::vector<Tile>& tiles);

    const std::vector<Tile>& tiles() const { return m_tiles; }
    void setMapLocation(int i, int j);

    const Index2D& mapLocation() { return m_mapLocation; }
    const std::vector<Index2D>& localOffsets() const { return m_localOffsets; }

private:
    std::vector<Tile> m_tiles;
    Index2D m_mapLocation;
    std::vector<Index2D> m_localOffsets;
};

} // namespace core

#endif // GAMEOBJECT_H
