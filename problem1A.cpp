#include <iostream>
#include <string>
#include <vector>

std::vector<int> prefix(const std::string& str) {
    int size = str.length();
    std::vector<int> pi(size, 0);

    for (int first = 1; first < size; ++first) {
        int second = pi[first - 1];
        while (second > 0 && str[first] != str[second]) {
            second = pi[second - 1];
        }
        if (str[first] == str[second]) {
            ++second;
        }
        pi[first] = second;
    }
    return pi;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str;
    std::cin >> str;
    std::vector<int> pi = prefix(str);
    int size = pi.size();
    for (int first = 0; first < size; ++first) {
        if (first > 0) std::cout << " ";
        std::cout << pi[first];
    }
    std::cout<< "\n";

    return 0;
}
