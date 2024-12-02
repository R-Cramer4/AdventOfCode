#include <iostream>
#include <fstream>
#include <string>

int main(){
	std::ifstream infile("input.txt");
	std::string temp;

	int hori = 0;
	int vert = 0;
	int aim = 0;
	
	while(std::getline(infile, temp)){
		std::string direction = temp.substr(0, temp.find(" "));
		int num = std::stoi(temp.substr(temp.find(" ") + 1, 1));
		if(direction == "forward"){
			hori += num;
			vert += (num * aim);
		}
		else if(direction == "up")
			aim -= num;
		else if(direction == "down")
			aim += num;
	}



	std::cout << "Final depth = " << vert << "\nFinal distance = " << hori << "\nMultiplied = " << 
		vert * hori << "\n";


	return 0;
}
