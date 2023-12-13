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
        int k = nums.size() - 1;
        while (!isAllSame) {
            isAllSame = 1;
            for (int i = 0; i < k; ++i) {
                nums[i] = nums[i + 1] - nums[i];
            }
            --k;
            for (int i = 0; i < k; ++i) {
                if (nums[i + 1] != nums[i]) {
                    isAllSame = 0;
                    break;
                }
            }
        }
        for (int i = k + 1; i < nums.size(); ++i) {
            nums[i] += nums[i - 1];
        }
        sum += nums[nums.size() - 1];
    }

    cout << sum;
}
