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

    const std::vector<Image>& images() const { return m_images; }
    void setMapLocation(int i);

    int mapLocation() { return m_mapLocation; }
    const std::vector<Index2D>& localOffsets() const { return m_localOffsets; }

private:
    std::vector<Image> m_images;
    int m_mapLocation;
    std::vector<Index2D> m_localOffsets;
};

} // namespace core

#endif // GAMEOBJECT_H
