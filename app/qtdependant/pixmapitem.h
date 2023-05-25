#ifndef PIXMAPITEM_H
#define PIXMAPITEM_H

#include <QGraphicsObject>

namespace view {

class PixmapItem : public QGraphicsObject
{
public:
    PixmapItem(const QPixmap& pixmap);

    void setPixmap(const QPixmap& pixmap) { m_pixmap = pixmap; }

    QSizeF size() const;
    QRectF boundingRect() const override;

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

private:
    QPixmap m_pixmap;
};

} // namespace view

#endif // PIXMAPITEM_H
