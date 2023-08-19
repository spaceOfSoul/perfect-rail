#pragma once
#include <array>
#include <fstream>
#include <string>
#include <filesystem>

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

void serialize(const ResultData& data, const std::string& filepath);
ResultData deserialize(const std::string& filepath);
void saveToDirectory(const ResultData& data, const std::string& directory);
ResultData loadFromDirectory(const std::string& directory);