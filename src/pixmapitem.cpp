#include "pixmapitem.h"

#include <QPainter>

PixmapItem::PixmapItem(const QString& fileName, QGraphicsItem* parent)
    : QGraphicsObject(parent)
{
    m_pixmap = QPixmap(fileName);
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

void PixmapItem::fit(float size)
{
    int w = m_pixmap.size().width();
    int h = m_pixmap.size().height();
    float scaleWidth = size/float(w);
    float scaleHeight = size/float(h);
    float scale = std::min(scaleWidth, scaleHeight);
    setScale(scale);

}

