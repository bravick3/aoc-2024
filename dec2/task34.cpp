#include "task34.h"
#include "../dec1/dec1.h"
#include <fstream>
#include <iostream>
#include <list>
using namespace std;

list<int> split(string input) {
    list<int> result;
    int pos = 0;
    while ((pos = input.find(' ')) != string::npos) {
        result.push_back(stoi(input.substr(0, pos)));
        input.erase(0, pos + 1);
    }
    result.push_back(stoi(input));
    return result;
}

int second(){
    ifstream file("dec2/rednose-reactor-data");
    string line;
    int sum = 0;

    if (!file.is_open()) {
        cerr << "Error: Could not open the file 'rednose-reactor-data'" << endl;
        return 1;
    }

    while (getline(file, line)) {
        list<int> data = split(line);
        auto iterator = data.begin();
        int previous = *iterator;
        bool asc = false;
        bool correct = true;
        ++iterator;
        if (previous < *iterator) {
            asc = true;
        }
        while (iterator != data.end()) {
            if (asc && previous > *iterator) {
                cout << "WRONG | asc: " << asc << " | line: " << line << endl;
                correct = false;
                break;
            }
            if (!asc && previous < *iterator) {
                cout << "WRONG | asc: " << asc << " | line: " << line << endl;
                correct = false;
                break;
            }
            int abs = absolute(previous, *iterator);
            if (abs < 1 || abs > 3) {
                cout << "WRONG | asc: " << asc << " | line: " << line << endl;
                correct = false;
                break;
            }
            previous = *iterator;
            ++iterator;
        }
        if (correct) {
            cout << "CORRECT | asc: " << asc << " | line: " << line << endl;
            sum++;
        }
    }
    cout << "Sum: " << sum << endl;
    return 0;
}

