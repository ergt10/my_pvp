#pragma once

#include <QObject>

// 游戏总控制器，协调各个子系统
class GameController : public QObject
{
    Q_OBJECT
    
public:
    explicit GameController(QObject *parent = nullptr);
    
    void initialize();
    void shutdown();
    
private:
    bool m_initialized;
}; 