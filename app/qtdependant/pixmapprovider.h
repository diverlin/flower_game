#ifndef PIXMAPPROVIDER_H
#define PIXMAPPROVIDER_H

#include "size.h"

#include <QPixmap>
#include <QMap>

namespace view {

/* this class implements two patterns: Singleton and LightWeight (to share commonly used resources) */
class PixmapProvider
{
public:
    static PixmapProvider& instance();
    const QPixmap& getPixmap(const QString& key, const core::Size& size);
    ~PixmapProvider()=default;

private:
    PixmapProvider()=default;

    QMap<core::Size, QMap<QString, QPixmap>> m_data;
};

} // namespace view

#endif // PIXMAPPROVIDER_H
