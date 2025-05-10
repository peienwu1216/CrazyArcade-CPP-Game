#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/select.h>
#include <ctime>
#include <cstring>
#include <random>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Game parameters and Basic Settings
extern int mapWidth;
extern int mapHeight;

extern string borderSymbol;
extern string obstacleSymbol;
extern string distructible_obstacleSymbol;
extern string bombSymbol;
extern string explosionSymbol;
extern string emptySymbol;
extern string player1Symbol;
extern string player2Symbol;

extern string addScoreSymbol;
extern string addLiveSymbol;
extern string addBombSymbol;
extern string addRangeSymbol;
extern int item_totol_number;

// Player controls
extern char p1_up;
extern char p1_down;
extern char p1_left;
extern char p1_right;
extern char p1_bomb;

extern char p2_up;
extern char p2_down;
extern char p2_left;
extern char p2_right;
extern char p2_bomb;

extern int bombDelay;
extern int bombDelay_Red;
extern int bombRange;
extern int maxBombs; 
extern int maxLives;

// Game Map Setting
extern vector<vector<string>> gameMap;
extern vector<vector<string>> itemMap;

#endif