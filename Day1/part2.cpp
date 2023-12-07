#include <iostream>
#include <fstream>
#include <ranges>
#include <unordered_map>
#include<algorithm>

using namespace std;

int main() {
    ifstream input("input.txt");

    if (!input.is_open()) {
        cerr << "The input file didn't open";
        return 0;
    }

    string line;
    int sum = 0;
    unordered_map<string, int> digits = {{"one",   1},
                                         {"two",   2},
                                         {"three", 3},
                                         {"four",  4},
                                         {"five",  5},
                                         {"six",   6},
                                         {"seven", 7},
                                         {"eight", 8},
                                         {"nine",  9}};

    while (getline(input, line)) {
        int firstEnterIndex = 1e9, num = 0;
        for (pair<string, int> digit: digits) {
            int x = line.find(digit.first);
            if (x != string::npos && x < firstEnterIndex) {
                firstEnterIndex = x;
                num = digit.second;
            }
        }
        for (int i = 0; i < line.size(); ++i) {
            if (isdigit(line[i]) && i < firstEnterIndex) {
                num = line[i] - '0';
                break;
            }
        }
        num *= 10;

        int lastEnterIndex = 0;
        for (pair<string, int> digit: digits) {
            string::iterator it = find_end(line.begin(), line.end(), digit.first.begin(), digit.first.end());
            if (it != line.end()) {
                int x = it - line.begin();
                if (x > lastEnterIndex) {
                    lastEnterIndex = x;
                    num /= 10;
                    num *= 10;
                    num += digit.second;
                }
            }
        }
        for (int i = line.size() - 1; i >= 0; --i) {
            if (isdigit(line[i]) && i >= lastEnterIndex) {
                num /= 10;
                num *= 10;
                num += line[i] - '0';
                break;
            }
        }

        sum += num;
    }

    cout << sum;
}
