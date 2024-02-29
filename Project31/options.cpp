#include "options.h"


void saveOptionFile(const Options& option, const std::string& filename) {
    std::filesystem::path filePath(filename);
    std::filesystem::path dirPath = filePath.parent_path(); // Directory

    //해당 디렉토리가 존재하지 않을 경우 생성
    if (!std::filesystem::exists(dirPath)) {
        std::filesystem::create_directories(dirPath);
    }

    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open the file for writing." << std:: endl;
        return;
    }

    file.write((char*)(&option.music_volume), sizeof(option.music_volume));
    file.write((char*)(&option.sound_volume), sizeof(option.sound_volume));
    file.write((char*)(&option.note_speed), sizeof(option.note_speed));
    file.write((char*)(&option.val_y), sizeof(option.val_y));
    file.write((char*)(&option.time_sync), sizeof(option.time_sync));

    file.close();

    std::cerr << "Successed writing." << std::endl;
}

void loadOptionFromFile(Options& option, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file for reading" << std::endl;
        initOptionSave(option, filename);
    }
    std::cerr << "music volume(세이브 직후)" << option.music_volume << std::endl;

    // 파일 사이즈 체크
    file.seekg(0, std::ios::end); // 포인터를 ios::end, 즉 파일의 끝으로 이동
    size_t fileSize = file.tellg();
    size_t expectedSize = sizeof(Options);
    file.seekg(0, std::ios::beg); // 포인터를 ios::beging, 즉 파일의 시작으로 이동

    if (fileSize < expectedSize) {
        file.close();
        remove(filename.c_str());// delete the file

        initOptionSave(option, filename);
        std::cerr << "Old setting file. new file create." << std::endl;
    }
    else {
        // read the settings
        file.read((char*)(&option.music_volume), sizeof(option.music_volume));
        file.read((char*)(&option.sound_volume), sizeof(option.sound_volume));
        file.read((char*)(&option.note_speed), sizeof(option.note_speed));
        file.read((char*)(&option.val_y), sizeof(option.val_y));
        file.read((char*)(&option.time_sync), sizeof(option.time_sync));

        std::cerr << "Options loaded successfully" << std::endl;
        file.close();
    }
}

void initOptionSave(Options& option, const std::string& filename) {
    option.music_volume = 30.f;
    option.sound_volume = 30.f;
    option.note_speed = 650;
    option.val_y = 0;
    option.time_sync = 0;

    saveOptionFile(option, filename);
}