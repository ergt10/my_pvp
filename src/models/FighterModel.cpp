#include "FighterModel.h"

FighterModel::FighterModel(QObject *parent)
    : QObject(parent)
    , m_name("默认战士")
    , m_description("一个基础的格斗角色")
{
    initializeAttacks();
    loadSprites();
}

QStringList FighterModel::availableAttacks() const
{
    return QStringList() << m_lightAttack.name << m_heavyAttack.name << m_specialAttack.name;
}

QPixmap FighterModel::getSprite(const QString& animationName) const
{
    // 这里应该从资源管理器加载对应的精灵图片
    // 目前返回空，后续会在资源管理器中实现
    Q_UNUSED(animationName)
    return QPixmap();
}

QStringList FighterModel::getAnimationFrames(const QString& animationName) const
{
    // 返回动画帧列表
    if (animationName == "idle") {
        return QStringList() << "idle_01.png" << "idle_02.png" << "idle_03.png" << "idle_04.png";
    } else if (animationName == "walk") {
        return QStringList() << "walk_01.png" << "walk_02.png" << "walk_03.png" << "walk_04.png" << "walk_05.png" << "walk_06.png";
    } else if (animationName == "jump") {
        return QStringList() << "jump_01.png" << "jump_02.png" << "jump_03.png";
    } else if (animationName == "light_attack") {
        return QStringList() << "light_attack_01.png" << "light_attack_02.png" << "light_attack_03.png";
    } else if (animationName == "heavy_attack") {
        return QStringList() << "heavy_attack_01.png" << "heavy_attack_02.png" << "heavy_attack_03.png" << "heavy_attack_04.png";
    } else if (animationName == "special_attack") {
        return QStringList() << "special_attack_01.png" << "special_attack_02.png" << "special_attack_03.png" << "special_attack_04.png" << "special_attack_05.png";
    } else if (animationName == "block") {
        return QStringList() << "block_01.png";
    } else if (animationName == "crouch") {
        return QStringList() << "crouch_01.png";
    }
    
    return QStringList();
}

void FighterModel::initializeAttacks()
{
    // 轻攻击
    m_lightAttack.name = "轻拳";
    m_lightAttack.damage = 15;
    m_lightAttack.energyCost = 10;
    m_lightAttack.range = 50;
    m_lightAttack.animationName = "light_attack";
    
    // 重攻击
    m_heavyAttack.name = "重拳";
    m_heavyAttack.damage = 30;
    m_heavyAttack.energyCost = 25;
    m_heavyAttack.range = 60;
    m_heavyAttack.animationName = "heavy_attack";
    
    // 特殊攻击
    m_specialAttack.name = "必杀技";
    m_specialAttack.damage = 50;
    m_specialAttack.energyCost = 50;
    m_specialAttack.range = 100;
    m_specialAttack.animationName = "special_attack";
}

void FighterModel::loadSprites()
{
    // 这里会加载角色的精灵图片
    // 实际实现会在资源管理器中完成
} 