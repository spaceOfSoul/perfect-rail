#include "utils.h"
std::string get_appdata_roaming_path() {
    char path[MAX_PATH];
    SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path);
    return std::string(path);
}

std::string getDirectoryPath(const std::string& filepath) {
    std::filesystem::path path(filepath);
    return path.parent_path().string();
}