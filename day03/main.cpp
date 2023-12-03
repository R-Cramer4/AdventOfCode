#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

// input the strings surrounding the number, and the location and size of the number in the current line
// returns 1 if it is a part number, 0 otherwise
int findPartNumber(string prevLine, string currentLine, string nextLine, int numStart, int numEnd);
int findGearRatio(string prevLine, string currentLine, string nextLine, int loc);

int main(){
    int partSum = 0;
    int gearRatios = 0;
    string currentLine;
    string prevLine = "";
    string nextLine = "";
    cin >> currentLine;
    int numStart = -1;
    int numEnd = -1;
    while(cin >> nextLine){
        //cout << "PrevLine: " << prevLine << "\nCurrentLine: " << currentLine << "\nNextLine: " << nextLine << "\n";
        for(int i = 0; i < currentLine.size(); i++){
            if(currentLine[i] == 42){
                gearRatios += findGearRatio(prevLine, currentLine, nextLine, i);
            }
            if(currentLine[i] >= 48 && currentLine[i] <= 57){
                if(numStart == -1){
                    numStart = i;
                    numEnd = i;
                }
                else numEnd = i;
            }
            else if(numStart != -1 && numEnd != -1){
                // reached the end of the number
                //cout << "searching around number " << currentLine.substr(numStart, numEnd - numStart + 1) << "\n";
                partSum += stoi(currentLine.substr(numStart, numEnd - numStart + 2)) * 
                    findPartNumber(prevLine, currentLine, nextLine, numStart, numEnd);
                numEnd = -1;
                numStart = -1;
            }
        }
        if(numStart != -1 && numEnd != -1){
            // reached the end of the number
            //cout << "searching around number " << currentLine.substr(numStart, numEnd - numStart + 1) << "\n";
            partSum += stoi(currentLine.substr(numStart, numEnd - numStart + 2)) * 
                findPartNumber(prevLine, currentLine, nextLine, numStart, numEnd);
            numEnd = -1;
            numStart = -1;
        }
        prevLine = currentLine;
        currentLine = nextLine;
    }

    nextLine = "";
    //cout << "PrevLine: " << prevLine << "\nCurrentLine: " << currentLine << "\nNextLine: " << nextLine << "\n";
    for(int i = 0; i < currentLine.size(); i++){
        if(currentLine[i] == 42){
            gearRatios += findGearRatio(prevLine, currentLine, nextLine, i);
        }
        if(currentLine[i] >= 48 && currentLine[i] <= 57){
            if(numStart == -1){ 
                numStart = i;
                numEnd = i;
            }
            else numEnd = i;
        }
        else if(numStart != -1 && numEnd != -1){
            // reached the end of the number
            partSum += stoi(currentLine.substr(numStart, numEnd - numStart + 2)) * 
                findPartNumber(prevLine, currentLine, nextLine, numStart, numEnd);
            numStart = -1;
            numEnd = -1;
        }
    }

    // 536884 is too low
    cout << "Part numbers = " << partSum << "\n";
    // 73731090 is too low
    cout << "Gear Ratios = " << gearRatios << "\n";
}

