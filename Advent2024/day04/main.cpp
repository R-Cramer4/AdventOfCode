#include <iostream>
#include <string>
#include <vector>
using namespace std;

int findWord(vector<string> *words, int x, int y){
    int wc = 0;
    // search right
    if((y + 3 < words->at(x).size()) && words->at(x).substr(y + 1, 3) == "MAS") wc++;
    // search left
    if((y - 3 >= 0) && words->at(x).substr(y - 3, 3) == "SAM") wc++;
    // search up
    if(x - 3 >= 0){
        if(words->at(x - 3)[y] == 'S' &&
                words->at(x - 2)[y] == 'A' &&
                words->at(x - 1)[y] == 'M') wc++;
        // and to the right
        if(y + 3 < words->at(x).size() &&
                words->at(x - 3)[y + 3] == 'S' &&
                words->at(x - 2)[y + 2] == 'A' &&
                words->at(x - 1)[y + 1] == 'M') wc++;
        // and to the left
        if(y - 3 >= 0 &&
                words->at(x - 3)[y - 3] == 'S' &&
                words->at(x - 2)[y - 2] == 'A' &&
                words->at(x - 1)[y - 1] == 'M') wc++;
    }
    // search down
    if(x + 3 < words->size()){
        if(words->at(x + 3)[y] == 'S' &&
                words->at(x + 2)[y] == 'A' &&
                words->at(x + 1)[y] == 'M') wc++;
        // and to the right
        if(y + 3 < words->at(x).size() &&
                words->at(x + 3)[y + 3] == 'S' &&
                words->at(x + 2)[y + 2] == 'A' &&
                words->at(x + 1)[y + 1] == 'M') wc++;
        // and to the left
        if(y - 3 >= 0 &&
                words->at(x + 3)[y - 3] == 'S' &&
                words->at(x + 2)[y - 2] == 'A' &&
                words->at(x + 1)[y - 1] == 'M') wc++;
    }

    return wc;
}


int main(){
    string temp;
    vector<string> words;
    int xmasCount = 0;
    int x_masCount = 0;

    while(getline(cin, temp)) words.push_back(temp);

    for(int i = 0; i < words.size(); i++){
        for(int j = 0; j < words[i].size(); j++){
            if(words[i][j] == 'X') xmasCount += findWord(&words, i, j);
            if(words[i][j] == 'M'){
                // search to the right, up and down
                if(j + 2 < words[i].size() && words[i][j + 2] == 'M'){
                    if(i - 1 > 0 && words[i - 1][j + 1] == 'A' && 
                            words[i - 2][j] == 'S' &&
                            words[i - 2][j + 2] == 'S'){
                        x_masCount++;
                    }
                    if(i + 2 < words.size() && words[i + 1][j + 1] == 'A' && 
                            words[i + 2][j] == 'S' &&
                            words[i + 2][j + 2] == 'S'){
                        x_masCount++;
                    }
                }
                // search down, left and right
                if(i + 2 < words.size() && words[i + 2][j] == 'M'){
                    if(j - 1 > 0 && 
                            words[i + 1][j - 1] == 'A' && 
                            words[i][j - 2] == 'S' &&
                            words[i + 2][j - 2] == 'S'){
                        x_masCount++;
                    }
                    if(j + 2 < words[i].size() && 
                            words[i + 1][j + 1] == 'A' && 
                            words[i][j + 2] == 'S' &&
                            words[i + 2][j + 2] == 'S'){
                        x_masCount++;
                    }
                }
            }
        }
    }
    cout << "Times XMAS appears = " << xmasCount << endl;
    cout << "Times X-MAS appears = " << x_masCount << endl;
    // pt 2, 1490 is too low
}
