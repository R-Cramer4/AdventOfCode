#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>

int contains(int nums[4]){
	
	if(nums[0] <= nums[2] && nums[1] >= nums[3])
		return 1;
	if(nums[2] <= nums[0] && nums[3] >= nums[1])
		return 1;

	return 0;
}

int overlap(int nums[4]){
	if(nums[2] >= nums[0] && nums[2] <= nums[1])
		return 1;
	if(nums[3] >= nums[0] && nums[3] <= nums[1])
		return 1;
	if(nums[0] >= nums[2] && nums[0] <= nums[3])
		return 1;
	if(nums[1] >= nums[2] && nums[1] <= nums[3])
		return 1;
	return 0;
}


int main(){

	int numbers[4];
	
	std::ifstream infile("input.txt");

	std::string temp;

	int count = 0;
	int pt2 = 0;
	
	while(std::getline(infile, temp)){
		int split = temp.find(",");
		std::string pair1;
		std::string pair2;
		pair1 = temp.substr(0, split);
		pair2 = temp.substr(split + 1, -1);

		int splitA = pair1.find("-");
		std::string num1 = pair1.substr(0, splitA);
		std::string num2 = pair1.substr(splitA + 1, -1);

		int splitB = pair2.find("-");
		std::string num3 = pair2.substr(0, splitB);
		std::string num4 = pair2.substr(splitB + 1, -1);
		
		numbers[0] = std::stoi(num1);
		numbers[1] = std::stoi(num2);
		numbers[2] = std::stoi(num3);
		numbers[3] = std::stoi(num4);

		if(contains(numbers))
			count++;
		if(overlap(numbers))
			pt2++;
	}

	std::cout << "number of pairs that fully contain the other is: " << count << "\n";
	std::cout << "number of pairs that overlap: " << pt2 << "\n";

	return 0;
}
