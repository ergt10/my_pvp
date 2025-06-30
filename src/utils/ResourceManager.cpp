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
    
    QPixmap player2_idle_sprite(":/assets/sprites/xi.png");
    if (player2_idle_sprite.isNull()) {
        qDebug() << "错误：无法加载图片 xi.png";
    } else {
        qDebug() << "成功加载图片 xi.png";
    }
    
    // Player 1 (Trump) 所有动画状态
    m_sprites["player1_idle"] = player1_idle_sprite;
    m_sprites["player1_walk"] = player1_idle_sprite;  // 临时使用同一张图片
    m_sprites["player1_jump"] = player1_idle_sprite;
    m_sprites["player1_light_attack"] = player1_idle_sprite;
    m_sprites["player1_heavy_attack"] = player1_idle_sprite;
    m_sprites["player1_special_attack"] = player1_idle_sprite;
    m_sprites["player1_block"] = player1_idle_sprite;
    m_sprites["player1_crouch"] = player1_idle_sprite;
    
    // Player 2 (Xi) 所有动画状态
    m_sprites["player2_idle"] = player2_idle_sprite;
    m_sprites["player2_walk"] = player2_idle_sprite;  // 临时使用同一张图片
    m_sprites["player2_jump"] = player2_idle_sprite;
    m_sprites["player2_light_attack"] = player2_idle_sprite;
    m_sprites["player2_heavy_attack"] = player2_idle_sprite;
    m_sprites["player2_special_attack"] = player2_idle_sprite;
    m_sprites["player2_block"] = player2_idle_sprite;
    m_sprites["player2_crouch"] = player2_idle_sprite;
    
    qDebug() << "所有精灵动画状态已加载";
}

void ResourceManager::loadBackgrounds()
{
    QPixmap background(":/assets/backgrounds/background.png");
    if (background.isNull()) {
        qDebug() << "错误：无法加载图片 my_bg.png";
    } else {
        qDebug() << "成功加载图片 my_bg.png";
    }
    m_backgrounds["default"] = background;
}

void ResourceManager::loadDefaultResources()
{
    // 加载默认资源，确保游戏可以运行
    qDebug() << "加载默认资源";
} 