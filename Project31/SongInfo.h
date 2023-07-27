#pragma once
#include <string>
#include <vector>
struct SongInfo {
    std::string songNameStr;
    std::string imagePath;
    std::string songPath;
    std::vector<int> difficultiesExist;
};