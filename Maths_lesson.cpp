#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <map>
#include <set>


bool CheckSums(std::vector<int> &numbers, std::vector<int> &sum_amounts, int sum, int amount_of_numbers) {
  for (int j = 0; j < amount_of_numbers; ++j) {
    if (sum_amounts[j] < amount_of_numbers && numbers[j] + numbers[sum_amounts[j]] == sum) {
      return false;
    }
  }

//  int min = std::numeric_limits<int>::max();
//  for (int j = 0; j < amount_of_numbers; ++j) {
//    if (numbers[j] != -1 && numbers[sum_amounts[j]] != -1 && numbers[j] + numbers[sum_amounts[j]] < min) {
//      min = numbers[j] + numbers[sum_amounts[j]];
//    }
//  }
//  if (min <= sum) {
//    return false;
//  }

  return true;
}

struct Index {
  int index;
};

int n;
std::set<Index> set;
std::vector<int> numbers, sum_amounts;

bool operator<(const Index &lhs, const Index &rhs) {
  int left = numbers[lhs.index] + numbers[sum_amounts[lhs.index]];
  int right = numbers[rhs.index] + numbers[sum_amounts[rhs.index]];
  if (numbers[sum_amounts[lhs.index]] == -1) {
    left = numbers[lhs.index] + numbers[sum_amounts[lhs.index] - 1];
  }
  if (numbers[sum_amounts[rhs.index]] == -1) {
    right = numbers[rhs.index] + numbers[sum_amounts[rhs.index] - 1];
  }
  return left >= right;
}

std::string MathsLesson2(const std::string &test) {
  std::stringstream ss(test), out;

  int n;
  ss >> n;

  numbers.resize(n, -1);
  sum_amounts.resize(n, -1);

  int i = 0, sum = 0, p = 0;
  ss >> sum;

  if (n == 1) {
    out << sum;
    return std::to_string(sum);
  }

  numbers[i] = sum / 2;
  sum_amounts[i] = 1;
  out << numbers[i] << "\n";
  set.insert({1});
  i++;
  while (i < n - 1) {
    ss >> sum;

//    if (CheckSums(numbers, sum_amounts, sum, i)) {
    if (sum_amounts[set.begin()->index] >= i ||
        numbers[set.begin()->index] + numbers[sum_amounts[set.begin()->index]] > sum || set.empty()) {
      numbers[i] = sum - numbers[0];
      out << numbers[i] << '\n';
      sum_amounts[0]++;
      sum_amounts[i] = 0;
      set.insert({i});
      i++;
    } else {
//      for (int j = 0; j < i; ++j) {
//        if (sum_amounts[j] < i) {
//          if (numbers[j] + numbers[sum_amounts[j]] <= sum) {
//            sum_amounts[j]++;
//            break;
//          }
//        }
//      }
      int min = set.begin()->index;
      set.erase(set.begin());
      sum_amounts[min]++;
      set.insert({min});
    }
    p++;
  }

  for (int k = p; k < n * n; ++k) {
    ss >> sum;
  }

  out << sum / 2;

  return out.str();
}

void Generator() {
  int n = 5, start_number = 1, max_number = 15;
  srand(time(0));

  for (int i = 0; i < 1'000'000; ++i) {
    std::stringstream ss, true_answer;

    std::vector<int> numbers(n), sums(n * n);
    for (int j = 0; j < n; ++j) {
      numbers[j] = start_number + rand() % max_number;
    }
//  numbers= {1, 5, 20, 20, 20, 10001};
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

    std::string algorithm = MathsLesson2(ss.str());

    if (true_answer.str() == algorithm + '\n') {
      std::cout << "Test #" << i + 1 << " completed successfully!\n";
    } else {
      std::cout << "Test #" << i + 1 << " failed!\n";
      std::ofstream writer("log.txt");
      writer << algorithm;
      writer << "\n-------------------------\n";
      writer << true_answer.str();
      writer << "-------------------------\n";
      writer << ss.str();
      return;
    }
  }
}

void MathsLesson2() {
  std::cin >> n;

  numbers.resize(n, -1);
  sum_amounts.resize(n, -1);

  int i = 0, sum = 0, p = 0;
  std::cin >> sum;

  if (n == 1) {
    std::cout << sum;
    return;
  }

  numbers[i] = sum / 2;
  sum_amounts[i] = 1;
  std::cout << numbers[i] << "\n";
  set.insert({0});
  i++;
  while (i < n - 1) {
    std::cin >> sum;

    if (sum_amounts[set.begin()->index] >= i ||
        numbers[set.begin()->index] + numbers[sum_amounts[set.begin()->index]] > sum || set.empty()) {
      numbers[i] = sum - numbers[0];
      std::cout << numbers[i] << '\n';
      sum_amounts[0]++;
      sum_amounts[i] = 0;
      set.insert({i});
      i++;
    } else {
      int min = set.begin()->index;
      set.erase(set.begin());
      sum_amounts[min]++;
      set.insert({min});
    }
    p++;
  }

  for (int k = p; k < n * n; ++k) {
    std::cin >> sum;
  }

  std::cout << sum / 2;
}

int main() {
//Generator();
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  MathsLesson2();

  return 0;
}


//#include <iostream>
//#include <fstream>
//#include <queue>
//#include <vector>
//
//using namespace std;
//
//int *numb;
//int *kol_sum;
//int k = 0;
//
//struct idx {
//	int i;
//};
//
//bool operator<(const idx &a, const idx &b) {
//	int si = numb[a.i] + numb[kol_sum[a.i]];
//	int sj = numb[b.i] + numb[kol_sum[b.i]];
//	return si >= sj;
//}
//
//int main() {
//	ifstream fin("input.txt");
//	ofstream fout("output.txt");
//	priority_queue<idx> cur_id, wait_id;
//	int n, a;
//	fin >> n;
//	numb = new int[n];
//	kol_sum = new int[n];
//	fin >> a;
//	numb[0] = a / 2;
//	fout << a / 2 << endl;
//	kol_sum[0] = 1;
//	k++;
//	cur_id.push({0});
//	while (k < n) {
//		fin >> a;
//		if (cur_id.empty() || kol_sum[cur_id.top().i] >= k || numb[cur_id.top().i] + numb[kol_sum[cur_id.top().i]] > a) {
//			numb[k] = a - numb[0];
//			fout << numb[k] << endl;
//			kol_sum[k] = 1;
//			k++;
//			cur_id.push({k - 1});
//			while (!wait_id.empty()) {
//				int top = wait_id.top().i;
//				wait_id.pop();
//				cur_id.push({top});
//			}
//		} else {
//			int top = cur_id.top().i;
//			cur_id.pop();
//			++kol_sum[top];
//			if (kol_sum[top] < k)
//				cur_id.push({top});
//			else
//				wait_id.push({top});
//		}
//	}
//	delete[] numb;
//	delete[] kol_sum;
//	fout.close();
//}
