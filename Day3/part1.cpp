#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream input("input.txt");

    vector<string> map;
    string line;
    while (getline(input, line)) map.push_back(line);
    int sum = 0;
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            bool isAdjacentNum = 0;
            int num = 0;
            while (j != map[i].size() && isdigit(map[i][j])) {
                for (int k = -1; k < 2; ++k) {
                    for (int l = -1; l < 2; ++l) {
                        if (i + k >= 0 && i + k <= map.size() - 1 && j + l >= 0 && j + l <= map[i].size() - 1 &&
                            map[i + k][j + l] != '.' && !isdigit(map[i + k][j + l])) {
                            isAdjacentNum = 1;
                        }
                    }
                }
                num *= 10;
                num += map[i][j] - '0';
                ++j;
            }
            if (isAdjacentNum) {
                sum += num;
            }
        }
    }

    cout << sum;
}