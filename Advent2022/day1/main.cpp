#include <iostream>
#include <fstream>
#include <string>

int main(){

	std::ifstream infile("input.txt");

	std::string temp;

	int maxCalories = 0;
	int second = 0;
	int third = 0;

	int tempCals = 0;
	while(std::getline(infile, temp)){
		if(temp.empty()){
			if(tempCals > maxCalories){
				maxCalories = tempCals;
			}else if(tempCals > second){
				second = tempCals;
			}else if(tempCals > third){
				third = tempCals;
			}
			tempCals = 0;
			continue;
		}
		tempCals += std::stoi(temp);
	}
	
	std::cout << "Max = " << maxCalories << "\n";
	std::cout << "second = " << second << "\n";
	std::cout << "third = " << third << "\n";
	std::cout << "total = " << maxCalories + second + third << "\n";

	return 0;
}
