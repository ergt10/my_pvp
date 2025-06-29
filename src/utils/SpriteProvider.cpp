#include "SpriteProvider.h"
#include <QDebug>

SpriteProvider::SpriteProvider() 
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}

QPixmap SpriteProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    qDebug() << "SpriteProvider: 请求图片ID:" << id;
    
    QPixmap pixmap = ResourceManager::getInstance().getSprite(id);
    
    if (pixmap.isNull()) {
        qWarning() << "SpriteProvider: 找不到图片:" << id;
        // 返回一个默认的占位符图片
        pixmap = QPixmap(64, 64);
        pixmap.fill(Qt::magenta);
    }
    
    if (size) {
        *size = pixmap.size();
    }
    
    return pixmap;
} 