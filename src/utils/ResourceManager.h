#pragma once

#include <QObject>
#include <QPixmap>
#include <QHash>
#include <QString>

class ResourceManager : public QObject
{
    Q_OBJECT
    
public:
    static ResourceManager& getInstance();
    
    void loadResources();
    QPixmap getSprite(const QString& spriteName);
    QPixmap getBackground(const QString& backgroundName);
    
private:
    explicit ResourceManager(QObject *parent = nullptr);
    ~ResourceManager() = default;
    
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    
    void loadSprites();
    void loadBackgrounds();
    void loadDefaultResources();
    
    QHash<QString, QPixmap> m_sprites;
    QHash<QString, QPixmap> m_backgrounds;
    bool m_loaded;
}; 