#include <climits>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int findPath(vector<string> map);
int dijkstras(vector<string> map);

struct Node{
    int x;
    int y;
    int cost = INT_MAX;
    int stepsWithoutTurn = 0;
    Node *prev = nullptr;
    char direction;
};

int main(){
    string temp;
    vector<string> map;

    while(getline(cin, temp)){
        map.push_back(temp);
    }
    int ans = findPath(map);
    cout << "lowest heat loss = " << ans << "\n";
    // 14192 is too high

    return 0;
}

int dijkstras(vector<string> map){
    int result = 0;


    return result;
}

int findPath(vector<string> map){
    int ans = 0;
    vector<vector<Node>> nodes;
    for(int i = 0; i < map.size(); i++){
        nodes.push_back(vector<Node>());
        for(int j = 0; j < map[0].size(); j++){
            Node temp;
            temp.x = j;
            temp.y = i;
            nodes.at(i).push_back(temp);
        }
    }
    nodes.at(0).at(0).cost = 0;
    nodes.at(0).at(0).direction = 'U'; // so the initial step will be a turn

    queue<Node*> q;
    q.push(&nodes[0][0]);
    while(q.size() > 0){
        //cout << "\r" << q.size();
        Node *n = q.front();
        q.pop();
        // check neighbors, can't go backwards
        // only push that node if the current cost is less than the previous cost
        if(n->x > 0 && n->direction != 'R'){
            // check left
            Node *next = &nodes[n->y][n->x - 1];
            if(n->cost + map[next->y][next->x] < next->cost){
                if(n->direction == 'L') next->stepsWithoutTurn = n->stepsWithoutTurn + 1;
                if(next->stepsWithoutTurn <= 3){
                    next->cost = n->cost + map[next->y][next->x];
                    next->prev = n;
                    next->direction = 'L';
                    q.push(next);
                }
            }
        }
        if(n->x < nodes[0].size() - 1 && n->direction != 'L'){
            // right
            Node *next = &nodes[n->y][n->x + 1];
            if(n->cost + map[next->y][next->x] < next->cost){
                if(n->direction == 'R') next->stepsWithoutTurn = n->stepsWithoutTurn + 1;
                if(next->stepsWithoutTurn <= 3){
                    next->cost = n->cost + map[next->y][next->x];
                    next->prev = n;
                    next->direction = 'R';
                    q.push(next);
                }
            }
        }
        if(n->y > 0 && n->direction != 'D'){
            // up
            Node *next = &nodes[n->y - 1][n->x];
            if(n->cost + map[next->y][next->x] < next->cost){
                if(n->direction == 'U') next->stepsWithoutTurn = n->stepsWithoutTurn + 1;
                if(next->stepsWithoutTurn <= 3){
                    next->cost = n->cost + map[next->y][next->x];
                    next->prev = n;
                    next->direction = 'U';
                    q.push(next);
                }
            }
        }
        if(n->y < nodes.size() - 1 && n->direction != 'U'){
            // down
            Node *next = &nodes[n->y + 1][n->x];
            if(n->cost + map[next->y][next->x] < next->cost){
                if(n->direction == 'D') next->stepsWithoutTurn = n->stepsWithoutTurn + 1;
                if(next->stepsWithoutTurn <= 3){
                    next->cost = n->cost + map[next->y][next->x];
                    next->prev = n;
                    next->direction = 'D';
                    q.push(next);
                }
            }
        }
    }
    
    ans = nodes[nodes.size() - 1][nodes[0].size() - 1].cost;
    /*
    Node temp = nodes[nodes.size() - 1][nodes[0].size() - 1];
    while(temp.prev != nullptr){
        cout << temp.x << ", " << temp.y << "\n";
        temp = *temp.prev;
        ans += map[temp.y][temp.x];
    }
    */

    return ans;
}
