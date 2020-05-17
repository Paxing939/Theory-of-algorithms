#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <iomanip>

template<typename T>
void PrintMatrix(const std::vector<std::vector<T>>& matrix) {
    for (const auto& vec : matrix) {
        for (const auto& x_ : vec) {
            std::cout << std::setw(7) << std::setprecision(2) << std::left << x_ << " ";
        }
        std::cout << std::endl;
    }
}

class Polygon {
public:
    Polygon(long long number, std::ifstream &in) : minimum(INT64_MAX), index_minimum(-1), numbers(number),
                                                   operations(number), n(number) {
        for (int i = 0; i < number; ++i) {
            in >> operations[i] >> numbers[i];
        }
    }

    Polygon(const std::vector<long long> &nums, const std::vector<char> &operations)
            : numbers(nums), operations(operations) {}

    void AddVertex(char operation, long long number) {
        if (number < minimum) {
            minimum = number;
            index_minimum = numbers.size();
        }
        numbers.push_back(number);
        operations.push_back(operation);
    }

    std::pair<long long, std::vector<int>> Find() {
//        n = 4;
//        numbers = {-7, 4, 2, 5};
//        operations = {'t', 't', 'x', 'x'};
        n = operations.size();
        std::vector<char> op(2 * n - 1);
        for (int i = 0, j = 1; i < 2 * n - 1; ++i, ++j) {
            op[i] = operations[j];
            if (j == n - 1) {
                j = -1;
            }
        }

        std::vector<std::vector<long long>> dp(2 * n - 1, std::vector<long long>(2 * n - 1, 0));
        for (int i = 0, j = 0; i < 2 * n - 1; ++i, ++j) {
            dp[i][i] = numbers[j];
            if (j == n - 1) {
                j = -1;
            }
        }
        long long max, min;
        for (int i = 0; i < 2 * n - 1; ++i) {
            for (int j = 0; j < 2 * n - 1 - i; ++j) {
                int m = j + i;

//                if (j > n && m > n) {
//                    continue;
//                }
                if (m - n >= j) {
                    continue;
                }

                max = -INT64_MAX, min = INT64_MAX;
                bool assign = false;
                for (int k = j; k < m; ++k) {
                    assign = true;
                    switch (op[k]) {
                        case 't': {
                            max = std::max<long long>(max, dp[j][k] + dp[k + 1][m]);
                            min = std::min<long long>(min, dp[k][j] + dp[m][k + 1]);
                            break;
                        }
                        case 'x': {
                            max = std::max<long long>(max, std::max(dp[j][k] * dp[k + 1][m],
                                                                    std::max(dp[k][j] * dp[m][k + 1],
                                                                             std::max(dp[j][k] * dp[m][k + 1],
                                                                                      dp[k][j] * dp[k + 1][m]))));
                            min = std::min<long long>(min,
                                                      std::min(dp[j][k] * dp[k + 1][m],
                                                               std::min(dp[k][j] * dp[m][k + 1],
                                                                        std::min(dp[j][k] * dp[m][k + 1],
                                                                                 dp[k][j] * dp[k + 1][m]))));
                            break;
                        }
                    }
                }

                if (assign) {
                    dp[j][m] = max;
                    dp[m][j] = min;
                }
            }
        }
//          0       1       2       3       4       5       6
//
//        -7      -3      1       33      26      30      67        0
//        -3      4       8       40      33      37      74        1
//        -6      8       2       10      3       7       14        2
//        -30     40      10      5       -2      2       6         3
//        -37     -16     -4      -2      -7      -3      1         4
//        -33     -12     0       2       -3      4       8         5
//        -66     -24     -2      -1      -6      8       2         6

        max = INT64_MIN;
        std::vector<int> edges;
        for (int i = 0; i < n; ++i) {
            if (dp[i][i + n - 1] > max) {
                max = dp[i][i + n - 1];
            }
        }

        for (int i = 0; i < n; ++i) {
            if (dp[i][i + n - 1] == max) {
                edges.push_back(i + 1);
            }
        }

        std::ofstream writer("output_ilya.txt");
        writer << max << '\n';
        for (int i = 0; i < edges.size() - 1; ++i) {
            writer << edges[i] << " ";
        }
        writer << edges[edges.size() - 1];

//        for (int i = 0; i < 2 * n - 1; ++i) {
//            for (int j = 0; j < 2 * n - 1; ++j) {
//                std::cerr << dp[i][j] << " ";
//            }
//            std::cerr << "\n";
//        }
//
//        PrintMatrix(dp);
//        std::cout << '\n';
        return {max, edges};
    }

private:
    long long n;
    std::vector<long long> numbers;
    std::vector<char> operations;
    long long minimum, index_minimum;
};

//std::ifstream in("input.txt");
//std::ofstream out("output_katya.txt");

const int N = 500;

long long table_min[N][N];
long long table[N][N];

