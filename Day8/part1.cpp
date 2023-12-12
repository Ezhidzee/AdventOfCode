#include <iostream>
#include <vector>
#include <fstream>
#include <limits>

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

    network::vertex *currentVertex = network::find(vertexes, "AAA");
    int counter = 0;
    int i = 0;
    while (currentVertex->value != "ZZZ") {
        if (i == instructions.size()) i = 0;
        if (instructions[i] == 'R') {
            currentVertex = currentVertex->r;
        } else currentVertex = currentVertex->l;
        ++counter;
        ++i;
    }

    cout << counter;
}