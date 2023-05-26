#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "index2d.h"

#include <string>
#include <vector>

namespace core {

class Image;

class StaticObject
{
public:
    StaticObject(const std::vector<Image>& images);
    virtual ~StaticObject()=default;

    const std::vector<Image>& images() const { return m_images; }
    void setMapTileIndex(std::size_t i);

    std::size_t mapTileIndex() { return m_mapLocation; }
    const std::vector<Index2D>& localOffsets() const { return m_localOffsets; }

    virtual void update(int frameDeltaTimeMs) {}

private:
    std::vector<Image> m_images;
    std::size_t m_mapLocation;
    std::vector<Index2D> m_localOffsets;
};

} // namespace core

#endif // GAMEOBJECT_H
