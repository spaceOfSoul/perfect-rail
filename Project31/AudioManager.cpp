#include "AudioManager.h"
#include <filesystem>
#include <iostream>

AudioManager::AudioManager() :sm(SettingsManager::Instance()) {
    music_volume = sm.GetMusicVolume();
    sound_volume = sm.GetSoundVolume();
    audio_flag = 0x00;
}

//sound
void AudioManager::LoadSound(const std::string& path) {
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(path)) {
        std::string name = std::filesystem::path(path).stem().string();
        soundBuffers[name] = buffer;
        std::unique_ptr<sf::Sound> sound = std::make_unique<sf::Sound>();
        sound->setBuffer(soundBuffers[name]);
        sounds[name] = std::move(sound);
    }
    else {
        std::cerr << "Failed to load sound from" << path << std::endl;
    }
}


void AudioManager::PlayEventSound(const std::string& soundName) {
    sound_volume = sm.GetSoundVolume();
    if (sounds.find(soundName) != sounds.end()) {
        std::unique_ptr<sf::Sound>& sound = sounds[soundName];
        sound->setVolume(sound_volume);
        sound->play();
    }
    else {
        std::cerr << "Sound " << soundName << " not found.\n" << std::endl;
    }
}
void AudioManager::StopSound(const std::string& soundName) {
    if (sounds.find(soundName) != sounds.end()) {
        sounds[soundName]->stop();
    }
    else {
        std::cerr << "Sound " << soundName << " not found.\n";
    }
}

void AudioManager::LoadMusic(const std::string& musicName, const std::string& path) {
    if (!std::filesystem::exists(path)) {
        std::cerr << "Failed to load music from " << path << "\n";
        return;
    }

    musics[musicName] = path;
}

void AudioManager::PlayMusic(const std::string& musicName) {
    music_volume = sm.GetMusicVolume();
    current_music_name = musicName;

    if (musics.find(musicName) == musics.end()) {
        std::cerr << "Music " << musicName << " not found. Can't start.\n";
        return;
    }

    currentMusic = std::make_unique<sf::Music>();
    if (!currentMusic->openFromFile(musics[musicName])) {
        std::cerr << "Failed to open music file " << musics[musicName] << "\n";
        return;
    }
    currentMusic->setVolume(music_volume);
    currentMusic->play();

    audio_flag = 0x01; // 나중에 bit oper로 변경
}

void AudioManager::StopMusic(const std::string& musicName) {
    if (musics.find(musicName) == musics.end()) {
        std::cerr << "Music " << musicName << " not found. Can't stop.\n";
        return;
    }

    currentMusic->stop();
}

void AudioManager::SetMusicTime(sf::Time offset) {
    currentMusic->setPlayingOffset(offset);
}

void AudioManager::SetSoundVolume(const std::string& soundName, float volume) {
    sound_volume = volume;
    if (sounds.find(soundName) != sounds.end()) {
        sounds[soundName]->setVolume(volume);
    }
    else {
        std::cerr << "Sound " << soundName << " not found.\n";
    }
}


void AudioManager::SetMusicVolume(float volume) {
    music_volume = volume;
    if (currentMusic) {
        currentMusic->setVolume(volume);
    }
}

sf::Music& AudioManager::getMusic() {
    if (audio_flag == 0x00)
        throw std::runtime_error("music is not loaded");
    return *currentMusic;
}

sf::SoundSource::Status AudioManager::GetMusicStatus() const {
    return currentMusic->getStatus();
}

std::string AudioManager::getMusicName() {
    return current_music_name;
}