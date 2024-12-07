// Advent of Code 2024
// Day 1: Historian Hysteria
// https://adventofcode.com/2024/day/1

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::vector<int> a, b;
  std::fstream inputFile("input.txt");

  if (!inputFile.is_open()) {
    std::cerr << "Error: Unable to open file 'input.txt'.\n";
    return 1;
  }

  std::string line;
  while (std::getline(inputFile, line)) {
    std::stringstream ss(line);
    int first, second;

    if (ss >> first >> second) {
      a.push_back(first);
      b.push_back(second);
    } else {
      std::cerr << "Warning: Skipping malformed line: " << line << "\n";
    }
  }

  inputFile.close();

  std::stable_sort(a.begin(), a.end());
  std::stable_sort(b.begin(), b.end());

  int sim{0}, simscore{0};

  long long netDistance = 0;
  for (size_t i = 0; i < a.size(); ++i) {
    netDistance += std::abs(a[i] - b[i]);
    for (size_t j = 0; j < a.size(); ++j) {
      if (a[i] == b[j]) {
        sim++;
      }
    }
    simscore += sim * a[i];
    sim = 0;
  }

  std::cout << "Net difference: " << netDistance << "\n";
  std::cout << "simmilarity score: " << simscore << "\n";
  return 0;
}
