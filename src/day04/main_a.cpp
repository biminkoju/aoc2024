#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
int main(int argc, const char** argv) {
  std::fstream inputFile{"input.txt"};
  int direction[3] = {-1, 0, 1};
  int count{0};
  std::vector<std::vector<char>> grid;
  if (!inputFile.is_open()) {
    std::cerr << "unable to open the file";
    return 1;
  }
  std::string line;
  while (std::getline(inputFile, line)) {
    if (!line.empty()) {
      std::vector<char> row(line.begin(), line.end());
      grid.push_back(row);
    } else {
      std::cerr << "Warning: Skipping empty line\n";
    }
  }

  inputFile.close();

  for (size_t r = 0; r < grid.size(); r++) {
    for (size_t c = 0; c < grid[r].size(); c++) {
      if (grid[r][c] == 'X') {
        for (int dr : direction) {
          for (int dc : direction) {
            if (dr == dc && dr == 0) {
              continue;
            }
            if (!((0 <= (r + 3 * dr) && (r + 3 * dr) < grid.size()) &&
                  (0 <= (c + 3 * dc) && (r + 3 * dr) < grid[r].size()))) {
              continue;
            }
            if (grid[r + dr][c + dc] == 'M' &&
                grid[r + 2 * dr][c + 2 * dc] == 'A' &&
                grid[r + 3 * dr][c + 3 * dc] == 'S') {
              count++;
            }
          }
        }
      }
    }
  }
  std::cout << count;

  return 0;
}