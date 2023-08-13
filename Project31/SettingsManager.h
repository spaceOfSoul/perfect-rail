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
		return get_appdata_roaming_path().append("perfectRail\\setting.bin");
	}

	float GetMusicVolume() const;
	float GetSoundVolume() const;
	float GetNoteSpeed() const;

	void SetMusicVolume(float vol);
	void SetSoundVolume(float vol);
	void SetNoteSpeed(float speed);

	void saveOption();
};
