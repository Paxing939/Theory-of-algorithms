#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <algorithm>

bool Comparator(int a, int b) {
	return a > b;
}

class Heap {
public:

	void push(int value) {
		int i = heap.size() - 1;

		while (i > 0) {
			int j = (i - 1) / 2;
			if (heap[j].first < heap[i].first) {
				break;
			}
			if (heap[j].first == heap[i].first) {

				break;
			}
			std::swap(heap[j], heap[i]);
			i = j;
		}
	}

	void pop() {

	}

	int top() {
		return heap[0].first;
	}

private:
	std::vector<std::pair<int, int>> heap;
};

std::string MathsLesson(const std::string &test) {
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

	std::vector<int> numbers(n);
	std::vector<int> heap;

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
		while (true) {
			if (!heap.empty()) {
				if (sum == heap[0]) {
					std::cin >> sum;
					pop_heap(heap.begin(), heap.end(), Comparator);
					heap.pop_back();
				} else {
					if (sum > heap[0]) {
						pop_heap(heap.begin(), heap.end(), Comparator);
						heap.pop_back();
					} else {
						break;
					}
				}
			} else {
				break;
			}
		}

		numbers[j] = sum - numbers[0];
		std::cout << numbers[j] << '\n';
		j++;
		for (int k = 0; k < j; ++k) {
			heap.push_back(numbers[j - 1] + numbers[k]);
			push_heap(heap.begin(), heap.end(), Comparator);
			if (k != j - 1) {
				heap.push_back(numbers[k] + numbers[j - 1]);
				push_heap(heap.begin(), heap.end(), Comparator);
			}
		}

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

//  std::priority_queue<int, std::vector<int>, std::greater<>> pq;
//
//  pq.push(1);
//  pq.push(2);
//  pq.push(2);
//  pq.push(3);
//  pq.push(4);
//  pq.push(5);
//
//  for (int i = 0; i < 6; ++i) {
//    std::cout << pq.top() << " ";
//    pq.pop();
//  }

	return 0;
}