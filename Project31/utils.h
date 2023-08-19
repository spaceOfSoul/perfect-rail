#pragma once
#ifdef _WIN32  // Windows ȯ��
#include <windows.h>
#include <shlobj.h>
#include <string>

std::string get_appdata_roaming_path();
#endif
// �������� �ϴ� ��� ����.

#include <filesystem>

std::string getDirectoryPath(const std::string& filepath) {
    std::filesystem::path path(filepath);
    return path.parent_path().string();
}