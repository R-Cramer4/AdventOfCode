#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct rule{
    int page = -1;
    rule *next = nullptr;
};
rule rules[100];

int whereLocViolates(vector<int> *update, int loc){
    for(int j = 0; j < loc; j++){
        rule *tempR = &rules[update->at(loc)];
        while(tempR != nullptr){
            if(tempR->page == update->at(j)){
                return j;
            }
            tempR = tempR->next;
        }
    }
    return -1;
}

int orderCorrectly(vector<int> *update){
    // if an index violates a rule, swap the values

    for(int i = 0; i < update->size(); i++){
        int violation = whereLocViolates(update, i);
        if(violation != -1){
            int temp = update->at(i);
            update->at(i) = update->at(violation);
            update->at(violation) = temp;
            i--; // dp it again
        }
    }
    return update->at(update->size() / 2);
}

int main(){
    string temp;
    int correctMids = 0;
    int correctedMids = 0;


    while(getline(cin, temp)){
        if(temp == "") break;
        // handles rules
        int x = stoi(temp.substr(0, 2));
        int y = stoi(temp.substr(3, 2));
        rule *temp = &rules[x];
        while(temp->next != nullptr) temp = temp->next;
        rule *next = new rule();
        next->page = y;
        temp->next = next;
    }
    //int lineNum = 0;
    while(getline(cin, temp)){
        //lineNum++;
        // handles pages
        vector<int> updates;
        while(temp != ""){
            if(temp.find(',') != -1){
                updates.push_back(stoi(temp.substr(0, 2)));
                temp = temp.substr(3);
            }
            else{
                updates.push_back(stoi(temp.substr(0, 2)));
                temp = "";
            }
        }
        // have a full list of updates
        bool valid = true;
        for(int i = 0; i < updates.size(); i++){
            if(whereLocViolates(&updates, i) != -1){
                valid = false;
                break;
            }
        }
        if(valid){
            correctMids += updates.at((updates.size() / 2));
        }else{
            correctedMids += orderCorrectly(&updates);
        }

    }
    cout << "middle page number totals: " << correctMids << endl;
    cout << "corrected middle page number totals: " << correctedMids << endl;
}
