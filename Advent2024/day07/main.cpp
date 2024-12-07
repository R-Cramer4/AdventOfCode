#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef uint64_t U64;


bool canSolve(U64 ans, vector<U64> nums){
    if(nums.size() < 2) cout << "Too small" << endl;
    if(nums.size() == 2){
        if(nums.at(0) + nums.at(1) == ans) return true;
        if(nums.at(0) * nums.at(1) == ans) return true;
        if(stoull(to_string(nums.at(0)) + to_string(nums.at(1))) == ans) return true;
        return false;
    }
    U64 mul = nums.at(0) * nums.at(1);
    U64 add = nums.at(0) + nums.at(1);
    U64 ored = stoull(to_string(nums.at(0)) + to_string(nums.at(1)));

    vector<U64> vMul, vAdd, vOred;
    vMul.push_back(mul);
    vAdd.push_back(add);
    vOred.push_back(ored);
    for(int i = 2; i < nums.size(); i++){
        vMul.push_back(nums.at(i));
        vAdd.push_back(nums.at(i));
        vOred.push_back(nums.at(i));
    }
    return canSolve(ans, vMul) || canSolve(ans, vAdd) || canSolve(ans, vOred);
}

int main(){
    string temp;
    U64 calibrations = 0;

    while(getline(cin, temp)){
        U64 ans = stoull(temp.substr(0, temp.find(':')));
        temp = temp.substr(temp.find(':') + 1);

        vector<U64> nums;
        stringstream ss(temp);
        string token;
        while(ss >> token) nums.push_back(stoi(token));


        calibrations += ans * canSolve(ans, nums);
    }

    cout << "Final calibration vals = " << calibrations << endl;
}
