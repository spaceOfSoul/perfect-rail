#pragma once
#include <string>
#include <map>
#include <SFML/Audio.hpp>
#include <memory>

#include "SettingsManager.h"

class AudioManager {
public:
    // 이 오브젝트는 싱글톤 인스턴스로 쓸거임.
    static AudioManager& Instance() {
        static AudioManager instance;
        return instance;
    }
    void LoadSound(const std::string& path);
    void PlayEventSound(const std::string& soundName);
    void StopSound(const std::string& soundName);

    void LoadMusic(const std::string& musicName, const std::string& path);
    void PlayMusic(const std::string& musicName);
    void StopMusic(const std::string& musicName);

    void SetSoundVolume(const std::string& soundName, float volume);
    void SetMusicVolume(float volume);

    void SetMusicTime(sf::Time offsetTime);

    sf::SoundSource::Status GetMusicStatus() const;
    sf::Music& getMusic();
    std::string getMusicName();

private:
    AudioManager();

    SettingsManager& sm;

    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, std::unique_ptr<sf::Sound>> sounds;

    std::map<std::string, std::string> musics;

    std::unique_ptr<sf::Music> currentMusic;
    std::string current_music_name;

    float music_volume;
    float sound_volume;
    /*
        0 : music set
        1 : current music is exsist
        2 : sound play
    */
    uint8_t audio_flag;
};