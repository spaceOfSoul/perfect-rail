#include "SettingsManager.h"

SettingsManager::SettingsManager() {
	printf("Generate Setting manager\n");
	loadOptionFromFile(options, OPTIONFILE_PATH());
}

SettingsManager& SettingsManager::Instance() {
	static SettingsManager instance;
	return instance;
}

// Getters
float SettingsManager::GetMusicVolume() const {
	return options.music_volume;
}

float SettingsManager::GetSoundVolume() const {
	return options.sound_volume;
}

float SettingsManager::GetNoteSpeed() const {
	return options.note_speed;
}

int SettingsManager::GetJudgeLine_Y() const {
	return options.val_y;
}

int SettingsManager::GetTimeSync() const {
	return options.time_sync;
}

// Setters
void SettingsManager::SetMusicVolume(float vol) {
	options.music_volume = vol;
}

void SettingsManager::SetSoundVolume(float vol) {
	options.sound_volume = vol;
}

void SettingsManager::SetNoteSpeed(float speed) {
	options.note_speed = speed;
}

void SettingsManager::SetJudgeLine_Y(int y) {
	options.val_y = y;
}

void SettingsManager::SetTimeSync(int sync) {
	options.time_sync = sync;
}

void SettingsManager::saveOption() {
	saveOptionFile(options, OPTIONFILE_PATH());
}
