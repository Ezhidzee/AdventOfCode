#include <iostream>
#include <fstream>
#include <ranges>

using namespace std;

int main() {
    ifstream input("input.txt");

    if (!input.is_open()) {
        cerr << "The input file didn't open";
        return 0;
    }

    string line;
    int sum = 0;
    while (getline(input, line)) {
        int num = 0;
        for (char i : line) {
            if (isdigit(i)) {
                num += i - '0';
                break;
            }
        }
        num *= 10;
        for (char i : line | views::reverse) {
            if (isdigit(i)) {
                num += i - '0';
                break;
            }
        }
        sum += num;
    }

    cout << sum;
}
