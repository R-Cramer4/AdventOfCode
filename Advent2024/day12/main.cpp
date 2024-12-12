#include <iostream>
#include <ostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Region{
    vector<pair<int, int>> locs;
    int area;
    int perimeter = 0;
    int sides = 0;
    char type;
    
    bool contains(int x, int y){
        for(int i = 0; i < locs.size(); i++){
            if(locs[i].first == x && locs[i].second == y) return true;
        }
        return false;
    }
};

vector<string> map;
vector<Region> regions;


Region* makeRegion(Region *r, int x, int y);

int main(){
    string temp;

    while(getline(cin, temp)){
        map.push_back(temp);
    }

    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            // if this location isnt in a region yet
            bool contains = false;
            for(int k = 0; k < regions.size(); k++){
                if(regions[k].contains(j, i)){
                    contains = true;
                    break;
                }
            }
            if(contains) continue;
            // create new region
            Region *r = new Region();
            regions.push_back(*makeRegion(r, j, i));
        }
    }

    int price = 0;
    int discount = 0;
    for(int i = 0; i < regions.size(); i++){
        //cout << "Region " << regions[i].type << " with price " << regions[i].area << " * " << regions[i].sides << endl;
        price += regions[i].area * regions[i].perimeter;
        discount += regions[i].area * regions[i].sides;
    }
    cout << "Total price = " << price << endl;
    cout << "Total price with discount = " << discount << endl;
}

Region* makeRegion(Region *r, int x, int y){
    r->type = map[y][x];
    queue<pair<int, int>> neighbors;
    neighbors.push({x, y});

    while(!neighbors.empty()){
        // add all neighbors if they arent in locs already
        auto temp = neighbors.front();
        neighbors.pop();
        if(r->contains(temp.first, temp.second)) continue;
        r->locs.push_back(temp);
        if(temp.first - 1 >= 0 && 
                map[temp.second][temp.first - 1] == r->type &&
                !r->contains(temp.first - 1, temp.second)){
            neighbors.push({temp.first - 1, temp.second});
        }
        if(temp.first + 1 < map[0].size() &&
                map[temp.second][temp.first + 1] == r->type &&
                !r->contains(temp.first + 1, temp.second)){
            neighbors.push({temp.first + 1, temp.second});
        }
        if(temp.second - 1 >= 0 &&
                map[temp.second - 1][temp.first] == r->type &&
                !r->contains(temp.first, temp.second - 1)){
            neighbors.push({temp.first, temp.second - 1});
        }
        if(temp.second + 1 < map.size() && 
                map[temp.second + 1][temp.first] == r->type &&
                !r->contains(temp.first, temp.second + 1)){
            neighbors.push({temp.first, temp.second + 1});
        }
    }
    // now has full area
    r->area = r->locs.size();

    // calculate perimeter
    for(auto i : r->locs){
        int corners = 0;
        bool left=1, right=1, up=1, down=1;
        if(!r->contains(i.first - 1, i.second)){
            r->perimeter++;
            left = 0;
        }
        if(!r->contains(i.first, i.second - 1)) {
            r->perimeter++;
            up = 0;
        }
        if(!r->contains(i.first + 1, i.second)) {
            r->perimeter++;
            right = 0;
        }
        if(!r->contains(i.first, i.second + 1)) {
            r->perimeter++;
            down = 0;
        }


        if(!left && !up) corners++;
        if(!up && !right) corners++;
        if(!right && !down) corners++;
        if(!down && !left) corners++;

        if(left && up && !r->contains(i.first - 1, i.second - 1)){
            // interior corner in the shape of a _|
            corners++;
        }
        if(right && up && !r->contains(i.first + 1, i.second - 1)){
            // interior corner in the shape of a L
            corners++;
        }
        if(right && down && !r->contains(i.first + 1, i.second + 1)){
            // interior corner in the shape of a |-
            corners++;
        }
        if(left && down && !r->contains(i.first - 1, i.second + 1)){
            // interior corner in the shape of a -|
            corners++;
        }
        r->sides += corners;

    }


    return r;
}
