#ifndef TEXTINFORMATIONITEM_H
#define TEXTINFORMATIONITEM_H

#include <QGraphicsTextItem>

namespace view {

class TextInformationItem : public QGraphicsTextItem
{
public:
    TextInformationItem(int fontSize, QGraphicsItem* parent = nullptr);
    void setMessage(const QString& text, bool centerPosition = false);

    int width() const;

private:
    QString m_text;
};

} // namespace view

#endif // TEXTINFORMATIONITEM_H
