#pragma once
#ifdef _WIN32 // ������
#include <windows.h>
#include <shlobj.h>
#else // ������
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

#include <filesystem>
std::string get_appdata_roaming_path();
std::string getDirectoryPath(const std::string& filepath);