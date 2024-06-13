#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>
#include <deque>
#include <unordered_set>
#include "../utils/input.hpp"
#include "../utils/grasp_constructive.hpp"
#include "../utils/lcr.hpp"

using namespace std;
typedef std::deque<Solution>::size_type deque_size_type;

// Hash para a estrutura Solution para usar em unordered_set
struct SolutionHash {
    size_t operator()(const Solution& sol) const {
        size_t seed = sol.items.size();
        for (auto& i : sol.items) {
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed ^ (sol.weight + sol.profit);
    }
};

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
Solution BT(const KnapsackData& data, int criterio_parada, int TABU_TENURE) {
    Solution solucao_inicial = {{}, 0, 0};
    Solution solucao = solucao_inicial;
    Solution melhor_solucao = solucao;
    int melhor_custo = custo(solucao, data);
    int iteracoes = 0;

    deque<Solution> lista_tabu;
    unordered_set<Solution, SolutionHash> set_tabu;

    while (iteracoes < criterio_parada) {
        iteracoes++;
        auto vizinhos = gera_vizinhos(solucao, data.num_items, data);
        Solution melhor_vizinho;
        int melhor_custo_vizinho = INT_MAX;

        for (const auto& vizinho : vizinhos) {
            int custo_vizinho = custo(vizinho, data);
            if (custo_vizinho < melhor_custo_vizinho && set_tabu.find(vizinho) == set_tabu.end()) {
                melhor_vizinho = vizinho;
                melhor_custo_vizinho = custo_vizinho;
            }
        }

        if (melhor_custo_vizinho < melhor_custo) {
            melhor_solucao = melhor_vizinho;
            melhor_custo = melhor_custo_vizinho;
        }

        solucao = melhor_vizinho;

        // Atualizar a lista tabu
        lista_tabu.push_back(solucao);
        set_tabu.insert(solucao);
        if (lista_tabu.size() > static_cast<deque_size_type>(TABU_TENURE)) {
            set_tabu.erase(lista_tabu.front());
            lista_tabu.pop_front();
        }
    }

    return melhor_solucao;
}

int main(int argc, char *argv[]) {
    const char *filename;
    int tenure = 5;

    // Check for the correct number of arguments
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <file_path> [alpha]\n";
        return EXIT_FAILURE;
    }

    filename = argv[1];

    // If alpha is provided, use it
    if (argc >= 3) {
        tenure = atof(argv[2]);
    }

    // Lê os dados do arquivo
    KnapsackData data = input(filename);

    // Definindo o critério de parada
    int criterio_parada = 1000;

    // Chamando a função de busca tabu
    Solution melhor_solucao = BT(data, criterio_parada, tenure);

    // Imprime a solução, o peso da solução e o lucro
    cout << "Solution: ";
    print_list(melhor_solucao.items);
    cout << "Solution Weight: " << melhor_solucao.weight << endl;
    cout << "Solution Profit: " << melhor_solucao.profit << endl;

    return 0;
}
