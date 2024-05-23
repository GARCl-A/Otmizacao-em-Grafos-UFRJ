import random

class Item:
    def __init__(self, weight, profit, index):
        self.weight = weight
        self.profit = profit
        self.ratio = profit / weight
        self.index = index

class BlockingPair:
    def __init__(self, item1, item2):
        self.item1 = item1
        self.item2 = item2

# Calcula (Wi / Pi) para cada item
def calculate_ratios(items):
    for item in items:
        item.ratio = item.profit / item.weight

# Ordena os itens em ordem decrescente pela razão (elemento, razão)
def construct_LCR(items, pairs, alpha, selected_indices):
    items.sort(key=lambda x: x.ratio, reverse=True)  # Ordena os itens em ordem decrescente pela razão (elemento, razão)
    
    min_ratio = items[-1].ratio  # Calcula a razão mínima e máxima (extremidades da lista em 2)
    max_ratio = items[0].ratio
    threshold = min_ratio + alpha * (max_ratio - min_ratio)

    LCR = []
    for item in items:
        # Para cada elemento da lista 2, adiciono se:
        if min_ratio <= item.ratio <= threshold and not is_blocked(item.index, pairs, selected_indices):  # b) se o par do elemento não estiver na lista
            LCR.append(item)
    
    return LCR

def is_blocked(item_index, pairs, selected_indices):
    for pair in pairs:
        if pair.item1 == item_index and pair.item2 in selected_indices:
            return True
        if pair.item2 == item_index and pair.item1 in selected_indices:
            return True
    return False

# GRASP: os pares bloqueadores serão uma lista onde o índice indica o índice dos elementos do outro par.
def GRASP(items, capacity, pairs, alpha):
    selected_indices = []
    current_weight = 0
    solution = []

    # 1- Cria o conjunto S_ com todos os elementos
    # 2- Cria o conjunto S inicialmente vazio com os elementos que entrarão na mochila
    # 3- Cria variável W com o peso da mochila (inicialmente 0)
    while items and current_weight < capacity:  # 4- Enquanto |S_| != 0 e W < C:
        LCR = construct_LCR(items, pairs, alpha, selected_indices)  # 4.1 Construo a LCR passando a S_, os pares bloqueados e A_
        
        if not LCR:
            break

        selected_item = random.choice(LCR)  # 4.2 Escolho elementos aleatórios da LCR e retiro de S_
        
        if current_weight + selected_item.weight <= capacity:  # 4.3 se W+Wi <= C:
            solution.append(selected_item)  # 4.3.1 Adiciono (Wi, Pi) a S
            current_weight += selected_item.weight  # 4.3.2 W+= Wi
            selected_indices.append(selected_item.index)

        items.remove(selected_item)

    print("Selected items:")
    for item in solution:
        print(f"Item {item.index}: Weight = {item.weight}, Profit = {item.profit}")
    print(f"Total weight: {current_weight}")

if __name__ == "__main__":
    random.seed()

    # Definir itens e pares bloqueadores aqui
    items = [Item(2, 10, 0), Item(3, 14, 1), Item(4, 16, 2), Item(5, 30, 3)]
    pairs = [BlockingPair(0, 2), BlockingPair(1, 3)]
    capacity = 7
    alpha = 0.3

    GRASP(items, capacity, pairs, alpha)
