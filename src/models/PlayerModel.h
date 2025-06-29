#pragma once

#include <QObject>
#include <QPointF>
#include <QRectF>
#include <QTimer>
#include <memory>
#include "FighterModel.h"

class PlayerModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int playerId READ playerId CONSTANT)
    Q_PROPERTY(int health READ health NOTIFY healthChanged)
    Q_PROPERTY(int maxHealth READ maxHealth CONSTANT)
    Q_PROPERTY(int energy READ energy NOTIFY energyChanged)
    Q_PROPERTY(int maxEnergy READ maxEnergy CONSTANT)
    Q_PROPERTY(QPointF position READ position NOTIFY positionChanged)
    Q_PROPERTY(bool facingRight READ facingRight NOTIFY facingRightChanged)
    Q_PROPERTY(QString currentAnimation READ currentAnimation NOTIFY currentAnimationChanged)
    
public:
    explicit PlayerModel(int playerId, QObject *parent = nullptr);
    
    // Getters
    int playerId() const { return m_playerId; }
    int health() const { return m_health; }
    int maxHealth() const { return m_maxHealth; }
    int energy() const { return m_energy; }
    int maxEnergy() const { return m_maxEnergy; }
    QPointF position() const { return m_position; }
    bool facingRight() const { return m_facingRight; }
    QString currentAnimation() const { return m_currentAnimation; }
    QRectF hitBox() const { return m_hitBox; }
    
    FighterModel* fighter() const { return m_fighter.get(); }
    
    // Setters
    void setPosition(const QPointF& position);
    void setFacingRight(bool facingRight);
    void setCurrentAnimation(const QString& animation);
    
    // Actions
    void takeDamage(int damage);
    void heal(int amount);
    void useEnergy(int amount);
    void restoreEnergy(int amount);
    void reset();
    void update();
    
    // Movement
    void moveLeft();
    void moveRight();
    void jump();
    void crouch();
    void stopMoving();
    
    // Combat
    void lightAttack();
    void heavyAttack();
    void specialAttack();
    void block();
    void stopBlocking();
    
signals:
    void healthChanged();
    void energyChanged();
    void positionChanged();
    void facingRightChanged();
    void currentAnimationChanged();
    void attackPerformed(const QString& attackType);
    void died();
    
private:
    int m_playerId;
    int m_health;
    int m_maxHealth;
    int m_energy;
    int m_maxEnergy;
    QPointF m_position;
    QPointF m_velocity;
    bool m_facingRight;
    QString m_currentAnimation;
    QRectF m_hitBox;
    QTimer m_attackTimer;
    
    std::unique_ptr<FighterModel> m_fighter;
    
    // State flags
    bool m_isMovingLeft;
    bool m_isMovingRight;
    bool m_isJumping;
    bool m_isCrouching;
    bool m_isBlocking;
    bool m_isAttacking;
    bool m_onGround;
    
    // Physics constants
    static constexpr float GRAVITY = 0.8f;
    static constexpr float JUMP_FORCE = -15.0f;
    static constexpr float MOVE_SPEED = 5.0f;
    static constexpr float GROUND_Y = 400.0f;
    
    void updatePhysics();
    void updateHitBox();
    void updateAnimation();
}; 
