#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream reader("input.txt");
    int number;
    reader >> number;

    std::vector<std::vector<int>> vec(number, std::vector<int>(2));
    for (auto &el : vec) {
        int a1, a2;
        reader >> a1 >> a2;
        el[0] = a1, el[1] = a2;
    }

    std::vector<std::vector<int>> vec2(number, std::vector<int>(number, 0));

    for (int i = 1; i < number; i++) {
        for (int j = 0; j < number && j + i < number; j++) {
            vec2[j][j + i] = INT32_MAX;
            for (int k = j; k < j + i; k++) {
                vec2[j][j + i] = std::min(vec2[j][j + i],
                                          vec2[j][k] + vec2[k + 1][j + i] + vec[j][0] * vec[j + i][1] * vec[k][1]);
            }
        }
    }

    std::ofstream writer("output.txt");

    writer << vec2[0].back() << '\n';

    return 0;
}

