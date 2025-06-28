#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QPixmap>

struct Attack {
    QString name;
    int damage;
    int energyCost;
    int range;
    QString animationName;
};

class FighterModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString description READ description CONSTANT)
    Q_PROPERTY(QStringList availableAttacks READ availableAttacks CONSTANT)
    
public:
    explicit FighterModel(QObject *parent = nullptr);
    
    // Getters
    QString name() const { return m_name; }
    QString description() const { return m_description; }
    QStringList availableAttacks() const;
    
    // Combat methods
    Attack getLightAttack() const { return m_lightAttack; }
    Attack getHeavyAttack() const { return m_heavyAttack; }
    Attack getSpecialAttack() const { return m_specialAttack; }
    
    // Graphics
    QPixmap getSprite(const QString& animationName) const;
    QStringList getAnimationFrames(const QString& animationName) const;
    
private:
    QString m_name;
    QString m_description;
    Attack m_lightAttack;
    Attack m_heavyAttack;
    Attack m_specialAttack;
    
    void initializeAttacks();
    void loadSprites();
}; 