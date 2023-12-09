#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <unordered_map>

using namespace std;

int main() {
    ifstream input("input.txt");

    string line;
    int sum = 0;
    while (getline(input, line)) {
        line.erase(0, line.find(':') + 2);
        while (line.find("  ") != string::npos) line.replace(line.find("  "), 2, " ");
        unordered_map<int, int> nums;
        string elfNums = line.substr(0, line.find('|') - 1), winningNums = line.substr(line.find('|') + 2, line.size());
        while (!elfNums.empty()) {
            nums[stoi(elfNums)] = 1;
            elfNums.erase(0, elfNums.find(' ') == string::npos ? elfNums.size() : elfNums.find(' ') + 1);
        }
        int counter = 0;
        while (!winningNums.empty()) {
            int x = stoi(winningNums);
            winningNums.erase(0, winningNums.find(' ') == string::npos ? winningNums.size() : winningNums.find(' ') + 1);
            if (nums[x] != 0) ++counter;
        }
        if (counter != 0) sum += pow(2, counter - 1);
    }

    cout << sum;
}