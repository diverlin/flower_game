#include "snakespawner.h"

namespace core {

void SnakeSpawner::reset()
{
    m_isFirstOccur = true;

    m_sinceLastOccurMs = 0;
    m_occurIntervalMs = DEFAULT_OCCUR_INTERVAL_MS;

    m_sinceLastDecreaseSpawnTimeMs = 0;
    m_decreaseSpawnTimeIntervalMs = DEFAULT_DECREASE_SPAWN_TIME_MS;
}

void SnakeSpawner::update(int frameDeltaTimeMs, int flowersCounter)
{
    if (flowersCounter > 0) {
        m_sinceLastOccurMs += frameDeltaTimeMs;
        if ((m_sinceLastOccurMs > m_occurIntervalMs) || m_isFirstOccur) {
            m_isQueued = true;
            m_sinceLastOccurMs = 0;

            if (m_isFirstOccur) {
                m_isFirstOccur = false;
            }
        }

        m_sinceLastDecreaseSpawnTimeMs += frameDeltaTimeMs;
        if (m_sinceLastDecreaseSpawnTimeMs > m_decreaseSpawnTimeIntervalMs) {
            m_occurIntervalMs *= 0.95;
            m_sinceLastDecreaseSpawnTimeMs = 0;
        }
    }
}

} // namespace core
