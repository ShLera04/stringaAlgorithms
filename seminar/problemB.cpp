#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> reconstructFromZ(const std::vector<int>& zFunc) {
    int size = zFunc.size();
    if (size == 0) return {};
    std::vector<int> pi(size, 0);

    for (int index = 1; index < size; ++index) {
        if (zFunc[index] > 0) {
            int lastPos = index + zFunc[index] - 1;
            if (lastPos < size) {
                pi[lastPos] = std::max(pi[lastPos], zFunc[index]);
            }
        }
    }
    for (int index = size - 2; index >= 0; --index) {
        pi[index] = std::max(pi[index], pi[index + 1] - 1);
    }

    return pi;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int size;
    std::cin >> size;
    std::vector<int> zFunc(size);
     for (int index = 0; index < size; ++index) {
        std::cin >> zFunc[index];
    }

    std::vector<int> pi = reconstructFromZ(zFunc);

    for (int index = 0; index < size; ++index) {
        if (index > 0) std::cout << " ";
        std::cout << pi[index];
    }
    std::cout<< "\n";

    return 0;
}
