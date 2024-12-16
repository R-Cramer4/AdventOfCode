#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Score{
    unsigned int l = INT_MAX - 1;
    unsigned int r = INT_MAX - 1;
    unsigned int u = INT_MAX - 1;
    unsigned int d = INT_MAX - 1;
};

vector<vector<int>> map;
pair<int, int> start;
pair<int, int> endPos;
int find_best_path();

int main(){
    string temp;
    while(getline(cin, temp)){
        vector<int> m;
        for(int i = 0; i < temp.size(); i++){
            switch (temp[i]) {
                case '#':
                    m.push_back(1);
                    break;
                case '.':
                    m.push_back(0);
                    break;
                case 'S':
                    m.push_back(2);
                    start = {i, map.size()};
                    break;
                case 'E':
                    m.push_back(3);
                    endPos = {i, map.size()};
                    break;
            }
        }
        map.push_back(m);
    }
    int best_path = find_best_path();
    cout << "The best path has a score of " << best_path << endl;
}

int find_best_path(){
    char dir = 'R'; // the reindeer always starts facing to the right
    Score scores[map.size()][map[0].size()];
    scores[start.second][start.first].r = 0;

    queue<pair<pair<int, int>, char>> nodes;
    nodes.push({{start.first, start.second}, dir});

    while(!nodes.empty()){
        // check all neighbors if we can go there
        // if the score to get there is lower than the score there, we go there
        auto n = nodes.front();
        nodes.pop();

        int newScore;
        int score;
        int x = n.first.first;
        int y = n.first.second;
        switch (n.second) {
            case 'R':
                score = scores[y][x].r;
                break;
            case 'L':
                score = scores[y][x].l;
                break;
            case 'U':
                score = scores[y][x].u;
                break;
            case 'D':
                score = scores[y][x].d;
                break;
        
        }
        if(n.second != 'R' && map[y][x - 1] != 1){
            if(n.second == 'L') newScore = 1 + score;
            else newScore = 1001 + score;
            // can move left
            if(newScore < scores[y][x - 1].l){
                scores[y][x - 1].l = newScore;
                nodes.push({{x - 1, y}, 'L'});
            }
        }
        if(n.second != 'L' && map[y][x + 1] != 1){
            if(n.second == 'R') newScore = 1 + score;
            else newScore = 1001 + score;
            // can move right
            if(newScore < scores[y][x + 1].r){
                scores[y][x + 1].r = newScore;
                nodes.push({{x + 1, y}, 'R'});
            }
        }
        if(n.second != 'D' && map[y - 1][x] != 1){
            if(n.second == 'U') newScore = 1 + score;
            else newScore = 1001 + score;
            // can move up
            if(newScore < scores[y - 1][x].u){
                scores[y - 1][x].u = newScore;
                nodes.push({{x, y - 1}, 'U'});
            }
        }
        if(n.second != 'U' && map[y + 1][x] != 1){
            if(n.second == 'D') newScore = 1 + score;
            else newScore = 1001 + score;
            // can move down
            if(newScore < scores[y + 1][x].d){
                scores[y + 1][x].d = newScore;
                nodes.push({{x, y + 1}, 'D'});
            }
        }
    }
    Score d = scores[endPos.second][endPos.first];
    return min(min(d.l, d.r), min(d.u, d.d));
}
