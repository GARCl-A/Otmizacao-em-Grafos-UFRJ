#include <iostream>
#include <vector>

#include "grasp_constructive.hpp"
#include "../utils/lcr.hpp"
#include "../utils/possible_to_add.hpp"

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

  cout << "iniciando busca local" << endl;
  
  // Itera sobre os índices de improved_solution
  for (size_t i = 0; i < improved_solution.items.size(); ++i) {
    // Verifica se o item está
    if (improved_solution.items[i] == 1) {
      // Cria solução retirando o item
      Solution new_solution;
      new_solution.items = improved_solution.items;
      new_solution.items[i] = 0;
      new_solution.profit = improved_solution.profit - profits[i];
      new_solution.weight = improved_solution.weight - weights[i];

      cout << "improved_solution" << endl;
      print_list(improved_solution.items);
      cout << "new_solution" << endl;
      print_list(new_solution.items);

      // Tenta adicionar um item que não está 
      for (size_t j = 0; j < new_solution.items.size(); ++j) {
        if (
          j != i &&
          new_solution.items[j] == 0 && 
          possible_to_add(
            j,
            new_solution,
            weights,
            forfeit_pairs,
            capacity
          ) &&
          new_solution.profit + profits[j] > improved_solution.profit
        ) { // Adiciona item na mochila
            cout << "adicionou índice: " << j << endl;
            improved_solution = new_solution;
            improved_solution.items[j] = 1;
            improved_solution.profit += profits[j];
            improved_solution.weight += weights[j];
            cout << "improved_solution" << endl;
            print_list(improved_solution.items);
            i = 0;
        }
      }
    }
  }

  // Encontrou ótimo local
  return improved_solution;
}
