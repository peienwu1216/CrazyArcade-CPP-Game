#include "GameCrazyArcade.h"
#include <queue>

void GameCrazyArcade::gameInitialization(Player &player1, Player &player2){
    // Set player controls
    player1.upKey = p1_up;
    player1.downKey = p1_down;
    player1.leftKey = p1_left;
    player1.rightKey = p1_right;
    player1.bombKey = p1_bomb;
    player1.score = 0;

    player2.upKey = p2_up;
    player2.downKey = p2_down;
    player2.leftKey = p2_left;
    player2.rightKey = p2_right;
    player2.bombKey = p2_bomb;
    player2.score = 0;
}

void GameCrazyArcade::drawGame(Player &p1, Player &p2,GameObject gameobject){
    cout << "\033[2J\033[1;1H";
    cout << "Player 1 Lives: " << p1.lives << "\tPlayer 2 Lives: " << p2.lives << endl;
    cout << "Player 1 Score: " << p1.score << "\tPlayer 2 score: " << p2.score << endl;

    time_t currentTime = time(NULL);
    int elapsedTime = (int)difftime(currentTime,gameobject.gameStartTime);
    cout << "Time: " << elapsedTime << endl;

    for(int i = 0;i < 2*mapWidth+2;i++)cout<<borderSymbol;
    cout<<endl;
    for (int i = 0; i < mapHeight; i++){
        for (int j = 0; j < mapWidth; j++){
            if(j == 0 || j == mapWidth-1)cout<<borderSymbol;
            if(gameMap[i][j].substr(0,gameMap[i][j].size()-1) == bombSymbol){
                string temp = gameMap[i][j];
                string a = temp.substr(0,temp.size()-1);
                char b = temp[temp.size()-1];
                cout << a << b;
            }
            else cout << gameMap[i][j] << gameMap[i][j];
        }
        cout << endl;
    }
    for(int i = 0;i < 2*mapWidth+2;i++)cout<<borderSymbol;
    cout<<endl;
}

void GameCrazyArcade::updateBombs(Player &p1, Player &p2,GameObject gameobject){
    time_t currentTime = time(NULL);
    vector<Bomb> newBombs;

    for (auto &bomb : bombs){
        int timeLeft = (bombDelay - (int)difftime(currentTime, bomb.placedTime));
        gameMap[bomb.y][bomb.x] = bombSymbol + to_string(timeLeft);
    }

    for (auto &bomb : bombs){
        if (difftime(currentTime, bomb.placedTime) >= bombDelay) {
            int x = bomb.x;
            int y = bomb.y;
            if (gameMap[y][x] == bombSymbol)
                gameMap[y][x] = emptySymbol;
            
            vector<pair<int, int>> explosionPositions;
            explosionPositions.push_back({x, y});
            Player *bombOwner;
            if(bomb.owner == 1)bombOwner = &p1;
            else if(bomb.owner == 2)bombOwner = &p2;
            // Up
            for (int i = 1; i <= bombOwner->bombrange; i++) {
                int ny = y - i;
                if (ny < 0 || gameMap[ny][x] == borderSymbol || gameMap[ny][x] == obstacleSymbol)
                    break;
                explosionPositions.push_back({x, ny});
                if (gameMap[ny][x] == bombSymbol)
                    break;
            }
            // Down
            for (int i = 1; i <= bombOwner->bombrange; i++) {
                int ny = y + i;
                if (ny >= mapHeight || gameMap[ny][x] == borderSymbol || gameMap[ny][x] == obstacleSymbol)
                    break;
                explosionPositions.push_back({x, ny});
                if (gameMap[ny][x] == bombSymbol)
                    break;
            }
            // Left
            for (int i = 1; i <= bombOwner->bombrange; i++) {
                int nx = x - i;
                if (nx < 0 || gameMap[y][nx] == borderSymbol || gameMap[y][nx] == obstacleSymbol)
                    break;
                explosionPositions.push_back({nx, y});
                if (gameMap[y][nx] == bombSymbol)
                    break;
            }
            // Right
            for (int i = 1; i <= bombOwner->bombrange; i++) {
                int nx = x + i;
                if (nx >= mapWidth || gameMap[y][nx] == borderSymbol || gameMap[y][nx] == obstacleSymbol)
                    break;
                explosionPositions.push_back({nx, y});
                if (gameMap[y][nx] == bombSymbol)
                    break;
            }

            for (auto &pos : explosionPositions) {
                if (gameMap[pos.second][pos.first] != borderSymbol && gameMap[pos.second][pos.first] != obstacleSymbol)
                    gameMap[pos.second][pos.first] = explosionSymbol;
            }

            drawGame(p1, p2, gameobject);
            usleep(200000);

            for (auto &pos : explosionPositions) {
                if (gameMap[pos.second][pos.first] == explosionSymbol)
                    gameMap[pos.second][pos.first] = emptySymbol;
                if (itemMap[pos.second][pos.first] != ""){
                    gameMap[pos.second][pos.first] = itemMap[pos.second][pos.first];
                }
            }

            for (auto &pos : explosionPositions) {
                if (p1.x == pos.first && p1.y == pos.second) {
                    p1.lives--;
                    if(bomb.owner == 2)p2.score += 100;
                    if (p1.lives <= 0) {
                        gameMap[p1.y][p1.x] = emptySymbol;
                    }
                }
                if (p2.x == pos.first && p2.y == pos.second) {
                    p2.lives--;
                    if(bomb.owner == 1)p1.score += 100;
                    if (p2.lives <= 0) {
                        gameMap[p2.y][p2.x] = emptySymbol;
                    }
                }
            }
            if (bomb.owner == 1)
                p1.bombsPlaced--;
            else
                p2.bombsPlaced--;

        } else {
            newBombs.push_back(bomb);
        }
    }
    bombs = newBombs;
}

