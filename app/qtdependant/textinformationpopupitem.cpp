#include "textinformationpopupitem.h"

#include <QFont>

namespace view {

TextInformationPopupItem::TextInformationPopupItem(const QPointF& pos, const QString& text, const QString& colorCode)
    : QGraphicsTextItem()
{
    setFont(QFont(QStringList{"Comic Sans MS"}, 14));
    setHtml(QString("<span style='color:%1;'>%2</span>").arg(colorCode).arg(text));
    setPos(pos);
}

TextInformationPopupItem::~TextInformationPopupItem()
{
}

void TextInformationPopupItem::update(int frameDeltaTimeMs)
{
    if (m_isDone) {
        return;
    }

    float stepAlpha = 1.0f*frameDeltaTimeMs/float(m_animationDurationMs);

    float alpha = opacity();
    alpha -= stepAlpha;
    if (alpha < 0.02) {
        alpha = 0;
        m_isDone = true;
    }
    setOpacity(alpha);
    setPos(pos().x(), pos().y()-50*stepAlpha);

    QGraphicsTextItem::update();
}

} // namespace view
