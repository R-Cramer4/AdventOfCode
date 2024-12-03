#include <iostream>
#include <string>
using namespace std;

int strToInt(string str){
    string temp = "";
    for(int i = 0; i < str.length(); i++){
        if(str[i] < 48 || str[i] > 57) return 0;
    }
    return stoi(str);
}

int main(){
    string temp;
    long long int multiplications = 0;
    bool enabled = true;
    while(getline(cin, temp)){
        while(!temp.empty()){
            auto loc = temp.find("mul(");
            auto locDo = temp.find("do()");
            auto locDont = temp.find("don't()");
            if(locDo == -1) locDo = temp.length();
            if(locDont == -1) locDont = temp.length();
            if(loc == string::npos) break;
            if(loc > locDo || loc > locDont){
                if(locDont > locDo && locDont < loc) enabled = false;
                else if(locDo > locDont && locDo < loc) enabled = true;
                else if(locDo < loc && locDont > loc) enabled = true;
                else if(locDont < loc && locDo > loc) enabled = false;
            }
            temp = temp.substr(loc + 4);
            string nums = temp.substr(0, temp.find(')'));
            int x = strToInt(nums.substr(0, nums.find(',')));
            int y = strToInt(nums.substr(nums.find(',') + 1));
            if(enabled) multiplications += (x * y);
        }
    }
    cout << "Final multiplications = " << multiplications << endl;
}
