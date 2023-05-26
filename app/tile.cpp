#include "tile.h"
#include "image.h"

namespace core {

bool Tile::addImage(const Image& image)
{
    return addImage(image.filePath(), image.layer());
}

bool Tile::addImage(const std::string& imageFilePath, PixmapLayer pixmapLayer)
{
    int key = static_cast<int>(pixmapLayer);
    if (m_data.find(key) != m_data.end()) {
        if (m_data[key] == imageFilePath) {
            // same image on same layer already exists
            return false;
        }
    }
    m_data[key] = imageFilePath;
    m_isDirty = true;
    return true;
}

bool Tile::removeImage(PixmapLayer pixmapLayer)
{
    int key = static_cast<int>(pixmapLayer);
    if (m_data.find(key) != m_data.end()) {
        m_data[key] = "";
        m_isDirty = true;
        return true;
    }
    return false;
}

} // namespace core
