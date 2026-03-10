#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

                                                                                                                                        std::string pattern, text;
                                                                                                                                            std::cin >> pattern >> text;
                                                                                                                                                int patternLen = pattern.length();
                                                                                                                                                    int textLen = text.length();

                                                                                                                                                        
                                                                                                                                                            std::vector<int> z_values1 = z_function(pattern + "#" + text);

                                                                                                                                                                std::string patternRev = pattern;
                                                                                                                                                                    std::reverse(patternRev.begin(), patternRev.end());
                                                                                                                                                                        std::string textRev = text;
                                                                                                                                                                            std::reverse(textRev.begin(), textRev.end());

                                                                                                                                                                                std::vector<int> z_values2 = z_function(patternRev + "#" + textRev);

                                                                                                                                                                                    std::vector<int> results;
                                                                                                                                                                                        for (int index = 0; index <= textLen - patternLen; ++index) {
                                                                                                                                                                                                int left = z_values1[patternLen + 1 + index];
                                                                                                                                                                                                        int right = z_values2[patternLen + 1 + (textLen - patternLen - index)];
                                                                                                                                                                                                                if (left + right >= patternLen - 1) {
                                                                                                                                                                                                                            results.push_back(index + 1);
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                        }

                                                                                                                                                                                                                                            int resultsSize = results.size();
                                                                                                                                                                                                                                                std::cout << resultsSize << "\n";


                                                                                                                                                                                                                                                    for (int index = 0; index < resultsSize; ++index) {
                                                                                                                                                                                                                                                            if (index > 0) std::cout << " ";
                                                                                                                                                                                                                                                                    std::cout << results[index];
                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                            std::cout<< "\n";

                                                                                                                                                                                                                                                                                return 0;
                                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                                