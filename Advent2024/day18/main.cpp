#include <cstdlib>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
using namespace std;

int bfs();
int map[71][71];
void printMap();

int main(){
    string temp;

    while(getline(cin, temp)){
        int comma = temp.find(',');
        map[stoi(temp.substr(0, comma))][stoi(temp.substr(comma + 1))] = 1;
        if(bfs() == 0){
            cout << "failed after " << temp << " fell" << endl;
            break;
        }
    }
    //int steps = bfs();

    //printMap();

    //cout << "Number of steps after a kilobyte = " << steps << endl;

}
int bfs(){
    int steps = 0;
    int visited[71][71];
    pair<int, int> parent[71][71];
    for(int i = 0; i < 71; i++){
        for(int j = 0; j < 71; j++){
            parent[i][j] = {-1, -1};
            visited[i][j] = 0;
        }
    }
    queue<pair<int, int>> nodes;
    nodes.push({0, 0});
    visited[0][0] = 1;
    parent[0][0] = {0, 0};
    while(!nodes.empty()){
        auto n = nodes.front();
        nodes.pop();
        if(n.first - 1 >= 0){
            // push left
            if(!visited[n.first - 1][n.second] && map[n.first - 1][n.second] != 1){
                visited[n.first - 1][n.second] = 1;
                nodes.push({n.first - 1, n.second});
                parent[n.first - 1][n.second] = n;
            }
        }
        if(n.first + 1 < 71){
            // push right
            if(!visited[n.first + 1][n.second] && map[n.first + 1][n.second] != 1){
                visited[n.first + 1][n.second] = 1;
                nodes.push({n.first + 1, n.second});
                parent[n.first + 1][n.second] = n;
            }
        }
        if(n.second - 1 >= 0){
            // push up
            if(!visited[n.first][n.second - 1] && map[n.first][n.second - 1] != 1){
                visited[n.first][n.second - 1] = 1;
                nodes.push({n.first, n.second - 1});
                parent[n.first][n.second - 1] = n;
            }
        }
        if(n.second + 1 < 71){
            // push up
            if(!visited[n.first][n.second + 1] && map[n.first][n.second + 1] != 1){
                visited[n.first][n.second + 1] = 1;
                nodes.push({n.first, n.second + 1});
                parent[n.first][n.second + 1] = n;
            }
        }
    }

    pair<int, int> p = {70, 70};
    while(p.first != 0 || p.second != 0){
        //printMap();
        //cout << p.first << ", " << p.second << endl;
        if(p.first < 0 || p.second< 0){
            cout << "No path" << endl;
            return 0;
        }
        if(p.first > 70 || p.second > 70){
            cout << "What" << endl;
            return 0;
        }
        map[p.first][p.second] = 2;
        steps++;
        p = parent[p.first][p.second];
    }

    return steps;
}
void printMap(){
    system("clear");
    cout << "\n";
    for(int i = 0; i < 71; i++){
        for(int j = 0; j < 71; j++){
            switch (map[i][j]){
                case 0:
                    cout << '.';
                    break;
                case 1:
                    cout << '#';
                    break;
                case 2:
                    cout << 'O';
                    break;
            }
        }
        cout << '\n';
    }
    cout << endl << flush;
}
