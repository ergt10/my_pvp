#include "PlayerViewModel.h"

PlayerViewModel::PlayerViewModel(PlayerModel* playerModel, QObject *parent)
    : QObject(parent)
    , m_playerModel(playerModel)
{
    // Connect model signals to view model signals
    connect(m_playerModel, &PlayerModel::healthChanged, 
            this, &PlayerViewModel::onHealthChanged);
    connect(m_playerModel, &PlayerModel::energyChanged, 
            this, &PlayerViewModel::onEnergyChanged);
    connect(m_playerModel, &PlayerModel::positionChanged, 
            this, &PlayerViewModel::onPositionChanged);
    connect(m_playerModel, &PlayerModel::facingRightChanged, 
            this, &PlayerViewModel::onFacingRightChanged);
    connect(m_playerModel, &PlayerModel::currentAnimationChanged, 
            this, &PlayerViewModel::onCurrentAnimationChanged);
    connect(m_playerModel, &PlayerModel::died, 
            this, &PlayerViewModel::onPlayerDied);
}

int PlayerViewModel::playerId() const
{
    return m_playerModel->playerId();
}

int PlayerViewModel::health() const
{
    return m_playerModel->health();
}

int PlayerViewModel::maxHealth() const
{
    return m_playerModel->maxHealth();
}

int PlayerViewModel::energy() const
{
    return m_playerModel->energy();
}

int PlayerViewModel::maxEnergy() const
{
    return m_playerModel->maxEnergy();
}

QPointF PlayerViewModel::position() const
{
    return m_playerModel->position();
}

bool PlayerViewModel::facingRight() const
{
    return m_playerModel->facingRight();
}

QString PlayerViewModel::currentAnimation() const
{
    return m_playerModel->currentAnimation();
}

double PlayerViewModel::healthPercentage() const
{
    if (maxHealth() == 0) return 0.0;
    return static_cast<double>(health()) / maxHealth();
}

double PlayerViewModel::energyPercentage() const
{
    if (maxEnergy() == 0) return 0.0;
    return static_cast<double>(energy()) / maxEnergy();
}

void PlayerViewModel::onHealthChanged()
{
    emit healthChanged();
}

void PlayerViewModel::onEnergyChanged()
{
    emit energyChanged();
}

void PlayerViewModel::onPositionChanged()
{
    emit positionChanged();
}

void PlayerViewModel::onFacingRightChanged()
{
    emit facingRightChanged();
}

void PlayerViewModel::onCurrentAnimationChanged()
{
    emit currentAnimationChanged();
}

void PlayerViewModel::onPlayerDied()
{
    emit playerDied();
} 