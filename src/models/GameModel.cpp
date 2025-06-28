#include "GameModel.h"
#include <QDebug>

GameModel::GameModel(QObject *parent)
    : QObject(parent)
    , m_state(GameState::Menu)
    , m_timeRemaining(99)
    , m_isPaused(false)
{
    m_gameTimer = new QTimer(this);
    m_roundTimer = new QTimer(this);
    
    connect(m_gameTimer, &QTimer::timeout, this, &GameModel::updateGame);
    connect(m_roundTimer, &QTimer::timeout, this, &GameModel::onTimerTick);
    
    initializePlayers();
}

GameModel::~GameModel() = default;

void GameModel::initializePlayers()
{
    m_player1 = std::make_unique<PlayerModel>(1, this);
    m_player2 = std::make_unique<PlayerModel>(2, this);
    
    // 设置玩家初始位置
    m_player1->setPosition(QPointF(200, 400));
    m_player2->setPosition(QPointF(600, 400));
    
    // 玩家面向对方
    m_player1->setFacingRight(true);
    m_player2->setFacingRight(false);
}

void GameModel::startGame()
{
    if (m_state != GameState::Menu) return;
    
    m_state = GameState::Fighting;
    m_timeRemaining = 99;
    m_isPaused = false;
    
    // 重置玩家状态
    m_player1->reset();
    m_player2->reset();
    
    // 启动游戏循环
    m_gameTimer->start(16); // 60 FPS
    m_roundTimer->start(1000); // 1秒倒计时
    
    emit stateChanged();
    qDebug() << "游戏开始！";
}

void GameModel::pauseGame()
{
    if (m_state != GameState::Fighting) return;
    
    m_isPaused = true;
    m_gameTimer->stop();
    m_roundTimer->stop();
    
    m_state = GameState::Paused;
    emit stateChanged();
}

void GameModel::resumeGame()
{
    if (m_state != GameState::Paused) return;
    
    m_isPaused = false;
    m_gameTimer->start(16);
    m_roundTimer->start(1000);
    
    m_state = GameState::Fighting;
    emit stateChanged();
}

void GameModel::endGame()
{
    m_gameTimer->stop();
    m_roundTimer->stop();
    m_state = GameState::GameOver;
    
    emit stateChanged();
}

void GameModel::resetGame()
{
    endGame();
    m_state = GameState::Menu;
    initializePlayers();
    emit stateChanged();
}

void GameModel::updateGame()
{
    if (m_isPaused) return;
    
    // 更新玩家状态
    m_player1->update();
    m_player2->update();
    
    // 检查胜负条件
    checkWinConditions();
}

void GameModel::onTimerTick()
{
    if (m_timeRemaining > 0) {
        m_timeRemaining--;
        emit timeRemainingChanged();
    } else {
        // 时间到，判断胜负
        checkWinConditions();
    }
}

void GameModel::checkWinConditions()
{
    // 检查是否有玩家血量归零或时间到
    bool player1Dead = m_player1->health() <= 0;
    bool player2Dead = m_player2->health() <= 0;
    bool timeUp = m_timeRemaining <= 0;
    
    if (player1Dead || player2Dead || timeUp) {
        int winnerId = 0;
        
        if (player1Dead && !player2Dead) {
            winnerId = 2;
        } else if (player2Dead && !player1Dead) {
            winnerId = 1;
        } else if (timeUp) {
            // 根据血量判断胜负
            winnerId = (m_player1->health() > m_player2->health()) ? 1 : 2;
        }
        
        endGame();
        emit gameEnded(winnerId);
    }
} 