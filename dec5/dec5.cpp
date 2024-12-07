
#include "dec5.h"
#include "../dec3/dec3.h"
#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;
using Next = list<int>;
std::unordered_map<int, Next> rules;
list<string> correctInstructions;
int counter5 = 0;

list<int> splitString(string &input, char divider) {
    list<int> result;
    int pos = 0;
    while ((pos = input.find(divider)) != string::npos) {
        result.push_front(stoi(input.substr(0, pos)));
        input.erase(0, pos + 1);
    }
    result.push_front(stoi(input));
    return result;
}
unordered_map<int, Next> &loadRules(ifstream &file) {
    string line;
    int i = 0;
    while (getline(file, line)) {
        list<int> rule = splitString(line, '|');
        rules[rule.back()].push_front(rule.front());
    }
    return rules;
}

bool isInRules(int &previous, int &instruction) {
    list<int> hm = rules[instruction];
    for (auto rule : hm) {
        if (previous == rule) {
            return false;
        }
    }
    return true;
}
bool lineCheck(string instructionSet) {
    list<int> checkedInstructions;
    list<int> instList = splitString(instructionSet, ',');
    for (auto instruction: instList) {
        for (auto previous : checkedInstructions) {
            if (isInRules(previous, instruction)) {
                return false;
            }
        }
        checkedInstructions.push_front(instruction);
    }
    return true;
}
void checkInstructions(ifstream &file) {
    string line;
    int i = 0;
    while (getline(file, line)) {
        if (lineCheck(line)) {
            correctInstructions.push_front(line);
        }
    }
}
void printMap(const unordered_map<int, list<int>>& map) {
    for (const auto& pair : map) {
        cout << "Key: " << pair.first << " | Values: ";
        for (const auto& value : pair.second) {
            cout << value << " ";
        }
        cout << endl;
    }
}

void sumCorrectInstructions() {
    for (auto instruction : correctInstructions) {
        list<int> instList = splitString(instruction, ',');
        auto middleiterator = instList.begin();
        advance(middleiterator, instList.size()/2);
        counter5 += *middleiterator;
        // cout << *middleiterator << endl;
    }
}

void day5() {
    ifstream rulesFile(loadFile("dec5/rules"));
    loadRules(rulesFile);
    //printMap(rules);
    ifstream instructionsFile(loadFile("dec5/safety-instructions"));
    checkInstructions(instructionsFile);

    sumCorrectInstructions();
    cout << counter5 << endl;

    /*for (string i : correctInstructions) {
        cout << i << endl;
    }*/

}

