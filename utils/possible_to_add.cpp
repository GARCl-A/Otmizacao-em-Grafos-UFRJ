#include <vector>

#include "grasp_constructive.hpp"

using namespace std;

bool possible_to_add(
  const int& i,
  const Solution& solution, 
  const vector<int>& weights, 
  const vector<vector<int>>& forfeit_pairs, 
  const int& capacity
) {  
  // Verifica se adicionar este item ultrapassará a capacidade da mochila
  if (solution.weight + weights[i] > capacity) {
    return false;  // Passa para o próximo item
  }

  // Verifica se tem conflito com algum item da solução
  for (size_t j = 0; j < forfeit_pairs[i].size(); ++j) {
    if (forfeit_pairs[i][j] == 1 && solution.items[j] == 1) {
      return false;
    }
  }

  return true;
}