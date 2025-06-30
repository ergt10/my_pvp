#include "GameViewModel.h"
#include "PlayerViewModel.h"
#include <QDebug>

GameViewModel::GameViewModel(QObject *parent)
    : QObject(parent)
{
    m_gameModel = std::make_unique<GameModel>(this);
    m_inputController = std::make_unique<InputController>(this);
    m_physicsController = std::make_unique<PhysicsController>(this);
    m_collisionController = std::make_unique<CollisionController>(this);
    
    initializeViewModels();
    connectSignals();
}

GameViewModel::~GameViewModel() = default;

QString GameViewModel::gameState() const
{
    return gameStateToString(m_gameModel->state());
}

int GameViewModel::timeRemaining() const
{
    return m_gameModel->timeRemaining();
}

bool GameViewModel::isPaused() const
{
    return m_gameModel->isPaused();
}

void GameViewModel::startGame()
{
    qDebug() << "GameViewModel: 开始游戏";
    m_gameModel->startGame();
}

void GameViewModel::pauseGame()
{
    qDebug() << "GameViewModel: 暂停游戏";
    m_gameModel->pauseGame();
}

void GameViewModel::resumeGame()
{
    qDebug() << "GameViewModel: 恢复游戏";
    m_gameModel->resumeGame();
}

void GameViewModel::endGame()
{
    qDebug() << "GameViewModel: 结束游戏";
    m_gameModel->endGame();
}

void GameViewModel::resetGame()
{
    qDebug() << "GameViewModel: 重置游戏";
    m_gameModel->resetGame();
}

void GameViewModel::handleKeyPress(int key)
{
    if (!m_gameModel || !m_gameModel->player1() || !m_gameModel->player2()) {
        qWarning() << "GameViewModel::handleKeyPress - 玩家对象为空";
        return;
    }
    
    m_inputController->handleKeyPress(key, m_gameModel->player1(), m_gameModel->player2());
}

void GameViewModel::handleKeyRelease(int key)
{
    if (!m_gameModel || !m_gameModel->player1() || !m_gameModel->player2()) {
        qWarning() << "GameViewModel::handleKeyRelease - 玩家对象为空";
        return;
    }
    
    m_inputController->handleKeyRelease(key, m_gameModel->player1(), m_gameModel->player2());
}

void GameViewModel::initializeViewModels()
{
    m_player1ViewModel = std::make_unique<PlayerViewModel>(m_gameModel->player1(), this);
    m_player2ViewModel = std::make_unique<PlayerViewModel>(m_gameModel->player2(), this);
}

void GameViewModel::connectSignals()
{
    // Connect game model signals
    connect(m_gameModel.get(), &GameModel::stateChanged, 
            this, &GameViewModel::onGameStateChanged);
    connect(m_gameModel.get(), &GameModel::timeRemainingChanged, 
            this, &GameViewModel::onTimeRemainingChanged);
    connect(m_gameModel.get(), &GameModel::gameEnded, 
            this, &GameViewModel::onGameEnded);
    
    // Connect player signals
    connect(m_gameModel->player1(), &PlayerModel::attackPerformed,
            [this](const QString& attackType) {
                onPlayerAttack(1, attackType);
            });
    connect(m_gameModel->player2(), &PlayerModel::attackPerformed,
            [this](const QString& attackType) {
                onPlayerAttack(2, attackType);
            });
    
    // Set up collision detection
    connect(m_gameModel.get(), &GameModel::stateChanged, 
            this, &GameViewModel::updateCollisions);
}

void GameViewModel::onGameStateChanged()
{
    emit gameStateChanged();
    emit isPausedChanged();
}

void GameViewModel::onTimeRemainingChanged()
{
    emit timeRemainingChanged();
}

void GameViewModel::onGameEnded(int winnerId)
{
    qDebug() << "游戏结束，获胜者:" << winnerId;
    emit gameEnded(winnerId);
}

void GameViewModel::onPlayerAttack(int playerId, const QString& attackType)
{
    qDebug() << "玩家" << playerId << "执行攻击:" << attackType;
    emit playerAttack(playerId, attackType);
    
    // 检查碰撞并处理伤害
    m_collisionController->checkAttackCollision(
        m_gameModel->player1(), 
        m_gameModel->player2(),
        playerId,
        attackType
    );
}

void GameViewModel::updateCollisions()
{
    if (m_gameModel->state() == GameState::Fighting) {
        m_collisionController->updateCollisions(
            m_gameModel->player1(),
            m_gameModel->player2()
        );
    }
}

QString GameViewModel::gameStateToString(GameState state) const
{
    switch (state) {
        case GameState::Menu: return "menu";
        case GameState::Fighting: return "fighting";
        case GameState::Paused: return "paused";
        case GameState::GameOver: return "gameOver";
        default: return "unknown";
    }
} 