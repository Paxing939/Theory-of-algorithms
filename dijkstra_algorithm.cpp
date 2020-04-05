#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

int main() {
  std::ofstream writer("output.txt");
  std::ifstream reader("input.txt");
  int n, m;
  reader >> n >> m;

  int index, vertex, length;
  std::vector<std::vector<std::pair<int, int>>> graph(n);
  for (int i = 0; i < n; ++i) {
    reader >> index >> vertex >> length;
    graph[index].push_back({vertex, length});
  }

  int s = 0;
  std::vector<int> d(n, INT_MAX), p(n);
  d[s] = 0;
  std::vector<bool> used(n);
  for (int i = 0; i < n; ++i) {
    int v = -1;
    for (int j = 0; j < n; ++j) {
      if (!used[j] && (v == -1 || d[j] < d[v])) {
        v = j;
      }
    }

    if (d[v] == INT_MAX) {
      break;
    }
    used[v] = true;

    for (size_t j = 0; j < graph[v].size(); ++j) {
      int to = graph[v][j].first, len = graph[v][j].second;

      if (d[v] + len < d[to]) {
        d[to] = d[v] + len;
        p[to] = v;
      }
    }
  }

  writer << *std::min_element(d.begin(), d.end());
}
