// Advent of Code 2024
// Day 2: Red-Nosed Reports
// https://adventofcode.com/2024/day/2

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::fstream inputFile("input.txt");
  std::vector<std::vector<int>> data;

  if (!inputFile.is_open()) {
    std::cerr << "Error: Unable to open file 'input.txt'.\n";
    return 1;
  }

  std::string line;
  while (std::getline(inputFile, line)) {
    std::stringstream ss(line);
    std::vector<int> row;
    int value;

    while (ss >> value) {
      row.push_back(value);
    }
    if (!row.empty()) {
      data.push_back(row);
    } else {
      std::cerr << "Warning: Skipping malformed or empty line: " << line
                << "\n";
    }
  }

  inputFile.close();

  for (size_t i = 0; i < data.size(); ++i) {
    std::cout << "Line " << i + 1 << ": ";
    for (int value : data[i]) {
      std::cout << value << " ";
    }
    std::cout << "\n";
  }

  int safeno{0};
  bool anysafeno = false;

  for (std::vector<int> record : data) {
    for (size_t i = 0; i < record.size(); ++i) {
      int unsafe{0};
      std::vector<int> temprecord = record;
      temprecord.erase(temprecord.begin() + i);

      for (size_t j = 0; j < temprecord.size() - 1; ++j) {
        if ((temprecord[j] - temprecord[j + 1]) == 0) {
          unsafe++;
          break;
        }
        int signcheck = std::copysign(1, temprecord[0] - temprecord[1]);
        int signnow = std::copysign(1, temprecord[j] - temprecord[j + 1]);
        if (signcheck != signnow) {
          unsafe++;
          break;
        }
        if (abs(temprecord[j] - temprecord[j + 1]) > 3) {
          unsafe++;
          break;
        }
      }

      if (unsafe == 0) {
        anysafeno = true;
      }
    }

    if (anysafeno) {
      safeno++;
    }
    anysafeno = false;
  }
  std::cout << safeno;
  return 0;
}