#ifndef GRASP_CONSTRUCTIVE_H
#define GRASP_CONSTRUCTIVE_H

struct SolutionResult {
  LinkedList solution;
  int solution_weight;
  int solution_profit;
};

// Declaração da função para construir uma solução usando GRASP
SolutionResult grasp_constructive(const std::vector<int>& profits, const std::vector<int>& weights, const std::vector<std::vector<int>>& forfeit_pairs, int capacity, float alpha);

#endif // GRASP_CONSTRUCTIVE_H