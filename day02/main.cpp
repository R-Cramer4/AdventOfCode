#include <iostream>
#include <string>


using namespace std;

int main(){
    int maxColor[3] = {12, 13, 14};
    string colorId[3] = {"red", "green", "blue"};
    int minColors[3] = {0, 0, 0};

    int possibleGames = 0;
    int powerSum = 0;

    string temp;
    int id = 0;
    int possible = 1;
    while(cin >> temp){
        if(temp == "Game"){
            cin >> temp;
            id = stoi(temp);
            possibleGames += id;
            possible = 1;

            // part 2
            powerSum += (minColors[0] * minColors[1] * minColors[2]);
            minColors[0] = minColors[1] = minColors[2] = 0;
            continue;
        }
        int num = stoi(temp);
        cin >> temp;
        if(temp.find(',') != -1) temp = temp.substr(0, temp.find(','));
        if(temp.find(';') != -1) temp = temp.substr(0, temp.find(';'));
        for(int i = 0; i < 3; i++){
            if(temp == colorId[i]){
                if(num > maxColor[i]){
                    if(possible != 0){
                        possible = 0;
                        possibleGames -= id;
                    }
                }
                if(num > minColors[i]) minColors[i] = num;
                break;
            }
        }
    }
    powerSum += (minColors[0] * minColors[1] * minColors[2]);

    cout << "\nTotal possible games = " << possibleGames << "\n";
    cout << "Power sum = " << powerSum << "\n";



    return 0;
}
