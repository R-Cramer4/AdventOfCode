#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Machine{
    pair<double, double> ba;
    pair<double, double> bb;
    pair<double, double> prize;
    void print(){
        cout << "Button A: X+" << ba.first << ", Y+" << ba.second << endl;
        cout << "Button B: X+" << bb.first << ", Y+" << bb.second << endl;
        cout << "Prize: X=" << prize.first << ", Y=" << prize.second << endl;
    }
    double calculate();
};
vector<Machine> machines;

int main(){
    string temp;

    while(getline(cin, temp)){
        Machine m;
        m.ba.first = stoi(temp.substr(temp.find("X+") + 2, 2));
        m.ba.second = stoi(temp.substr(temp.find("Y+") + 2));

        getline(cin, temp);
        m.bb.first = stoi(temp.substr(temp.find("X+") + 2, 2));
        m.bb.second = stoi(temp.substr(temp.find("Y+") + 2));

        getline(cin, temp);
        int loc = temp.find("X=") + 2;
        m.prize.first = stoi(temp.substr(loc, temp.find(',') - loc)) + 10000000000000;
        m.prize.second = stoi(temp.substr(temp.find("Y=") + 2)) + 10000000000000;

        getline(cin, temp);

        machines.push_back(m);
    }
    double totalCost = 0;
    for(auto i : machines){
        //cout << "Machine had cost of " << curCost << endl;
        totalCost += i.calculate();
    }
    cout << "Total cost = " << fixed << totalCost << endl;
    // 27688 is too low

}
double Machine::calculate(){
    // use inverse matricies to solve

    double denom = (ba.first * bb.second) - (bb.first * ba.second);
    if(denom == 0) return 0; // cant solve

    double aPress = ((prize.first * bb.second) - (prize.second * bb.first)) / denom;
    double bPress = ((prize.second * ba.first) - (prize.first * ba.second)) / denom;

    //cout << fixed <<  "Pressed a " << aPress << " times and pressed b " << bPress << " times" << endl;

    if(fabs(round(aPress) - aPress) <= 0.0001f &&
        fabs(round(bPress) - bPress) <= 0.0001f){
        return (3 * round(aPress)) + round(bPress);
    }

    return 0;
}
