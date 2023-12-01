#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

int main(int argc, char *argv[]){
    int ans = 0;
    std::string numbers[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    std::string temp;
    int i = 0;
    while(std::cin >> temp){
        int beg = -1;
        int end = -1;
        for(int j = 0; j < temp.size(); j++){
            // this checks for digits
            if(beg == -1){
                beg = temp[j] - 48;
                if(beg > 9 || beg < 0) beg = -1;
            }
            if(end == -1){
                end = temp[temp.size() - 1 - j] - 48;
                if(end > 9 || end < 0) end = -1;
            }
            // this will check for words
            for(int k = 0; k < 10; k++){
                int test = 0;
                try {
                    if(beg == -1 && j + numbers[k].size() < temp.size() &&
                            temp.substr(j, numbers[k].size()) == numbers[k]){
                        beg = k;
                    }
                    test = 1;
                    if(end == -1 && temp.size() - j > numbers[k].size()){
                        if(temp.substr(temp.size() - j - numbers[k].size(), numbers[k].size()) == numbers[k]){
                            end = k;
                        }
                    }
                } catch (const std::exception &exc) {
                    std::cout << exc.what() << "\n";
                    std::cout << "temp = " << temp << "\nk = " 
                        << k << "\nj = " << j << "\ni = " << i << std::endl;
                    std::cout << "test = " << test << "\n";
                    return 1;
                }
            }
        }
        ans += (beg * 10) + end;
        i++;
    }
    std::cout << "Answer = " << ans << "\n";
    // 54574 is too high

    return 0;
}
