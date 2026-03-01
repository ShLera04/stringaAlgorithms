#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> z_function(const std::string& str) {
    int size = str.length();
    std::vector<int> z_values(size, 0);
    z_values[0] = size;

    int left = 0, right = 0;
    for (int first = 1; first < size; ++first) {
        if (first < right) {
            z_values[first] = std::min(right - first, z_values[first - left]);
        }
        while (first + z_values[first] < size && str[z_values[first]] == str[first + z_values[first]]) {
            z_values[first]++;
        }
        if (first + z_values[first] > right) {
            left = first;
            right = first + z_values[first];
        }
    }

    return z_values;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str;
    std::cin >> str;
    int str_len = str.length();
    int max_k = 1;

    for (int start = 0; start < str_len; ++start) {
        std::string substr = str.substr(start);
        std::vector<int> z_values = z_function(substr);
        int substr_len = substr.length();

        for (int period = 1; period < substr_len; ++period) {
            if (z_values[period] >= period) {
                int current_k = z_values[period] / period + 1;
                max_k = std::max(max_k, current_k);
            }
        }
    }
    

    std::cout << max_k << "\n";

    return 0;
}
