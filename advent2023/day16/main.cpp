#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct beam{
    int x;
    int y;
    char direc; // L, R, U, D
                // left, right, up, down
};

int propagateBeams(beam be, map<pair<int, int>, int> energy, vector<string> tiles, vector<pair<pair<int, int>, char>> visited);

int main(){
    string temp;
    vector<string> tiles;
    map<pair<int, int>, int> energy; // key is the location, value is the amount of beams on it
    vector<pair<pair<int, int>, char>> visited; // theres loops

    while(getline(cin, temp)){
        tiles.push_back(temp);
    }

    beam origBeam;
    int maxSize = 0;
    // entering from left side
    cout << "checking left\n";
    for(int i = 0; i < tiles.size(); i++){
        origBeam.x = -1;
        origBeam.y = i;
        origBeam.direc = 'R';
        int size = propagateBeams(origBeam, energy, tiles, visited);
        if(size > maxSize) maxSize = size;
        if(i == 0) cout << "energized squares = " << size << "\n";
    }
    // entering from top
    cout << "checking top\n";
    for(int i = 0; i < tiles[0].size(); i++){
        origBeam.x = i;
        origBeam.y = -1;
        origBeam.direc = 'D';
        int size = propagateBeams(origBeam, energy, tiles, visited);
        if(size > maxSize) maxSize = size;
    }
    // right
    cout << "checking right\n";
    for(int i = 0; i < tiles.size(); i++){
        origBeam.x = tiles[0].size();
        origBeam.y = i;
        origBeam.direc = 'L';
        int size = propagateBeams(origBeam, energy, tiles, visited);
        if(size > maxSize) maxSize = size;
    }
    // bottom
    cout << "checking bottom\n";
    for(int i = 0; i < tiles[0].size(); i++){
        origBeam.x = i;
        origBeam.y = tiles.size();
        origBeam.direc = 'U';
        int size = propagateBeams(origBeam, energy, tiles, visited);
        if(size > maxSize) maxSize = size;
    }


    cout << "Max energy = " << maxSize << "\n";
    return 0;
}

int propagateBeams(beam be, map<pair<int, int>, int> energy, vector<string> tiles, vector<pair<pair<int, int>, char>> visited){
    queue<beam> beams;
    beams.push(be);
    while(beams.size() > 0){
        beam b = beams.front(); 
        beams.pop();
        // check if in loop
        pair<pair<int, int>, char> temp = {{b.x, b.y}, b.direc};
        if(find(visited.begin(), visited.end(), temp) != visited.end()) continue;
        visited.push_back(temp);
        // check if hitting wall
        switch (b.direc) {
            case 'R':
                if(b.x == tiles[0].size() - 1) continue;
                break;
            case 'L':
                if(b.x == 0) continue;
                break;
            case 'U':
                if(b.y == 0) continue;
                break;
            case 'D':
                if(b.y == tiles.size() - 1) continue;
                break;
            default:
                cout << "that shouldn't happen\n";
                return -1;
        }
        // what to do at the next tile
        switch (b.direc) {
            case 'R':
                b.x++;
                if(energy.find({b.x, b.y}) == energy.end()) energy.insert({{b.x, b.y}, 0});
                else energy.find({b.x, b.y})->second++;
                switch (tiles.at(b.y).at(b.x)) {
                    case '/':
                        b.direc = 'U';
                        break;
                    case '\\':
                        b.direc = 'D';
                        break;
                    case '|':
                        beam newBeam;
                        newBeam.x = b.x;
                        newBeam.y = b.y;
                        b.direc = 'U';
                        newBeam.direc = 'D';
                        beams.push(newBeam);
                        break;
                }
                break;
            case 'L':
                b.x--;
                if(energy.find({b.x, b.y}) == energy.end()) energy.insert({{b.x, b.y}, 0});
                else energy.find({b.x, b.y})->second++;
                switch (tiles.at(b.y).at(b.x)) {
                    case '/':
                        b.direc = 'D';
                        break;
                    case '\\':
                        b.direc = 'U';
                        break;
                    case '|':
                        beam newBeam;
                        newBeam.x = b.x;
                        newBeam.y = b.y;
                        b.direc = 'U';
                        newBeam.direc = 'D';
                        beams.push(newBeam);
                        break;
                }
                break;
            case 'U':
                b.y--;
                if(energy.find({b.x, b.y}) == energy.end()) energy.insert({{b.x, b.y}, 0});
                else energy.find({b.x, b.y})->second++;
                switch (tiles.at(b.y).at(b.x)) {
                    case '/':
                        b.direc = 'R';
                        break;
                    case '\\':
                        b.direc = 'L';
                        break;
                    case '-':
                        beam newBeam;
                        newBeam.x = b.x;
                        newBeam.y = b.y;
                        b.direc = 'L';
                        newBeam.direc = 'R';
                        beams.push(newBeam);
                        break;
                }
                break;
            case 'D':
                b.y++;
                if(energy.find({b.x, b.y}) == energy.end()) energy.insert({{b.x, b.y}, 0});
                else energy.find({b.x, b.y})->second++;
                switch (tiles.at(b.y).at(b.x)) {
                    case '/':
                        b.direc = 'L';
                        break;
                    case '\\':
                        b.direc = 'R';
                        break;
                    case '-':
                        beam newBeam;
                        newBeam.x = b.x;
                        newBeam.y = b.y;
                        b.direc = 'L';
                        newBeam.direc = 'R';
                        beams.push(newBeam);
                        break;
                }
                break;
            default:
                cout << "that shouldn't happen\n";
                return -1;
        }
        beams.push(b);
    }
    return energy.size();
}