int GameCrazyArcade::GameStart(Player player1,Player player2,GameObject gameobject,Menu menu){
    gameobject.setConioTerminalMode();
    menu.initial_animation();
    bool Status;
    Status = menu.initGame(player1, player2);
    if(!Status)return 0;

    gameInitialization(player1,player2);
    gameobject.gameStartTime = time(NULL);

    while(true){
        if (player1.lives <= 0 || player2.lives <= 0){
            cout << "\033[2J\033[H";
            time_t currentTime = time(NULL);
            int elapsedTime = (int)difftime(currentTime,gameobject.gameStartTime);

            menu.DeathEffect(player1,player2,elapsedTime);
            usleep(3000000);
            break;
        }
        drawGame(player1, player2,gameobject);
        if(player2.isComputer)cout<<"Current AI state: "<< enum_to_string(currentState)<<endl;
        updateBombs(player1, player2,gameobject);
        usleep(100000); 
        // Process Player 1 (human) input
        if(player2.isComputer)computeMove(player2, player1);

        while (gameobject.kbhit()) {
            char ch = gameobject.getch();
            if (ch == player1.upKey || ch == player1.downKey || ch == player1.leftKey || ch == player1.rightKey) {
                movePlayer(player1, ch);
            } else if (ch == player1.bombKey) {
                placeBomb(player1, 1);
            }
            if(!player2.isComputer){
                // Human-controlled Player 2
                if (ch == player2.upKey || ch == player2.downKey || ch == player2.leftKey || ch == player2.rightKey) {
                    movePlayer(player2, ch);
                } else if (ch == player2.bombKey) {
                    placeBomb(player2, 2);
                }
            }
        }
    }
    time_t endTime = time(NULL);
    int matchTime = (int)difftime(endTime, gameobject.gameStartTime);
    string winnerName;
    int winnerScore;
    if (player1.lives == player2.lives) {
        resetTerminalMode();
        cout << "It's a tie!" << endl;
        usleep(1000000);
    }
    else if (player2.lives > player1.lives){
        if(player2.isComputer)menu.ai_win_ani();
        else menu.player2_win_ani();
        resetTerminalMode();
        if(!player2.isComputer){
            cout << "Congratulations Player2!\nPlease Enter your name for leaderboard: ";
            cin >> winnerName;
            winnerScore = player2.score;
            int index = updateLeaderboard(winnerName, winnerScore, matchTime);
            cout << "Congratulations "<<winnerName<<"!"<<endl;
            cout << "Your score is "<<winnerScore<<"\nUsed time: "<<matchTime<<" seconds"<<endl;
            if(index == 0)cout << "Your are not in the top ten leaderboard.\nNext time, TRY HARDER!!\n";
            else cout << "Your are currently in the "<<index<<" place!\nKeep it up!"<<endl;
        }
        else{
            cout << "AI wins!\nPlease try harder next time!"<<endl;
        }
        usleep(1000000);
    }else {
        menu.player1_win_ani();
        resetTerminalMode();
        cout << "Congratulations Player1!\nPlease Enter your name for leaderboard: ";
        cin >> winnerName;
        winnerScore = player1.score;
        int index = updateLeaderboard(winnerName, winnerScore, matchTime);
        cout << "Congratulations "<<winnerName<<"!"<<endl;
        cout << "Your score is "<<winnerScore<<"\nUsed time: "<<matchTime<<" seconds"<<endl;
        if(index == 0)cout << "Your are not in the top ten leaderboard.\nNext time, TRY HARDER!!\n";
        else cout << "Your are currently in the "<<index<<" place!\nKeep it up!"<<endl;
        usleep(1000000);
    }
    cout<<"Do you want to play it again?(Y/N):";
    string answer;
    while(cin>>answer){
        if(answer == "Y" ||answer == "y" ||answer == "yes"||answer == "YES"){
            cout<<"The Game will start right away.";
            usleep(500000);
            break;
        }
        else if(answer == "N" ||answer == "n" ||answer == "no"||answer == "NO"){
            cout << "Thanks for playing, goodbye!\n";
            return 0;
        }
        else{
            cout << "Invalid Input. Please try again.\n";
            cout<<"Do you want to play it again?(Y/N):";
        }
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    return 1;
}