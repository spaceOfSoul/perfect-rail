#pragma once

#include <fstream>
#include <string>
#include <filesystem>
#include <iostream>

struct Options {
	float music_volume;
	float sound_volume;
	double note_speed;
	int val_y;
	int time_sync;
};

void saveOptionFile(const Options& option, const std::string& filename);
void loadOptionFromFile(Options&, const std::string& filename);
void initOptionSave(Options& option, const std::string& filename);