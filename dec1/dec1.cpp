#include "dec1.h"
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string.h>

using namespace std;

list<int> split(const string& input) {
    list<int> result;
    int pos = 0;
    pos = input.find('\t');
    result.push_back(stoi(input.substr(0, pos)));
    pos += 4;
    result.push_front(stoi(input.substr(pos+4, input.size() - pos)));
    // cout << "First part:" << result.back() << "\nSecond part:" << result.front() << endl;
    return result;
}

int absolute(int number1, int number2) {
    int result = number1 - number2;
    if (result < 0) {
        result *= -1;
    }
    return result;
}

list<int> hamming(const list<int>& left, const list<int>& right) {
    list<int> result;
    auto itLeft = left.begin();
    auto itRight = right.begin();
    while (itLeft != left.end() && itRight != right.end()) {
        result.push_back(absolute(*itLeft, *itRight));
        ++itLeft;
        ++itRight;
    }
    return result;
}

int similarity(const list<int>& left, const list<int>& right) {
    int simCount = 0;
    auto itLeft = left.begin();
    while (itLeft != left.end()) {
        int count = 0;
        auto itRight = right.begin();
        while(itRight != right.end()) {
            if (*itLeft == *itRight) {
                count++;
            }
            ++itRight;
        }
        simCount += *itLeft * count;
        ++itLeft;
    }
    return simCount;
}

int first() {
    ifstream file("dec1/input1.txt");
    string line;
    list<int> left = {};
    list<int> right = {};

    if (!file.is_open()) {
        cerr << "Error: Could not open the file 'input1.txt'" << endl;
        return 1;
    }
    while (getline(file, line)) {
        list<int> parts = split(line);
        left.push_back(parts.back());
        right.push_back(parts.front());
    }
    left.sort();
    right.sort();
    file.close();

    list<int> result = hamming(left, right);
    cout << "Result len: " << result.size() << endl;
    //print
    int sum = 0;
    for(int i = 0; i < 1000; i++) {
        sum += result.front();
        result.pop_front();
    }
    cout << "Sum: " << sum << endl;
    cout << "Sim Left -> Right: " << similarity(left, right) << endl;
    cout << "Sim Right -> Left: " << similarity(right, left) << endl;


    return 0;
}

int test() {
    list<int> left = {1, 2, 3, 4, 5};
    list<int> right = {5, 4, 3, 2, 1};
    int result = similarity(left, right);
    cout << "Result: " << result << endl;
    /*list<int> result = hamming(left, right);
    for (auto it = result.begin(); it != result.end(); ++it) {
        cout << *it << endl;
    }*/
    return 0;
}


