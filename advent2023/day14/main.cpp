#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
using namespace std;

void tiltNorth(vector<string> *rocks);
void moveRockNorth(vector<string> *rocks, int y, int x);

void tiltSouth(vector<string> *rocks);
void moveRockSouth(vector<string> *rocks, int y, int x);

void tiltWest(vector<string> *rocks);
void moveRockWest(vector<string> *rocks, int y, int x);

void tiltEast(vector<string> *rocks);
void moveRockEast(vector<string> *rocks, int y, int x);

int findLoad(vector<string> rocks);


int main(){
    string temp;
    vector<string> rocks;

    while(getline(cin, temp)){
        rocks.push_back(temp);
    }
    map<int, pair<int, int>> loads; // key is load, value is {lastOcc, cycle length}
    int ans = 0;
    for(int i = 0; i < 1000000000; i++){
        // need to check for cycles so i dont have to do 1 trillion loops
        tiltNorth(&rocks);
        tiltWest(&rocks);
        tiltSouth(&rocks);
        tiltEast(&rocks);
        int temp = findLoad(rocks);
        map<int, pair<int, int>>::iterator it;
        it = loads.find(temp);
        if(it != loads.end()){
            it->second.second = i - it->second.first; // cycle length for this number
            it->second.first = i; // last occurrance
        }else{
            loads.insert({temp, {i, 0}});
        }
        // in my map i have the cycle length, every time i hit the cycle i check if 1,000,000,000 - i % cycle length == 0
        // if it is that is my answer and i can exit
    }
    if(ans == 0) ans = findLoad(rocks);
    
    cout << "Total load is " << ans << "\n";
    // 101016 is too high
}

void tiltNorth(vector<string> *rocks){
    // one rock at a time
    for(int i = 0; i < rocks->size(); i++){
        for(int j = 0; j < rocks->at(i).size(); j++){
            if(rocks->at(i)[j] == 'O') moveRockNorth(rocks, i, j);
        }
    }

}
void moveRockNorth(vector<string> *rocks, int y, int x){
    bool canMove = true;
    while(canMove){
        if(y == 0) break;
        if(rocks->at(y - 1)[x] == '.'){
            rocks->at(y - 1)[x] = 'O';
            rocks->at(y)[x] = '.';
            y--;
        }else{
            canMove = false;
        }
    }
}
void tiltSouth(vector<string> *rocks){
    // one rock at a time
    for(int i = rocks->size() - 1; i >= 0; i--){
        for(int j = 0; j < rocks->at(i).size(); j++){
            if(rocks->at(i)[j] == 'O') moveRockSouth(rocks, i, j);
        }
    }
}
void moveRockSouth(vector<string> *rocks, int y, int x){
    bool canMove = true;
    while(canMove){
        if(y == rocks->size() - 1) break;
        if(rocks->at(y + 1)[x] == '.'){
            rocks->at(y + 1)[x] = 'O';
            rocks->at(y)[x] = '.';
            y++;
        }else{
            canMove = false;
        }
    }
}

void tiltWest(vector<string> *rocks){
    for(int i = 0; i < rocks->at(0).size(); i++){
        for(int j = 0; j < rocks->size(); j++){
            if(rocks->at(j)[i] == 'O') moveRockWest(rocks, j, i);
        }
    }
}
void moveRockWest(vector<string> *rocks, int y, int x){
    bool canMove = true;
    while(canMove){
        if(x == 0) break;
        if(rocks->at(y)[x - 1] == '.'){
            rocks->at(y)[x - 1] = 'O';
            rocks->at(y)[x] = '.';
            x--;
        }else{
            canMove = false;
        }
    }
}

void tiltEast(vector<string> *rocks){
    for(int i = rocks->at(0).size() - 1; i >= 0; i--){
        for(int j = 0; j < rocks->size(); j++){
            if(rocks->at(j)[i] == 'O') moveRockEast(rocks, j, i);
        }
    }
}
void moveRockEast(vector<string> *rocks, int y, int x){
    bool canMove = true;
    while(canMove){
        if(x == rocks->at(0).size() - 1) break;
        if(rocks->at(y)[x + 1] == '.'){
            rocks->at(y)[x + 1] = 'O';
            rocks->at(y)[x] = '.';
            x++;
        }else{
            canMove = false;
        }
    }

}
int findLoad(vector<string> rocks){
    int ans = 0;
    for(int i = 0; i < rocks.size(); i++){
        for(int j = 0; j < rocks[i].size(); j++){
            if(rocks[i][j] == 'O'){
                ans += rocks.size() - i;
            }
        }
    }
    return ans;
}
