#ifndef LOCAL_SEARCH_HPP
#define LOCAL_SEARCH_HPP

#include <vector>

#include "grasp_constructive.hpp"

using namespace std;

// Declaração da função de busca local
Solution local_search(
  const Solution& solution,
  const vector<int>& profits,
  const vector<int>& weights,
  const vector<vector<int>>& forfeit_pairs,
  const int& capacity
);

#endif /* LOCAL_SEARCH_HPP */
