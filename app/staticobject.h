#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include "ibaseobject.h"
#include "index2d.h"

#include <string>
#include <vector>
#include <map>

namespace core {

class Image;

class StaticObject : public IBaseObject
{
public:
    StaticObject(const std::vector<Image>& images, int delaysMs = 1000);
    ~StaticObject() override = default;

    void enableAnimationPingPongMode() { m_isAnimationPingPongModeEnabled = true; }
    void acceptNewImages() { m_isImagesChanged = false; }

    bool isImagesChanged() const { return m_isImagesChanged; }
    void addAnimationFrame(const std::vector<Image>& images, int delayMs);

    const std::vector<Image>& images() const;
    void setMapTileIndex(std::size_t mapTileIndex);

    std::size_t mapTileIndex() { return m_mapTileIndex; }
    const std::vector<Index2D>& localOffsets() const { return m_localOffsets; }

    void update(int frameDeltaTimeMs) override;

private:
    bool m_isImagesChanged = false;
    int m_sinceLastAnimationMs = 0;

    // ping pong mode
    bool m_isAnimationPingPongModeEnabled = false;
    bool m_animationPingPongUpDirection = true;
    //

    std::map<int, std::vector<Image>> m_images;
    std::map<int, int> m_animationDelays;

    std::size_t m_currentImagesIndex = 0;

    std::size_t m_mapTileIndex;
    std::vector<Index2D> m_localOffsets;

    void updateAnimation(int frameDeltaTimeMs);
};

} // namespace core

#endif // GAMEOBJECT_H
