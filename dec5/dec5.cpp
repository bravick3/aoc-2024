
#include "dec5.h"
#include "../dec3/dec3.h"
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;
using Next = list<int>;
std::unordered_map<int, Next> rules;
list<string> correctInstructions;
list<string> falseInstructions;
list<vector<int>> fixedFalseInstructions;
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

vector<int> splitStringVector(string &input, char divider) {
    vector<int> result;
    int pos = 0;
    while ((pos = input.find(divider)) != string::npos) {
        result.push_back(stoi(input.substr(0, pos)));
        input.erase(0, pos + 1);
    }
    result.push_back(stoi(input));
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
        } else {
            falseInstructions.push_front(line);
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

bool findInstruction(int &key, int &value) {
    for (auto ruleValue : rules[key]) {
        if (ruleValue == value) {
            // cout << "Rule Found: " << key << " | " << ruleValue << endl;
            return true;
        }
    }
    return false;
}


bool sortInstruction(vector<int> &list) {
    for (int i = 0; i < list.size(); i++) {
        for (int j = i + 1; j < list.size(); j++) {
            // cout << list.at(i) << " | " << list.at(j) << endl;
            bool iBeforeJ = findInstruction(list.at(i), list.at(j));
            bool jBeforeI = findInstruction(list.at(j), list.at(i));
            if (iBeforeJ && jBeforeI) {
                cout << "Two rules found! Incorrect Set!" << endl;
                return false;
            }
            if (jBeforeI) {
                int temp = list.at(i);
                list.at(i) = list.at(j);
                list.at(j) = temp;
            }
        }
    }
     //check if final instruction is correct
    vector<int> checkedInstructions;
    for (int k = 0; k < list.size(); k++) {
        for (int l = k + 1; l < list.size(); l++) {
            if (isInRules(list.at(l),list.at(k))) {
                cout << "Instruction is wrong: " << l << " | " << k << endl;
                return false;
            }
        }
    }
    return true;
}

void sumFalseInstructions() {
    for (auto instruction : falseInstructions) {
        vector<int> instList = splitStringVector(instruction, ',');
        bool isSorted = sortInstruction(instList);
        if (isSorted) {
            // get middle value and add it up
            //fixedFalseInstructions.push_front(instList);
            counter5 += instList.at(instList.size()/2);
        }

    }
}

void day5() {
    ifstream rulesFile(loadFile("dec5/rules"));
    loadRules(rulesFile);
    //printMap(rules);
    ifstream instructionsFile(loadFile("dec5/safety-instructions"));
    checkInstructions(instructionsFile);

    cout << correctInstructions.size() << endl;;
    cout << falseInstructions.size() << endl;

    // sumCorrectInstructions();
    sumFalseInstructions();
    cout << counter5 << endl;

}

