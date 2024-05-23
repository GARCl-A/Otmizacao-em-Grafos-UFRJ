#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int weight;
    int profit;
    double ratio;
    int index;
} Item;

typedef struct {
    int item1;
    int item2;
} BlockingPair;

// Calcula (Wi / Pi) para cada item
void calculate_ratios(Item items[], int n) {
    for (int i = 0; i < n; i++) {
        items[i].ratio = (double)items[i].profit / items[i].weight;
        items[i].index = i;
    }
}

// Ordena os itens em ordem decrescente pela razão (elemento, razão)
int compare_items(const void *a, const void *b) {
    double ratioA = ((Item *)a)->ratio;
    double ratioB = ((Item *)b)->ratio;
    return (ratioB - ratioA) > 0 ? 1 : -1;
}

// Verifica se o item está bloqueado pelos pares selecionados
int is_blocked(int itemIndex, BlockingPair pairs[], int numPairs, int selectedIndices[], int numSelected) {
    for (int i = 0; i < numPairs; i++) {
        if (pairs[i].item1 == itemIndex) {
            for (int j = 0; j < numSelected; j++) {
                if (pairs[i].item2 == selectedIndices[j]) return 1;
            }
        }
        if (pairs[i].item2 == itemIndex) {
            for (int j = 0; j < numSelected; j++) {
                if (pairs[i].item1 == selectedIndices[j]) return 1;
            }
        }
    }
    return 0;
}

// Construo a LCR da seguinte forma:
void construct_LCR(Item items[], int n, BlockingPair pairs[], int numPairs, double alpha, Item LCR[], int *lcrSize, int selectedIndices[], int numSelected) {
    qsort(items, n, sizeof(Item), compare_items); // Ordena os itens em ordem decrescente pela razão (elemento, razão)
    
    double minRatio = items[n-1].ratio; // Calcula a razão mínima e máxima (extremidades da lista em 2)
    double maxRatio = items[0].ratio;
    double threshold = minRatio + alpha * (maxRatio - minRatio);

    *lcrSize = 0;
    for (int i = 0; i < n; i++) {
        // Para cada elemento da lista 2, adiciono se:
        if (items[i].ratio >= minRatio && items[i].ratio <= threshold && 
            !is_blocked(items[i].index, pairs, numPairs, selectedIndices, numSelected)) { // b) se o par do elemento não estiver na lista
            LCR[(*lcrSize)++] = items[i];
        }
    }
}

// GRASP: os pares bloqueadores serão uma lista onde o índice indica o índice dos elementos do outro par.
void GRASP(Item items[], int n, int capacity, BlockingPair pairs[], int numPairs, double alpha) {
    Item *LCR = (Item *)malloc(n * sizeof(Item));
    int *selectedIndices = (int *)malloc(n * sizeof(int));
    int lcrSize, numSelected = 0;
    int currentWeight = 0;
    Item *solution = (Item *)malloc(n * sizeof(Item));
    int solutionSize = 0;
    
    // 1- Cria o conjunto S_ com todos os elementos
    // 2- Cria o conjunto S inicialmente vazio com os elementos que entrarão na mochila
    // 3- Cria variável W com o peso da mochila (inicialmente 0)
    while (n > 0 && currentWeight < capacity) { // 4- Enquanto |S_| != 0 e W < C:
        construct_LCR(items, n, pairs, numPairs, alpha, LCR, &lcrSize, selectedIndices, numSelected); // 4.1 Construo a LCR passando a S_, os pares bloqueados e A_
        
        if (lcrSize == 0) break;

        int randomIndex = rand() % lcrSize; // 4.2 Escolho elementos aleatórios da LCR e retiro de S_
        Item selectedItem = LCR[randomIndex];
        
        if (currentWeight + selectedItem.weight <= capacity) { // 4.3 se W+Wi <= C:
            solution[solutionSize++] = selectedItem; // 4.3.1 Adiciono (Wi, Pi) a S
            currentWeight += selectedItem.weight; // 4.3.2 W+= Wi
            selectedIndices[numSelected++] = selectedItem.index;
        }

        int removeIndex = -1;
        for (int i = 0; i < n; i++) {
            if (items[i].index == selectedItem.index) {
                removeIndex = i;
                break;
            }
        }
        
        if (removeIndex != -1) {
            for (int i = removeIndex; i < n - 1; i++) {
                items[i] = items[i + 1];
            }
            n--;
        }
    }

    printf("Selected items:\n");
    for (int i = 0; i < solutionSize; i++) {
        printf("Item %d: Weight = %d, Profit = %d\n", solution[i].index, solution[i].weight, solution[i].profit);
    }
    printf("Total weight: %d\n", currentWeight);
    
    free(LCR);
    free(selectedIndices);
    free(solution);
}

int main() {
    srand(time(NULL));

    // Definir itens e pares bloqueadores aqui
    Item items[] = {{2, 10}, {3, 14}, {4, 16}, {5, 30}};
    int numItems = sizeof(items) / sizeof(items[0]);
    BlockingPair pairs[] = {{0, 2}, {1, 3}};
    int numPairs = sizeof(pairs) / sizeof(pairs[0]);
    int capacity = 7;
    double alpha = 0.3;

    calculate_ratios(items, numItems);
    GRASP(items, numItems, capacity, pairs, numPairs, alpha);

    return 0;
}
