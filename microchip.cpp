#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <utility>
#include <set>

template<typename T>
void PrintMatrix(const std::vector<std::vector<T>> &matrix) {
  for (const auto &vec : matrix) {
    for (const auto &x_ : vec) {
      std::cout << std::setw(7) << std::setprecision(2) << std::left << x_ << " ";
    }
    std::cout << std::endl;
  }
}

struct Point {
  int x;
  int y;
  int direction;
  int x_end;
  int y_end;
};

std::ostream &operator<<(std::ostream &out, const Point &point) {
  out << point.x << " " << point.y << " " << point.direction << " " << point.x_end << " " << point.y_end;
  return out;
}

bool operator<(const Point &lhs, const Point &rhs) {
  if (lhs.x < rhs.x) {
    return true;
  } else {
    return lhs.y < rhs.y;
  }
}

class Microchip {
public:

  Microchip() {}

  Microchip(int length, const std::vector<Point> &points) : length(length), points(points), n(points.size()),
                                                            result_length(0) {
    processed_points.reserve(n);
  }

  void FindDirection(Point &point) {
    std::vector<bool> dirs(4, true);
    for (const auto &processed_point : processed_points) {
      if (dirs[0]) {
        dirs[0] = !intersect(point, {point.x, length, 0, 0, 0}, processed_point,
                             {processed_point.x_end, processed_point.y_end, 0, 0, 0});
      }

      if (dirs[1]) {
        dirs[1] = !intersect(point, {length, point.y, 0, 0, 0}, processed_point,
                             {processed_point.x_end, processed_point.y_end, 0, 0, 0});
      }

      if (dirs[2]) {
        dirs[2] = !intersect(point, {point.x, 1, 0, 0, 0}, processed_point,
                             {processed_point.x_end, processed_point.y_end, 0, 0, 0});
      }

      if (dirs[3]) {
        dirs[3] = !intersect(point, {1, point.y, 0, 0, 0}, processed_point,
                             {processed_point.x_end, processed_point.y_end, 0, 0, 0});
      }
    }

    std::vector<int> lines = {length - point.y, length - point.x, point.y, point.x};
    int min = lines[0], min_ind = 0;
    for (int i = 0; i < 4; ++i) {
      if (dirs[i]) {
        if (min > lines[i]) {
          min = lines[i];
          min_ind = i;
        }
      }
    }

    point.direction = min_ind;

    switch (min_ind) {
      case 0: {
        point.x_end = point.x;
        point.y_end = length;
        result_length += length - point.y;
        break;
      }
      case 1: {
        point.x_end = length;
        point.y_end = point.y;
        result_length += length - point.x;
        break;
      }
      case 2: {
        point.x_end = point.x;
        point.y_end = 1;
        result_length += point.y;
        break;
      }
      case 3: {
        point.x_end = 1;
        point.y_end = point.y;
        result_length += point.x;
        break;
      }
    }

    processed_points.push_back(point);
  }

  void FindRoutes() {

    std::vector<std::vector<Point *>> grid(n, std::vector<Point *>(n, nullptr));
//
//    n = 6;
//    std::vector<std::vector<int>> grid = {
//        {0,  1,  2,  3,  4, 5},
//        {6,  7,  8,  9, 10, 11},
//        {12, 13, 14, 15, 16, 17},
//        {18, 19, 20, 21, 22, 23},
//        {24, 25, 26, 27, 28, 29},
//        {30, 31, 32, 33, 34, 35}
//    };
//
    for (auto &point : points) {
      grid[point.x - 1][point.y - 1] = &point;
    }

//    PrintMatrix(grid);

    for (int i = 0; i < n / 2; ++i) {

//      std::cerr << 0 << '\n';
      for (int j = i; j < n - i; ++j) {
//        std::cerr << grid[j][i] << " ";
        if (grid[j][i] != nullptr) {
          FindDirection(*grid[j][i]);
        }
      }
//      std::cerr << 1 << '\n';

      for (int j = i + 1; j < n - i; ++j) {
        int tmp = n - i - 1;
//        std::cerr << grid[tmp][j] << " ";
        if (grid[n - i - 1][j] != nullptr) {
          FindDirection(*grid[n - i - 1][j]);
        }
      }

//      std::cerr << 2 << '\n';
      for (int j = i + 1; j < n - i; ++j) {
//        std::cerr << grid[n - j - 1][n - i - 1] << " ";
        if (grid[n - j - 1][n - i - 1] != nullptr) {
          FindDirection(*grid[n - j - 1][n - i - 1]);
        }
      }

//      std::cerr << 3 << '\n';
      for (int j = i + 1; j < n - i - 1; ++j) {
//        std::cerr << grid[i][n - j - 1] << " ";
        if (grid[i][n - j - 1] != nullptr) {
          FindDirection(*grid[i][n - j - 1]);
        }
      }

//      std::cerr << 4 << '\n';
//      std::cerr << std::endl;

    }

    if (n % 2 == 1) {
//      std::cerr << grid[n / 2][n / 2];
      if (grid[n / 2][n / 2] != nullptr) {
        FindDirection(*grid[n / 2][n / 2]);
      }
    }

    WriteAnswer();
//    std::vector<int> sides, directions(n);
//    int max_ind = 0, max, i = 0;
//    for (auto &point : points) {
//      sides = {15 - point.y, 15 - point.x, point.y, point.x};
//      max = sides[max_ind];
//      for (int i = 0; i < 4; ++i) {
//        if (max < sides[i]) {
//          max = sides[i];
//          max_ind = i;
//        }
//      }
//      directions[i] = 0;
//
//
//      ++i;
//    }

  }

private:

  void WriteAnswer() {
    std::ofstream writer("output.txt");
    writer << result_length << '\n';
    for (const auto &point : points) {
      switch (point.direction) {
        case 0: {
          writer << "UP" << '\n';
          break;
        }
        case 1: {
          writer << "RIGHT" << '\n';
          break;
        }
        case 2: {
          writer << "DOWN" << '\n';
          break;
        }
        case 3: {
          writer << "LEFT" << '\n';
          break;
        }
      }
    }
  }

  inline int area(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
  }

  inline bool intersect_1(int a, int b, int c, int d) {
    if (a > b) { std::swap(a, b); }
    if (c > d) { std::swap(c, d); }
    return std::max(a, c) <= std::min(b, d);
  }

  bool intersect_old(Point a, Point b, Point c, Point d) {
    return intersect_1(a.x, b.x, c.x, d.x)
           && intersect_1(a.y, b.y, c.y, d.y)
           && area(a, b, c) * area(a, b, d) <= 0
           && area(c, d, a) * area(c, d, b) <= 0;
  }

  bool intersect(Point a, Point b, Point c, Point d) {
    return intersect_old(a, b, c, d);
  }

  bool Belongs(Point a, Point b, Point c, Point d) {
    return b.x == d.x && b.y == d.y;
  }


  int length, n, result_length;
  std::vector<Point> points;
  std::vector<Point> processed_points;
};

int main() {
  std::ifstream reader("input.txt");
  int length, n, x, y;
  reader >> length >> n;

  std::vector<Point> points(n);
  for (int i = 0; i < n; ++i) {
    reader >> x >> y;
    points[i] = {x, y, 0, 0, 0};
  }

  Microchip microchip(length, points);

  microchip.FindRoutes();

  return 0;
}
