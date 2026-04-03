#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
const int kMaxStringLength = 200005;
const int kLen = 26;

struct AutomatonState {
    int max_length;
    int suffix_link;
    int transitions[kLen];
    int first_end_pos;
};

AutomatonState automaton[kMaxStringLength * 2];
int min_match[kMaxStringLength * 2];
int temp_match[kMaxStringLength * 2];

int states_count;
int last_state;

void InitializeAutomaton() {
    automaton[0].max_length = 0;
    automaton[0].suffix_link = -1;
    automaton[0].first_end_pos = -1;
    for (int index = 0; index < kLen; ++index) {
        automaton[0].transitions[index] = -1;
    }
    states_count = 1;
    last_state = 0;
}

void ExtendAutomaton(char character, int pos) {
    int char_index = character - 'a';
    int current_state = states_count++;
    automaton[current_state].max_length = automaton[last_state].max_length + 1;
    automaton[current_state].first_end_pos = pos;
    for (int index = 0; index < kLen; ++index) {
        automaton[current_state].transitions[index] = -1;
    }
    int prev_state = last_state;
    while (prev_state != -1 &&
           automaton[prev_state].transitions[char_index] == -1) {
        automaton[prev_state].transitions[char_index] = current_state;
        prev_state = automaton[prev_state].suffix_link;
    }

    if (prev_state == -1) {
        automaton[current_state].suffix_link = 0;
    } else {
        int next_state = automaton[prev_state].transitions[char_index];
        if (automaton[prev_state].max_length + 1 ==
            automaton[next_state].max_length) {
            automaton[current_state].suffix_link = next_state;
        } else {
            int cloned_state = states_count++;
            automaton[cloned_state].max_length =
                automaton[prev_state].max_length + 1;
            automaton[cloned_state].suffix_link =
                automaton[next_state].suffix_link;
            automaton[cloned_state].first_end_pos =
                automaton[next_state].first_end_pos;
            for (int index = 0; index < kLen; ++index) {
                automaton[cloned_state].transitions[index] =
                    automaton[next_state].transitions[index];
            }
            while (prev_state != -1 &&
                   automaton[prev_state].transitions[char_index] ==
                       next_state) {
                automaton[prev_state].transitions[char_index] = cloned_state;
                prev_state = automaton[prev_state].suffix_link;
            }
            automaton[next_state].suffix_link =
                automaton[current_state].suffix_link = cloned_state;
        }
    }
    last_state = current_state;
}

void ProcessString(const std::string& str,
                   const std::vector<int>& states_by_len) {
    for (int index = 0; index < states_count; ++index) {
        temp_match[index] = 0;
    }
    int current_state = 0;
    int current_len = 0;
    for (char character : str) {
        int char_index = character - 'a';
        while (current_state != 0 &&
               automaton[current_state].transitions[char_index] == -1) {
            current_state = automaton[current_state].suffix_link;
            current_len = automaton[current_state].max_length;
        }
        if (automaton[current_state].transitions[char_index] != -1) {
            current_state = automaton[current_state].transitions[char_index];
            current_len++;
        }
        temp_match[current_state] =
            std::max(temp_match[current_state], current_len);
    }
    for (int idx : states_by_len) {
        if (idx != 0 && automaton[idx].suffix_link != -1) {
            int parent = automaton[idx].suffix_link;
            temp_match[parent] = std::max(
                temp_match[parent],
                std::min(automaton[parent].max_length, temp_match[idx]));
        }
    }
    for (int index = 0; index < states_count; ++index) {
        min_match[index] = std::min(min_match[index], temp_match[index]);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int count;
    if (!(std::cin >> count)) {
        return 0;
    }

    std::string first_string;
    std::cin >> first_string;

    InitializeAutomaton();
    for (int index = 0; index < (int)first_string.size(); ++index) {
        ExtendAutomaton(first_string[index], index);
    }

    for (int index = 0; index < states_count; ++index) {
        min_match[index] = automaton[index].max_length;
    }

    std::vector<int> states_by_len(states_count);
    for (int index = 0; index < states_count; ++index) {
        states_by_len[index] = index;
    }
    std::sort(states_by_len.begin(), states_by_len.end(), [](int aa, int bb) {
        return automaton[aa].max_length > automaton[bb].max_length;
    });

    for (int i_count = 1; i_count < count; ++i_count) {
        std::string current_str;
        std::cin >> current_str;
        ProcessString(current_str, states_by_len);
    }

    int best_len = 0;
    int best_end_pos = -1;
    for (int index = 1; index < states_count; ++index) {
        if (min_match[index] > best_len) {
            best_len = min_match[index];
            best_end_pos = automaton[index].first_end_pos;
        }
    }

    if (best_len > 0) {
        std::cout << first_string.substr(best_end_pos - best_len + 1, best_len)
                  << "\n";
    } else {
        std::cout << "\n";
    }

    return 0;
}
