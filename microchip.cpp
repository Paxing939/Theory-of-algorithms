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

class Microchip {
public:
//checks if the direction is closed
	static bool IsClosed(int directionsArray, int direction) {
		return ((directionsArray >> direction) & 1) != 0;
	}

//checks if we can draw the line in a certain direction
	bool LineExist(int horiz, int vert, int directionsArray, int direction) {
		if (IsClosed(directionsArray, direction))
			return false;
		if (direction == UP) {
			return verticals.at(vert).at(0) == horiz;
		} else if (direction == DOWN) {
			return verticals.at(vert).at(verticals.at(vert).size() - 1) == horiz;
		} else if (direction == LEFT) {
			return horizontals.at(horiz).at(0) == vert;
		} else {
			return horizontals.at(horiz).at(horizontals.at(horiz).size() - 1) == vert;
		}
	}

//finds first value in the array which is greater or equals val
	static int FirstValueGreaterOrEqual(std::vector<int64_t> line, int64_t val) {
		if (line.empty()) {
			return 9999;
		}

		for (int i = 0; i < line.size(); ++i) {
			if (line.at(i) >= val) {
				return i;
			}
		}
		return 9999;

	}

//finds first value in the array which is greater than val
	static int FirstGreaterValue(std::vector<int64_t> line, int64_t val) {
		if (line.empty()) {
			return 9999;
		}

		for (int i = 0; i < line.size(); ++i) {
			if (line.at(i) > val) {
				return i;
			}
		}
		return 9999;

	}

//closes a certain direction
	static int CloseDirection(int directionsArray, int direction) {
		return directionsArray | (1 << direction);
	}

//interprets bytes of directionsArray into direction
	static int DirectionsToDirection(int directionsArray) {
		return (directionsArray + 3) % 4;
	}

