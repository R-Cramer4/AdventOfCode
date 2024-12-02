#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

struct Valve{
	int flowRate;
	std::string name;
	std::vector<std::string> leadsTo;

public:
	bool operator==(const Valve& other){
		return flowRate == other.flowRate &&
			   name == other.name &&
			   leadsTo == other.leadsTo;
	}
};


int findValve(std::vector<Valve> *valves, std::string name){
	for(int i = 0; i < valves->size(); i++){
		if(valves->at(i).name == name){
			return i;
		}
	}
	return -1;
}

// current valve is location in valves
// previous valves is all valves traveled too
// dont want to go to the same place twice (why not) (this approach will not work)
int findBestPath(std::vector<Valve> *valves, int currentCost, int currentPressure, 
		int currentValve, std::vector<int> previousValves){
	// something is wrong
	// 1665 < ans < 2074
	std::vector<int> nextMoves;
	for(int i = 0; i < valves->at(currentValve).leadsTo.size(); i++){ // loops through evverywhere i'm trying to go
		bool canMove = true;

		for(int j = 0; j < previousValves.size(); j++){// check if I have gone there before
			if(valves->at(currentValve).leadsTo.at(i) == valves->at(previousValves.at(j)).name){
				canMove = false;
			}
		}
		if(canMove){
			for(int j = 0; j < valves->size(); j++){
				if(valves->at(j).name == valves->at(currentValve).leadsTo.at(i))
					nextMoves.push_back(j);
			}
			
		}
	}
	if(nextMoves.size() == 0){
		return currentPressure;
	}
	// else call this algorithm on all future nodes
	
	previousValves.push_back(currentValve);
	// update cost and preassure
	currentCost --; // traveling cost
	if(valves->at(currentValve).flowRate > 0){
		currentCost --; // this is the opening cost
		int toAdd = valves->at(currentValve).flowRate * currentCost;
		if(toAdd > 0){
			currentPressure += toAdd;
		}
	}
	if(currentCost <= 0){
		return currentPressure;// if time is up
	}
	
	int maxPressure = currentPressure;
	for(int i = 0; i < nextMoves.size(); i++){
		int tempPress = findBestPath(valves, currentCost, currentPressure, nextMoves.at(i), previousValves);
		if(tempPress > maxPressure){
			maxPressure = tempPress;
		}
	}
	return maxPressure;
}



// ^^ this does not work for many reasons so i will try again

// valves points to the vector of valves
// valvesOpen is a vector of valves that have been opened
// currentValve is the valve that i am at
int part1(std::vector<Valve> *valves, int timeLeft, std::vector<Valve> valvesOpen, int currentPressure, int currentValve){
	// this can be a non recursive function!!!!
	
	// travel to a valve, open if nonzero and isnt already open

	// if am at a valve that isnt opened
	if(std::find(valvesOpen.begin(), valvesOpen.end(), valves->at(currentValve)) != valvesOpen.end()){
		// open valve
		valvesOpen.push_back(valves->at(currentValve));
		timeLeft--;
	}else{
		//find a valve to go to
		//this will probably be the closest valve i havent opened left
		//
		//bfs to nearest valve i can open
		//set the first valve on the list as the new current valve
		//subtract a minute


		//bfs
		std::queue<Valve> queue;
		bool* visited = new bool[valves->size()] ();
		int* parent = new int[valves->size()] ();

		visited[currentValve] = true;
		parent[currentValve] = currentValve;
		queue.push(valves->at(currentValve));

		Valve goal;

		while(queue.size() > 0){
			Valve v = queue.front();
			queue.pop();
			if(v.flowRate != 0 && !(std::find(valvesOpen.begin(), valvesOpen.end(), v) != valvesOpen.end())){
				// valve can be opened and therefore is the goal
				goal = v;
				break;
			}
			for(int i = 0; i < v.leadsTo.size(); i++){
				for(int j = 0; j < valves->size(); j++){
					if((valves->at(j) == valves->at(findValve(valves, v.leadsTo.at(i)))) && !visited[j]){
						queue.push(valves->at(j));
						visited[j] = true;
						parent[j] = findValve(valves, v.name);
					}
				}
			}
		}
		

		// needs to delete so it doesn't memory leak
		delete []visited;
		delete []parent;
	}	


	// updates pressure based on time open
	for(int i = 0; i < valvesOpen.size(); i++){
		currentPressure += valvesOpen.at(i).flowRate;
	}

	if(timeLeft == 0) return currentPressure;
	else return part1(valves, timeLeft, valvesOpen, currentPressure, currentValve);
}



int main(){
	std::ifstream infile("day16ex.txt");
	std::string temp;

	std::vector<Valve> valves(10);
	// Input
	while(std::getline(infile, temp)){
		Valve tempValve;
		tempValve.name = temp.substr(6, 2);
		tempValve.flowRate = std::stoi(temp.substr(temp.find("=") + 1, temp.find(";") - temp.find("=")));
		temp.erase(0, temp.find("to valve") + 8);
		temp.erase(0, temp.find(" ") + 1);
		
		while(temp.length() != 0){
			tempValve.leadsTo.push_back(temp.substr(0, 2));
			if(temp.length() == 2){
				temp.erase(0, temp.length());
			}
			temp.erase(0, temp.find(" ") + 1);
		}
		valves.push_back(tempValve);
	}
	// has all valves
	std::vector<int> tempValves;

	// find the location of the starting position
	int currentValve = 0;
	for(int i = 0; i < valves.size(); i++){
		if(valves.at(i).name == "AA"){
			currentValve = i;
		}
	}

	int pressure = findBestPath(&valves, 30, 0, currentValve, tempValves);

	std::cout << "The most pressure that can be released is: " << pressure << "\n";

	return 0;
}
