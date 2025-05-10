#include "AIController.h"
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

void AIController::computeMove(Player &computerPlayer, Player &humanPlayer) {
    aiMoveCounter++;
    if(aiMoveCounter < AI_MOVE_DELAY)return;
    aiMoveCounter = 0;

    if(computerPlayer.y == lastAiY && computerPlayer.x == lastAiX) aiStuckCounter++;
    else aiStuckCounter = 0;
    lastAiY = computerPlayer.y;lastAiX = computerPlayer.x;

    updateState(computerPlayer,humanPlayer);

    switch(currentState) {
        case AIState::ESCAPE:
            handleEscapeState(computerPlayer);
            break;
        case AIState::WAIT_EXPLOSION:
            handleWaitExplosionState(computerPlayer);
            break;
        case AIState::FETCH_ITEMS:
            handleFetchItemsState(computerPlayer);
            break;
        case AIState::ATTACK_PLAYER:
            handleAttackPlayerState(computerPlayer,humanPlayer);
            break;
        case AIState::IDLE:
        default:
            handleIdleState(computerPlayer,humanPlayer);
            break;
    }
}

void AIController::updateState(Player &computerPlayer, Player &humanPlayer) {
    double sinceBombPlaced = difftime(time(NULL), lastBombTime);
    bool bombActive = (sinceBombPlaced < bombWaitDuration && aiRecentlyPlacedBomb);
    // Priority 1 : Check if bomb nearby
    if(bombActive){
        vector<pair<int,int>> safeCells = getSafeCells();
        if(!safeCells.empty()){
            auto path = bfsFindPath(computerPlayer,safeCells,true);
            if(!path.empty()){
                currentPath = path;currentPathIndex = 0;
                if(currentState != AIState::ESCAPE)startState(AIState::ESCAPE);
                return;
            }
            else{
                if(currentState != AIState::ESCAPE)startState(AIState::ESCAPE);
                return;
            }
        }
        else{
            if(currentState != AIState::WAIT_EXPLOSION)startState(AIState::WAIT_EXPLOSION);
            return;
        }
    }
    // Priority 2 : Check if player is reachable
    vector<pair<int,int>> playerPath = bfsFindPath(computerPlayer,getPlayerCell(humanPlayer),true);
    if(!playerPath.empty()){
        if(shouldPlaceBombToAttack(computerPlayer,humanPlayer)) {
            placeBombSafely(computerPlayer);
            auto safeCells = getSafeCells();
            if(!safeCells.empty()){
                auto path = bfsFindPath(computerPlayer,safeCells,true);
                if(!path.empty()){
                    currentPath = path;currentPathIndex=0;
                    startState(AIState::ESCAPE);
                }
            }
            else startState(AIState::ESCAPE);
            return;
        }
        else{
            if(currentState != AIState::ATTACK_PLAYER)startState(AIState::ATTACK_PLAYER);
            currentPath = playerPath;currentPathIndex = 0;
            return;
        }
    }
    else{   // Priority 3 : Fetch Items
        auto items = getItemCells();
        auto itemPath = bfsFindPath(computerPlayer,items,true);
        if(!itemPath.empty()){
            if(shouldPlaceBombToClear(computerPlayer)) {
                placeBombSafely(computerPlayer);
                auto safeCells = getSafeCells();
                if(!safeCells.empty()){
                    auto path = bfsFindPath(computerPlayer,safeCells,true);
                    if(!path.empty()){
                        currentPath = path;currentPathIndex=0;
                        startState(AIState::ESCAPE);
                    }
                }
                else startState(AIState::WAIT_EXPLOSION);
                return;
            }
            else{
                if(currentState != AIState::FETCH_ITEMS)startState(AIState::FETCH_ITEMS);
                currentPath = itemPath;currentPathIndex = 0;
                return;
            }
        }
        else{   // Default : Nothing else, idle or move randomly
            if(currentState!=AIState::IDLE)startState(AIState::IDLE);
        }
    }
}

