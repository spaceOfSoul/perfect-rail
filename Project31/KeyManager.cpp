#include "KeysManager.h"
#include <fstream>
#include <iostream>

KeysManager::KeysManager() {
    // ¾Æ·¡´Â Default
    keyMap[0] = sf::Keyboard::S;
    keyMap[1] = sf::Keyboard::D;
    keyMap[2] = sf::Keyboard::L;
    keyMap[3] = sf::Keyboard::SemiColon;
    Load();
}

KeysManager& KeysManager::Instance() {
    static KeysManager instance;
    return instance;
}

sf::Keyboard::Key KeysManager::GetKey(int index) const {
    auto it = keyMap.find(index);
    if (it != keyMap.end()) {
        return it->second;
    }
    return sf::Keyboard::Unknown;
}

void KeysManager::SetKey(int index, sf::Keyboard::Key key) {
    keyMap[index] = key;
}

void KeysManager::Save() {
    saveKeyConfigToFile(keyConfigPath);
}

void KeysManager::Load() {
    loadKeyConfigFromFile(keyConfigPath);
}

void KeysManager::loadKeyConfigFromFile(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open key config file: " << path << std::endl;
        return;
    }

    int idx, keyVal;

    while (ifs >> idx >> keyVal) {
        if (keyVal >= sf::Keyboard::A && keyVal <= sf::Keyboard::KeyCount) {
            keyMap[idx] = static_cast<sf::Keyboard::Key>(keyVal);
        }
    }
    ifs.close();
}

void KeysManager::saveKeyConfigToFile(const std::string& path) {
    std::ofstream ofs(path);
    if (!ofs.is_open()) {
        std::cerr << "Failed to save key config file: " << path << std::endl;
        return;
    }
    for (auto& kv : keyMap) {
        ofs << kv.first << " " << (int)kv.second << "\n";
    }
    ofs.close();
}
