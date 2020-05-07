#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

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

int UP = 0;
int RIGHT = 1;
int DOWN = 2;
int LEFT = 3;

int dp[31][31][31][31][16];
bool existence[31][31][31][31][16];
int answer[31][31];

int n, a;
std::vector<std::vector<int64_t>> horizontals, verticals;

//checks if the direction is closed
bool isClosed(int directionsArray, int direction) {
  return  ((directionsArray >> direction) & 1) != 0;
}

//checks if we can draw the line in a certain direction
bool lineExist(int horiz, int vert, int directionsArray, int direction) {
  if (isClosed(directionsArray, direction))
    return false;
  if (direction == UP) {
    return verticals.at(vert).at(0) == horiz;
  } else if (direction == DOWN) {
    return verticals.at(vert).at(verticals.at(vert).size()-1) == horiz;
  } else if (direction == LEFT) {
    return horizontals.at(horiz).at(0) == vert;
  } else {
    return horizontals.at(horiz).at(horizontals.at(horiz).size()-1) == vert;
  }
}

//finds first value in the array which is greater or equals val
int firstGEqualValue(std::vector<int64_t> arrayList, int64_t val) {
  if (arrayList.empty())
    return 9999;
  for (int i = 0; i < arrayList.size(); ++i) {
    if (arrayList.at(i) >= val)
      return i;
  }
  return 9999;

}

//finds first value in the array which is greater than val
int FirstGreaterValue(std::vector<int64_t> arrayList, int64_t val) {
  if (arrayList.empty()) {
    return 9999;
  }
  for (int i = 0; i < arrayList.size(); ++i) {
    if (arrayList.at(i) > val) {
      return i;
    }
  }
  return 9999;

}

//closes a certain direction
int CloseDirection(int directionsArray, int direction) {
  return directionsArray | (1 << direction);
}

//interprets bytes of directionsArray into direction
int DirectionsToDirection(int directionsArray) {
  return (directionsArray + 3) % 4;
}

