#include "tile.h"

#include <QPainter>

Tile::Tile(const std::string& imageFilePath, TileLayer tileLayer, const Index2D& indexOffsetFromLeftTopCorner)
    :
    m_imageFilePath(imageFilePath)
  , m_tileLayer(tileLayer)
  , m_indexOffsetFromLeftTopCorner(indexOffsetFromLeftTopCorner)
{
}
