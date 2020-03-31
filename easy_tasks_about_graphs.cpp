#include <iostream>
#include <fstream>
#include <vector>

template<typename T>
void PrintVector(std::ostream &out, const std::vector<T>& vector) {
  for (const auto& x_ : vector) {
    out << x_ << " ";
  }
  out << '\n';
}

template<typename T>
void PrintMatrix(std::ostream &out, const std::vector<std::vector<T>>& matrix) {
  for (const auto& vec : matrix) {
    for (const auto& x_ : vec) {
      out << x_ << " ";
    }
    out << '\n';
  }
}

void BuildAdjacencyMatrix(std::ostream &writer, std::istream &reader) {
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

void BuildAdjacencyList(std::ostream &writer, std::istream &reader) {
  int n, m;
  reader >> n >> m;
  int vertex1, vertex2;
  std::vector<std::vector<int>> graph(n);
  for (auto &vec : graph) {
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

void BuildCanonicalView(std::ostream &writer, std::istream &reader) {
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

void BuildCanonicalViewByAdjacencyMatrix(std::ostream &writer, std::istream &reader) {
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

int main() {
  std::ifstream reader("input.txt");
  std::ofstream writer("output.txt");

  int number_of_task = 3;
  switch(number_of_task) {
    case 0: {
      BuildAdjacencyMatrix(writer, reader);
      break;
    }
    case 1: {
      BuildAdjacencyList(writer, reader);
      break;
    }
    case 2: {
      BuildCanonicalView(writer, reader);
      break;
    }
    case 3: {
      BuildCanonicalViewByAdjacencyMatrix(writer, reader);
      break;
    }

  }

  return 0;
}