#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>
#include "../utils/input.hpp"
#include "../utils/input.cpp"

using namespace std;
// Função para calcular o custo de uma solução
int custo(const vector<int>& solucao, const KnapsackData& data) {
    int valor_total = 0;
    int peso_total = 0;
    for (int i : solucao) {
        valor_total += data.profits[i];
        peso_total += data.weights[i];
    }
    if (peso_total > data.capacity) {
        return INT_MAX;  // Penalidade para soluções que excedem a capacidade da mochila
    }
    return -valor_total;
}

// Função para gerar vizinhos de uma solução
vector<vector<int>> gera_vizinhos(const vector<int>& solucao, int num_items) {
    vector<vector<int>> vizinhos;
    for (int i = 0; i < num_items; ++i) {
        vector<int> novo_vizinho = solucao;
        auto it = find(novo_vizinho.begin(), novo_vizinho.end(), i);
        if (it != novo_vizinho.end()) {
            novo_vizinho.erase(it);
        } else {
            novo_vizinho.push_back(i);
        }
        vizinhos.push_back(novo_vizinho);
    }
    return vizinhos;
}

// Função de busca tabu
vector<int> BT(const KnapsackData& data, int criterio_parada) {
    vector<int> solucao_inicial;
    vector<int> solucao = solucao_inicial;
    vector<int> melhor_solucao = solucao;
    int melhor_custo = custo(solucao, data);
    int iteracoes = 0;

    while (iteracoes < criterio_parada) {
        iteracoes++;
        auto vizinhos = gera_vizinhos(solucao, data.num_items);
        vector<int> melhor_vizinho;
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
    vector<int> melhor_solucao = BT(data, criterio_parada);

    // Imprimindo a melhor solução encontrada
    for (int item : melhor_solucao) {
        cout << "Item: " << item << " Valor: " << data.profits[item] << " Peso: " << data.weights[item] << endl;
    }

    return 0;
}
