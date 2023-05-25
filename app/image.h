#ifndef IMAGE_H
#define IMAGE_H

#include "index2d.h"
#include "pixmaplayer.h"

#include <string>

namespace core {

class Image
{
public:
    Image(const std::string& imageFilePath, PixmapLayer pixmapLayer, const Index2D& indexOffsetFromLeftTopCorner = Index2D(0,0));

    const std::string& filePath() const { return m_filePath; }
    PixmapLayer layer() const { return m_pixmapLayer; }

    const Index2D& indexOffsetFromLeftTopCorner() const { return m_indexOffsetFromLeftTopCorner; }

private:
    std::string m_filePath;
    PixmapLayer m_pixmapLayer;
    Index2D m_indexOffsetFromLeftTopCorner;
};

} // namespace core

#endif // TILE_H
