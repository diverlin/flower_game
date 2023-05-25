#include "tile.h"

#include <QPainter>

namespace core {

Tile::Tile(const std::string& imageFilePath, PixmapLayer PixmapLayer, const Index2D& indexOffsetFromLeftTopCorner)
    :
    m_imageFilePath(imageFilePath)
  , m_PixmapLayer(PixmapLayer)
  , m_indexOffsetFromLeftTopCorner(indexOffsetFromLeftTopCorner)
{
}

} // namespace core
