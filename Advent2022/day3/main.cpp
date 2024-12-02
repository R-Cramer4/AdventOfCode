#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int commonLetter(std::string str[], int n){
	// Caps letters in first half
	// lowercase in second half
	bool prim[52];
	std::memset(prim, true, sizeof(prim));
	
	for(int i = 0; i < n; i++){
		bool sec[52] = { false };

		for(int j = 0; str[i][j]; j++){
			if(str[i][j] <= 'Z'){
				if(prim[str[i][j] - 'A'])
					sec[str[i][j] - 'A'] = true;
			}else{
				if(prim[str[i][j] - 'a' + 26])
					sec[str[i][j] - 'a' + 26] = true;
			}
		}
		std::memcpy(prim, sec, 52);
	}

	for(int i = 0; i < 52; i++){
		if(prim[i]){
			if(i < 26)
				return i + 'A';
			else
				return i - 26 + 'a';
		}
	}

	return -1;
}


int main(){
	
	std::ifstream infile("input.txt");
	std::string temp;

	std::vector<std::string> groups;


	int part1 = 0;
	int part2 = 0;

	while(std::getline(infile, temp)){
		groups.push_back(temp);
		if(groups.size() >= 3){
			// do the math here
			std::string str[] = {
				groups.at(0),
				groups.at(1),
				groups.at(2)
			};
			int x = commonLetter(str, 3);
			
			if(x >= 97){
				// lowercase
				part2 += (x - 96);
			}else{
				part2 += (x - 38);
			}
			groups.erase(groups.begin(), groups.end());
		}
		
		//do stuff
		std::string halves[2];
		halves[0] = temp.substr(0, temp.length()/2); // contains first half
		halves[1] = temp.substr(temp.length()/2, -1); // contains second half
		
		

		int x = int(commonLetter(halves, 2));
		
		if(x >= 97){
			// lowercase
			part1 += (x - 96);
		}else{
			part1 += (x - 38);
		}
	}

	std::cout << "Sum of priorities is: " << part1 << "\n";
	std::cout << "Sum of badges is: " << part2 << "\n";
	
	return 0;
}
