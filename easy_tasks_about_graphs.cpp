#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

template<typename T>
void PrintVector(std::ostream& out, const std::vector<T>& vector) {
  for (const auto& x_ : vector) {
    out << x_ << " ";
  }
  out << '\n';
}

template<typename T>
void PrintMatrix(std::ostream& out, const std::vector<std::vector<T>>& matrix) {
  for (const auto& vec : matrix) {
    for (const auto& x_ : vec) {
      out << x_ << " ";
    }
    out << '\n';
  }
}

void BuildAdjacencyMatrix(std::ostream& writer, std::istream& reader) {
  int n, m;
  reader >> n >> m;
  int vertex1, vertex2;
  std::vector<std::vector<int>> graph(n, std::vector<int>(n));
  for (int i = 0; i < m; ++i) {
    reader >> vertex1 >> vertex2;
    graph[vertex1 - 1][vertex2 - 1] = 1;
    graph[vertex2 - 1][vertex1 - 1] = 1;
  }

  PrintMatrix(writer, graph);
}

void BuildAdjacencyList(std::ostream& writer, std::istream& reader) {
  int n, m;
  reader >> n >> m;
  int vertex1, vertex2;
  std::vector<std::vector<int>> graph(n);
  for (auto& vec : graph) {
    vec.push_back(0);
  }

  for (int i = 0; i < m; ++i) {
    reader >> vertex1 >> vertex2;
    graph[vertex1 - 1][0]++;
    graph[vertex1 - 1].push_back(vertex2);

    graph[vertex2 - 1][0]++;
    graph[vertex2 - 1].push_back(vertex1);
  }

  PrintMatrix(writer, graph);
}

void BuildCanonicalView(std::ostream& writer, std::istream& reader) {
  int n;
  reader >> n;
  int vertex1, vertex2;
  std::vector<int> root_tree(n, 0);
  for (int i = 0; i < n - 1; ++i) {
    reader >> vertex1 >> vertex2;
    root_tree[vertex2 - 1] = vertex1;
  }

  PrintVector(writer, root_tree);
}

void BuildCanonicalViewByAdjacencyMatrix(std::ostream& writer, std::istream& reader) {
  int n;
  reader >> n;
  int vertex;
  std::vector<int> root_tree(n, 0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      reader >> vertex;
      if (vertex == 1) {
        root_tree[j] = i + 1;
      }
    }
  }

  PrintVector(writer, root_tree);
}

void BFS(std::ostream& writer, std::istream& reader) {
  int n;
  reader >> n;
  int vertex;
  std::vector<std::vector<int>> graph(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      reader >> vertex;
      if (vertex) {
        graph[i].push_back(j + 1);
      }
    }

    if (graph[i].empty()) {
      graph[i].push_back(0);
    }
  }

  PrintMatrix(std::cerr, graph);

  int s = 0, mark = 1;
  std::queue<int> q;
  std::vector<std::pair<bool, int>> used(n);

  q.push(s);
  used[s].first = true;
  used[s].second = mark++;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    bool empty = true;
    for (int to : graph[v]) {
      if (!used[to - 1].first && to != 0) {
        empty = false;
        used[to - 1].first = true;
        used[to - 1].second = mark++;
        q.push(to - 1);
      }
    }

    if (empty && q.empty()) {
      for (size_t i = 0; i < n; ++i) {
        if (!used[i].first) {
          used[i].first = true;
          used[i].second = mark++;
          q.push(i);
          break;
        }
      }
    }
  }

  for (auto& pair : used) {
    writer << pair.second << " ";
  }
}

void dfs(int v, int &mark, const std::vector<std::vector<int>>& graph, std::vector<int>& used) {
  if (used[v] == 0) {
    used[v] = mark++;
    for (auto i : graph[v]) {
      if (i != -1 && used[i] == 0) {
        dfs(i, mark, graph, used);
      }
    }
  }
}

void BuildGraph(std::ostream& writer, std::istream& reader) {
  int n;
  reader >> n;
  int vertex;
  std::vector<std::vector<int>> graph(n);
  std::vector<int> used(n);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      reader >> vertex;
      if (vertex) {
        graph[i].push_back(j);
      }
    }

    if (graph[i].empty()) {
      graph[i].push_back(-1);
    }
  }

  int mark = 1;
  for (int i = 0; i < n; ++i) {
    dfs(i, mark, graph, used);
  }

  for (auto& el : used) {
    if (el == 0) {
      el = mark++;
    }
  }

  PrintVector(writer, used);
}

int main() {

  std::unordered_set<int> set;
  std::vector<int> nums = {1, 2, 2};
  for (auto el : nums) {
    if (set.count(el) == 0) {
      set.insert(el);
    } else {
      set.erase(el);
    }
  }
  for (auto el : set) {
    std::cout << el << " ";
  }

//  std::ifstream reader("input.txt");
//  std::ofstream writer("output.txt");
//
//  int number_of_task = 5;
//  switch (number_of_task) {
//    case 0: {
//      BuildAdjacencyMatrix(writer, reader);
//      break;
//    }
//    case 1: {
//      BuildAdjacencyList(writer, reader);
//      break;
//    }
//    case 2: {
//      BuildCanonicalView(writer, reader);
//      break;
//    }
//    case 3: {
//      BuildCanonicalViewByAdjacencyMatrix(writer, reader);
//      break;
//    }
//    case 4: {
//      BFS(writer, reader);
//      break;
//    }
//    case 5: {
//      BuildGraph(writer, reader);
//      break;
//    }
//  }

  return 0;
}