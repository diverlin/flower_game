#include "image.h"

namespace core {

Image::Image(const std::string& imageFilePath, PixmapLayer PixmapLayer, const Index2D& indexOffsetFromLeftTopCorner)
    :
    m_filePath(imageFilePath)
    , m_pixmapLayer(PixmapLayer)
    , m_indexOffsetFromLeftTopCorner(indexOffsetFromLeftTopCorner)
{
}

} // namespace core
