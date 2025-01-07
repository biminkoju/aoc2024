#include <cstdio>
#include <fstream>
#include <iostream>
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

  for (size_t r = 1; r < (grid.size() - 1); r++) {
    for (size_t c = 1; c < (grid[r].size() - 1); c++) {
      if (grid[r][c] != 'A') {
        continue;
      }
      char corners[4] = {grid[r - 1][c - 1], grid[r - 1][c + 1],
                         grid[r + 1][c + 1], grid[r + 1][c - 1]};
      std::string joint(corners, 4);

      if (joint == "MMSS" || joint == "SMMS" || joint == "SSMM" ||
          joint == "MSSM") {
        count++;
      }
    }
  }
  std::cout << count;

  return 0;
}