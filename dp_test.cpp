#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

int main() {
    int n = 0;
    std::ifstream reader("input.txt");
    reader >> n;

    std::vector<int> d(n, 1), a(n);
    for (auto& el : a) {
        reader >> el;
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (a[j] == 0) {
                continue;
            }
            if (a[i] % a[j] == 0 || a[i] == 0) {
                d[i] = std::max(d[i], 1 + d[j]);
            }
        }
    }

    int ans = d[0], max_ind = 0;
    for (int i = 0; i < n; ++i) {
        ans = std::max(ans, d[i]);
        max_ind = i;
    }
    std::cout << ans << '\n';

    std::vector<int> answer;
    int ind_diff = 1;
    for (int i = max_ind - 1; i >= 0; --i) {
        if (a[max_ind] % a[i] == 0 && d[max_ind] - d[i] == ind_diff) {
            answer.push_back(i + 1);
            ind_diff++;
//            std::cout << i + 1 << " ";
        }
    }

    std::reverse(answer.begin(), answer.end());

    for (const auto& el : answer) {
        std::cout << el << " ";
    }
std::cout << '\n';
    for (const auto& el : d) {
        std::cout << el << " ";
    }

    return 0;
}