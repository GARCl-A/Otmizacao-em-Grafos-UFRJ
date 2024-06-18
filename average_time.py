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

# Calcular o tempo máximo para cada tamanho de instância
max_times = {}
for size in instance_sizes:
    df_size = df[df['Instance'].str.contains(f'{size} Itens')]
    max_time = df_size['Average Time'].max()
    max_times[size] = max_time if not pd.isnull(max_time) else 0

# Plotando gráficos separados para cada tamanho de instância
for size in instance_sizes:
    # Filtrar os dados para o tamanho de instância específico e os algoritmos desejados
    df_filtered = df[(df['Instance'].str.contains(f'{size} Itens')) & (df['Executable'].isin(algorithms))]
    
    # Extraindo os dados relevantes para Average Time
    executables = df_filtered['Executable']
    times = df_filtered['Average Time']

    # Configuração do gráfico
    plt.figure(figsize=(10, 6))
    
    # Plotando gráfico de barras para Average Time com escala linear
    bars = plt.bar(executables, times, color=[colors[algo] for algo in executables])
    plt.xlabel('Algoritmo')
    plt.ylabel('Average Time (s)')
    plt.title(f'Average Time para {size} Itens')
    plt.ylim(0, max_times[size] * 1.1)  # Usando o tempo máximo específico para o tamanho de instância

    # Adicionar legenda customizada para cores
    legend_labels = [plt.Rectangle((0,0),1,1, color=colors[algo]) for algo in algorithms]
    plt.legend(legend_labels, algorithms)

    # Exibindo e salvando o gráfico
    plt.tight_layout()
    plt.savefig(f'comparacoes_tempo_{size}_itens.png')
    plt.show()
