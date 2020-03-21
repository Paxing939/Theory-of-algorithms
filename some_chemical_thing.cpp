#include <iostream>
#include <vector>
#include <fstream>

int main() {
    int n = 0, m = 0;

    std::ifstream reader("input.txt");
    reader >> n >> m;

    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
    int tmp = 0;
    for (int i  = 0; i < n; i++) {
        for (int j  = 0; j < n; j++) {
            reader >> tmp;
            matrix[i][j] = tmp;
        }
    }

    std::vector<int> elements(m);
    for (int i = 0; i < m; i++) {
        reader >> tmp;
        elements[i] = tmp;
    }

    std::vector<int> d(8, 1), a = {5, 2, 3, 12, 25, 24, 125, 120};
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (a[i] % a[j] == 0) {
                d[i] = std::max(d[i], 1 + d[j]);
            }
        }
    }

    int ans = d[0];
    for (int i = 0; i < n; ++i) {
        std::cout << d[i] << " ";
        ans = std::max(ans, d[i]);
    }
    std::cout << std::endl << ans << std::endl;

    return 0;
}