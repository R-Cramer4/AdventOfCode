#include <iostream>
using namespace std;

unsigned long long int comp(unsigned long long int a);
void check(unsigned long long int a);
int p[] = {2,4,1,3,7,5,1,5,0,3,4,1,5,5,3,0};
unsigned long long int mask = 7;
unsigned long long int A = 0;
unsigned long long int B = 0;
unsigned long long int C = 0;

int main(){

    // adv A =A/2^combo: 0, combo
    // bxl B = B ^ literal: 1, literal
    // bst B = combo % 8: 2, combo
    // jnz if A is not zero, jump to literal: 3, literal (dont increase ip)
    // bxc B = B ^ C : 4, combo(not read)
    // out outputs combo % 8 : 5, combo
    // bdv B =A/2^combo: 6, combo
    // cdv V =A/2^combo: 7, combo
    //

    unsigned long long int i = 0;
    unsigned long long int found = 0;
    // d294e6d = 7 * 4 = 28
    // 45 - 28 = 17
    // e6d
    while (i < (unsigned long long)1 << 32){
        found = comp((i << 16) + 0x4e6d);
        if(found != 0) break;
        i++;
        if(i == (unsigned long long)1 << 32) cout << "End" << endl;
    }
    /*
    unsigned long long int i = ((unsigned long long)1 << 16);
    // goes from 1 << 45
    // to 1 << 48
    // increment i << 17, then shift left 28
    // 0a94e(bf | 6d)
    // 20 + 8 = 28 bits known
    // 45 - 28 = 17
    unsigned long long int found = 0;
    while(i < ((unsigned long long)1 << 20)){
        found = comp(((i << 28) + 0x0a94ebf));
        if(found != 0) break;
        found = comp(((i << 28) + 0x0a94e6d));
        if(found != 0) break;
        i++;
    }
    */

    cout << endl << "Found at " << found << endl;
    check(found);
}
unsigned long long int comp(unsigned long long int a){
    unsigned long long temp = a;
    A = a;

    int i = 0;
    while(A != 0){
        B = A & mask;
        B = B ^ 3;
        C = A / (1 << B);
        B = B ^ 5;
        A = A >> 3;
        B = B ^ C;
        // out B % 8
        if(p[i] != (B & mask)){
            return false;
        }
        i++;
    }
    if(i < 16) return 0;
    return a;
}
void check(unsigned long long int a){
    A = a;

    while(A != 0){
        B = A & mask;
        B = B ^ 3;
        C = A / (1 << B);
        B = B ^ 5;
        A = A >> 3;
        B = B ^ C;
        // out B % 8
        cout << B % 8 << ",";
    }
    cout << endl;

}
