#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> reconstructFromPrefix(const std::vector<int>& pi) {
    int size = pi.size();
    std::vector<int> zFunc(size, 0);
    zFunc[0] = size;

    for (int index = 1; index < size; ++index) {
        if (pi[index] > 0) {
            int startPos = index - pi[index] + 1;
            zFunc[startPos] = std::max(zFunc[startPos], pi[index]);
        }
    }
    int left = 0, right = 0;
    for (int index = 1; index < size; ++index) {
        if (left <= right) {
            zFunc[index] = std::max(zFunc[index], std::min(zFunc[index - left], right - index + 1));
        }
        if (index + zFunc[index] - 1 > right) {
            left = index;
            right = index + zFunc[index] - 1;
        }
    }

    return zFunc;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int size;
    std::cin >> size;
    std::vector<int> pi(size);
     for (int index = 0; index < size; ++index) {
        std::cin >> pi[index];
    }

    std::vector<int> zFunc = reconstructFromPrefix(pi);

    for (int index = 0; index < size; ++index) {
        if (index > 0) std::cout << " ";
        std::cout << zFunc[index];
    }
    std::cout<< "\n";

    return 0;
}
