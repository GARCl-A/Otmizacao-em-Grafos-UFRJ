#include <vector>

#include "grasp_constructive.hpp"
#include "local_search.hpp"

using namespace std;

Solution local_search(
  const Solution& solution, 
  const vector<int>& profits, 
  const vector<int>& weights, 
  const vector<vector<int>>& forfeit_pairs, 
  const int& capacity
) {
  // Inicializa improved_solution como uma cópia da solução atual
  Solution improved_solution = solution;
  
  // Itera sobre os índices da solução
  for (size_t i = 0; i < solution.items.size(); ++i) {
    // Verifica se o item não está selecionado
    if (solution.items[i] == 0) {
      // Verifica se adicionar este item ultrapassará a capacidade da mochila
      if (solution.weight + weights[i] > capacity) {
        continue;  // Passa para o próximo item
      }

      // Verifica se algum item no conjunto de penalização já está selecionado
      bool has_conflict = false;
      for (size_t j = 0; j < forfeit_pairs[i].size(); ++j) {
        if (forfeit_pairs[i][j] == 1 && solution.items[j] == 1) {
          has_conflict = true;
          break;
        }
      }
      if (has_conflict) continue; // Passa para o próximo item

      // Verifica se adicionar este item melhora a solução
      if (solution.profit + profits[i] > improved_solution.profit) {
        // Atualiza improved_solution com os novos valores
        improved_solution.items = solution.items;  
        improved_solution.items[i] = 1;
        improved_solution.weight = solution.weight + weights[i];
        improved_solution.profit = solution.profit + profits[i];
      }
    }
  }

  return improved_solution;
}
