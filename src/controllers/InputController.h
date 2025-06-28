#pragma once

#include <QObject>
#include <QKeyEvent>
#include <QSet>
#include "models/PlayerModel.h"

class InputController : public QObject
{
    Q_OBJECT
    
public:
    explicit InputController(QObject *parent = nullptr);
    
    void handleKeyPress(int key, PlayerModel* player1, PlayerModel* player2);
    void handleKeyRelease(int key, PlayerModel* player1, PlayerModel* player2);
    
private:
    QSet<int> m_pressedKeys;
    
    // Player 1 控制 (WASD + JKL)
    static constexpr int PLAYER1_LEFT = Qt::Key_A;
    static constexpr int PLAYER1_RIGHT = Qt::Key_D;
    static constexpr int PLAYER1_UP = Qt::Key_W;
    static constexpr int PLAYER1_DOWN = Qt::Key_S;
    static constexpr int PLAYER1_LIGHT_ATTACK = Qt::Key_J;
    static constexpr int PLAYER1_HEAVY_ATTACK = Qt::Key_K;
    static constexpr int PLAYER1_SPECIAL_ATTACK = Qt::Key_L;
    static constexpr int PLAYER1_BLOCK = Qt::Key_U;
    
    // Player 2 控制 (方向键 + 数字键盘)
    static constexpr int PLAYER2_LEFT = Qt::Key_Left;
    static constexpr int PLAYER2_RIGHT = Qt::Key_Right;
    static constexpr int PLAYER2_UP = Qt::Key_Up;
    static constexpr int PLAYER2_DOWN = Qt::Key_Down;
    static constexpr int PLAYER2_LIGHT_ATTACK = Qt::Key_1;
    static constexpr int PLAYER2_HEAVY_ATTACK = Qt::Key_2;
    static constexpr int PLAYER2_SPECIAL_ATTACK = Qt::Key_3;
    static constexpr int PLAYER2_BLOCK = Qt::Key_0;
    
    void handlePlayer1Input(int key, bool pressed, PlayerModel* player);
    void handlePlayer2Input(int key, bool pressed, PlayerModel* player);
}; 