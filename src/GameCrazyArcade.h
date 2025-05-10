#ifndef GAMECRAZYARCADE_H
#define GAMECRAZYARCADE_H

#include "GameObject.h"
#include "AIController.h"
#include "Menu.h"

class GameCrazyArcade : public AIController {
public:
    void gameInitialization(Player &player1, Player &player2);
    void drawGame(Player &p1, Player &p2,GameObject gameobject);
    void updateBombs(Player &p1, Player &p2,GameObject gameobject);
    int GameStart(Player player1,Player player2,GameObject gameobject,Menu menu);
};

#endif
