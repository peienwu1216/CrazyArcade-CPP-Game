#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include "GameObject.h"
#include <vector>
#include <string>
#include <utility>

enum class AIState {
    ESCAPE,
    WAIT_EXPLOSION,
    FETCH_ITEMS,
    ATTACK_PLAYER,
    IDLE,
};


class AIController : public GameObject {
private:
    // Movement and AI parameters
    int aiMoveCounter = 0;
    int aiStuckCounter = 0;
    int aiStuckThreshold = 5;
    int lastAiY = -1;
    int lastAiX = -1;

    bool aiRecentlyPlacedBomb = false;
    time_t lastBombTime = 0;  
    double bombWaitDuration = 2.0; // seconds to wait after bomb placed before fetching items

    vector<pair<int,int>> currentPath;
    int currentPathIndex = 0;
    time_t stateStartTime;

    vector<vector<bool>> computeDangerMap();
    bool canEscapeAfterBomb(const Player &computerPlayer);
    bool shouldPlaceBombToAttack(const Player &computerPlayer, const Player &humanPlayer);
    bool shouldPlaceBombToClear(const Player &computerPlayer);
    void placeBombSafely(Player &computerPlayer);
    
    vector<pair<int,int>> bfsFindPath(const Player &start, const vector<pair<int,int>> &targets, bool avoidDanger = true);
    vector<pair<int,int>> getSafeCells();
    vector<pair<int,int>> getItemCells();
    vector<pair<int,int>> getPlayerCell(const Player &humanPlayer);
    vector<pair<int,int>> getObstaclesNearby(const Player &computerPlayer);

    void moveAlongPath(Player &computerPlayer);
    char movePlayerRandomDirection(const Player &computerPlayer);

    void startState(AIState newState);
    bool isTimeToReevaluateState();
    void updateState(Player &computerPlayer, Player &humanPlayer);

    // State handling
    void handleEscapeState(Player &computerPlayer);
    void handleWaitExplosionState(Player &computerPlayer);
    void handleFetchItemsState(Player &computerPlayer);
    void handleAttackPlayerState(Player &computerPlayer, Player &humanPlayer);
    void handleIdleState(Player &computerPlayer, Player &humanPlayer);

    void chooseEscapePath(Player &computerPlayer);
    void chooseFetchItemsPath(Player &computerPlayer);
    void chooseAttackPath(Player &computerPlayer, Player &humanPlayer);

public:
    AIState currentState = AIState::IDLE;
    void movePlayer(Player &player, char input);
    void placeBomb(Player &player, int owner);
    void moveToNewPlace(Player &player,int x,int y,int newX,int newY);
    string enum_to_string(AIState state);
    void computeMove(Player &computerPlayer, Player &humanPlayer);
};

#endif