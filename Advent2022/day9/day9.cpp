#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int moveTail(int * tailLoc, int * headLoc, std::vector<std::vector<int> > * spacesVisated){
	// moves tail in reference to where the head is
	
	// check if tail and head are the same
	if(tailLoc[0] == headLoc[0] && tailLoc[1] == headLoc[1]){
		// tail and head are the same
	}else if(tailLoc[1] == headLoc[1]){
		// tail and head are in the same y (same row)
		// check if head is at least 2 spaces to the right
		if((headLoc[0] - tailLoc[0]) >= 2){
			// head is at least 2 greater than tail
			tailLoc[0] ++;
			// move tail towards the head
		}else if((tailLoc[0] - headLoc[0]) >= 2){
			// head is at least 2 less than tail
			tailLoc[0] --;
			// move tail towards the head
		}
	}else if(tailLoc[0] == headLoc[0]){
		// tail and head are in the same x (same col)
		// same logic as before but in vertical direction
		if((headLoc[1] - tailLoc[1]) >= 2){
			// head is at leas 2 spaces higher than tail
			tailLoc[1] ++;
			// move tail closer
		}else if((tailLoc[1] - headLoc[1]) >= 2){
			// head is at least 2 spaces lower than tail
			tailLoc[1] --;
			// move tail closer
		}
	}else{
		// they are diaganolly separated
		// check if up and right
		if(headLoc[1] > tailLoc[1] && headLoc[0] > tailLoc[0]){
			// head is up and right
			// need to check if it is more than 2 spaces ahead
			if(!(headLoc[1] == tailLoc[1] + 1 && headLoc[0] == tailLoc[0] + 1)){
				// if tail isnt going to land right ontop of head
				tailLoc[0] ++;
				tailLoc[1] ++;
				// move tail
			}
		}
		// check if up and left
		else if(headLoc[1] > tailLoc[1] && headLoc[0] < tailLoc[0]){
			// head is up and left
			// check if it is at least 2 spaces ahead
			if(!(headLoc[1] == tailLoc[1] + 1 && headLoc[0] == tailLoc[0] - 1)){
				// tail wont land on head
				tailLoc[0] --; // move left
				tailLoc[1] ++; //move up
			}
		}
		// check if down and right
		else if(headLoc[1] < tailLoc[1] && headLoc[0] > tailLoc[0]){
			// head is down and right
			// check if tail will land on head
			if(!(headLoc[1] == tailLoc[1] - 1 && headLoc[0] == tailLoc[0] + 1)){
				// tail wont land on head
				tailLoc[0] ++; // move right
				tailLoc[1] --; // move down
			}
		}
		// check if down and left
		else if(headLoc[1] < tailLoc[1] && headLoc[0] < tailLoc[0]){
			// head is down and left
			// check if tail will land on head
			if(!(headLoc[1] == tailLoc[1] - 1 && headLoc[0] == tailLoc[0] - 1)){
				// tail wont land on head
				tailLoc[0] --; // move left
				tailLoc[1] --; // move down
			}
		}
	}

	// after all logic
	// checking if tail has been there
	bool hasVisated = false;
	for(int i = 0; i < int(spacesVisated->size()); i++){
		if(spacesVisated->at(i).at(0) == tailLoc[0] && spacesVisated->at(i).at(1) == tailLoc[1]){
			hasVisated = true;
		}
	}
	// if tail hasnt been there i add it to spacesVisated
	if(!hasVisated){
		std::vector<int> temp;
		temp.push_back(tailLoc[0]);
		temp.push_back(tailLoc[1]);
		spacesVisated->push_back(temp);
	}
	return 0;
}


int main(){
	std::fstream infile("day9.txt");
	std::string temp;

	// make a 2d array rope
	// each loc is one knot and has a position
	
	int rope[10][2] = {
		{0, 0}, // Head
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0}// loc 9 (tail)
	};

	int travelDist = 0;
	char direction;
	// need a vector because the tail could go to the same place twice
	std::vector<std::vector<int> > spacesVisated;
	std::vector<std::vector<int> > otherSpaces; // for other knots
	

	while(std::getline(infile, temp)){
		direction = temp[0];
		travelDist = std::stoi(temp.substr(2, temp.length() - 2));
		for(int i = 0; i < travelDist; i++){
			if(direction == 'U'){
				// head moves up
				rope[0][1] ++;
			}
			else if(direction == 'D'){
				// head moves down
				rope[0][1] --;
			}
			else if(direction == 'R'){
				// head moves right
				rope[0][0] ++;
			}
			else if (direction == 'L'){
				// head moves left
				rope[0][0] --;
			}
			// head has moved one space
			// now makes the rest follow
			// loop through each location of the rope starting at the head
			for(int i = 1; i < 9; i++){
				moveTail(rope[i], rope[i - 1], &otherSpaces);
			}
			// optimize
			otherSpaces.clear();

			// at the end do last knot so i can get space
			moveTail(rope[9], rope[8], &spacesVisated);
		}
	}

	std::cout << "Number of spaces the tail has visited: " << spacesVisated.size() << "\n";

	return 0;
}
