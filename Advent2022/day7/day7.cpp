#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct dir{
	int size;
	std::string name;
	struct dir* inDir;
	std::vector<dir> dirs;
	std::vector<int> fileSizes;
};

int * getSize(int sizes[], struct dir * direct){
	int sizeOfDir = 0; // just this folder
	int smallSize = 0; // all sizes combined that are smaller than 100,000
	
	// returns int[] = [smallSize, size]

	// calculate total size of each dir
	// if the size is less than 100,000
	// add that to the smallSize
	//
	// size is equal to all files
	// plus all dirs in the folder
	
	// add up all sizes of the files
	for(int i = 0; i < int(direct->fileSizes.size()); i++){
		sizeOfDir += direct->fileSizes.at(i);
	}
	// now need to also add all sizes of each dir in this folder
	for(int i = 0; i < int(direct->dirs.size()); i++){
		int *newSizes = getSize(sizes, &direct->dirs.at(i));
		sizeOfDir += newSizes[1];
	}
	// sizeOfDir has the size of this dir
	// check if its smaller than 100,000
	if(sizeOfDir <= 100000){
		smallSize += sizeOfDir;
	}

	sizes[0] += smallSize;
	sizes[1] = sizeOfDir; // the last return is the dir / which has total size as its size
	
	direct->size = sizeOfDir;

	return sizes;
}

int findSize(int size, int * minSize, struct dir *direct){
	// recursivly look for the size
	if(direct->size > size && direct->size < *minSize){
		*minSize = direct->size;
	}
	for(int i = 0; i < int(direct->dirs.size()); i++){
		int temp = findSize(size, minSize, &direct->dirs.at(i));
		if(temp > size && temp < *minSize){
			*minSize = temp;
		}
	}
	return *minSize;
}

int main(){
	std::ifstream infile("day7.txt");
	std::string command;

	struct dir first;
	first.name = "/";

	struct dir* workingDir;
	workingDir = &first;
	first.inDir = workingDir;

	//always points to first
	struct dir* firstPtr;
	firstPtr = &first;

	while(std::getline(infile, command)){
		if(command[0] == '$'){
			// command
			if(!command.substr(0, 4).compare("$ cd")){
				// it is a cd command
				if(!command.substr(0, 7).compare("$ cd ..")){
					// Go backwards
					workingDir = workingDir->inDir;
					continue;
				}
				// cd command
				// look in workingdir for the next dir
				command.erase(0, 5);
				for(int i = 0; i < int(workingDir->dirs.size()); i++){
					if(workingDir->dirs.at(i).name == command){
						workingDir = &workingDir->dirs.at(i);
					}
				}
			}else{
				// ls command
				continue;
			}
		}else{
			// result of ls
			if(!command.substr(0, 4).compare("dir ")){
				// Is a dir
				struct dir newDir;
				newDir.inDir = workingDir;
				newDir.name = command.substr(command.find("dir ") + 4, command.length() - 4);
				// pointing to null dir
				workingDir->dirs.push_back(newDir);
			}else{
				// is a file
				int size = std::stoi(command.substr(0, command.find(" ")));
				workingDir->fileSizes.push_back(size);
			}
		}
	}
	int sizes[] = {0, 0};
	int* ptr;
	ptr = getSize(sizes, firstPtr);
	// ptr[0] has pt1
	// ptr[1] has total size
	// now each dir has its size

	int totalSize = 70000000;
	int neededUnusedSpace = 30000000;
	int extraSpaceNeeded = neededUnusedSpace - (totalSize - ptr[1]);

	std::cout << "total size of sizes less than 100,000: " << ptr[0] <<"\n";
	std::cout << "Dir that can be deleted with the smallest space is: " << 
		findSize(extraSpaceNeeded, &firstPtr->size, firstPtr) << "\n";

	return 0;
}
