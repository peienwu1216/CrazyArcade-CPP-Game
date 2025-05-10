#include "Menu.h"

void Menu::initial_animation(){
    ifstream inputfile1("assets/animation.txt");
    for(int i = 0;i <= 58;i++){
        string temp;
        getline(inputfile1,temp);
        input_file_edit.push_back(temp);
    }
    vector<string> animationFrames;
    for(int i = 0;i < 14;i++){
        animationFrames.push_back(input_file_edit[i]);
    }
    cout << "\033[2J\033[H";
    for(auto &line : animationFrames){
        cout << line << endl;
        usleep(200000);
    }
    usleep(250000);
    cout << "\033[2J\033[H";
    usleep(250000);
}

void Menu::player1_win_ani(){
    cout << "\033[2J\033[H";
    vector<string> player1Frames;
    for(int i = 15;i <= 28;i++)player1Frames.push_back(input_file_edit[i]);
    for (auto &line : player1Frames){
        cout << line << endl;
        usleep(200000);
    }
    cout <<"Press any buttom to quit!"<<endl; 
    while (!kbhit()){
        char key = getch();
        usleep(100000);
        cout << "\033[2J\033[H";
    }
}

void Menu::player2_win_ani(){
    cout << "\033[2J\033[H";
    vector<string> player2Frames;
    for(int i = 30;i <= 43;i++)player2Frames.push_back(input_file_edit[i]);
    for (auto &line : player2Frames){
        cout << line << endl;
        usleep(100000);
    }
    cout <<"Press any buttom to quit!"<<endl; 
    while (!kbhit()){
        char key = getch();
        usleep(100000);
        cout << "\033[2J\033[H";
    }
}
void Menu::ai_win_ani(){
    cout << "\033[2J\033[H";
    vector<string> player2Frames;
    for(int i = 53;i <= 58;i++)player2Frames.push_back(input_file_edit[i]);
    for (auto &line : player2Frames){
        cout << line << endl;
        usleep(100000);
    }
    cout <<"Press any buttom to quit!"<<endl; 
    while (!kbhit()){
        char key = getch();
        usleep(100000);
        cout << "\033[2J\033[H";
    }
}

void Menu::DeathEffect(Player &p1,Player &p2,int elapsedTime){
    cout << "Player 1 Lives: " << p1.lives << "\tPlayer 2 Lives: " << p2.lives << endl;
    cout << "Player 1 Score: " << p1.score << "\tPlayer 2 score: " << p2.score << endl;
    cout << "Time: " << elapsedTime << endl;
    vector<string> current_display_frame(mapHeight+2,"");
    for(int i = 0;i < 2*mapWidth+2;i++)current_display_frame[0] += borderSymbol;
    for (int i = 0; i < mapHeight; i++){
        for (int j = 0; j < mapWidth; j++){
            if(j == 0 || j == mapWidth-1)current_display_frame[i+1]+=(borderSymbol+borderSymbol+borderSymbol);
            else if(gameMap[i][j] == bombSymbol)current_display_frame[i+1] += gameMap[i][j];
            else current_display_frame[i+1] += (gameMap[i][j]+gameMap[i][j]);
        }
    }
    for(int i = 0;i < 2*mapWidth+2;i++)current_display_frame[mapHeight+1] += borderSymbol;
    for(int i = 8;i < 15;i++){
        current_display_frame[i] = "║"+input_file_edit[i+37]+"║";
    }
    current_display_frame[7] = "╔═══════════════════════════════════════════════════════╗";
    current_display_frame[15] = "╚═══════════════════════════════════════════════════════╝";
    for(auto &line : current_display_frame){
        cout << line << endl;
        usleep(200000);
    }
}


