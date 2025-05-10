#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Globals.h"

struct LeaderboardEntry {
    string playerName;
    int score;
    int time; 
};

extern vector<LeaderboardEntry> leaderboard;

class GameObject {
protected:
    struct Bomb {
        int x, y;
        time_t placedTime;
        int owner;  // 1 or 2
        int bomb_Range;
    };
    vector<Bomb> bombs;
public:
    time_t gameStartTime;
    int AI_MOVE_DELAY = 2;
    struct Player {
        int x, y;
        int lives;
        int bombsPlaced;
        int score;
        int maxbomb;
        int bombrange;
        bool isComputer = false;
        string symbol;
        char upKey, downKey, leftKey, rightKey, bombKey;
    };

    int kbhit();
    int getch();
    void setConioTerminalMode();
    void resetTerminalMode();
    string centerText(const string &text, int width);
    string leftAlignText(const string &text, int prefixSpaces, int width);

    void loadLeaderboard();
    int updateLeaderboard(const string &winnerName, int winnerScore, int matchTime);
    void displayLeaderboard();
};

#endif
