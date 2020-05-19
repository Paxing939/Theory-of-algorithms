#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <set>
#include <map>

std::string ReadWholeFile(std::string filename) {
    std::ifstream ifs(filename);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    return content;
}

struct Index {
    int index;
};

std::vector<int> numbers, sum_amounts;

bool operator<(const Index &lhs, const Index &rhs) {
    int left = numbers[lhs.index] + numbers[sum_amounts[lhs.index]];
    int right = numbers[rhs.index] + numbers[sum_amounts[rhs.index]];

    return left <= right;
}

class MathsLesson {
public:

    void MathsLesson3() {
	    std::ifstream reader("input.txt");
	    std::ofstream writer("output.txt");

        std::multiset<Index> set, set2;

        reader >> n;

        numbers.resize(n, -1);
        for (int i = 0; i < n; i++) {
            numbers[i] = 100 + 10 * i;
        }
        sum_amounts.resize(n, -1);

        int i = 0, sum = 0, p = 0;
        reader >> sum;

        if (n == 1) {
            writer << sum / 2 << '\n';
            return;
        }

        numbers[i] = sum / 2;
        sum_amounts[i] = 1;
        writer << numbers[i] << "\n";
        set.insert({0});
        i++;
        while (i < n - 1) {
            reader >> sum;

            if (sum_amounts[set.begin()->index] >= i ||
                numbers[set.begin()->index] + numbers[sum_amounts[set.begin()->index]] > sum || set.empty()) {
                numbers[i] = sum - numbers[0];
                writer << numbers[i] << '\n';
                sum_amounts[i] = 1;
                set.insert({i});
                i++;
                while (!set2.empty()) {
                    int top = set2.begin()->index;
                    set2.erase(set2.begin());
                    set.insert({top});
                }
            } else {
                int min = set.begin()->index;
                set.erase(set.begin());
                sum_amounts[min]++;
                if (sum_amounts[min] < i) {
                    set.insert({min});
                } else {
                    set2.insert({min});
                }
            }
            p++;
        }

        for (int k = p; k < n * n; ++k) {
            reader >> sum;
        }

        writer << sum / 2 << '\n';

        numbers.clear();
        sum_amounts.clear();
    }

    void MathsLesson3(int k, const std::vector<int> &sums) {
        n = k;
        std::multiset<Index> set, set2;

        numbers.resize(n, -1);
//		for (int i = 0; i < n; i++) {
//			numbers[i] = 100 + 10 * i;
//		}
        sum_amounts.resize(n, -1);

        int i = 0, sum = 0, p = 0;
        sum = sums[0];

        if (n == 1) {
            numbers[0] = sum;
        }

        numbers[i] = sum / 2;
        sum_amounts[i] = 1;
        set.insert({0});
        i++;
        while (i < n - 1) {
            sum = sums[i];

            if (sum_amounts[set.begin()->index] >= i ||
                numbers[set.begin()->index] + numbers[sum_amounts[set.begin()->index]] > sum || set.empty()) {
                numbers[i] = sum - numbers[0];
                sum_amounts[i] = 1;
                set.insert({i});
                i++;
                while (!set2.empty()) {
                    int top = set2.begin()->index;
                    set2.erase(set2.begin());
                    set.insert({top});
                }
            } else {
                int min = set.begin()->index;
                set.erase(set.begin());
                sum_amounts[min]++;
                if (sum_amounts[min] < i) {
                    set.insert({min});
                } else {
                    set2.insert({min});
                }
            }
            p++;
        }

        numbers[numbers.size() - 1] = sums[sums.size() - 1] / 2;

        numbers.clear();
        sum_amounts.clear();
    }

private:
    int n{};
};

void Generator() {
    srand(time(0));

    for (int i = 0; i < 10'000'000; ++i) {
	    int n = rand() % 1500 + 1, start_number = 1, max_number = 1'000'000;
        std::stringstream true_answer;

        std::vector<int> numbers_to_test(n), sums(n * n);
        for (int j = 0; j < n; ++j) {
            numbers_to_test[j] = start_number + rand() % max_number;
        }

        std::sort(numbers_to_test.begin(), numbers_to_test.end());
        for (int j = 0; j < n; ++j) {
            true_answer << numbers_to_test[j] << '\n';
        }

        int ind = 0;
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                sums[ind++] = numbers_to_test[j] + numbers_to_test[k];
            }
        }

        std::ofstream writer("input.txt");
        writer << n << std::endl;

        std::sort(sums.begin(), sums.end());
        for (int j = 0; j < n * n; ++j) {
            writer << sums[j] << ' ';
        }
        writer.close();

        MathsLesson maths_lesson;
        maths_lesson.MathsLesson3();

        std::string algorithm = ReadWholeFile("output.txt");

        if (true_answer.str() == algorithm) {
            std::cout << "Test #" << i + 1 << " completed successfully!\n";
        } else {
            std::cout << "Test #" << i + 1 << " failed!\n";
            std::ofstream writer("tst.out");
            writer << algorithm;
            writer << "-------------------------\n";
            writer << true_answer.str();
            writer << "-------------------------\n";
            writer << ReadWholeFile("input.txt");
            writer.close();
            return;
        }
    }
}

void Generator2() {
    int n = rand() % 1500 + 1, start_number = 1, max_number = 1'000'000;
    srand(time(0));
while (true)
    for (int i = 0; i < 10'000'000; ++i) {
        std::vector<int> numbers_to_test(n), sums(n * n);
        for (int j = 0; j < n; ++j) {
            numbers_to_test[j] = start_number + rand() % max_number;
        }

        std::sort(numbers_to_test.begin(), numbers_to_test.end());

        int ind = 0;
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                sums[ind++] = numbers_to_test[j] + numbers_to_test[k];
            }
        }
        std::sort(sums.begin(), sums.end());

        MathsLesson maths_lesson;
        maths_lesson.MathsLesson3(n, sums);

        for (int j = 0; j < n; ++j) {
            if (numbers_to_test[i] != numbers[i]) {
                std::cout << "Test #" << i + 1 << " failed!\n";
                std::ofstream writer("log.txt");
                for (auto &el : numbers) {
                    writer << el << '\n';
                }
                writer << "-------------------------\n";
                for (auto &el : numbers_to_test) {
                    writer << el << '\n';
                }
                writer << "-------------------------\n";
                writer << n << '\n';
                for (auto &el : sums) {
                    writer << el << ' ';
                }
                writer.close();
                return;
            }
        }
        std::cout << "Test #" << i + 1 << " completed successfully!\n";
    }
}

int main() {
//	Generator();
    MathsLesson maths_lesson;
    maths_lesson.MathsLesson3();

    return 0;
}