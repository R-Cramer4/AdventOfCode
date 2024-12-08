#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
using namespace std;

struct Node{
    char frequency;
    int x;
    int y;
    Node(char f, int x, int y){
        this->frequency = f;
        this->x = x;
        this->y = y;
    }
};

void printGraph(Node *a, Node *b, Node *c, Node *d, int maxX, int maxY);
int printGraph(vector<Node> nodes, int maxX, int maxY);

int main(){
    string temp;
    vector<Node> nodes;

    int maxX, maxY;
    int i = 0;
    while(getline(cin, temp)){
        int j;
        for(j = 0; j < temp.size(); j++){
            if(temp[j] != '.'){
                nodes.push_back({temp[j], j, i});
            }
        }
        maxX = j;
        i++;
    }
    maxY = i;
    cout << "Bounds = (" << maxX << ", " << maxY << ")" << endl;

    sort(nodes.begin(), nodes.end(), [](Node a, Node b){
        return a.frequency < b.frequency; });

    vector<Node> antinodes;
    for(int i = 0; i < nodes.size(); i++){
        for(int k = i + 1; k < nodes.size(); k++){
            if(nodes[i].frequency == nodes[k].frequency){
                bool dirx = 0;
                bool diry = 0;
                // find antinodes
                int distx = abs(nodes[i].x - nodes[k].x);
                int disty = abs(nodes[i].y - nodes[k].y);
                // needs to be in line
                if(nodes[i].x > nodes[k].x) dirx = 1;
                if(nodes[i].y > nodes[k].y) diry = 1;

                int x = nodes[i].x;
                int y = nodes[i].y;
                while(x >= 0 && y >= 0 && x < maxX && y < maxY){
                    // not going in the correct direction
                    antinodes.push_back({nodes[i].frequency, x, y});
                    x -= dirx ? -distx : distx;
                    y -= diry ? -disty : disty;
                }
                x = nodes[i].x;
                y = nodes[i].y;
                while(x >= 0 && y >= 0 && x < maxX && y < maxY){
                    antinodes.push_back({nodes[i].frequency, x, y});
                    x += dirx ? -distx : distx;
                    y += diry ? -disty : disty;
                }
                /*

                int x1 = 0, x2 = 0, y1 = 0, y2 = 0; // there is two antinodes
                if(nodes[i].x - distx == nodes[k].x) x1 = nodes[k].x - distx;
                else if(nodes[i].x + distx == nodes[k].x) x1 = nodes[k].x + distx;
                if(nodes[i].y - disty == nodes[k].y) y1 = nodes[k].y - disty;
                else if(nodes[i].y + disty == nodes[k].y) y1 = nodes[k].y + disty;

                if(nodes[k].x - distx == nodes[i].x) x2 = nodes[i].x - distx;
                else if(nodes[k].x + distx == nodes[i].x) x2 = nodes[i].x + distx;
                if(nodes[k].y - disty == nodes[i].y) y2 = nodes[i].y - disty;
                else if(nodes[k].y + disty == nodes[i].y) y2 = nodes[i].y + disty;

                // bounds check
                Node *a = &nodes[i], *b = &nodes[k], *c = nullptr, *d = nullptr;
                if(x1 >= 0 && x1 < maxX && y1 >= 0 && y1 < maxY){
                    //cout << nodes[i].frequency << ": (" << nodes[i].x << ", " << nodes[i].y << ")\t";
                    //cout << nodes[k].frequency << ": (" << nodes[k].x << ", " << nodes[k].y << ")\t\t";
                    //cout << nodes[i].frequency << ": (" << x1 << ", " << y1 << ")" << endl;
                    antinodes.push_back({nodes[i].frequency, x1, y1});
                    c = &antinodes.back();
                }
                if(x2 >= 0 && x2 < maxX && y2 >= 0 && y2 < maxY){
                    //cout << nodes[i].frequency << ": (" << nodes[i].x << ", " << nodes[i].y << ")\t";
                    //cout << nodes[k].frequency << ": (" << nodes[k].x << ", " << nodes[k].y << ")\t\t";
                    //cout << nodes[i].frequency << ": (" << x2 << ", " << y2 << ")" << endl;
                    antinodes.push_back({nodes[i].frequency, x2, y2});
                    d = &antinodes.back();
                }
                //printGraph(a, b, c, d, maxX, maxY);
                //this_thread::sleep_for(chrono::milliseconds(1000));
                */
            }else break;
        }
    }

    sort(antinodes.begin(), antinodes.end(), [](Node a, Node b){
            if(a.x == b.x) return a.y < b.y;
            return a.x < b.x;
        });
    int numDup = 0;
    for(int i = 0; i < antinodes.size() - 1; i++){
        if(antinodes[i].x == antinodes[i + 1].x && antinodes[i].y == antinodes[i + 1].y){
            numDup++;
        }
    }
    printGraph(antinodes, maxX, maxY);
    cout << "Number of antinoeds = " << antinodes.size() - numDup << endl;
}

void printGraph(Node *a, Node *b, Node *c, Node *d, int maxX, int maxY){
    system("clear");
    cout << a->frequency << ": (" << a->x << ", " << a->y << ")\t";
    cout << b->frequency << ": (" << b->x << ", " << b->y << ")\t";
    if(c != nullptr) cout << c->frequency << ": (" << c->x << ", " << c->y << ")\t";
    if(d != nullptr) cout << d->frequency << ": (" << d->x << ", " << d->y << ")\t";
    cout << endl;
    for(int i = 0; i < maxY; i++){
        for(int j = 0; j < maxX; j++){
            if(i == a->y && j == a->x) cout << a->frequency;
            else if(i == b->y && j == b->x) cout << b->frequency;
            else if(c != nullptr && i == c->y && j == c->x) cout << c->frequency;
            else if(d != nullptr && i == d->y && j == d->x) cout << d->frequency;
            else cout << '.';
        }
        cout << endl;
    }

}
int printGraph(vector<Node> nodes, int maxX, int maxY){
    int num = 0;
    for(int i = 0; i < maxY; i++){
        for(int j = 0; j < maxX; j++){
            for(int k = 0; k < nodes.size(); k++){
                if(nodes[k].y == i && nodes[k].x == j){
                    cout << nodes[k].frequency;
                    num++;
                    break;
                }
                if(k == nodes.size() - 1) cout << '.';
            }
        }
        cout << endl;
    }

    return num;
}
