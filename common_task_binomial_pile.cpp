#include <iostream>
#include <fstream>
#include <vector>

int main() {
    long long n = 0;

    std::ifstream reader("input.txt");
    reader >> n;

    std::vector<long long> answer;
    do {
        answer.push_back(n % 2);
        n /= 2;
    } while (n > 0);

    std::ofstream writer("output.txt");
    if (answer.empty()) {
        writer << -1;
        return 0;
    }

    long long i = 0;
    for (auto el : answer) {
        if (el == 1) {
            writer << i << '\n';
        }
        i++;
    }

    return 0;
}