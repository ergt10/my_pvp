#include "PlayerModel.h"
#include <QDebug>
#include <algorithm>

PlayerModel::PlayerModel(int playerId, QObject *parent)
    : QObject(parent)
    , m_playerId(playerId)
    , m_health(100)
    , m_maxHealth(100)
    , m_energy(100)
    , m_maxEnergy(100)
    , m_position(0, 0)
    , m_velocity(0, 0)
    , m_facingRight(true)
    , m_currentAnimation("idle")
    , m_isMovingLeft(false)
    , m_isMovingRight(false)
    , m_isJumping(false)
    , m_isCrouching(false)
    , m_isBlocking(false)
    , m_isAttacking(false)
    , m_onGround(true)
{
    m_fighter = std::make_unique<FighterModel>(this);
    updateHitBox();
}

void PlayerModel::setPosition(const QPointF& position)
{
    if (m_position != position) {
        m_position = position;
        updateHitBox();
        emit positionChanged();
    }
}

void PlayerModel::setFacingRight(bool facingRight)
{
    if (m_facingRight != facingRight) {
        m_facingRight = facingRight;
        emit facingRightChanged();
    }
}

void PlayerModel::setCurrentAnimation(const QString& animation)
{
    if (m_currentAnimation != animation) {
        m_currentAnimation = animation;
        emit currentAnimationChanged();
    }
}

void PlayerModel::takeDamage(int damage)
{
    m_health = std::max(0, m_health - damage);
    emit healthChanged();
    
    if (m_health <= 0) {
        emit died();
    }
}

void PlayerModel::heal(int amount)
{
    m_health = std::min(m_maxHealth, m_health + amount);
    emit healthChanged();
}

void PlayerModel::useEnergy(int amount)
{
    m_energy = std::max(0, m_energy - amount);
    emit energyChanged();
}

void PlayerModel::restoreEnergy(int amount)
{
    m_energy = std::min(m_maxEnergy, m_energy + amount);
    emit energyChanged();
}

void PlayerModel::reset()
{
    m_health = m_maxHealth;
    m_energy = m_maxEnergy;
    m_velocity = QPointF(0, 0);
    m_isMovingLeft = false;
    m_isMovingRight = false;
    m_isJumping = false;
    m_isCrouching = false;
    m_isBlocking = false;
    m_isAttacking = false;
    m_onGround = true;
    setCurrentAnimation("idle");
    
    emit healthChanged();
    emit energyChanged();
}

void PlayerModel::update()
{
    updatePhysics();
    updateAnimation();
    
    // 自动恢复能量
    if (!m_isAttacking && m_energy < m_maxEnergy) {
        restoreEnergy(1);
    }
}

void PlayerModel::moveLeft()
{
    m_isMovingLeft = true;
    m_isMovingRight = false;
    setFacingRight(false);
}

void PlayerModel::moveRight()
{
    m_isMovingRight = true;
    m_isMovingLeft = false;
    setFacingRight(true);
}

void PlayerModel::jump()
{
    if (m_onGround && !m_isJumping) {
        m_velocity.setY(JUMP_FORCE);
        m_isJumping = true;
        m_onGround = false;
    }
}

void PlayerModel::crouch()
{
    if (m_onGround) {
        m_isCrouching = true;
    }
}

void PlayerModel::stopMoving()
{
    m_isMovingLeft = false;
    m_isMovingRight = false;
    m_isCrouching = false;
}

void PlayerModel::lightAttack()
{
    if (!m_isAttacking && m_energy >= 10) {
        m_isAttacking = true;
        useEnergy(10);
        setCurrentAnimation("light_attack");
        emit attackPerformed("light");
    }
}

void PlayerModel::heavyAttack()
{
    if (!m_isAttacking && m_energy >= 25) {
        m_isAttacking = true;
        useEnergy(25);
        setCurrentAnimation("heavy_attack");
        emit attackPerformed("heavy");
    }
}

void PlayerModel::specialAttack()
{
    if (!m_isAttacking && m_energy >= 50) {
        m_isAttacking = true;
        useEnergy(50);
        setCurrentAnimation("special_attack");
        emit attackPerformed("special");
    }
}

void PlayerModel::block()
{
    if (!m_isAttacking) {
        m_isBlocking = true;
        setCurrentAnimation("block");
    }
}

void PlayerModel::stopBlocking()
{
    m_isBlocking = false;
}

void PlayerModel::updatePhysics()
{
    // 水平移动
    if (m_isMovingLeft && !m_isCrouching) {
        m_velocity.setX(-MOVE_SPEED);
    } else if (m_isMovingRight && !m_isCrouching) {
        m_velocity.setX(MOVE_SPEED);
    } else {
        m_velocity.setX(0);
    }
    
    // 应用重力
    if (!m_onGround) {
        m_velocity.setY(m_velocity.y() + GRAVITY);
    }
    
    // 更新位置
    QPointF newPosition = m_position + m_velocity;
    
    // 地面碰撞检测
    if (newPosition.y() >= GROUND_Y) {
        newPosition.setY(GROUND_Y);
        m_velocity.setY(0);
        m_onGround = true;
        m_isJumping = false;
    }
    
    // 边界检测
    newPosition.setX(std::max(0.0, std::min(800.0, newPosition.x())));
    
    setPosition(newPosition);
}

void PlayerModel::updateHitBox()
{
    // 更新碰撞盒
    m_hitBox = QRectF(m_position.x() - 25, m_position.y() - 50, 50, 50);
}

void PlayerModel::updateAnimation()
{
    if (m_isAttacking) {
        // 攻击动画会在动画完成后自动重置
        return;
    }
    
    if (m_isBlocking) {
        setCurrentAnimation("block");
    } else if (!m_onGround) {
        setCurrentAnimation("jump");
    } else if (m_isCrouching) {
        setCurrentAnimation("crouch");
    } else if (m_isMovingLeft || m_isMovingRight) {
        setCurrentAnimation("walk");
    } else {
        setCurrentAnimation("idle");
    }
} 