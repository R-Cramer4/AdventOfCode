#include <iostream>
#include <fstream>
#include <string>

bool checkCycle(int cycle){
	if(cycle == 20 || cycle == 60)
		return true;
	else if(cycle == 100 || cycle == 140)
		return true;
	else if(cycle == 180 || cycle == 220)
		return true;
	return false;
}
void printCRT(int cycle, int x){
	// cycle % 40 is the current location
	// check if cycle is in the sprite
	if(cycle % 40 >= x && cycle % 40 <= x + 2){
		std::cout << "#";
	}else{
		std::cout << ".";
	}
}

int main(){
	std::ifstream infile("day10.txt");
	std::string temp;

	int x = 1;
	int cycle = 1; // set to 1 because the first instruction is at cycle 1
	int signalStrengths = 0;

	while(std::getline(infile, temp)){
		// check for special cycles
		if(checkCycle(cycle)){
			signalStrengths += cycle * x;
		}
		// do instruction
		if(int(temp.find("noop")) != -1){
			// noop instruction
			printCRT(cycle, x);
			cycle ++;
			if(cycle % 40 == 1)
				std::cout << "\n";
			continue;
		}
		// otherwise its an addx
		// takes 2 cycles to complete
		printCRT(cycle, x);
		cycle++;
		if(checkCycle(cycle)){
			signalStrengths += cycle * x;
		}
		if(cycle % 40 == 1){
			std::cout << "\n";
		}
		printCRT(cycle, x);
		cycle ++;
		x += std::stoi(temp.substr(temp.find(" ")));
		if(cycle % 40 == 1){
			std::cout << "\n";
		}
	}

	std::cout << "Sum of signal Strengths: " << signalStrengths << "\n";


	return 0;
}
