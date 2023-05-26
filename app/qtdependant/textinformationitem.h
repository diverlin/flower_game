#ifndef TEXTINFORMATIONITEM_H
#define TEXTINFORMATIONITEM_H

#include <QGraphicsTextItem>

namespace view {

class TextInformationItem : public QGraphicsTextItem
{
public:
    TextInformationItem(QGraphicsItem* parent = nullptr);
    void setMessage(const QString& text, bool centerPosition = false);
};

} // namespace view

#endif // TEXTINFORMATIONITEM_H
