#include "AudioManager.h"
#include <stdio.h>
#include <filesystem>

AudioManager::AudioManager():sm(SettingsManager::Instance()) {
    music_volume = sm.GetMusicVolume();
    sound_volume = sm.GetSoundVolume();
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
        printf("Failed to load sound from %s\n", path.c_str());
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
        printf("Sound %s not found.\n", soundName.c_str());
    }
}

void AudioManager::StopSound(const std::string& soundName) {
    if (sounds.find(soundName) != sounds.end()) {
        sounds[soundName]->stop();
    }
    else {
        printf("Sound %s not found.\n", soundName.c_str());
    }
}

//music
void AudioManager::LoadMusic(const std::string& musicName, const std::string& path) {
    if (!std::filesystem::exists(path)) {
        printf("Failed to load music from %s\n", path.c_str());
        return;
    }

    musics[musicName] = path;
}

void AudioManager::PlayMusic(const std::string& musicName) {
    music_volume = sm.GetMusicVolume();
    if (musics.find(musicName) == musics.end()) {
        printf("Music %s not found. Can't start.\n", musicName.c_str());
        return;
    }

    currentMusic = std::make_unique<sf::Music>();
    if (!currentMusic->openFromFile(musics[musicName])) {
        printf("Failed to open music file %s\n", musics[musicName].c_str());
        return;
    }
    currentMusic->setVolume(music_volume);
    currentMusic->play();
}

void AudioManager::StopMusic(const std::string& musicName) {
    if (musics.find(musicName) == musics.end()) {
        printf("Music %s not found. Can't stop.\n", musicName.c_str());
        return;
    }

    currentMusic->stop();
}


// Volume Setting
void AudioManager::SetSoundVolume(const std::string& soundName, float volume) {
    sound_volume = volume;
    if (sounds.find(soundName) != sounds.end()) {
        sounds[soundName]->setVolume(volume);
    }
    else {
        printf("Sound %s not found.\n", soundName.c_str());
    }
}

void AudioManager::SetMusicVolume(const std::string& musicName, float volume) {
    music_volume = volume;
    if (currentMusic) {
        currentMusic->setVolume(volume);
    }
}

sf::Music& AudioManager::getMusic() {
    return *currentMusic;
}

sf::SoundSource::Status AudioManager::GetMusicStatus() const {
    return currentMusic->getStatus();
}