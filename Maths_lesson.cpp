#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <map>

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

  std::vector<int> numbers(n);
  std::map<int, int> map;

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
    while (true) {
      if (!map.empty()) {
        if (map.begin()->first == sum) {
          if (map.begin()->second > 1) {
            map.begin()->second--;
          } else {
            map.erase(map.begin());
          }
        } else {
          if (sum > map.begin()->first) {
            map.erase(map.begin());
          } else {
            break;
          }
        }
        ss >> sum;
      } else {
        break;
      }
    }

    numbers[j] = sum - numbers[0];
    out << numbers[j] << '\n';
    j++;
    if (map.count(numbers[j - 1] + numbers[0]) != 0) {
      map.at(numbers[j - 1] + numbers[0])++;
    } else {
      map.insert({numbers[j - 1] + numbers[0], 1});
    }
    for (int k = 1; k < j; ++k) {
      if (k != j - 1) {
        if (map.count(numbers[j - 1] + numbers[k]) != 0) {
          map.at(numbers[j - 1] + numbers[k]) += 2;
        } else {
          map.insert({numbers[j - 1] + numbers[k], 2});
        }
      } else {
        if (map.count(numbers[j - 1] + numbers[k]) != 0) {
          map.at(numbers[j - 1] + numbers[k])++;
        } else {
          map.insert({numbers[j - 1] + numbers[k], 1});
        }
      }
    }

    i++;
  }

  return out.str();
}

void MathsLesson() {
  int n;
  std::cin >> n;

  std::vector<int> numbers(n);
  std::map<int, short> map;

  int i = 0, j = 0, sum = 0;
  std::cin >> sum;
  numbers[j] = sum / 2;
  std::cout << numbers[j] << "\n";
  i++, j++;
  while (true) {
    std::cin >> sum;
    if (sum % 2 == 1) {
      continue;
    }
    while (true) {
      if (!map.empty()) {
        if (map.begin()->first == sum) {
          if (map.begin()->second > 1) {
            map.begin()->second--;
          } else {
            map.erase(map.begin());
          }
        } else {
          break;
        }
        std::cin >> sum;
      } else {
        break;
      }
    }

    if (sum % 2 == 1) {
      continue;
    }
    numbers[j] = sum / 2;
    std::cout << numbers[j] << '\n';
    j++;
    if (j == n - 1) {
      break;
    }
    if (numbers[j - 1] + numbers[0] % 2 == 0) {
      if (map.count(numbers[j - 1] + numbers[0]) != 0) {
        map.at(numbers[j - 1] + numbers[0])++;
      } else {
        map.insert({numbers[j - 1] + numbers[0], 1});
      }
    }
    for (int k = 1; k < j - 1; ++k) {
      if (numbers[j - 1] + numbers[k] % 2 == 0) {
        if (map.count(numbers[j - 1] + numbers[k]) != 0) {
          map.at(numbers[j - 1] + numbers[k]) += 2;
        } else {
          map.insert({numbers[j - 1] + numbers[k], 2});
        }
      }
    }
    if (map.count(2 * numbers[j - 1]) != 0) {
      map.at(2 * numbers[j - 1])++;
    } else {
      map.insert({2 * numbers[j - 1], 1});
    }

    i++;
  }

  for (int k = i; k < n * n; ++k) {
    std::cin >> sum;
  }

  std::cout << sum / 2;
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
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  MathsLesson();

  return 0;
}