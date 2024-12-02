#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    string temp;
    int sum = 0;
    int sumBack = 0;

    while(getline(cin, temp)){
        vector<vector<int>> history;
        history.push_back(vector<int>());
        while(temp.find(' ') != -1){
            history[0].push_back(stoi(temp.substr(0, temp.find(' '))));
            temp.erase(0, temp.find(' ') + 1);
        }
        history[0].push_back(stoi(temp));
        int isZero = 0;
        while(isZero == 0){
            vector<int> tempHist;
            for(int i = 0; i < history.back().size() - 1; i++){
                tempHist.push_back(history.back()[i + 1] - history.back()[i]);
            }
            history.push_back(tempHist);

            for(int i = 0; i < history.back().size(); i++){
                if(history.back()[i] != 0) break;
                if(i == history.back().size() - 1) isZero = 1;
            }
        }
        int nextNum = 0;
        int prevNum = 0;
        for(int i = history.size() - 1; i >= 0; i--){
            nextNum = history[i].back() + nextNum;
            prevNum = history[i].front() - prevNum;
        }
        sum += nextNum;
        sumBack += prevNum;
    }
    cout << "total extrapolated values = " << sum << "\n";
    cout << "total values before = " << sumBack << "\n";
}
