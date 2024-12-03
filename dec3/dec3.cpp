#include "dec3.h"
#include <fstream>
#include <iostream>
#include <list>
#include <regex>
using namespace std;

ifstream loadFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file '" << filename << "'" << endl;
        exit(1);
    }
    return file;
}

int expressionFinder(string& line) {
    regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    int sum = 0;
    //sum += stoi(match[1]) * stoi(match[2]);
    for(sregex_iterator i = sregex_iterator(line.begin(), line.end(), pattern);
            i != std::sregex_iterator(); ++i ) {
        smatch match = *i;
        //cout << m.str() << " | " << m[1] << " | " << m[2] << '\n';
        sum += stoi(match[1]) * stoi(match[2]);
    }
    return sum;
}

// void multipleExpressionFinder(string& line) {
//     regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
//
//
//     regex_search(line, match, pattern);
//     smatch match;
// }

void loop(ifstream& file) {
    string line;
    int total_sum = 0;
    int index = 1;
    while (getline(file, line)) {
        cout << "Line no. " << index << endl;
        index++;
        total_sum += expressionFinder(line);
    }
    cout << total_sum << endl;
}

void day3(){
    ifstream file = loadFile("dec3/corrupted-pc-data");
    loop(file);

}