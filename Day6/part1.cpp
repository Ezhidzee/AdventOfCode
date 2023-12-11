#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

int main() {
    ifstream input("input.txt");
    vector<int> times, distances;
    string line;
    getline(input, line);
    while (line.find("  ") != string::npos) line.replace(line.find("  "), 2, " ");
    line.erase(0, line.find(' ') == string::npos ? line.size() : line.find(' ') + 1);
    while (!line.empty()) {
        times.push_back(stoi(line));
        line.erase(0, line.find(' ') == string::npos ? line.size() : line.find(' ') + 1);
    }
    getline(input, line);
    while (line.find("  ") != string::npos) line.replace(line.find("  "), 2, " ");
    line.erase(0, line.find(' ') == string::npos ? line.size() : line.find(' ') + 1);
    while (!line.empty()) {
        distances.push_back(stoi(line));
        line.erase(0, line.find(' ') == string::npos ? line.size() : line.find(' ') + 1);
    }

    int multiplication = 1;
    for (int i = 0; i < times.size(); ++i) {
        int counter = 0;
        for (int j = (times[i] / 2) + 1; j < times[i]; ++j) {
            if (j * (times[i] - j) > distances[i]) {
                ++counter;
            }
        }
        multiplication *= (times[i] % 2 == 0 ? (counter * 2) + 1 : counter * 2);
    }

    cout << multiplication;
}