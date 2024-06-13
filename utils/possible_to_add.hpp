#ifndef POSSIBLE_TO_ADD_HPP
#define POSSIBLE_TO_ADD_HPP

#include <vector>

#include "grasp_constructive.hpp"

using namespace std;

// Declaração da função de busca local
bool possible_to_add(
  const int& i,
  const Solution& solution, 
  const vector<int>& weights, 
  const vector<vector<int>>& forfeit_pairs, 
  const int& capacity
);

#endif /* POSSIBLE_TO_ADD_HPP */
