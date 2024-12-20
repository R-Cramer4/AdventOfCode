#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <thread>
#include <vector>
using namespace std;

#define CHEAT_LENGTH 20
#define THREADS 16

vector<vector<int>> inMap;
pair<int, int> endPos;
vector<pair<int, int>> path;
map<pair<int, int>, int> seen;


int find_path(int x, int y, bool orig);
int dist(pair<int, int> p1, pair<int, int> p2);
void getNumPaths(int start, int end, int pathLen, unsigned long long int &ret);

int main(){
    string temp;
pair<int, int> start;

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
                    start = {i, inMap.size()};
                    break;
                case 'E':
                    m.push_back(3);
                    endPos = {i, inMap.size()};
                    break;
            }
        }
        inMap.push_back(m);
    }
    int pathLen = find_path(start.first, start.second, true);
    cout << "Path has length of " << pathLen << endl;
    // path holds the path we take
    // at each step we search from all cheats we can make from there
    // if we save time, add to the number of cheats

    vector<thread> threads;
    unsigned long long int results[THREADS];
    int len = path.size() / THREADS;
    for(int i = 0; i < THREADS; i++){
        threads.emplace_back(getNumPaths, (i * len), (i + 1) * len, pathLen, ref(results[i]));
    }
    
    unsigned long long int numCheats = 0;
    for(auto& t : threads){
        t.join();
    }
    for(int i = 0; i < THREADS; i++){
        numCheats += results[i];
    }

    /* part 1
    for(int i = 1; i < inMap.size() - 1; i++){
        cout << '\r' << i << flush;
        for(int j = 1; j < inMap[i].size() - 1; j++){
            if(inMap[i][j] == 1){
                inMap[i][j] = 0;
                int newPath = find_path();
                inMap[i][j] = 1;
                if(newPath + 100 <= path) numCheats++;
            }
        }
    }
    */
    cout << endl << "Number of cheats = " << numCheats << endl;

}
void getNumPaths(int start, int end, int pathLen, unsigned long long &ret){
    unsigned long long int numCheats = 0;
    for(int i = start; i < end; i++){
        //cout << path[i].first << ", " << path[i].second << endl;
        // each cheat is identified by its start and end
        // so length = i + cheat length + find_path(cheat_end.x, cheat_end.y, false);
        for(int k = 0; k < inMap.size(); k++){
            for(int j = 0; j < inMap[k].size(); j++){
                if(inMap[k][j] == 1) continue;
                int cheatLength = dist({j, k}, path[i]);
                if(cheatLength <= CHEAT_LENGTH){
                    // can cheat
                    int newLen = i + cheatLength + find_path(j, k, false);
                    if(newLen + 100 <= pathLen) numCheats++;
                }
            }
        }
    }
    ret = numCheats;
}
int find_path(int x, int y, bool orig){
    try {
        return seen.at({x, y});
    
    } catch (...) {}

    pair<int, int> start = {x, y};
    queue<pair<int, int>> q;
    vector<vector<pair<int, int>>> parents;
    vector<vector<int>> visited;
    for(int i = 0; i < inMap.size(); i++){
        vector<pair<int, int>> p;
        vector<int> v;
        for(int j = 0; j < inMap[i].size(); j++){
            p.push_back({0, 0});
            v.push_back(0);
        }
        parents.push_back(p);
        visited.push_back(v);
    }
    visited[start.second][start.first] = 1;
    parents[start.second][start.first] = {-1, -1};
    q.push(start);
    while(!q.empty()){
        auto n = q.front();
        q.pop();

        if(n.first - 1 >= 0 &&!visited[n.second][n.first - 1] && 
                inMap[n.second][n.first - 1] != 1){
            q.push({n.first - 1, n.second});
            visited[n.second][n.first - 1] = 1;
            parents[n.second][n.first - 1] = n;
        }
        if(n.first + 1 < inMap[0].size() && !visited[n.second][n.first + 1] && 
                inMap[n.second][n.first + 1] != 1){
            q.push({n.first + 1, n.second});
            visited[n.second][n.first + 1] = 1;
            parents[n.second][n.first + 1] = n;
        }
        if(n.second - 1 >= 0 && !visited[n.second - 1][n.first] && 
                inMap[n.second - 1][n.first] != 1){
            q.push({n.first, n.second - 1});
            visited[n.second - 1][n.first] = 1;
            parents[n.second - 1][n.first] = n;
        }
        if(n.second + 1 < inMap.size() && !visited[n.second + 1][n.first] && 
                inMap[n.second + 1][n.first] != 1){
            q.push({n.first, n.second + 1});
            visited[n.second + 1][n.first] = 1;
            parents[n.second + 1][n.first] = n;
        }
    }
    // iterate through parents
    int length = 0;
    if(orig) path.push_back(endPos);
    auto p = parents[endPos.second][endPos.first];
    while(p.first != -1 && p.second != -1){
        if(orig) path.insert(path.begin(), p);
        length++;
        p = parents[p.second][p.first];
    }
    seen.insert({{x, y}, length});
    return length;
}
int dist(pair<int, int> p1, pair<int, int> p2){
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

