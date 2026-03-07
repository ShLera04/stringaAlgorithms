// // #include <iostream>
// // #include <string>
// // #include <vector>

// // std::vector<int> prefix(const std::string& str) {
// //     int size = str.length();
// //     std::vector<int> pi(size, 0);

// //     for (int first = 1; first < size; ++first) {
// //         int second = pi[first - 1];
// //         while (second > 0 && str[first] != str[second]) {
// //             second = pi[second - 1];
// //         }
// //         if (str[first] == str[second]) {
// //             ++second;
// //         }
// //         pi[first] = second;
// //     }
// //     return pi;
// // }

// // int main() {
// //     std::ios_base::sync_with_stdio(false);
// //     std::cin.tie(nullptr);

// //     std::string str;
// //     std::cin >> str;
// //     std::vector<int> pi = prefix(str);
// //     int size = pi.size();

// //     int period = size - pi[size - 1];
// //     if (size % period == 0) {
// //         std::cout << size / period << "\n";
// //     } else {
// //         std::cout << 1 << "\n";
// //     }

// //     return 0;
// // }
// #include <iostream>
// #include <string>
// #include <vector>

// std::vector<int> prefix(const std::string& str) {
//     int size = str.length();
//     std::vector<int> pi(size, 0);

//     for (int first = 1; first < size; ++first) {
//         int second = pi[first - 1];
//         while (second > 0 && str[first] != str[second]) {
//             second = pi[second - 1];
//         }
//         if (str[first] == str[second]) {
//             ++second;
//         }
//         pi[first] = second;
//     }
//     return pi;
// }

// std::string reconstructFromZ(const std::vector<int>& zFunc) {
//     int size = zFunc.size();
//     std::string str(size, 'a');

//     int left = 0, right = 0;
//     char nextChar = 'b';

//     for (int first = 0; first < size; ++first) {
//         if (first < right) {
//             str[first] = str[first-left];
//         }
//         if (first + zFunc[first] > right) {
//             for (int second = std::max(0, right - first); second <zFunc[first] && first + second < size; ++second) {
//                 str[first + second] = str[second];
//             }
//             left = first;
//             right = first + zFunc[first];
//         }
//         if (zFunc[first] == 0 && str[first] == str[0]) {
//             str[first] = nextChar++;
//         }
//     }
//     return str;
// }

// int main() {
//     std::ios_base::sync_with_stdio(false);
//     std::cin.tie(nullptr);

//     int size;
//     std::cin >> size;
//     std::vector<int> zFunc(size);
//      for (int index = 0; index < size; ++index) {
//         std::cin >> zFunc[index];
//     }

//     std::string str = reconstructFromZ(zFunc);
//     std::vector<int> pi = prefix(str);

//     for (int index = 0; index < size; ++index) {
//         if (index > 0) std::cout << " ";
//         std::cout << pi[index];
//     }
//     std::cout<< "\n";

//     return 0;
// }
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Оптимизация ввода-вывода
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> z(n);
    vector<int> p(n, 0);

    for (int i = 0; i < n; ++i) {
        cin >> z[i];
    }

    // Заполняем префикс-функцию на основе Z-функции
    // Если z[i] = k, то префикс длины k начинается в i.
    // Значит, p[i + k - 1] как минимум k.
    for (int i = 1; i < n; ++i) {
        if (z[i] > 0) {
            // Мы обновляем только правую границу совпадения
            p[i + z[i] - 1] = max(p[i + z[i] - 1], z[i]);
        }
    }

    // Проход справа налево для заполнения промежуточных значений.
    // Если на позиции j значение p[j] = k, то на позиции j-1 
    // значение p[j-1] должно быть как минимум k-1.
    for (int i = n - 2; i >= 0; --i) {
        p[i] = max(p[i], p[i + 1] - 1);
    }

    for (int i = 0; i < n; ++i) {
        cout << p[i] << (i == n - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Преобразует Z-функцию в префикс-функцию за O(N).
 * @param z Входной вектор с Z-функцией.
 * @return Вектор с префикс-функцией.
 */
vector<int> convertZtoP(const vector<int>& z) {
    int n = z.size();
    if (n == 0) return {};
    
    vector<int> p(n, 0);

    // Этап 1: Переносим значения Z-функции в конечные точки префиксов
    for (int i = 1; i < n; ++i) {
        if (z[i] > 0) {
            int last_pos = i + z[i] - 1;
            p[last_pos] = max(p[last_pos], z[i]);
        }
    }

    // Этап 2: Распространяем значения справа налево (деградация длины)
    for (int i = n - 2; i >= 0; --i) {
        p[i] = max(p[i], p[i + 1] - 1);
    }

    return p;
}

/**
 * Вспомогательная функция для вывода вектора в поток.
 */
void printVector(const vector<int>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << (i == vec.size() - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    // Ускоряем ввод и вывод
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> z(n);
    for (int i = 0; i < n; ++i) {
        cin >> z[i];
    }

    // Вычисляем результат
    vector<int> p = convertZtoP(z);

    // Выводим результат
    printVector(p);

    return 0;
}