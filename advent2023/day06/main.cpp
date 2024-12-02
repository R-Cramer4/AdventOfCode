#include <iostream>
using namespace std;
using lint = long long int;

int main(){
    int numWays = 1;
    int time[4] = {40, 82, 91, 66};
    int dist[4] = {277, 1338, 1349, 1063};
    for(int i = 0; i < 4; i++){
        int currentRace = 0;
        for(int j = 0; j < time[i]; j++){
            if((time[i] - j) * j > dist[i]) currentRace++;
        }
        numWays *= currentRace;
    }
    cout << "Number of ways to win = " << numWays << "\n";
    
    lint bigRaceTime = 40829166;
    lint bigRaceDist = 277133813491063;
    int bigRaceWins = 0;
    for(lint i = 0; i < bigRaceTime; i++){
        if((bigRaceTime - i) * i > bigRaceDist) bigRaceWins++;
    }
    cout << "Number of ways to win the big race = " << bigRaceWins << "\n";

    return 0;
}
