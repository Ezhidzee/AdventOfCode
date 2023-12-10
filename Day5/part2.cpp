#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

class converter {

    struct destinationSourceRange {

        long long destinationBegin;

        long long destinationEnd;

        long long sourceBegin;

        long long sourceEnd;

        destinationSourceRange(long long destinationBegin, long long sourceBegin, long long rangeLength) {
            this->destinationBegin = destinationBegin;
            this->destinationEnd = destinationBegin + rangeLength;
            this->sourceBegin = sourceBegin;
            this->sourceEnd = sourceBegin + rangeLength;
        }

        long long convertNum(long long num) {
            if (num < destinationBegin || num >= destinationEnd) {
                return -1;
            } else {
                return sourceBegin + num - destinationBegin;
            }
        }
    };

    vector<destinationSourceRange> ranges;

public:

    void addRange(long long destinationBegin, long long sourceBegin, long long rangeLength) {
        ranges.emplace_back(destinationBegin, sourceBegin, rangeLength);
    }

    long long convert(long long num) {
        for (destinationSourceRange i: ranges) {
            long long convertedNum = i.convertNum(num);
            if (convertedNum != -1) return convertedNum;
        }
        return num;
    }
};

int main() {
    ifstream input("input.txt");
    input.ignore(numeric_limits<streamsize>::max(), ' ');
    vector<long long> seeds;
    string line;
    getline(input, line);
    while (!line.empty()) {
        long long rangeBegin = stoll(line);
        line.erase(0, line.find(' ') == string::npos ? line.size() : line.find(' ') + 1);
        long long rangeLength = stoll(line);
        line.erase(0, line.find(' ') == string::npos ? line.size() : line.find(' ') + 1);
        seeds.push_back(rangeBegin);
        seeds.push_back(rangeBegin + rangeLength);
    }
    input.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<converter> converters;

    for (int i = 0; i < 7; ++i) {
        input.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(input, line);
        converter conv;
        while (line != "" && !input.eof()) {
            long long destinationBegin, sourceBegin, rangeLength;
            destinationBegin = stoll(line);
            line.erase(0, line.find(' ') == string::npos ? line.size() : line.find(' ') + 1);
            sourceBegin = stoll(line);
            line.erase(0, line.find(' ') == string::npos ? line.size() : line.find(' ') + 1);
            rangeLength = stoll(line);
            conv.addRange(destinationBegin, sourceBegin, rangeLength);
            getline(input, line);
        }
        if (input.eof()) {
            long long destinationBegin, sourceBegin, rangeLength;
            destinationBegin = stoll(line);
            line.erase(0, line.find(' ') == string::npos ? line.size() : line.find(' ') + 1);
            sourceBegin = stoll(line);
            line.erase(0, line.find(' ') == string::npos ? line.size() : line.find(' ') + 1);
            rangeLength = stoll(line);
            conv.addRange(destinationBegin, sourceBegin, rangeLength);
        }
        converters.push_back(conv);
    }

    for (int i = 0; i < 10000000; ++i) {
        long long num = i;
        for (long long j = converters.size() - 1; j >= 0; --j) {
            num = converters[j].convert(num);
        }
        for (int j = 0; j < seeds.size() - 1; j += 2) {
            if (num >= seeds[j] && num <= seeds[j + 1]) {
                cout << i;
                return 0;
            }
        }
    }
}