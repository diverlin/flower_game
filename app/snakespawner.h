#ifndef SNAKESPAWNER_H
#define SNAKESPAWNER_H

namespace core {

class SnakeSpawner
{
    const int DEFAULT_OCCUR_INTERVAL_MS = 5000;
    const int DEFAULT_DECREASE_SPAWN_TIME_MS = 10000;

public:
    SnakeSpawner()=default;
    ~SnakeSpawner()=default;

    bool isQueued() const { return m_isQueued; }
    void releaseQueued() { m_isQueued = false; }

    void reset();
    void update(int frameDeltaTimeMs, int flowersCounter);

private:
    bool m_isFirstOccur = true;
    bool m_isQueued = false;

    int m_sinceLastOccurMs = 0;
    float m_occurIntervalMs = DEFAULT_OCCUR_INTERVAL_MS;

    int m_sinceLastDecreaseSpawnTimeMs = 0;
    int m_decreaseSpawnTimeIntervalMs = DEFAULT_DECREASE_SPAWN_TIME_MS;
};

} // namespace core

#endif // SNAKESPAWNER_H
