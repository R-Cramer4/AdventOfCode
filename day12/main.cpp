#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdint.h>
using namespace std;

uint64_t findArrangements(string str, vector<int> dmg);

map<pair<string, vector<int>>, uint64_t> finishedArrangements;

int main(){
    string temp;
    vector<pair<string, vector<int>>> springs;
    uint64_t arrangements = 0;

    while(getline(cin, temp)){
        pair<string, vector<int>> springRow;
        string tempFirst = temp.substr(0, temp.find(' '));
        temp.erase(0, temp.find(' ') + 1);
        vector<int> tempSecond;
        while(temp.find(',') != -1){
            tempSecond.push_back(stoi(temp.substr(0, temp.find(','))));
            temp.erase(0, temp.find(',') + 1);
        }
        tempSecond.push_back(stoi(temp));

        // unfold 5 times
        for(int i = 0; i < 5; i++){
            springRow.first.append(tempFirst);
            if(i != 4) springRow.first.append(1, '?');
            springRow.second.insert(springRow.second.end(), tempSecond.begin(), tempSecond.end());

        }
        springs.push_back(springRow);
    }
    for(int i = 0; i < springs.size(); i++){
        arrangements += findArrangements(springs[i].first, springs[i].second);
    }

    cout << "number of arrangements = " << arrangements << "\n";
    return 0;
}

uint64_t findArrangements(string str, vector<int> dmg){
    if(str.size() == 0 && dmg.size() == 0) return 1;
    if(str.size() == 0 && dmg.size() != 0) return 0;
    if(dmg.size() == 0){
        if(str.find('#') == -1) return 1;
        return 0;
    }
    map<pair<string, vector<int>>, uint64_t>::iterator it;
    it = finishedArrangements.find({str, dmg});
    if(it != finishedArrangements.end()){
        return it->second;
    }


    uint64_t ans = 0;
    if(str.front() == '.'){
        ans = findArrangements(str.substr(1), dmg);
        finishedArrangements.insert({{str, dmg}, ans});
        return ans;
    }
    if(str.front() == '?'){
        str.front() = '#';
        ans = findArrangements(str, dmg) + findArrangements(str.substr(1), dmg);
        str.front() = '?';
        finishedArrangements.insert({{str, dmg}, ans});
        return ans;
    }


    int size = 0;
    if(str.size() < dmg[0]) return 0;
    for(int i = 0; i < str.size(); i++){
        if(str[i] == '#'){
            size++;
            continue;
        }
        if(str[i] == '.'){
            if(size < dmg[0]) return 0;
            break;
        }
        // ?
        size++;
    }
    if(str[dmg[0]] == '#') return 0;
    bool changed = false;
    if(str[dmg[0]] == '?'){
        str[dmg[0]] = '.';
        changed = true;
    }


    string newStr = str.substr(dmg[0]);
    vector<int> tempDmg;
    tempDmg.insert(tempDmg.begin(), dmg.begin() + 1, dmg.end());
    ans = findArrangements(newStr, tempDmg);
    if(changed) str[dmg[0]] = '?';
    finishedArrangements.insert({{str, dmg}, ans});
    return ans;

}
