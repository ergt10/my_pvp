#pragma once

#include <QObject>
#include <QRectF>
#include "models/PlayerModel.h"

class CollisionController : public QObject
{
    Q_OBJECT
    
public:
    explicit CollisionController(QObject *parent = nullptr);
    
    void updateCollisions(PlayerModel* player1, PlayerModel* player2);
    void checkAttackCollision(PlayerModel* player1, PlayerModel* player2, 
                              int attackingPlayerId, const QString& attackType);
    
private:
    bool isColliding(const QRectF& rect1, const QRectF& rect2);
    QRectF getAttackHitBox(PlayerModel* player, const QString& attackType);
    int getAttackDamage(const QString& attackType);
    void applyKnockback(PlayerModel* attacker, PlayerModel* target, const QString& attackType);
}; 