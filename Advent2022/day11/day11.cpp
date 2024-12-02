#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Monkey{
	std::vector<long long int> items;
	int first; // holds -1 if old
	int second; // holds -1 if old
	int test; // test is just checking if divisible by some number
	int result[2]; // if true throw to loc 1 else throw to loc 0
	int timesInspected;
	char operation; // operation
};

void round(struct Monkey * monkeys, int sizeOfMonkeys){
	// loop through each monkeys one at a time
	for(int i = 0; i < sizeOfMonkeys; i++){
		// each turn starting with monkey 0;
		// loop through each items
		for(int j = 0; j < monkeys[i].items.size(); j++){
			// at each item do turn
			// first change worry level
			// cjecl operation
			if(monkeys[i].operation == '+'){
				if(monkeys[i].second == -1){
					monkeys[i].items.at(j) *= 2;
					// adds it to itself so same as doubling
				}else{
					monkeys[i].items.at(j) += monkeys[i].second;
				}
			}else if(monkeys[i].operation == '*'){
				if(monkeys[i].second == -1){
					// squares itself
					monkeys[i].items.at(j) *= monkeys[i].items.at(j);
				}else{
					monkeys[i].items.at(j) *= monkeys[i].second;
				}
			}
			// then worry level gets divided by 3 (relief)
			monkeys[i].items.at(j) %= 9699690;
			// no longer divided by 3 from relief
			// monkeys[i].items.at(j) /= 3;
			// test and then throw
			if(monkeys[i].items.at(j) % monkeys[i].test == 0){
				// do true
				monkeys[monkeys[i].result[1]].items.push_back(monkeys[i].items.at(j));
				// add to next monkey
			}else{
				// do false
				monkeys[monkeys[i].result[0]].items.push_back(monkeys[i].items.at(j));
			}
			// add to items inspected
			monkeys[i].timesInspected ++;
		}
		// remove all items here
		monkeys[i].items.clear();
	}
}

int main(){
	std::ifstream infile("day11.txt");
	std::string temp;

	struct Monkey monkeys[8];
	int sizeOfMonkeys = sizeof(monkeys)/sizeof(monkeys[0]);

	int monkeyNum = 0;

	while(std::getline(infile, temp)){
		// check if inbetween monkeys
		if(!temp.compare("")){
			continue;
		}
		// first check if its a new monkey
		if(temp.find("Monkey ") != -1){
			// new monkey times
			monkeyNum = std::stoi(temp.substr(temp.find(" "), 2));
			// set inspected to 0
			monkeys[monkeyNum].timesInspected = 0;
			continue;
		}
		// check if starting items
		if(temp.find("Starting items: ") != -1){
			std::string del = "  Starting items: ";
			temp.erase(0, del.length());
			// temp holds items
			// nnow need to store items
			// first add the first number
			// little bit of cheating as all numbers are 2 digit
			monkeys[monkeyNum].items.push_back(std::stoi(temp.substr(0, 2)));
			// after last cycle the length is 2
			while(temp.size() > 2){
				// first erase old number
				temp.erase(0, temp.find(", ") + 2);
				monkeys[monkeyNum].items.push_back(std::stoi(temp.substr(0, 2)));
			}	
			continue;
		}
		// operation time
		if(temp.find("Operation: ") != -1){
			// operation
			std::string del = "  Operation: new = ";
			temp.erase(0, del.length());
			// temp just has old/number +/* old/number
			// always starts with old then opperation
			monkeys[monkeyNum].first = -1;
			// erasr old
			temp.erase(0, 4);
			// now has operator and number/old
			// set operator
			monkeys[monkeyNum].operation = temp[0];
			// erase
			temp.erase(0, 2);
			if(temp.find("old") != -1){
				monkeys[monkeyNum].second = -1;
			}else{
				monkeys[monkeyNum].second = std::stoi(temp);
			}
			continue;
		}
		// test time
		if(temp.find("Test: ") != -1){
			// is the test
			std::string del = "  Test: divisible by ";
			temp.erase(0, del.length());
			// temp just has number
			monkeys[monkeyNum].test = std::stoi(temp);
			continue;
		}
		// result of test
		if(temp.find("true") != -1){
			// if true condition
			std::string del = "    If true: throw to monkey ";
			temp.erase(0, del.length());
			monkeys[monkeyNum].result[1] = std::stoi(temp);
			continue;
		}
		// check if false
		if(temp.find("false") != -1){
			// if false
			std::string del = "    If false: throw to monkey ";
			temp.erase(0, del.length());
			monkeys[monkeyNum].result[0] = std::stoi(temp);
		}
	}
	// now do rounds
	int numRounds = 10000;
	for(int i = 0; i < numRounds; i++){
		// each round call round function
		round(monkeys, sizeOfMonkeys);
	}
	long long int insLess = 0;
	long long int insBig = 0;
	for(int i = 0; i < sizeOfMonkeys; i++){
		std::cout << "Monkey " << i << " Inspected: " << monkeys[i].timesInspected << " times\n";
		if(monkeys[i].timesInspected > insBig){
			insLess = insBig;
			insBig = monkeys[i].timesInspected;
		}else if(monkeys[i].timesInspected > insLess){
			insLess = monkeys[i].timesInspected;
		}
	}
	std::cout << "Level of monkey business: " << insLess * insBig << "\n";
	return 0;
}
