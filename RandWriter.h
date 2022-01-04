/**
 * @file randomWriter.h
 * @author Jae Choi       ID: 01998621
 * @author Sandra Hawkins ID: 01843958
 * @brief
 * @version 0.1
 * @date 2021-11-10
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <random>
#include <utility>

using markov_table_t = std::map<std::string, std::map<char, int>>;

class RandWriter {
 public:
  RandWriter(const std::string &text, int k);  // text length min k
  RandWriter(RandWriter &rw) = delete;  // NOLINT
  RandWriter() = delete;
  int order_k() { return m_k; }  // order k of Markov model
  int freq(std::string k_gram);  // throw except if gram length < k
  int freq(std::string k_gram, char c);
  char k_Rand(std::string k_gram);
  std::string generate(std::string k_gram, int L);
  std::string get_kgram() { return m_kgram; }
  friend std::ostream& operator<<(std::ostream &o, RandWriter &rw);  // NOLINT
 private:
  int m_k;
  std::string m_kgram;  // current kgram string
  std::unique_ptr<std::mt19937> m_rmachine;
  markov_table_t m_markov_map;  // has frequency for next chars

  std::string getKG(const std::string &text, int i, int k);
};
