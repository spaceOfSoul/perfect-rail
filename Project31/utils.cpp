#include "utils.h"

std::string get_appdata_roaming_path() {
#ifdef _WIN32
    char path[MAX_PATH];
    SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path);
    return std::string(path);
#else
    const char* homeDir;

    if ((homeDir = getenv("HOME")) == NULL) {
        homeDir = getpwuid(getuid())->pw_dir;
    }

    return std::string(homeDir);
#endif
}

std::string getDirectoryPath(const std::string& filepath) {
    std::filesystem::path path(filepath);
    return path.parent_path().string();
}