#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <limits>
#include <utility>
#include <fstream>

struct Point {
  int x, y, id;
};

std::ostream &operator<<(std::ostream &out, const Point &point) {
  out << point.x << " " << point.y;
  return out;
}

void GenerateSample(std::vector<Point> &points) {
  points.resize(rand() % 10 + 2);

  std::ofstream writer("samples.txt");
  for (int i = 0; i < points.size(); ++i) {
    points[i] = {rand() % 10 - 5, rand() % 10 - 5, i};
    writer << points[i] << '\n';
  }
}

double CalcDistance(const Point &point1, const Point &point2) {
  return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

std::pair<int, int> BruteForce(const std::vector<Point> &points) {
  int index1 = 0, index2 = 1;
  double min_distance = 1'000'000'000, distance = 0;
  for (int i = 0; i < points.size(); ++i) {
    for (int j = i + 1; j < points.size(); ++j) {
      distance = CalcDistance(points[i], points[j]);
      if (min_distance > distance) {
        index1 = i;
        index2 = j;
        min_distance = distance;
      }
    }
  }
  return {index1, index2};
}

inline bool CompareForX(const Point &a, const Point &b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

inline bool CompareForY(const Point &a, const Point &b) {
  return a.y < b.y;
}

double min_dist;
int ansa, ansb;

inline void UpdateAnswer(const Point &a, const Point &b) {
  double dist = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + .0);
  if (dist < min_dist) {
    min_dist = dist, ansa = a.id, ansb = b.id;
  }
}

std::vector<Point> tmp_vector;

void Recursion(std::vector<Point> &points, int left, int right) {
  if (right - left <= 3) {
    for (int i = left; i <= right; ++i) {
      for (int j = i + 1; j <= right; ++j) {
        UpdateAnswer(points[i], points[j]);
      }
    }

    std::sort(points.begin() + left, points.begin() + right + 1, &CompareForY);
    return;
  }

  int m = (left + right) >> 1;
  int midx = points[m].x;

  Recursion(points, left, m);

  Recursion(points, m + 1, right);

  std::merge(points.begin() + left, points.begin() + m + 1, points.begin() + m + 1, points.begin() + right + 1,
             tmp_vector.begin(), &CompareForY);

  std::copy(tmp_vector.begin(), tmp_vector.begin() + right - left + 1, points.begin() + left);

  int tsz = 0;
  for (int i = left; i <= right; ++i) {
    if (abs(points[i].x - midx) < min_dist) {
      for (int j = tsz - 1; j >= 0 && points[i].y - tmp_vector[j].y < min_dist; --j) {
        UpdateAnswer(points[i], tmp_vector[j]);
      }
      tmp_vector[tsz++] = points[i];
    }
  }
}

std::pair<int, int> Fast(std::vector<Point> &points) {
  std::sort(points.begin(), points.end(), &CompareForX);
  tmp_vector.resize(points.size());
  min_dist = std::numeric_limits<double>::max();
  Recursion(points, 0, points.size() - 1);
  return {ansa, ansb};
}

bool CheckSolutions(std::vector<Point> &copy_points, int i1, int j1, int i2, int j2) {
  if (i1 == i2 && j1 == j2) {
    return true;
  }
  if (j1 == i2 && i1 == j2) {
    return true;
  }
  return CalcDistance(copy_points[i1], copy_points[j1]) - CalcDistance(copy_points[i2], copy_points[j2]) < 0.1;
}

//int main() {
//  srand(time(0));
//
//  int n = 100'000;
//  std::string brute_force_solution, fast_solution;
//  std::vector<Point> points, copy_points;
//
//  for (int i = 0; i < n; ++i) {
//    GenerateSample(points);
//    copy_points = points;
//    std::cout << "Generated samples\n";
//
//    std::pair<int, int> brute = BruteForce(points);
//    std::cout << "Did brute\n";
//
//    std::pair<int, int> fast = Fast(points);
//    std::cout << "Did fast\n";
//
//    std::string copy_fast = fast_solution;
//    std::reverse(copy_fast.begin(), copy_fast.end());
//    if (CheckSolutions(copy_points, fast.first, fast.second, brute.first, brute.second)) {
//      std::cout << "Test #" << i + 1 << " completed successfully!\n";
//    } else {
//      std::cout << "Test #" << i + 1 << " failed!\n";
//      std::cout << "Brute force: " << brute_force_solution << '\n';
//      std::cout << "Fast: " << fast_solution << '\n';
//      std::cout << "Input vector:\n";
//      for (const auto &point : copy_points) {
//        std::cout << point << '\n';
//      }
//      break;
//    }
//    std::cout << "Did check\n";
//  }
//
//  std::cout << "finished";
//  return 0;
//}

int main() {
  int n;
  std::cin >> n;

  int x, y;
  std::vector<Point> points(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> x >> y;
    points[i].x = x;
    points[i].y = y;
  }

  auto answer = Fast(points);

  std::cout << answer.first << " " << answer.second;
}