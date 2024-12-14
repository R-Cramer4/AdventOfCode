#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <vector>
using namespace std;

#define WIDTH 101
#define HEIGHT 103
#define SECONDS 100

struct Robot{
    pair<int, int> pos;
    pair<int, int> v;
    void print(){
        cout << "p=" << pos.first << "," << pos.second << " v=" << v.first << "," << v.second << endl;
    }
    void move();
};
vector<Robot> robots;
void printRobots();
double calculateVariance();

int main(){
    string temp;

    while(getline(cin, temp)){
        Robot r;
        r.pos = {stoi(temp.substr(2, temp.find(',') - 2)), 
            stoi(temp.substr(temp.find(',') + 1, temp.find(' ') - temp.find(',') + 1))};

        temp = temp.substr(temp.find(' ') + 1);
        r.v= {stoi(temp.substr(2, temp.find(',') - 2)), 
            stoi(temp.substr(temp.find(',') + 1, temp.find(' ') - temp.find(',') + 1))};

        robots.push_back(r);
    }


    int q1=0, q2=0, q3=0, q4=0;
    for(int i = 0; i < 100000; i++){
        for(int k = 0; k < robots.size(); k++) {
            robots[k].move();
        }
        sort(robots.begin(), robots.end(), [](Robot a, Robot b){
                if(a.pos.second == b.pos.second) return a.pos.first < b.pos.first;
                return a.pos.second < b.pos.second;
                });
        int num = 0;
        for(int k = 0; k < robots.size() - 1; k++){
            if(robots[k].pos.second == robots[k + 1].pos.second && abs(robots[k].pos.first - robots[k+ 1].pos.first) == 1) num++;
            else num = 0;
            if(num > 5){
                printRobots();
                cout << i << endl;
                this_thread::sleep_for(chrono::milliseconds(2000));
            }
        }
    }
    for(int i = 0; i < robots.size(); i++) {
        if(robots[i].pos.first < WIDTH / 2){ // q1 or q3
            if(robots[i].pos.second < HEIGHT / 2) q1++;
            else if(robots[i].pos.second > HEIGHT / 2) q3++;
        }else if(robots[i].pos.first > WIDTH / 2){
            if(robots[i].pos.second < HEIGHT / 2) q2++;
            else if(robots[i].pos.second > HEIGHT / 2) q4++;
        }
    }
    cout << "Q1 has " << q1 << " robots" << endl;
    cout << "Q2 has " << q2 << " robots" << endl;
    cout << "Q3 has " << q3 << " robots" << endl;
    cout << "Q4 has " << q4 << " robots" << endl;
    cout << "Saftey Factor = " << q1 * q2 * q3 * q4 << endl;
}
void Robot::move(){
    int f = (pos.first + v.first);
    int s = (pos.second + v.second);
    if(f < 0){
        f += WIDTH * ((-1 * f / WIDTH) + 1);
    }
    f = f % WIDTH;
    if(s < 0){
        s += HEIGHT * ((-1 * s / HEIGHT) + 1);
    }
    s = s % HEIGHT;
    pos.first = f;
    pos.second = s;

}
void printRobots(){
    system("clear");
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            bool f = false;
            for(int k = 0; k < robots.size(); k++){
                if(robots[k].pos.first == j && robots[k].pos.second == i){
                    cout << '#';
                    f = true;
                    break;
                }
            }
            if(!f) cout << '.';
        }
        cout << '\n';
    }
    cout << flush;
}
