#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

int main(){
    string temp;
    string steps;
    map<string, pair<string, string>> nodes;
    map<string, pair<string, string>>::iterator it;
    cin >> temp;
    steps = temp;
    while(getline(cin, temp)){
        string loc = temp.substr(0, temp.find(' '));
        pair<string, string> to;
        temp.erase(0, temp.find('(') + 1);
        to.first = temp.substr(0, temp.find(','));
        temp.erase(0, temp.find(' ') + 1);
        to.second = temp.substr(0, temp.find(')'));
        nodes.emplace(loc, to);
        
    }
    string currentLoc = "AAA";
    int numSteps = 0;
    while(currentLoc != "ZZZ"){
        it = nodes.find(currentLoc);
        if(steps[numSteps % steps.size()] == 'L'){
            currentLoc = it->second.first;
            numSteps++;
        }else{
            currentLoc = it->second.second;
            numSteps++;
        }
    }
    cout << "number of steps it took = " << numSteps << "\n";


    // Part 2
    vector<string> currentLocations;
    numSteps = 0;
    it = nodes.begin();
    while(it != nodes.end()){
        if(it->first.back() == 'A'){
            currentLocations.push_back(it->first);
        }
        it++;
    }
    int end = 0;
    vector<unsigned long long int> cycleLen;
    for(int i = 0; i < currentLocations.size(); i++){
        cycleLen.push_back(0);
    }
    while(end == 0){
        for(int i = 0; i < currentLocations.size(); i++){
            it = nodes.find(currentLocations[i]);
            if(steps[numSteps % steps.size()] == 'L'){
                currentLocations[i] = it->second.first;
            }else{
                currentLocations[i] = it->second.second;
            }
        }
        numSteps++;
        for(int i = 0; i < currentLocations.size(); i++){
            if(currentLocations[i].back() == 'Z'){
                cycleLen[i] = numSteps;
            }
            if(cycleLen[i] != 0) end++;
        }
        if(end == currentLocations.size()) break;
        end = 0;
    }
    // instead of brute forcing, i can figure out how long one cycle takes then do math to find the cycle length for everythign
    cout << "number of steps = " << lcm(lcm(lcm(cycleLen[0], cycleLen[1]), cycleLen[2]), lcm(lcm(cycleLen[3], cycleLen[4]), cycleLen[5])) << "\n";

    return 0;
}
