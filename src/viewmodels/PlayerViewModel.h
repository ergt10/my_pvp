#pragma once

#include <QObject>
#include <QPointF>
#include "models/PlayerModel.h"

class PlayerViewModel : public QObject
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
    Q_PROPERTY(double healthPercentage READ healthPercentage NOTIFY healthChanged)
    Q_PROPERTY(double energyPercentage READ energyPercentage NOTIFY energyChanged)
    
public:
    explicit PlayerViewModel(PlayerModel* playerModel, QObject *parent = nullptr);
    
    // Properties
    int playerId() const;
    int health() const;
    int maxHealth() const;
    int energy() const;
    int maxEnergy() const;
    QPointF position() const;
    bool facingRight() const;
    QString currentAnimation() const;
    double healthPercentage() const;
    double energyPercentage() const;
    
    // Getters for model access
    PlayerModel* playerModel() const { return m_playerModel; }
    
signals:
    void healthChanged();
    void energyChanged();
    void positionChanged();
    void facingRightChanged();
    void currentAnimationChanged();
    void playerDied();
    
private slots:
    void onHealthChanged();
    void onEnergyChanged();
    void onPositionChanged();
    void onFacingRightChanged();
    void onCurrentAnimationChanged();
    void onPlayerDied();
    
private:
    PlayerModel* m_playerModel;
}; 