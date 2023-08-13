#pragma once

#include <fstream>
#include <stdio.h>
#include <string>

struct Options {
	float music_volume;
	float sound_volume;
	double note_speed;
};

void saveOptionFile(const Options& option, const std::string& filename);

void loadOptionFromFile(Options&, const std::string& filename);