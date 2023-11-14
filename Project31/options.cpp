#include "options.h"

#include <filesystem>

void saveOptionFile(const Options& option, const std::string& filename) {
    std::filesystem::path filePath(filename);
    std::filesystem::path dirPath = filePath.parent_path(); // Directory

    //해당 디렉토리가 존재하지 않을 경우 생성
    if (!std::filesystem::exists(dirPath)) {
        std::filesystem::create_directories(dirPath);
    }

    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        printf("Failed to open the file for writing.\n");
        return;
    }

    file.write((char*)(&option.music_volume), sizeof(option.music_volume));
    file.write((char*)(&option.sound_volume), sizeof(option.sound_volume));
    file.write((char*)(&option.note_speed), sizeof(option.note_speed));

    file.close();

    printf("Successed writing.\n");
}


void loadOptionFromFile(Options& option, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        printf("Failed to open file for reading\n");
        option.music_volume = 30.f;
        option.sound_volume = 30.f;
        option.note_speed = 600;

        saveOptionFile(option, filename);
    }

    printf("music volume(세이브 직후) :%f\n", option.music_volume);

    file.read((char*)(&option.music_volume), sizeof(option.music_volume));
    file.read((char*)(&option.sound_volume), sizeof(option.sound_volume));
    file.read((char*)(&option.note_speed), sizeof(option.note_speed));

    printf("option read\n");

    file.close();
}
