#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <utility>

int getShortWeight(const std::vector<std::vector<char>> &map, const std::pair<int, int> &in_start, const std::pair<int, int> &in_end) {
    std::vector<std::vector<int>> weight(map.size(), std::vector<int>(map[0].size(), std::numeric_limits<int>::max()));
    std::queue<std::pair<int, int>> q;
    q.push({(in_start.first - 1), (in_start.second - 1)});
    weight[in_start.first - 1][in_start.second - 1] = 0;
    std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (auto& dir : directions) {
            if (x == (in_end.first - 1) && (y == in_end.second - 1))
                continue;
            int nx = x + dir.first, ny = y + dir.second;
            if (nx >= 0 && nx < (int)map.size() && ny >= 0 && ny < (int)map[0].size() &&
                map[nx][ny] != 'W') {
                int nweight = weight[x][y] + (map[nx][ny] == '.' ? 1 : 2);
                if(nweight < weight[nx][ny]) {
                    weight[nx][ny] = nweight;
                    q.push({nx, ny});
                }
            }
        }
    }
    // TODO return shortest path and shortest steps
    return 0;
}

bool canReach(std::vector<std::vector<char>>& grid, const std::pair<int, int> &in_start, const std::pair<int, int> &in_end) {
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

        std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (auto& dir : directions) {
            int nx = x + dir.first, ny = y + dir.second;
            if (nx >= 0 && nx < (int)grid.size() && ny >= 0 && ny < (int)grid[0].size() &&
                grid[nx][ny] != 'W' && !visited[nx][ny]) {
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

std::vector<std::vector<char>> readMap(int in_n, int in_m) {
    std::vector<std::vector<char>> grid(in_n, std::vector<char>(in_m));
    for (int i = 0; i < in_n; ++i) {
        for (int j = 0; j < in_m; ++j) {
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
    std::pair<int, int> start, end;
    
    // std::cin >> n >> m;
    // std::cin >> start.first >> start.second;
    // std::cin >> end.first >> end.second;

    // std::vector<std::vector<char>> grid = readMap(n, m);
    std::vector<std::vector<char>> grid = readMapFromFile("data.txt", n, m, start, end);

    bool pathExists = canReach(grid, start, end);
    getShortWeight(grid, start, end);
    std::cout << pathExists;
//    printMap(grid);

    return 0;
}
