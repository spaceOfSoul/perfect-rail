#include "parse_data.h"

#include <iostream>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

std::string Trim(std::string& str)
{
	str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
	return str;
}

// note info
void note_info(std::string str, SongData& data)
{
	// Trim leading/trailing white space
	str = Trim(str);

	// Split the string into a vector of strings
	std::vector<std::string> tokens;
	std::istringstream ss(str);
	std::string buffer;
	while (std::getline(ss, buffer, ','))
	{
		tokens.push_back(Trim(buffer));
	}

	// Convert each string in the vector to an integer
	std::vector<int> row;
	for (const auto& token : tokens)
	{
		row.push_back(std::stoi(token));
	}

	int key = 0;
	switch (row[0])  // 0th value (key position)
	{
	case 64:
		key = 0;
		break;
	case 192:
		key = 1;
		break;
	case 320:
		key = 2;
		break;
	case 448:
		key = 3;
		break;
	}

	data.NotePoints[row[2]][key] = 1;     // Add note
	data.Last_Note_pos = row[2];          // Update last note position
	if (row[3] == 128) {             // Check if it's a long note (0: single note, 128: long note)
		for (int n = row[2]; n <= row[5]; n++) // Fill until the end of long note : up to row[5]
			data.ImagePoints[n][key] = 2;  // Fill long note
	}
	else
	{
		data.ImagePoints[row[2]][key] = 1; // Fill single note
	}
}



// ReadProperty
// ------------------------------------------------------------------------------------------
// General Section 읽기
void ReadProperty_General(std::string str, SongData &data)
{
	std::istringstream ss(str);
	std::string buffer;
	std::vector<std::string> tokens;

	while (std::getline(ss, buffer, ':'))
	{
		buffer = Trim(buffer); // Assuming Trim() function trims the string and returns it
		tokens.push_back(buffer);
	}

	if (tokens.size() > 1)
	{
		if (tokens[0] == "AudioFilename")
		{
			data.M_General.AudioFilename = tokens[1];
		}
		else if (tokens[0] == "AudioLeadIn")
		{
			data.M_General.AudioLeadIn = std::stoi(tokens[1]);
		}
		else if (tokens[0] == "PreviewTime")
		{
			data.M_General.PreviewTime = std::stoi(tokens[1]);
		}
		else if (tokens[0] == "Countdown")
		{
			data.M_General.Countdown = std::stoi(tokens[1]);
		}
		else if (tokens[0] == "StackLeniency")
		{
			data.M_General.StackLeniency = std::stof(tokens[1]);
		}
	}
}


// MetaData Section 읽기
void ReadProperty_MetaData(std::string str, SongData & data)
{
	std::istringstream ss(str); // 공백에 맞게 문자열을 분할
	std::string buffer;
	std::vector<std::string> tokens;

	while (std::getline(ss, buffer, ':'))
	{
		buffer = Trim(buffer);
		tokens.push_back(buffer);
	}

	// 토큰 처리(각 섹션에 맞게 정보를 파싱 )
	if (tokens[0] == "Title")
	{
		data.M_MetaData.Title = tokens[1];
	}
	else if (tokens[0] == "TitleUnicode")
	{
		data.M_MetaData.TitleUnicode = tokens[1];
	}
	else if (tokens[0] == "Artist")
	{
		data.M_MetaData.Artist = tokens[1];
	}
	else if (tokens[0] == "ArtistUnicode")
	{
		data.M_MetaData.ArtistUnicode = tokens[1];
	}
	else if (tokens[0] == "Creator")
	{
		data.M_MetaData.Creator = tokens[1];
	}
	else if (tokens[0] == "Version")
	{
		data.M_MetaData.Version = tokens[1];
	}
	else if (tokens[0] == "Source")
	{
		data.M_MetaData.Source = tokens[1];
	}
	else if (tokens[0] == "Tags")
	{
		data.M_MetaData.Tags = tokens[1];
	}
	else if (tokens[0] == "BeatmapID")
	{
		data.M_MetaData.BeatmapID = std::stoi(tokens[1]);
	}
	else if (tokens[0] == "BeatmapSetID")
	{
		data.M_MetaData.BeatmapSetID = std::stoi(tokens[1]);
	}
}