int Solution(int left, int top, int right, int bottom, int directions) {
  if (existence[left][top][right][bottom][directions])
    return dp[left][top][right][bottom][directions];

  dp[left][top][right][bottom][directions] = 9999;

  if (right < left || bottom < top) {
    return 0;
  }

  if (directions == 15) {
    return dp[left][top][right][bottom][directions];
  }

  int leftL = firstGEqualValue(horizontals.at(left), top);
  int leftR = FirstGreaterValue(horizontals.at(left), bottom);
  if (leftL == leftR) {
    dp[left][top][right][bottom][directions] = Solution(left + 1, top, right, bottom, directions);
    existence[left][top][right][bottom][directions] = true;
    return dp[left][top][right][bottom][directions];
  }

  int rightL = firstGEqualValue(horizontals.at(right), top);
  int rightR = FirstGreaterValue(horizontals.at(right), bottom);
  if (rightL == rightR) {
    dp[left][top][right][bottom][directions] = Solution(left, top, right - 1, bottom, directions);
    existence[left][top][right][bottom][directions] = true;
    return dp[left][top][right][bottom][directions];
  }

  int topT = firstGEqualValue(verticals.at(top), left);
  int topB = FirstGreaterValue(verticals.at(top), right);
  if (topT == topB) {
    dp[left][top][right][bottom][directions] = Solution(left, top + 1, right, bottom, directions);
    existence[left][top][right][bottom][directions] = true;
    return dp[left][top][right][bottom][directions];
  }
  int bottomT = firstGEqualValue(verticals.at(bottom), left);
  int bottomB = FirstGreaterValue(verticals.at(bottom), right);
  if (bottomT == bottomB) {
    dp[left][top][right][bottom][directions] = Solution(left, top, right, bottom - 1, directions);
    existence[left][top][right][bottom][directions] = true;
    return dp[left][top][right][bottom][directions];
  }


  if (!isClosed(directions, UP) || !isClosed(directions, DOWN)) {
    bool upAvailable = true;
    int count = 0;
    for (int i = leftL; i != leftR && i < horizontals.at(left).size(); ++i) {
      int vert = horizontals.at(left).at(i);
      if (lineExist(left, vert, directions, DOWN)) {
        int result = Solution(left, top, right, vert - 1, CloseDirection(directions, RIGHT))
                     + Solution(left, vert + 1, right, bottom, CloseDirection(directions, LEFT))
                     + a - left;
        dp[left][top][right][bottom][directions] = std::min(dp[left][top][right][bottom][directions], result);
      }
      ++count;
      upAvailable &= lineExist(left, vert, directions, UP);
    }
    if (upAvailable) {
      int result = Solution(left + 1, top, right, bottom, directions) + left * count;
      dp[left][top][right][bottom][directions] = std::min(dp[left][top][right][bottom][directions], result);
    }

    bool downAvailable = true;
    count = 0;
    for (int i = rightL; i != rightR && i < horizontals.at(right).size(); ++i) {
      int vert = horizontals.at(right).at(i);
      if (lineExist(right, vert, directions, UP)) {
        int result = Solution(left, top, right, vert - 1, CloseDirection(directions, RIGHT)) +
                     Solution(left, vert + 1, right, bottom, CloseDirection(directions, LEFT))
                     + right;
        dp[left][top][right][bottom][directions] = std::min(dp[left][top][right][bottom][directions], result);
      }
      ++count;
      downAvailable &= lineExist(right, vert, directions, DOWN);
    }
    if (downAvailable) {
      int result = Solution(left, top, right - 1, bottom, directions) + (a - right) * count;
      dp[left][top][right][bottom][directions] = std::min(dp[left][top][right][bottom][directions], result);
    }
  }


  if (!isClosed(directions, LEFT) || !isClosed(directions, RIGHT)) {
    bool leftAvailable = true;
    int count = 0;
    for (int i = topT; i != topB && i < verticals.at(top).size(); ++i) {
      int horiz = verticals.at(top).at(i);
      if (lineExist(horiz, top, directions, RIGHT)) {
        int result = Solution(left, top, horiz - 1, bottom, CloseDirection(directions, DOWN)) +
                     Solution(horiz + 1, top, right, bottom, CloseDirection(directions, UP)) + a - top;
        dp[left][top][right][bottom][directions] = std::min(dp[left][top][right][bottom][directions], result);
      }
      ++count;
      leftAvailable &= lineExist(horiz, top, directions, LEFT);
    }
    if (leftAvailable) {
      int result = Solution(left, top + 1, right, bottom, directions) + top * count;
      dp[left][top][right][bottom][directions] = std::min(dp[left][top][right][bottom][directions], result);
    }


    bool rightAvailable = true;
    count = 0;
    for (int i = bottomT; i != bottomB && i < verticals.at(bottom).size(); ++i) {
      int horiz = verticals.at(bottom).at(i);
      if (lineExist(horiz, bottom, directions, LEFT)) {
        int result = Solution(left, top, horiz - 1, bottom, CloseDirection(directions, DOWN)) +
                     Solution(horiz + 1, top, right, bottom, CloseDirection(directions, UP)) + bottom;
        dp[left][top][right][bottom][directions] = std::min(dp[left][top][right][bottom][directions], result);
      }
      ++count;
      rightAvailable &= lineExist(horiz, bottom, directions, RIGHT);
    }
    if (rightAvailable) {
      int result = Solution(left, top, right, bottom - 1, directions) + (a - bottom) * count;
      dp[left][top][right][bottom][directions] = std::min(dp[left][top][right][bottom][directions], result);
    }
  }

  existence[left][top][right][bottom][directions] = true;
  return dp[left][top][right][bottom][directions];
}

