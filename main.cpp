#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <utility>
#include <algorithm>

const std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

std::string getShortestPath(const std::vector<std::vector<int>> &in_weight, const std::pair<int, int> &in_start, const std::pair<int, int> &in_end) {
    std::string result;
    std::pair<int, int> current(in_end.first - 1, in_end.second - 1);
    auto [x, y] = current;
    int nx = 0;
    int ny = 0;
    while(!(current.first == in_start.first - 1 && current.second == in_start.second - 1)) {
        std::pair<int, int> temp_point = {};
        int temp_weight = std::numeric_limits<int>::max();
        for(auto &&el: directions) {
            nx = x + el.first;
            ny = y + el.second;
            if(nx >= 0 && nx < (int)in_weight.size() && ny >= 0 && ny < (int)in_weight[0].size()) {
                if(temp_weight > in_weight[nx][ny]) {
                    temp_weight = in_weight[nx][ny];
                    temp_point = {nx, ny};
                }
            }
        }

        if (temp_point.first == x - 1) result += 'S';
        if (temp_point.first == x + 1) result += 'N';
        if (temp_point.second == y - 1) result += 'E';
        if (temp_point.second == y + 1) result += 'W';

        current = temp_point;
        x = temp_point.first;
        y = temp_point.second;
    }
    std::reverse(result.begin(), result.end());
    return result;
}


std::pair<int, std::string> getShortWeight(const std::vector<std::vector<char>> &map, const std::pair<int, int> &in_start, const std::pair<int, int> &in_end) {
    std::vector<std::vector<int>> weight(map.size(), std::vector<int>(map[0].size(), std::numeric_limits<int>::max()));
    std::queue<std::pair<int, int>> q;
    q.push({(in_start.first - 1), (in_start.second - 1)});
    weight[in_start.first - 1][in_start.second - 1] = 0;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (auto&& dir : directions) {
            if (x == (in_end.first - 1) && (y == in_end.second - 1))
                continue;
            int nx = x + dir.first, ny = y + dir.second;
            if (nx >= 0 && nx < (int)map.size() && ny >= 0 && ny < (int)map[0].size() &&
                map[nx][ny] != '#') {
                int nweight = weight[x][y] + (map[nx][ny] == '.' ? 1 : 2);
                if(nweight < weight[nx][ny]) {
                    weight[nx][ny] = nweight;
                    q.push({nx, ny});
                }
            }
        }
    }

    return std::make_pair(weight[in_end.first - 1][in_end.second - 1], getShortestPath(weight, in_start, in_end));
}

bool canReach(std::vector<std::vector<char>>& grid, const std::pair<int, int> &in_start, const std::pair<int, int> &in_end) {
    if(grid[in_start.first - 1][in_start.second - 1] == '#' || grid[in_end.first - 1][in_end.second - 1] == '#') return false;
    std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));
    std::queue<std::pair<int, int>> q;
    q.push({(in_start.first - 1), (in_start.second - 1)});
    visited[in_start.first - 1][in_start.second - 1] = true;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (x == (in_end.first - 1) && (y == in_end.second - 1)) {
            return true;
        }

        for (auto& dir : directions) {
            int nx = x + dir.first, ny = y + dir.second;
            if (nx >= 0 && nx < (int)grid.size() && ny >= 0 && ny < (int)grid[0].size() &&
                grid[nx][ny] != '#' && !visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
    return false;
}

std::vector<std::vector<char>> readMapFromFile(const std::string& filename,
                                            int& out_n, int& out_m,
                                            std::pair<int, int> &out_start,
                                            std::pair<int, int> &out_end) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    file >> out_n >> out_m;
    file >> out_start.first >> out_start.second;
    file >> out_end.first >> out_end.second;

    std::vector<std::vector<char>> grid(out_n, std::vector<char>(out_m));
    for (int i = 0; i < out_n; ++i) {
        for (int j = 0; j < out_m; ++j) {
            file >> grid[i][j];
        }
    }
    file.close();
    return grid;
}

std::vector<std::vector<char>> inputData(int& out_n, int& out_m,
                                        std::pair<int, int> &out_start,
                                        std::pair<int, int> &out_end) {

    std::cin >> out_n >> out_m;
    std::cin >> out_start.first >> out_start.second;
    std::cin >> out_end.first >> out_end.second;

    std::vector<std::vector<char>> grid(out_n, std::vector<char>(out_m));
    for (int i = 0; i < out_n; ++i) {
        for (int j = 0; j < out_m; ++j) {
            std::cin >> grid[i][j];
        }
    }
    return grid;
}

void printMap(const std::vector<std::vector<char>>& grid) {
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
}

int main() {
    int n = 0;
    int m = 0;
    std::pair<int, int> start;
    std::pair<int, int> end;

    std::vector<std::vector<char>> grid = inputData(n, m, start, end);

    if(!canReach(grid, start, end)) {
        std::cout << -1;
        return 0;
    }
    auto result = getShortWeight(grid, start, end);
    std::cout << result.first << std::endl << result.second;

    return 0;
}
