#pragma once
#include <array>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>

class ResultData {
public:
    double accuracy;
    int score;
    int maxCom;
    std::array<int, 5> targetPass;

    // 기본 생성자
    ResultData(double acc, int score, int maxCom, std::array<int, 5> target)
        : accuracy(acc), score(score), maxCom(maxCom), targetPass(target) {}
    ResultData()
        : accuracy(0.0), score(0), maxCom(0), targetPass{0,0,0,0,0} {}

    ~ResultData() {
    }
};

class Results {
public:
    std::vector<ResultData> results;

    void add(const ResultData& data) {
        results.push_back(data);
    }

    size_t size() const {
        return results.size();
    }

    ResultData& operator[](size_t index) {
        return results[index];
    }
};

namespace SaveResult {
    void results_serialize(const Results& results, const std::string& filepath);
    Results results_deserialize(const std::string& filepath);
    void SaveResult::saveToDirectory(const Results& results, const std::string& directory);
    Results SaveResult::loadFromDirectory(const std::string& directory);
}