vector<pair<int,int>> AIController::bfsFindPath(const Player &start, const vector<pair<int,int>> &targets, bool avoidDanger){
    auto dangerMap = computeDangerMap();
    vector<vector<bool>> visited(mapHeight, vector<bool>(mapWidth,false));
    vector<vector<pair<int,int>>> parent(mapHeight, vector<pair<int,int>>(mapWidth, {-1,-1}));
    queue<pair<int,int>> q; //BFS path finding queue
    q.push({start.y,start.x});
    visited[start.y][start.x] = true;
    vector<pair<int,int>> directions = {{-1,0},{1,0},{0,-1},{0,1}};
    bool found = false;
    pair<int,int> foundTarget = {-1,-1};
    while(!q.empty()){
        int cy = q.front().first,cx = q.front().second;
        q.pop();
        for(auto &t: targets) {
            if(t.first == cy && t.second == cx){
                found = true;
                foundTarget = t;
                break;
            }
        }
        if(found)break;
        for(auto &dir: directions){
            int ny = cy + dir.first;
            int nx = cx + dir.second;
            if(ny < 0||ny >= mapHeight||nx < 0||nx >= mapWidth)continue;
            if(!visited[ny][nx]) {
                string cell = gameMap[ny][nx];
                if(cell == borderSymbol || cell == obstacleSymbol || cell == distructible_obstacleSymbol)continue;
                if(cell.substr(0,bombSymbol.size()) == bombSymbol)continue;
                if(avoidDanger && dangerMap[ny][nx]) continue;
                visited[ny][nx] = true;
                parent[ny][nx] = {cy,cx};
                q.push({ny,nx});
            }
        }
    }
    if(!found)return{};
    vector<pair<int,int>> path; //Use parent vector to find its way to start
    int py = foundTarget.first,px = foundTarget.second;
    while(!(py == start.y && px == start.x)) {
        path.push_back({py,px});
        auto p = parent[py][px];
        py = p.first;px = p.second;
    }
    path.push_back({start.y,start.x});
    reverse(path.begin(),path.end());
    return path;
}

vector<pair<int,int>> AIController::getSafeCells() {
    vector<vector<bool>> dangerMap = computeDangerMap();
    vector<pair<int,int>> safeCells;
    for(int i = 0;i < mapHeight;i++){
        for(int j = 0;j < mapWidth;j++){
            if(!dangerMap[i][j] && (gameMap[i][j] == emptySymbol || gameMap[i][j] == addScoreSymbol || gameMap[i][j] == addLiveSymbol
                ||gameMap[i][j] == addBombSymbol || gameMap[i][j] == addRangeSymbol)){
                safeCells.push_back({i,j});
            }
        }
    }
    return safeCells;
}

vector<vector<bool>> AIController::computeDangerMap() {
    vector<vector<bool>> dangerMap(mapHeight, vector<bool>(mapWidth, false));
    for(auto &bomb : bombs) {
        dangerMap[bomb.y][bomb.x] = true;
        for(int i = 1; i <= bomb.bomb_Range; i++){    // Up
            int ny = bomb.y-i;
            if(ny<0||gameMap[ny][bomb.x]==borderSymbol||gameMap[ny][bomb.x]==obstacleSymbol) break;
            dangerMap[ny][bomb.x] = true;
        }
        for(int i=1; i <= bomb.bomb_Range; i++){    // Down
            int ny = bomb.y+i;
            if(ny>=mapHeight||gameMap[ny][bomb.x]==borderSymbol||gameMap[ny][bomb.x]==obstacleSymbol) break;
            dangerMap[ny][bomb.x] = true;
        }
        // Left
        for(int i=1; i <= bomb.bomb_Range; i++){
            int nx = bomb.x - i;
            if(nx<0||gameMap[bomb.y][nx]==borderSymbol||gameMap[bomb.y][nx]==obstacleSymbol) break;
            dangerMap[bomb.y][nx] = true;
        }
        // Right
        for(int i=1; i <= bomb.bomb_Range; i++){
            int nx = bomb.x + i;
            if(nx>=mapWidth||gameMap[bomb.y][nx]==borderSymbol||gameMap[bomb.y][nx]==obstacleSymbol) break;
            dangerMap[bomb.y][nx] = true;
        }
    }
    return dangerMap;
}

void AIController::moveAlongPath(Player &computerPlayer) {
    if(currentPathIndex + 1 < currentPath.size()){
        int nextY = currentPath[currentPathIndex+1].first;
        int nextX = currentPath[currentPathIndex+1].second;
        int dy = nextY-computerPlayer.y;
        int dx = nextX-computerPlayer.x;
        char moveKey;
        if(dy == -1 && dx == 0) moveKey=computerPlayer.upKey;
        else if(dy == 1 && dx == 0) moveKey=computerPlayer.downKey;
        else if(dy == 0 && dx == -1) moveKey=computerPlayer.leftKey;
        else if(dy == 0 && dx == 1) moveKey=computerPlayer.rightKey;
        else return;
        movePlayer(computerPlayer,moveKey);
        currentPathIndex++;
    }
}

