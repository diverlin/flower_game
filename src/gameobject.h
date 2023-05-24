#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "index2d.h"
#include "tilelayer.h"

#include <string>
#include <vector>

class Tile;

class GameObject
{
public:
    GameObject(const std::vector<Tile>& tiles);

    void setMapLocation(int i, int j);

    const Index2D& mapLocation() { return m_mapLocation; }

private:
    std::vector<Tile> m_tiles;
    Index2D m_mapLocation;
};

#endif // GAMEOBJECT_H
