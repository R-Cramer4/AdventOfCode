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

struct Box{
    int x1;
    int x2;
    int y;
};

vector<vector<int>> map;
D robot;

void printMap();
void moveRobot(D dir);
bool push_if_can(D dir, Box b);
void move_box(D dir, Box b);
bool can_move_box(D dir, Box b);

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
                    m.push_back(1);
                    break;
                case 'O':
                    m.push_back(2);
                    m.push_back(3);
                    break;
                case '.':
                    m.push_back(0);
                    m.push_back(0);
                    break;
                case '@':
                    robot.x = i * 2;
                    robot.y = k;
                    m.push_back(4);
                    m.push_back(0);
                    break;
            }
        }
        map.push_back(m);
        k++;
    }

    while(getline(cin, temp)){
        // moves
        for(int i = 0; i < temp.size(); i++){
            // if(i % 5 == 0) printMap(); // creates a visualization
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
    bool move = false;
    Box b;
    switch (map[robot.y + dir.y][robot.x + dir.x]) {
        case 0:
            move = true;
            break;
        case 1:
            return; // cant move there
        case 4:
            cout << "This shouldnt happen" << endl;
            break;
        case 2:
            b = {robot.x + dir.x, robot.x + dir.x + 1, robot.y + dir.y};
            move = push_if_can(dir, b);
            break;
        case 3:
            b = {robot.x + dir.x - 1, robot.x + dir.x, robot.y + dir.y};
            move = push_if_can(dir, b);
            break;
    }
    if(move){
        map[robot.y][robot.x] = 0;
        robot.y += dir.y;
        robot.x += dir.x;
        map[robot.y][robot.x] = 4;
    }
}

bool push_if_can(D dir, Box b){
    bool yes = can_move_box(dir, b);
    if(yes) move_box(dir, b);
    return yes;
}
void move_box(D dir, Box b){
    // only call if we can move a box

    // first move boxes in the way
    if(b.x1 + dir.x != b.x2){
        // checks if box to the left and to the left and up/down
        if(map[b.y + dir.y][b.x1 + dir.x] == 3){
            // if the left hand side is touching a right hand side of a box
            Box a = {b.x1 + dir.x - 1, b.x1 + dir.x, b.y + dir.y};
            move_box(dir, a);
        }
    }
    if(b.x2 + dir.x != b.x1){
        // checks if box to the right and to the right and down
        if(map[b.y + dir.y][b.x2 + dir.x] == 2){
            // if the right hand side is touching a left hand side of a box
            Box c = {b.x2 + dir.x, b.x2 + dir.x + 1, b.y + dir.y};
            move_box(dir, c);
        }
    }
    // need to check if there is a box directly above or below
    if(abs(dir.y) == 1 && map[b.y + dir.y][b.x1] == 2){
        move_box(dir, {b.x1, b.x2, b.y + dir.y});
    }
    // all boxes moved out of the way
    // move ourselves
    map[b.y][b.x1] = 0;
    map[b.y][b.x2] = 0;
    map[b.y + dir.y][b.x1 + dir.x] = 2;
    map[b.y + dir.y][b.x2 + dir.x] = 3;
}
bool can_move_box(D dir, Box b){
    if(map[b.y + dir.y][b.x1 + dir.x] == 1 || map[b.y + dir.y][b.x2 + dir.x] == 1){ 
        // hits a wall
        return false;
    }
    if(abs(dir.y) == 1){ // can move up
        if(map[b.y + dir.y][b.x1] == 0 && map[b.y + dir.y][b.x2] == 0) return true;
    }
    if(dir.x == -1 && map[b.y][b.x1 -1] == 0) return true; 
    if(dir.x == 1 && map[b.y][b.x2 + 1] == 0) return true; // can move side to side
    


    int moveA = -1;
    int moveC = -1;
    if(b.x1 + dir.x != b.x2){
        if(map[b.y + dir.y][b.x1 + dir.x] == 3){
            // if the left hand side is touching a right hand side of a box
            Box a = {b.x1 + dir.x - 1, b.x1 + dir.x, b.y + dir.y};
            moveA = can_move_box(dir, a);
        }
    }
    if(b.x2 + dir.x != b.x1){
        if(map[b.y + dir.y][b.x2 + dir.x] == 2){
            // if the right hand side is touching a left hand side of a box
            Box c = {b.x2 + dir.x, b.x2 + dir.x + 1, b.y + dir.y};
            moveC = can_move_box(dir, c);
        }
    }
    if(moveA == -1 && moveC == -1){
        // need to check if there is a box directly above or below
        if(abs(dir.y) == 1){
            if(map[b.y + dir.y][b.x1] == 2){
                return can_move_box(dir, {b.x1, b.x2, b.y + dir.y});
            }else{
                return true;
            }
        }
    }
    // else we have moved a box or two
    if(moveA == -1) return moveC;
    if(moveC == -1) return moveA; // only moved 1 box
    
    // moved two boxes
    return moveA && moveC;

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
                    cout << '[';
                    break;
                case 3:
                    cout << ']';
                    break;
                case 4:
                    cout << '@';
                    break;
            }
        }
        cout << '\n';
    }
    cout << '\n' << flush;
}