// Difficulty Section 읽기
void ReadProperty_Difficulty(std::string str, SongData &data)
{
	std::istringstream ss(str);
	std::string buffer;
	std::vector<std::string> tokens;

	while (std::getline(ss, buffer, ':'))
	{
		buffer = Trim(buffer);
		tokens.push_back(buffer);
	}

	// 토큰 처리...
	if (tokens[0] == "HPDrainRate")
	{
		data.M_Difficulty.HPDrainRate = std::stof(tokens[1]);
	}
	else if (tokens[0] == "CircleSize")
	{
		data.M_Difficulty.CircleSize = std::stof(tokens[1]);
	}
	else if (tokens[0] == "OverallDifficulty")
	{
		data.M_Difficulty.OverallDifficulty = std::stof(tokens[1]);
	}
	else if (tokens[0] == "ApproachRate")
	{
		data.M_Difficulty.ApproachRate = std::stof(tokens[1]);
	}
}


// TimingPoint Section 읽기
void ReadProperty_TimingPoint(std::string str, SongData &data)
{
	std::istringstream ss(str);
	std::string buffer;
	std::vector<std::string> tokens;

	while (std::getline(ss, buffer, ','))
	{
		buffer = Trim(buffer);
		tokens.push_back(buffer);
	}

	// 토큰 처리...
	if (tokens.size() >= 8)  // Ensure there are enough tokens
	{
		data.TimingPoints[data.TPoint_array_section].time = std::stoi(tokens[0]);
		data.TimingPoints[data.TPoint_array_section].meter = std::stoi(tokens[2]);
		data.TimingPoints[data.TPoint_array_section].Volume = std::stoi(tokens[5]);
		data.TimingPoints[data.TPoint_array_section].uninherited = std::stoi(tokens[6]);
		data.TimingPoints[data.TPoint_array_section].effects = std::stoi(tokens[7]);
		data.TimingPoints[data.TPoint_array_section].beatLength = std::stof(tokens[1]);
	}
	else
	{
		// Handle error: not enough tokens
	}

	data.TPoint_array_section++;
}



// ------------------------------------------------------------------------------------------
// 구역구별
void ReadLine_Check(std::string str, int section, SongData& data) {
	switch (section)
	{
	case S_GENERAL:
		ReadProperty_General(str, data);     // Basic settings
		break;
	case S_METADATA:
		ReadProperty_MetaData(str, data);    // Meta data (title, name, etc.)
		break;
	case S_DIFFICULTY:
		ReadProperty_Difficulty(str, data);  // Difficulty settings
		break;
	case S_TIMINGPOINT:
		ReadProperty_TimingPoint(str, data); // Timing settings
		break;
	case S_HOBJECT:
		note_info(str, data);                // Note settings
		break;
	default:
		// pass
		// Not applicable.
		// s_event, s_editor
		break;
	}
}

int LoadMapFile(std::string beatmap, SongData& data) // Load map file
{
	std::ifstream file(beatmap);
	if (file.is_open())
	{
		std::unordered_map<std::string, int> sectionMap = {
			{"[General]\n", S_GENERAL},
			{"[Editor]\n", S_EDITOR},
			{"[Metadata]\n", S_METADATA},
			{"[Difficulty]\n", S_DIFFICULTY},
			{"[Events]\n", S_EVENTS},
			{"[TimingPoints]\n", S_TIMINGPOINT},
			{"[HitObjects]\n", S_HOBJECT}
		};

		std::string strTemp;
		int section = 0;

		while (std::getline(file, strTemp))
		{
			auto sectionIt = sectionMap.find(strTemp);
			if (sectionIt != sectionMap.end()) // Section modification
			{
				section = sectionIt->second;
			}
			else  // Information processing
			{
				ReadLine_Check(strTemp, section, data);
			}
		}
		file.close();
		return 1;
	}
	else {
		return 0;
	}
}
