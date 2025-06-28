#pragma once

#include <QObject>

// 战斗角色视图模型 - 目前简化处理
class FighterViewModel : public QObject
{
    Q_OBJECT
    
public:
    explicit FighterViewModel(QObject *parent = nullptr);
}; 