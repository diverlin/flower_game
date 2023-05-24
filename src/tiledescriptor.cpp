#include "tiledescriptor.h"

#include <QPainter>

TileDescriptor::TileDescriptor(const std::string& imageFilePath, const Index2D& indexOffsetFromLeftTopCorner)
    :
    m_imageFilePath(imageFilePath)
    , m_indexOffsetFromLeftTopCorner(indexOffsetFromLeftTopCorner)
{
}
