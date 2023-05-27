#include "snakespropertymodifier.h"

namespace core {

void SnakesPropertyModifier::reset()
{
    m_moveSpeedRatioDurationMs = -1;
    m_moveSpeedMultiplier = 1.0f;
    m_maxLengthMultiplier = 1.0f;
}

void SnakesPropertyModifier::update(int frameDeltaTimeMs, int flowersCounter, bool atLeastOneFlowerWasEaten)
{
    if (atLeastOneFlowerWasEaten) {
        m_moveSpeedRatioDurationMs = SPEED_MULTIPLIER_EXPIRATION_MS;
    }

    // update length modificator
    if (flowersCounter >= 2) {
        m_maxLengthMultiplier = 2.0f;
    } else {
        m_maxLengthMultiplier = 1.0f;
    }

    // update move speed modificator
    if (m_moveSpeedRatioDurationMs > 0) {
        m_moveSpeedRatioDurationMs -= frameDeltaTimeMs;
        m_moveSpeedMultiplier = 2.0f;
    } else {
        m_moveSpeedMultiplier = 1.0f;
    }
}

} // namespace core
