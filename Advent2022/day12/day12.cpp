#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <map>
	
int bfs(std::vector<std::vector<std::pair<bool, char> > > heightMap, int startPos[], int finalPos[]){
	std::queue<std::pair<int, int> > q;	
	q.push({startPos[0], startPos[1]});

	int moves = 0;
	int rows = heightMap.size();
	int cols = heightMap[0].size();

	std::vector<std::vector<int> > offsets = {{0,1},{1,0},{0,-1},{-1,0}};

	// mark first pos as visited
	heightMap[startPos[0]][startPos[1]].first = true;

	while(!q.empty()){
		int l = q.size();
		// visit every adjacent node for the nodes in queue
		for(int k = 0; k < l; k++){
			auto [i, j] = q.front();
			q.pop();
			// try all 4 directions
			for(int l = 0; l < 4; l++){
				int x = i + offsets[l][0];
				int y = j + offsets[l][1];
				// check for invalid moves
				// if(heightMap[x][y] - 1 > heightMap[i][j]) means that it is too hight to move too
				if(x < 0 || y < 0 || x >= rows || y >= cols || heightMap[x][y].first
						|| heightMap[x][y].second - 1 > heightMap[i][j].second){
					continue;
				}
				// check if we have reached the final loc
				if(x == finalPos[0] && y == finalPos[1])
					return moves + 1;
				// mark space as visited
				heightMap[x][y].first = true;
				q.push({x, y});
			}
		}
		moves++;
	}


	return -1;
}

int main(){
	std::ifstream infile("day12.txt");
	std::string temp;

	std::vector<std::vector<std::pair<bool, char> > > heightMap;

	int currentPos[] = {0, 0};
	int finalPos[] = {0, 0};

	int steps = 0;

	int i = 0;
	while(std::getline(infile, temp)){
		if(temp.find("S") != -1){
			currentPos[0] = i;
			currentPos[1] = temp.find("S");
			temp.replace(temp.find("S"), 1, "a");
		}
		if(temp.find("E") != -1){
			finalPos[0] = i;
			finalPos[1] = temp.find("E");
			temp.replace(temp.find("E"), 1, "{");// 1 above z
		}
		std::vector<std::pair<bool, char> > tempVec;
		heightMap.push_back(tempVec);
		for(int j = 0; j < temp.length(); j++){
			heightMap[i].push_back({false, temp[j]});
		}
		
		i++;
	}
	steps = bfs(heightMap, currentPos, finalPos);
	std::cout << "Steps taken = " << steps << "\n";

	// look from every position with height a
	int minSteps = 1000000;
	// loop through every position
	for(int i = 0; i < heightMap.size(); i++){
		for(int j = 0; j < heightMap[i].size(); j++){
			if(heightMap[i][j].second == 'a'){
				int pos[] = {i, j};
				int step = bfs(heightMap, pos, finalPos);
				if(step < minSteps && step >= 0)
					minSteps = step;
			}
		}
	}
	std::cout << "Fewest steps = " << minSteps << "\n";


	return 0;
}
