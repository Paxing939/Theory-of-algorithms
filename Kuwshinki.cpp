#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream reader("input.txt");
    int number;
    reader >> number;

    std::vector<int> vec(number, -1);
    for (auto &el : vec) {
        reader >> el;
    }

    std::ofstream writer("output.txt");
    std::vector<int> res(vec.size(), -1);

    res[0] = vec[0];
    res[2] = res[0] + vec[2];

    for (int i = 3; i < vec.size(); i++) {
        res[i] = std::max(res[i], res[i - 2] + vec[i]);
        res[i] = std::max(res[i], res[i - 3] + vec[i]);
    }
    writer << res.back() << '\n';

    return 0;
}
