#include <iostream>
#include <vector>
#include <fstream>

int main() {
    int n = 0;

    std::ifstream reader("input.txt");
    reader >> n;

    std::vector<int> vector(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        reader >> vector[i];
    }

    std::string answer = "Yes";
    for (int i = 1; i <= n / 2; i++) {
        if (2 * i < n + 1) {
            if (vector[i] > vector[2 * i]) {
                answer = "No";
                break;
            }
        }
        if (2 * i + 1 < n + 1) {
            if (vector[i] > vector[2 * i + 1]) {
                answer = "No";
                break;
            }
        }
    }

    std::ofstream writer("output.txt");
    writer << answer;

    return 0;
}