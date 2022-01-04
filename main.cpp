/**
 * @file TextWriter.cpp
 * @author Jae Choi       ID: 01998621
 * @author Sandra Hawkins ID: 01843958
 * @brief
 * @version 0.1
 * @date 2021-11-10
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <cstdio>
#include <exception>
#include <memory>
#include <string>
#include <algorithm>

#include "RandWriter.h"

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    std::__throw_invalid_argument("Not enough arguments.");
  }
  std::string str; char ch;
  ch = std::char_traits<char>::eof();
  std::getline(std::cin, str, ch);

  int k = atoi(argv[1]);
  int L = atoi(argv[2]);
  RandWriter r(str, k);
  std::string gram = r.get_kgram();
  std::string word = r.generate(gram, L);
  std::cout << word << std::endl;
  std::cout << r << std::endl;
}
