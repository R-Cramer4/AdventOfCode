#include <fstream>
#include <string>
#include <iostream>

int main(){
	std::ifstream infile("input.txt");
	std::string temp;

	int part1 = 0;
	int part2 = 0;

	while(std::getline(infile, temp)){
		
		if(temp[0] == 'A'){ // rock
			if(temp[2] == 'X'){
				part1 += 4;
				part2 += 3;
			} 
			else if(temp[2] == 'Y'){
				part1 += 8;
				part2 += 4;
			}
			else if(temp[2] == 'Z'){
				part1 += 3;
				part2 += 8;
			} 
		}else if(temp[0] == 'B'){ // paper
			if(temp[2] == 'X'){
				part1 += 1;
				part2 += 1;
			}
			else if(temp[2] == 'Y'){
				part1 += 5;
				part2 += 5;
			}
			else if(temp[2] == 'Z'){
				part1 += 9;
				part2 += 9;
			}
		}else if(temp[0] == 'C'){ // scissors
			if(temp[2] == 'X'){
				part1 += 7;
				part2 += 2;
			}
			else if(temp[2] == 'Y'){
				part1 += 2;
				part2 += 6;
			}
			else if(temp[2] == 'Z'){ 
				part1 += 6;
				part2 += 7;
			}
		}
	}

	std::cout << "Your part1 Score is: " << part1 << "\n";
	std::cout << "Your part2 Score is: " << part2 << "\n";

	return 0;
}
