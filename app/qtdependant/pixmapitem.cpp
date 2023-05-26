#include "pixmapitem.h"

#include <QPainter>

namespace view {

PixmapItem::PixmapItem()
    : QGraphicsObject()
{
}

QSizeF PixmapItem::size() const
{
    return m_finalPixmap.size();
}

QRectF PixmapItem::boundingRect() const
{
    return QRectF(QPointF(0, 0), m_finalPixmap.size());
}

void PixmapItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if (m_isDirty) {
        //qInfo() << "solve isDirty";
        unitePixmaps();
        m_isDirty = false;
    }

    painter->drawPixmap(0, 0, m_finalPixmap);
}

void PixmapItem::setPixmap(const QPixmap& pixmap, core::PixmapLayer layer)
{
    if (m_pixmaps.contains(layer)) {
        if (m_pixmaps[layer].cacheKey() == pixmap.cacheKey()) {
            //qDebug() << "the equal pixmap for that layer is already set, skip";
            return;
        }
    }
    if (m_finalPixmap.isNull()) {
        m_finalPixmap = pixmap;
    }
    m_pixmaps[layer] = pixmap;

    m_isDirty = true;
    update();
}

void PixmapItem::removePixmap(core::PixmapLayer layer)
{
    if (m_pixmaps.contains(layer)) {
        m_pixmaps[layer] = QPixmap();
        m_isDirty = true;
        update();
    }
}

void PixmapItem::unitePixmaps()
{
    QPainter painter(&m_finalPixmap);
    QList<core::PixmapLayer> keys = m_pixmaps.keys();
    //qInfo() << "unitePixmaps";
    for (core::PixmapLayer layer: qAsConst(keys)) {
        //qInfo() << "layer=" << static_cast<int>(layer);
        const QPixmap& pixmap = m_pixmaps[layer];
        if (pixmap.isNull()) {
            continue;
        }
        if (m_finalPixmap.cacheKey() == pixmap.cacheKey()) {
            continue; // we already set m_finalPixmap as first pixmap
        }
        painter.drawPixmap(0, 0, pixmap);
    }
}

} // namespace view
