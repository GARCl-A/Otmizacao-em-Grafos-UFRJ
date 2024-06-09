#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "input.hpp"

using namespace std;

// Função para ler os dados do arquivo
KnapsackData input(const string &filename) {
  KnapsackData data;

  ifstream file(filename);
  if (!file) {
    cerr << "Failed to open file" << endl;
    exit(EXIT_FAILURE);
  }

  file >> data.num_items >> data.num_pairs >> data.capacity;

  // Redimensiona os vetores de acordo com o número de itens
  data.profits.resize(data.num_items);
  data.weights.resize(data.num_items);

  // Lê os lucros
  for (int i = 0; i < data.num_items; i++) {
    file >> data.profits[i];
  }

  // Lê os pesos
  for (int i = 0; i < data.num_items; i++) {
    file >> data.weights[i];
  }

  // Redimensiona e inicializa a matriz de pares de penalidade
  data.forfeit_pairs.resize(data.num_items, vector<int>(data.num_items, 0));

  // Lê os pares de penalidade e preenche a matriz
  for (int i = 0; i < data.num_pairs; i++) {
    int id_0, id_1;
    file >> id_0 >> id_1;
    data.forfeit_pairs[id_0][id_1] = 1;
    data.forfeit_pairs[id_1][id_0] = 1;
  }

  file.close();
  return data;
}