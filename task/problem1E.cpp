#include <iostream>
#include <string>
#include <vector>

bool check(const std::string& str, int start, int len) {
    std::string pattern = str.substr(start, len);
    int count = 0;
    int pos = 0;
    int size = str.length();

    while (pos <= size - len) {
        int found = str.find(pattern, pos);
        if (found == std::string::npos) {
            break;
        }
        ++count;
        pos = found + len;
        if (count >= 3) {
            return true;
        }
    }

    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str;
    std::cin >> str;
    int str_len = str.length();
    std::string ans = "";
    int left = 1, right = str_len / 3;

    while (left <= right) {
        int mid = (left + right) / 2;
        bool found = false;
        std::string cur_ans = "";

        for (int index = 0; index <= str_len - mid; ++index) {
            if (check(str, index, mid)) {
                found = true;
                cur_ans = str.substr(index, mid);
                break;
            }
        }

        if (found) {
            ans = cur_ans;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    std::cout << ans << "\n";

    return 0;
}
