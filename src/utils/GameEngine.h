#pragma once

#include <QObject>

class GameEngine : public QObject
{
    Q_OBJECT
    
public:
    static GameEngine& getInstance();
    
    void initialize();
    void shutdown();
    
private:
    explicit GameEngine(QObject *parent = nullptr);
    ~GameEngine() = default;
    
    GameEngine(const GameEngine&) = delete;
    GameEngine& operator=(const GameEngine&) = delete;
    
    bool m_initialized;
}; 