void RestoreSolution(int left, int top, int right, int bottom, int directionsArray) {
  int step = dp[left][top][right][bottom][directionsArray];

  if (right < left || bottom < top)
    return;

  //TOP
  int leftL = firstGEqualValue(horizontals.at(left), top);
  int leftR = FirstGreaterValue(horizontals.at(left), bottom);
  if (leftL == leftR) {
    RestoreSolution(left + 1, top, right, bottom, directionsArray);
    return;
  }

  int rightL = firstGEqualValue(horizontals.at(right), top);
  int rightR = FirstGreaterValue(horizontals.at(right), bottom);
  if (rightL == rightR) {
    RestoreSolution(left, top, right - 1, bottom, directionsArray);
    return;
  }
  //LEFT
  int topT = firstGEqualValue(verticals.at(top), left);
  int topB = FirstGreaterValue(verticals.at(top), right);
  if (topT == topB) {
    RestoreSolution(left, top + 1, right, bottom, directionsArray);
    return;
  }
  int bottomT = firstGEqualValue(verticals.at(bottom), left);
  int bottomB = FirstGreaterValue(verticals.at(bottom), right);
  if (bottomT == bottomB) {
    RestoreSolution(left, top, right, bottom - 1, directionsArray);
    return;
  }


  if (!isClosed(directionsArray, UP) || !isClosed(directionsArray, DOWN)) {
    bool upAvailable = true;
    int count = 0;
    for (int i = leftL; i != leftR && i < horizontals.at(left).size(); ++i) {
      int vert = horizontals.at(left).at(i);
      if (lineExist(left, vert, directionsArray, DOWN)) {
        int result = Solution(left, top, right, vert - 1, CloseDirection(directionsArray, RIGHT))
                     + Solution(left, vert + 1, right, bottom, CloseDirection(directionsArray, LEFT))
                     + a - left;
        if (result == step) {
          answer[left][vert] = DOWN;
          RestoreSolution(left, top, right, vert - 1, CloseDirection(directionsArray, RIGHT));
          RestoreSolution(left, vert + 1, right, bottom, CloseDirection(directionsArray, LEFT));
          return;
        }
      }
      ++count;
      upAvailable &= lineExist(left, vert, directionsArray, UP);
    }
    if (upAvailable) {
      int result = Solution(left + 1, top, right, bottom, directionsArray) + left * count;
      if (result == step) {
        for (int i = leftL; i != leftR && i < horizontals.at(left).size(); ++i) {
          answer[left][horizontals.at(left).at(i)] = UP;
        }
        RestoreSolution(left + 1, top, right, bottom, directionsArray);
        return;
      }
    }


    bool downAvailable = true;
    count = 0;
    for (int i = rightL; i != rightR && i < horizontals.at(right).size(); ++i) {
      int vert = horizontals.at(right).at(i);
      if (lineExist(right, vert, directionsArray, UP)) {
        int result = Solution(left, top, right, vert - 1, CloseDirection(directionsArray, RIGHT)) +
                     Solution(left, vert + 1, right, bottom, CloseDirection(directionsArray, LEFT)) + right;
        if (result == step) {
          answer[right][vert] = UP;
          RestoreSolution(left, top, right, vert - 1, CloseDirection(directionsArray, RIGHT));
          RestoreSolution(left, vert + 1, right, bottom, CloseDirection(directionsArray, LEFT));
          return;
        }
      }
      ++count;
      downAvailable &= lineExist(right, vert, directionsArray, DOWN);
    }

    if (downAvailable) {
      int result = Solution(left, top, right - 1, bottom, directionsArray) + (a - right) * count;
      if (result == step) {
        for (int i = rightL; i != rightR && i < horizontals.at(right).size(); ++i) {
          answer[right][horizontals.at(right).at(i)] = DOWN;
        }
        RestoreSolution(left, top, right - 1, bottom, directionsArray);
        return;
      }
    }
  }

  if (!isClosed(directionsArray, LEFT) || !isClosed(directionsArray, RIGHT)) {
    bool leftAvailable = true;
    int count = 0;
    for (int i = topT; i != topB && i < verticals.at(top).size(); ++i) {
      int horiz = verticals.at(top).at(i);
      if (lineExist(horiz, top, directionsArray, RIGHT)) {
        int result = Solution(left, top, horiz - 1, bottom, CloseDirection(directionsArray, DOWN)) +
                     Solution(horiz + 1, top, right, bottom, CloseDirection(directionsArray, UP)) + a - top;
        if (result == step) {
          answer[horiz][top] = RIGHT;
          RestoreSolution(left, top, horiz - 1, bottom, CloseDirection(directionsArray, DOWN));
          RestoreSolution(horiz + 1, top, right, bottom, CloseDirection(directionsArray, UP));
          return;
        }
      }
      ++count;
      leftAvailable &= lineExist(horiz, top, directionsArray, LEFT);
    }

    if (leftAvailable) {
      int result = Solution(left, top + 1, right, bottom, directionsArray) + top * count;
      if (result == step) {
        for (int i = topT; i != topB && i < verticals.at(top).size(); ++i) {
          answer[verticals.at(top).at(i)][top] = LEFT;
        }
        RestoreSolution(left, top + 1, right, bottom, directionsArray);
        return;
      }
    }

    bool rightAvailable = true;
    count = 0;
    for (int i = bottomT; i != bottomB && i < verticals.at(bottom).size(); ++i) {
      int horiz = verticals.at(bottom).at(i);
      if (lineExist(horiz, bottom, directionsArray, LEFT)) {
        int result = Solution(left, top, horiz - 1, bottom, CloseDirection(directionsArray, DOWN)) +
                     Solution(horiz + 1, top, right, bottom, CloseDirection(directionsArray, UP)) + bottom;
        if (result == step) {
          answer[horiz][bottom] = LEFT;
          RestoreSolution(left, top, horiz - 1, bottom, CloseDirection(directionsArray, DOWN));
          RestoreSolution(horiz + 1, top, right, bottom, CloseDirection(directionsArray, UP));
          return;
        }
      }
      ++count;
      rightAvailable &= lineExist(horiz, bottom, directionsArray, RIGHT);
    }
    if (rightAvailable) {
      int result = Solution(left, top, right, bottom - 1, directionsArray) + (a - bottom) * count;
      if (result == step) {
        for (int i = bottomT; i != bottomB && i < verticals.at(bottom).size(); ++i) {
          answer[verticals.at(bottom).at(i)][bottom] = RIGHT;
        }
        RestoreSolution(left, top, right, bottom - 1, directionsArray);
      }
    }
  }
}

