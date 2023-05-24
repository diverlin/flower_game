#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "index2d.h"
#include "objectlayer.h"

#include <string>
#include <vector>

class TileDescriptor;

class GameObject
{
public:
    GameObject(const std::vector<TileDescriptor>& tiles, ObjectLayer layer);
    GameObject(const std::string& imageFilePath, ObjectLayer layer);

    void setMapLocation(int i, int j);

    const Index2D& mapLocation() { return m_mapLocation; }

    ObjectLayer layer() const { return m_layer; }

private:
    std::vector<TileDescriptor> m_tiles;
    Index2D m_mapLocation;
    ObjectLayer m_layer;

    std::vector<Index2D> m_occupiedIndexes;
};

#endif // GAMEOBJECT_H
