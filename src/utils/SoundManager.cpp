#include "SoundManager.h"
#include <QDebug>
#include <QUrl>

SoundManager& SoundManager::getInstance()
{
    static SoundManager instance;
    return instance;
}

SoundManager::SoundManager(QObject *parent)
    : QObject(parent)
    , m_initialized(false)
    , m_volume(1.0f)
    , m_musicPlayer(nullptr)
    , m_audioOutput(nullptr)
{
}

void SoundManager::initialize()
{
    if (m_initialized) {
        qWarning() << "SoundManager already initialized";
        return;
    }
    
    qDebug() << "初始化音效系统...";
    
    // 创建音频输出设备
    m_audioOutput = new QAudioOutput(this);
    m_audioOutput->setVolume(m_volume);
    
    // 创建音乐播放器
    m_musicPlayer = new QMediaPlayer(this);
    m_musicPlayer->setAudioOutput(m_audioOutput);
    
    // 设置循环播放
    m_musicPlayer->setLoops(QMediaPlayer::Infinite);
    
    m_initialized = true;
    qDebug() << "音效系统初始化完成";
}

void SoundManager::playSound(const QString& soundName)
{
    if (!m_initialized) return;
    
    qDebug() << "播放音效:" << soundName;
    // 实际播放音效的代码
}

void SoundManager::playMusic(const QString& musicName)
{
    if (!m_initialized || !m_musicPlayer) return;
    
    qDebug() << "播放音乐:" << musicName;
    
    // 构建资源URL
    QString resourcePath = "qrc:/assets/sounds/" + musicName;
    QUrl musicUrl(resourcePath);
    
    qDebug() << "音乐文件路径:" << resourcePath;
    
    // 设置音乐源并播放
    m_musicPlayer->setSource(musicUrl);
    m_musicPlayer->play();
}

void SoundManager::stopMusic()
{
    if (!m_initialized || !m_musicPlayer) return;
    
    qDebug() << "停止音乐";
    m_musicPlayer->stop();
}

void SoundManager::setVolume(float volume)
{
    m_volume = qBound(0.0f, volume, 1.0f);
    qDebug() << "设置音量为:" << m_volume;
    
    if (m_audioOutput) {
        m_audioOutput->setVolume(m_volume);
    }
} 