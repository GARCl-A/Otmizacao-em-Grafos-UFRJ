#ifndef PERTURBATE_HPP
#define PERTURBATE_HPP

#include <vector>

#include "../utils/grasp_constructive.hpp"

using namespace std;

// Declaração da função de perturbação
Solution perturbate(
  const Solution& solution, 
  const vector<int>& weights, 
  const vector<int>& profits, 
  const vector<vector<int>>& forfeit_pairs, 
  const int& capacity
);

#endif /* PERTURBATE_HPP */