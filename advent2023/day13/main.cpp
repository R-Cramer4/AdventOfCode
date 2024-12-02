#include <iostream>
#include <string>
#include <vector>
using namespace std;

int findColMirror(vector<string> pattern, int initAns);
int findRowMirror(vector<string> pattern, int initAns);

int main(){
    string temp;
    vector<vector<string>> patterns;
    int ans = 0;

    while(getline(cin, temp)){
        vector<string> tempPattern;
        tempPattern.push_back(temp);
        while(getline(cin, temp)){
            if(temp == "") break;
            tempPattern.push_back(temp);
        }
        patterns.push_back(tempPattern);
    }
    vector<pair<int, int>> initReflec;

    for(int i = 0; i < patterns.size(); i++){
        int col = findColMirror(patterns[i], 0);
        int row = findRowMirror(patterns[i], 0);
        initReflec.push_back({col, row});
        //cout << "reflection of pattern " << i << " is across row " << row << " or col " << col << "\n";
        if(col != 0) ans += col;
        if(row != 0) ans += (row * 100);
    }
    cout << "Results of notes: " << ans << "\n";
    // part 2
    ans = 0;
    for(int i = 0; i < patterns.size(); i++){
        bool found = false;
        for(int j = 0; j < patterns[i].size(); j++){
            for(int k = 0; k < patterns[i][j].size(); k++){
                if(patterns.at(i).at(j).at(k) == '.') patterns[i][j][k] = '#';
                else if(patterns[i][j][k] == '#') patterns[i][j][k] = '.';
                int col = findColMirror(patterns[i], initReflec[i].first);
                int row = findRowMirror(patterns[i], initReflec[i].second);
                // returning it back to original
                if(patterns[i][j][k] == '.') patterns[i][j][k] = '#';
                else if(patterns[i][j][k] == '#') patterns[i][j][k] = '.';

                if((initReflec[i].first != col || initReflec[i].second != row) && (col != 0 || row != 0)){
                    if(row != 0 && row != initReflec[i].second) ans += (row * 100);
                    if(col != 0 && col != initReflec[i].first) ans += col;
                    found = true;
                    break;
                }
            }
            if(found) break;
        }
        if(!found){
            if(initReflec[i].first != 0) ans += initReflec[i].first;
            if(initReflec[i].second != 0) ans += (initReflec[i].second * 100);
        }
    }
    cout << "Results of notes with smudge: " << ans << "\n";
    // 36126 is too low
    // 41856 is too high
}

int findColMirror(vector<string> pattern, int initAns){
    // returns the number of columns to the left of my line
    int ans = 0;
    for(int i = 0; i < pattern[0].size() - 1; i++){
        bool isReflect = true;
        for(int j = i; j >= 0; j--){
            if((2 * i) - j + 1 >= pattern[0].size()) break;
            for(int k = 0; k < pattern.size(); k++){
                if(pattern[k][j] != pattern[k].at((2 * i) - j + 1)) isReflect = false;
            }
        }
        if(isReflect && i + 1 != initAns){
            ans = i + 1;
            break;
        }
    }

    return ans;
}
int findRowMirror(vector<string> pattern, int initAns){
    // returns the number of rows above the line
    int ans = 0;
    for(int i = 0; i < pattern.size() - 1; i++){
        bool isReflect = true;
        for(int j = i; j >= 0; j--){
            if(((2 * i) - j + 1) >= pattern.size()) break;
            if(pattern[j] != pattern.at((2 * i) - j + 1)) isReflect = false;
        }
        if(isReflect && i + 1 != initAns){
            ans = i + 1;
            break;
        }
    }

    return ans;
}
