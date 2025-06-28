#pragma once

#include <QObject>

// 简单的物理控制器，目前物理计算直接在PlayerModel中进行
// 可以在后续扩展更复杂的物理系统
class PhysicsController : public QObject
{
    Q_OBJECT
    
public:
    explicit PhysicsController(QObject *parent = nullptr);
}; 