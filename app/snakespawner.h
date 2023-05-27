#ifndef SNAKESPAWNER_H
#define SNAKESPAWNER_H

namespace core {

class SnakeSpawner
{
    const int DEFAULT_OCCUR_INTERVAL_MS = 5000;

public:
    SnakeSpawner()=default;
    ~SnakeSpawner()=default;

    bool isQueued() const { return m_isQueued; }
    void releaseQueued() { m_isQueued = false; }

    void reset();
    void update(int frameDeltaTimeMs, int flowersCounter);

private:
    int m_msSinceLastOccur = 0;
    int m_occurIntervalMs = 0;

    bool m_isQueued = false;
};

} // namespace core

#endif // SNAKESPAWNER_H
