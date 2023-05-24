#ifndef PIXMAPITEM_H
#define PIXMAPITEM_H

#include <QGraphicsObject>

class PixmapItem : public QGraphicsObject
{
public:
    PixmapItem(const QString& fileName, QGraphicsItem* parent = nullptr);

    QSizeF size() const;
    QRectF boundingRect() const override;

    void fit(float size);
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

private:
    QPixmap m_pixmap;
};

#endif // PIXMAPITEM_H
