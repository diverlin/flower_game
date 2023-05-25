#include "tile.h"
#include "image.h"

namespace core {

void Tile::addImage(const Image& image)
{
    addImage(image.filePath(), image.layer());
}

void Tile::addImage(const std::string& imageFilePath, PixmapLayer pixmapLayer)
{
    int key = static_cast<int>(pixmapLayer);
    if (m_data.find(key) != m_data.end()) {
        if (m_data[key] == imageFilePath) {
            // same image on same layer already exists
            return;
        }
    }
    m_data[key] = imageFilePath;
    m_isDirty = true;
}

void Tile::removeImage(PixmapLayer pixmapLayer)
{
    int key = static_cast<int>(pixmapLayer);
    if (m_data.find(key) != m_data.end()) {
        m_data[key] = "";
        m_isDirty = true;
    }
}

} // namespace core
