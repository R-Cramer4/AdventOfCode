#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <queue>
using namespace std;

int main(){
    string temp;
    priority_queue<int> left;
    priority_queue<int> right;
    map<int, int> rightMap;


    while(getline(cin, temp)){
        int l = stoi(temp.substr(0, temp.find(' ')));
        int r = stoi(temp.substr(temp.find(' ') + 2));
        left.push(l);
        right.push(r);

        if(rightMap.find(r) != rightMap.end()){
            rightMap.at(r)++;
        }else{
            rightMap.insert({r, 1});
        }
    }

    int totalDist = 0;
    int similarity = 0;
    while(!left.empty()){
        int l = left.top();
        totalDist += abs(l - right.top());
        left.pop();
        right.pop();

        int r = (rightMap.find(l) == rightMap.end() ? 0 : rightMap.at(l));
        similarity += r * l;
    }

    cout << "Total Distance: " << totalDist << endl;
    cout << "Similarity: " << similarity << endl;
}
