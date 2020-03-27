#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <utility>
#include <set>

struct Point {
  int x;
  int y;
  int direction;
};

bool operator<(const Point &lhs, const Point &rhs) {
  if (lhs.x < rhs.x) {
    return true;
  } else {
    return lhs.y < rhs.y;
  }
}

class Microchip {
public:

  Microchip(int length, const std::set<Point> &points) : length(length), points(points), n(points.size()) {}

  void FindRoutes() {

    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

    std::vector<int> sides, directions(n);
    int max_ind = 0, max, i = 0;
    for (auto &point : points) {
      sides = {15 - point.y, 15 - point.x, point.y, point.x};
      max = sides[max_ind];
      for (int i = 0; i < 4; ++i) {
        if (max < sides[i]) {
          max = sides[i];
          max_ind = i;
        }
      }
      directions[i] = 0;

      ++i;
    }

  }

private:
  int length, n;
  std::set<Point> points;
};

int main() {
  std::ifstream reader("input.txt");
  int length, n, x, y;
  reader >> length >> n;

  std::set<Point> points;
  for (int i = 0; i < n; ++i) {
    reader >> x >> y;
    points.insert({x, y});
  }

  Microchip microchip(length, points);

  microchip.FindRoutes();

  return 0;
}
