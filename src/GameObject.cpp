#include "GameObject.h"

static struct termios orig_termios;

vector<LeaderboardEntry> leaderboard;

void GameObject::resetTerminalMode(){
    tcsetattr(0, TCSANOW, &orig_termios);
    tcflush(0, TCIFLUSH);
}

int GameObject::kbhit() {
    struct timeval tv = {0, 0};
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    return select(1, &readfds, NULL, NULL, &tv);
}

int GameObject::getch() {
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0)return -1;
    else return c;
}

void GameObject::setConioTerminalMode() {
    struct termios new_termios;
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));
    new_termios.c_lflag &= ~(ICANON | ECHO);
    new_termios.c_cc[VTIME] = 0;
    new_termios.c_cc[VMIN] = 0;
    tcsetattr(0, TCSANOW, &new_termios);
}

string GameObject::centerText(const string &text, int width) {
    int padding = (width - (int)text.length()) / 2;
    return string(padding, ' ') + text + string(width - (int)text.length() - padding, ' ');
}

string GameObject::leftAlignText(const string &text, int prefixSpaces, int width) {
    int remainingSpace = width - (int)text.length() - prefixSpaces;
    remainingSpace = max(0, remainingSpace);
    return string(prefixSpaces, ' ') + text + string(remainingSpace, ' ');
}

void GameObject::loadLeaderboard(){
    ifstream file("assets/leaderboard.txt");
    string line;
    while(getline(file,line)){
        stringstream ss(line);
        LeaderboardEntry entry;
        ss >> entry.playerName >> entry.score >> entry.time;
        leaderboard.push_back(entry);
    }
    file.close();
}

int GameObject::updateLeaderboard(const string &winnerName, int winnerScore, int matchTime){
    LeaderboardEntry newEntry = {winnerName, winnerScore, matchTime};
    leaderboard.push_back(newEntry);

    sort(leaderboard.begin(), leaderboard.end(), [](const LeaderboardEntry &a, const LeaderboardEntry &b){
        if(a.score == b.score) return a.time < b.time;
        return a.score > b.score;
    });

    if (leaderboard.size() > 10)leaderboard.resize(10);
    int ind = -1;
    for(int i = 0;i < leaderboard.size();i++){
        if(winnerName == leaderboard[i].playerName){
            ind = i;
            break;
        }
    }
    return ind+1;
}

void GameObject::displayLeaderboard() {
    cout << "\033[2J\033[H";
    cout << "Loading Leaderboard...\n";
    usleep(500000);
    resetTerminalMode();
    cout << "\033[2J\033[H";
    cout << "====== Leaderboard ======\n";
    cout << "Leaderboard size: "<<leaderboard.size()<<endl;
    cout << "Name\t\tScore\tTime(s)\n";
    cout << "----------------------------\n";
    for (const auto &entry : leaderboard) {
        cout << setw(15) << left << entry.playerName
             << setw(10) << entry.score
             << setw(8) << entry.time << "\n";
    }
    cout << "=========================\n";
    cout << "Press enter to return to menu...\n";

    cin.get();
    setConioTerminalMode();
}
