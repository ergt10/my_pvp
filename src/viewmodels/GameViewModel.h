#pragma once

#include <QObject>
#include <QQmlEngine>
#include <memory>
#include "models/GameModel.h"
#include "controllers/InputController.h"
#include "controllers/PhysicsController.h"
#include "controllers/CollisionController.h"
#include "PlayerViewModel.h"

class GameViewModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    
    Q_PROPERTY(QString gameState READ gameState NOTIFY gameStateChanged)
    Q_PROPERTY(int timeRemaining READ timeRemaining NOTIFY timeRemainingChanged)
    Q_PROPERTY(PlayerViewModel* player1 READ player1 CONSTANT)
    Q_PROPERTY(PlayerViewModel* player2 READ player2 CONSTANT)
    Q_PROPERTY(bool isPaused READ isPaused NOTIFY isPausedChanged)
    
public:
    explicit GameViewModel(QObject *parent = nullptr);
    ~GameViewModel();
    
    // Properties
    QString gameState() const;
    int timeRemaining() const;
    PlayerViewModel* player1() const { return m_player1ViewModel.get(); }
    PlayerViewModel* player2() const { return m_player2ViewModel.get(); }
    bool isPaused() const;
    
    // Game actions - exposed to QML
    Q_INVOKABLE void startGame();
    Q_INVOKABLE void pauseGame();
    Q_INVOKABLE void resumeGame();
    Q_INVOKABLE void endGame();
    Q_INVOKABLE void resetGame();
    
    // Input handling - exposed to QML
    Q_INVOKABLE void handleKeyPress(int key);
    Q_INVOKABLE void handleKeyRelease(int key);
    
signals:
    void gameStateChanged();
    void timeRemainingChanged();
    void isPausedChanged();
    void gameEnded(int winnerId);
    void playerAttack(int playerId, const QString& attackType);
    
private slots:
    void onGameStateChanged();
    void onTimeRemainingChanged();
    void onGameEnded(int winnerId);
    void onPlayerAttack(int playerId, const QString& attackType);
    void updateCollisions();
    
private:
    std::unique_ptr<GameModel> m_gameModel;
    std::unique_ptr<PlayerViewModel> m_player1ViewModel;
    std::unique_ptr<PlayerViewModel> m_player2ViewModel;
    std::unique_ptr<InputController> m_inputController;
    std::unique_ptr<PhysicsController> m_physicsController;
    std::unique_ptr<CollisionController> m_collisionController;
    
    void initializeViewModels();
    void connectSignals();
    QString gameStateToString(GameState state) const;
}; 