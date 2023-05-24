#ifndef TILEDESCRIPTOR_H
#define TILEDESCRIPTOR_H

#include "index2d.h"

#include <string>

class TileDescriptor
{
public:
    TileDescriptor(const std::string& imageFilePath, const Index2D& indexOffsetFromLeftTopCorner = Index2D(0,0));

    const std::string& imageFilePath() const { return m_imageFilePath; }
    const Index2D& mapLocation() const { return m_mapLocation; }

    const Index2D& indexOffsetFromLeftTopCorner() const { return m_indexOffsetFromLeftTopCorner; }
    void updateMapLocation(const Index2D& rootMapLocation) {
        m_mapLocation.set(rootMapLocation.i(), rootMapLocation.j());
        m_mapLocation += m_indexOffsetFromLeftTopCorner;
    }

private:
    std::string m_imageFilePath;
    Index2D m_indexOffsetFromLeftTopCorner;
    Index2D m_mapLocation;
};

#endif // TILEDESCRIPTOR_H
