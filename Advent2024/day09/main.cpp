#include <iostream>
#include <string>
using namespace std;

void printDisk(int *disk, int size);

int main(){
    string temp;
    getline(cin, temp); // one line that is very long

    int diskSize = 0;
    for(int i = 0; i < temp.size(); i++){
        diskSize += temp[i] - '0';
    }
    cout << "Disk size needed = " << diskSize << endl;

    int disk[diskSize];
    bool file = false; // file is true, free space is false
    int k = 0;
    int id = -1;
    for(int i = 0; i < temp.size(); i++){
        file = !file;
        id += file;
        int curSize = temp[i] - '0';
        for(int j = 0; j < curSize; j++){
            if(file) disk[k + j] = id;
            else disk[k + j] = -1;
        }
        k += curSize;
    }
    /*
    //part 1
    int left = 0;
    int right = diskSize - 1;
    while(left < right){
        if(disk[right] == -1){
            right --;
            continue;
        }
        if(disk[left] != -1){
            left ++;
            continue;
        }
        disk[left] = disk[right];
        disk[right] = -1;
        right --;
        left ++;
    }
    */
    
    // part 2
    // id holds max id
    while(id >= 0){
        //cout << "Id: " << id << endl;
        //printDisk(disk, diskSize);
        int idLoc = -1;
        for(int i = diskSize - 1; i >= 0; i--){
            if(disk[i] == id){
                idLoc = i;
                break;
            }
        }
        if(idLoc == -1){
            cout << "couldnt find id" << endl;
            break;
        }
        int idSize = 0;
        for(int i = idLoc; i >= 0; i--){
            if(disk[i] == id) idSize++;
            else break;
        }
        int emptyStart = -1;
        int emptySize = 0;
        for(int i = 0; i < diskSize; i++){
            if(disk[i] == -1){
                if(emptyStart == -1) emptyStart = i;
                emptySize++;
            }else{
                emptyStart = -1;
                emptySize = 0;
                continue;
            }
            if(emptyStart >= idLoc) break;
            if(emptyStart != -1 && emptySize >= idSize){
                //cout << "ID: (" << idLoc << ", " << idSize << ")" << endl;
                //cout << "Empty: (" << emptyStart << ", " << emptySize << ")" << endl;
                // move id into the empty space
                for(int k = 0; k < idSize; k++){
                    disk[emptyStart + k] = disk[idLoc - k];
                    disk[idLoc - k] = -1;
                }
                break;
            }
        }
        id--;
    }


    long long unsigned int checkSum = 0;
    for(int i = 0; i < diskSize; i++){
        if(disk[i] == -1) continue;
        checkSum += i * disk[i];
    }
    cout << "Checksum = " << checkSum << endl;

}

void printDisk(int *disk, int size){
    for(int i = 0; i < size; i++){
        if(disk[i] == -1) cout << '.';
        else cout << disk[i];
    }
    cout << endl;
}
