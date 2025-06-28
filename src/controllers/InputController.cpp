#include "InputController.h"
#include <QDebug>

InputController::InputController(QObject *parent)
    : QObject(parent)
{
}

void InputController::handleKeyPress(int key, PlayerModel* player1, PlayerModel* player2)
{
    if (m_pressedKeys.contains(key)) {
        return; // 防止重复按键
    }
    
    m_pressedKeys.insert(key);
    
    handlePlayer1Input(key, true, player1);
    handlePlayer2Input(key, true, player2);
}

void InputController::handleKeyRelease(int key, PlayerModel* player1, PlayerModel* player2)
{
    m_pressedKeys.remove(key);
    
    handlePlayer1Input(key, false, player1);
    handlePlayer2Input(key, false, player2);
}

void InputController::handlePlayer1Input(int key, bool pressed, PlayerModel* player)
{
    if (!player) return;
    
    if (pressed) {
        switch (key) {
            case PLAYER1_LEFT:
                player->moveLeft();
                break;
            case PLAYER1_RIGHT:
                player->moveRight();
                break;
            case PLAYER1_UP:
                player->jump();
                break;
            case PLAYER1_DOWN:
                player->crouch();
                break;
            case PLAYER1_LIGHT_ATTACK:
                player->lightAttack();
                break;
            case PLAYER1_HEAVY_ATTACK:
                player->heavyAttack();
                break;
            case PLAYER1_SPECIAL_ATTACK:
                player->specialAttack();
                break;
            case PLAYER1_BLOCK:
                player->block();
                break;
        }
    } else {
        switch (key) {
            case PLAYER1_LEFT:
            case PLAYER1_RIGHT:
            case PLAYER1_DOWN:
                if (!m_pressedKeys.contains(PLAYER1_LEFT) && 
                    !m_pressedKeys.contains(PLAYER1_RIGHT) &&
                    !m_pressedKeys.contains(PLAYER1_DOWN)) {
                    player->stopMoving();
                }
                break;
            case PLAYER1_BLOCK:
                player->stopBlocking();
                break;
        }
    }
}

void InputController::handlePlayer2Input(int key, bool pressed, PlayerModel* player)
{
    if (!player) return;
    
    if (pressed) {
        switch (key) {
            case PLAYER2_LEFT:
                player->moveLeft();
                break;
            case PLAYER2_RIGHT:
                player->moveRight();
                break;
            case PLAYER2_UP:
                player->jump();
                break;
            case PLAYER2_DOWN:
                player->crouch();
                break;
            case PLAYER2_LIGHT_ATTACK:
                player->lightAttack();
                break;
            case PLAYER2_HEAVY_ATTACK:
                player->heavyAttack();
                break;
            case PLAYER2_SPECIAL_ATTACK:
                player->specialAttack();
                break;
            case PLAYER2_BLOCK:
                player->block();
                break;
        }
    } else {
        switch (key) {
            case PLAYER2_LEFT:
            case PLAYER2_RIGHT:
            case PLAYER2_DOWN:
                if (!m_pressedKeys.contains(PLAYER2_LEFT) && 
                    !m_pressedKeys.contains(PLAYER2_RIGHT) &&
                    !m_pressedKeys.contains(PLAYER2_DOWN)) {
                    player->stopMoving();
                }
                break;
            case PLAYER2_BLOCK:
                player->stopBlocking();
                break;
        }
    }
} 