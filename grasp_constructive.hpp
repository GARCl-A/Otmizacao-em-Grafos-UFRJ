#ifndef GRASP_CONSTRUCTIVE_H
#define GRASP_CONSTRUCTIVE_H

// Inclua os cabeçalhos necessários aqui, como "linked_list.h" e outros

// Declaração da função para construir uma solução usando GRASP
void grasp_constructive(const std::vector<int>& profits, const std::vector<int>& weights, const std::vector<std::vector<int>>& forfeit_pairs, int capacity, float alpha);

#endif // GRASP_CONSTRUCTIVE_H