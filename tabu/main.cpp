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
        size_t hashValue = 0;

        // Incorpora o peso e o lucro da solução
        hash_combine(hashValue, sol.weight);
        hash_combine(hashValue, sol.profit);

        // Incorpora os itens selecionados na solução
        for (auto item : sol.items) {
            hash_combine(hashValue, item);
        }

        return hashValue;
    }

private:
    // Função auxiliar para combinar hashes
    static void hash_combine(size_t& seed, size_t value) {
        seed ^= value + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
};


// Função para calcular o custo de uma solução
int custo(const Solution& solucao, const KnapsackData& data) {
    if (solucao.weight > data.capacity) {
        std::cout << "CAPACIDADE EXCEDIDA";
        return INT_MAX;  // Penalidade para soluções que excedem a capacidade da mochila
    }

    // Verificar conflitos
    for (size_t i = 0; i < solucao.items.size(); ++i) {
        for (size_t j = i + 1; j < solucao.items.size(); ++j) {
            if (solucao.items[i] == 1 && solucao.items[j] == 1 && data.forfeit_pairs[i][j]) {
                std::cout << "CONFLITO";
                return INT_MAX;  // Penalidade para soluções com itens conflitantes
            }
        }
    }

    return -solucao.profit;
}

bool input_valido(const KnapsackData& data, int index, const Solution& solution){
    // Verifica se adicionar este item ultrapassará a capacidade da mochila
    if (solution.weight + data.weights[index] > data.capacity) {
        return false;  // Passa para o próximo item
    }

    // Verifica se tem conflito com algum item da solução
    for (size_t j = 0; j < data.forfeit_pairs[index].size(); ++j) {
        if (data.forfeit_pairs[index][j] == 1 && solution.items[j] == 1) {
        return false;
        }
    }

  return true;
}

// Função para gerar vizinhos respeitando as restrições de conflito
vector<Solution> gera_vizinhos(const Solution& solucao, const KnapsackData& data) {
    vector<Solution> vizinhos;
    int num_items = data.num_items;

    for (int i = 0; i < num_items; ++i) {
        if (solucao.items[i] == 1) {
            Solution novo_vizinho = solucao;
            novo_vizinho.weight -= data.weights[i];
            novo_vizinho.profit -= data.profits[i];
            novo_vizinho.items[i] = 0;
            
            if(input_valido(data, i, novo_vizinho)){
                vizinhos.push_back(novo_vizinho);
            }
        } else {
            Solution novo_vizinho = solucao;
            novo_vizinho.weight += data.weights[i];
            novo_vizinho.profit += data.profits[i];
            novo_vizinho.items[i] = 1;

            if(input_valido(data, i, novo_vizinho)){
                vizinhos.push_back(novo_vizinho);
            }
        }
    }

    return vizinhos;
}

// Função de busca tabu
Solution BT(const KnapsackData& data, int criterio_parada, int TABU_TENURE) {
    // Constrói uma solução inicial usando um método construtivo (GRASP)
    Solution solucao_inicial = grasp_constructive(
        data.profits, 
        data.weights, 
        data.forfeit_pairs, 
        data.num_items,
        data.capacity, 
        0.75
    );

    Solution solucao = solucao_inicial;
    Solution melhor_solucao = solucao;
    Solution melhor_vizinho = solucao;
    int melhor_custo = custo(solucao, data);
    int iteracoes = 0;
    int iteracoes_sem_melhoria = 0; // Contador para contar iterações sem melhoria na melhor solução

    unordered_set<Solution, SolutionHash> set_tabu;

    while (iteracoes < criterio_parada && iteracoes_sem_melhoria < 200) {
        iteracoes++;
        vector<Solution> vizinhos = gera_vizinhos(solucao, data);
        
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
            iteracoes_sem_melhoria = 0; // Resetar o contador de iterações sem melhoria
        } else {
            iteracoes_sem_melhoria++;
        }

        solucao = melhor_vizinho;
        // Atualizar a lista tabu
        set_tabu.insert(solucao);
        if (set_tabu.size() > static_cast<deque_size_type>(TABU_TENURE)) {
            auto it = set_tabu.begin();
            advance(it, set_tabu.size() - TABU_TENURE);
            set_tabu.erase(set_tabu.begin(), it);
        }
    }

    return melhor_solucao;
}


int main(int argc, char *argv[]) {
    const char *filename;
    int tenure = 15;

    // Verifica se o número correto de argumentos foi fornecido
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <caminho_do_arquivo> [tenure]\n";
        return EXIT_FAILURE;
    }

    filename = argv[1];

    // Se tenure (tenure) for fornecido, use-o
    if (argc >= 3) {
        tenure = atoi(argv[2]);
    }

    // Lê os dados do arquivo
    KnapsackData data = input(filename);

    // Define o critério de parada
    int criterio_parada = 2000;

    // Chama a função de busca tabu
    Solution melhor_solucao = BT(data, criterio_parada, tenure);

    // Imprime a solução, o peso da solução e o lucro
    std::cout << "Solucao: ";
    for (int item : melhor_solucao.items) {
        std::cout << item << " ";
    }
    std::cout << endl;
    std::cout << "Peso da Solucao: " << melhor_solucao.weight << endl;
    std::cout << "Lucro da Solucao: " << melhor_solucao.profit << endl;

    return 0;
}
