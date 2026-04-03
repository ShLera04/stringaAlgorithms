#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const int kAlphabetSize = 256;

void SortInitial(const std::string& str, std::vector<int>* pos,
                 std::vector<int>* classes, int* cl) {
    int len = static_cast<int>(str.length());
    std::vector<int> cnt(std::max(kAlphabetSize, len), 0);
    for (int index = 0; index < len; ++index) {
        cnt[static_cast<unsigned char>(str[index])]++;
    }
    for (int index = 1; index < kAlphabetSize; ++index) {
        cnt[index] += cnt[index - 1];
    }
    for (int index = 0; index < len; ++index) {
        (*pos)[--cnt[static_cast<unsigned char>(str[index])]] = index;
    }
    (*classes)[(*pos)[0]] = 0;
    *cl = 1;
    for (int index = 1; index < len; ++index) {
        if (str[(*pos)[index]] != str[(*pos)[index - 1]]) {
            ++(*cl);
        }
        (*classes)[(*pos)[index]] = (*cl) - 1;
    }
}

std::string BuildBwt(std::string str) {
    int len = static_cast<int>(str.length());
    std::vector<int> pos(len);
    std::vector<int> classes(len);
    int cl = 0;
    SortInitial(str, &pos, &classes, &cl);
    std::vector<int> pn(len);
    std::vector<int> cn(len);
    std::vector<int> cnt(std::max(kAlphabetSize, len));
    for (int step = 0; (1 << step) < len; ++step) {
        for (int index = 0; index < len; ++index) {
            pn[index] = (pos[index] - (1 << step) + len) % len;
        }
        std::fill(cnt.begin(), cnt.begin() + cl, 0);
        for (int index = 0; index < len; ++index) {
            cnt[classes[pn[index]]]++;
        }
        for (int index = 1; index < cl; ++index) {
            cnt[index] += cnt[index - 1];
        }
        for (int index = len - 1; index >= 0; --index) {
            pos[--cnt[classes[pn[index]]]] = pn[index];
        }
        cn[pos[0]] = 0;
        cl = 1;
        for (int index = 1; index < len; ++index) {
            std::pair<int, int> cur = {
                classes[pos[index]], classes[(pos[index] + (1 << step)) % len]};
            std::pair<int, int> prev = {
                classes[pos[index - 1]],
                classes[(pos[index - 1] + (1 << step)) % len]};
            if (cur != prev) {
                ++cl;
            }
            cn[pos[index]] = cl - 1;
        }
        classes = cn;
    }
    std::string result;
    result.reserve(len);
    for (int index = 0; index < len; ++index) {
        result += str[(pos[index] + len - 1) % len];
    }
    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string alpha;
    if (!(std::cin >> alpha)) {
        return 0;
    }
    if (alpha.length() == 1) {
        std::cout << alpha << "\n";
    } else {
        std::cout << BuildBwt(alpha) << "\n";
    }
    return 0;
}