	int Solution(int left, int top, int right, int bottom, int directions) {
		if (existence[left][top][right][bottom][directions]) {
			return dp[left][top][right][bottom][directions];
		}

		dp[left][top][right][bottom][directions] = std::numeric_limits<int>::max();

		if (right < left || bottom < top) {
			return 0;
		}

		if (directions == 15) {
			return dp[left][top][right][bottom][directions];
		}

		int leftL = FirstValueGreaterOrEqual(horizontals.at(left), top);
		int leftR = FirstGreaterValue(horizontals.at(left), bottom);
		if (leftL == leftR) {
			dp[left][top][right][bottom][directions] = Solution(left + 1, top, right, bottom, directions);
			existence[left][top][right][bottom][directions] = true;
			return dp[left][top][right][bottom][directions];
		}

		int rightL = FirstValueGreaterOrEqual(horizontals.at(right), top);
		int rightR = FirstGreaterValue(horizontals.at(right), bottom);
		if (rightL == rightR) {
			dp[left][top][right][bottom][directions] = Solution(left, top, right - 1, bottom, directions);
			existence[left][top][right][bottom][directions] = true;
			return dp[left][top][right][bottom][directions];
		}

		int topT = FirstValueGreaterOrEqual(verticals.at(top), left);
		int topB = FirstGreaterValue(verticals.at(top), right);
		if (topT == topB) {
			dp[left][top][right][bottom][directions] = Solution(left, top + 1, right, bottom, directions);
			existence[left][top][right][bottom][directions] = true;
			return dp[left][top][right][bottom][directions];
		}

		int bottomT = FirstValueGreaterOrEqual(verticals.at(bottom), left);
		int bottomB = FirstGreaterValue(verticals.at(bottom), right);
		if (bottomT == bottomB) {
			dp[left][top][right][bottom][directions] = Solution(left, top, right, bottom - 1, directions);
			existence[left][top][right][bottom][directions] = true;
			return dp[left][top][right][bottom][directions];
		}

		if (!IsClosed(directions, UP) || !IsClosed(directions, DOWN)) {
			bool up_available = true;
			int count = 0;
			for (int i = leftL; i != leftR && i < horizontals.at(left).size(); ++i) {
				int vert = horizontals.at(left).at(i);
				if (LineExist(left, vert, directions, DOWN)) {
					int result = Solution(left, top, right, vert - 1, CloseDirection(directions, RIGHT))
					             + Solution(left, vert + 1, right, bottom, CloseDirection(directions, LEFT))
					             + a - left;
					dp[left][top][right][bottom][directions] = std::min(dp[left][top][right][bottom][directions], result);
				}
				++count;
				up_available &= LineExist(left, vert, directions, UP);
			}
			if (up_available) {
				int result = Solution(left + 1, top, right, bottom, directions) + left * count;
				dp[left][top][right][bottom][directions] = std::min(dp[left][top][right][bottom][directions], result);
			}

			bool down_available = true;
			count = 0;
			for (int i = rightL; i != rightR && i < horizontals.at(right).size(); ++i) {
				int vert = horizontals.at(right).at(i);
				if (LineExist(right, vert, directions, UP)) {
					int result = Solution(left, top, right, vert - 1, CloseDirection(directions, RIGHT)) +
					             Solution(left, vert + 1, right, bottom, CloseDirection(directions, LEFT))
					             + right;
					dp[left][top][right][bottom][directions] = std::min(dp[left][top][right][bottom][directions], result);
				}
				++count;
				down_available &= LineExist(right, vert, directions, DOWN);
			}
			if (down_available) {
				int result = Solution(left, top, right - 1, bottom, directions) + (a - right) * count;
				dp[left][top][right][bottom][directions] = std::min(dp[left][top][right][bottom][directions], result);
			}
		}


		if (!IsClosed(directions, LEFT) || !IsClosed(directions, RIGHT)) {
			bool left_available = true;
			int count = 0;
			for (int i = topT; i != topB && i < verticals.at(top).size(); ++i) {
				int horiz = verticals.at(top).at(i);
				if (LineExist(horiz, top, directions, RIGHT)) {
					int result = Solution(left, top, horiz - 1, bottom, CloseDirection(directions, DOWN)) +
					             Solution(horiz + 1, top, right, bottom, CloseDirection(directions, UP)) + a - top;
					dp[left][top][right][bottom][directions] = std::min(dp[left][top][right][bottom][directions], result);
				}
				++count;
				left_available &= LineExist(horiz, top, directions, LEFT);
			}
			if (left_available) {
				int result = Solution(left, top + 1, right, bottom, directions) + top * count;
				dp[left][top][right][bottom][directions] = std::min(dp[left][top][right][bottom][directions], result);
			}


			bool right_available = true;
			count = 0;
			for (int i = bottomT; i != bottomB && i < verticals.at(bottom).size(); ++i) {
				int horiz = verticals.at(bottom).at(i);
				if (LineExist(horiz, bottom, directions, LEFT)) {
					int result = Solution(left, top, horiz - 1, bottom, CloseDirection(directions, DOWN)) +
					             Solution(horiz + 1, top, right, bottom, CloseDirection(directions, UP)) + bottom;
					dp[left][top][right][bottom][directions] = std::min(dp[left][top][right][bottom][directions], result);
				}
				++count;
				right_available &= LineExist(horiz, bottom, directions, RIGHT);
			}
			if (right_available) {
				int result = Solution(left, top, right, bottom - 1, directions) + (a - bottom) * count;
				dp[left][top][right][bottom][directions] = std::min(dp[left][top][right][bottom][directions], result);
			}
		}

		existence[left][top][right][bottom][directions] = true;
		return dp[left][top][right][bottom][directions];
	}

