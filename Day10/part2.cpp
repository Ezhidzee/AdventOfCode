#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

struct point {
    double x;

    double y;
};

struct line {
    point a;

    point b;
};


double area(point a, point b, point c) {
    return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

bool intersect_1(double a, double b, double c, double d) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return max(a, c) <= min(b, d);
}

bool intersect(point a, point b, point c, point d) {
    return intersect_1(a.x, b.x, c.x, d.x)
           && intersect_1(a.y, b.y, c.y, d.y)
           && area(a, b, c) * area(a, b, d) <= 0
           && area(c, d, a) * area(c, d, b) <= 0;
}

int main() {
    ifstream input("input.txt");
    if (!input.is_open()) {
        cerr << "The input file didn't open";
        return 0;
    }

    vector<string> maze;
    vector<point> coordinates;
    sf::RenderWindow window;

    string str;
    while (getline(input, str)) {
        maze.push_back(str);
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

    while (true) {
        coordinates.emplace_back(x, y);
        if (maze[y][x] == 'S') {
            maze[y][x] = '*';
            if (y != 0 && (maze[y - 1][x] == '|' || maze[y - 1][x] == '7' || maze[y - 1][x] == 'F')) {
                --y;
            } else if (x != maze[0].size() - 1 &&
                       (maze[y][x + 1] == '-' || maze[y][x + 1] == 'J' || maze[y][x + 1] == '7')) {
                ++x;
            } else if (y != maze.size() - 1 &&
                       (maze[y + 1][x] == '|' || maze[y + 1][x] == 'L' || maze[y + 1][x] == 'J')) {
                ++y;
            } else if (x != 0 && (maze[y][x - 1] == '-' || maze[y][x - 1] == 'F' || maze[y][x - 1] == 'L')) {
                --x;
            } else {
                maze[y][x] = '*';
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
            coordinates.erase(coordinates.end() - 1);
            break;
        }
    }
    coordinates.push_back(*coordinates.begin());

    vector<line> lines;

    int i = 0;
    while (i != coordinates.size() - 1) {
        line l;
        l.a = coordinates[i];
        if (coordinates[i].x == coordinates[i + 1].x) {
            while (coordinates[i].x == coordinates[i + 1].x) {
                ++i;
            }
        } else {
            while (coordinates[i].y == coordinates[i + 1].y) {
                ++i;
            }
        }
        l.b = coordinates[i];
        lines.push_back(l);
    }

    window.create(sf::VideoMode(1200, 800), "SFML works!");
    for (line l: lines) {
        sf::Vertex line[] =
                {
                        sf::Vertex(sf::Vector2f(l.a.x * 5 + 50, l.a.y * 5 + 50), sf::Color::Green),
                        sf::Vertex(sf::Vector2f(l.b.x * 5 + 50, l.b.y * 5 + 50), sf::Color::Green)
                };
        window.draw(line, 2, sf::Lines);
    }
    window.display();
    window.display();
    int tilesCount = 0;
    for (int j = 0; j < maze.size(); ++j) {
        for (int k = 0; k < maze[j].size(); ++k) {
            if (maze[j][k] == '*') {
                continue;
            }
            point a{double(k) + 0.5, double(maze.size())};
            point b{double(k) + 0.5, double(j)};
            int counter = 0;
            for (int l = 0; l < lines.size(); ++l) {
                if (l != 0 && intersect(a, b, lines[l - 1].a, lines[l - 1].b) &&
                    area(a, b, lines[l].a) == 0) {
                    continue;
                }
                if (intersect(a, b, lines[l].a, lines[l].b)) {
                    counter++;
                }
            }
            if (counter % 2 != 0) {
                sf::CircleShape circle(1);
                circle.setFillColor(sf::Color::Blue);
                circle.setPosition(b.x * 5 + 50, b.y * 5 + 50);
                window.draw(circle);
                ++tilesCount;
            }
        }
    }

    cout << tilesCount;
    window.display();
    system("PAUSE");
}