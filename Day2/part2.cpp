#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream input("input.txt");

    string line;
    int sum = 0;
    while (getline(input, line)) {
        line.erase(0, line.find(' ') + 1);
        line.erase(0, line.find(' ') + 1);

        int blueMinCount = 1, greenMinCount = 1, redMinCount = 1;
        while (line.size() != 0) {
            string set = line.substr(0, line.find(';') == string::npos ? line.size() : line.find(';'));
            line.erase(0, line.find(';') == string::npos ? line.size() : line.find(';') + 2);

            while (set.size() != 0) {
                string cubeCount = set.substr(0, set.find(',') == string::npos ? set.size() : set.find(','));
                set.erase(0, set.find(',') == string::npos ? set.size() : set.find(',') + 2);
                int count = stoi(cubeCount.substr(0, cubeCount.find(' ')));
                string colour = cubeCount.substr(cubeCount.find(' ') + 1, cubeCount.size());

                if (colour == "blue" && count > blueMinCount) {
                    blueMinCount = count;
                } else if (colour == "red" && count > redMinCount) {
                    redMinCount = count;
                } else if (colour == "green" && count > greenMinCount) {
                    greenMinCount = count;
                }
            }
        }
        sum += blueMinCount * redMinCount * greenMinCount;
    }
    cout << sum;
}