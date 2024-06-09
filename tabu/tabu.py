def BT(solucao_inicial, criterio_parada, capacidade_maxima):
    solucao = solucao_inicial
    melhor_solucao = solucao
    melhor_custo = custo(solucao, capacidade_maxima)
    iteracoes = 0
    while not iteracoes >= criterio_parada:
        iteracoes += 1
        vizinhos = gera_vizinhos(solucao, capacidade_maxima)
        melhor_vizinho = None
        melhor_custo_vizinho = float('inf')
        for vizinho in vizinhos:
            custo_vizinho = custo(vizinho)
            if custo_vizinho < melhor_custo_vizinho:
                melhor_vizinho = vizinho
                melhor_custo_vizinho = custo_vizinho
        if melhor_custo_vizinho < melhor_custo:
            melhor_solucao = melhor_vizinho
            melhor_custo = melhor_custo_vizinho
        solucao = melhor_vizinho
    return melhor_solucao

def custo(solucao, capacidade_maxima):
    valor_total = 0
    peso_total = 0
    for item in solucao:
        valor_total += item['valor']
        peso_total += item['peso']
    if peso_total > capacidade_maxima:
        return float('inf')  # Penalidade para soluções que excedem a capacidade da mochila
    return -valor_total

def gera_vizinhos(solucao, mochila):
    vizinhos = []
    for i in range(len(mochila)):
        novo_vizinho = solucao[:]
        if mochila[i] in solucao:
            novo_vizinho.remove(mochila[i])
        else:
            novo_vizinho.append(mochila[i])
        vizinhos.append(novo_vizinho)
    return vizinhos
