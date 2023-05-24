#include "textinformationitem.h"

#include <QFont>

TextInformationItem::TextInformationItem(QGraphicsItem* parent)
    : QGraphicsTextItem(parent)
{
    setFont(QFont(QStringList{"Comic Sans MS"}, 15));
}

void TextInformationItem::setMessage(const QString& text, bool centerPosition)
{
    setHtml(text);
    if (centerPosition) {
        setPos(parentItem()->boundingRect().center().x() - boundingRect().size().width() / 2,
               parentItem()->boundingRect().center().y());
    }
}
