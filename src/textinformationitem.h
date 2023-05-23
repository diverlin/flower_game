#ifndef TEXTINFORMATIONITEM_H
#define TEXTINFORMATIONITEM_H

#include <QGraphicsTextItem>

class TextInformationItem : public QGraphicsTextItem
{
public:
    TextInformationItem(QGraphicsItem* parent = nullptr);
    void setMessage(const QString& text, const bool centerPosition = true);
};

#endif // TEXTINFORMATIONITEM_H
