#include "ResourceManager.h"
#include <QDebug>
#include <QPainter>

ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager instance;
    return instance;
}

ResourceManager::ResourceManager(QObject *parent)
    : QObject(parent)
    , m_loaded(false)
{
}

void ResourceManager::loadResources()
{
    if (m_loaded) {
        qWarning() << "Resources already loaded";
        return;
    }
    
    qDebug() << "加载游戏资源...";
    
    loadSprites();
    loadBackgrounds();
    loadDefaultResources();
    
    m_loaded = true;
    qDebug() << "游戏资源加载完成";
}

QPixmap ResourceManager::getSprite(const QString& spriteName)
{
    if (m_sprites.contains(spriteName)) {
        return m_sprites[spriteName];
    }
    
    qWarning() << "Sprite not found:" << spriteName;
    return QPixmap();
}

QPixmap ResourceManager::getBackground(const QString& backgroundName)
{
    if (m_backgrounds.contains(backgroundName)) {
        return m_backgrounds[backgroundName];
    }
    
    qWarning() << "Background not found:" << backgroundName;
    return QPixmap();
}

void ResourceManager::loadSprites()
{
    QPixmap player1_idle_sprite(":/assets/sprites/trump.png");
    if (player1_idle_sprite.isNull()) {
        qDebug() << "错误：无法加载图片 trump.png";
    } else {
        qDebug() << "成功加载图片 trump.png";
    }
    m_sprites["player1_idle"] = player1_idle_sprite;

    QPixmap player2_idle_sprite(":/assets/sprites/xi.png");
    if (player2_idle_sprite.isNull()) {
        qDebug() << "错误：无法加载图片 xi.png";
    } else {
        qDebug() << "成功加载图片 xi.png";
    }
    m_sprites["player2_idle"] = player2_idle_sprite;
}

void ResourceManager::loadBackgrounds()
{
    // 创建简单的背景
    QPixmap background(800, 600);
    background.fill(QColor(135, 206, 235)); // 天蓝色
    
    QPainter painter(&background);
    painter.setPen(Qt::darkGreen);
    painter.setBrush(Qt::green);
    painter.drawRect(0, 450, 800, 150); // 地面
    painter.end();
    
    m_backgrounds["default"] = background;
}

void ResourceManager::loadDefaultResources()
{
    // 加载默认资源，确保游戏可以运行
    qDebug() << "加载默认资源";
} 