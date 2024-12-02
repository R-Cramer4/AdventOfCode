#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <future>

std::mutex mtx;

void fillSpace(std::vector<long long int> * beaconless, 
		std::pair<int, int> sensor, int distance, int loc, int num){
	bool hasComplete = false;
	long long int x = 0;
	long long int y = distance;
	int q = 1;
	while(!hasComplete){
		// looking at y = 2,000,000
		if(sensor.second + y == loc){
			for(int i = sensor.first - x; i <= sensor.first + x; i++){
				// all x coordinates
				// just add x and no y
				mtx.lock();
				beaconless->push_back(i);
				mtx.unlock();
			}
		}
		// incrementation
		switch(q){
			case 1:
				x++;
				y--;
				break;
			case 2:
				x--;
				y--;
				break;
		}
		if(y == 0 || x == 0){
			q ++;
			if(q == 3){
				hasComplete = true;
			}
		}
	}
}

void eraseDuplicates(std::vector<int> * beaconSplit){
	mtx.lock();	
	for(int i = beaconSplit->size() - 1; i > 0; i--){
		if(beaconSplit->at(i) == beaconSplit->at(i - 1)){
			beaconSplit->erase(beaconSplit->begin() + i);
		}
	}
	mtx.unlock();
}

int noBeacons(std::vector<std::pair<int, int> > sensors, 
		std::vector<std::pair<int, int> > beacons, 
		std::vector<int> distances,
		long long int loc){
	// loop through each sensor beacon pair
	// at each sensor create a circle around it with radius in distances
	// the circle has all locations the beacon cant be in
	// not including the actual beacon
	std::vector<long long int> beaconless;
	std::vector<std::thread> threads;

	for(int i = 0; i < sensors.size(); i++){
		std::pair<int, int> sensor = sensors.at(i);
		int distance = distances.at(i);
		threads.emplace_back(std::thread(fillSpace, &beaconless, sensor, distance, loc, i));
	}	

	for(auto &th : threads){
		th.join();
	}

	std::cout << "All threads have finished\n";
	// beaconless can have duplicates
	// first sort
	sort(beaconless.begin(), beaconless.end());
	// then remove duplicates
	std::cout << "\n";
	// this vector is too large
	// split into 10 smaller vectors
	// multithread
	int numThreads = 20;
	int split = beaconless.size() / numThreads;
	int extra = beaconless.size() % numThreads;
	std::vector<int> extraLocs(beaconless.end() - extra - 1, beaconless.end());
	std::vector<std::vector<int> > beaconSplit;
	std::vector<std::thread> newThreads;

	for(int i = 0; i < numThreads; i++){
		std::vector<int> temp(beaconless.begin() + (split * i), beaconless.begin() + (split * i) + split);
		beaconSplit.push_back(temp);
	}
	for(int i = 0; i < numThreads; i++){
		newThreads.emplace_back(std::thread(eraseDuplicates, &beaconSplit.at(i)));
	}
	newThreads.emplace_back(std::thread(eraseDuplicates, &extraLocs));

	for(auto &th : newThreads){
		th.join();
	}
	std::cout << "Erased duplicates\n";

	// need to check for duplicates inbetween each array
	for(int i = beaconSplit.size() - 1; i > 0; i--){
		if(beaconSplit.at(i).front() == beaconSplit.at(i - 1).back()){
			beaconSplit.at(i).erase(beaconSplit.at(i).begin());
		}
	}
	if(beaconSplit.back().back() == extraLocs.front()){
		extraLocs.erase(extraLocs.begin());
	}

	int num = 0;
	for(int i = 0; i < beaconSplit.size(); i++){
		num += beaconSplit.at(i).size();
	}
	num += extraLocs.size();
	// there is duplicates in beacons
	sort(beacons.begin(), beacons.end());
	for(int i = beacons.size() - 1; i > 0; i--){
		if(beacons.at(i) == beacons.at(i - 1)){
			beacons.erase(beacons.begin() + i);
		}
	}
	std::cout << "Erased beacon duplicates\n";

	for(int i = 0; i < beacons.size(); i++){
		if(beacons.at(i).second == loc){
			num --;
		}
	}
	return num;
}

