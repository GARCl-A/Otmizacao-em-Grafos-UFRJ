#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

#include "../utils/input.hpp"
#include "../utils/lcr.hpp"
#include "../utils/grasp_constructive.hpp"
#include "../utils/local_search.hpp"
#include "perturbate.hpp"
#include "ils_constructive.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  const char *filename;
  float alpha = 0.75;

  // Check for the correct number of arguments
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <file_path> [alpha]\n";
    return EXIT_FAILURE;
  }

  filename = argv[1];

  // If alpha is provided, use it
  if (argc >= 3) {
    alpha = atof(argv[2]);
  }

  KnapsackData data = input(filename);

  Solution solution_star;
  Solution solution = ils_constructive(
    data.profits,
    data.weights,
    data.forfeit_pairs,
    data.num_items,
    data.capacity,
    alpha
  );
  Solution improved_solution = local_search(
    solution,
    data.profits, 
    data.weights, 
    data.forfeit_pairs, 
    data.capacity
  );
  int k = 0;
  while (k < 50) {
    Solution perturbated_solution = perturbate(
      solution, 
      data.weights,
      data.profits, 
      data.forfeit_pairs, 
      data.capacity
    );
    Solution improved_perturbated_solution = local_search(
      perturbated_solution,
      data.profits, 
      data.weights, 
      data.forfeit_pairs, 
      data.capacity
    );

    if (improved_perturbated_solution.profit > solution_star.profit) {
      solution_star = improved_perturbated_solution;
    }
    k++;
  }

  // Imprime a solução, o peso da solução e o lucro
  cout << "Solution: ";
  print_list(solution_star.items);
  cout << "Solution Weight: " << solution_star.weight << endl;
  cout << "Solution Profit: " << solution_star.profit << endl;

  // Retorna a solução, o peso da solução e o lucro
  return 0;
}