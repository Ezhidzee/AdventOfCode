#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream input("input.txt");
    vector<string> maze;

    string line;
    while(getline(input, line)) {
        maze.push_back(line);
    }

    int x, y;
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            if (maze[i][j] == 'S') {
                y = i;
                x = j;
                goto loopSearch;
            }
        }
    }
    loopSearch:

    int counter = 0;
    while (true) {
        if (maze[y][x] == 'S') {
            maze[y][x] = '*';
            if (y != 0 && (maze[y - 1][x] == '|' || maze[y - 1][x] == '7' || maze[y - 1][x] == 'F')) {
                --y;
            } else if (x != maze[0].size() - 1 && (maze[y][x + 1] == '-' || maze[y][x + 1] == 'J' || maze[y][x + 1] == '7')) {
                ++x;
            } else if (y != maze.size() - 1 && (maze[y + 1][x] == '|' || maze[y + 1][x] == 'L' || maze[y + 1][x] == 'J')) {
                ++y;
            } else if (x != 0 && (maze[y][x - 1] == '-' || maze[y][x - 1] == 'F' || maze[y][x - 1] == 'L')) {
                --x;
            } else {
                maze[y][x] = '*';
                ++counter;
                break;
            }
            continue;
        }
        if (maze[y][x] == '|') {
            maze[y][x] = '*';
            if (y != 0 && maze[y - 1][x] == '*') {
                ++y;
            } else --y;
        } else if (maze[y][x] == '-') {
            maze[y][x] = '*';
            if (x != 0 && maze[y][x - 1] == '*') {
                ++x;
            } else x--;
        } else if (maze[y][x] == 'L') {
            maze[y][x] = '*';
            if (x != maze[0].size() - 1 && maze[y][x + 1] == '*') {
                --y;
            } else ++x;
        } else if (maze[y][x] == 'J') {
            maze[y][x] = '*';
            if (x != 0 && maze[y][x - 1] == '*') {
                --y;
            } else --x;
        } else if (maze[y][x] == '7') {
            maze[y][x] = '*';
            if (x != 0 && maze[y][x - 1] == '*') {
                ++y;
            } else --x;
        } else if (maze[y][x] == 'F') {
            maze[y][x] = '*';
            if (x != maze[0].size() - 1 && maze[y][x + 1] == '*') {
                ++y;
            } else ++x;
        } else {
            ++counter;
            break;
        }
        ++counter;
    }

    cout << counter / 2;
}