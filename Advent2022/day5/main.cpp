#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>



int main(){
	
	std::ifstream infile("input.txt");
	if(!infile){
		return 1;
	}
	std::vector<std::vector<char> > crates(9);

	std::string temp;
	// input time
	while(std::getline(infile, temp)){
		if(!infile){
			std::cout << "I have failed in life";
		}
		if(int(temp.find("move")) == -1){
			// do the array
			
			// 1 empty column = 3 spaces
			// 1 space inbetween columns


			// first thing is remove space inbetween rows
			for(int i = 3; i < int(temp.length()); i+= 3){
				temp.erase(i, 1);
			}
			// input line has no buffer spaces

			// check if its the last line
			if(int(temp.find("1")) != -1){
				continue;
			}

			// loop through at each location where the number will buffer
			for(int i = 1; i < int(temp.length()); i+= 3){
				if(temp.substr(i, 1).compare(" ")){
					// if not a space
					// insert at beginning of vector
					int x = i / 3;
					crates.at(x).insert(crates.at(x).begin(), temp.substr(i, 1)[0]);
				}
			}

		}else{
			// command time
			int moveNum = 0;
			int moveFrom = 0;
			int moveTo = 0;

			// erases "move "
			temp.erase(0, 5);
			moveNum = std::stoi(temp.substr(0, temp.find(" from")));

			// erases "x from "
			temp.erase(0, temp.find("m ") + 2);
			moveFrom = std::stoi(temp.substr(0, temp.find(" to"))) - 1;

			// erases "x to "
			temp.erase(0, temp.find("to ") + 3);
			moveTo = std::stoi(temp) - 1;

			// Now time to move
			// crate mover 9000 code
			/*
			for(int i = 1; i <= moveNum; i++){
				char x = crates.at(moveFrom).back();
				crates.at(moveFrom).pop_back();
				crates.at(moveTo).push_back(x);
			}
			*/

			// crate mover 9001 code
			int temp = crates.at(moveTo).size();
			for(int i = 1; i <= moveNum; i++){
				// inset puts before elemnt said
				char x = crates.at(moveFrom).back();
				crates.at(moveFrom).pop_back();
				crates.at(moveTo).insert(crates.at(moveTo).begin() + temp, x);
			}
		}
	}

	for(int i = 0; i < int(crates.size()); i++){
		std::cout << crates.at(i).back();
	}
	std::cout << std::endl;
	exit(1);
	return 0;
}


