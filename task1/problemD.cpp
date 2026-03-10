#include <iostream>
#include <string>
#include <vector>

struct AutomatonState {
    int maxLength;
    int suffixLink;
    int transitions[26];
};

const int MAX_STRING_LENGTH = 100005;
AutomatonState automaton[MAX_STRING_LENGTH * 2];

int statesCount;
int lastState;

void initializeAutomaton() {
    automaton[0].maxLength = 0;
    automaton[0].suffixLink = -1;
    for (int i = 0; i < 26; i++) {
        automaton[0].transitions[i] = -1;
    }
    statesCount = 1;
    lastState = 0;
}

void extendAutomaton(char character) {
    int charIndex = character - 'a';
    int currentState = statesCount++;
    
    automaton[currentState].maxLength = automaton[lastState].maxLength + 1;
    for (int i = 0; i < 26; i++) {
        automaton[currentState].transitions[i] = -1;
    }
    int prevState = lastState;
    while (prevState != -1 && automaton[prevState].transitions[charIndex] == -1) {
        automaton[prevState].transitions[charIndex] = currentState;
        prevState = automaton[prevState].suffixLink;
    }

    if (prevState == -1) {
        automaton[currentState].suffixLink = 0;
    } else {
        int nextState = automaton[prevState].transitions[charIndex];
        
        if (automaton[prevState].maxLength + 1 == automaton[nextState].maxLength) {
            automaton[currentState].suffixLink = nextState;
        } else {
            int clonedState = statesCount++;
            automaton[clonedState].maxLength = automaton[prevState].maxLength + 1;
            automaton[clonedState].suffixLink = automaton[nextState].suffixLink;
            
            for (int i = 0; i < 26; i++) {
                automaton[clonedState].transitions[i] = automaton[nextState].transitions[i];
            }

            while (prevState != -1 && automaton[prevState].transitions[charIndex] == nextState) {
                automaton[prevState].transitions[charIndex] = clonedState;
                prevState = automaton[prevState].suffixLink;
            }
            
            automaton[nextState].suffixLink = automaton[currentState].suffixLink = clonedState;
        }
    }
    lastState = currentState;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string inputString;
    std::cin >> inputString;

    initializeAutomaton();
    for (char character : inputString) {
        extendAutomaton(character);
    }

    int distinctSubstringsCount = 0;
    for (int i = 1; i < statesCount; i++) {
        int parentLink = automaton[i].suffixLink;
        distinctSubstringsCount += (automaton[i].maxLength - automaton[parentLink].maxLength);
    }

    std::cout << distinctSubstringsCount << "\n";

    return 0;
}
