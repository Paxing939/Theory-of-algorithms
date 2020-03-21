#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

int main() {
    std::ifstream reader("input.txt");
    int n = 0;
    std::cin >> n;
    std::vector<int> dp(n, 1), rec(n, -1), a(n), line;
    for (auto &el : a) {
        std::cin >> el;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] == 0) {
                continue;
            }
            if (a[i] % a[j] == 0 || a[i] == 0) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    rec[i] = j;
                }
            }
        }
    }

    int answer = dp[0], index = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] > answer) {
            answer = dp[i];
            index = i;
        }
    }
    std::cout << answer << std::endl;

    while (index != -1) {
        line.push_back(index + 1);
        index = rec[index];
    }

    reverse(line.begin(), line.end());

    for (int i : line) {
        std::cout << i << " ";
    }
}