void maxSumRing(std::vector<long long> &nodes, std::vector<char> &links) {
    for (auto &i : table_min) {
        for (auto &j : i) {
            j = INT64_MAX;
        }
    }
    for (auto &i : table) {
        for (auto &j : i) {
            j = INT64_MIN;
        }
    }
    for (int i = 0; i < nodes.size(); i++) {
        table[0][i] = nodes[i];
    }
    for (int i = 0; i < nodes.size(); i++) {
        table_min[0][i] = nodes[i];
    }
    for (int row = 1; row < nodes.size(); row++) {
        for (int col = 0; col < nodes.size(); col++) {
            for (int k = 0; k < row; k++) {
                auto a = row - k - 1;
                auto b = k + col + 1;
                if (b >= nodes.size()) {
                    b = b % nodes.size();
                }
                if (links[b] == 't') {
                    table[row][col] = std::max(table[row][col], table[k][col] + table[a][b]);
                    table_min[row][col] = std::min(table_min[row][col], table_min[k][col] + table_min[a][b]);
                } else {
                    table[row][col] = std::max(table[row][col], table_min[k][col] * table_min[a][b]);
                    table[row][col] = std::max(table[row][col], table[k][col] * table[a][b]);
                    table_min[row][col] = std::min(table_min[row][col], table_min[k][col] * table[a][b]);
                    table_min[row][col] = std::min(table_min[row][col], table_min[k][col] * table_min[a][b]);
                    table_min[row][col] = std::min(table_min[row][col], table[k][col] * table_min[a][b]);
                }
            }
        }
    }
}

//int main2() {
//    int n;
//    std::vector<char> links;
//    std::vector<long long> nodes;
//    if (in.is_open()) {
//        in >> n;
//        for (int i = 0; i < n; i++) {
//            char link;
//            long long node;
//            in >> link >> node;
//            links.push_back(link);
//            nodes.push_back(node);
//        }
//    }
//    long long result = INT64_MIN;
//    maxSumRing(nodes, links);
//    for (int i = 0; i < nodes.size(); i++) {
//        result = std::max(result, table[nodes.size() - 1][i]);
//    }
//    std::vector<long long> index;
//    out << result << std::endl;
//    for (int i = 0; i < nodes.size(); i++) {
//        if (table[nodes.size() - 1][i] == result) {
//            index.push_back(i + 1);
//        }
//    }
//    for (int i = 0; i < index.size() - 1; i++) {
//        out << index[i] << " ";
//    }
//    out << index[index.size() - 1];
//    return 0;
//}

std::pair<std::vector<long long>, std::vector<char>> GenerateSample(int amount, int max_number) {
    std::random_device rd;

    std::mt19937_64 generator(rd());
    std::uniform_int_distribution<int> real_amount_generator(3, amount);
    int real_amount = real_amount_generator(generator);
    std::vector<long long> nums(real_amount);
    std::vector<char> links(real_amount);

    std::uniform_int_distribution<int> link_generator(0, 20);
    std::uniform_int_distribution<long long> number_generator(0, max_number);
    for (int i = 0; i < real_amount; ++i) {
        nums[i] = number_generator(generator);
        links[i] = (link_generator(generator) % 2 == 1) ? 't' : 'x';
    }

    return {std::move(nums), std::move(links)};
}

template<typename T, typename U>
bool operator==(const std::vector<T> &lhs, const std::vector<U> &rhs) {
    if (lhs.size() != rhs.size()) return false;

    for (int i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) return false;
    }

    return true;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
    for (const auto &el : v) {
        out << el << " ";
    }

    return out;
}

void TestSolutions(int amount_of_tests, int max_amount_in_sample, int max_number_in_sample) {
    for (int i = 0; i < amount_of_tests; ++i) {
        auto[nums, links] = GenerateSample(max_amount_in_sample, max_number_in_sample);

        Polygon polygon(nums, links);
        auto[ilya_result, ilya_edges] = polygon.Find();
        maxSumRing(nums, links);
        long long katya_result = INT64_MIN;
        for (int j = 0; j < nums.size(); j++) {
            katya_result = std::max(katya_result, table[nums.size() - 1][j]);
        }

        std::vector<long long> katya_edges;
//        out << katya_result << std::endl;
        for (int i = 0; i < nums.size(); i++) {
            if (table[nums.size() - 1][i] == katya_result) {
                katya_edges.push_back(i + 1);
            }
        }

//        if (!(ilya_edges == katya_edges) || katya_result != ilya_result) {
//            std::cerr << "=======================================================\n";
//            std::cerr << "Something went wrong!\n";
//            std::cerr << katya_result << " vs " << ilya_result << "\n";
//            std::cerr << "-------------------------------------------\n";
//            std::cerr << "{" << katya_edges << "} vs {" << ilya_edges << "}\n";
//            std::cerr << "In sample:\n";
//            for (int j = 0; j < nums.size(); ++j) {
//                std::cerr << links[j] << " " << nums[j] << " ";
//            }
//            std::cerr << "\n=======================================================\n";
//        }
    }
}

int main() {
//    srand(time(0));
    std::ifstream reader("input.txt");
    long long number;
    reader >> number;
    Polygon polygon(number, reader);
//
//    polygon.Find();
    TestSolutions(10000, 10, 10);
    return 0;
}