int findPartNumber(string prevLine, string currentLine, string nextLine, int numStart, int numEnd){
    // need to check the rectangle around our number for any character thats not a .
    
    // check in the previous line
    if(prevLine != ""){
        for(int i = max(0, numStart - 1); i < min((int)prevLine.size(), numEnd + 2); i++){
            if(prevLine[i] != 46 && prevLine[i] > 32){
                //cout << prevLine.substr(max(0, numStart - 1), min((int)prevLine.size(), numEnd + 1) - numStart + 1) << " Has a symbol for the number " <<currentLine.substr(numStart, numEnd) <<"\n";
                return 1;
            }
        }
    }

    // check current Line
    if(numStart - 1 >= 0){
        int loc = numStart - 1;
        if(currentLine[loc] != 46 && currentLine[loc] > 32){
            //cout << currentLine.substr(numStart - 1, numEnd - numStart + 1) << " Has a symbol\n";
            return 1;
        }
    }
    if(numEnd + 1 < currentLine.size()){
        int loc = numEnd + 1;
        if(currentLine[loc] != 46 && currentLine[loc] > 32){
            //cout << currentLine.substr(numStart, numEnd - numStart + 2) << " has a symbol\n";
            return 1;
        }
    }

    // check next Line
    if(nextLine != ""){
        for(int i = max(0, numStart - 1); i < min((int)nextLine.size(), numEnd + 2); i++){
            if(nextLine[i] != 46 && nextLine[i] > 32){
                //cout << nextLine.substr(max(0, numStart - 1), min((int)nextLine.size(), numEnd + 1) - numStart + 1) << " Has a symbol for the number " <<currentLine.substr(numStart, numEnd) <<"\n";
                return 1;
            }
        }
    }
    //cout << prevLine << " ;PrevLine\n";
    //cout << currentLine << " ;currentLine no symbol fiund for: " << currentLine.substr(numStart, numEnd - numStart + 1) << "\n";
    //cout << nextLine << " ;NextLine\n";
    return 0;
}

int findGearRatio(string prevLine, string currentLine, string nextLine, int loc){
    // given a gear we need to find 2 numbers surrounding it
    int num1 = 0;
    int num2 = 0;

    // check above
    for(int i = -1; i <= 1; i++){
        int temp = 0;
        if(prevLine[loc + i] >= 48 && prevLine[loc + i] <= 57){
            temp = prevLine[loc + i] - 48;
            // left
            for(int j = loc + i - 1; j >= 0; j--){
                if(prevLine[j] >= 48 && prevLine[j] <= 57){
                    temp += (prevLine[j] - 48) * pow((double)10, (double)(loc + i - j));
                }else break;
            }
            // right
            for(int j = loc + i + 1; j < prevLine.size(); j++){
                if(prevLine[j] >= 48 && prevLine[j] <= 57){
                    temp = (temp * 10) + prevLine[j] - 48;
                }else break;
            }
            if(num1 == temp || num2 == temp) temp = 0;
            else if(num1 == 0) num1 = temp;
            else if(num2 == 0) num2 = temp;
        }
    }


    // check below
    for(int i = -1; i <= 1; i++){
        int temp = 0;
        if(nextLine[loc + i] >= 48 && nextLine[loc + i] <= 57){
            temp = nextLine[loc + i] - 48;
            // left
            for(int j = loc + i - 1; j >= 0; j--){
                if(nextLine[j] >= 48 && nextLine[j] <= 57){
                    temp += (nextLine[j] - 48) * pow((double)10, (double)(loc + i - j));
                }else break;
            }
            // right
            for(int j = loc + i + 1; j < nextLine.size(); j++){
                if(nextLine[j] >= 48 && nextLine[j] <= 57){
                    temp = (temp * 10) + nextLine[j] - 48;
                }else break;
            }
            if(num1 == temp || num2 == temp) temp = 0;
            else if(num1 == 0) num1 = temp;
            else if(num2 == 0) num2 = temp;
        }
    }

    // check to the sides
    if(currentLine[loc - 1] >= 48 && currentLine[loc - 1] <= 57){
        int temp = currentLine[loc - 1] - 48;
        for(int i = loc - 2; i >= 0; i--){
            if(currentLine[i] >= 48 && currentLine[i] <= 57){
                temp += (currentLine[i] - 48) * pow((double)10, (double)(loc - 1 - i));
            }else break;
        }
        if(num1 == temp || num2 == temp) temp = 0;
        else if(num1 == 0) num1 = temp;
        else if(num2 == 0) num2 = temp;
    }
    if(currentLine[loc + 1] >= 48 && currentLine[loc + 1] <= 57){
        int temp = currentLine[loc + 1] - 48;
        for(int i = loc + 2; i < currentLine.size(); i++){
            if(currentLine[i] >= 48 && currentLine[i] <= 57){
                temp = (temp * 10) + currentLine[i] - 48;
            }else break;
        }
        if(num1 == temp || num2 == temp) temp = 0;
        else if(num1 == 0) num1 = temp;
        else if(num2 == 0) num2 = temp;
    }
    return num1 * num2;
}
