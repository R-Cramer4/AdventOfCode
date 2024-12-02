#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

bool checkStrA(char* str){
    const char* del = " ";
    char *a = strtok(str, del);
    char *b = strtok(NULL, del);
    int x = stoi(a), y = stoi(b);
    bool inc;
    bool usedBad = false;
    if(x > y) inc = false;
    else if(x < y) inc = true;
    else usedBad = true;
    if(abs(x - y) > 3) usedBad = true;
    a = b;
    if(usedBad){
        b = strtok(NULL, del);
        if(b == NULL) return true;
        x = stoi(a), y = stoi(b);
        if(x > y) inc = false;
        else if(x < y) inc = true;
        if(x == y || abs(x - y) > 3) return false;
        a = b;
    }

    while (a != NULL) {
        b = strtok(NULL, del);
        if(b == NULL) return true;
        x = stoi(a), y = stoi(b);
        if((inc && x > y) || (!inc && x < y) || x == y || abs(x - y) > 3){
            if(usedBad) return false;
            usedBad = true;
            continue;
        }
        // valid, move on
        a = b;
    }
    return true;
}
bool checkStrB(char* str){
    const char* del = " ";
    char *a = strtok(str, del);
    char *b = strtok(NULL, del);
    int x = stoi(a), y = stoi(b);
    bool inc;
    bool usedBad = false;
    if(x > y) inc = false;
    else if(x < y) inc = true;
    else usedBad = true;
    if(abs(x - y) > 3) usedBad = true;
    if(!usedBad) a = b;
    else{
        b = strtok(NULL, del);
        if(b == NULL) return true;
        x = stoi(a), y = stoi(b);
        if(x > y) inc = false;
        else if(x < y) inc = true;
        if(x == y || abs(x - y) > 3) return false;
        a = b;
    }

    while (a != NULL) {
        b = strtok(NULL, del);
        if(b == NULL) return true;
        x = stoi(a), y = stoi(b);
        if((inc && x > y) || (!inc && x < y) || x == y || abs(x - y) > 3){
            if(usedBad) return false;
            usedBad = true;
            continue;
        }
        // valid, move on
        a = b;
    }
    return true;
}

// between 425 and 427
// not 417
int main(){
    string temp;
    int valid = 0;

    while(getline(cin, temp)){
        valid += checkStrA(strdup(temp.c_str())) || checkStrB(strdup(temp.c_str()));
    }

    cout << "Safe reports: " << valid << endl;
}
