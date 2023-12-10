#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

struct gear {
    int partNumbersCount = 0;

    long long gearRatio = 1;
};

int main() {
    ifstream input("input.txt");

    vector<string> map;
    string line;
    while (getline(input, line)) map.push_back(line);
    long long sum = 0;
    unordered_map<string, gear> gears;

    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            bool isAdjacentNum = 0;
            int num = 0;
            string key;
            while (j != map[i].size() && isdigit(map[i][j])) {
                for (int k = -1; k < 2 && !isAdjacentNum; ++k) {
                    for (int l = -1; l < 2; ++l) {
                        if (i + k >= 0 && i + k <= map.size() - 1 && j + l >= 0 && j + l <= map[i].size() - 1 &&
                            map[i + k][j + l] != '.' && !isdigit(map[i + k][j + l])) {
                            if (map[i + k][j + l] == '*') {
                                key = to_string(i + k) + ' ' + to_string(j + l);
                                gears[key].partNumbersCount += 1;
                            }
                            isAdjacentNum = 1;
                        }
                    }
                }
                num *= 10;
                num += map[i][j] - '0';
                ++j;
            }
            if (isAdjacentNum) {
                gears[key].gearRatio *= num;
            }
        }
    }

    for (pair<string, gear> i : gears) {
        if (i.second.partNumbersCount == 2) sum += i.second.gearRatio;
    }
    cout << sum;
}
