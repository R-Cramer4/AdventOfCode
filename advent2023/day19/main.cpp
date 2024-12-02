#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

struct Rule{
    char category;
    char op;
    int num;
    string result;
};
struct Workflow{
    string name;
    vector<Rule> rules;
};
struct Part{
    int x;
    int m;
    int a;
    int s;
};

vector<Rule> workflowInput(string str);
Part partInput(string str);
bool processPart(Part part, map<string, vector<Rule>> workflows, map<string, vector<Rule>>::iterator rule);

int main(){
    string temp;
    map<string, vector<Rule>> workflows;
    vector<Part> parts;

    bool isWork = true;
    while(getline(cin, temp)){
        if(temp == ""){
            isWork = false;
            continue;
        }
        if(isWork){
            workflows.insert({temp.substr(0, temp.find('{')), workflowInput(temp)});
        }else{
            parts.push_back(partInput(temp));
        }
    }
    int sumAccParts = 0;
    map<string, vector<Rule>>::iterator it;
    for(int i = 0; i < parts.size(); i++){
        it = workflows.find("in");
        //cout << "part{x=" << parts[i].x << ", m=" << parts[i].m << ", a=" << parts[i].a << ", s=" << parts[i].s << "}\n";
        if(processPart(parts[i], workflows, it)){
            sumAccParts += parts[i].x + parts[i].m + parts[i].a + parts[i].s;
        }

        //sumAccParts += (parts[i].x + parts[i].m + parts[i].a + parts[i].s) * 
            //processPart(parts[i], workflows, it); // will add if true, otherwise will add 0
    }

    cout << "sum of accepted parts = " << sumAccParts << "\n";
    // 374173 is too low
}

bool processPart(Part part, map<string, vector<Rule>> workflows, map<string, vector<Rule>>::iterator rule){
    for(int i = 0; i < rule->second.size(); i++){
        /*cout << "rule " << rule->first << " : ";
        for(int j = 0; j < rule->second.size(); j++){
            cout << rule->second[j].category << rule->second[j].op << rule->second[j].num << ":" << rule->second[j].result << ", ";
        }
        cout << "\n";*/
        int comp = 0;
        switch (rule->second[i].category) {
            case 'x':
                comp = part.x;
                break;
            case 'm':
                comp = part.m;
                break;
            case 'a':
                comp = part.a;
                break;
            case 's':
                comp = part.s;
                break;
            default: // this is D, the default case
                if(rule->second[i].result == "A") return true;
                if(rule->second[i].result == "R") return false;
                rule = workflows.find(rule->second[i].result);
                i = -1;
                continue;
        }
        bool isValid = false;
        if(rule->second[i].op == '>'){
            if(comp > rule->second[i].num) isValid = true;
        }else{
            if(comp < rule->second[i].num) isValid = true;
        }
        if(isValid){
            switch (rule->second[i].result[0]) {
                case 'A':
                    return true;
                    break;
                case 'R':
                    return false;
                    break;
                default:
                    rule = workflows.find(rule->second[i].result);
                    i = -1;
                    break;
            }
        }
    }
    return false;
}

vector<Rule> workflowInput(string str){
    str.erase(0, str.find('{') + 1);
    str.erase(str.size() - 1); // erases the curly brackets
    vector<Rule> rules;
    while(str.find(',') != -1){
        Rule rule;
        rule.category = str[0];
        rule.op = str[1];
        str.erase(0, 2);
        rule.num = stoi(str.substr(0, str.find(':')));
        str.erase(0, str.find(':') + 1);
        rule.result = str.substr(0, str.find(','));
        str.erase(0, str.find(',') + 1);
        rules.push_back(rule);
    }
    Rule defaultRule;
    defaultRule.result = str;
    defaultRule.category = 'D';
    rules.push_back(defaultRule);

    return rules;
}

Part partInput(string str){
    Part part;
    str.erase(0, str.find('=') + 1);
    part.x = stoi(str.substr(0, str.find(',')));
    str.erase(0, str.find('=') + 1);
    part.m = stoi(str.substr(0, str.find(',')));
    str.erase(0, str.find('=') + 1);
    part.a = stoi(str.substr(0, str.find(',')));
    str.erase(0, str.find('=') + 1);
    part.s = stoi(str);
    return part;
}
