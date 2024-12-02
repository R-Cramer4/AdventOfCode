#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>

void parseLine(std::vector<std::pair<int, int> > * airBlocked, std::string temp){
	int loc = 0;
	while(loc < temp.length()){
		int x1 = std::stoi(temp.substr(loc, temp.find(",", loc) - loc));
		// failing because at the end of temp there is no space
		int y1 = std::stoi(temp.substr(temp.find(",", loc) + 1, temp.find(" ", loc) - loc));
		loc = temp.find("->", loc) + 3;
		int x2 = std::stoi(temp.substr(loc, temp.find(",", loc) - loc));
		int y2 = std::stoi(temp.substr(temp.find(",", loc) + 1, temp.find(" ", loc) - loc));
		// now add all the locations blocked by this line to airBlocked
		if(x1 == x2){
			// vertical line
			if(y2 > y1){
				for(int i = y1; i <= y2; i++){
					airBlocked->push_back({x1, i});
				}
			}else{
				for(int i = y2; i <= y1; i++){
					airBlocked->push_back({x1, i});
				}
			}
		}
		if(y1 == y2){
			// horizontal line
			if(x2 > x1){
				for(int i = x1; i <= x2; i++){
					airBlocked->push_back({i, y1});
				}
			}else{
				for(int i = x2; i <= x1; i++){
					airBlocked->push_back({i, y1});
				}
			}
		}
		if(temp.find("->", loc) == -1){
			break;
		}
	}
}

int binarySearch(std::vector<std::pair<int, int> > airBlocked, 
		std::pair<int, int> look, int low, int high, int findX){
	if(low > high){
		return -1;
	}
	int mid = (low + high) / 2;
	if(airBlocked.at(mid).first == look.first){
		if(findX != -1){
			return mid;
		}
		// need to look throught all of the sections
		for(int i = mid; i >= 0; i--){
			if(airBlocked.at(i).first != look.first){
				break;
			}else if(airBlocked.at(i).second == look.second){
				return i;
			}
		}
		for(int i = mid; i < airBlocked.size(); i++){
			if(airBlocked.at(i).first != look.first){
				break;
			}else if(airBlocked.at(i).second == look.second){
				return i;
			}
		}
	}
	else if(look.first > airBlocked.at(mid).first){
		return binarySearch(airBlocked, look, mid + 1, high, findX);
	}
	else{
		return binarySearch(airBlocked, look, low, mid - 1, findX);
	}
	return -1;
}

void eraseElements(std::vector<std::pair<int, int> > * airBlocked, std::vector<std::pair<int, int> > * airBlockedFull){
	sort(airBlockedFull->begin(), airBlockedFull->end());
	// go throgh all elements
	// if an element is completely blocked in above, from the left, and from the right
	// delete it
	std::vector<int> deleteItems;
	for(int i = 0; i < airBlocked->size(); i++){
		// check if there is something on top of this element
		// sorted by x value
		// so im looking for {x, y-1}
		// if found, it is blocked above
		std::pair<int, int> tempPair;
		// the current pair is { airBlocked->at(i).first, airBlocked->at(i).second }
		// i look to see if there is anything in the surrounding directions
		tempPair.first = airBlocked->at(i).first;
		tempPair.second = airBlocked->at(i).second - 1;
		int sizeFull = airBlockedFull->size();
		int searchUp = binarySearch(*airBlockedFull, tempPair, 0, sizeFull - 1, -1);

		if(searchUp == -1){
			// it is not bloked from above
			continue;
		}
		// left
		tempPair.first = airBlocked->at(i).first - 1;
		tempPair.second = airBlocked->at(i).second;
		int searchLeft = binarySearch(*airBlockedFull, tempPair, 0, sizeFull - 1, -1);

		if(searchLeft == -1){
			// not blocked from left
			continue;
		}
		// right
		tempPair.first = airBlocked->at(i).first + 1;
		tempPair.second = airBlocked->at(i).second;
		int searchRight = binarySearch(*airBlockedFull, tempPair, 0, sizeFull - 1, -1); 

		if(searchRight == -1){
			continue;
		}
		// search diagonals too
		// up right
		tempPair.first = airBlocked->at(i).first + 1;
		tempPair.second = airBlocked->at(i).second - 1;
		int searchUpRight = binarySearch(*airBlockedFull, tempPair, 0, sizeFull - 1, -1);

		if(searchUpRight == -1)
			continue;
		// up left
		tempPair.first = airBlocked->at(i).first - 1;
		// Temp Pair second can stau the same
		int searchUpLeft = binarySearch(*airBlockedFull, tempPair, 0, sizeFull - 1, -1);
		if(searchUpLeft == -1)
			continue;
		// blocked in all directions
		deleteItems.push_back(i);
	}
	// deletes valid items
	for(int i = deleteItems.size() - 1; i >= 0; i--){
		airBlocked->erase(airBlocked->begin() + deleteItems.at(i));
	}
}


