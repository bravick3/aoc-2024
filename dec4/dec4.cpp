#include "../dec3/dec3.h"
#include "dec4.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <array>
#include <string.h>
#include <unordered_map>
using namespace std;

using Coordinate = array<int, 2>;       // (x, y)
using CoordinateSet = array<Coordinate, 3>; // (x, y) (x, y) (x, y)
// map (string, object) => {{x, {{1, 2}, {3, 4}, {5, 6}}}, {y, {{1, 2}, {3, 4}, {5, 6}}}, {z, {{1, 2}, {3, 4}, {5, 6}}}}
unordered_map<string, CoordinateSet> coordinates;
array<string, 8> directions;
unordered_map<int, string> lines;
string xmas("MAS");
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

void initMap() {
    directions = {"up_left", "up", "up_right", "right", "down_right", "down", "down_left", "left"};
    coordinates["up_left"] = {{{-1, -1}, {-2, -2}, {-3, -3}}};
    coordinates["up"] = {{{0, -1}, {0, -2}, {0, -3}}};
    coordinates["up_right"] = {{{1, -1}, {2, -2}, {3, -3}}};
    coordinates["right"] = {{{1, 0}, {2, 0}, {3, 0}}};
    coordinates["down_right"] = {{{1, 1}, {2, 2}, {3, 3}}};
    coordinates["down"] = {{{0, 1}, {0, 2}, {0, 3}}};
    coordinates["down_left"] = {{{-1, 1}, {-2, 2}, {-3, 3}}};
    coordinates["left"] = {{{-1, 0}, {-2, 0}, {-3, 0}}};
}

void initMap2() {
    directions = {"left_diag", "right_diag"};
    coordinates["left_diag"] = {{{-1, -1}, {0, 0}, {1, 1}}};
    coordinates["right_diag"] = {{{1, -1}, {0, 0}, {-1, 1}}};
}

bool checkCoordinates(int& x, int& y, string direction) {
    string check;
    try {
        for (int i = 0; i < xmas.length(); i++) {
            check += lines.at(x + coordinates[direction].at(i)[1]).at(y + coordinates[direction].at(i)[0]);
        }
    } catch (const std::out_of_range& e) {/* Ignore the out_of_range error and do nothing, cuz i'm lazy */}
    if (check == xmas) {return true;}
    return false;
}

void searchXmas(int& x, int& y) {
    for (auto direction : directions) {
        if (checkCoordinates(x, y, direction)) {counter += 1;}
    }
}

bool checkCoordinates2(int& x, int& y, string direction) {
    string check;
    try {
        for (int i = 0; i < xmas.length(); i++) {
            check += lines.at(x + coordinates[direction].at(i)[1]).at(y + coordinates[direction].at(i)[0]);
        }
    } catch (const std::out_of_range& e) {/* Ignore the out_of_range error and do nothing, cuz i'm lazy */}
    cout << check << " ";
    if (check == "MAS" || check == "SAM") {return true;}
    /*ranges::reverse(check);
    if (check == xmas) {return true;}*/
    return false;
}

void searchXmas2(int& x, int& y) {
    bool first = checkCoordinates2(x, y, "left_diag");
    bool second = checkCoordinates2(x, y, "right_diag");
    cout<< " | " << first << " " << second << " ";
    if (first && second) {counter += 1;}
    cout << endl;
}


void findXmas(const unordered_map<int, string>& lines_map) {
    for (int i = 0; i < lines_map.size(); i++) {
        for (int j = 0; j < lines_map.at(0).length(); j++) {
            if (lines_map.at(i).at(j) != 'A') {continue;} //X for the first A for the second
            // searchXmas(i, j);
            searchXmas2(i, j);
        }
    }
}

void day4() {
    // initMap();
    initMap2();
    ifstream file(loadFile("dec4/xmas"));
    findXmas(loadXmas(file));
    cout << counter << endl;
}
