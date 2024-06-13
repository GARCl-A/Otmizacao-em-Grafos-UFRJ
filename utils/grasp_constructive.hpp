#ifndef GRASP_CONSTRUCTIVE_H
#define GRASP_CONSTRUCTIVE_H

#include <vector>

using namespace std;

struct Solution {
  vector<int> items;
  int weight;
  int profit;
};

// Declaração da função para construir uma solução usando GRASP
Solution grasp_constructive(
  const vector<int>& profits, 
  const vector<int>& weights, 
  const vector<vector<int>>& forfeit_pairs, 
  const int& num_items,
  const int& capacity, 
  const float& alpha
);

#endif // GRASP_CONSTRUCTIVE_H