	void RestoreSolution(int left, int top, int right, int bottom, int directions) {
		int step = dp[left][top][right][bottom][directions];

		if (right < left || bottom < top)
			return;

		//TOP
		int leftL = FirstValueGreaterOrEqual(horizontals.at(left), top);
		int leftR = FirstGreaterValue(horizontals.at(left), bottom);
		if (leftL == leftR) {
			RestoreSolution(left + 1, top, right, bottom, directions);
			return;
		}

		int rightL = FirstValueGreaterOrEqual(horizontals.at(right), top);
		int rightR = FirstGreaterValue(horizontals.at(right), bottom);
		if (rightL == rightR) {
			RestoreSolution(left, top, right - 1, bottom, directions);
			return;
		}
		//LEFT
		int topT = FirstValueGreaterOrEqual(verticals.at(top), left);
		int topB = FirstGreaterValue(verticals.at(top), right);
		if (topT == topB) {
			RestoreSolution(left, top + 1, right, bottom, directions);
			return;
		}
		int bottomT = FirstValueGreaterOrEqual(verticals.at(bottom), left);
		int bottomB = FirstGreaterValue(verticals.at(bottom), right);
		if (bottomT == bottomB) {
			RestoreSolution(left, top, right, bottom - 1, directions);
			return;
		}

		if (!IsClosed(directions, UP) || !IsClosed(directions, DOWN)) {
			bool upAvailable = true;
			int count = 0;
			for (int i = leftL; i != leftR && i < horizontals.at(left).size(); ++i) {
				int vert = horizontals.at(left).at(i);
				if (LineExist(left, vert, directions, DOWN)) {
					int result = Solution(left, top, right, vert - 1, CloseDirection(directions, RIGHT))
					             + Solution(left, vert + 1, right, bottom, CloseDirection(directions, LEFT))
					             + a - left;
					if (result == step) {
						answer[left][vert] = DOWN;
						RestoreSolution(left, top, right, vert - 1, CloseDirection(directions, RIGHT));
						RestoreSolution(left, vert + 1, right, bottom, CloseDirection(directions, LEFT));
						return;
					}
				}
				++count;
				upAvailable &= LineExist(left, vert, directions, UP);
			}
			if (upAvailable) {
				int result = Solution(left + 1, top, right, bottom, directions) + left * count;
				if (result == step) {
					for (int i = leftL; i != leftR && i < horizontals.at(left).size(); ++i) {
						answer[left][horizontals.at(left).at(i)] = UP;
					}
					RestoreSolution(left + 1, top, right, bottom, directions);
					return;
				}
			}

			bool down_available = true;
			count = 0;
			for (int i = rightL; i != rightR && i < horizontals.at(right).size(); ++i) {
				int vert = horizontals.at(right).at(i);
				if (LineExist(right, vert, directions, UP)) {
					int result = Solution(left, top, right, vert - 1, CloseDirection(directions, RIGHT)) +
					             Solution(left, vert + 1, right, bottom, CloseDirection(directions, LEFT)) + right;
					if (result == step) {
						answer[right][vert] = UP;
						RestoreSolution(left, top, right, vert - 1, CloseDirection(directions, RIGHT));
						RestoreSolution(left, vert + 1, right, bottom, CloseDirection(directions, LEFT));
						return;
					}
				}
				++count;
				down_available &= LineExist(right, vert, directions, DOWN);
			}

			if (down_available) {
				int result = Solution(left, top, right - 1, bottom, directions) + (a - right) * count;
				if (result == step) {
					for (int i = rightL; i != rightR && i < horizontals.at(right).size(); ++i) {
						answer[right][horizontals.at(right).at(i)] = DOWN;
					}
					RestoreSolution(left, top, right - 1, bottom, directions);
					return;
				}
			}
		}

		if (!IsClosed(directions, LEFT) || !IsClosed(directions, RIGHT)) {
			bool left_available = true;
			int count = 0;
			for (int i = topT; i != topB && i < verticals.at(top).size(); ++i) {
				int horiz = verticals.at(top).at(i);
				if (LineExist(horiz, top, directions, RIGHT)) {
					int result = Solution(left, top, horiz - 1, bottom, CloseDirection(directions, DOWN)) +
					             Solution(horiz + 1, top, right, bottom, CloseDirection(directions, UP)) + a - top;
					if (result == step) {
						answer[horiz][top] = RIGHT;
						RestoreSolution(left, top, horiz - 1, bottom, CloseDirection(directions, DOWN));
						RestoreSolution(horiz + 1, top, right, bottom, CloseDirection(directions, UP));
						return;
					}
				}
				++count;
				left_available &= LineExist(horiz, top, directions, LEFT);
			}

			if (left_available) {
				int result = Solution(left, top + 1, right, bottom, directions) + top * count;
				if (result == step) {
					for (int i = topT; i != topB && i < verticals.at(top).size(); ++i) {
						answer[verticals.at(top).at(i)][top] = LEFT;
					}
					RestoreSolution(left, top + 1, right, bottom, directions);
					return;
				}
			}

			bool right_available = true;
			count = 0;
			for (int i = bottomT; i != bottomB && i < verticals.at(bottom).size(); ++i) {
				int horiz = verticals.at(bottom).at(i);
				if (LineExist(horiz, bottom, directions, LEFT)) {
					int result = Solution(left, top, horiz - 1, bottom, CloseDirection(directions, DOWN)) +
					             Solution(horiz + 1, top, right, bottom, CloseDirection(directions, UP)) + bottom;
					if (result == step) {
						answer[horiz][bottom] = LEFT;
						RestoreSolution(left, top, horiz - 1, bottom, CloseDirection(directions, DOWN));
						RestoreSolution(horiz + 1, top, right, bottom, CloseDirection(directions, UP));
						return;
					}
				}
				++count;
				right_available &= LineExist(horiz, bottom, directions, RIGHT);
			}
			if (right_available) {
				int result = Solution(left, top, right, bottom - 1, directions) + (a - bottom) * count;
				if (result == step) {
					for (int i = bottomT; i != bottomB && i < verticals.at(bottom).size(); ++i) {
						answer[verticals.at(bottom).at(i)][bottom] = RIGHT;
					}
					RestoreSolution(left, top, right, bottom - 1, directions);
				}
			}
		}
	}

