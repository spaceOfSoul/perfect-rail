#include "AudioManager.h"
#include <stdio.h>
#include <filesystem>

AudioManager::AudioManager() {}

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
        printf("Failed to load sound from %s\n", path.c_str());
    }
}


void AudioManager::PlaySound(const std::string& soundName) {
    if (sounds.find(soundName) != sounds.end()) {
        std::unique_ptr<sf::Sound>& sound = sounds[soundName];
        sound->setVolume(sound_volume);
        sound->play();
    }
    else {
        printf("Sound %s not found.\n", soundName.c_str());
    }
}

void AudioManager::StopSound(const std::string& soundName) {
    if (sounds.find(soundName) != sounds.end()) {
        sounds[soundName]->stop();
    }
    else {
        printf("Sound %s not found.\n", soundName);
    }
}

//music
void AudioManager::LoadMusic(const std::string& path) {
    std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();
    if (music->openFromFile(path)) {
        std::string name = std::filesystem::path(path).stem().string();
        musics[name] = std::move(music);
    }
    else {
        printf("Failed to load music from %s\n", path.c_str());
    }
}

void AudioManager::PlayMusic(const std::string& musicName) {
    if (musics.find(musicName) != musics.end()) {
        std::unique_ptr<sf::Music>& music = musics[musicName];
        music->setVolume(music_volume);
        music->play();
    }
    else {
        printf("Music %s not found.\n", musicName.c_str());
    }
}

void AudioManager::StopMusic(const std::string& musicName) {
    if (musics.find(musicName) != musics.end()) {
        musics[musicName]->stop();
    }
    else {
        printf("Music %s not found.\n", musicName);
    }
}

// Volume Setting
void AudioManager::SetSoundVolume(const std::string& soundName, float volume) {
    sound_volume = volume;
    if (sounds.find(soundName) != sounds.end()) {
        sounds[soundName]->setVolume(volume);
    }
    else {
        printf("Sound %s not found.\n", soundName);
    }
}

void AudioManager::SetMusicVolume(const std::string& musicName, float volume) {
    music_volume = volume;
    if (musics.find(musicName) != musics.end()) {
        musics[musicName]->setVolume(volume);
    }
    else {
        printf("Music %s not found.\n", musicName);
    }
}