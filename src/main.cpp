#include "Globals.h"
#include "GameObject.h"
#include "Menu.h"
#include "GameCrazyArcade.h"

int main(){
    GameObject gameobject;
    gameobject.loadLeaderboard();
    while(true){
        Menu menu;
        GameCrazyArcade game;
        GameCrazyArcade::Player player1;
        GameCrazyArcade::Player player2;
        bool Status;
        Status = game.GameStart(player1,player2,gameobject,menu);
        if(!Status)break;
    }
    ofstream file("leaderboard.txt");
    for (auto &entry : leaderboard) {
        file << entry.playerName << " " << entry.score << " " << entry.time << "\n";
    }
    file.close();
    return 0;
}