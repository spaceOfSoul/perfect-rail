#pragma once
#ifdef _WIN32  // Windows 환경
#include <windows.h>
#include <shlobj.h>
#include <string>

std::string get_appdata_roaming_path();
#endif
// 리눅스는 일단 고려 안함.

#include <filesystem>

std::string getDirectoryPath(const std::string& filepath) {
    std::filesystem::path path(filepath);
    return path.parent_path().string();
}