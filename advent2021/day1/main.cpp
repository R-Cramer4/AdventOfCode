#include <iostream>
#include <fstream>
#include <string>


int main(){
	
	std::fstream infile("input.txt");
	std::string temp;

	int prev = 100000000;
	int count = 0;
	int countWin = 0;
	int a = 0;
	int b = 0;
	int c = 0;
	int i = 0;
	while(std::getline(infile, temp)){
		int num = std::stoi(temp);
		if(prev < num)
			count++;
		prev = num;
		
		//windows
		if(i % 3 == 0){
			b += num;
			if(b > a)
				countWin++;
			a = num;
			c += num;
		}else if(i % 3 == 1){
			c += num;
			if(c > b)
				countWin++;
			b = num;
			a += num;
		}else if(i % 3 == 2){
			a += num;
			if(a > c)
				countWin++;
			b += num;
			c = num;
		}
		i++;
	}
	
	std::cout << "Times increased = " << count << "\n";
	std::cout << "Times increased in 3 window = " << countWin - 3 << "\n";

	return 0;
}
