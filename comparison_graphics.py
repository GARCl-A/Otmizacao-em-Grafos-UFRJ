import pandas as pd
import matplotlib.pyplot as plt

# Dados fornecidos (exemplo)
file_path = 'tabela_processada.csv'  # Caminho para o arquivo processado
df = pd.read_csv(file_path)

# Tamanhos de instância desejados
instance_sizes = [500, 700, 800, 1000]

# Algoritmos desejados
algorithms = ['ils', 'grasp', 'tabu']

# Cores para os algoritmos
colors = {'ils': 'blue', 'grasp': 'green', 'tabu': 'orange'}

# Configurações para o gráfico
plt.figure(figsize=(12, 12))

# Plotando gráficos para cada tamanho de instância
for i, size in enumerate(instance_sizes):
    plt.subplot(4, 2, i*2 + 1)

    # Filtrar os dados para o tamanho de instância específico e os algoritmos desejados
    df_filtered = df[(df['Instance'].str.contains(f'{size} Itens')) & (df['Executable'].isin(algorithms))]
    
    # Extraindo os dados relevantes
    executables = df_filtered['Executable']
    profits = df_filtered['Best Profit']

    # Plotando gráfico de barras para Best Profit
    bars = plt.bar(executables, profits, color=[colors[algo] for algo in executables])
    plt.xlabel('Algoritmo')
    plt.ylabel('Best Profit')
    plt.title(f'Best Profit para {size} Itens')
    plt.ylim(0, df['Best Profit'].max() * 1.1)  # Ajuste para melhor visualização dos dados

    # Adicionar legenda customizada para cores
    legend_labels = [plt.Rectangle((0,0),1,1, color=colors[algo]) for algo in algorithms]
    plt.legend(legend_labels, algorithms)

    plt.subplot(4, 2, i*2 + 2)

    # Extraindo os dados relevantes para Average Time
    times = df_filtered['Average Time']

    # Plotando gráfico de barras para Average Time com escala linear
    bars = plt.bar(executables, times, color=[colors[algo] for algo in executables])
    plt.xlabel('Algoritmo')
    plt.ylabel('Average Time')
    plt.title(f'Average Time para {size} Itens')
    plt.ylim(1, 2000)  # Ajuste para melhor visualização dos dados

    # Adicionar legenda customizada para cores
    plt.legend(legend_labels, algorithms)

# Ajustes finais e exibição do gráfico
plt.tight_layout()
plt.savefig('comparacoes.png')
plt.show()
