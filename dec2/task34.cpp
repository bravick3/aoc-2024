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

bool isCorrect(auto& iterator, list<int>& data, bool asc, int previous, string& line) {
    bool correct = true;
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
    return correct;
}


int second() {
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
        ++iterator;
        if (previous < *iterator) {
            asc = true;
        }
        bool correct = isCorrect(iterator, data, asc, previous, line);

        if (correct) {
            cout << "CORRECT | asc: " << asc << " | line: " << line << endl;
            sum++;
        }
    }
    cout << "Sum: " << sum << endl;
}

int third() {
    ifstream file("dec2/rednose-reactor-data");
    // ifstream file("dec2/test-file");
    string line;
    int sum = 0;
    if (!file.is_open()) {
        cerr << "Error: Could not open the file 'rednose-reactor-data'" << endl;
        return 1;
    }
    while (getline(file, line)) { //while 1
        list<int> data = split(line);
        auto iterator = data.begin();

        while (iterator != data.end()) { //while 2
            cout << "Iterator: " << *iterator << endl;
            list<int> copy = data;
            auto copy_iterator = copy.begin();
            advance(copy_iterator, distance(data.begin(), iterator));
            copy.erase(copy_iterator);
            auto inner_iterator = copy.begin();
            int inner_previous = *inner_iterator;
            bool asc = false;
            ++inner_iterator;
            if (inner_previous < *inner_iterator) {
                asc = true;
            }
            bool correct = isCorrect(inner_iterator, copy, asc, inner_previous, line);
            cout << "Correct: " << correct << endl;

            if (correct) {
                cout << "CORRECT | asc: " << asc << " | line: " << line << endl;
                sum++;
                break;
                //stop the while 2 and continue with while 1
            }
            ++iterator;
        }

    }
    cout << "Sum: " << sum << endl;
}

