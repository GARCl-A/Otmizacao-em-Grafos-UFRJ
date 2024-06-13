#ifndef ILS_CONSTRUCTIVE_HPP
#define ILS_CONSTRUCTIVE_HPP

#include <vector>

#include "../utils/grasp_constructive.hpp"

using namespace std;

// Declaração da função de construção do ils
Solution ils_constructive(
  const vector<int>& profits, 
  const vector<int>& weights, 
  const vector<vector<int>>& forfeit_pairs, 
  const int& num_items,
  const int& capacity,
  const float& alpha
);

#endif /* ILS_CONSTRUCTIVE_HPP */