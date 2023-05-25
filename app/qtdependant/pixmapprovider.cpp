#include "pixmapprovider.h"

PixmapProvider& PixmapProvider::instance()
{
    static PixmapProvider provider;
    return provider;
}

const QPixmap& PixmapProvider::getPixmap(const QString& imageFilePath, const Size& size)
{
    QMap<QString, QPixmap>& pixmaps = m_data[size];
    if (!pixmaps.contains(imageFilePath)) {
        QPixmap pixmap(imageFilePath);

        if (Size(pixmap.size().width(), pixmap.size().height()) != size) {
            pixmap = pixmap.scaled(size.width(), size.height());
        }
        pixmaps[imageFilePath] = pixmap;
    }
    return pixmaps[imageFilePath];
}




