#include "textinformationitem.h"

#include <QFont>
#include <QFontMetrics>

namespace view {

TextInformationItem::TextInformationItem(int fontSize, QGraphicsItem* parent)
    : QGraphicsTextItem(parent)
{
    setFont(QFont(QStringList{"Comic Sans MS"}, fontSize));
}

void TextInformationItem::setMessage(const QString& text, bool centerPosition)
{
    m_text = text;
    setHtml(text);
    if (centerPosition) {
        setPos(parentItem()->boundingRect().center().x() - boundingRect().size().width() / 2,
               parentItem()->boundingRect().center().y());
    }
}

int TextInformationItem::width() const
{
    QFontMetrics fontMetrics(font());
    return fontMetrics.horizontalAdvance(m_text);
}

} // namespace view
