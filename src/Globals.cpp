#include "Globals.h"

int mapWidth = 21;
int mapHeight = 21;

string borderSymbol = "/";
string obstacleSymbol = "\033[0m█\033[0m";
string distructible_obstacleSymbol = "\033[90m█\033[0m";
string bombSymbol = "\033[31m●\033[0m";
string explosionSymbol = "\033[31m※\033[0m";
string emptySymbol = " ";
string player1Symbol = "\033[34mA\033[0m";
string player2Symbol = "\033[34mB\033[0m";

string addScoreSymbol = "\033[32m★\033[0m";
string addLiveSymbol = "\033[31m♥\033[0m";
string addBombSymbol = "\033[35m♠\033[0m";
string addRangeSymbol = "\033[91m❁\033[0m";
int item_totol_number = 4;

char p1_up = 'w';
char p1_down = 's';
char p1_left = 'a';
char p1_right = 'd';
char p1_bomb = 'f';

char p2_up = 'o';
char p2_down = 'l';
char p2_left = 'k';
char p2_right = ';';
char p2_bomb = 'j';

int bombDelay = 3;
int bombDelay_Red = 1;
int bombRange = 3;
int maxBombs = 1; 
int maxLives = 3;

vector<vector<string>> gameMap;
vector<vector<string>> itemMap;
