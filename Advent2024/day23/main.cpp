#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <vector>
using namespace std;

#define THREADS 8

vector<vector<string>> kCliques; // where k is the size of kCliques[0]
vector<pair<string, string>> edges;
void getKPlus1Clique(vector<vector<string>> *kClique, int start, int end, vector<vector<string>> &ret);
vector<string> getIntersectionIfValid(vector<string> c1, vector<string> c2);

int main(){
    string temp;
    ifstream inFile;
    inFile.open("input.txt");

    string n1, n2;
    while(getline(inFile, temp)){
        n1 = temp.substr(0, 2);
        n2 = temp.substr(3, 2);
        edges.push_back({n1, n2});
        vector<string> clique2;
        clique2.push_back(n1);
        clique2.push_back(n2);
        kCliques.push_back(clique2);
    }

    while(kCliques.size() > 1){
        cout << kCliques.at(0).size() << ": " << kCliques.size() << '\t' << endl;

        vector<thread> threads;
        int len = kCliques.size() / THREADS;
        vector<vector<vector<string>>> results;
        for(int i = 0; i < THREADS; i++){
            results.emplace_back();
        }

        for(int i = 0; i < THREADS; i++){
            threads.emplace_back(getKPlus1Clique, &kCliques, i * len, (i + 1) * len, ref(results.at(i)));
        }
        for(auto &t : threads){ t.join(); }
        cout << "Joined" << endl;
        kCliques.clear();
        for(auto &ret : results){
            if(ret.size() == 0) continue;
            kCliques.insert(kCliques.end(), ret.begin(), ret.end());
        }
        // Need to clear duplicates
        for(int i = 0; i < kCliques.size(); i++){
            sort(kCliques[i].begin(), kCliques[i].end());
        }
        for(int i = 0; i < kCliques.size() - 1; i++){
            for(int j = i + 1; j < kCliques.size(); j++){
                bool equal = true;
                for(int k = 0; k < kCliques[i].size(); k++){
                    if(kCliques[i][k] != kCliques[j][k]){
                        equal = false;
                        break;
                    }
                }
                if(equal){
                    kCliques.erase(kCliques.begin() + j);
                    j--;
                }
            }
        }
    }
    cout << endl;
    if(kCliques.size() == 0) cout << "Oops" << endl;
    for(auto c : kCliques[0]){
        cout << c << ',';
    }
    cout << endl;
}
void getKPlus1Clique(vector<vector<string>> *kClique, int start, int end, vector<vector<string>> &ret){
    int last = end;
    if(last == kClique->size()) last -= 1;
    for(int i = start; i < last; i++){
        for(int j = i + 1; j < kClique->size(); j++){
            vector<string> temp = getIntersectionIfValid(kClique->at(i), kClique->at(j));
            if(temp.size() != 0) ret.push_back(temp);
        }
    }
}
vector<string> getIntersectionIfValid(vector<string> c1, vector<string> c2){
    // find intersection, if only two nodes left and if they are an edge, valid
    vector<string> intersection;
    for(int i = 0; i < c1.size(); i++){
        for(int j = 0; j < c2.size(); j++){
            if(c1.at(i) == c2.at(j)){
                intersection.push_back(c1.at(i));
                c1.erase(c1.begin() + i);
                c2.erase(c2.begin() + j);
                i--;
                break;
            }
        }
    }
    if(c1.size() == c2.size() && c1.size() == 1){
        //cout << c1[0] << ", " << c2[0] << endl;
        // has 1 element in each
        for(auto &e : edges){
            if((e.first == c1.at(0) && e.second == c2.at(0)) || (e.first == c2.at(0) && e.second == c1.at(0))){
                // valid edge
                intersection.push_back(c1.at(0));
                intersection.push_back(c2.at(0));
                /*
                for(auto e : intersection){
                    cout << e;
                }
                cout << endl;
                */
                return intersection;
            }
        }
    }
    intersection.clear();
    return intersection;
}
