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

void getKeySeq(string in, vector<pair<int, int>> *out);
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
        getKeySeq(code, &keySeq); // robot controlling the keypads movements

        vector<pair<int, int>> dirSeq;
        getDirSeq(keySeq, &dirSeq); // robot controlling the robot controlling the keypad

        vector<pair<int, int>> mySeq;
        getDirSeq(dirSeq, &mySeq);

        codeComplexity += mySeq.size() * stoi(code.substr(0, code.size() - 1));
    }

    cout << "Code complexity = " << codeComplexity << endl;
}
void getKeySeq(string in, vector<pair<int, int>> *out){
    // always starts at A, (2, 3) x = 2, y = 3

}
void getDirSeq(vector<pair<int, int>>, vector<pair<int, int>> *out){

}
