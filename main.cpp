#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

template<typename T>
void PrintMatrix(const std::vector<std::vector<T>> &matrix) {
    for (const auto &vec : matrix) {
        for (const auto &x_ : vec) {
            std::cout << std::setw(7) << std::setprecision(2) << std::left << x_ << " ";
        }
        std::cout << std::endl;
    }
}

class Polygon {
public:

    Polygon(long long number, std::ifstream &in) : minimum(LONG_LONG_MAX), index_minimum(-1), numbers(number),
                                                   operations(number), n(number) {
        int i = 0;
        for (int i = 0; i < number; ++i) {
            in >> operations[i] >> numbers[i];
        }
    }

    void AddVertex(char operation, long long number) {
        if (number < minimum) {
            minimum = number;
            index_minimum = numbers.size();
        }
        numbers.push_back(number);
        operations.push_back(operation);
    }

    void Find() {
//        n = 4;
//        numbers = {-7, 4, 2, 5 };
//        operations = {'t', 't', 'x', 'x', '1', '1', '1'};

        std::vector<char> op(2 * n - 1);
        for (int i = 0, j = 1; i < 2 * n - 1; ++i, ++j) {
            op[i] = operations[j];
            if (j == n - 1) {
                j = -1;
            }
        }

//        for (auto el : op) {
//            std::cout << el << " ";
//        }
//        std::cout << std::endl;

        std::vector<std::vector<long long>> dp(2 * n - 1, std::vector<long long>(2 * n - 1, 0));
        for (int i = 0, j = 0; i < 2 * n - 1; ++i, ++j) {
            dp[i][i] = numbers[j];
//            std::cout << numbers[j] << " ";
            if (j == n - 1) {
                j = -1;
            }
        }

        long long max, min;
        for (int i = 0; i < 2 * n - 1; ++i) {
            for (int j = 0; j < 2 * n - 1 - i; ++j) {
                int m = j + i;
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

        max = -INT64_MAX;
        std::vector<int> edges;
        for (int i = n - 1; i < 2 * n; ++i) {
            if (dp[i - n + 1][i] > max) {
                max = dp[i - n + 1][i];
            }
        }
        for (int i = n - 1; i < 2 * n; ++i) {
            if (dp[i - n + 1][i] == max) {
                edges.push_back(i - n + 2);
            }
        }
        std::ofstream writer("output.txt");
        writer << max << '\n';
        for (const auto &edge : edges) {
            writer << edge << " ";
        }
//        writer << '\n';
//        PrintMatrix<long long>(dp);
    }

private:

    long long factorial(long long n) {
        int sum = 1;
        for (int i = 2; i <= n; i++) {
            sum *= i;
        }
        return sum;
    }

    long long n;
    std::vector<long long> numbers;
    std::vector<char> operations;
    long long minimum, index_minimum;
};

int main() {
    std::ifstream reader("input.txt");
    long long number;
    reader >> number;
    Polygon polygon(number, reader);

    polygon.Find();

    return 0;
}
