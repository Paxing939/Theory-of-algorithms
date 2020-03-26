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

  void DeleteEdge(int edge) {
    if (connectedness) {

    }
  }

  [[nodiscard]] bool isConnectedness() const {
    return connectedness;
  }

private:
  bool connectedness;
  int connectivity_components_;
  std::vector<std::pair<int, int>> dsu_;
};

int main() {
  std::ifstream reader("input.txt");
  int n, m, q;
  reader >> n >> m >> q;

  DSU dsu(n);

  int x, y;
  std::ofstream writer("output.txt");
  for(int i = 0; i < q; ++i) {
    reader >> x >> y;
    dsu.Union(x, y);
  }

  int tmp;
  for (int i = 0; i < m; ++i) {
    reader >> tmp;
    dsu.DeleteEdge(tmp);
    if (!dsu.isConnectedness()) {
      writer << 0;
    } else {
      writer << 1;
    }
  }

  return 0;
}