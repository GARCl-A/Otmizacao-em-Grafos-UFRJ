#include <iostream>
#include <vector>
#include <algorithm>

#include "../utils/grasp_constructive.hpp"
#include "../utils/local_search.hpp"
#include "../utils/lcr.hpp"
#include "../utils/compare_pairs.hpp"
#include "../utils/possible_to_add.hpp"
#include "perturbate.hpp"

using namespace std;

bool compare_solutions(const Solution& a, const Solution& b) {
  return a.profit > b.profit; // Ordena em ordem decrescente
}

Solution ils_constructive(
  const vector<int>& profits, 
  const vector<int>& weights, 
  const vector<vector<int>>& forfeit_pairs, 
  const int& num_items,
  const int& capacity,
  const float& alpha
) {  
  // Inicia vetor para armazenar soluções 
  int n = 50;
  vector<Solution> solutions(n);
  
  // Gera n soluções utilizando o construtivo do grasp
  for (size_t i = 0; i < solutions.size(); i++) {
    Solution solution = grasp_constructive(
      profits, 
      weights, 
      forfeit_pairs, 
      num_items,
      capacity, 
      alpha
    );

    solutions[i] = solution;
  }
  // Ordena soluções pelo lucro 
  sort(solutions.begin(), solutions.end(), compare_solutions);

  // Seleciona as 20% melhores soluções
  vector<Solution> best_solutions(solutions.begin(), solutions.begin() + (n * 0.2));

  // Itera sobre as 20% melhores soluções e armazena as frequências dos itens nas soluções
  vector<int> items_frequency(num_items, 0);
  for (const auto& solution : best_solutions) {
    for (size_t i = 0; i < solution.items.size(); i++) {
      if (solution.items[i] == 1) {
        items_frequency[i]++;
      }
    }
  }

  // Zera os índices menos frequentes na melhor solução
  Solution best_solution = best_solutions[0];
  for (size_t i = 0; i < items_frequency.size(); i++) {
    if (items_frequency[i] != 0 && items_frequency[i] < (0.7 * best_solutions.size())) {
      best_solution.items[i] = 0;
      best_solution.weight -= weights[i];
      best_solution.profit -= profits[i];
    }
  }
  
  // Preenche melhor solução utilizando abordagem gulosa
  vector<pair<float, int>> ratios(num_items); 
  for (int i = 0; i < num_items; i++) {
    float ratio = static_cast<float>(weights[i]) / profits[i];
    ratios[i] = {ratio, i};
  }
  sort(ratios.begin(), ratios.end(), compare_pairs);
  for (size_t i = 0; i < ratios.size(); i++) {
    int index_to_add = ratios[i].second;
    if (
      best_solution.items[index_to_add] == 0 &&
      possible_to_add(
        index_to_add,
        best_solution,
        weights,
        forfeit_pairs,
        capacity
      )
    ) {
      best_solution.items[index_to_add] = 1;
      best_solution.weight += weights[index_to_add];
      best_solution.profit += profits[index_to_add];
    }
  }
  
  return best_solution;
}