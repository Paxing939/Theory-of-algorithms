#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <set>
#include <queue>

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

bool operator==(const Index &lhs, const Index &rhs) {
    int left = numbers[lhs.index] + numbers[sum_amounts[lhs.index]];
    int right = numbers[rhs.index] + numbers[sum_amounts[rhs.index]];
    return left == right;
}

bool operator!=(const Index &lhs, const Index &rhs) {
    int left = numbers[lhs.index] + numbers[sum_amounts[lhs.index]];
    int right = numbers[rhs.index] + numbers[sum_amounts[rhs.index]];
    return left != right;
}

bool operator<(const Index &lhs, const Index &rhs) {
    int left = numbers[lhs.index] + numbers[sum_amounts[lhs.index]];
    int right = numbers[rhs.index] + numbers[sum_amounts[rhs.index]];
    if (numbers[sum_amounts[lhs.index]] == -1) {
        left = numbers[lhs.index] + numbers[sum_amounts[lhs.index]] + 100;
    }
    if (numbers[sum_amounts[rhs.index]] == -1) {
        right = numbers[rhs.index] + numbers[sum_amounts[rhs.index]] + 100;
    }
    //   if (left == right)
    //       return lhs.index < rhs.index;

    return left < right;
}

bool operator>(const Index &lhs, const Index &rhs) {
    int left = numbers[lhs.index] + numbers[sum_amounts[lhs.index]];
    int right = numbers[rhs.index] + numbers[sum_amounts[rhs.index]];
    if (numbers[sum_amounts[lhs.index]] == -1) {
        left = numbers[lhs.index] + numbers[sum_amounts[lhs.index]] + 100;
    }
    if (numbers[sum_amounts[rhs.index]] == -1) {
        right = numbers[rhs.index] + numbers[sum_amounts[rhs.index]] + 100;
    }
    //   if (left == right)
    //       return lhs.index < rhs.index;

    return left > right;
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
            writer << sum;
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

private:
    int n{};
};

void Generator() {
    int n = 1500, start_number = 1, max_number = 15;
    srand(time(0));

    for (int i = 0; i < 1'000'000; ++i) {
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

int main() {
//  Generator();
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    MathsLesson maths_lesson;
    maths_lesson.MathsLesson3();


    return 0;
}
