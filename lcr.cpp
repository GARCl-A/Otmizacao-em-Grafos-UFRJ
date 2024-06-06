#include <iostream>
#include <vector>
#include <algorithm>
#include "linked_list.hpp"

LinkedList lcr(LinkedList& solution_line, const std::vector<int>& profits, const std::vector<int>& weights, float alpha) {
  // Para cada item em solution_line
  Node* currentNode = solution_line.getHead();
  std::cout << "solution_line" << std::endl;

  solution_line.printList();
  LinkedList solution_line_sorted;

  while (currentNode != nullptr) {
    // Calcula (w[i] / p[i]) para cada item em solution_line e armazena em solution_line_sorted
    int index = currentNode->data1;

    float weight_profit_ratio = static_cast<float>(weights[index]) / profits[index];
    solution_line_sorted.addNode(weight_profit_ratio, index);
    currentNode = currentNode->next;
  }
  std::cout << "solution_line_with_weights" << std::endl;
  solution_line_sorted.printList();

  // Ordena solution_line_sorted em ordem decrescente
  solution_line_sorted = solution_line_sorted.sortListDescending();
  std::cout << "solution_line_sorted" << std::endl;
  solution_line_sorted.printList();

  // Calcula o min e max corretamente
  float min = solution_line_sorted.getTail()->data1;
  float max = solution_line_sorted.getHead()->data1;
  std::cout << "min: " << min << " | max: " << max << std::endl;

  LinkedList lcr;
  // Para cada elemento em solution_line_sorted
  Node* sortedNode = solution_line_sorted.getHead();
  std::cout << "sortedNode->data2: " << sortedNode->data2 << std::endl;
  while (sortedNode != nullptr) {
    float current_ratio = sortedNode->data1;
    float current_index = sortedNode->data2;
    // Se min <= s_line_sorted[i] <= max + alpha, adiciona o elemento na lcr
    if (min <= current_ratio && current_ratio <= max + alpha) {
      lcr.addNode(current_index);
    }
    sortedNode = sortedNode->next;
  }

  return lcr;
}

