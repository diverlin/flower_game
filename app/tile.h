#ifndef TILE_H
#define TILE_H

#include "pixmaplayer.h"

#include <map>
#include <string>

namespace core {

class Image;

class Tile
{
public:
    Tile(int id): m_id(id) {}

    int id() const { return m_id; }
    void addImage(const Image& image);
    void removeImage(PixmapLayer pixmapLayer);

    bool isDirty() const { return m_isDirty; }
    void resetIsDirtyFlag() const { m_isDirty = false; }

    const std::map<int, std::string>& data() const { return m_data; }

private:
    int m_id = -1;
    std::map<int, std::string> m_data;
    mutable bool m_isDirty = false;

    void addImage(const std::string& imageFilePath, PixmapLayer pixmapLayer);
};

} // namespace core

#endif // TILE_H
