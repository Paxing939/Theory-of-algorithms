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
  std::vector<int> d(n, INT_MAX);
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
      if (d[v] + graph[v][j].second < d[graph[v][j].first]) {
        d[graph[v][j].first] = d[v] + graph[v][j].second;
      }
    }
  }

  writer << *std::min_element(d.begin(), d.end());
}
