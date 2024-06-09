#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "../utils/lcr.hpp"
#include "grasp_constructive.hpp"

using namespace std;

Solution grasp_constructive(
  const vector<int>& profits, 
  const vector<int>& weights, 
  const vector<vector<int>>& forfeit_pairs, 
  const int& num_items,
  const int& capacity,
  const float& alpha
) {
  // Variável para manter itens já avaliados
  int evaluated_items = num_items;
  // Criação da solution_line
  vector<int> solution_line(num_items, 1);
  for (int i = 0; i < num_items; i++) {
    if (weights[i] > capacity) {
      solution_line[i] = 0;
      evaluated_items--;
    }
  }
  print_list(solution_line);

  // Criação da solution
  vector<int> solution(num_items, 0);
  print_list(solution);

  // Variáveis para manter o peso e o lucro da solução
  int solution_weight = 0;
  int solution_profit = 0;

  // Enquanto solution_line não estiver vazia
  while (evaluated_items > 0 || solution_weight >= capacity) {
    cout << "executando" << endl;
    // Construindo lcr a partir de solution_line
    vector<int> lcr_list = lcr(
      solution_line, 
      profits, 
      weights, 
      alpha
    );
    cout << "lcr_list" << endl;
    print_list(lcr_list);

    // Escolhe um elemento aleatório de lcr
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    int random_index = rand() % lcr_list.size(); // Gera um índice aleatório dentro do tamanho da lista
    int random_element = lcr_list[random_index];

    // Remove o elemento de solution_line
    solution_line[random_element] = 0;
    evaluated_items--;

    // Adiciona o elemento a solution
    solution[random_element] = 1;

    // Soma weights[elemento] a solution_weight
    solution_weight += weights[random_element];

    // Soma profits[elemento] a solution_profit
    solution_profit += profits[random_element];

    print_list(solution_line);
    print_list(solution);

    // Itera sobre solution_line para remover elementos
    for (size_t i = 0; i < solution_line.size(); i++) {
      // Remove elementos que weights[i] > (capacity - solution_weight)
      if (solution_line[i] != 0 && weights[i] > (capacity - solution_weight)) {
        solution_line[i] = 0;
        evaluated_items--;
        continue;
      }

      // Remove elementos que têm conflito com o elemento
      if (solution_line[i] != 0 && forfeit_pairs[random_element][i] == 1) {
        solution_line[i] = 0;
        evaluated_items--;
        continue;
      }
    }
    print_list(solution_line);
  }

  // Imprime a solução, o peso da solução e o lucro
  cout << "Solution: ";
  print_list(solution);
  cout << "Solution Weight: " << solution_weight << endl;
  cout << "Solution Profit: " << solution_profit << endl;

  // Retorna a solução, o peso da solução e o lucro
  return { solution, solution_weight, solution_profit };
}
