#pragma once
#ifdef _WIN32  // Windows ȯ��
#include <windows.h>
#include <shlobj.h>
#include <string>

std::string get_appdata_roaming_path();
#endif
// �������� �ϴ� ��� ����.