#pragma once
#include <string>
#include <vector>

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

extern General_Set M_General;
extern MetaData_Set M_MetaData;
extern Difficulty_Set M_Difficulty;
extern std::vector<TimingPoint_Set> TimingPoints;
extern std::vector<std::vector<int>> NotePoints;
extern std::vector<std::vector<int>> ImagePoints;
extern int TPoint_array_section;
extern int Last_Note_pos;
extern int _KEY_COUNT_;

void note_info(std::string str);
std::string Trim(std::string& str);
void ReadProperty_General(std::string str);
void ReadProperty_MetaData(std::string str);
void ReadProperty_TimingPoint(std::string str);
void ReadProperty_Difficulty(std::string str);
void ReadLine_Check(std::string str, int section);
int LoadMapFile(std::string beatmap);
