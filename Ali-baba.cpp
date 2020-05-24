#include <cmath>
#include <algorithm>
#include <fstream>

int main() {
    std::ifstream reader("input.txt");
    std::ofstream writer("output.txt");

    int64_t infinity = std::numeric_limits<int64_t>::max() - 10;
    int64_t n;
    reader >> n;

    std::vector<int64_t> positions(n), time(n);
    std::vector<std::vector<int64_t>> dp(n * 2, std::vector<int64_t>(n));

    for (int64_t i = 0; i < n; ++i) {
        reader >> positions[i] >> time[i];
    }

    for (int64_t k = 2; k < n * 2 + 2; k += 2) {
        for (int64_t i = 0; i < n - k / 2; ++i) {
            int64_t first = dp[k - 2][i] + positions[i + k / 2] - positions[i + k / 2 - 1];
            int64_t second = dp[k - 1][i] + positions[i + k / 2] - positions[i];

            dp[k][i] = std::min(first, second);
            if (dp[k][i] > time[i + k / 2]) {
                dp[k][i] = infinity;
            }

            first = dp[k - 2][i + 1] + positions[i + k / 2] - positions[i];
            second = dp[k - 1][i + 1] + positions[i + 1] - positions[i];

            dp[k + 1][i] = std::min(first, second);
            if (dp[k + 1][i] > time[i]) {
                dp[k + 1][i] = infinity;
            }
        }
    }

    int64_t result = std::min(dp[n * 2 - 2][0], dp[n * 2 - 1][0]);
    if (result != infinity) {
        writer << result;
    } else {
        writer << "No solution";
    }

    return 0;
}
