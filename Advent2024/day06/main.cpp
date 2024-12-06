#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
using namespace std;


void printMap(int **map);
bool moveGuard(pair<int, int> guardLoc, int **guardMap);
void resetMap(int **map);

int main(){
    string temp;
    pair<int, int> guardLoc = {0, 0};
    pair<int, int> initGuardLoc;
    int **guardMap = new int*[130];
    for(int i = 0; i < 130; i++) guardMap[i] = new int[130];

    int line = 0;
    while(getline(cin, temp)){
        for(int i = 0; i < temp.size(); i++){
            switch (temp[i]){
                case '.':
                    guardMap[line][i] = 0;
                    break;
                case '#':
                    guardMap[line][i] = 1;
                    break;
                case '^':
                    guardMap[line][i] = 10;
                    // 10 is up, 11 is right, 12 is down, 13 is left
                    guardLoc = {line, i};
                    initGuardLoc = {line, i};
                    break;
            }
        }
        line++;
    }

    moveGuard(guardLoc, guardMap);

    int usedPos = 0;
    for(int i = 0; i < 130; i++){
        for(int j = 0; j < 130; j++){
            if(guardMap[i][j] < 0 || guardMap[i][j] > 1) usedPos++;
        }
    }
    cout << "Positions visited = " << usedPos << endl;
    resetMap(guardMap);

    int cycles = 0;
    pair<int, int> prev = {0, 0};
    for(int i = 0; i < 130; i++){
        for(int j = 0; j < 130; j++){
            if(initGuardLoc.first == i && initGuardLoc.second == j) continue;
            if(guardMap[i][j] == 1) continue;
            // test if we can add a blockade
            guardMap[prev.first][prev.second] = 0;
            guardMap[i][j] = 1;
            prev = {i, j};
            guardLoc = initGuardLoc;
            guardMap[guardLoc.first][guardLoc.second] = 10;

            //cout << '\r' << i << ", " << j << "\t\t\t" << flush;
            //cout << guardLoc.first << guardLoc.second << ", " << initGuardLoc.first << initGuardLoc.second << endl;
            if(moveGuard(guardLoc, guardMap)){
                //printMap(guardMap);
                cycles++;
            }
            resetMap(guardMap);
        }
    }
    // free
    for(int i = 0; i < 130; i++) delete [] guardMap[i];
    delete [] guardMap;

    cout << "Cycles = " << cycles << endl;
    // 1586
}
bool moveGuard(pair<int, int> guardLoc, int **guardMap){
    // have map, now move the guard
    int i = 0;
    while((guardLoc.first > 0 && guardLoc.first < 130) && 
            (guardLoc.second > 0 && guardLoc.second < 130)){
        i++;
        if(i > 30000) return true;
        //cout << '\r' << guardLoc.first << ", " << guardLoc.second << ": " << guardMap[guardLoc.first][guardLoc.second] << " : " << i << "\t\t\t" << flush;
        
        //printMap();
        // while the guard is in the board
        // need to check for turns, encode that it just turned
        int temp;
        switch (guardMap[guardLoc.first][guardLoc.second]){
            // visited is -1
            case 10:
            case 20:
                // up
                if(guardLoc.first - 1 >= 0){
                    temp = guardMap[guardLoc.first - 1][guardLoc.second];
                    if(temp <= 0){
                        if(temp == -10 || temp == -21) return true; // in a loop, could have double turns
                        // move guard
                        guardMap[guardLoc.first - 1][guardLoc.second] = 10;
                        guardMap[guardLoc.first][guardLoc.second] *= -1; // visited
                        guardLoc.first = guardLoc.first - 1;
                    }else{
                        // turn right
                        guardMap[guardLoc.first][guardLoc.second] = 21;
                    }
                }else guardLoc.first --; // leave the map
                break;
            case 11:
            case 21:
                // right
                if(guardLoc.second + 1 < 130){
                    temp = guardMap[guardLoc.first][guardLoc.second + 1];
                    if(temp <= 0){
                        if(temp == -11 || temp == -22) return true; // in a loop, could have double turns
                        // move guard
                        guardMap[guardLoc.first][guardLoc.second + 1] = 11;
                        guardMap[guardLoc.first][guardLoc.second] *= -1; // visited
                        guardLoc.second += 1;
                    }else{
                        // turn right
                        guardMap[guardLoc.first][guardLoc.second] = 22;
                    }
                }else guardLoc.second++; // leave the map
                break;
            case 12:
            case 22:
                // down
                if(guardLoc.first + 1 < 130){
                    temp = guardMap[guardLoc.first + 1][guardLoc.second];
                    if(temp <= 0){
                        if(temp == -12 || temp == -23) return true; // in a loop, could have double turns
                        // move guard
                        guardMap[guardLoc.first + 1][guardLoc.second] = 12;
                        guardMap[guardLoc.first][guardLoc.second] *= -1; // visited
                        guardLoc.first = guardLoc.first + 1;
                    }else{
                        // turn right
                        guardMap[guardLoc.first][guardLoc.second] = 23;
                    }
                }else guardLoc.first++; // leave the map
                break;
            case 13:
            case 23:
                //left
                if(guardLoc.second - 1 >= 0){
                    temp = guardMap[guardLoc.first][guardLoc.second - 1];
                    if(temp <= 0){
                        if(temp == -13 || temp == -20) return true; // in a loop, could have double turns
                        // move guard
                        guardMap[guardLoc.first][guardLoc.second - 1] = 13;
                        guardMap[guardLoc.first][guardLoc.second] *= -1; // visited
                        guardLoc.second = guardLoc.second - 1;
                    }else{
                        // turn right
                        guardMap[guardLoc.first][guardLoc.second] = 20;
                    }
                }else guardLoc.second--; // leave the map
                break;
        }
    }
    return false;
}
void resetMap(int **map){
    for(int i = 0; i < 130; i++){
        for(int j = 0; j < 130; j++){
            if(map[i][j] != 1) map[i][j] = 0;
        }
    }
}
void printMap(int ** guardMap){
    system("clear");
    for(int i = 0; i < 130; i++){
        for(int j = 0; j < 130; j++){
            switch(guardMap[i][j]){
                case -1:
                    cout << 'X';
                    break;
                case 0:
                    cout << '.';
                    break;
                case 1:
                    cout << '#';
                    break;
                default:
                    cout << '^';
            }
        }
        cout << endl;
    }
}
