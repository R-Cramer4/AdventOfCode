#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<vector<int>> locks;
vector<vector<int>> keys;

int main(){
    string temp;

    bool lock = true;
    while(getline(cin, temp)){
        vector<int> v = {0, 0, 0, 0, 0};
        if(temp[0] == '#') lock = true;
        for(int i = 0; i < 5; i++){
            getline(cin, temp);
            for(int j = 0; j < temp.size(); j++){
                if(temp[j] == '#'){
                    v.at(j)++;
                }
            }
        }
        getline(cin, temp);
        if(temp[0] =='#') lock = false;
        if(lock) locks.push_back(v);
        else keys.push_back(v);
        getline(cin, temp);
    }
    int combos = 0;
    for(int i = 0; i < locks.size(); i++){
        for(int j = 0; j < keys.size(); j++){
            bool fit = true;
            for(int k = 0; k < 5; k++){
                if(locks[i][k] + keys[j][k] > 5){
                    fit = false;
                    break;
                }
            }
            combos += fit;
        }
    }
    cout << "Combos = " << combos << endl;
}
