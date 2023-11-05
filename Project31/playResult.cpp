#include "playResult.h"

//직렬화
void SaveResult::results_serialize(const Results& results, const std::string& filepath) {
    std::ofstream out(filepath, std::ios::binary);
    if (!out.is_open()) {
        throw std::runtime_error("Failed to open file for writing");
    }

    size_t count = results.size();
    out.write(reinterpret_cast<char*>(&count), sizeof(count));

    for (const auto& data : results.results) {
        // Serialize the 'username' string
        size_t username_length = data.username.size();
        out.write(reinterpret_cast<const char*>(&username_length), sizeof(username_length));
        out.write(data.username.data(), username_length);

        // Serialize other data members
        out.write(reinterpret_cast<const char*>(&data.accuracy), sizeof(data.accuracy));
        out.write(reinterpret_cast<const char*>(&data.score), sizeof(data.score));
        out.write(reinterpret_cast<const char*>(&data.maxCom), sizeof(data.maxCom));
        for (int i = 0; i < 5; ++i) {
            out.write(reinterpret_cast<const char*>(&data.targetPass[i]), sizeof(data.targetPass[i]));
        }
    }

    out.close();
}

// 역직렬화
Results SaveResult::results_deserialize(const std::string& filepath) {
    std::ifstream in(filepath, std::ios::binary);
    if (!in.is_open()) {
        throw std::runtime_error("Failed to open file for reading");
    }

    Results results;
    size_t count;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (size_t i = 0; i < count; ++i) {
        ResultData data;

        // Deserialize the 'username' string
        size_t username_length;
        in.read(reinterpret_cast<char*>(&username_length), sizeof(username_length));
        data.username.resize(username_length);
        in.read(&data.username[0], username_length);

        // Deserialize other data members
        in.read(reinterpret_cast<char*>(&data.accuracy), sizeof(data.accuracy));
        in.read(reinterpret_cast<char*>(&data.score), sizeof(data.score));
        in.read(reinterpret_cast<char*>(&data.maxCom), sizeof(data.maxCom));
        for (int j = 0; j < 5; ++j) {
            in.read(reinterpret_cast<char*>(&data.targetPass[j]), sizeof(data.targetPass[j]));
        }
        results.add(data);
    }

    in.close();

    return results;
}

// 저장
void SaveResult::saveToDirectory(const Results& results, const std::string& directory) {
    std::filesystem::path dir(directory);
    if (!std::filesystem::exists(dir)) {
        std::filesystem::create_directories(dir);
    }

    std::string filepath = directory + "/data.bin";
    results_serialize(results, filepath);
}

// 기록 로드
Results SaveResult::loadFromDirectory(const std::string& directory) {
    std::string filepath = directory + "/data.bin";
    Results loadedResults;
    try
    {
        loadedResults = results_deserialize(filepath);
    }
    catch (const std::exception&)
    {
        printf("못 불러옴!\n");
    }

    return loadedResults;
}
