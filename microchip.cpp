#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <utility>

template<typename T>
void PrintMatrix(const std::vector<std::vector<T>> &matrix) {
  for (const auto &vec : matrix) {
    for (const auto &x_ : vec) {
      std::cout << std::setw(7) << std::setprecision(2) << std::left << x_ << " ";
    }
    std::cout << std::endl;
  }
}

template<typename T>
void PrintVector(const std::vector<T>& vector) {
  for (const auto& x_ : vector) {
    std::cout << std::setw(7) << std::setprecision(2) << std::left << x_ << " ";
  }
  std::cout << std::endl;
}

struct Point {
  int x;
  int y;
  int direction;
  int x_end;
  int y_end;
};

std::ostream &operator<<(std::ostream &out, const Point &point) {
  out << point.x << " " << point.y;
  return out;
}

//std::ostream &operator<<(std::ostream &out, const Point &point) {
//  out << point.x << " " << point.y << " " << point.direction << " " << point.x_end << " " << point.y_end;
//  return out;
//}

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
//    std::cerr << "FindDirection call\n";
if (point.x == 3 && point.y == 11) {
  int kawabanga = 1212;
}

    std::vector<bool> dirs(4, true);
    for (const auto &processed_point : points) {
      if (dirs[0]) {
//        dirs[0] = !intersect(point, {point.x, length, 0, 0, 0}, processed_point,
//                             {processed_point.x_end, processed_point.y_end, 0, 0, 0});
        if (processed_point.x == point.x && processed_point.y > point.y) {
          dirs[0] = false;
        }
      }

      if (dirs[1]) {
//        dirs[1] = !intersect(point, {length, point.y, 0, 0, 0}, processed_point,
//                             {processed_point.x_end, processed_point.y_end, 0, 0, 0});
        if (processed_point.y == point.y && processed_point.x > point.x) {
          dirs[1] = false;
        }
      }

      if (dirs[2]) {
//        dirs[2] = !intersect(point, {point.x, 1, 0, 0, 0}, processed_point,
//                             {processed_point.x_end, processed_point.y_end, 0, 0, 0});
        if (processed_point.x == point.x && processed_point.y < point.y) {
          dirs[2] = false;
        }
      }

      if (dirs[3]) {
//        dirs[3] = !intersect(point, {1, point.y, 0, 0, 0}, processed_point,
//                             {processed_point.x_end, processed_point.y_end, 0, 0, 0});
        if (processed_point.y == point.y && processed_point.x < point.x) {
          dirs[3] = false;
        }
      }
    }

    length++;
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
//        point.x_end = point.x;
//        point.y_end = length;
        result_length += length - point.y;
        break;
      }
      case 1: {
//        point.x_end = length;
//        point.y_end = point.y;
        result_length += length - point.x;
        break;
      }
      case 2: {
//        point.x_end = point.x;
//        point.y_end = 1;
        result_length += point.y;
        break;
      }
      case 3: {
//        point.x_end = 1;
//        point.y_end = point.y;
        result_length += point.x;
        break;
      }
    }
    length--;
//    processed_points.push_back(point);
  }

  std::string FindRoutes() {
    length -= 1;
    std::vector<std::vector<Point *>> grid(length, std::vector<Point *>(length, nullptr));
    for (auto &point : points) {
      grid[grid.size() - point.y][point.x - 1] = &point;
    }
//      PrintMatrix(grid);

    for (int i = 0; i < length / 2; ++i) {

      for (int j = i; j < length - i; ++j) {
        if (grid[j][i] != nullptr) {
          FindDirection(*grid[j][i]);
        }
      }

      for (int j = i + 1; j < length - i; ++j) {
        if (grid[length - i - 1][j] != nullptr) {
          FindDirection(*grid[length - i - 1][j]);
        }
      }

      for (int j = i + 1; j < length - i; ++j) {
        if (grid[length - j - 1][length - i - 1] != nullptr) {
          FindDirection(*grid[length - j - 1][length - i - 1]);
        }
      }

      for (int j = i + 1; j < length - i - 1; ++j) {
        if (grid[i][length - j - 1] != nullptr) {
          FindDirection(*grid[i][length - j - 1]);
        }
      }

    }

    if (length % 2 == 1) {
      if (grid[length / 2][length / 2] != nullptr) {
        FindDirection(*grid[length / 2][length / 2]);
      }
    }

    return WriteAnswer();
  }

private:

  std::string WriteAnswer() {
//    std::ofstream writer("output.txt");
    std::stringstream writer;
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

    return writer.str();
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
    return Belongs(a, b, c, d);
  }

  bool Belongs(Point a, Point b, Point c, Point d) {
    return b.x == d.x && b.y == d.y;
  }

  int length, n, result_length;
  std::vector<Point> points;
  std::vector<Point> processed_points;
};

std::string ReadInfo(std::ifstream &tests_reader) {
  std::string test;
  std::getline(tests_reader, test, '&');
  return test;
}

void Generator() {
  int amount_of_tests = 2;
  std::ifstream tests_reader("tests.txt");
  std::ifstream answers_reader("answers.txt");

  for (int i = 0; i < amount_of_tests; ++i) {
    std::stringstream ss(ReadInfo(tests_reader));
    std::string answer = ReadInfo(answers_reader);

    int length, n, x, y;
    ss >> length >> n;
    std::vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
      ss >> x >> y;
      points[i] = {x, y, 0, 0, 0};
    }

    Microchip microchip(length, points);
    std::string algo_answer = microchip.FindRoutes();

    if (algo_answer == answer) {
      std::cout << "Test №" << i + 1 << " is complete!\n";
    } else {
      std::cout << "Test №" << i + 1 << " is failed!\n";
      std::ofstream logs_writer("log.txt");
      logs_writer << "Algorithm answer is:\n" << algo_answer;
      logs_writer << "Correct answer is:" << answer;
      logs_writer.close();
      exit(123);
    }
  }
}

int main() {Generator();
//  std::ifstream reader("input.txt");
//  int length, n, x, y;
//  reader >> length >> n;
//
//  std::vector<Point> points(n);
//  for (int i = 0; i < n; ++i) {
//    reader >> x >> y;
//    points[i] = {x, y, 0, 0, 0};
//  }
//
//  Microchip microchip(length, points);
//
//  microchip.FindRoutes();

  return 0;
}

//6
//5
//4 1
//5 1
//1 5
//4 2
//5 2