int banishFromCircle(int x, int y, std::pair<int, int> sensor, int distance){
	// called for every circle
	
	// first check if inside this circle
	int manDistance = abs(int(x - sensor.first)) + abs(int(y - sensor.second));
	if(manDistance <= distance){
		// inside circle and now need to move to edge
		// manhattan distance = x + y

		// this is finding a location thats moving me backwards
		int newX = abs(distance - (abs(sensor.second - y))) + sensor.first;
		
		return newX;
	}

	return -1;
}

long long int part2(std::vector<std::pair<int, int> > sensors, std::vector<int> distances, int size){

	// instead of going through every single coordinates
	// all coordinates = 4,000,000 * 4,000,000 = 16,000,000,000,000 = 16 quadrilion
	// each location = 16 bytes
	// 256 quadrilion bytes = 244 terrabytes
	// HUGE
	
	// i know where the location can't be

	// TODO 
	// this seems a lot easier
	// or i can just search through everything
	// but when i hit an edge i skip to the other edge
	// 
	// TODO dont need to generate circles
	// i have distances and radius so i can just calculate where the point should go
	// and move there
	
	
	for(long long int y = 0; y <= size; y++){
		for(long long int x = 0; x <= size; x++){
			bool inCirc = false;
			for(int i = 0; i < sensors.size(); i++){

				//check if im inside circle
				// each point in one of the circles goes clockwise starting from the top
				// if i am in a circle, the distance from the center is less than the radius
				// Manhattan distance = radius
				// distances holds radiuss
				// sensors holds center
				
				// check if manhattan distance is less than the radius
				int newX = banishFromCircle(x, y, sensors.at(i), distances.at(i));
				if(newX != -1){
					x = newX;
					inCirc = true;
					break;
				}
			}
			printf("\r%lld, %lld   ", x, y);
			if(!inCirc){
				return (x * 4000000) + y;
			}
			// if i get here im not in a circle
			// check if its empty space
			// if it is return and exit
			// check if in circle
			// if so jump to end of the circle
			
		}
	}

	return -1;
}

int main(){
	std::fstream infile("day15.txt");
	std::string temp;
	std::vector<std::pair<int, int> > sensors;
	std::vector<std::pair<int, int> > beacons;
	std::vector<int> distances; // distance = |x2 - x1| + |y2 - y1|

	while(std::getline(infile, temp)){
		sensors.push_back({
				std::stoi(temp.substr(temp.find("x=") + 2, temp.find(",") - temp.find("x=") - 2)),
				std::stoi(temp.substr(temp.find("y=") + 2, temp.find(":") - temp.find("y=") - 2))
				});
		temp.erase(0, temp.find(": ") + 2);
		beacons.push_back({
				std::stoi(temp.substr(temp.find("=") + 1, temp.find(",") - temp.find("=") - 1)),
				std::stoi(temp.substr(temp.find("y=") + 2))
				});
		distances.push_back(abs(sensors.back().first - beacons.back().first) + 
			abs(sensors.back().second - beacons.back().second));
	}
	// input done
	// each location has matching sensor and beacon
	// distances has the distance from sensor to beacon
	printf("Calling no beacons\n");
	//int numBeacons = noBeacons(sensors, beacons, distances, 2000000);
	long long int tuningFreq = part2(sensors, distances, 4000000);
	std::cout << "The tuning frequency is: " << tuningFreq << "\n";
	//std::cout << "At row 2,000,000: " << numBeacons 
	//	<< " positions can't have a beacon\n";

	// 5,395,360 is too high
	// 4717642 too high
	return 0;
}
