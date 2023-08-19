#include "playResult.h"

void serialize(const ResultData& data, const std::string& filepath) {
    std::ofstream out(filepath, std::ios::binary);
    if (!out.is_open()) {
        throw std::runtime_error("Failed to open file for writing");
    }

    out.write((char*)&data.accuracy, sizeof(data.accuracy));
    out.write((char*)&data.score, sizeof(data.score));
    out.write((char*)&data.maxCom, sizeof(data.maxCom));
    for (int i = 0; i < 5; ++i) {
        out.write((char*)&data.targetPass[i], sizeof(data.targetPass[i]));
    }

    out.close();
}

ResultData deserialize(const std::string& filepath) {
    std::ifstream in(filepath, std::ios::binary);
    if (!in.is_open()) {
        throw std::runtime_error("Failed to open file for reading");
    }

    ResultData data;
    in.read((char*)&data.accuracy, sizeof(data.accuracy));
    in.read((char*)&data.score, sizeof(data.score));
    in.read((char*)&data.maxCom, sizeof(data.maxCom));
    for (int i = 0; i < 5; ++i) {
        in.read((char*)&data.targetPass[i], sizeof(data.targetPass[i]));
    }

    in.close();

    return data;
}


void saveToDirectory(const ResultData& data, const std::string& directory) {
    std::filesystem::path dir(directory);
    if (!std::filesystem::exists(dir)) {
        std::filesystem::create_directories(dir);
    }

    std::string filepath = directory + "/data.bin";
    serialize(data, filepath);
}

ResultData loadFromDirectory(const std::string& directory) {
    std::string filepath = directory + "/data.bin";
    return deserialize(filepath);
}
