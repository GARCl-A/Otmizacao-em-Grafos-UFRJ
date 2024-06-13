#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>
#include "../utils/input.hpp"
#include "../utils/input.cpp"
#include "../utils/grasp_constructive.hpp"

using namespace std;

// Função para calcular o custo de uma solução
int custo(const Solution& solucao, const KnapsackData& data) {
    if (solucao.weight > data.capacity) {
        return INT_MAX;  // Penalidade para soluções que excedem a capacidade da mochila
    }

    // Verificar conflitos
    for (size_t i = 0; i < solucao.items.size(); ++i) {
        for (size_t j = i + 1; j < solucao.items.size(); ++j) {
            if (data.forfeit_pairs[solucao.items[i]][solucao.items[j]]) {
                return INT_MAX;  // Penalidade para soluções com itens conflitantes
            }
        }
    }

    return -solucao.profit;
}

// Função para gerar vizinhos de uma solução
vector<Solution> gera_vizinhos(const Solution& solucao, int num_items, const KnapsackData& data) {
    vector<Solution> vizinhos;
    for (int i = 0; i < num_items; ++i) {
        Solution novo_vizinho = solucao;
        auto it = find(novo_vizinho.items.begin(), novo_vizinho.items.end(), i);
        if (it != novo_vizinho.items.end()) {
            novo_vizinho.weight -= data.weights[i];
            novo_vizinho.profit -= data.profits[i];
            novo_vizinho.items.erase(it);
        } else {
            novo_vizinho.weight += data.weights[i];
            novo_vizinho.profit += data.profits[i];
            novo_vizinho.items.push_back(i);
        }
        vizinhos.push_back(novo_vizinho);
    }
    return vizinhos;
}

// Função de busca tabu
Solution BT(const KnapsackData& data, int criterio_parada) {
    Solution solucao_inicial = {{}, 0, 0};
    Solution solucao = solucao_inicial;
    Solution melhor_solucao = solucao;
    int melhor_custo = custo(solucao, data);
    int iteracoes = 0;

    while (iteracoes < criterio_parada) {
        iteracoes++;
        auto vizinhos = gera_vizinhos(solucao, data.num_items, data);
        Solution melhor_vizinho;
        int melhor_custo_vizinho = INT_MAX;

        for (const auto& vizinho : vizinhos) {
            int custo_vizinho = custo(vizinho, data);
            if (custo_vizinho < melhor_custo_vizinho) {
                melhor_vizinho = vizinho;
                melhor_custo_vizinho = custo_vizinho;
            }
        }

        if (melhor_custo_vizinho < melhor_custo) {
            melhor_solucao = melhor_vizinho;
            melhor_custo = melhor_custo_vizinho;
        }

        solucao = melhor_vizinho;
    }

    return melhor_solucao;
}

int main() {
    // Lê os dados do arquivo
    KnapsackData data = input("input.txt");

    // Definindo o critério de parada
    int criterio_parada = 1000;

    // Chamando a função de busca tabu
    Solution melhor_solucao = BT(data, criterio_parada);

    // Imprimindo a melhor solução encontrada
    for (int item : melhor_solucao.items) {
        cout << "Item: " << item << " Valor: " << data.profits[item] << " Peso: " << data.weights[item] << endl;
    }
    cout << "Total Weight: " << melhor_solucao.weight << endl;
    cout << "Total Profit: " << melhor_solucao.profit << endl;

    return 0;
}
