#pragma once

#include <fstream>
#include <string>
#include <filesystem>
#include <iostream>
#include <SFML/Graphics.hpp>

struct Options {
	float music_volume;
	float sound_volume;
	double note_speed;
	int val_y;
	int time_sync;
	sf::Keyboard::Key keys[4];
};

void saveOptionFile(const Options& option, const std::string& filename);
void loadOptionFromFile(Options&, const std::string& filename);
void initOptionSave(Options& option, const std::string& filename);