void AIController::handleEscapeState(Player &computerPlayer) {
    if(!currentPath.empty()) {
        moveAlongPath(computerPlayer);
    }
    else{
        char mk = movePlayerRandomDirection(computerPlayer);
        movePlayer(computerPlayer,mk);
    }
}

void AIController::handleWaitExplosionState(Player &computerPlayer) {
    if(!currentPath.empty())moveAlongPath(computerPlayer);
    if(difftime(time(NULL),lastBombTime) > bombWaitDuration) {
        currentPath.clear();
        currentPathIndex = 0;
        startState(AIState::FETCH_ITEMS);
    }   //If none of the above are satisfied, wait.
}

void AIController::handleFetchItemsState(Player &computerPlayer) {
    if(!currentPath.empty()) {
        moveAlongPath(computerPlayer);
    } else {    // If no path, try items again or idle
        vector<pair<int,int>> items=getItemCells();
        if(!items.empty()){
            auto path = bfsFindPath(computerPlayer,items,true);
            if(!path.empty()){
                currentPath = path;currentPathIndex = 0;
                moveAlongPath(computerPlayer);
            } else {    // Move Randomly
                char mk = movePlayerRandomDirection(computerPlayer);
                movePlayer(computerPlayer,mk);
            }
        } else startState(AIState::IDLE);
    }
}

void AIController::handleAttackPlayerState(Player &computerPlayer, Player &humanPlayer) {
    if(!currentPath.empty())moveAlongPath(computerPlayer);
    else {  // If no path to player, Re-check state
        if(isTimeToReevaluateState()){
            updateState(computerPlayer, humanPlayer);
            if (currentState == AIState::ATTACK_PLAYER) {   // Still in attack mode
                char randomMove = movePlayerRandomDirection(computerPlayer);
                movePlayer(computerPlayer, randomMove);
            }
        }
    }
}

void AIController::handleIdleState(Player &computerPlayer, Player &humanPlayer) {
    char mk = movePlayerRandomDirection(computerPlayer);
    movePlayer(computerPlayer,mk);
}

bool AIController::canEscapeAfterBomb(const Player &computerPlayer){
    // simulate a bomb at current position
    int bx = computerPlayer.x;
    int by = computerPlayer.y;
    Bomb simulatedBomb = {bx, by, time(NULL), 2};
    bombs.push_back(simulatedBomb);
    vector<vector<bool>> dangerMap = computeDangerMap();
    bombs.pop_back();

    vector<vector<bool>> visited(mapHeight, vector<bool>(mapWidth,false));
    queue<pair<int,int>>q;
    q.push({by,bx});
    visited[by][bx] = true;
    vector<pair<int,int>> directions={{-1,0},{1,0},{0,-1},{0,1}};
    while(!q.empty()){
        int cy = q.front().first,cx = q.front().second;
        q.pop();
        if(!dangerMap[cy][cx]) return true;
        for(auto &dir: directions){
            int ny = cy + dir.first;
            int nx = cx + dir.second;
            if(ny < 0|| ny >= mapHeight||nx < 0||nx >= mapWidth) continue;
            if(!visited[ny][nx]) {
                string cell = gameMap[ny][nx];
                if(cell == borderSymbol||cell == obstacleSymbol || cell == distructible_obstacleSymbol)continue;
                if(cell.substr(0,bombSymbol.size()) == bombSymbol) continue;
                visited[ny][nx] = true;
                q.push({ny,nx});
            }
        }
    }
    return false;
}

bool AIController::shouldPlaceBombToAttack(const Player &computerPlayer, const Player &humanPlayer) {
    int dist = abs(humanPlayer.x - computerPlayer.x) + abs(humanPlayer.y - computerPlayer.y);
    return (dist <= 3 && computerPlayer.bombsPlaced < computerPlayer.maxbomb && canEscapeAfterBomb(computerPlayer));
}

bool AIController::shouldPlaceBombToClear(const Player &computerPlayer) {
    if(computerPlayer.bombsPlaced >= computerPlayer.maxbomb) return false;
    // Check adjacent for destructible obstacles
    vector<pair<int,int>> directions={{-1,0},{1,0},{0,-1},{0,1}};
    for(auto &dir: directions) {
        int ny = computerPlayer.y+dir.first;
        int nx = computerPlayer.x+dir.second;
        if(ny >= 0 && ny < mapHeight && nx >= 0 && nx < mapWidth){
            if(gameMap[ny][nx] == distructible_obstacleSymbol && canEscapeAfterBomb(computerPlayer)) {
                return true;
            }
        }
    }
    return false;
}

