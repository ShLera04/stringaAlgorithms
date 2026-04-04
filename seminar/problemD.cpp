#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int getOverlap(const std::string& aa, const std::string& bb) {
    int n1 = aa.size();
    int n2 = bb.size();
    for (int len = std::min(n1, n2); len > 0; --len) {
        if (aa.compare(n1 - len, len, bb, 0, len) == 0) {
            return len;
        }
    }
    return 0;
}

std::vector<std::string> filterSubstrings(const std::vector<std::string>& raw_s) {
    int size = raw_s.size();
    std::vector<std::string> filtered;
    for (int index = 0; index < size; ++index) {
        bool is_redundant = false;
        for (int jndex = 0; jndex < size; ++jndex) {
            if (index == jndex) {
                continue;
            }
            if (raw_s[jndex].find(raw_s[index]) != std::string::npos) {
                if (raw_s[index].length() < raw_s[jndex].length() || index > jndex) {
                    is_redundant = true;
                    break;
                }
            }
        }
        if (!is_redundant) {
            filtered.push_back(raw_s[index]);
        }
    }
    return filtered;
}

std::vector<std::vector<int>> precomputeOverlaps(const std::vector<std::string>& str) {
    int size = str.size();
    std::vector<std::vector<int>> overlap(size, std::vector<int>(size));
    for (int index = 0; index < size; ++index) {
        for (int jndex = 0; jndex < size; ++jndex) {
            if (index != jndex) {
                overlap[index][jndex] = getOverlap(str[index], str[jndex]);
            }
        }
    }
    return overlap;
}

std::string solveSCS(const std::vector<std::string>& str) {
    int size = str.size();
    if (size == 0) {
        return "";
    }
    
    auto overlaps = precomputeOverlaps(str);
    
    std::vector<std::vector<std::string>> dp(1 << size, std::vector<std::string>(size, ""));

    for (int index = 0; index < size; ++index) {
        dp[1 << index][index] = str[index];
    }

    for (int mask = 1; mask < (1 << size); ++mask) {
        for (int index = 0; index < size; ++index) {
            if (dp[mask][index].empty()) {
                continue;
            }
            for (int jndex = 0; jndex < size; ++jndex) {
                if (!(mask & (1 << jndex))) {
                    int next_mask = mask | (1 << jndex);
                    std::string next_s = dp[mask][index] + str[jndex].substr(overlaps[index][jndex]);

                    if (dp[next_mask][jndex].empty() || 
                        next_s.length() < dp[next_mask][jndex].length() ||
                        (next_s.length() == dp[next_mask][jndex].length() && next_s < dp[next_mask][jndex])) {
                        dp[next_mask][jndex] = std::move(next_s);
                    }
                }
            }
        }
    }

    std::string result;
    int final_mask = (1 << size) - 1;
    for (int index = 0; index < size; ++index) {
        if (dp[final_mask][index].empty()) {
            continue;
        }
        if (result == "" || 
            dp[final_mask][index].length() < result.length() ||
            (dp[final_mask][index].length() == result.length() && dp[final_mask][index] < result)) {
            result = dp[final_mask][index];
        }
    }
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int size;
    if (!(std::cin >> size)) {
        return 0;
    }

    std::vector<std::string> raw_s(size);
    for (int index = 0; index < size; ++index) {
        std::cin >> raw_s[index];
    }

    std::vector<std::string> filtered = filterSubstrings(raw_s);

    std::string answer = solveSCS(filtered);

    std::cout << answer << "\n";

    return 0;
}
