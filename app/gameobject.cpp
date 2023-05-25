#include "gameobject.h"

#include "image.h"

namespace core {

StaticObject::StaticObject(const std::vector<Image>& images)
    :
    m_images(images)
{
    for (Image& image: m_images) {
        if (!image.indexOffsetFromLeftTopCorner().isNull()) {
            m_localOffsets.push_back(image.indexOffsetFromLeftTopCorner());
        }
    }
}

void StaticObject::setMapLocation(int index1d)
{
    if (m_mapLocation == index1d) {
        return;
    }
    m_mapLocation = index1d;
}

} // namespace core
