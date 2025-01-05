#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

enum Type{
    OR,
    AND,
    XOR,
};

struct Wire{
    string name;
    int val = -1;
    Wire(string n){name = n;}
    Wire(string n, int i){
        name = n;
        val = i;
    }
};

struct Gate{
    Wire *A;
    Wire *B;
    Type type;
    Wire *out;
    bool operate();
    Gate(Wire *a, Wire *b, Type t, Wire *o){
        A = a;
        B = b;
        type = t;
        out = o;
    }
};
map<string, Wire> wires;
vector<Gate> gates;

int main(){
    string temp;

    while(getline(cin, temp)){
        if(temp == "") break;
        string name = temp.substr(0, 3);
        int val = stoi(temp.substr(5, 1));
        wires.insert({name, {name, val}});
    }
    // have all input wires

    while(getline(cin, temp)){
        // all the gates
        string w1, w2, o1;
        Type t = OR;
        w1 = temp.substr(0, 3);
        temp.erase(0, 4);
        w2 = temp.substr(0, temp.find(' '));
        if(w2 == "OR") t = OR;
        else if(w2 == "AND") t = AND;
        else if(w2 == "XOR") t = XOR;
        else cout << w2 << endl;
        temp.erase(0, temp.find(' ') + 1);
        w2 = temp.substr(0, 3);
        temp.erase(0, 7);
        o1 = temp;

        if(wires.find(w1) == wires.end()){
            wires.insert({w1, {w1}});
        }
        if(wires.find(w2) == wires.end()){
            wires.insert({w2, {w2}});
        }
        if(wires.find(o1) == wires.end()){
            wires.insert({o1, {o1}});
        }
        Gate g(&wires.find(w1)->second, &wires.find(w2)->second, t, &wires.find(o1)->second);
        gates.push_back(g);
    }
    cout << "Parsed" << endl;
    unsigned long long int a = 0;
    unsigned long long int b = 0;
    for(auto &w : wires){
        if(w.first[0] == 'x' && w.second.val == 1){
            a = a | ((unsigned long long)1 << stoi(w.first.substr(1)));
        }
        if(w.first[0] == 'y' && w.second.val == 1){
            b = b | ((unsigned long long)1 << stoi(w.first.substr(1)));
        }
    }
    cout << hex << a << ", " << b << endl;
    // have all gates
    // need to loop through until all wires have a value
    bool valid = true;
    while(valid){
        valid = false;
        for(int i = 0; i < gates.size(); i++){
            if(!gates[i].operate()) valid = true;
        }
    }
    // need to collect outputs;
    unsigned long long int output = 0;
    for(auto &w : wires){
        if(w.first[0] == 'z' && w.second.val == 1){
            output = output | ((unsigned long long)1 << stoi(w.first.substr(1)));
        }
    }
    if((a + b) == output) cout << "Correct" << endl;
    cout << "Number outputted = " << output << " wanted: " << a + b << endl;
}
bool Gate::operate(){
    // only do the operation if we can
    if(out->val != -1) return true;
    if(A->val == -1 || B->val == -1) return false;

    switch (type) {
        case OR:
            out->val = A->val | B->val;
            break;
        case AND:
            out->val = A->val & B->val;
            break;
        case XOR:
            out->val = A->val ^ B->val;
            break;
    }
    return true;
}
