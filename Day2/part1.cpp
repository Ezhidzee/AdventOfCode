#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream input("input.txt");
    const int RED_CUBES_COUNT = 12, GREEN_CUBES_COUNT = 13, BLUE_CUBES_COUNT = 14;

    string line;
    int sum = 0;
    while (getline(input, line)) {
        bool isPossible = 1;
        line.erase(0, line.find(' ') + 1);
        int gameIndex = stoi(line.substr(0, line.find(':')));
        line.erase(0, line.find(' ') + 1);

        while (line.size() != 0 && isPossible) {
            string set = line.substr(0, line.find(';') == string::npos ? line.size() : line.find(';'));
            line.erase(0, line.find(';') == string::npos ? line.size() : line.find(';') + 2);

            while (set.size() != 0 && isPossible) {
                string cubeCount = set.substr(0, set.find(',') == string::npos ? set.size() : set.find(','));
                set.erase(0, set.find(',') == string::npos ? set.size() : set.find(',') + 2);
                int count = stoi(cubeCount.substr(0, cubeCount.find(' ')));
                string colour = cubeCount.substr(cubeCount.find(' ') + 1, cubeCount.size());

                if ((colour == "blue" && count > BLUE_CUBES_COUNT) ||
                    (colour == "red" && count > RED_CUBES_COUNT) ||
                    (colour == "green" && count > GREEN_CUBES_COUNT)) {
                    isPossible = 0;
                }
            }
        }
        if (isPossible) {
            sum += gameIndex;
        }
    }
    cout << sum;
}