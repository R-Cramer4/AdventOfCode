#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct D{
    int x;
    int y;
};
D l = D{-1, 0};
D u = D{0, -1};
D r = D{1, 0};
D d = D{0, 1};

vector<vector<int>> map;
D robot;

void printMap();
void moveRobot(D dir);

int main(){
    string temp;

    int k = 0;
    while(getline(cin, temp)){
        if(temp == "") break;
        // map
        vector<int> m;
        for(int i = 0; i < temp.size(); i++){
            switch (temp[i]) {
                case '#':
                    m.push_back(1);
                    break;
                case 'O':
                    m.push_back(2);
                    break;
                case '.':
                    m.push_back(0);
                    break;
                case '@':
                    robot.x = i;
                    robot.y = k;
                    m.push_back(3);
                    break;
            }
        }
        map.push_back(m);
        k++;
    }

    while(getline(cin, temp)){
        // moves
        for(int i = 0; i < temp.size(); i++){
            switch (temp[i]) {
                case '<':
                    moveRobot(l);
                    break;
                case '^':
                    moveRobot(u);
                    break;
                case '>':
                    moveRobot(r);
                    break;
                case 'v':
                    moveRobot(d);
                    break;
            }
        }
    }
    int sumGPS = 0;
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            if(map[i][j] == 2){
                sumGPS += (i * 100) + j;
            }
        }
    }
    cout << "Final GPS positions = " << sumGPS << endl;
}

void moveRobot(D dir){
    //printMap();
    //cout << dir.x << ", " << dir.y << endl;
    switch (map[robot.y + dir.y][robot.x + dir.x]) {
        case 0:
            map[robot.y][robot.x] = 0;
            robot.y += dir.y;
            robot.x += dir.x;
            map[robot.y][robot.x] = 3;
            return;
        case 1:
            return; // cant move there
        case 3:
            cout << "This shouldnt happen" << endl;
            break;
        case 2:
            // traverse this direction until we hit a wall or empty space
            // if wall, we cant move
            // if empty space, make into a O, and move robot where it wants to go
            int i = 1;
            while(map[robot.y + (dir.y * i)][robot.x + (dir.x * i)] != 1 && i < map.size()){
                // while not a wall
                if(map[robot.y + (dir.y * i)][robot.x + (dir.x * i)] == 0){
                    // empty space
                    map[robot.y + (dir.y * i)][robot.x + (dir.x * i)] = 2;
                    map[robot.y][robot.x] = 0;
                    robot.y += dir.y;
                    robot.x += dir.x;
                    map[robot.y][robot.x] = 3;
                    return;
                }
                i++;
            }
            return;
    }
}


void printMap(){
    system("clear");
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            switch (map[i][j]) {
                case 0:
                    cout << '.';
                    break;
                case 1:
                    cout << '#';
                    break;
                case 2:
                    cout << 'O';
                    break;
                case 3:
                    cout << '@';
                    break;
            }
        }
        cout << '\n';
    }
    cout << '\n' << flush;
}