int produceSand(std::vector<std::pair<int, int> > * airBlocked, std::vector<std::pair<int, int> > * airBlockedFull){
	// call once per sand
	// returns 1 if the sand stops
	// returns 0 if it never does
	int airBlockedSize = airBlocked->size();
	int sandX = 500;
	int sandY = 0;
	bool stopped = false;
	while(!stopped){
		// 179 is the floor
		if(sandY >= 178){
			// insertion logic
			int loc = binarySearch(*airBlocked, {sandX, 0}, 0, airBlockedSize - 1, 1);
			if(loc == -1){
				if(sandX < airBlocked->at(0).first){
					loc = -1;
				}else if(sandX > airBlocked->at(airBlockedSize - 1).first){
					loc = airBlockedSize - 1;
				}else{
					for(int i = 0; i < airBlockedSize - 1; i++){
						if(airBlocked->at(i).first < sandX && airBlocked->at(i + 1).first > sandX){
							loc = i;
						}
					}
				}
			}
			airBlocked->insert(airBlocked->begin() + loc + 1, {sandX, sandY});
			airBlockedFull->push_back({sandX, sandY});
			return 1;
			break;
		}
		// dropped sand
		// move one location down
		// first check if it can move down
		bool canMoveDown = true;
		std::pair<int, int> temp;
		temp.first = sandX;
		temp.second = sandY + 1;
		if(binarySearch(*airBlocked, temp, 0, airBlockedSize - 1, -1) != -1){
			canMoveDown = false;
		}
		if(canMoveDown){
			sandY++;
			continue;
		}
		// check down and to the left
		bool downAndLeft = true;
		temp.first = sandX - 1;
		temp.second = sandY + 1;
		if(binarySearch(*airBlocked, temp, 0, airBlockedSize - 1, -1) != -1){
			downAndLeft = false;
		}
		if(downAndLeft){
			sandX--;
			sandY++;
			continue;
		}
		// check down and to the right
		bool downAndRight = true;
		temp.first = sandX + 1;
		temp.second = sandY + 1;
		if(binarySearch(*airBlocked, temp, 0, airBlockedSize - 1, -1) != -1){
			downAndRight = false;
		}
		if(downAndRight){
			sandX++;
			sandY++;
			continue;
		}
		if(sandX == 500 && sandY == 0){
			return 0;
		}
		// sand cant move and therefore is stopped
		stopped = true;
	}	
	// can put in where it should go and i will only have to sort once
	int loc = binarySearch(*airBlocked, {sandX, 0}, 0, airBlockedSize - 1, 1);
	// insertion logic
	if(loc == -1){
		if(sandX < airBlocked->at(0).first){
			loc = -1;
		}else if(sandX > airBlocked->at(airBlockedSize - 1).first){
			loc = airBlockedSize - 1;
		}
		else{
			for(int i = 0; i < airBlockedSize - 1; i++){
				if(airBlocked->at(i).first < sandX && airBlocked->at(i + 1).first > sandX){
					loc = i;
				}
			}
		}
	}
	airBlocked->insert(airBlocked->begin() + loc + 1, {sandX, sandY});
	airBlockedFull->push_back({sandX, sandY});
	return 1;
}


int main(){
	std::ifstream infile("day14.txt");
	std::string temp;
	std::vector<std::pair<int, int> > airBlocked; // has all air that is blocked by sand or rock
	std::vector<std::pair<int, int> > airBlockedFull;
	
	// input
	while(std::getline(infile, temp)){
		parseLine(&airBlocked, temp);
	}
	// need to remove duplicates
	// complexity of o(N^2) but i dont really care
	for(int i = 0; i < airBlocked.size(); i++){
		for(int j = 0; j < airBlocked.size(); j++){
			if(airBlocked.at(i) == airBlocked.at(j) && i != j){
				airBlocked.erase(airBlocked.begin() + j);
			}
		}
	}
	printf("Input done\n");
	// now needs to start producing sand
	int numSand = 0;
	// sort air Blokced
	sort(airBlocked.begin(), airBlocked.end());
	// has all of the locations
	for(int i = 0; i < airBlocked.size(); i++){
		airBlockedFull.push_back(airBlocked.at(i));
	}
	while(produceSand(&airBlocked, &airBlockedFull)){
		if(numSand % 300 == 0)
			eraseElements(&airBlocked, &airBlockedFull);
		numSand++;
		std::cout << "\033[A\rCurrent number of sand fallen = " << numSand;
		std::cout << "\nSize of airBlocked = " << airBlocked.size() << "  ";
	}
	std::cout << "\nnumber of sand fallen before sand falls into the abyss = " << numSand + 1 << "\n";
	// heights go from 14 - 177
	// widths go from 492 - 551

	return 0;
}
