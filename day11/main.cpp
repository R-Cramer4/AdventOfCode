#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void expandGalaxy(vector<string> *galaxy);
void findEmpty(vector<string> galaxy, vector<int> *emptyRow, vector<int> *emptyCol);

int main(){
    string temp;
    vector<string> galaxy;

    while(getline(cin, temp)){
        galaxy.push_back(temp);
    }
    //expandGalaxy(&galaxy);
    // ^ part 1
    vector<int> emptyRow;
    vector<int> emptyCol;
    findEmpty(galaxy, &emptyRow, &emptyCol);
    // ^part 2
    vector<pair<int, int>> galaxyLocs;
    for(int i = 0; i < galaxy.size(); i++){
        for(int j = 0; j < galaxy.at(i).size(); j++){
            if(galaxy[i][j] == '#') galaxyLocs.push_back({i, j});
        }
    }
    cout << "number of pairs = " << (galaxyLocs.size() * (galaxyLocs.size() - 1))/2 << "\n";
    unsigned long long int minLengths = 0; // this will just be all of the manhattan distances summed up
    for(int i = 0; i < galaxyLocs.size(); i++){
        for(int j = i + 1; j < galaxyLocs.size(); j++){
            pair<int, int> p1 = galaxyLocs[i];
            pair<int, int> p2 = galaxyLocs[j];

            for(int k = 0; k < emptyRow.size(); k++){
                if(!emptyRow[k]){
                    if(galaxyLocs[i].first < k && k < galaxyLocs[j].first) p2.first += 1000000 - 1;
                    else if(galaxyLocs[i].first > k &&  k > galaxyLocs[j].first) p1.first += 1000000 - 1;
                }
            }
            for(int k = 0; k < emptyCol.size(); k++){
                if(!emptyCol[k]){
                    if(galaxyLocs[i].second < k && galaxyLocs[j].second > k) p2.second += 1000000 - 1;
                    else if(galaxyLocs[i].second > k && galaxyLocs[j].second < k) p1.second += 1000000 - 1;
                }
            }

            minLengths += abs(p2.first - p1.first) + 
                abs(p2.second - p1.second);
        }
    }
    //for(int i = 0; i < galaxy.size(); i++) cout << galaxy.at(i) << "\n";
    cout << "total min lengths = " << minLengths << "\n";
}

void expandGalaxy(vector<string> *galaxy){
    // first expand rows (its easier)
    for(int i = 0; i < galaxy->size(); i++){
        if(galaxy->at(i).find('#') == -1){
            galaxy->insert(galaxy->begin() + i, galaxy->at(i));
            i++;
        }
    }

    // expand columns
    vector<int> isEmpty;
    // doing this for memory reasons, just feels wrong to iterate the other way
    for(int i = 0; i < galaxy->at(0).size(); i++){
        isEmpty.push_back(0);
    }
    for(int i = 0; i < galaxy->size(); i++){
        for(int j = 0; j < galaxy->at(i).size(); j++){
            if(galaxy->at(i)[j] == '#') isEmpty[j] = 1;
        }
    }
    for(int i = 0; i < galaxy->size(); i++){
        for(int j = isEmpty.size() - 1; j >= 0; j--){
            if(!isEmpty[j]){
                galaxy->at(i).insert(galaxy->at(i).begin() + j + 1, ',');
            }
        }
    }

}
void findEmpty(vector<string> galaxy, vector<int> *emptyRow, vector<int> *emptyCol){
    for(int i = 0; i < galaxy.size(); i++){
        if(galaxy.at(i).find('#') == -1) emptyRow->push_back(0);
        else emptyRow->push_back(1);
    }
    for(int i = 0; i < galaxy.at(0).size(); i++){
        emptyCol->push_back(0);
    }
    for(int i = 0; i < galaxy.size(); i++){
        for(int j = 0; j < galaxy.at(i).size(); j++){
            if(galaxy.at(i)[j] == '#') emptyCol->at(j) = 1;
        }
    }
}
