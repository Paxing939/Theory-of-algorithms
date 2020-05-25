#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include <utility>
#include <iomanip>
#include <iostream>

struct Pair {
	int first;
	int second;
};

void PrintMatrix(const std::vector<std::vector<Pair>>& matrix) {
	for (const auto& vec : matrix) {
		for (const auto& x_ : vec) {
			std::cout << "(" << x_.first << ", " << x_.second << ") ";
		}
		std::cout << std::endl;
	}
}

//std::ostream operator<<(std::ostream out, Pair pair) {
//	out << "(" << pair.first << ", " << pair.second << ") ";
//}

int main() {
	std::ifstream reader("input.txt");
	std::ofstream writer("output.txt");

	int64_t infinity = std::numeric_limits<int32_t>::max() - 10;
	int64_t n;
	reader >> n;

	std::vector<int64_t> positions(n), time(n);
	std::vector<std::vector<Pair>> dp(n + 1, std::vector<Pair>(n));

	for (int64_t i = 0; i < n; ++i) {
		reader >> positions[i] >> time[i];
	}

//	for (int64_t k = 2; k < n * 2 + 2; k += 2) {
//		for (int64_t i = 0; i < n - k / 2; ++i) {
//			int64_t first = dp[k - 2][i] + positions[i + k / 2] - positions[i + k / 2 - 1];
//			int64_t second = dp[k - 1][i] + positions[i + k / 2] - positions[i];
//
//			dp[k][i] = std::min(first, second);
//			if (dp[k][i] > time[i + k / 2]) {
//				dp[k][i] = infinity;
//			}
//
//			first = dp[k - 2][i + 1] + positions[i + k / 2] - positions[i];
//			second = dp[k - 1][i + 1] + positions[i + 1] - positions[i];
//
//			dp[k + 1][i] = std::min(first, second);
//			if (dp[k + 1][i] > time[i]) {
//				dp[k + 1][i] = infinity;
//			}
//		}
//	}

	for (int64_t k = 1; k < n; k++) {
		for (int64_t i = 0; i < n - k; ++i) {
			int64_t first = dp[k - 1][i].first + positions[i + k] - positions[i + k - 1];
			int64_t second = dp[k - 1][i].second + positions[i + k] - positions[i];

			dp[k][i].first = std::min(first, second);
			if (dp[k][i].first > time[i + k]) {
				dp[k][i].first = infinity;
			}

			first = dp[k - 1][i + 1].first + positions[i + k] - positions[i];
			second = dp[k - 1][i + 1].second + positions[i + 1] - positions[i];

			dp[k + 1][i].second = std::min(first, second);
			if (dp[k + 1][i].second > time[i]) {
				dp[k + 1][i].second = infinity;
			}
		}
	}

	PrintMatrix(dp);
	int64_t result = std::min(dp[n - 1][0].first, dp[n - 2][0].second);
	if (result != infinity) {
		writer << result;
	} else {
		writer << "No solution";
	}

	return 0;
}
