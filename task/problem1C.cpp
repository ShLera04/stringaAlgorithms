#include <iostream>
#include <string>
#include <vector>

std::vector<int> z_function(const std::string& str) {
    int size = str.length();
    std::vector<int> z_values(size);
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
    std::vector<int> z_values = z_function(str);
    int size = z_values.size();

    for (int first = 0; first < size; ++first) {
        if (first > 0) std::cout << " ";
        std::cout << z_values[first];
    }
    std::cout<< "\n";

    return 0;
}
