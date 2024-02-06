#pragma once
#ifdef _WIN32 // 윈도우
#include <windows.h>
#include <shlobj.h>
#else // 리눅스
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

#include <filesystem>
std::string get_appdata_roaming_path();
std::string getDirectoryPath(const std::string& filepath);