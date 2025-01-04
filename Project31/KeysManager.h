#pragma once
#include <map>
#include <string>
#include <SFML/Window/Keyboard.hpp>

class KeysManager {
private:
    KeysManager();
    ~KeysManager() {}
    KeysManager(const KeysManager&) = delete;
    KeysManager& operator=(const KeysManager&) = delete;

    std::map<int, sf::Keyboard::Key> keyMap;

    // 키 설정 파일 경로
    std::string keyConfigPath;

    void loadKeyConfigFromFile(const std::string& path);
    void saveKeyConfigToFile(const std::string& path);

public:
    static KeysManager& Instance();

    sf::Keyboard::Key GetKey(int index) const;
    void SetKey(int index, sf::Keyboard::Key key);

    void Save();
    void Load();
};
