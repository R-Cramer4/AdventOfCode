#include <iostream>
#include <fstream>
#include <string>

int checkDuplicates(std::string str){
	std::sort(str.begin(), str.end());
	for(int i = 0; i < str.length() - 1; i++){
		if(str[i] == str[i + 1])
			return 1;
	}
	return 0;
}

int main(){
	
	std::ifstream infile("input.txt");
	std::string chars;

	std::getline(infile, chars);
	// chars has all characters
	bool foundMarker = false;
	for(int i = 0; i < int(chars.length()) - 14; i++){
		if(!checkDuplicates(chars.substr(i, 4)) && !foundMarker){
			std::cout << "first marker after character: " << i + 4 << "\n";
			foundMarker = true;
		}
		if(!checkDuplicates(chars.substr(i, 14))){
			std::cout << "first message after character: " << i + 14 << "\n";
			break;
		}
	}
	return 0;
}
