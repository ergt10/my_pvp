#include "CollisionController.h"
#include <QDebug>
#include <cmath>

CollisionController::CollisionController(QObject *parent)
    : QObject(parent)
{
}

void CollisionController::updateCollisions(PlayerModel* player1, PlayerModel* player2)
{
    if (!player1 || !player2) return;
    
    // 检查玩家之间的基础碰撞（防止重叠）
    QRectF hitBox1 = player1->hitBox();
    QRectF hitBox2 = player2->hitBox();
    
    if (isColliding(hitBox1, hitBox2)) {
        // 计算推开距离
        float overlap = std::abs(hitBox1.center().x() - hitBox2.center().x());
        float pushDistance = (hitBox1.width() + hitBox2.width()) / 2 - overlap + 5;
        
        // 推开玩家
        if (player1->position().x() < player2->position().x()) {
            player1->setPosition(QPointF(player1->position().x() - pushDistance/2, player1->position().y()));
            player2->setPosition(QPointF(player2->position().x() + pushDistance/2, player2->position().y()));
        } else {
            player1->setPosition(QPointF(player1->position().x() + pushDistance/2, player1->position().y()));
            player2->setPosition(QPointF(player2->position().x() - pushDistance/2, player2->position().y()));
        }
    }
}

void CollisionController::checkAttackCollision(PlayerModel* player1, PlayerModel* player2, 
                                               int attackingPlayerId, const QString& attackType)
{
    if (!player1 || !player2) return;
    
    PlayerModel* attacker = (attackingPlayerId == 1) ? player1 : player2;
    PlayerModel* target = (attackingPlayerId == 1) ? player2 : player1;
    
    // 获取攻击判定框
    QRectF attackHitBox = getAttackHitBox(attacker, attackType);
    QRectF targetHitBox = target->hitBox();
    
    // 检查攻击是否命中
    if (isColliding(attackHitBox, targetHitBox)) {
        int damage = getAttackDamage(attackType);
        
        // 如果目标在格挡状态，减少伤害
        if (target->currentAnimation() == "block") {
            damage = static_cast<int>(damage * 0.3); // 格挡减少70%伤害
            qDebug() << "攻击被格挡！伤害减少为:" << damage;
        }
        
        // 应用伤害
        target->takeDamage(damage);
        
        // 应用击退效果
        applyKnockback(attacker, target, attackType);
        
        qDebug() << "玩家" << attackingPlayerId << "的" << attackType << "攻击命中！造成" << damage << "点伤害";
    }
}

bool CollisionController::isColliding(const QRectF& rect1, const QRectF& rect2)
{
    return rect1.intersects(rect2);
}

QRectF CollisionController::getAttackHitBox(PlayerModel* player, const QString& attackType)
{
    QPointF position = player->position();
    bool facingRight = player->facingRight();
    
    QRectF attackBox;
    
    if (attackType == "light") {
        // 轻攻击范围较小
        float width = 60;
        float height = 40;
        float offsetX = facingRight ? 30 : -90;
        attackBox = QRectF(position.x() + offsetX, position.y() - 30, width, height);
    } else if (attackType == "heavy") {
        // 重攻击范围较大
        float width = 80;
        float height = 50;
        float offsetX = facingRight ? 30 : -110;
        attackBox = QRectF(position.x() + offsetX, position.y() - 35, width, height);
    } else if (attackType == "special") {
        // 特殊攻击范围最大
        float width = 120;
        float height = 60;
        float offsetX = facingRight ? 30 : -150;
        attackBox = QRectF(position.x() + offsetX, position.y() - 40, width, height);
    }
    
    return attackBox;
}

int CollisionController::getAttackDamage(const QString& attackType)
{
    if (attackType == "light") {
        return 15;
    } else if (attackType == "heavy") {
        return 30;
    } else if (attackType == "special") {
        return 50;
    }
    return 0;
}

void CollisionController::applyKnockback(PlayerModel* attacker, PlayerModel* target, const QString& attackType)
{
    float knockbackForce = 0;
    
    if (attackType == "light") {
        knockbackForce = 10;
    } else if (attackType == "heavy") {
        knockbackForce = 20;
    } else if (attackType == "special") {
        knockbackForce = 35;
    }
    
    // 计算击退方向
    bool pushRight = attacker->position().x() < target->position().x();
    float direction = pushRight ? 1.0f : -1.0f;
    
    // 应用击退
    QPointF newPosition = target->position();
    newPosition.setX(newPosition.x() + knockbackForce * direction);
    
    // 确保不超出边界
    newPosition.setX(std::max(0.0, std::min(800.0, newPosition.x())));
    
    target->setPosition(newPosition);
} 