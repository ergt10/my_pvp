#ifndef SPRITEPROVIDER_H
#define SPRITEPROVIDER_H

#include <QQuickImageProvider>
#include "ResourceManager.h"

class SpriteProvider : public QQuickImageProvider
{
public:
    SpriteProvider();
    
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
};

#endif // SPRITEPROVIDER_H 