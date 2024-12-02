#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int hashString(string str);
struct box{
    int number;
    vector<pair<string, int>> lenses;
};

int main(){
    string temp;
    vector<box> boxes;
    for(int i = 0; i < 255; i++){
        box tempBox;
        tempBox.number = i;
        boxes.push_back(tempBox);
    }
    getline(cin, temp);
    int ans = 0;
    while(temp.find(',') != -1){
        string instruction = temp.substr(0, temp.find(','));
        temp.erase(0, temp.find(',') + 1);
        string label = instruction.substr(0, min(instruction.find('='), instruction.find('-')));
        char operation = instruction[min(instruction.find('='), instruction.find('-'))];
        int focalLength = 0;
        if(operation == '='){
            focalLength = stoi(instruction.substr(instruction.find('=') + 1));
        }
        int box = hashString(instruction);
        ans += box;
        box = hashString(label); // its actually the label

        // box stuff here
        if(operation == '-'){
            for(int i = 0; i < boxes[box].lenses.size(); i++){
                if(boxes[box].lenses[i].first == label){
                    boxes[box].lenses.erase(boxes[box].lenses.begin() + i);
                }
            }
        }else if(operation == '='){
            bool isFound = false;
            for(int i = 0; i < boxes[box].lenses.size(); i++){
                if(boxes[box].lenses[i].first == label){
                    boxes[box].lenses[i].second = focalLength;
                    isFound = true;
                    break;
                }
            }
            if(!isFound){
                boxes[box].lenses.push_back({label, focalLength});
            }
        }else cout << "invalid operation\n";
    }
    // need to get the last value
    string instruction = temp;
    string label = instruction.substr(0, min(instruction.find('='), instruction.find('-')));
    char operation = instruction[min(instruction.find('='), instruction.find('-'))];
    int focalLength = 0;
    if(operation == '='){
        focalLength = stoi(instruction.substr(instruction.find('=') + 1));
    }
    int box = hashString(instruction);
    ans += box;
    box = hashString(label); // its actually the label

    // box stuff here
    if(operation == '-'){
        for(int i = 0; i < boxes[box].lenses.size(); i++){
            if(boxes[box].lenses[i].first == label){
                boxes[box].lenses.erase(boxes[box].lenses.begin() + i);
            }
        }
    }else if(operation == '='){
        bool isFound = false;
        for(int i = 0; i < boxes[box].lenses.size(); i++){
            if(boxes[box].lenses[i].first == label){
                boxes[box].lenses[i].second = focalLength;
                isFound = true;
                break;
            }
        }
        if(!isFound){
            boxes[box].lenses.push_back({label, focalLength});
        }
    }else cout << "invalid operation\n";
    
    cout << "sum of results = " << ans << "\n";
    
    int focusingPower = 0;
    for(int i = 0; i < boxes.size(); i++){
        for(int j = 0; j < boxes[i].lenses.size(); j++){
            focusingPower += (i + 1) * (j + 1) * boxes[i].lenses[j].second;
        }
    }
    cout << "sum of focusing power = " << focusingPower << "\n";

    return 0;
}

int hashString(string str){
    int hash = 0;
    for(int i = 0; i < str.size(); i++){
        hash = ((hash + str[i]) * 17) % 256;
    }
    return hash;
}