void run() {
  std::ifstream reader("input.txt");

  reader >> a >> n;

  horizontals.resize(39, std::vector<int64_t>());
  verticals.resize(39, std::vector<int64_t>());

  std::vector<std::pair<int64_t, int64_t>> points(n);
  for (auto &point : points) {
    reader >> point.first >> point.second;
    horizontals[point.first].push_back(point.second);
    verticals[point.second].push_back(point.first);
  }

  for (int64_t i = 0; i < 31; ++i) {
    std::sort(horizontals[i].begin(), horizontals[i].end());
    std::sort(verticals[i].begin(), verticals[i].end());
  }

  PrintMatrix(horizontals);
  std::cout << "---------------\n";
  PrintMatrix(verticals);

  std::ofstream writer("output.txt");
  writer << Solution(1, 1, a - 1, a - 1, 0) << '\n';
  RestoreSolution(1, 1, a - 1, a - 1, 0);
  for (auto temp : points) {
    switch (DirectionsToDirection(answer[temp.first][temp.second])) {
      case 0: {
        writer << "UP\n";
        break;
      }
      case 2: {
        writer << "DOWN\n";
        break;
      }
      case 3: {
        writer << "LEFT\n";
        break;
      }
      case 1: {
        writer << "RIGHT\n";
        break;
      }
    }
  }
}

int main() {
  run();
  return 0;
}