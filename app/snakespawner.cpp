#include "snakespawner.h"

namespace core {

void SnakeSpawner::reset()
{
    m_msSinceLastOccur = 0;
    m_occurIntervalMs = 0;
}

void SnakeSpawner::update(int frameDeltaTimeMs, int flowersCounter)
{
    m_msSinceLastOccur += frameDeltaTimeMs;
    if (flowersCounter > 0) {
        if (m_msSinceLastOccur > m_occurIntervalMs) {
            m_isQueued = true;
            m_occurIntervalMs = DEFAULT_OCCUR_INTERVAL_MS; // todo decrease
            m_msSinceLastOccur = 0;
        }
    }
}

} // namespace core
