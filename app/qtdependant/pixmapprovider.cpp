#include "pixmapprovider.h"

namespace view {

PixmapProvider& PixmapProvider::instance()
{
    static PixmapProvider provider;
    return provider;
}

const QPixmap& PixmapProvider::getPixmap(const QString& imageFilePath, const core::Size& size)
{
    QMap<QString, QPixmap>& pixmaps = m_data[size];
    if (!pixmaps.contains(imageFilePath)) {
        QPixmap pixmap(imageFilePath);

        if (core::Size(pixmap.size().width(), pixmap.size().height()) != size) {
            pixmap = pixmap.scaled(size.width(), size.height());
        }
        pixmaps[imageFilePath] = pixmap;
    }
    return pixmaps[imageFilePath];
}

} // namespace view



