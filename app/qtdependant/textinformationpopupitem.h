#ifndef TEXTINFORMATIONPOPUPITEM_H
#define TEXTINFORMATIONPOPUPITEM_H

#include <QGraphicsTextItem>

namespace view {

class TextInformationPopupItem final : public QGraphicsTextItem
{
public:
    TextInformationPopupItem(const QPointF& pos, const QString& text, const QString& colorCode);
    ~TextInformationPopupItem() override final;

    void update(int frameDeltaTimeMs);

    bool isDone() const { return m_isDone; }

private:
    int m_animationDurationMs = 2000;
    bool m_isDone = false;
};

} // namespace view

#endif // TEXTINFORMATIONPOPUPITEM_H
