#ifndef MENU_H
#define MENU_H

#include "GameObject.h"

class Menu : public GameObject {
public:
    enum MenuOption {
        START_GAME_SINGLE_PLAYER_EasyMode = 1,
        START_GAME_SINGLE_PLAYER_HardMode,
        START_GAME_TWO_PLAYER,
        SELECT_MAP,
        VIEW_LEADERBOARD,
        EXIT
    };
    vector<string> input_file_edit;

    void initial_animation();
    void player1_win_ani();
    void player2_win_ani();
    void ai_win_ani();
    void DeathEffect(Player &p1,Player &p2,int elapsedTime);
    void Display_Main_Menu(int currentSelection);
    void Display_Map_Selection(vector<string> &maps,int currentSelection);
    void setGameMap(int mapSelection);
    void game_setup(Player &p1, Player &p2,int currChoice);
    bool initGame(Player &p1, Player &p2);
};

#endif
