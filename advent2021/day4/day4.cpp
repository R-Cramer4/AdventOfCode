#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int main(){
	std::ifstream infile("day4.txt");

	std::string numstr;
	std::getline(infile, numstr);
	//numstr has all inputs
	//turn numstr into numbers
	std::vector<int> nums;
	while(numstr.find(",") != -1){
		nums.push_back(std::stoi(numstr.substr(0, numstr.find(","))));
		numstr.erase(0, numstr.find(",") + 1);
	}
	nums.push_back(52);
	// nums has all inputs
	
	std::vector<std::vector<std::vector<int> > > boards;
	// 2d vector inside vector holds each board
	std::string temp;

	int i = -1;
	int j = 0;
	while(std::getline(infile, temp)){
		if(temp == ""){
			i++;
			continue;
		}
		// boards.at(i) holds the board I'm working in
		while(temp[0] != '\0'){
			boards.at(i).at(j % 5).push_back(2);
		}
	}
	std::cout << i << "\n";


	return 0;
}