void AIController::placeBombSafely(Player &computerPlayer) {
    // Actually place the bomb, assuming checks done
    placeBomb(computerPlayer, 2);
    aiRecentlyPlacedBomb = true;
    lastBombTime = time(NULL);
}

vector<pair<int,int>> AIController::getItemCells(){
    vector<pair<int,int>> items;
    for(int i = 0;i < mapHeight;i++){
        for(int j = 0;j < mapWidth;j++){
            if(itemMap[i][j]!="") items.push_back({i,j});
        }
    }
    return items;
}

vector<pair<int,int>> AIController::getPlayerCell(const Player &humanPlayer){
    return {{humanPlayer.y,humanPlayer.x}};
}

char AIController::movePlayerRandomDirection(const Player &computerPlayer){
    vector<pair<int,int>> directions={{-1,0},{1,0},{0,-1},{0,1}};
    vector<char> keys={computerPlayer.upKey,computerPlayer.downKey,computerPlayer.leftKey,computerPlayer.rightKey};
    // fixed seed or no seed for deterministic results
    static mt19937 g(42);
    shuffle(directions.begin(), directions.end(), g);
    shuffle(keys.begin(), keys.end(), g);

    int cy = computerPlayer.y;int cx = computerPlayer.x;
    for(int i = 0;i < 4;i++){
        int ny = cy + directions[i].first;
        int nx = cx + directions[i].second;
        if(ny < 0||ny >= mapHeight||nx < 0||nx >= mapWidth) continue;
        string cell = gameMap[ny][nx];
        if(cell != borderSymbol && cell != obstacleSymbol && cell.substr(0,bombSymbol.size()) != bombSymbol) {
            return keys[i];
        }
    }
    return computerPlayer.upKey; 
}

void AIController::startState(AIState newState) {
    currentState = newState;
    stateStartTime = time(NULL);
    currentPath.clear();
    currentPathIndex = 0;
}

bool AIController::isTimeToReevaluateState(){
    return difftime(time(NULL), stateStartTime) > 3.0; // Reeval after 3s if stuck
}

void AIController::movePlayer(Player &player, char input) {
    int newX = player.x;
    int newY = player.y;
    if(input == player.upKey) newY--;
    else if(input == player.downKey) newY++;
    else if(input == player.leftKey) newX--;
    else if(input == player.rightKey) newX++;
    else return;

    if(newX <= 0 || newX >= mapWidth - 1 || newY <= 0 || newY >= mapHeight - 1)return;

    string dest = gameMap[newY][newX];
    if(dest == emptySymbol) {
        moveToNewPlace(player, player.x, player.y, newX, newY);
    } else if(dest == addScoreSymbol) {
        player.score += 50;
        itemMap[newY][newX] = "";
        moveToNewPlace(player, player.x, player.y, newX, newY);
    } else if(dest == addLiveSymbol) {
        player.score += 20;
        player.lives++;
        itemMap[newY][newX] = "";
        moveToNewPlace(player, player.x, player.y, newX, newY);
    } else if(dest == addBombSymbol) {
        player.score += 20;
        player.maxbomb++;
        itemMap[newY][newX] = "";
        moveToNewPlace(player, player.x, player.y, newX, newY);
    } else if(dest == addRangeSymbol) {
        player.score += 20;
        player.bombrange++;
        itemMap[newY][newX] = "";
        moveToNewPlace(player, player.x, player.y, newX, newY);
    }
}

void AIController::placeBomb(Player &player, int owner) {
    if(player.bombsPlaced >= player.maxbomb) return;
    Bomb newBomb;
    newBomb.x = player.x;
    newBomb.y = player.y;
    newBomb.bomb_Range = player.bombrange;
    newBomb.placedTime = time(NULL);
    newBomb.owner = owner;
    gameMap[newBomb.y][newBomb.x] = bombSymbol;
    bombs.push_back(newBomb);
    gameMap[player.y][player.x] = bombSymbol;
    player.bombsPlaced++;
}

void AIController::moveToNewPlace(Player &player,int x,int y,int newX,int newY){
    gameMap[player.y][player.x] = emptySymbol;
    player.x = newX;
    player.y = newY;
    gameMap[player.y][player.x] = player.symbol;
}

string AIController::enum_to_string(AIState state){
    switch (state) {
        case AIState::ESCAPE: return "ESCAPE";
        case AIState::WAIT_EXPLOSION: return "WAIT_EXPLOSION";
        case AIState::FETCH_ITEMS: return "FETCH_ITEMS";
        case AIState::ATTACK_PLAYER: return "ATTACK_PLAYER";
        case AIState::IDLE: return "IDLE";
        default: return "UNKNOWN_STATE";
    }
}