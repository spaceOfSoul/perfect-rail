#include "options.h"

void saveOptionFile(const Options& option, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        printf("Failed to open the file for writting.\n");
        return;
    }

    file.write(reinterpret_cast<const char*>(&option.music_volume), sizeof(option.music_volume));
    file.write(reinterpret_cast<const char*>(&option.sound_volume), sizeof(option.sound_volume));
    file.write(reinterpret_cast<const char*>(&option.note_speed), sizeof(option.note_speed));

    file.close();
}

void loadOptionFromFile(Options& option, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        printf("Failed to open file for reading\n");
        option.music_volume = 30.f;
        option.sound_volume = 30.f;
        option.note_speed = 1100;

        saveOptionFile(option, filename);
    }

    Options options;

    file.read(reinterpret_cast<char*>(&options.music_volume), sizeof(options.music_volume));
    file.read(reinterpret_cast<char*>(&options.sound_volume), sizeof(options.sound_volume));
    file.read(reinterpret_cast<char*>(&options.note_speed), sizeof(options.note_speed));

    option = options;

    file.close();
}
