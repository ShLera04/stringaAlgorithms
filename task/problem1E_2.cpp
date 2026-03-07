#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> buildSuffixArray(const std::string& str) {
    int size = str.size();
    std::vector<int> sa(size), rank(size), temp(size);

    for (int index = 0; index < size; ++index) {
        sa[index] = index;
        rank[index] = str[index];
    }

    for (int first = 1; first < size; first *= 2) {
        auto cmp = [&](int ii, int jj) {
            if (rank[ii] != rank[jj]) {
                return rank[ii] < rank[jj];
            }
            int ri = (ii + first < size) ? rank[ii + first] : -1;
            int rj = (jj + first < size) ? rank[jj + first] : -1;
            return ri < rj;
        };

        sort(sa.begin(), sa.end(), cmp);

        temp[sa[0]] = 0;
        for (int second = 1; second < size; ++second) {
            temp[sa[second]] = temp[sa[second - 1]] + (cmp(sa[second - 1], sa[second]) ? 1 : 0);
        }
        rank = temp;
    }

    return sa;

}

std::vector<int> buildLCP(const std::string& str, const std::vector<int>& sa) {
    int size = str.size();
    std::vector<int> lcp(size, 0);
    std::vector<int> rank(size, 0);

    for (int index = 0; index < size; ++index) {
        rank[sa[index]] = index;
    }

    int kk = 0;
    for (int first = 0; first < size; ++first) {
        if (rank[first] == size - 1) {
            kk = 0;
            continue;
        }

        int second = sa[rank[first] + 1];
        while (first + kk < size && second + kk < size && str[first + kk] == str[second + kk]) {
            ++kk;
        }

        lcp[rank[first]] = kk;
        if (kk > 0) {
            --kk;
        }
    }

    return lcp;
}

bool check(const std::string& str, const std::vector<int>& sa,
    const std::vector<int>& lcp, int len, int& startPos) {
    int count = 0;
    int size = str.length();

    while (count < size) {
        if (lcp[count] < len) {
            ++count;
            continue;
        }

        int start = count;
        while (count  < size - 1 && lcp[count] >= len) {
            ++count;
        }

        int end = count;

        std::vector<int> poss;
        for (int index = start; index <= end; ++index) {
            poss.push_back(sa[index]);
        }
        sort(poss.begin(), poss.end());

        std::vector<int> validPoss;
        for (int pos : poss) {
            if (validPoss.empty() || pos - validPoss.back() >= len) {
                validPoss.push_back(pos);
                if (validPoss.size() >= 3) {
                    startPos = validPoss[0];
                    return true;
                }
            }
        }
        ++count;
    }

    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str;
    std::cin >> str;

    int str_len = str.size();

    std::vector<int> sa = buildSuffixArray(str);
    std::vector<int> lcp = buildLCP(str, sa);

    int left = 1, right = str_len / 3;
    int bestLen = 0;
    int bestPos = 0;

    while (left <= right) {
        int mid = (left + right) / 2;
        int pos;

        if (check(str, sa, lcp, mid, pos)) {
            bestLen = mid;
            bestPos = pos;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    std::cout << str.substr(bestPos, bestLen) << "\n";

    return 0;
}
