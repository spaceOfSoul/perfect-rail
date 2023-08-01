#pragma once
#include <string>
#include <vector>
#include <array>

#define S_GENERAL 1
#define S_EDITOR 2
#define S_METADATA 3
#define S_DIFFICULTY 4
#define S_EVENTS 5
#define S_TIMINGPOINT 6
#define S_HOBJECT 7

#define MAX_TSTAMP 300000
#define M_ROW 4
#define MAX_PSTAMP 2000

struct General_Set {
    std::string AudioFilename;
    int AudioLeadIn;
    int PreviewTime;
    int Countdown;
    float StackLeniency;
};

struct MetaData_Set {
    std::string Title;
    std::string TitleUnicode;
    std::string Artist;
    std::string ArtistUnicode;
    std::string Creator;
    std::string Version;
    std::string Source;
    std::string Tags;
    int BeatmapID;
    int BeatmapSetID;
};

struct Difficulty_Set {
    float HPDrainRate;
    int CircleSize;
    float OverallDifficulty;
    int ApproachRate;
};

struct TimingPoint_Set {
    int time;
    double beatLength;
    int meter;
    int Volume;
    bool uninherited;
    int effects;
};

struct SongData {
    General_Set M_General;
    MetaData_Set M_MetaData;
    Difficulty_Set M_Difficulty;
    std::vector<TimingPoint_Set> TimingPoints;
    std::vector<std::pair<int, std::array<int, 4>>> NotePoints;
    std::vector<std::pair<int, std::array<int, 4>>> ImagePoints;
    int TPoint_array_section;
    int Last_Note_pos;
    int _KEY_COUNT_;
};

void note_info(std::string str, SongData& data);
std::string Trim(std::string& str);
void ReadProperty_General(std::string str, SongData& data);
void ReadProperty_MetaData(std::string str, SongData& data);
void ReadProperty_TimingPoint(std::string str, SongData& data);
void ReadProperty_Difficulty(std::string str, SongData& data);
void ReadLine_Check(std::string str, int section, SongData& data);
int LoadMapFile(std::string beatmap, SongData& data);

