#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

enum kind {five, four, fullHouse, three, twoPair, onePair, highCard, none};
char cards[13] = {'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A'};
int findCard(char card);

int main(){
    vector<pair<string, pair<kind, int>>> hands;
    string temp = "";
    while(getline(cin, temp)){
        string first = temp.substr(0, temp.find(' '));
        temp.erase(0, temp.find(' '));
        int second = stoi(temp);
        hands.push_back({first, {none, second}});
    }
    for(int i = 0; i < hands.size(); i++){
            int chars[5] = {-1, -1, -1, -1, -1};
            for(int j = 0; j < hands[i].first.size(); j++){
                int card = findCard(hands[i].first[j]);
                for(int k = 0; k < 5; k++){
                    if(chars[k] == card) break;
                    if(chars[k] == -1){
                        chars[k] = card;
                        break;
                    }
                }
            }
            int uniqueChars = 0;
            for(int i = 0; i < 5; i++){
                if(chars[i] != -1) uniqueChars++;
            }

            // Joker time
            int jokers = 0;
            if(hands[i].first.find('J') != -1){
                uniqueChars--;
                if(uniqueChars <= 1){
                    hands.at(i).second.first = five;
                    continue;
                }
                jokers = count(hands[i].first.begin(), hands[i].first.end(), 'J');
                if(jokers == 3){
                    hands.at(i).second.first = four;
                    continue;
                }
                if(uniqueChars == 2 && jokers == 2){
                    hands.at(i).second.first = four;
                    continue;
                }
                if(uniqueChars == 2 && jokers == 1){
                    if(count(hands.at(i).first.begin(), hands.at(i).first.end(), cards[chars[0]]) == 3 ||
                    count(hands.at(i).first.begin(), hands.at(i).first.end(), cards[chars[1]]) == 3 ||
                    count(hands.at(i).first.begin(), hands.at(i).first.end(), cards[chars[2]]) == 3){
                        hands.at(i).second.first = four;
                    }else hands.at(i).second.first = fullHouse;
                    continue;
                }
                if(uniqueChars == 3){
                    hands.at(i).second.first = three;
                    continue;
                }
                if(uniqueChars == 4){
                    hands.at(i).second.first = onePair;
                    continue;
                }
                cout << "whoops\n";
            }

            // five
            if(uniqueChars == 1){
                hands.at(i).second.first = five;
                continue;
            }

            // four
            if(uniqueChars == 2 &&
                    (count(hands.at(i).first.begin(), hands.at(i).first.end(), cards[chars[0]]) == 4 ||
                     count(hands.at(i).first.begin(), hands.at(i).first.end(), cards[chars[0]]) == 1)){
                hands.at(i).second.first = four;
                continue;
            }
            
            // full house
            if(uniqueChars == 2){
                hands.at(i).second.first = fullHouse;
                continue;
            }

            // three
            if(uniqueChars == 3 && 
                    (count(hands.at(i).first.begin(), hands.at(i).first.end(), cards[chars[0]]) == 3 ||
                    count(hands.at(i).first.begin(), hands.at(i).first.end(), cards[chars[1]]) == 3 ||
                    count(hands.at(i).first.begin(), hands.at(i).first.end(), cards[chars[2]]) == 3)){
                hands.at(i).second.first = three;
                continue;
            }

            // two pair
            if(uniqueChars == 3){
                hands.at(i).second.first = twoPair;
                continue;
            }

            // one pair
            if(uniqueChars == 4){
                hands.at(i).second.first = onePair;
                continue;
            }

            // high card
            hands.at(i).second.first = highCard;
    }
    sort(hands.begin(), hands.end(), [](pair<string, pair<kind, int>> a, pair<string, pair<kind, int>> b) -> bool{
            // going to sort from weakest to strongest hand
            // so will return the weaker of the two hands
            if(b.second.first == a.second.first){
                for(int i = 0; i < a.first.size(); i++){
                    int aCard = 0;
                    for(int j = 0; j < 13; j++){
                        if(a.first[i] == cards[j]){
                            aCard = j;
                            break;
                        }
                    }
                    int bCard = 0;
                    for(int j = 0; j < 13; j++){
                        if(b.first[i] == cards[j]){
                            bCard = j;
                            break;
                        }
                    }
                    if(aCard > bCard) return false;
                    if(bCard > aCard) return true;
                }
            }
            return a.second.first > b.second.first;
        });

    int totalWinnings = 0;
    for(int i = 0; i < hands.size(); i++){
        totalWinnings += hands.at(i).second.second * (i + 1);
        //cout << "hands[" << i << "] = " << hands.at(i).first << ", " << hands.at(i).second.first << ", " << hands.at(i).second.second << "\n";
    }
    cout << "total winnings = " << totalWinnings << "\n";

    return 0;
}

int findCard(char card){
    for(int i = 0; i < 13; i++){
        if(card == cards[i]) return i;
    }
    return -1;
}
