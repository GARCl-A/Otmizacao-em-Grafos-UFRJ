#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "linked_list.hpp"
#include "lcr.hpp"

void grasp_constructive(const std::vector<int>& profits, const std::vector<int>& weights, const std::vector<std::vector<int>>& forfeit_pairs, int capacity, float alpha) {
  // Criação da solution_line
  LinkedList solution_line;
  for (int i = 0; i < profits.size(); i++) {
    if (weights[i] <= capacity) {
      solution_line.addNode(i);
    }
  }
  solution_line.printList();

  // Criação da solution
  LinkedList solution;
  solution.printList();

  // Variáveis para manter o peso e o lucro da solução
  int solution_weight = 0;
  int solution_profit = 0;

  // Enquanto solution_line não estiver vazia
  while (solution_line.getSize() > 0) {
    std::cout << "executando" << std::endl;
    // Construindo lcr a partir de solution_line
    LinkedList lcr_list = lcr(solution_line, profits, weights, alpha);
    std::cout << "lcr_list" << std::endl;
    lcr_list.printList();

    // Escolhe um elemento aleatório de lcr
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    int random_index = rand() % lcr_list.getSize(); // Gera um índice aleatório dentro do tamanho da lista
    int random_element = lcr_list.removeNodeByIndex(random_index)->data1;

    // Remove o elemento de solution_line
    solution_line.removeNodeByData(random_element);

    // Adiciona o elemento a solution
    solution.addNode(random_element);

    // Soma weights[elemento] a solution_weight
    solution_weight += weights[random_element];

    // Soma profits[elemento] a solution_profit
    solution_profit += profits[random_element];

    solution_line.printList();
    solution.printList();

    // Itera sobre solution_line para remover elementos
    Node* currentNode = solution_line.getHead();
    while (currentNode) {
      int current_element = currentNode->data1;

      // Remove elementos que weights[i] > (capacity - solution_weight)
      if (weights[current_element] > (capacity - solution_weight)) {
        std::cout << "remove por peso: " << current_element << std::endl;
        Node* nextNode = currentNode->next;
        solution_line.removeNodeByData(current_element);
        currentNode = nextNode;
        continue;
      }

      // Remove elementos que têm conflito com o elemento
      if (forfeit_pairs[random_element][current_element] == 1) {
        std::cout << "remove por par: " << current_element << std::endl;
        Node* nextNode = currentNode->next;
        solution_line.removeNodeByData(current_element);
        currentNode = nextNode;
        continue;
      }

      currentNode = currentNode->next;
    }
  }

  // Imprime a solução, o peso da solução e o lucro
  std::cout << "Solution: ";
  solution.printList();
  std::cout << "Solution Weight: " << solution_weight << std::endl;
  std::cout << "Solution Profit: " << solution_profit << std::endl;
}
