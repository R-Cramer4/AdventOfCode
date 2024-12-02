#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int * isVisable(std::vector<std::vector<int> > trees, int row, int col){
	int senicScore = 0;
	int height = trees.at(row).at(col);
	bool isVis = false;
	static int arr[2];
	arr[0] = 1;
	arr[1] = senicScore;

	// if the tree is on the top or bottom
	if(row == 0 || row == trees.size() - 1){
		return arr;
	}
	// if tree is on either side
	if(col == 0 || col == trees.at(0).size() - 1)
		return arr;

	// tree is in the middle
	// check looking from the left
	bool visLeft = true;
	for(int i = col - 1; i >= 0; i--){
		if(trees.at(row).at(i) >= height){
			visLeft = false;
			senicScore += col - i;
			break;
		}
	}
	if(visLeft){
		isVis = true;
		senicScore += col;
	}

	// check looking from the right
	bool visRight = true;
	for(int i = col + 1; i < trees.at(row).size(); i++){
		if(trees.at(row).at(i) >= height){
			visRight = false;
			senicScore *= i - col;
			break;
		}
	}
	if(visRight){
		isVis = true;
		senicScore *= trees.at(row).size() - col - 1;
	}

	//check looking from top
	bool visTop = true;
	for(int i = row - 1; i >= 0; i--){
		if(trees.at(i).at(col) >= height){
			visTop = false;
			senicScore *= row - i;
			break;
		}
	}
	if(visTop){
		isVis = true;
		senicScore *= row;
	}
	
	// check looking from bottom
	bool visBottom = true;
	for(int i = row + 1; i < trees.size(); i++){
		if(trees.at(i).at(col) >= height){
			visBottom = false;
			senicScore *= i - row;
			break;
		}
	}
	if(visBottom){
		isVis = true;
		senicScore *= trees.size() - row - 1;
	}


	if(isVis){
		arr[0] = 1;
	}else{
		arr[0] = 0;
	}
	arr[1] = senicScore;

	return arr;
}


int main(){
	std::ifstream infile("day8.txt");
	std::string temp;
	std::vector<std::vector<int> > trees;

	while(std::getline(infile, temp)){
		std::vector<int> tempLine;
		for(int i = 0; i < temp.length(); i++){
			tempLine.push_back(int(temp[i]) - 48);
		}
		trees.push_back(tempLine);
	}
	// all heights of trees are in trees
	int visableTrees = 0;
	int maxSenicScore = 0;
	for(int i = 0; i < trees.size(); i++){
		for(int j = 0; j < trees.at(i).size(); j++){
			int * arr;
			arr = isVisable(trees, i, j);
			visableTrees += arr[0];
			if(arr[1] > maxSenicScore)
				maxSenicScore = arr[1];
		}
	}

	std::cout << "Number of trees that are visable outside the grid is: " << visableTrees << "\n";
	std::cout << "Max senic score is: " << maxSenicScore << "\n";


	return 0;
}
