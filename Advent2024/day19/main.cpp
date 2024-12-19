#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<string> patterns;
map<string, long long int> seen_patterns;

long long int findMatch(string *t, int s);

int main(){
    string temp;
    getline(cin, temp);
    // temp holds towel patterns
    stringstream s(temp);
    while(getline(s, temp, ',')){
        // have each individual pattern
        patterns.push_back(temp);
    }
    
    long long int patternsUsed = 0;
    int towelsPossible = 0;
    getline(cin, temp);
    while(getline(cin, temp)){
        // all towels
        long long int t = findMatch(&temp, 0);
        if(t != -1){
            towelsPossible++;
            patternsUsed += t;
        }
    }
    cout << endl << "Possible towels = " << towelsPossible << endl;
    cout << "Number of ways to make the towels = " << patternsUsed << endl;
    // 105751964392 is too low
    // 813026025594332 is too high
}

long long int findMatch(string *t, int s){
    if(s == t->size()) return 1;

    try {
        auto i = seen_patterns.at(t->substr(s));
        return i;
    } catch (...) {}
    long long int numTowels = 0;

    for(int i = 0; i < patterns.size(); i++){
        if(s + patterns[i].size() > t->size()) continue;

        if(t->substr(s, patterns[i].size()) == patterns[i]){
            // find a match for the first part of the substring
            long long int temp = findMatch(t, s + patterns[i].size());
            // search for a matches in the rest of the string
            if(temp >= 0) numTowels += temp;
        }
    }

    seen_patterns.insert({t->substr(s), numTowels == 0 ? -1 : numTowels});
    if(numTowels == 0) return -1;
    return numTowels;
}
