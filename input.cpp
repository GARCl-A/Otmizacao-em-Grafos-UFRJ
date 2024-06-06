#include <iostream>
#include <fstream>
#include <vector>

void input(const char *filename, std::vector<int> &profits, std::vector<int> &weights, std::vector<std::vector<int>> &forfeit_pairs, int &num_items, int &num_pairs, int &knapsack_size) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Failed to open file" << std::endl;
    exit(EXIT_FAILURE);
  }

  file >> num_items >> num_pairs >> knapsack_size;

  // Allocate memory for profits and weights vectors
  profits.resize(num_items);
  weights.resize(num_items);

  // Read profits
  for (int i = 0; i < num_items; i++) {
    file >> profits[i];
  }

  // Read weights
  for (int i = 0; i < num_items; i++) {
    file >> weights[i];
  }

  // Resize and initialize forfeit_pairs matrix
  forfeit_pairs.resize(num_items, std::vector<int>(num_items, 0));

  // Read forfeit pairs and populate the matrix
  for (int i = 0; i < num_pairs; i++) {
    int id_0, id_1;
    file >> id_0 >> id_1;
    forfeit_pairs[id_0][id_1] = 1;
    forfeit_pairs[id_1][id_0] = 1;
  }

  file.close();
}