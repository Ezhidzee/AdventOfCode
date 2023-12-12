#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <numeric>
#include <algorithm>

using namespace std;

namespace network {
    struct vertex {
        string value;

        vertex *l = nullptr;

        vertex *r = nullptr;
    };

    vertex *find(const vector<vertex *> &vertexes, const string &value) {
        for (vertex *v: vertexes) if (v->value == value) return v;

        return nullptr;
    }
}

int main() {
    ifstream input("input.txt");
    string instructions;
    getline(input, instructions);
    vector<network::vertex *> vertexes(0);
    input.ignore(numeric_limits<streamsize>::max(), '\n');

    string line;
    while (getline(input, line)) {
        string node = line.substr(0, 3), l = line.substr(7, 3), r = line.substr(12, 3);
        network::vertex *v = network::find(vertexes, node);
        if (v == nullptr) {
            v = new network::vertex{node};
            vertexes.push_back(v);
        }
        network::vertex *lV = network::find(vertexes, l);
        if (lV == nullptr) {
            lV = new network::vertex{l};
            vertexes.push_back(lV);
        }
        network::vertex *rV = network::find(vertexes, r);
        if (rV == nullptr) {
            rV = new network::vertex{r};
            vertexes.push_back(rV);
        }
        v->l = lV;
        v->r = rV;
    }

    vector<network::vertex *> nodes;
    vector<long long> loops;
    for (network::vertex *i: vertexes) if (i->value[2] == 'A') nodes.push_back(i);


    for (int j = 0; j < nodes.size(); ++j) {
        int counter = 0;
        int i = 0;
        while (nodes[j]->value[2] != 'Z') {
            if (i == instructions.size()) i = 0;
            if (instructions[i] == 'R') {
                nodes[j] = nodes[j]->r;
            } else nodes[j] = nodes[j]->l;
            ++counter;
            ++i;
        }
        loops.push_back(counter);
    }

    for (int i : loops) cout << i << ", ";
}