#ifndef SNAKESPROPERTYMODIFIER_H
#define SNAKESPROPERTYMODIFIER_H

namespace core {

class SnakesPropertyModifier
{
    const int SPEED_MULTIPLIER_EXPIRATION_MS = 5000;
public:
    SnakesPropertyModifier();
    ~SnakesPropertyModifier()=default;

    float moveSpeedMultiplier() const { return m_moveSpeedMultiplier; }
    float maxLengthMultiplier() const { return m_maxLengthMultiplier; }

    void reset();
    void update(int frameDeltaTimeMs, int flowersCounter, bool atLeastOneFlowerWasEaten);

private:
    int m_moveSpeedRatioDurationMs = -1;

    float m_moveSpeedMultiplier = 1.0f;
    float m_maxLengthMultiplier = 1.0f;
};

} // namespace core

#endif // SNAKEPROPERTYMODIFIER_H
