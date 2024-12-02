#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
using namespace std;
enum direc {north, south, east, west, none};

int main(){
    string temp;
    vector<string> loop;
    vector<vector<pair<int, pair<int, int>>>> isLoop; // first int is if its in the loop, next it is where to go next
    pair<int, int> currentLoc;

    while(getline(cin, temp)){
        loop.push_back(temp);
        vector<pair<int, pair<int, int>>> tempLoop;
        for(int i = 0; i < temp.size(); i++){
            tempLoop.push_back({0, {0, 0}});
        }
        isLoop.push_back(tempLoop);
        if(temp.find('S') != -1){
            currentLoc.first = loop.size() - 1;
            currentLoc.second = temp.find('S');
        }
    }
    int steps = 0;
    // all of these positions are based on coming from on top or from the left
    map<char, pair<direc, direc>> pipes = {
        {'|', {north, south}}, 
        {'-', {west, east}}, 
        {'L', {north, east}}, 
        {'J', {west, north}}, 
        {'7', {west, south}}, 
        {'F', {south, east}}, 
        {'.', {none, none}},
        {'S', {none, none}}};

    if(pipes.at(loop[currentLoc.first][currentLoc.second + 1]).first == west){
        isLoop[currentLoc.first][currentLoc.second] = {1, {currentLoc.first, currentLoc.second + 1}};
        currentLoc.second++;
        steps++;
    }else if(pipes.at(loop[currentLoc.first + 1][currentLoc.second]).first == south){
        isLoop[currentLoc.first][currentLoc.second] = {1, {currentLoc.first + 1, currentLoc.second}};
        currentLoc.first++;
        steps++;
    }else if(pipes.at(loop[currentLoc.first - 1][currentLoc.second]).second == north){
        cout << "uhoh";
    }else if(pipes.at(loop[currentLoc.first][currentLoc.second - 1]).second == east){
        cout << "uhoh pt2";
    }else cout << "WTF\n";
    
    int side = 0; // this will be if i come in through the second or the first loc
    while(loop[currentLoc.first][currentLoc.second] != 'S'){
        // i just need to move to the pipe that has my second direction as its first
        pair<direc, direc> currentPipe = pipes.at(loop[currentLoc.first][currentLoc.second]);
        // cout << "\r" << currentLoc.first << ", " << currentLoc.second << " " << steps;
        pair<direc, direc> nextPipe;
        if(side == 0){
            // go out the second loc
            switch (currentPipe.second) {
                case north:
                    nextPipe = pipes.at(loop[currentLoc.first - 1][currentLoc.second]);
                    isLoop[currentLoc.first][currentLoc.second] = {1, {currentLoc.first - 1, currentLoc.second}};
                    currentLoc.first--;
                    if(nextPipe.first == south) side = 0;
                    else if(nextPipe.second == south) side = 1;
                    break;
                case south:
                    nextPipe = pipes.at(loop[currentLoc.first + 1][currentLoc.second]);
                    isLoop[currentLoc.first][currentLoc.second] = {1, {currentLoc.first + 1, currentLoc.second}};
                    currentLoc.first++;
                    if(nextPipe.first == north) side = 0;
                    else if(nextPipe.second == north) side = 1;
                    break;
                case east:
                    nextPipe = pipes.at(loop[currentLoc.first][currentLoc.second + 1]);
                    isLoop[currentLoc.first][currentLoc.second] = {1, {currentLoc.first, currentLoc.second + 1}};
                    currentLoc.second++;
                    if(nextPipe.first == west) side = 0;
                    else if(nextPipe.second == west) side = 1;
                    break;
                case west:
                    nextPipe = pipes.at(loop[currentLoc.first][currentLoc.second - 1]);
                    isLoop[currentLoc.first][currentLoc.second] = {1, {currentLoc.first, currentLoc.second - 1}};
                    currentLoc.second--;
                    if(nextPipe.first == east) side = 0;
                    else if(nextPipe.second == east) side = 1;
                    break;
                default:
                    break;
            }
        }
        else{
            switch (currentPipe.first) {
                case north:
                    nextPipe = pipes.at(loop[currentLoc.first - 1][currentLoc.second]);
                    isLoop[currentLoc.first][currentLoc.second] = {1, {currentLoc.first - 1, currentLoc.second}};
                    currentLoc.first--;
                    if(nextPipe.first == south) side = 0;
                    else if(nextPipe.second == south) side = 1;
                    break;
                case south:
                    nextPipe = pipes.at(loop[currentLoc.first + 1][currentLoc.second]);
                    isLoop[currentLoc.first][currentLoc.second] = {1, {currentLoc.first + 1, currentLoc.second}};
                    currentLoc.first++;
                    if(nextPipe.first == north) side = 0;
                    else if(nextPipe.second == north) side = 1;
                    break;
                case east:
                    nextPipe = pipes.at(loop[currentLoc.first][currentLoc.second + 1]);
                    isLoop[currentLoc.first][currentLoc.second] = {1, {currentLoc.first, currentLoc.second + 1}};
                    currentLoc.second++;
                    if(nextPipe.first == west) side = 0;
                    else if(nextPipe.second == west) side = 1;
                    break;
                case west:
                    nextPipe = pipes.at(loop[currentLoc.first][currentLoc.second - 1]);
                    isLoop[currentLoc.first][currentLoc.second] = {1, {currentLoc.first, currentLoc.second - 1}};
                    currentLoc.second--;
                    if(nextPipe.first == east) side = 0;
                    else if(nextPipe.second == east) side = 1;
                    break;
                default:
                    break;
            }
        }
        steps++;
    }
    cout << "Steps / 2 = " << steps / 2 << "\n";

    // scan left to right, if cross pipe switch inside flag
    int spotsIn = 0;
    for(int i = 0; i < isLoop.size(); i++){
        bool isIn = false;
        char lastCross = '.';
        for(int j = 0; j < isLoop[i].size(); j++){
            if(isLoop[i][j].first == 1){
                switch(loop[i][j]){
                    case '|':
                        isIn = !isIn;
                        lastCross = '|';
                        break;
                    case 'L':
                        isIn = !isIn;
                        lastCross = 'L';
                        break;
                    case 'J':
                        if(lastCross != 'F'){
                            isIn = !isIn;
                            lastCross = 'J';
                        }
                        break;
                    case '7':
                        if(lastCross != 'L'){
                            isIn = !isIn;
                            lastCross = '7';
                        }
                        break;
                    case 'F':
                        isIn = !isIn;
                        lastCross = 'F';
                        break;
                }

            }else if(isIn) spotsIn++;
        }
    }
    cout << "spots inside = " << spotsIn << "\n";

    /*
    cout << "\n";
    for(int i = 0; i < isLoop.size(); i++){
        for(int j = 0; j < isLoop[i].size(); j++){
            cout << isLoop[i][j].first;
        }
        cout << "\n";
    }
    */

}
