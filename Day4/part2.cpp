#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    ifstream input("input.txt");

    string line;
    unordered_map<int, int> cards;
    while (getline(input, line)) {
        while (line.find("  ") != string::npos) line.replace(line.find("  "), 2, " ");
        int cardNumber = stoi(line.substr(line.find(' '), line.find(':') - line.find(' ')));
        line.erase(0, line.find(':') + 2);
        unordered_map<int, int> nums;
        string elfNums = line.substr(0, line.find('|') - 1), winningNums = line.substr(line.find('|') + 2, line.size());
        while (!elfNums.empty()) {
            nums[stoi(elfNums)] = 1;
            elfNums.erase(0, elfNums.find(' ') == string::npos ? elfNums.size() : elfNums.find(' ') + 1);
        }
        int counter = 0;
        while (!winningNums.empty()) {
            int x = stoi(winningNums);
            winningNums.erase(0,
                              winningNums.find(' ') == string::npos ? winningNums.size() : winningNums.find(' ') + 1);
            if (nums[x] != 0) ++counter;
        }
        cards[cardNumber] = counter;
    }

    vector<int> instances;
    for (pair<int, int> i : cards) instances.push_back(i.first);

    for (int i = 0; i < instances.size(); ++i) {
        for (int j = 1; j <= cards[instances[i]]; ++j) {
            if (cards.contains(instances[i] + j)) instances.push_back(instances[i] + j);
        }
    }

    cout << instances.size();
}
