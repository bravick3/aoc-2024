#include "../dec3/dec3.h"
#include "dec4.h"
#include <fstream>
#include <iostream>
#include <array>
#include <unordered_map>
using namespace std;

using Coordinate = array<int, 2>;       // (x, y)
using CoordinateSet = array<Coordinate, 3>; // (x, y) (x, y) (x, y)
// map (string, object) => {{x, {{1, 2}, {3, 4}, {5, 6}}}, {y, {{1, 2}, {3, 4}, {5, 6}}}, {z, {{1, 2}, {3, 4}, {5, 6}}}}
unordered_map<string, CoordinateSet> coordinates;
unordered_map<int, string> lines;
string xmas("mas");
int counter = 0;


unordered_map<int, string> &loadXmas(ifstream &file) {
    string line;
    int i = 0;
    while (getline(file, line)) {
        lines[i] = line;
        i++;
    }
    return lines;
}



void searchXmas(int& x, int& y) {
    for (int i = 0; i < xmas.length(); i++) {

    }

}

void findXmas(const unordered_map<int, string>& lines_map) {
    for (int i = 0; i < lines_map.size(); i++) {
        for (int j = 0; j < lines_map.at(0).length(); j++) {
            if (lines_map.at(i).at(j) != 'X') {
                continue;
            }



            // check if X
            // check the index => block
        }
        cout << endl;
    }
}

void initMap() {
    coordinates["up_left"] = {{{-1, -1}, {-2, -2}, {-3, -3}}};
    coordinates["up"] = {{{0, -1}, {0, -2}, {0, -3}}};
    coordinates["up_right"] = {{{1, -1}, {2, -2}, {3, -3}}};
    coordinates["right"] = {{{1, 0}, {2, 0}, {3, 0}}};
    coordinates["down_right"] = {{{1, 1}, {2, 2}, {3, 3}}};
    coordinates["down"] = {{{0, 1}, {0, 2}, {0, 3}}};
    coordinates["down_left"] = {{{-1, 1}, {-2, 2}, {-3, 3}}};
    coordinates["left"] = {{{-1, 0}, {-2, 0}, {-3, 0}}};
}

void day4() {
    initMap();
    ifstream file(loadFile("dec4/xmas"));
    findXmas(loadXmas(file));
}
