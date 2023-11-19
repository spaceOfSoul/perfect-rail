#include "options.h"

#include <filesystem>

void saveOptionFile(const Options& option, const std::string& filename) {
    std::filesystem::path filePath(filename);
    std::filesystem::path dirPath = filePath.parent_path(); // Directory

    //�ش� ���丮�� �������� ���� ��� ����
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
    file.write((char*)(&option.val_y), sizeof(option.val_y));
    file.write((char*)(&option.time_sync), sizeof(option.time_sync));

    file.close();

    printf("Successed writing.\n");
}

void loadOptionFromFile(Options& option, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        printf("Failed to open file for reading\n");
        initOptionSave(option, filename);
    }
    printf("music volume(���̺� ����) :%f\n", option.music_volume);

    // ���� ������ üũ
    file.seekg(0, std::ios::end); // �����͸� ios::end, �� ������ ������ �̵�
    size_t fileSize = file.tellg();
    size_t expectedSize = sizeof(Options);
    file.seekg(0, std::ios::beg); // �����͸� ios::beging, �� ������ �������� �̵�

    if (fileSize < expectedSize) {
        file.close();
        remove(filename.c_str());// delete the file

        initOptionSave(option, filename);
        printf("Old setting file. new file create.\n");
    }
    else {
        // read the settings
        file.read((char*)(&option.music_volume), sizeof(option.music_volume));
        file.read((char*)(&option.sound_volume), sizeof(option.sound_volume));
        file.read((char*)(&option.note_speed), sizeof(option.note_speed));
        file.read((char*)(&option.val_y), sizeof(option.val_y));
        file.read((char*)(&option.time_sync), sizeof(option.time_sync));

        printf("Options loaded successfully\n");
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