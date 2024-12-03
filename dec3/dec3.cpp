#include "dec3.h"
#include <fstream>
#include <iostream>
#include <list>
#include <regex>
using namespace std;

bool permission = true;

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
        //cout << match.str() << " | " << match[1] << " | " << match[2] << '\n';
        sum += stoi(match[1]) * stoi(match[2]);
    }
    return sum;
}

int improvedExpressionFinder(string& line) {
    regex pattern(R"((do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\)))");
    int sum = 0;
    //sum += stoi(match[1]) * stoi(match[2]);
    for(sregex_iterator i = sregex_iterator(line.begin(), line.end(), pattern);
        i != std::sregex_iterator(); ++i ) {
        smatch match = *i;
        string match_str = match.str();
        // cout << match_str << endl;
        if (match_str == "don't()") {
            permission = false;
            cout << "Permission False: " << match_str << endl;
            continue;
        }
        if (match_str == "do()") {
            permission = true;
            cout << "Permission True: " << match_str << endl;
            continue;
        }
        if (permission) {
            //cout << match.str() << " | " << match[2] << " | " << match[3] << '\n';
            sum += stoi(match[2]) * stoi(match[3]);
        }

        //sum += stoi(match[1]) * stoi(match[2]);
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
        total_sum += improvedExpressionFinder(line);
    }
    cout << total_sum << endl;
}

void day3(){
    ifstream file = loadFile("dec3/corrupted-pc-data");
    loop(file);

}