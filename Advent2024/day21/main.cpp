#include <iostream>
#include <string>
#include <vector>
using namespace std;

string codes[5];

char keyPad[4][3] = {
    {'7', '8', '9'},
    {'4', '5', '6'},
    {'1', '2', '3'},
    {0, '0', 'A'}
};
pair<int, int> keys[12] = {
    {3, 1}, {2, 0}, {2, 1}, {2, 2},
    {1, 0}, {1, 1}, {1, 2},
    {0, 0}, {0, 1}, {0, 2},
    {3, 2}
};

char dirPad[2][3] = {
    {0, '^', 'A'},
    {'<', 'v', '>'}
};
struct D {
    pair<int, int> left = {1, 0};
    pair<int, int> right = {1, 2};
    pair<int, int> up = {0, 1};
    pair<int, int> down = {1, 1};
    pair<int, int> a = {0, 2};
};
D dir;

void getKeySeq(string in, string *out);
void getDirSeq(vector<pair<int, int>>, vector<pair<int, int>> *out);

int main(){
    string temp;

    for(int i = 0; i < 5; i++){
        getline(cin, temp);
        codes[i] = temp;
    }
    long long int codeComplexity = 0;
    for(auto code : codes){
        vector<pair<int, int>> keySeq;
        string out;
        getKeySeq(code, &out); // robot controlling the keypads movements

        vector<pair<int, int>> dirSeq;
        getDirSeq(keySeq, &dirSeq); // robot controlling the robot controlling the keypad

        vector<pair<int, int>> mySeq;
        getDirSeq(dirSeq, &mySeq);

        codeComplexity += mySeq.size() * stoi(code.substr(0, code.size() - 1));
    }

    cout << "Code complexity = " << codeComplexity << endl;
}
void getKeySeq(string in, string *out){
    // always starts at A, (2, 3) x = 2, y = 3
    // always go up before moving left
    // always go right before moving down
    string res = "";
    pair<int, int> loc = {3, 2};
    for(int i = 0; i < in.size(); i++){
        auto next = (in[i] == 'A' ? keys[10] : keys[in[i] - '0']);
        
        if(loc.first > next.first){
            // we need to go up
            int num = loc.first - next.first;
            for(int j = 0; j < num; j++) res = res + '^';
        }
        // go left or right
        if(loc.second < next.second){
            // need to move right
            int num = next.second - loc.second;
            for(int j = 0; j < num; j++) res = res + '>';
        }else if(loc.second > next.second){
            // left
            int num = loc.second - next.second;
            for(int j = 0; j < num; j++) res = res + '<';
        }
        if(loc.first < next.first){
            // down
            int num = next.first - loc.first;
            for(int j = 0; j < num; j++) res = res + 'v';
        }
    }
    cout << res << endl;
    *out = res;
}
void getDirSeq(vector<pair<int, int>>, vector<pair<int, int>> *out){

}