void Menu::Display_Main_Menu(int currentSelection){
    cout << "\033[2J\033[H";
    const int width = 55;
    const int leftWidth = 5;
    cout << "╔" << "═══════════════════════════════════════════════════════" << "╗" << endl;
    cout << "║" << centerText("~ Crazy Arcade ~",width) << "║" << endl;
    cout << "║" << centerText("Welcome to the Ultimate Battle",width) << "║" << endl;
    cout << "║" << string(width,' ') << "║" << endl;
    cout << "║" << centerText("This is the Menu", width) << "║" << endl;
    cout << "║" << string(width,' ') << "║" << endl;
    cout << "║" << centerText("Instructions:", width) << "║" << endl;
    cout << "║" << leftAlignText("Player 1: Use [W,A,S,D] to move,[F] to place bombs", 2,width) << "║" << endl;
    cout << "║" << leftAlignText("Player 2: Use [O,K,L,;] to move,[J] to place bombs", 2,width) << "║" << endl;
    cout << "║" << string(width,' ') << "║" << endl;
    cout << "║" << string(width,' ') << "║" << endl;
    cout << "╠" << "═══════════════════════════════════════════════════════" << "╣" << endl;
    cout << "║" << string(width,' ') << "║" << endl;
    cout << "║" << centerText("Select the Following Mode : ", width) << "║" << endl;
    cout << "║" << centerText("(Use [W,S] to select)",width) << "║" << endl;
    cout << "║" << string(width,' ') << "║" << endl;
    cout << "║" << leftAlignText((currentSelection == MenuOption::START_GAME_SINGLE_PLAYER_EasyMode ? ">> 1) Start Single-Player Game(Easy)" : "   1) Start Single-Player Game(Easy)"),leftWidth,width) << "║" << endl;
    cout << "║" << leftAlignText((currentSelection == MenuOption::START_GAME_SINGLE_PLAYER_HardMode ? ">> 2) Start Single-Player Game(Hard)" : "   2) Start Single-Player Game(Hard)"),leftWidth,width) << "║" << endl;
    cout << "║" << leftAlignText((currentSelection == MenuOption::START_GAME_TWO_PLAYER ? ">> 3) Start Two-Player Game" : "   3) Start Two-Player Game"),leftWidth,width) << "║" << endl;
    cout << "║" << leftAlignText((currentSelection == MenuOption::SELECT_MAP ? ">> 4) Select Map" : "   4) Select Map"),leftWidth,width) << "║" << endl;
    cout << "║" << leftAlignText((currentSelection == MenuOption::VIEW_LEADERBOARD ? ">> 5) View Leaderboard" : "   5) View Leaderboard"),leftWidth,width) << "║" << endl;
    cout << "║" << leftAlignText((currentSelection == MenuOption::EXIT ? ">> 6) Exit" : "   6) Exit"),leftWidth,width) << "║" << endl;
    cout << "║" << string(width,' ') << "║" << endl;
    cout << "║" << string(width,' ') << "║" << endl;
    cout << "╚" << "═══════════════════════════════════════════════════════" << "╝" << endl;
}

void Menu::Display_Map_Selection(vector<string> &maps,int currentSelection){
    const int width = 40;
    const int leftWidth = 5;
    cout << "\033[2J\033[H";
    cout << "╔" << "════════════════════════════════════════" << "╗" << endl;
    cout << "║" << string(width,' ') << "║" << endl;
    cout << "║" << centerText("Available Maps : ", width) << "║" << endl;
    cout << "║" << string(width,' ') << "║" << endl;
    for(size_t i = 0; i < maps.size();i++){
        string display1 = "  "+to_string(i+1)+". "+maps[i];
        string display2 = "> "+to_string(i+1)+". "+maps[i];
        if((int)i == currentSelection)cout<<"║"<<leftAlignText(display2,leftWidth,width)<<"║" << endl;
        else cout<<"║"<<leftAlignText(display1,leftWidth,width)<<"║" << endl;
    }
    cout << "║" << string(width,' ') << "║" << endl;
    cout << "║" << string(width,' ') << "║" << endl;
    cout << "╚" << "════════════════════════════════════════" << "╝" << endl;
}

void Menu::setGameMap(int mapSelection){
    for (int i = 0; i < mapHeight;i++){
        for(int j = 0;j < mapWidth;j++){
            gameMap[i][j] = emptySymbol;
        }
    }
    for (int i = 0; i < mapWidth;i++){
        gameMap[0][i] = borderSymbol;
        gameMap[mapHeight - 1][i] = borderSymbol;
    }
    for (int i = 0; i < mapHeight; i++){
        gameMap[i][0] = borderSymbol;
        gameMap[i][mapWidth - 1] = borderSymbol;
    }
    srand(time(NULL));

    switch (mapSelection){
        case 0: 
            for (int i = 2; i < mapHeight -2; i += 2){
                if (i%4 == 0){
                    for (int j = 2; j < mapWidth - 2; j += 2)
                        gameMap[i][j] = obstacleSymbol;
                }
            }
            break;
        case 1:
            for (int i = 2; i < mapHeight -2; i += 2)
                for(int j = 2; j < mapWidth - 2; j += 2)
                    gameMap[i][j] = obstacleSymbol;
            break;
        case 2:
            int radius = 2;
            for (int i = 1; i < mapHeight - 1; i++) {
                for (int j = 1; j < mapWidth - 1; j++) {
                    bool inProtectedZoneP1 = (i >= 1 && i <= 1 + radius && j >= 1 && j <= 1 + radius);
                    bool inProtectedZoneP2 = (i >= mapHeight - 2 - radius && i <= mapHeight - 2 &&
                                              j >= mapWidth - 2 - radius && j <= mapWidth - 2);
                    if (!inProtectedZoneP1 && !inProtectedZoneP2 && rand() % 10 == 0) {
                        gameMap[i][j] = obstacleSymbol;
                    } else if(!inProtectedZoneP1 && !inProtectedZoneP2 && rand() % 10 == 0){
                        gameMap[i][j] = distructible_obstacleSymbol;
                        int chance = rand() % 100;  //Probability of Obsticles
                        if (chance < 80){
                            int p = rand() % 100;
                            if(0 <= p && p < 50)itemMap[i][j] = addScoreSymbol;
                            else if(50 <= p && p< 60)itemMap[i][j] = addLiveSymbol;
                            else if(60 <= p && p < 90)itemMap[i][j] = addBombSymbol;
                            else if(90 <= p && p < 100)itemMap[i][j] = addRangeSymbol;
                        }
                        else itemMap[i][j] = "";
                    } else {
                        gameMap[i][j] = emptySymbol;
                    }
                }
            }
            break;
    }
}

