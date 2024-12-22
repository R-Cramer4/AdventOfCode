#include <iostream>
#include <map>
#include <string>
#include <utility>
using namespace std;


struct Sequence{
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;

    void shiftAndInsert(long long int prev, long long int next){
        a = b;
        b = c;
        c = d;

        int x = prev % 10;
        int y = next % 10;
        d = y - x;
    }
    bool operator()(const Sequence& a, const Sequence& b) const{
        if(a.a == b.a){
            if(a.b == b.b){
                if(a.c == b.c){
                    return a.d < b.d;
                }
                return a.c < b.c;
            }
            return a.b < b.b;
        }
        return a.a < b.a;
    }
};

long long int getNextSecret(long long int x);
map<Sequence, pair<int, bool>, Sequence> sequences;

int main(){
    string temp;

    long long int sums = 0;
    while(getline(cin, temp)){
        long long int x = stoi(temp);

        Sequence seq;
        for(int i = 0; i < 2000; i++){
            long long int next = getNextSecret(x);
            // shift seq left
            // then insert this change into d
            seq.shiftAndInsert(x, next);
            if(i < 4){
                x = next;
                continue;
            }
            auto j = sequences.find(seq);
            if(j == sequences.end()){
                // not there, need to insert
                sequences.insert({seq, {next % 10, true}});
            }else{
                // there can update
                if(!j->second.second){
                    j->second.first += next % 10;
                    j->second.second = true;
                }
            }
            x = next;
        }
        sums += x;
        for(auto it = sequences.begin(); it != sequences.end(); it++){
            it->second.second = false;
        }
    }

    int max = 0;
    Sequence seq;
    for(auto it = sequences.begin(); it != sequences.end(); it++){
        if(it->second.first > max) {
            max = it->second.first;
            seq = it->first;
        }
    }

    cout << "Sums of numbers: " << sums << endl;
    cout << "Max bannanas: " << max << " at ";
    cout << seq.a << ',' << seq.b << ',' << seq.c << ',' <<seq.d<< endl;
}


long long int getNextSecret(long long int x){
    long long int next = x;
    long long int prev = x;
    next = next * 64;
    next = prev ^ next;
    next = next % 16777216;

    prev = next;
    next = next / 32;
    next = prev ^ next;
    next = next % 16777216;

    prev = next;
    next = next * 2048;
    next = prev ^ next;
    next = next % 16777216;


    return next;
}
