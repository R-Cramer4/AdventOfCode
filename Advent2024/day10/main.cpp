#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

vector<vector<int>> map;

int findPaths(int x, int y){ // x, y are the coordinates of a 0
    int numPaths = 0;
    queue<pair<int, int>> next;
    vector<pair<int, int>> peaks;
    next.push({x, y});
    while(!next.empty()){
        pair<int, int> curLoc = next.front();
        next.pop();
        //cout << "(" << curLoc.first << ", " << curLoc.second << ")" << endl;
        // check 4 directions
        int comp = map[curLoc.second][curLoc.first];
        if(comp == 9){
            peaks.push_back({curLoc.first, curLoc.second});
            continue;
        }
        if(curLoc.first - 1 >= 0 && 
                map[curLoc.second][curLoc.first - 1] == comp + 1){ // left
            next.push({curLoc.first - 1, curLoc.second});
        }
        if(curLoc.first + 1 < map[0].size() && 
                map[curLoc.second][curLoc.first + 1] == comp + 1){ // right
            next.push({curLoc.first + 1, curLoc.second});
        }
        if(curLoc.second - 1 >= 0 && 
                map[curLoc.second - 1][curLoc.first] == comp + 1){ // up
            next.push({curLoc.first, curLoc.second - 1});
        }
        if(curLoc.second + 1 < map.size() && 
                map[curLoc.second + 1][curLoc.first] == comp + 1){ // down
            next.push({curLoc.first, curLoc.second + 1});
        }
    }
    sort(peaks.begin(), peaks.end(), [](pair<int, int> a, pair<int, int> b){
                if(a.first == b.first) return a.second > b.second;
                return a.first > b.first;
            });

    for(int i = 0; i < peaks.size() - 1; i++){
        //cout << peaks[i].first << ", " << peaks[i].second << endl;
        if(peaks[i].first != peaks[i + 1].first || peaks[i].second != peaks[i + 1].second) numPaths++;
    }
    if(peaks.size() > 0) numPaths++;

    // part 1
    // return numPaths;

    // part 2
    return peaks.size();
}

int main(){
    string temp;

    while(getline(cin, temp)){
        vector<int> tempv;
        for(int i = 0; i < temp.size(); i++) tempv.push_back(temp[i] - '0');
        map.push_back(tempv);
    }
    // have map
    int sumTrailheads = 0;
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            if(map[i][j] == 0) sumTrailheads += findPaths(j, i);
        }
    }
    cout << "Sum of all trailheads = " << sumTrailheads << endl;
}
