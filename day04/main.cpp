#include <iostream>
#include <string>
#include <vector>

using namespace std;

int findCards(vector<int> numWinnings, int loc, int *numCards);

int main(){
    string temp;
    int ans = 0;
    int winningNumbers[10] = {0};
    int side = 0;
    int currentWinnings = 0;
    vector<int> numWinnings;
    int numCards[187] = {0};
    while(cin >> temp){
        if(temp == "Card"){
            side = 0;
            ans += currentWinnings;
            currentWinnings = 0;
            numWinnings.push_back(0);
            cin >> temp;
            continue;
        }
        if(!side){
            for(int i = 0; i < 10; i++){
                winningNumbers[i] = stoi(temp);
                cin >> temp;
            }
            side = 1;
            continue;
        }
        int currentNum = stoi(temp);
        for(int i = 0; i < 10; i++){
            if(currentNum == winningNumbers[i]){
                if(currentWinnings == 0){
                    currentWinnings = 1;
                }
                else{
                    currentWinnings = currentWinnings << 1;
                }
                numWinnings.back() += 1;
            }
        }
    }

    cout << "Total winnings = " << ans << "\n";
    int totalCards = 0;
    for(int i = 0; i < numWinnings.size(); i++){
        totalCards += findCards(numWinnings, i, numCards);
    }
    cout << "Total number of cards = " << totalCards << "\n";


    return 0;
}

int findCards(vector<int> numWinnings, int loc, int *numCards){
    if(numCards[loc] != 0) return numCards[loc];
    if(numWinnings.at(loc) == 0){
        numCards[loc] = 1;
        return 1; // the original card
    }

    int currentCard = 1;
    for(int i = 1; i <= numWinnings.at(loc); i++){
        currentCard += findCards(numWinnings, loc + i, numCards);
    }
    numCards[loc] = currentCard;
    return currentCard;
}
