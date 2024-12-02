#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

void printHole(vector<vector<int>> holeArea);
int holeSize(vector<pair<int, int>> hole);

int main(){
    string temp;
    vector<pair<char, int>> directions;
    vector<string> colors;

    while(getline(cin, temp)){
        pair<char, int> tempDir;
        tempDir.first = temp[0];
        temp.erase(0, temp.find(' ') + 1);
        tempDir.second = stoi(temp.substr(0, temp.find(' ')));
        directions.push_back(tempDir);

        temp.erase(0, temp.find('#') + 1);
        colors.push_back(temp.substr(0, temp.find(')')));
    }
    vector<pair<int, int>> hole; // pair is the location of the hole, string is the edge color
    int x = 0;
    int y = 0;
    hole.push_back({0, 0});
    for(int i = 0; i < directions.size(); i++){
        for(int j = 0; j < directions[i].second; j++){
            switch(directions[i].first){
                case 'L':
                    x--;
                    break;
                case 'R':
                    x++;
                    break;
                case 'U':
                    y--;
                    break;
                case 'D':
                    y++;
                    break;
                default:
                    cout << "uhoh\n";
            }
            hole.push_back({x, y});
        }
    }
    int size = holeSize(hole);
    cout << "total area for part 1 = " << size << "\n";
    vector<pair<int, int>> hole2;
    x = 0;
    y = 0;
    hole2.push_back({0, 0});
    for(int i = 0; i < colors.size(); i++){
        for(int j = 0; j < stoi(colors[i].substr(0, 5), nullptr, 16); j++){
            switch (colors[i].at(5)) {
                case '0':
                    x++;
                    break;
                case '1':
                    y++;
                    break;
                case '2':
                    x--;
                    break;
                case '3':
                    y--;
                    break;
                default:
                    cout << "uhoh\n";
            }
            hole2.push_back({x, y});
        }
    }
    cout << "\n";
    size = holeSize(hole2);
    cout << "total area for part 2 = " << size << "\n";
}

int holeSize(vector<pair<int, int>> hole){
    cout << "called with hole size " << hole.size() << "\n";
    // find the x, y coord range
    pair<int, int> xRange = {0, 0};
    pair<int, int> yRange = {0, 0};
    for(int i = 0; i < hole.size(); i++){
        if(hole[i].first < xRange.first) xRange.first = hole[i].first;
        if(hole[i].first > xRange.second) xRange.second = hole[i].first;
        if(hole[i].second < yRange.first) yRange.first = hole[i].second;
        if(hole[i].second > yRange.second) yRange.second = hole[i].second;
    }
    vector<vector<int>> holeArea(
            yRange.second - yRange.first + 1, vector<int>(xRange.second - xRange.first + 1, 0));
    xRange.first = abs(xRange.first);
    yRange.first = abs(yRange.first);
    cout << "generating graph\n";
    for(int i = 0; i < hole.size(); i++){
        holeArea.at(hole.at(i).second + yRange.first).at(hole.at(i).first + xRange.first) = 1;
        // aligns the upper left most corner at 0,0 and makes a boundary
    }
    //printHole(holeArea);

    // same thing as day 10, if cross a boundary, start marking stuff as inside or vise versa
    int size = 0;
    cout << "filling\n";
    for(int i = 0; i < holeArea.size(); i++){
        bool inside = false;
        char lastTurn = ' '; // can be L, J, 7, F : These are the different types of turns
        for(int j = 0; j < holeArea[0].size(); j++){
            if(holeArea[i][j] == 1){
                // regular edge
                if(j == 0 && holeArea[i][j + 1] == 0) inside = !inside;
                else if(j > 0 && j < holeArea[0].size() - 2 &&
                        (holeArea[i][j - 1] == 2 || holeArea[i][j - 1] == 0) && holeArea[i][j + 1] == 0) inside = !inside;
                else if(j < holeArea[0].size() - 2 && holeArea[i][j + 1] == 1){
                    // either a F or L turn
                    // F
                    if(i < holeArea.size() - 2 && holeArea[i + 1][j] == 1){
                        lastTurn = 'F';
                        inside = !inside;
                    }
                    // L
                    if(i > 0 && holeArea[i - 1][j] == 1){
                        lastTurn = 'L';
                        inside = !inside;
                    }
                }
                else{
                    // either a 7 or J turn
                    if(i < holeArea.size() - 2 && holeArea[i + 1][j] == 1){
                        // 7 turn
                        if(lastTurn == 'F') inside = !inside;
                        lastTurn = '7';
                    }
                    if(i > 0 && holeArea[i - 1][j] == 1){
                        // J turn
                        if(lastTurn == 'L') inside = !inside;
                        lastTurn = 'L';
                    }
                }
            }
            else if(inside){
                holeArea[i][j] = 2;
            }
            if(holeArea[i][j]) size++;
        }
    }
    //printHole(holeArea);
    return size;
}


void printHole(vector<vector<int>> holeArea){
    for(int i = 0; i < holeArea.size(); i++){
        cout << "\n";
        for(int j = 0; j < holeArea.size(); j++){
            if(holeArea[i][j] == 1 || holeArea[i][j] == 2) cout << '#';
            else cout << '.';
        }
    }
    cout << "\n\n";
}
