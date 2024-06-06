#include <iostream>
#include <cstdlib>
#include "input.hpp"
#include "linked_list.hpp"
#include "grasp_constructive.hpp"

int main(int argc, char *argv[]) {
  const char *filename;
  double alpha = 0.75;

  // Check for the correct number of arguments
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <file_path> [alpha]\n";
    return EXIT_FAILURE;
  }

  filename = argv[1];

  // If alpha is provided, use it
  if (argc >= 3) {
    alpha = atof(argv[2]);
  }

  std::vector<int> profits, weights;
  std::vector<std::vector<int>> forfeit_pairs;
  int num_items, num_pairs, capacity;

  input(filename, profits, weights, forfeit_pairs, num_items, num_pairs, capacity);
  grasp_constructive(profits, weights, forfeit_pairs, capacity, alpha); 

  // No need to free allocated memory when using vectors

  return 0;
}
