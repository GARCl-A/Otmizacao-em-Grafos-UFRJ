#ifndef KNAPSACK_INPUT_HPP
#define KNAPSACK_INPUT_HPP

#include <vector>

using namespace std;

// Estrutura para armazenar todos os dados
struct KnapsackData {
  vector<int> profits;
  vector<int> weights;
  vector<vector<int>> forfeit_pairs;
  int num_items;
  int num_pairs;
  int capacity;
};

// Declaração da função para ler os dados do arquivo
KnapsackData input(const string &filename);

#endif // KNAPSACK_INPUT_HPP