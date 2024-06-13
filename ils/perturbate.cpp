#include <iostream>
#include <vector>

#include "../utils/lcr.hpp"
#include "../utils/possible_to_add.hpp"

using namespace std;

Solution perturbate(
  const Solution& solution, 
  const vector<int>& weights, 
  const vector<vector<int>>& forfeit_pairs, 
  const int& capacity,
  const vector<int>& less_frequent_items = vector<int>() 
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
      if (less_frequent_items.size() == 0) {
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
      } else {
        // Se recebe vetor de índices menos frequentes, sorteia índice da lista
        for (size_t i = 1; i < less_frequent_items.size(); i++) {
          if (possible_to_add(
            index_to_flip,
            perturbated_solution,
            weights,
            forfeit_pairs,
            capacity
          )) {
            index_to_flip = less_frequent_items[i];
            break;
          }
        }
        index_possible_to_add = true;
      }
    }

    // Inverte índice sorteado
    int item_value = perturbated_solution.items[index_to_flip];
    perturbated_solution.items[index_to_flip] = (item_value == 1) ? 0 : 1;
  }

  return perturbated_solution;
}
