#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <iomanip>

using namespace std;

template<typename T>
void PrintMatrix(const std::vector<std::vector<T>>& matrix) {
  for (const auto& vec : matrix) {
    for (const auto& x_ : vec) {
      std::cout << std::setw(7) << std::setprecision(2) << std::left << x_ << " ";
    }
    std::cout << std::endl;
  }
}

class Shooting {
public:
  Shooting(int r, int c, std::istream &in) : r(r), c(c) {
    g.resize(c);
    for (int i = 0; i < c; ++i) {
      int row_1, row_2;
      in >> row_1 >> row_2;
      g[i] = {row_1, row_2};
    }
  }

  bool try_kuhn(int v) {
    if (used[v]) {
      return false;
    }

    used[v] = true;
    for (size_t i = 0; i < g[v].size(); ++i) {
      int to = g[v][i];
      if (mt[to] == -1 || try_kuhn(mt[to])) {
        mt[to] = v;
        return true;
      }
    }
    return false;
  }

  int r, c;
  std::vector<std::vector<int>> g;
  std::vector<int> mt;
  std::vector<char> used{};
};

int n, k;
vector<vector<int>> g;
vector<int> mt;
vector<char> used;

bool try_kuhn(int v) {
  if (used[v]) return false;
  used[v] = true;
  for (size_t i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    if (mt[to] == -1 || try_kuhn(mt[to])) {
      mt[to] = v;
      return true;
    }
  }
  return false;
}

//int main() {
//
//  std::ifstream reader("input.txt");
//  reader >> k >> n;
//  g.resize(n);
//  for (int i = 0; i < n; ++i) {
//    int row_1, row_2;
//    reader >> row_1 >> row_2;
//    g[i] = {row_1, row_2};
//  }
//
//  mt.assign(k, -1);
//  for (int v = 0; v < n; ++v) {
//    used.assign(n, false);
//    try_kuhn(v);
//  }
//
//  for (int i = 0; i < k; ++i)
//    if (mt[i] != -1)
//      printf("%d %d\n", mt[i] + 1, i + 1);
//}

int main() {
  std::ifstream reader("input.txt");
  reader >> k >> n;
  g.resize(n);
  for (int i = 0; i < n; ++i) {
    int row_1, row_2;
    reader >> row_1 >> row_2;
    g[i] = {row_1 - 1, row_2 - 1};
  }

  PrintMatrix(g);
  std::cout << "\n------------\n";

  mt.assign(k, -1);
  vector<char> used1(n);
  for (int i = 0; i < n; ++i)
    for (size_t j = 0; j < g[i].size(); ++j)
      if (mt[g[i][j]] == -1) {
        mt[g[i][j]] = i;
        used1[i] = true;
        break;
      }
  for (int i = 0; i < n; ++i) {
    if (used1[i]) continue;
    used.assign(n, false);
    try_kuhn(i);
  }

  for (int i = 0; i < k; ++i)
    if (mt[i] != -1)
      printf("%d %d\n", mt[i] + 1, i + 1);
}

//int main() {
//  std::ofstream writer("output.txt");
//  std::ifstream reader("input.txt");
//
//  int r, c;
//  reader >> r >> c;
//  Shooting shooting(r, c, reader);
//
//  shooting.mt.assign(r, -1);
//  for (int v = 0; v < c; ++v) {
//    shooting.used.assign(c, false);
//    shooting.try_kuhn(v);
//  }
//
//  std::set<int> s;
//  std::vector<int> v(c);
//  for (int i = 0; i < r; ++i) {
//    if (shooting.mt[i] != -1) {
////			int size = s.size();
////			s.insert(i + 1);
////			if (s.size() != size) {
////				v[p++] = i + 1;
////				size++;
////			}
////
////			s.insert(shooting.mt[i] + 1);
////			if (s.size() != size) {
////				v[p++] = shooting.mt[i] + 1;
////			}
//      printf("%d %d\n", shooting.mt[i] + 1, i + 1);
//    }
//  }
//
////	if (s.size() < c) {
////		writer << "No";
////	} else {
////		for (const auto &el : v) {
////			writer << el << " ";
////		}
////	}
//}
