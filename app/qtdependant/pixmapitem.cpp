#include "pixmapitem.h"

#include <QPainter>

namespace view {

PixmapItem::PixmapItem(const QPixmap& pixmap)
    : QGraphicsObject(),
    m_pixmap(pixmap)
{
}

QSizeF PixmapItem::size() const
{
    return m_pixmap.size();
}

QRectF PixmapItem::boundingRect() const
{
    return QRectF(QPointF(0, 0), m_pixmap.size());
}

void PixmapItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->drawPixmap(0, 0, m_pixmap);
}

} // namespace view
