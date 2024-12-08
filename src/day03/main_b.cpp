#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

int main() {
  std::fstream inputFile("input.txt");
  std::vector<std::vector<std::string>> data;

  if (!inputFile.is_open()) {
    std::cerr << "Error: Unable to open file 'input.txt'.\n";
    return 1;
  }

  std::string line;
  while (std::getline(inputFile, line)) {
    std::stringstream ss(line);
    std::vector<std::string> row;
    std::string value;

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

  int temp{1};
  int net{0};
  int donet{0};
  bool doing = true;

  std::regex word_regex("(mul\\([0-9]+,[0-9]+\\)|do\\(\\)|don't\\(\\))");
  std::regex mul_regex("[0-9]+");

  for (auto svec : data) {
    for (auto s : svec) {
      auto words_begin = std::sregex_iterator(s.begin(), s.end(), word_regex);
      auto words_end = std::sregex_iterator();

      for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();

        if (match_str == "do()") {
          doing = true;
        } else if (match_str == "don't()") {
          doing = false;
        } else if (doing) {
          auto num_begin = std::sregex_iterator(match_str.begin(),
                                                match_str.end(), mul_regex);
          auto num_end = std::sregex_iterator();

          for (std::sregex_iterator j = num_begin; j != num_end; ++j) {
            std::smatch num_match = *j;
            std::string num_str = num_match.str();
            temp *= std::stoi(num_str);
          }
          net += temp;
          temp = 1;
        }
      }
    }
  }
  std::cout << net << std::endl;
  return 0;
}