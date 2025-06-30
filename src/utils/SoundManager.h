#pragma once

#include <QObject>
#include <QString>
#include <QMediaPlayer>
#include <QAudioOutput>

// 简单的音效管理器占位符
// 后续可以扩展为完整的音频系统
class SoundManager : public QObject
{
    Q_OBJECT
    
public:
    static SoundManager& getInstance();
    
    void initialize();
    void playSound(const QString& soundName);
    void playMusic(const QString& musicName);
    void stopMusic();
    void setVolume(float volume);
    
private:
    explicit SoundManager(QObject *parent = nullptr);
    ~SoundManager() = default;
    
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;
    
    bool m_initialized;
    float m_volume;
    
    QMediaPlayer* m_musicPlayer;
    QAudioOutput* m_audioOutput;
}; 