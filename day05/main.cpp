#include <climits>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;
using ulint = unsigned long long int;

string seedLoc[8] = {"seed", "soil", "fertilizer", "water", "light", "temperature", "humidity", "location"};

struct seedMap{
    string currentPos;
    ulint num;
};
struct seedRange{
    ulint start;
    ulint length;
};

void mapRanges(vector<seedRange> *seedRanges, vector<vector<ulint>> currentRanges, int loc);

int main(){
    string temp;
    vector<vector<seedMap>> seeds;
    vector<vector<vector<ulint>>> ranges;
    // ^ first vector holds which one is it(seed-soil, soil-fert, etc)
    // second vector holds the ranges

    int where = 0;
    cin >> temp;
    for(int i = 0; i < 20; i++){
        cin >> temp;
        seedMap tempSeed;
        tempSeed.currentPos = seedLoc[where];
        tempSeed.num = stoull(temp);
        seeds.push_back(vector<seedMap>());
        seeds.back().push_back(tempSeed);
    }
    while(cin >> temp){
        if(temp == "map:"){
            //cout << seedLoc[where] << " has finished\n";
            // need to make sure everything goes forward
            for(int i = 0; i < seeds.size(); i++){
                if(seeds[i].back().currentPos != seedLoc[where]){
                    // wasn't mapped to anything
                    seedMap tempSeed;
                    tempSeed.currentPos = seedLoc[where];
                    tempSeed.num = seeds[i].back().num;
                    seeds[i].push_back(tempSeed);
                }
            }
            ranges.push_back(vector<vector<ulint>>());
            where++;
            continue;
        }
        // need to check for the string before map
        if(temp.find('-') != -1) continue;

        // we get the first number of our map string
        // temp currently holds the destination range start
        ulint destStart = stoull(temp);
        cin >> temp;
        ulint sourceStart = stoull(temp);
        cin >> temp;
        ulint rangeLength = stoull(temp);
        long long int diff = sourceStart - destStart; // will be what we have to change to remap it
        ranges.back().push_back({destStart, sourceStart, rangeLength});

        // map some seeds
        for(int i = 0; i < seeds.size(); i++){
            // need to move the pointer to the end
            if(seeds[i].back().num >= sourceStart && seeds[i].back().num <= sourceStart + rangeLength && 
                    seeds[i].back().currentPos == seedLoc[where - 1]){
                seedMap tempSeed;
                tempSeed.currentPos = seedLoc[where];
                tempSeed.num = seeds[i].back().num - diff;
                seeds[i].push_back(tempSeed);
            }
        }
    }
    ulint min = 0xffffffffffffffff;
    for(int i = 0; i < seeds.size(); i++){
        //cout << "seed " << i << " " << seeds[i].back().currentPos << " is " << seeds[i].back().num << "\n";
        if(seeds[i].back().num < min) min = seeds[i].back().num;
    }
    cout << "min = " << min << '\n';


    // PART TWOOOOO
    // could brute force with every single seed
    // or do more complex thing by splitting ranges when hitting a boundary
    // the way the ranges are given is: starting index, length
    // so i do a vector of ranges
    vector<seedRange> seedRanges;
    for(int i = 0; i < seeds.size(); i+=2){
        seedRange tempRange;
        tempRange.start = seeds.at(i).at(0).num;
        tempRange.length = seeds.at(i + 1).at(0).num;
        seedRanges.push_back(tempRange);
    }
    // then start mapping
    // if we hit a range boundary, create a new range(will need to run the loop on it again, maybe do recursion?)
    // will have a bunch of ranges by the end but thats fine, then will just find the minimum
    // won't deal with moving through, each number will have to update, if it doesn't it isnt in a map so it just stays the same

    // will do a for loop to run through each mappings
    for(int i = 0; i < 7; i++){
        vector<vector<ulint>> currentRanges = ranges.at(i);
        // a range could split into 2 or 3 ranges
        // should probably do the next step in a function
        // it will modify ranges and can call recursivly
        mapRanges(&seedRanges, currentRanges, 0);

    }
    // find the lowest location
    ulint minLoc = 0xffffffffffffffff;
    for(int i = 0; i < seedRanges.size(); i++){
        if(seedRanges.at(i).start < minLoc) minLoc = seedRanges.at(i).start;
    }
    cout << "Lowest seed location: " << minLoc << "\n";
    return 0;
}


void mapRanges(vector<seedRange> *seedRanges, vector<vector<ulint>> currentRanges, int loc){
    // need to loop through seed ranges
    // when we need to split, split the range, delete current range, add the 2 or 3 ranges to the end, break out of the loop, call mapRanges starting at the last location
    int callAgain = -1;
    for(int i = loc; i < seedRanges->size(); i++){
        for(int j = 0; j < currentRanges.size(); j++){
            ulint seedStart = seedRanges->at(i).start;
            ulint seedLength = seedRanges->at(i).length;
            ulint mapStart = currentRanges.at(j).at(1); // reminder it is (destination range start(map start), source range start, length)
            ulint mapLength = currentRanges.at(j).at(2);
            long long int diff = mapStart - currentRanges.at(j).at(0); // what to map to after conversion
            // four cases
            // 1. this seed range isnt in the map range
            if(seedStart + seedLength < mapStart || mapStart + mapLength <= seedStart){
                continue;
            }
            // 2. this seed range is completely in the map range
            if(seedStart >= mapStart && seedStart + seedLength <= mapStart + mapLength){
                seedRanges->at(i).start -= diff;
                break;
            }
            // 3. this seed range is partially in the map range
            if(seedStart < mapStart && seedStart + seedLength <= mapStart + mapLength && seedStart + seedLength > mapStart){
                // left side is outside, right side is inside
                seedRanges->push_back({mapStart, seedStart + seedLength - mapStart});
                // ^ right side
                seedRanges->push_back({seedStart, mapStart - seedStart});
                // ^ left side

                seedRanges->erase(seedRanges->begin() + i);
                callAgain = i;
                break;
            }
            if((seedStart >= mapStart && seedStart < mapStart + mapLength) 
                    && seedStart + seedLength > mapStart + mapLength){
                // left side is inside, right side is outside
                seedRanges->push_back({mapStart + mapLength, seedStart + seedLength - (mapStart + mapLength)});
                // ^ right side
                seedRanges->push_back({seedStart, mapStart + mapLength - seedStart});
                // ^ left side

                seedRanges->erase(seedRanges->begin() + i);
                callAgain = i;
                break;
            }
            // 4. the seed range completely contains the map range
            if(seedStart < mapStart && seedStart + seedLength > mapStart + mapLength){
                seedRanges->push_back({seedStart, mapStart - seedStart});
                // ^ left side
                seedRanges->push_back({mapStart, mapLength});
                // ^ middle
                seedRanges->push_back({mapStart + mapLength, seedStart + seedLength - (mapStart + mapLength)});
                // ^ right side

                seedRanges->erase(seedRanges->begin() + i);
                callAgain = i;
                break;
            }
        }
        if(callAgain != -1) break;
    }
    if(callAgain != -1) mapRanges(seedRanges, currentRanges, callAgain);
}
