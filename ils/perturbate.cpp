#include <iostream>
#include <vector>

#include "../utils/lcr.hpp"
#include "../utils/possible_to_add.hpp"

using namespace std;

Solution perturbate(
  const Solution& solution, 
  const vector<int>& weights, 
  const vector<int>& profits, 
  const vector<vector<int>>& forfeit_pairs, 
  const int& capacity
) {
  // Inicializa perturbated_solution como uma cópia da solução atual
  Solution perturbated_solution = solution;
  
  // Sorteia "n" itens para inverter os bits (tirar / colocar na mochila)
  int flip_count = (rand() % perturbated_solution.items.size()) + 1;

  // Inverte "n" índices sorteados
  for (int i = 1; i <= flip_count; i++) {
    // Sorteia até um índice possível de inverter
    bool index_possible_to_add = false;
    int index_to_flip;
    while (!index_possible_to_add) {
      index_to_flip = rand() % perturbated_solution.items.size();

      if (perturbated_solution.items[index_to_flip] == 1) {
        index_possible_to_add = true;
      } else {
        index_possible_to_add = possible_to_add(
          index_to_flip,
          perturbated_solution,
          weights,
          forfeit_pairs,
          capacity
        );
      }
    }

    // Inverte índice sorteado
    int item_value = perturbated_solution.items[index_to_flip];
    if (item_value == 1) {
      perturbated_solution.items[index_to_flip] = 0;
      perturbated_solution.weight -= weights[index_to_flip];
      perturbated_solution.profit -= profits[index_to_flip];
    } else {
      perturbated_solution.items[index_to_flip] = 1;
      perturbated_solution.weight += weights[index_to_flip];
      perturbated_solution.profit += profits[index_to_flip];
    }
  }

  return perturbated_solution;
}
