#pragma once
#include <string>
#include <map>
#include <SFML/Audio.hpp>
#include <memory>

class AudioManager {
public:
    // 이 오브젝트는 싱글톤 인스턴스로 쓸거임.
    static AudioManager& Instance() {
        static AudioManager instance;
        return instance;
    }
    void LoadSound(const std::string& path);
    void PlaySound(const std::string& soundName);
    void StopSound(const std::string& soundName);

    void LoadMusic(const std::string& musicName, const std::string& path);
    void PlayMusic(const std::string& musicName);
    void StopMusic(const std::string& musicName);
    void PlaySegmentMusic(const std::string& musicName, sf::Time start, sf::Time end);

    void SetSoundVolume(const std::string& soundName, float volume);
    void SetMusicVolume(const std::string& musicName, float volume);

    sf::Music& getMusic();

private:
    AudioManager();
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, std::unique_ptr<sf::Sound>> sounds;

    std::map<std::string, std::string> musics;

    std::unique_ptr<sf::Music> currentMusic;

    float music_volume = 30.f;
    float sound_volume = 30.f;
};
