#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string findRatings(std::vector<std::string> bits, int loc, int max){
	int size = bits.size();
	if(bits.size() == 1){
		return bits.at(0);
	}
	std::vector<std::string> reducedBits;
	int numBits[2];
	std::memset(numBits, 0, sizeof(numBits));
	for(int i = 0; i < size; i++){
		if(bits.at(i)[loc] == 49)
			numBits[1]++;
		else
			numBits[0]++;
	}
	if(numBits[0] > numBits[1]){
		// if more 0 that 1
		for(int i = 0; i < size; i++){
			if(bits.at(i)[loc] == 48 && max){
				reducedBits.push_back(bits.at(i));
			}else if(bits.at(i)[loc] == 49 && !max){
				reducedBits.push_back(bits.at(i));
			}
		}
	}else{
		// if more 1 than 0
		for(int i = 0; i < size; i++){
			if(bits.at(i)[loc] == 49 && max){
				reducedBits.push_back(bits.at(i));
			}else if(bits.at(i)[loc] == 48 && !max){
				reducedBits.push_back(bits.at(i));
			}
		}
	}
	return findRatings(reducedBits, loc + 1, max);
}

int main(){
	std::ifstream infile("day3.txt");
	std::string temp;
	std::vector<std::string> bits;

	int zbits[12];
	std::memset(zbits, 0, sizeof(zbits));
	int obits[12];
	std::memset(obits, 0, sizeof(obits));
	while(std::getline(infile, temp)){
		for(int i = 0; i < temp.length(); i++){
			if(temp[i] == 48)
				obits[i]++;
			else
				zbits[i]++;
		}
		bits.push_back(temp);
	}
	int gamma = 0;
	int epsilon = 0;
	for(int i = 0; i < 12; i++){
		gamma = gamma << 1;
		epsilon = epsilon << 1;
		if(zbits[i] < obits[i]){
			gamma++;
		}else{
			epsilon++;
		}
	}
	std::string o2Rating = findRatings(bits, 0, 1);
	std::string co2Rating = findRatings(bits, 0, 0);
	int numO2 = 0;
	int numCO2 = 0;

	for(int i = 0; i < o2Rating.length(); i++){
		numO2 = numO2 << 1;
		numCO2 = numCO2 << 1;
		if(o2Rating[i] == 49){
			numO2++;
		}
		if(co2Rating[i] == 49)
			numCO2++;
	}

	std::cout << "O2 Rating = " << numO2 << "\n";
	std::cout << "CO2 Rating = " << numCO2 << "\n";
	std::cout << "Life support rating = " << numO2 * numCO2 << "\n";
	

	std::cout << "Gamma = " << gamma << "\nEpsilon = " << epsilon << "\nMultiplied = " <<
		gamma * epsilon << "\n";
	return 0;
}
