#include "staticobject.h"

#include "image.h"

namespace core {

StaticObject::StaticObject(const std::vector<Image>& images, int delayMs)
{
    for (const Image& image: images) {
        if (!image.indexOffsetFromLeftTopCorner().isNull()) {
            m_localOffsets.push_back(image.indexOffsetFromLeftTopCorner());
        }
    }

    m_currentImagesIndex = 0;
    m_images[m_currentImagesIndex] = images;
    m_animationDelays[m_currentImagesIndex] = delayMs;
}

void StaticObject::setMapTileIndex(std::size_t index1d)
{
    if (m_mapTileIndex == index1d) {
        return;
    }
    m_mapTileIndex = index1d;
}

const std::vector<Image>& StaticObject::images() const
{
    return m_images.at(m_currentImagesIndex);
}

void StaticObject::update(int frameDeltaTimeMs)
{
    if (isAlive()) {
        updateAnimation(frameDeltaTimeMs);
    }
}

void StaticObject::updateAnimation(int frameDeltaTimeMs)
{
    m_sinceLastAnimationMs += frameDeltaTimeMs;
    if (m_sinceLastAnimationMs > m_animationDelays[m_currentImagesIndex]) {
        if (m_isAnimationPingPongModeEnabled) {
            if (m_animationPingPongUpDirection) {
                if (m_currentImagesIndex < m_images.size()-1) {
                    m_currentImagesIndex++;
                    m_sinceLastAnimationMs = 0;
                    m_isImagesChanged = true;
                } else {
                    m_animationPingPongUpDirection = false;
                }
            } else {
                if (m_currentImagesIndex > 0) {
                    m_currentImagesIndex--;
                    m_sinceLastAnimationMs = 0;
                    m_isImagesChanged = true;
                } else {
                    m_animationPingPongUpDirection = true;
                }
            }
        } else {
            if (m_currentImagesIndex < m_images.size()-1) {
                m_currentImagesIndex++;
                m_sinceLastAnimationMs = 0;
                m_isImagesChanged = true;
            }
        }
    }
}

void StaticObject::addAnimationFrame(const std::vector<Image>& images, int delayMs)
{
    std::size_t nextAnimationIndex = m_images.size();
    m_images[nextAnimationIndex] = images;
    m_animationDelays[nextAnimationIndex] = delayMs;
}

} // namespace core
