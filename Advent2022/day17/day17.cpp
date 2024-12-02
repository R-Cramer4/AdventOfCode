#include <iostream>
#include <fstream>
#include <string>

int main(){
	std::ifstream infile("day17.txt");
	std::string input;

	std::getline(infile, input);// input has the input sting
	
	int loc = 0; // location in input, if it reaches the end of the string it repeats;
	
	int width = 7;

	// spawning rules:
	// left edge is 2 units away from the wall
	// bottom is 3 units above tallest point
	//
	// spawns in this repeating pattern:
	//
	// ####
	//
	// .#.
	// ###
	// .#.
	//
	// ..#
	// ..#
	// ###
	//
	// #
	// #
	// #
	// #
	//
	// ##
	// ##
	
	int rockNum = 0;

	// moving rules:
	// gets pushed 1 unit
	// moves down 1 unit
	

	// 2022 rocks fall and stop
	// need to find height
	
	
}
