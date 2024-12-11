#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
using namespace std;

#define BLINKS 75

struct Stone{
    unsigned long long int countp;
    unsigned long long int counta;
};
map<unsigned long long int, Stone> stones;

void blink();

int main(){
    string temp;
    getline(cin, temp);
    stringstream ss(temp);

    while(ss >> temp){
        stones.insert({stoull(temp), {1, 0}});
    }
    for(int i = 0; i < BLINKS; i++){
        blink();
    }
    unsigned long long int numStones = 0;
    for(auto i : stones){
        //cout << i.first << ", " << i.second.countp + i.second.counta << endl;
        numStones += i.second.counta + i.second.countp;
    }
    cout << "Number of stones = " << numStones << endl;
    // 6701716403 is too low
}

void blink(){
    for(auto k : stones){
        stones.at(k.first).countp += stones.at(k.first).counta;
        stones.at(k.first).counta = 0;
    }
    for(auto k = stones.begin(); k != stones.end();){
        auto num = k->first;
        string nums = to_string(k->first);
        auto sum = k->second.countp;
        if(k->second.countp == 0){
            k++;
            continue;
        }

        if(num == 0){
            try {
                stones.at(1).counta += sum;
            } catch (...) {
                stones.insert({1, {0, sum}});
            }
        }else if(nums.size() % 2 == 0){
            auto left = stoull(nums.substr(0, nums.size() / 2));
            auto right = stoull(nums.substr(nums.size() / 2));
            try {
                stones.at(left).counta += sum;
            }catch (...) {
                stones.insert({left, {0, sum}});
            }
            try {
                stones.at(right).counta += sum;
            }catch (...) {
                stones.insert({right, {0, sum}});
            }
        }else{
            try {
                stones.at(num * 2024).counta += sum;
            } catch (...) {
                stones.insert({num * 2024, {0, sum}});
            }
        }
        bool erase = k->second.counta == 0;
        k->second.countp = 0;
        k++;
        if(erase) stones.erase(num);
    }
}
