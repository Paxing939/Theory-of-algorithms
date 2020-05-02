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
void PrintVector(const std::vector<T> &vector) {
    for (const auto &x_ : vector) {
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
  std::vector<int> dirs;
  std::vector<int> distances;
  int closed;

  Point(int x1, int y1) : x(x1), y(y1), direction(-1), dirs(4, 1), distances(4, 0), closed(0) {}

  Point() {}
};

std::ostream &operator<<(std::ostream &out, const Point &point) {
    out << point.closed; //<< " " << point.y;
    return out;
}


bool operator<(const Point &lhs, const Point &rhs) {
    //   if (lhs.x < rhs.x) {
    //       return true;
    //   } else {
    //       return lhs.y < rhs.y;
    //   }
    return lhs.closed > rhs.closed;
}

bool operator<(const std::vector<int> &lhs, const std::vector<int> &rhs) {
    return lhs[0] > rhs[0];
}

class Microchip {
public:

  Microchip() {}

  Microchip(int length, const std::vector<Point *> &points) : length(length), points(points), n(points.size()),
                                                              result_length(0) {}

//    void FindDirection(Point &point) {
//
//        if (point.x == 12 && point.y == 1) {
//            int kawabanga = 1212;
//        }
//
//        std::vector<bool> dirs(4, true);
//        for (const auto &processed_point : points) {
//            if (dirs[0]) {
//
//                if (processed_point.x == point.x && processed_point.y > point.y) {
//                    dirs[0] = false;
//                }
//
//                if (processed_point.direction == 1) {
//                    if (processed_point.x < point.x) {
//                        dirs[0] = false;
//                    }
//                }
//                if (processed_point.direction == 3) {
//                    if (processed_point.x > point.x) {
//                        dirs[0] = false;
//                    }
//                }
//            }
//
//            if (dirs[1]) {
//                if (processed_point.y == point.y && processed_point.x > point.x) {
//                    dirs[1] = false;
//                }
//
//                if (processed_point.direction == 0) {
//                    if (processed_point.y < point.y) {
//                        dirs[1] = false;
//                    }
//                }
//                if (processed_point.direction == 2) {
//                    if (processed_point.y > point.y) {
//                        dirs[1] = false;
//                    }
//                }
//            }
//
//            if (dirs[2]) {
//                if (processed_point.x == point.x && processed_point.y < point.y) {
//                    dirs[2] = false;
//                }
//
//                if (processed_point.direction == 1) {
//                    if (processed_point.x < point.x) {
//                        dirs[2] = false;
//                    }
//                }
//                if (processed_point.direction == 3) {
//                    if (processed_point.x > point.x) {
//                        dirs[2] = false;
//                    }
//                }
//            }
//
//            if (dirs[3]) {
//                if (processed_point.y == point.y && processed_point.x < point.x) {
//                    dirs[3] = false;
//                }
//
//                if (processed_point.direction == 0) {
//                    if (processed_point.y < point.y) {
//                        dirs[3] = false;
//                    }
//                }
//                if (processed_point.direction == 2) {
//                    if (processed_point.y > point.y) {
//                        dirs[3] = false;
//                    }
//                }
//            }
//        }
//
//        length++;
//        std::vector<int> lines = {length - point.y, length - point.x, point.y, point.x};
//        int min = 2147483647, min_ind;
//        for (int i = 0; i < 4; ++i) {
//            if (dirs[i]) {
//                if (min > lines[i]) {
//                    min = lines[i];
//                    min_ind = i;
//                }
//            }
//        }
//
//        point.direction = min_ind;
//        switch (min_ind) {
//            case 0: {
////        point.x_end = point.x;
////        point.y_end = length;
//                result_length += length - point.y;
//                break;
//            }
//            case 1: {
////        point.x_end = length;
////        point.y_end = point.y;
//                result_length += length - point.x;
//                break;
//            }
//            case 2: {
////        point.x_end = point.x;
////        point.y_end = 1;
//                result_length += point.y;
//                break;
//            }
//            case 3: {
////        point.x_end = 1;
////        point.y_end = point.y;
//                result_length += point.x;
//                break;
//            }
//        }
//        length--;
////    processed_points.push_back(point);
//    }
//
//    std::string FindRoutes() {
//        length -= 1;
//        std::vector<std::vector<Point *>> grid(length, std::vector<Point *>(length, nullptr));
//        for (auto &point : points) {
//            grid[grid.size() - point.y][point.x - 1] = &point;
//        }
////      PrintMatrix(grid);
//
//        for (int i = 0; i < length / 2; ++i) {
//
//            for (int j = i; j < length - i; ++j) {
//                if (grid[j][i] != nullptr) {
//                    FindDirection(*grid[j][i]);
//                }
//            }
//
//            for (int j = i + 1; j < length - i; ++j) {
//                if (grid[length - i - 1][j] != nullptr) {
//                    FindDirection(*grid[length - i - 1][j]);
//                }
//            }
//
//            for (int j = i + 1; j < length - i; ++j) {
//                if (grid[length - j - 1][length - i - 1] != nullptr) {
//                    FindDirection(*grid[length - j - 1][length - i - 1]);
//                }
//            }
//
//            for (int j = i + 1; j < length - i - 1; ++j) {
//                if (grid[i][length - j - 1] != nullptr) {
//                    FindDirection(*grid[i][length - j - 1]);
//                }
//            }
//
//        }
//
//        if (length % 2 == 1) {
//            if (grid[length / 2][length / 2] != nullptr) {
//                FindDirection(*grid[length / 2][length / 2]);
//            }
//        }
//
//        return WriteAnswer();
//    }

  int FindDirMinLength(Point &point) {
      int minLength = length + 1;   // UP
      int minDir = -1;
      if ((point.dirs[0]) && (minLength > length - point.y)) {  // UP
          minLength = length - point.y;
          minDir = 0;
      }

      if ((point.dirs[1]) && (minLength > length - point.x)) {  // RIGHT
          minLength = length - point.x;
          minDir = 1;
      }
      if ((point.dirs[2]) && (minLength > point.y)) {  // DOWN
          minLength = point.y;
          minDir = 2;
      }
      if ((point.dirs[3]) && (minLength > point.x)) {  // LEFT
          minLength = point.x;
          minDir = 3;
      }

      if (minDir == -1) {
          throw std::runtime_error("sdgjdgj");
      }
      return minDir;
  }

  int CheckClosedPoint(int dir, int x, int y) {
      std::vector<std::vector<int>> matrLines(length + 1, std::vector<int>(length + 1, 0));
      if (dir == 0) {    // UP
          for (int i = y + 1; i < length; i++)
              matrLines[x][i] = 1;
          for (auto &point : points) {
              // if point to left of line
              if ((matrLines[x][point->y]) && point->dirs[1] && (point->x < x)) {
                  if (point->closed == 3) {  // if point became completely closed
                      return -1;
                  } else {
                      point->dirs[1] = 0;
                      point->closed++;
                  }
              }
              // if point to right of line
              if ((matrLines[x][point->y]) && point->dirs[3] && (point->x > x)) {
                  if (point->closed == 3) {  // if point became completely closed
                      return -1;
                  } else {
                      point->dirs[3] = 0;
                      point->closed++;
                  }
              }
          }
          return length - y;
      }
      if (dir == 2) {    // DOWN
          for (int i = y - 1; i > 0; i--)
              matrLines[x][i] = 1;
          for (auto &point : points) {
              // if point to left of line
              if (matrLines[x][point->y] && point->dirs[1] && (point->x < x)) {
                  if (point->closed == 3) {
                      return -1;
                  } else {
                      point->dirs[1] = 0;
                      point->closed++;
                  }
              }
              // if point to left of line
              if (matrLines[x][point->y] && point->dirs[3] && (point->x > x)) {
                  if (point->closed == 3) {
                      return -1;
                  } else {
                      point->dirs[3] = 0;
                      point->closed++;
                  }
              }
          }
          return y;
      }
      if (dir == 1) {    // RIGHT
          for (int i = x + 1; i < length; i++)
              matrLines[i][y] = 1;
          for (auto &point : points) {
              // if point to bottom of line
              if (matrLines[point->x][y] && point->dirs[0] && (point->y < y)) {
                  if (point->closed == 3) {
                      return -1;
                  } else {
                      point->dirs[0] = 0;
                      point->closed++;
                  }
              }
              // if point to top of line
              if (matrLines[point->x][y] && point->dirs[2] && (point->y > y)) {
                  if (point->closed == 3) {
                      return -1;
                  } else {
                      point->dirs[2] = 0;
                      point->closed++;
                  }
              }
          }
          return length - x;
      }
      if (dir == 3) {    // LEFT
          for (int i = x - 1; i > 0; i--)
              matrLines[i][y] = 1;
          for (auto &point : points) {
              // if point to top of line
              if (matrLines[point->x][y] && point->dirs[0] && (point->y < y)) {
                  if (point->closed == 3) {
                      return -1;
                  } else {
                      point->dirs[0] = 0;
                      point->closed++;
                  }
              }
              // if point to bottom of line
              if (matrLines[point->x][y] && point->dirs[2] && (point->y > y)) {
                  if (point->closed == 3) {
                      return -1;
                  } else {
                      point->dirs[2] = 0;
                      point->closed++;
                  }
              }
          }
          return x;
      }
      return 0;
  }

  void CheckDirs(Point &point_to_check) {
      point_to_check.closed = 0;
      for (auto &point : points) {
          if (point->x == point_to_check.x && point->y > point_to_check.y && point_to_check.dirs[0] > 0) {
              point_to_check.dirs[0] = 0;
              point_to_check.closed++;
          }
          if (point->y == point_to_check.y && point->x > point_to_check.x && point_to_check.dirs[1] > 0) {
              point_to_check.dirs[1] = 0;
              point_to_check.closed++;
          }
          if (point->x == point_to_check.x && point->y < point_to_check.y && point_to_check.dirs[2] > 0) {
              point_to_check.dirs[2] = 0;
              point_to_check.closed++;
          }
          if (point->y == point_to_check.y && point->x < point_to_check.x && point_to_check.dirs[3] > 0) {
              point_to_check.dirs[3] = 0;
              point_to_check.closed++;
          }
      }

      if (point_to_check.closed == 4) {
          throw std::runtime_error("Point is closed, test is bad!");
      }
  }

  std::string FindRoutes2() {
//        length -= 1;
//        std::vector<std::vector<Point *>> grid(length, std::vector<Point *>(length, nullptr));
//        for (auto &point : points) {
//            grid[grid.size() - point->y][point->x - 1] = &point;
//        }

      // n^2
      for (auto &point : points) {
          CheckDirs(*point);
      }

      auto points_sorted(points);
      for (auto &point : points_sorted) {
          std::cout << int(point->x) << ", " << int(point->y) << ", " << point->closed << '\n';
      }
//        std::sort(points_sorted.begin(), points_sorted.end());

      // sort points
      while (true) {
          for (int i = 0; i < points_sorted.size(); ++i) {
              for (int j = 0; j < points_sorted.size(); ++j) {
                  if (points_sorted[i]->closed > points_sorted[j]->closed) {
                      std::swap(points_sorted[i], points_sorted[j]);
                  } else {
                      if (points_sorted[i]->closed == 2 && (points_sorted[i]->closed == points_sorted[j]->closed)) {
                          std::vector<int> arr_dfi = {points_sorted[i]->dirs[0] * points_sorted[i]->distances[0],
                                                      points_sorted[i]->dirs[1] * points_sorted[i]->distances[1],
                                                      points_sorted[i]->dirs[2] * points_sorted[i]->distances[2],
                                                      points_sorted[i]->dirs[3] * points_sorted[i]->distances[3]};
                          std::vector<int> arr_dfj = {points_sorted[j]->dirs[0] * points_sorted[j]->distances[0],
                                                      points_sorted[j]->dirs[1] * points_sorted[j]->distances[1],
                                                      points_sorted[j]->dirs[2] * points_sorted[j]->distances[2],
                                                      points_sorted[j]->dirs[3] * points_sorted[j]->distances[3]};
                          if ((std::max_element(arr_dfi.begin(), arr_dfi.end()) -
                               std::min_element(arr_dfi.begin(), arr_dfi.end())) <
                              (std::max_element(arr_dfj.begin(), arr_dfj.end()) -
                               std::min_element(arr_dfj.begin(), arr_dfj.end()))) {
                              std::swap(points_sorted[i], points_sorted[j]);
                          }
                      }
                  }
              }
          }
          std::cout << "Sort" << '\n';
          for (auto &point : points_sorted) {
              //std::cout << point << '\n'
              std::cout << int(point->x) << ", " << int(point->y) << ", " << point->closed << '\n';
          }

          bool bExistClosedPoint = true;
          // Point *point = points_sorted[0];
          int cnt_points = 0;
          for (auto &point: points_sorted) {
              cnt_points++;
              if (point->direction > 0) {
                  while (point->closed < 4) {
                      int minDir = FindDirMinLength(*point);   // choose direction with min length

                      int pointLength = CheckClosedPoint(minDir, point->x, point->y);
                      if (pointLength == -1) {     // check completely closed points (point.close = 4)
                          point->dirs[minDir] = 0;
                      } else {
                          bExistClosedPoint = false;
                          point->direction = minDir;
                          result_length += pointLength;
                          break;
                      }
                  }
                  if (bExistClosedPoint)
                      exit(123);
                  break;
              }
          }
          if (cnt_points == n) {
              break;
          }
      }

      return WriteAnswer();
  }

private:

  void WriteAnswerRun() {
      std::ofstream writer("output.txt");
      writer << result_length << '\n';
      for (const auto &point : points) {
          switch (point->direction) {
              case 0: {
                  writer << "UP" << '\n';
                  break;
              }
              case 1: {
                  writer << "RIGHT" << '\n';
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

  std::string WriteAnswer() {
//    std::ofstream writer("output.txt");
      std::stringstream writer;
      writer << result_length << '\n';
      for (const auto &point : points) {
          switch (point->direction) {
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

  int length, n, result_length;
  std::vector<Point *> points;
};

std::string ReadInfo(std::ifstream &tests_reader) {
    std::string test;
    std::getline(tests_reader, test, '&');
    return test;
}

void Generator() {
    int amount_of_tests = 6;
    std::ifstream tests_reader("tests.txt");
    std::ifstream answers_reader("answers.txt");

    for (int i = 0; i < amount_of_tests; ++i) {
        std::string test = ReadInfo(tests_reader);
        std::stringstream ss(test);
        std::string answer = ReadInfo(answers_reader);

        int length, n, x, y;
        ss >> length >> n;
        std::vector<Point *> points(n);
        for (int i = 0; i < n; ++i) {
            ss >> x >> y;
            points[i] = new Point(x, y);
            points[i]->distances[0] = length - points[i]->y;
            points[i]->distances[1] = length - points[i]->x;
            points[i]->distances[2] = points[i]->y;
            points[i]->distances[3] = points[i]->x;
        }

        Microchip microchip(length, points);
        std::string algo_answer = microchip.FindRoutes2();
//    std::cout << algo_answer << '\n';

        if (algo_answer == answer) {
            std::cout << "Test №" << i + 1 << " is completed!\n";
            std::ofstream logs_writer("log.txt");
//      logs_writer << "Algorithm answer is:\n" << algo_answer;
//      logs_writer << "Correct answer is:\n" << answer;
        } else {
            std::cout << "Test №" << i + 1 << " is failed!\n";
            std::ofstream logs_writer("log.txt");
            logs_writer << "Algorithm answer is:\n" << algo_answer;
            logs_writer << "Correct answer is:\n" << answer;
            logs_writer.close();
            exit(123);
        }
    }
}

int main() {
    Generator();
//    std::ifstream reader("input.txt");
//    int length, n, x, y;
//    reader >> length >> n;
//
//    std::vector<Point *> points(n);
//    for (int i = 0; i < n; ++i) {
//        reader >> x >> y;
//        points[i] = new Point(x, y);
//        points[i]->distances[0] = length - points[i]->y;
//        points[i]->distances[1] = length - points[i]->x;
//        points[i]->distances[2] = points[i]->y;
//        points[i]->distances[3] = points[i]->x;
//    }
//
//    Microchip microchip(length, points);
//
//    std::ofstream writer("output.txt");
//    writer << microchip.FindRoutes2();

    return 0;
}
