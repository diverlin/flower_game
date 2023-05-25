#ifndef PIXMAPITEM_H
#define PIXMAPITEM_H

#include <QGraphicsObject>
#include <QMap>

#include "pixmaplayer.h"

namespace view {

class PixmapItem : public QGraphicsObject
{
public:
    PixmapItem();
    ~PixmapItem()=default;

    void setPixmap(const QPixmap& pixmap, core::PixmapLayer layer);
    void removePixmap(core::PixmapLayer layer);

    QSizeF size() const;
    QRectF boundingRect() const override;

protected:
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

private:
    bool m_isDirty = false; // if true request to re-draw (unite all pixmaps according to layer hierarcy into final pixmap)
    QMap<core::PixmapLayer, QPixmap> m_pixmaps;
    QPixmap m_finalPixmap;

    void unitePixmaps();
};

} // namespace view

#endif // PIXMAPITEM_H
