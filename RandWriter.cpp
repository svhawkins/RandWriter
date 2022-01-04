/**
 * @file randomWriter.cpp
 * @author Jae Choi       ID: 01998621
 * @author Sandra Hawkins ID: 01843958
 * @brief
 * @version 0.1
 * @date 2021-11-10
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <vector>
#include "RandWriter.h"

const char* small = "length of kgram is smaller than k.";

RandWriter::RandWriter(const std::string &text, int k)
        : m_k(k), m_kgram("") {
  // check for valid arguments.
  if (static_cast<int>(text.size()) < k || k < 0) {
    const char* e = "RandWriter: invalid arguments.";
    throw std::invalid_argument(e);
  }
  // set random machine
  std::random_device rd;
  m_rmachine = std::make_unique<std::mt19937>(rd());

  // go through the text and fill out our markov model map
  std::string kg;
  auto grab_next_char = [&](int index) {
    return text.at((index + k) % text.size());
  };

  for (auto i = 0u; i < text.size(); i++) {
    kg = getKG(text, i, k);
    m_markov_map[kg][grab_next_char(i)]++;
    kg.clear();
  }

  // Find the first kgram string.
  if (m_k >= 0) {
    std::vector<int> kgram_weights;
    for (const auto & m : m_markov_map) {
      kgram_weights.push_back(freq(m.first));
    }
    std::discrete_distribution<int> dist(kgram_weights.begin(),
                                         kgram_weights.end());
    int kg_index = dist(*m_rmachine);
    auto itr = m_markov_map.begin();
    for (auto i = 0; i < kg_index; i++)
      itr++;
    m_kgram = (*itr).first;
  }
}

/**
 * @brief Grabs k length kgram string from text. Starting at index i
 *
 * @param text base pool of text
 * @param i starting index
 * @param k
 * @return std::string kgram substring
 */
std::string RandWriter::getKG(const std::string &text, int i, int k) {
  std::string ret;

  for (auto j = 0; j < k; ++j)
    ret.push_back(text.at([=] {
      return (i + j) % text.size(); }()));

  return ret;
}

/**
 * @brief returns frequency of k_gram
 * if length of k_gram is less than m_k throws invalid error.
 *
 * @param k_gram
 * @return int
 */
int RandWriter::freq(std::string k_gram) {
  if (static_cast<int>(k_gram.length()) < m_k)
    throw std::invalid_argument(small);

  int ret = 0;
  if (m_markov_map.find(k_gram) != m_markov_map.end())
    for (auto e : m_markov_map[k_gram])
      ret += e.second;

  return ret;
}

int RandWriter::freq(std::string k_gram, char c) {
  if (static_cast<int>(k_gram.length()) < m_k)
    throw std::invalid_argument(small);
  return m_markov_map[k_gram][c];
}

/**
 * @brief Returns error if k_gram isn't k length and if it cannot be found
 * on the markov map
 *
 * @param k_gram
 * @return next character
 */
char RandWriter::k_Rand(std::string k_gram) {
  std::vector<int> wei_ve;
  // Check for valid condition
  if (static_cast<int>(k_gram.length()) <  m_k
  ||  m_markov_map.find(k_gram) == m_markov_map.end()) {
    std::invalid_argument e("k_Rand: Invalid k_gram");
    throw e;
  }

  // populate the wei_ve
  for (const auto &val : m_markov_map[k_gram])
    wei_ve.push_back(val.second);

  std::discrete_distribution<int> dist(wei_ve.begin(), wei_ve.end());
  int index = dist(*m_rmachine);
  auto itr = m_markov_map[k_gram].begin();
  for (int i = 0; i < index; i++)
    itr++;
  // Change internally stored kgram.
  if (m_k > 0) {
    m_kgram.erase(0, 1);
    m_kgram.push_back((*itr).first);
  }

  return (*itr).first;
}

/**
 * @brief Generate and return string until L length string is created.
 *
 * @param k_gram
 * @param L
 * @return std::string
 */
std::string RandWriter::generate(std::string k_gram, int L) {
  std::string ret;
  m_kgram = k_gram;
  for (auto i = 0; i < L; ++i) {
    ret.push_back(k_Rand(m_kgram));
  }
  return ret;
}

/**
 * @brief
 * overload the stream insertion operator and display
 * the internal state of the Markov Model. Print out
 * the order, the alphabet, and the frequencies of
 * the k-grams and k+1-grams.
 *
 */
std::ostream& operator<<(std::ostream &o, RandWriter &rw) {
  o << "kgram: " << rw.m_kgram << " frequency: ";
  o << rw.freq(rw.m_kgram) << std::endl;
  // loop through the map of current kgram and then print.
  for (const auto &itr_ref : rw.m_markov_map[rw.m_kgram]) {
    o << "next possible: " << itr_ref.first << " frequency: ";
    o << itr_ref.second << std::endl;
  }
  return o;
}
