#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <algorithm>

std::string MathsLesson(const std::string& test) {
	std::stringstream ss(test), out;

	int n;
	ss >> n;

	std::vector<int> numbers(n), sums_to_skip(200 * n);
	int current = 0, fill = 0;
	int i = 0, j = 0, sum = 0;
	ss >> sum;
	numbers[j] = sum / 2;
	out << numbers[j] << "\n";
	i++, j++;
	while (i < n * n) {
		if (j == n) {
			break;
		}

		ss >> sum;
		for (int k = current; k < fill; ++k) {
			if (sum == sums_to_skip[k]) {
				ss >> sum;
				current++;
			}
		}

		numbers[j] = sum - numbers[0];
		out << numbers[j] << '\n';
		j++;
		for (int k = 0; k < j; ++k) {
			sums_to_skip[fill] = numbers[j - 1] + numbers[k];
			fill++;
		}

		i++;
	}

	return out.str();
}

void MathsLesson() {
	int n;
	std::cin >> n;

	std::vector<int> numbers(n), sums_to_skip(200 * n);
	int current = 0, fill = 0;
	int i = 0, j = 0, sum = 0;
	std::cin >> sum;
	numbers[j] = sum / 2;
	std::cout << numbers[j] << "\n";
	i++, j++;
	while (i < n * n) {
		if (j == n) {
			break;
		}

		std::cin >> sum;
		for (int k = current; k < fill; ++k) {
			if (sum == sums_to_skip[k]) {
				std::cin >> sum;
				current++;
			}
		}

		numbers[j] = sum - numbers[0];
		std::cout << numbers[j] << '\n';
		j++;
		for (int k = 0; k < j; ++k) {
			sums_to_skip[fill] = numbers[j - 1] + numbers[k];
			fill++;
		}
		std::sort(sums_to_skip.begin(), sums_to_skip.end());

		i++;
	}
}

void Generator() {
	int n = 5, max_number = 5;
	srand(time(0));

	for (int i = 0; i < 100'000; ++i) {
		std::stringstream ss, true_answer;

		std::vector<int> numbers(n), sums(n * n);
		for (int j = 0; j < n; ++j) {
			numbers[j] = rand() % max_number + 1;
		}

		std::sort(numbers.begin(), numbers.end());
		for (int j = 0; j < n; ++j) {
			true_answer << numbers[j] << '\n';
		}

		ss << n << '\n';
		int ind = 0;
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				sums[ind++] = numbers[j] + numbers[k];
			}
		}
		std::sort(sums.begin(), sums.end());
		for (int j = 0; j < n * n; ++j) {
			ss << sums[j] << ' ';
		}

		std::string algorithm = MathsLesson(ss.str());

		if (true_answer.str() == algorithm) {
			std::cout << "Test #" << i + 1 << " completed successfully!\n";
		} else {
			std::cout << "Test #" << i + 1 << " failed!\n";
			std::ofstream writer("log.txt");
			writer << algorithm;
			writer << "-------------------------\n";
			writer << true_answer.str();
			writer << "-------------------------\n";
			writer << ss.str();
			return;
		}
	}
}

int main() {
//	Generator();

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	MathsLesson();
	return 0;
}