	Microchip() {
		std::ifstream reader("input.txt");
		reader >> a >> n;

		horizontals.resize(31, std::vector<int64_t>());
		verticals.resize(31, std::vector<int64_t>());

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

private:

	int UP = 0;
	int RIGHT = 1;
	int DOWN = 2;
	int LEFT = 3;

	int dp[31][31][31][31][16]{};
	bool existence[31][31][31][31][16]{};
	int answer[31][31]{};

	int n{}, a{};
	std::vector<std::vector<int64_t>> horizontals, verticals;
};

std::string readFile(const std::string &fileName) {
	std::ifstream f(fileName);
	std::stringstream ss;
	ss << f.rdbuf();
	return ss.str();
}

int main() {
//  int amount_of_tests = 6;
//  for (int i = 0; i < amount_of_tests; ++i) {
//    std::ifstream reader("tests.txt");
//    std::string str;
//    std::getline(reader, str, '&');
//    reader.close();
//
//    std::ofstream writer("input.txt");
//    writer << str;
//    writer.close();
//
//    run();
//
//    std::string algorithm, answer;
//    reader.open("answers.txt");
//    std::getline(reader, algorithm, '&');
//
//    answer = readFile("output.txt");
//
//    if (answer == algorithm)  {
//      std::cout << "Test #" << i + 1 << " completed successfully!\n";
//    } else {
//      std::cout << "Test #" << i + 1 << " failed!\n";
//      std::ofstream log("log.txt");
//      log << algorithm << "\n -------------- \n" << answer;
//      log.close();
//      exit(123);
//    }
//  }

	Microchip microchip;
	return 0;
}