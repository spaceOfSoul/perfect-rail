#pragma once
#include "options.h"
#include "utils.h"

class SettingsManager
{
private:
	Options options;

	SettingsManager();

public:
	static SettingsManager& Instance();

	static inline std::string OPTIONFILE_PATH() {
#ifdef _WIN32
		return get_appdata_roaming_path().append("\\perfectRail\\setting.bin");
#else
		return get_appdata_roaming_path().append("/perfectRail/setting.bin");
#endif
	}

	float GetMusicVolume() const;
	float GetSoundVolume() const;
	float GetNoteSpeed() const;
	int GetJudgeLine_Y() const;
	int GetTimeSync() const;

	void SetMusicVolume(float vol);
	void SetSoundVolume(float vol);
	void SetNoteSpeed(float speed);
	void SetJudgeLine_Y(int y);
	void SetTimeSync(int sync); 

	void saveOption();
};
