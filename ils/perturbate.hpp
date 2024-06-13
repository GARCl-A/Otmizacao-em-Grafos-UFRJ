#ifndef PERTURBATE_HPP
#define PERTURBATE_HPP

#include <vector>

#include "../utils/grasp_constructive.hpp"

using namespace std;

// Declaração da função de perturbação
Solution perturbate(
  const Solution& solution, 
  const vector<int>& weights, 
  const vector<vector<int>>& forfeit_pairs, 
  const int& capacity,
  const vector<int>& less_frequent_items
);

#endif /* PERTURBATE_HPP */