void Menu::game_setup(Player &p1, Player &p2,int currChoice){
    setGameMap(currChoice);
    p1.x = 1;
    p1.y = 1;
    p1.lives = maxLives;
    p1.bombsPlaced = 0;
    p1.symbol = player1Symbol;
    p1.maxbomb = maxBombs;
    p1.bombrange = bombRange;
    p1.isComputer = false;

    p2.x = mapWidth - 2;
    p2.y = mapHeight - 2;
    p2.lives = maxLives;
    p2.bombsPlaced = 0;
    p2.symbol = player2Symbol;
    p2.maxbomb = maxBombs;
    p2.bombrange = bombRange;

    gameMap[p1.y][p1.x] = p1.symbol;
    gameMap[p2.y][p2.x] = p2.symbol;
    return;
}

bool Menu::initGame(Player &p1, Player &p2){
    gameMap.resize(mapHeight, vector<string>(mapWidth, emptySymbol));
    itemMap.resize(mapHeight, vector<string>(mapWidth, ""));
    vector<string> maps = {"Game Map 1(Easy Mode)", "Game Map 2(Medium Mode)", "Game Map 3(Hard Mode)"};
    int currentSelection = MenuOption::START_GAME_SINGLE_PLAYER_EasyMode;

    bool running = true;
    while(true){
        usleep(100000);
        Display_Main_Menu(currentSelection);
        if(!running)break;
        while(kbhit()){
            char key = getch();
            if(key == 'w' || key == 'W'){
                currentSelection = (currentSelection > MenuOption::START_GAME_SINGLE_PLAYER_EasyMode) ? currentSelection - 1 : MenuOption::EXIT;
            }
            else if(key == 's' || key == 'S'){
                currentSelection = (currentSelection < MenuOption::EXIT) ? currentSelection + 1 : MenuOption::START_GAME_SINGLE_PLAYER_EasyMode;
            }
            else if(key == '\n'){
                int currChoice = 0;
                switch(currentSelection){
                    case START_GAME_SINGLE_PLAYER_EasyMode:
                        AI_MOVE_DELAY = 4;
                        cout << "\nSingle-Player Game (Easy Mode) starting!\n";
                        currChoice = 2; 
                        usleep(500000);
                        game_setup(p1, p2, currChoice);
                        p2.isComputer = true;
                        return 1;
                    case START_GAME_SINGLE_PLAYER_HardMode:
                        AI_MOVE_DELAY = 2;
                        cout << "\nSingle-Player Game (Hard Mode) starting!\n";
                        currChoice = 2; 
                        usleep(500000);
                        game_setup(p1, p2, currChoice);
                        p2.isComputer = true;
                        return 1;
                    case START_GAME_TWO_PLAYER:
                        cout << "\nTwo-Player Game starting!\n";
                        currChoice = 2;
                        usleep(500000);
                        game_setup(p1, p2, currChoice);
                        p2.isComputer = false;
                        return 1;
                    case EXIT:
                        cout << "\nThanks for playing, goodbye!\n";
                        return 0;
                    case VIEW_LEADERBOARD:
                        this->displayLeaderboard();
                        break;
                    case SELECT_MAP:
                    {
                        bool currentRunning = true;
                        while(true){
                            usleep(100000);
                            Display_Map_Selection(maps,currChoice);
                            if(!currentRunning)break;
                            while(kbhit()){
                                char key = getch();
                                if(key == 'w' || key == 'W'){
                                    currChoice = (currChoice > 0) ? currChoice - 1 : (int)maps.size()-1;
                                }
                                else if(key == 's' || key == 'S'){
                                    currChoice = (currChoice < (int)maps.size()-1) ? currChoice + 1 : 0;
                                }
                                else if(key == '\n'){
                                    currentRunning = false;
                                    break;
                                }
                            }
                        }
                        game_setup(p1,p2,currChoice);
                        p2.isComputer = false;
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
