#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream input("input.txt");

    string line;
    long long sum = 0;
    while (getline(input, line)) {
        vector<int> nums;
        while (!line.empty()) {
            nums.push_back(stoi(line));
            line.erase(0, line.find(' ') == string::npos ? line.size() : line.find(' ') + 1);
        }
        bool isAllSame = 0;
        int k = 0;
        while (!isAllSame) {
            isAllSame = 1;
            for (int i = nums.size() - 1; i > k; --i) {
                nums[i] = nums[i] - nums[i - 1];
            }
            ++k;
            for (int i = nums.size() - 1; i > k; --i) {
                if (nums[i] != nums[i - 1]) {
                    isAllSame = 0;
                    break;
                }
            }
        }
        for (int i = k - 1; i >= 0; --i) {
            nums[i] -= nums[i + 1];
        }
        sum += nums[0];
    }

    cout << sum;
}
