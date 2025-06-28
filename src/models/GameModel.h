#pragma once

#include <QObject>
#include <QTimer>
#include <memory>
#include "PlayerModel.h"

enum class GameState {
    Menu,
    Fighting,
    Paused,
    GameOver
};

class GameModel : public QObject
{
    Q_OBJECT
    
public:
    explicit GameModel(QObject *parent = nullptr);
    ~GameModel();
    
    // Getters
    GameState state() const { return m_state; }
    PlayerModel* player1() const { return m_player1.get(); }
    PlayerModel* player2() const { return m_player2.get(); }
    int timeRemaining() const { return m_timeRemaining; }
    bool isPaused() const { return m_isPaused; }
    
    // Game actions
    void startGame();
    void pauseGame();
    void resumeGame();
    void endGame();
    void resetGame();
    
signals:
    void stateChanged();
    void timeRemainingChanged();
    void gameEnded(int winnerId);
    
private slots:
    void updateGame();
    void onTimerTick();
    
private:
    GameState m_state;
    std::unique_ptr<PlayerModel> m_player1;
    std::unique_ptr<PlayerModel> m_player2;
    QTimer* m_gameTimer;
    QTimer* m_roundTimer;
    int m_timeRemaining;
    bool m_isPaused;
    
    void initializePlayers();
    void checkWinConditions();
}; 