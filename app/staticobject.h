#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include "ibaseobject.h"
#include "index2d.h"

#include <string>
#include <vector>

namespace core {

class Image;

class StaticObject : public IBaseObject
{
public:
    StaticObject(const std::vector<Image>& images);
    ~StaticObject() override = default;

    const std::vector<Image>& images() const { return m_images; }
    void setMapTileIndex(std::size_t i);

    std::size_t mapTileIndex() { return m_mapLocation; }
    const std::vector<Index2D>& localOffsets() const { return m_localOffsets; }

    void update(int /*frameDeltaTimeMs*/) override {}

private:
    std::vector<Image> m_images;
    std::size_t m_mapLocation;
    std::vector<Index2D> m_localOffsets;
};

} // namespace core

#endif // GAMEOBJECT_H
