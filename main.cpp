#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::vector<char>> readMapFromFile(const std::string& filename,
                                            int& in_out_n, int& in_out_m,
                                            int& in_out_x1,int& in_out_y1,
                                            int& in_out_x2, int& in_out_y2) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    file >> in_out_n >> in_out_m;
    file >> in_out_x1 >> in_out_y1;
    file >> in_out_x2 >> in_out_y2;

    std::vector<std::vector<char>> grid(in_out_n, std::vector<char>(in_out_m));
    for (int i = 0; i < in_out_n; ++i) {
        for (int j = 0; j < in_out_m; ++j) {
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
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    
    // std::cin >> N >> M;
    // std::cin >> x1 >> y1;
    // std::cin >> x2 >> y2;

    // std::vector<std::vector<char>> grid = readMap(N, M);
    std::vector<std::vector<char>> grid = readMapFromFile("data.txt", n, m, x1, y1, x2, y2);

    printMap(grid);

    return 0;
}
