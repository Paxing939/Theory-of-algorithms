#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

class DSU {
public:

  DSU(int n) : dsu_(n), connectivity_components_(n) {
    for (int i = 0; i < n; ++i) {
      dsu_[i] = {1, i + 1};
    }
  }

  int FindSet(int element_to_find) {
    if (element_to_find == dsu_[element_to_find - 1].second) {
      return element_to_find;
    }
    dsu_[element_to_find - 1].second = FindSet(dsu_[element_to_find - 1].second);
    return dsu_[element_to_find - 1].second;
  }

  int Union(int x, int y) {
    x = FindSet(x);
    y = FindSet(y);

    if (x != y) {
      if (dsu_[x - 1].first < dsu_[y - 1].first) {
        std::swap(x , y);
      }
      dsu_[y - 1].second = x;
      dsu_[x - 1].first += dsu_[y - 1].first;
      connectivity_components_--;
    }

    return connectivity_components_;
  }

  int getConnectivityComponents() const {
    return connectivity_components_;
  }

private:
  int connectivity_components_;
  std::vector<std::pair<int, int>> dsu_;
};

int main() {
  std::ifstream reader("input.txt");
  std::ofstream writer("output.txt");
  int n, m, q;
  reader >> n >> m >> q;

  if (n == 1) {
    for (int i = 0; i < q; ++i) {
      writer << 1;
    }
    return 0;
  }

  DSU dsu(n);

  int x, y;
  std::vector<std::pair<std::pair<int, int>, bool>> edges(m);
  for(int i = 0; i < m; ++i) {
    reader >> x >> y;
    edges[i].first.first = x, edges[i].first.second = y, edges[i].second = true;
  }

  int tmp;
  std::vector<int> deleted(q);
  for (int i = 0; i < q; ++i) {
    reader >> tmp;
    deleted[i] = tmp - 1;
    edges[tmp - 1].second = false;
  }

  for (int i = 0; i < m; ++i) {
    if (edges[i].second) {
      dsu.Union(edges[i].first.first, edges[i].first.second);
    }
  }

  std::vector<int> result(q);
  int pok = 0;
  for (int i = q - 1; i >= 0; --i) {
    dsu.Union(edges[deleted[i]].first.first, edges[deleted[i]].first.second);

    if (dsu.getConnectivityComponents() == 1) {
//      if (q == 1) {
//        break;
//      }
//
//      result[i] = 0;
      pok = i - 1;
      break;
    } else {
      result[i] = 0;
    }
  }

  for (int i = pok; i >= 0; --i) {
    result[i] = 1;
  }

  for (int i = 0; i < q; ++i) {
    writer << result[i];
  }
  return 0;
}