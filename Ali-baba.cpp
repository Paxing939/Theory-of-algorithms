#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	std::cin.tie(nullptr);
	std::ios_base::sync_with_stdio(false);

	int64_t infinity = std::numeric_limits<int32_t>::max(), n;
	std::cin >> n;

	std::vector<int64_t> positions(n), time(n);
	std::vector<std::vector<std::pair<int64_t, int64_t>>> dp(n, std::vector<std::pair<int64_t, int64_t>>(n));

	for (int64_t i = 0; i < n; ++i) {
		std::cin >> positions[i] >> time[i];
	}

	for (int64_t k = 1; k < n; k++) {
		for (int64_t i = 0; i < n - k; i++) {

			dp[k][i].first = std::min(dp[k - 1][i].first + positions[i + k] - positions[i + k - 1],
			                          dp[k - 1][i].second + positions[i + k] - positions[i]);
			if (dp[k][i].first > time[i + k]) {
				dp[k][i].first = infinity;
			}

			dp[k][i].second = std::min(dp[k - 1][i + 1].first + positions[i + k] - positions[i],
			                           dp[k - 1][i + 1].second + positions[i + 1] - positions[i]);
			if (dp[k][i].second > time[i]) {
				dp[k][i].second = infinity;
			}
		}
	}

	int64_t result = std::min(dp[n - 1][0].first, dp[n - 1][0].second);
	if (result != infinity) {
		std::cout << result;
	} else {
		std::cout << "No solution";
	}

	return 0;
}
