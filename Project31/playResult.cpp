#include "playResult.h"

void SaveResult::results_serialize(const Results& results, const std::string& filepath) {
    std::ofstream out(filepath, std::ios::binary);
    if (!out.is_open()) {
        throw std::runtime_error("Failed to open file for writing");
    }

    size_t count = results.size();
    out.write((char*)&count, sizeof(count));

    for (const auto& data : results.results) {
        out.write((char*)&data.accuracy, sizeof(data.accuracy));
        out.write((char*)&data.score, sizeof(data.score));
        out.write((char*)&data.maxCom, sizeof(data.maxCom));
        for (int i = 0; i < 5; ++i) {
            out.write((char*)&data.targetPass[i], sizeof(data.targetPass[i]));
        }
    }

    out.close();
}

Results SaveResult::results_deserialize(const std::string& filepath) {
    std::ifstream in(filepath, std::ios::binary);
    if (!in.is_open()) {
        throw std::runtime_error("Failed to open file for reading");
    }

    Results results;
    size_t count;
    in.read((char*)&count, sizeof(count));

    for (size_t i = 0; i < count; ++i) {
        ResultData data;
        in.read((char*)&data.accuracy, sizeof(data.accuracy));
        in.read((char*)&data.score, sizeof(data.score));
        in.read((char*)&data.maxCom, sizeof(data.maxCom));
        for (int j = 0; j < 5; ++j) {
            in.read((char*)&data.targetPass[j], sizeof(data.targetPass[j]));
        }
        results.add(data);
    }

    in.close();

    return results;
}

void SaveResult::saveToDirectory(const Results& results, const std::string& directory) {
    std::filesystem::path dir(directory);
    if (!std::filesystem::exists(dir)) {
        std::filesystem::create_directories(dir);
    }

    std::string filepath = directory + "/data.bin";
    results_serialize(results, filepath);
}

Results SaveResult::loadFromDirectory(const std::string& directory) {
    std::string filepath = directory + "/data.bin";
    Results loadedResults;
    try
    {
        loadedResults = results_deserialize(filepath);
    }
    catch (const std::exception&)
    {
        printf("¸ø ºÒ·¯¿È!\n");
    }

    return loadedResults;
}
